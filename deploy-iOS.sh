#!/bin/sh

# Script does not work if the project is not checked out in correct directory
cd ~/Documents/w2a/
rm -rf ~/Documents/w2a/ios-build
rm -rf ~/Desktop/w2a.ipa
mkdir ios-build
cd ios-build
echo $1 > ~/Documents/w2a/01-Code/config-files/configfile-client.txt
~/Qt-ios/5.5/ios/bin/qmake ~/Documents/w2a/01-Code/Web2App-mobile.pro -r -spec macx-ios-clang CONFIG+=iphoneos
#unlock keychain for ssh access to signing certificate (User dependant :( )
security unlock-keychain -p synnext /Users/da3/Library/Keychains/login.keychain
make release-iphoneos
mkdir Payload
cp -R Release-iphoneos/Web2App-mobile.app Payload
zip -r Web2App-mobile.ipa Payload
mv Web2App-mobile.ipa ~/Desktop/