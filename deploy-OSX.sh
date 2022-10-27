#!/bin/sh

# Script does not work if the project is not checked out in correct directory
cd ~/Documents/w2a
rm -rf ~/Documents/w2a/macos-build
rm -rf ~/Desktop/w2a.dmg
mkdir macos-build
cd macos-build
echo $1 > ~/Documents/w2a/01-Code/config-files/configfile-client.txt
~/Qt/5.5/clang_64/bin/qmake ~/Documents/w2a/01-Code/Web2App.pro -r -spec macx-clang CONFIG+=x86_64 -config release
make
~/Qt/5.5/clang_64/bin/macdeployqt Web2App.app/ -qmldir=~/Documents/w2a/01-Code/qml/ -dmg
make clean
rm -rf Web2App.app Makefile .qmake.stash
mv w2a.dmg ~/Desktop/
