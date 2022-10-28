TEMPLATE = app

QT += qml quick widgets core
CONFIG += c++11

CONFIG(debug, release|debug):DEFINES += _DEBUG
CONFIG(release, release|debug):DEFINES += _PRINTTOFILE
DEFINES += STANDALONE_VIEWER _WEB2APP


SOURCES += main.cpp \
    domparser.cpp \
    qhttpconnection.cpp \
    qhttprequest.cpp \
    qhttpresponse.cpp \
    qhttpserver.cpp \
    http_parser.c \
    qjson.cpp \
    colorcomponents.cpp \
    sslserver.cpp \
    documenthandler.cpp \
    skinprovider.cpp \
    resizer.cpp \
    settingsprovider.cpp \
    simplecrypt.cpp \
    colorimageprovider.cpp \
    colorimageresponse.cpp \
    recursivevariantmodifier.cpp

RESOURCES += qml-mobile.qrc \ 
	    skins.qrc \
    defaultconfig.qrc


#Android only
android{
    QT += positioning androidextras
    ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android
    DEFINES+= LYV_MOBILE

    equals(ANDROID_TARGET_ARCH, armeabi-v7a) {
        ANDROID_EXTRA_LIBS = $$PWD/OpenSSL-Libs/android-armv7/libcrypto.so $$PWD/OpenSSL-Libs/android-armv7/libssl.so
    }
    equals(ANDROID_TARGET_ARCH, armeabi) {
        ANDROID_EXTRA_LIBS = $$PWD/OpenSSL-Libs/android-armv7/libcrypto.so $$PWD/OpenSSL-Libs/android-armv7/libssl.so
    }
    equals(ANDROID_TARGET_ARCH, x86)  {
        ANDROID_EXTRA_LIBS = $$PWD/OpenSSL-Libs/android-x86/libcrypto.so $$PWD/OpenSSL-Libs/android-x86/libssl.so
    }
}


# ios only
ios {
    # Info.plist file path
    QMAKE_INFO_PLIST = ios/Info.plist
    #Icons need to be included in application bundle
    QT += positioning
    databases.files = $$files($$PWD/ios/xp-apt.sqlite)
    databases.path = Documents
    ios_icon.files = $$files($$PWD/ios/*.png)
    QMAKE_BUNDLE_DATA += ios_icon  databases
    DEFINES+= LYV_MOBILE
#for notifications, may crash ios-version if not compileable
    HEADERS+=ios/notificationclientios.h
    OBJECTIVE_SOURCES+=ios/notificationclientios.mm
#plugins need to be explicitly imported for ios
    QTPLUGIN += qsqlite qavfcamera
}

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH = qml

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    domparser.h \
    http_parser.h \
    qhttpconnection.h \
    qhttprequest.h \
    qhttpresponse.h \
    qhttpserver.h \
    qhttpserverapi.h \
    qhttpserverfwd.h \
    qjson.h \
    colorcomponents.h \
    sslserver.h \
    documenthandler.h\
    skinprovider.h \
    resizer.h \
    settingsprovider.h \
    simplecrypt.h \
    colorimageprovider.h \
    colorimageresponse.h \
    recursivevariantmodifier.h



OTHER_FILES += \
    android/AndroidManifest.xml \
    synnext.rc \
    synnext.ico

DISTFILES += \
    android/src/org/qtproject/web2apps/FileOpener.java  
