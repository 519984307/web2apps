#include <QGuiApplication>
#include <QApplication>
#include <QQmlApplicationEngine>
#ifndef STANDALONE_VIEWER
#include <colorcomponents.h>
#include <webpageprovider.h>
#include <serverhandler.h>
#include <QtWebEngine>
#endif
#include <qobject.h>
#include <qhttpserver.h>
#include <qhttprequest.h>
#include <qqmlcontext.h>
#include <qhttpresponse.h>
#include <domparser.h>
#ifndef CONVERSION_SERVER
#include <documenthandler.h>
#include <colorimageprovider.h>
#endif
#include <skinprovider.h>
#include <resizer.h>
#include <QStandardPaths>
#include <settingsprovider.h>
#include <qjson.h>
#include <QDateTime>

DomParser * domParser;



#ifdef _PRINTTOFILE
FILE * pFile=0;
void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg){
    QByteArray localMsg = msg.toLocal8Bit();
    if(pFile!=0){
        fprintf(pFile, "%s (%s:%u, %s)\n\r", localMsg.constData(),context.file , context.line, context.function);
        fflush(pFile);
    } else {
        fprintf(stderr, "%s (%s:%u, %s)\n\r", localMsg.constData(),context.file , context.line, context.function);
        fflush(stderr);
    }
}
#endif



int main(int argc, char *argv[])
{

    QApplication app(argc, argv); // Not directly used but necessary for creating QWebpage

    qDebug()<<"WHAT";
    exit(0);
    return 0;
    qsrand(uint(QDateTime::currentMSecsSinceEpoch() & 0xFFFFFFFF));

    //Bug reported here: https://bugreports.qt.io/browse/QTBUG-44505
#ifdef _PRINTTOFILE
#if 0
    /* Code for Windows Mobile */
    QDir().mkdir(QString(QStandardPaths::writableLocation(QStandardPaths::AppDataLocation)+"/indexed"));
    qDebug() << QStandardPaths::writableLocation(QStandardPaths::AppDataLocation)+"/indexed/synnext-debug-log.txt";
    pFile = fopen (QString(QStandardPaths::writableLocation(QStandardPaths::AppDataLocation)+"/indexed/synnext-debug-log.txt").toLocal8Bit().constData(),"w");
#endif

    QDir().mkdir(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation));
    qDebug() << QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation)+"/w2a-debug-log.txt";
    pFile = fopen (QString(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation)+"/w2a-debug-log.txt").toLocal8Bit().constData(),"w");
    if(pFile){
        qDebug() << "Installing new debug handler!" ;
        qInstallMessageHandler(myMessageOutput);
    } else {
        qDebug() << "Could not open output file!" ;
    }

#endif
#ifdef STANDALONE_VIEWER
    QString mCacheFolder =
        QStandardPaths::writableLocation(QStandardPaths::GenericDataLocation) + "/w2a/";

    QDir uploadDir(mCacheFolder);
    if (!uploadDir.exists()) {
      if (!uploadDir.mkpath(mCacheFolder)) {
        qDebug() << "Fatal! Unable to create dir for files";
      } else {
          qDebug() << "Copy config file";
          if(!QFile::copy(":/config-files/content.js",mCacheFolder+"content.js")){
            qDebug() << "Error while copying";
          } else {
            QFile::setPermissions(mCacheFolder+"content.js",QFileDevice::WriteOther);
          }
      }
    }
#endif
    //QGuiApplication app(argc, argv);

    domParser = new DomParser();
    g_Skins = new SkinProvider();
    g_Settings = new settingsprovider();
    g_Resizer = new resizer();

    QQmlApplicationEngine viewer;


#ifndef CONVERSION_SERVER
    viewer.rootContext()->setContextProperty("domParser", domParser);
    qmlRegisterType<DocumentHandler>("MyDocument", 1, 0, "DocumentHandler");
    viewer.rootContext()->setContextProperty("skin", g_Skins);
    viewer.rootContext()->setContextProperty("s", &g_Resizer->s);
    viewer.addImageProvider(QLatin1String("ip"), new ColorImageProvider);
#endif

#ifdef STANDALONE_VIEWER
    //Load last cached version
    QFile f(mCacheFolder+"content.js");
    if (f.open(QFile::ReadOnly | QFile::Text)){
        QTextStream in(&f);
        QString contentString=in.readAll();
        //QVariant definition=
        domParser->_content=QJson::decode(contentString).toMap();
        f.close();
    }
    domParser->loadContent();
    viewer.load(QUrl(QStringLiteral("qrc:/qml/mainPhone.qml")));
#else
    viewer.load(QUrl(QStringLiteral("qrc:/qml/Server.qml")));
    //qputenv("QT_QUICK_CONTROLS_STYLE", "Flat");
    g_webPageProvider = new webPageProvider();
    domParser->loadConfig();

    QtWebEngine::initialize();

#ifndef CONVERSION_SERVER
    qmlRegisterType<ColorComponents>("ColorComponents", 1, 0, "ColorComponents");
    viewer.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));
#endif // CONVERSION_SERVER

    // Start Server listening
    ServerHandler * serverHandler = new ServerHandler();
    QHttpServer *server = new QHttpServer;
    QObject::connect(server, SIGNAL(newRequest(QHttpRequest*, QHttpResponse*)),
                     serverHandler, SLOT(handle(QHttpRequest*, QHttpResponse*)));
#ifndef CONVERSION_SERVER
    server->listen(8080);
#else
    server->listen(8181);
#endif

#endif  // STANDALONE_VIEWER

    return app.exec();
}

