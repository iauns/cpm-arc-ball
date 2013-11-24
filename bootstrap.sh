#!/usr/bin/env bash

# Install toolchain for g++-4.8
sudo add-apt-repository ppa:ubuntu-toolchain-r/test -y
sudo apt-get update -qq

# Install OSMesa
sudo apt-get install libosmesa6-dev -y
sudo apt-get install -qq g++-4.8
sudo apt-get install freeglut3-dev -y
