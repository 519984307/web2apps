cd C:\synnext_build\32bits
del synnext-setup-32.exe 
call "C:\Program Files (x86)\Microsoft Visual Studio 12.0\VC\vcvarsall.bat" x86
set PATH=C:\Qt\5.5\msvc2013\bin;%PATH%
set QTDIR=C:\Qt\5.5\msvc2013
echo %1 > C:\svn-synnext-code\SynNext\config-files\configfile-client.txt
"C:\Qt\5.5\msvc2013\bin\qmake.exe" "C:\svn-synnext-code\SynNext\SynNext.pro" -r -spec win32-msvc2013
"C:\Qt\Tools\QtCreator\bin\jom.exe" -f Makefile.Release
"C:\Qt\Tools\QtCreator\bin\jom.exe" -f Makefile.Release clean
cd C:\synnext_build\32bits
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
xcopy /S /q /Y C:\Qt\5.5\msvc2013\bin\Qt5MultimediaWidgets.dll release
xcopy /S /q /Y C:\Qt\5.5\msvc2013\bin\Qt5MultimediaQuick_p.dll release
xcopy /S /q /Y C:\Qt\5.5\msvc2013\bin\Qt5Multimedia.dll release
xcopy /S /q /Y C:\Qt\5.5\msvc2013\plugins\mediaservice release\mediaservice
xcopy /S /q /Y C:\Qt\Tools\msvc2013\bin\*.dll release
xcopy /S C:\Qt\5.5\msvc2013\qml\QtGraphicalEffects release\QtGraphicalEffects
xcopy /S C:\Qt\5.5\msvc2013\qml\QtQuick.2 release\QtQuick.2
xcopy /S C:\Qt\5.5\msvc2013\qml\QtQuick release\QtQuick
xcopy /S C:\Qt\5.5\msvc2013\qml\Qt release\Qt
xcopy /S C:\Qt\5.5\msvc2013\qml\QtQml release\QtQml
xcopy /S C:\Qt\5.5\msvc2013\qml\QtMultimedia release\QtMultimedia
#BE REALLY CAREFULL WHEN CHANING THAT! Recursive delete without prompt!
cd C:\synnext_build\32bits
del /s C:\synnext_build\32bits\*d.dll
del /s C:\synnext_build\32bits\*.pdb
"C:\Qt\5.5\msvc2013\bin\windeployqt" --release --qmldir C:\synnext_build\32bits\release\qml C:\synnext_build\32bits\release\SynNext.exe
"C:\Program Files (x86)\Inno Setup 5\iscc" "C:\svn-synnext-code\Windows-Installer\SynNext - msvc.iss"
echo Finished script.