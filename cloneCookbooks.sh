#!/bin/bash

if [ ! -d ./cookbooks ]; then
  mkdir cookbooks
fi

function CloneCookbook
{
  DIR_NAME=$1
  REPO_NAME=$2
  if [ ! -d ${DIR_NAME} ]; then
    git clone ${REPO_NAME} ${DIR_NAME}
  fi
}

CloneCookbook ./cookbooks/build-essential https://github.com/opscode-cookbooks/build-essential.git 
CloneCookbook ./cookbooks/apt https://github.com/opscode-cookbooks/apt.git 
CloneCookbook ./cookbooks/nodejs https://github.com/mdxp/nodejs-cookbook.git 
CloneCookbook ./cookbooks/git https://github.com/opscode-cookbooks/git.git 
CloneCookbook ./cookbooks/subversion https://github.com/opscode-cookbooks/subversion.git
CloneCookbook ./cookbooks/cmake https://github.com/phlipper/chef-cmake.git 
CloneCookbook ./cookbooks/vim http://github.com/opscode-cookbooks/vim
CloneCookbook ./cookbooks/python-software-properties https://github.com/nisaacson/chef-python-software-properties.git

