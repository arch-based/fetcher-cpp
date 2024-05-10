<p align="center"><img src="https://github.com/arch-based/fetcher-cpp/blob/main/fetcher.png?raw=true"></p>
<h1 align="center">fetcher-based</h1>
<p align="center">A pretty bash system information tool re-written in pure C++</p><br>

# Deprecation
_**After the rust reimplementation, this has now been deprecated. The rust re-implementation is way safer and better because of the fact this programming language is nice but unsecure with its vulnerabilities.**_

# Description

This rewrite of fetcher-based prioritizes speed and resource efficiency by focusing 
on essential data retrieval with minimal overhead. This makes it a good
choice when you need system information quickly and simply. The only tool
that lets you become an elitist of Arch Linux by showing you the old coding language: CPP/C++. It only has 100 lines of code.

The old "fetcher" script is a lightweight Bash tool that displays system information very quickly but it quickly got rewritten in Pure C++ no shell script at all, because of its immense slowness :( it was 0.3 seconds away from our goal of 0.10 seconds of 0.13. Now with C++ it's 0.8! :) 

Using time scales we scaled that fast fetch, is 0.14 in user, and 0.8 in system, while with my tool it is 0.04s in system, and 0.08s in user. Although my tool is faster, it is said that fastfetch is universal, while my tool is just for arch linux. You can choose between us! No worries, I am not forcing you to use my tool.

As said, this tool is focused on arch-based systems or arch linux itself as the only repo that it supports for now is in the A.U.R format or in this github repo.

# Installation

Since this git repo isn't offering a binary for the cpp rewrite but the A.U.R tarball has, you'll have to compile it yourself or extract the tarball using the following:
```
$ git clone https://github.com/arch-based/fetcher-cpp
cd fetcher-cpp
$ g++ system_info.cpp -o fetcher
# mv fetcher /usr/bin/fetcher
```
To install using the A.U.R repo, use any aur-helper using paru or yay.

```
# For paru:
$ paru -S fetcher-based

# For yay:
$ yay -S fetcher-based
```

If you'd like to use the A.U.R repo manually, use this method:
```
$ git clone https://aur.archlinux.org/fetcher-based.git ~/fetcher-based
$ cd fetcher-based
$ makepkg -si 
```
To do it manually using the tarball:
```
$ wget https://github.com/arch-based/fetcher-cpp/raw/main/fetcher.tar.gz -O fetcher.tar.gz
$ tar -xvf fetcher.tar.gz
$ chmod 0755 fetcher
$ mv fetcher /usr/bin/fetcher
```
# Usage

You can use it with the command: fetcher which is inside of /usr/bin.
```
fetcher
```
