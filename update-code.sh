#!/bin/sh

# Script does not work if the project is not checked out in correct directory
cd ~/Documents/w2a/
/usr/local/bin/svn up --depth=files
/usr/local/bin/svn up $1 01-Code