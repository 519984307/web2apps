cd C:\w2a_build\64bits
del w2a-setup-64.exe 
call "C:\Program Files (x86)\Microsoft Visual Studio 12.0\VC\vcvarsall.bat" x64
set PATH=C:\Qt\5.5\msvc2013_64\bin;%PATH%
set QTDIR=C:\Qt\5.5\msvc2013_64
echo %1 > C:\svn-w2a-code\w2a\config-files\configfile-client.txt
"C:\Qt\5.5\msvc2013_64\bin\qmake.exe" "C:\svn-w2a-code\w2a\Web2App.pro" -r -spec win32-msvc2013
"C:\Qt\Tools\QtCreator\bin\jom.exe" -f Makefile.Release
"C:\Qt\Tools\QtCreator\bin\jom.exe" -f Makefile.Release clean
cd C:\w2a_build\64bits
rmdir /q /s release\QtGraphicalEffects
rmdir /q /s release\QtQuick.2
rmdir /q /s release\QtQuick
rmdir /q /s release\QtMultimedia
rmdir /q /s release\mediaservice
rmdir /q /s release\Qt
rmdir /q /s release\QtQml
mkdir release\QtGraphicalEffects
mkdir release\QtQuick.2
mkdir release\QtQuick
mkdir release\Qt
mkdir release\QtQml
mkdir release\QtMultimedia
mkdir release\mediaservice
xcopy /S /q /Y C:\Qt\5.5\msvc2013_64\bin\Qt5MultimediaWidgets.dll release
xcopy /S /q /Y C:\Qt\5.5\msvc2013_64\bin\Qt5MultimediaQuick_p.dll release
xcopy /S /q /Y C:\Qt\5.5\msvc2013_64\bin\Qt5Multimedia.dll release
xcopy /S /q /Y C:\Qt\5.5\msvc2013_64\plugins\mediaservice release\mediaservice
xcopy /S /q /Y C:\Qt\Tools\msvc2013_64\bin\*.dll release
xcopy /S C:\Qt\5.5\msvc2013_64\qml\QtGraphicalEffects release\QtGraphicalEffects
xcopy /S C:\Qt\5.5\msvc2013_64\qml\QtQuick.2 release\QtQuick.2
xcopy /S C:\Qt\5.5\msvc2013_64\qml\QtQuick release\QtQuick
xcopy /S C:\Qt\5.5\msvc2013_64\qml\Qt release\Qt
xcopy /S C:\Qt\5.5\msvc2013_64\qml\QtQml release\QtQml
xcopy /S C:\Qt\5.5\msvc2013_64\qml\QtMultimedia release\QtMultimedia
#BE REALLY CAREFULL WHEN CHANING THAT! Recursive delete without prompt!
cd C:\w2a_build\64bits
del /s C:\w2a_build\64bits\*d.dll
del /s C:\w2a_build\64bits\*.pdb
"C:\Qt\5.5\msvc2013_64\bin\windeployqt" --release --qmldir C:\w2a_build\32bits\release\qml C:\w2a_build\64bits\release\Web2App.exe
"C:\Program Files (x86)\Inno Setup 5\iscc" "C:\svn-w2a-code\Windows-Installer\w2a - msvc - 64.iss"
echo Finished script.