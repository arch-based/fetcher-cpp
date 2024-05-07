#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdlib> // for system()
#include <cstring> // for getenv() and gethostname()
#include <functional>
#include <unordered_map>

using namespace std;

// Function to execute a command and capture its output
string captureOutput(const string& command) {
  FILE* pipe = popen(command.c_str(), "r");
  if (!pipe) return "";

  char buffer[128];
  string result;
  while (fgets(buffer, sizeof(buffer), pipe) != NULL) {
    result += buffer;
  }
  pclose(pipe);
  return result;
}
// Function to parse a line from /proc/meminfo
pair<string, long long> parseLine(const string& line) {
  stringstream ss(line);
  string key, value;
  getline(ss, key, ':');
  getline(ss, value);
  value.erase(remove_if(value.begin(), value.end(), ::isspace), value.end()); // Remove whitespaces
  return {key, stoll(value.substr(0, value.size() - 2))}; // Remove "kB"
}
string readFile(const string& filename) {
  ifstream file(filename);
  if (file.is_open()) {
    string line;
    getline(file, line);
    file.close();
    return line;
  } else {
    cerr << "Error opening file: " << filename << endl;
    return "";
  }
}

int main() {
  string name = readFile("/sys/devices/virtual/dmi/id/product_name");
  string version = readFile("/sys/devices/virtual/dmi/id/product_version");

  // Handle potential errors where files might not be accessible
  if (name.empty() || version.empty()) {
    cerr << "Warning: Unable to read system name or version information." << endl;
  }

  string model; // Add logic to read model if needed (similar to name and version)

  string host = name + " " + version + (model.empty() ? "" : " " + model);


  ifstream meminfo("/proc/meminfo");
  if (!meminfo.is_open()) {
    cerr << "Error opening /proc/meminfo" << endl;
    return 1;
  }

  long long mem_total = 0, mem_used = 0, mem_avail = 0;
  unordered_map<string, function<void(long long&)>> memory_handlers = {
    {"MemTotal", [&](long long& value) { mem_total = value; }},
    {"Shmem", [&](long long& value) { mem_used += value; }},
    {"MemFree", [&](long long& value) { mem_used -= value; }},
    {"Buffers", [&](long long& value) { mem_used -= value; }},
    {"Cached", [&](long long& value) { mem_used -= value; }},
    {"SReclaimable", [&](long long& value) { mem_used -= value; }},
    {"MemAvailable", [&](long long& value) { mem_avail = value; }}
  };

  string line;
  while (getline(meminfo, line)) {
    auto [key, value] = parseLine(line);
    if (memory_handlers.count(key)) {
      memory_handlers[key](value);
    }
  }

  if (mem_avail) {
    mem_used = (mem_total - mem_avail) / 1024;
  } else {
    mem_used /= 1024;
  }

  mem_total /= 1024;
  string mem_label = "MiB"; // Modify this for different units (e.g., GiB)
  string memory = to_string(mem_used) + mem_label + " / " + to_string(mem_total) + mem_label;

  string bold = captureOutput("tput bold");
  string reset = captureOutput("tput sgr0");
  string hostname = captureOutput("cat /etc/hostname");
  string os_info = captureOutput("hostnamectl | grep \"Operating System\" | awk '{print $3,$4}'");
  string uptime_info = captureOutput("uptime -p | sed 's/up //'");
  string kernel_info = captureOutput("uname -sr");
  string shell_info = captureOutput("basename $SHELL");
	// string hostname = captureOutput("cat /etc/hostname");
  // Replace with your package manager command
  string package_count = captureOutput("pacman -Qe | wc -l");
  cout << "\033[36m" << bold << "                    " << getenv("USER") << "\033[37m" << bold << "@" "\033[36m" << bold << hostname;
  cout << "\033[36m" << bold << "          ------------------------------" << endl;

  cout << "\033[36m" << bold << " OS: ~~~~~~~~~> " << "\033[37m" << bold << os_info;
  cout << "\033[36m" << bold << "󰌢 HOST: ~~~~~~~> " << "\033[37m" << bold << host << endl;
  cout << "\033[36m" << bold << "󰅐 UPTIME: ~~~~~> " << "\033[37m" << bold << uptime_info;
  cout << "\033[36m" << bold << " KERNEL: ~~~~~> " << "\033[37m" << bold << kernel_info;
  cout << "\033[36m" << bold << " SHELL: ~~~~~~> " << "\033[37m" << bold << shell_info;
  cout << "\033[36m" << bold << " PACKAGES: ~~~> " << "\033[37m" << bold << package_count;
  cout << "\033[36m" << bold << "󰍛 MEMORY: ~~~~~> " << "\033[37m" << bold << memory << endl << endl;

  return 0;
}
