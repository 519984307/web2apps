TEMPLATE = app

QT += core qml quick widgets webengine webkitwidgets xml webkitwidgets
CONFIG += c++11
DEFINES += _PRINTTOFILE CONVERSION_SERVER _WEB2APP

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
    sslserver.cpp \
    skinprovider.cpp \
    resizer.cpp \
    settingsprovider.cpp \
    simplecrypt.cpp \
    recursivevariantmodifier.cpp \
    uploader.cpp

RESOURCES += qml.qrc
#Android only
# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

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
    sslserver.h \
    skinprovider.h \
    resizer.h \
    settingsprovider.h \
    simplecrypt.h \
    recursivevariantmodifier.h \
    uploader.h

OTHER_FILES += \
    android/AndroidManifest.xml \
    synnext.rc \
    synnext.ico
