TEMPLATE = app

QT += gui core qml quick webengine webkitwidgets xml svg
CONFIG += c++11

DEFINES += _WEB2APP
CONFIG(release, release|debug):DEFINES += _PRINTTOFILE

SOURCES += main.cpp \
    domparser.cpp \
    qhttpconnection.cpp \
    qhttprequest.cpp \
    qhttpresponse.cpp \
    qhttpserver.cpp \
    serverhandler.cpp \
    http_parser.c \
    qjson.cpp \
    webpageprovider.cpp \
    colorcomponents.cpp \
    sslserver.cpp \
    documenthandler.cpp \
    skinprovider.cpp \
    resizer.cpp \
    settingsprovider.cpp \
    simplecrypt.cpp \
    recursivevariantmodifier.cpp \
    uploader.cpp \
    colorimageprovider.cpp \
    colorimageresponse.cpp \
    webexplorer.cpp

RESOURCES += qml.qrc \
    images.qrc \
    skins.qrc

# Additional import path used to resolve qml modules in Qt Creator's code model
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
    serverhandler.h \
    qjson.h \
    webpageprovider.h \
    colorcomponents.h \
    sslserver.h \
    documenthandler.h \
    skinprovider.h \
    resizer.h \
    settingsprovider.h \
    simplecrypt.h \
    recursivevariantmodifier.h \
    uploader.h \
    colorimageprovider.h \
    colorimageresponse.h \
    webexplorer.h

DISTFILES += \
    android/src/org/qtproject/web2apps/FileOpener.java
