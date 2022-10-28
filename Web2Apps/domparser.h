#ifndef DOMPARSER_H
#define DOMPARSER_H
#include <qobject.h>
#include <qstring.h>
#include <QVariant>
#include <QVariantList>
#include <QMap>
#include <QNetworkReply>


//#undef STANDALONE_VIEWER
class DomParser: public QObject
{
    Q_OBJECT
public:
    DomParser();
    Q_PROPERTY(QVariantMap content READ content NOTIFY contentChanged)
    Q_PROPERTY(bool fullEditor READ fullEditor NOTIFY fullEditorChanged)
    Q_PROPERTY(QStringList pageList READ pageList NOTIFY pageListChanged)
    Q_PROPERTY(QString currentPage READ currentPage WRITE setCurrentPage NOTIFY currentPageChanged)

    void setCurrentPage(QString page);
    QString currentPage(){
        return _currentPage;
    }
QVariantMap defaultPageEntry(QString container="", QString name="",QStringList urls=QStringList());

    int fullEditor(){
#ifndef STANDALONE_VIEWER
        return true;
#else
        return false;
#endif
    }

    void setContent(QVariantList path, QVariant value);

    QVariant getContent(QVariantList path);
        QVariant getConfig(QVariantList path);
#ifndef STANDALONE_VIEWER

    void updateElementForContainer(QString container,
                              int position,
                              QString part,
                              QString field,
                              QVariant value);

    void setConfig(QVariantList path, QVariant value);



    Q_INVOKABLE void updateElementParam(int position,
                                        QString field,
                                        QVariant value);
    Q_INVOKABLE void updateElementContent(int position,
                                          QString field,
                                          QVariant value);

    Q_INVOKABLE void updateParam(QString field,
                                 QVariant value);



    void updateElementParamForContainer(QString container,
                                   int position,
                                   QString field,
                                   QVariant value);




    Q_INVOKABLE void updatePosition(int position, int offset);
    Q_PROPERTY(QString currentContainer READ currentContainer WRITE setCurrentContainer NOTIFY currentContainerChanged)
    Q_PROPERTY(int currentItem READ currentItem WRITE setCurrentItem NOTIFY currentItemChanged)
    void setCurrentContainer(QString container){
        setCurrentItem(-1);
        _currentContainer=container;
        emit currentContainerChanged();
    }
    QString currentContainer(){
        return _currentContainer;
    }
    void setCurrentItem(int currentItem){
        _currentItem=currentItem;
        emit currentItemChanged();
    }
    int currentItem(){
        return _currentItem;
    }

    Q_INVOKABLE void addItem(QString type,QString value);


    void insertItemToContainer(QString container,
                             QString url,
                             QVariantMap itemInPage,
                             QVariantMap style);
    void addDOMItemToContainer(QString container, QVariantMap domtreeSpec);

    QString getNewPage(QString url, bool virtualPage=false);
#endif

    Q_INVOKABLE void updateContainerConfig(QString container,
                                     QString field,
                                     QVariant value);
    Q_INVOKABLE void updatePageConfig(QString page,
                                     QString field,
                                     QVariant value);

    QString getNewContainer(bool virtualContainer=false);
    QString createAutoContainerForUrl(QString basePage, QString url,QRegExp urlRegex);

    QVariantMap content(){
        return _content;
    }
    QStringList pageList();
    Q_INVOKABLE void resetProject();
    Q_INVOKABLE QString getPageFromUrl(QString url);
    void createContentContainerBasedOnConfigCOntainer(QString configPage,
                                            QString contentPage,
                                            QRegExp overrideUrlsFor=QRegExp("["),
                                            QString overidingUrl="");
    bool copyFileToCache(QString uploadFileName, QString uniqueFileName);

    QNetworkReply* downloadFile(QString downloadFileName, bool openAfterDownload);
    QString getRandomString();
#ifndef STANDALONE_VIEWER
    Q_INVOKABLE void loadConfig();
    Q_INVOKABLE void storeConfig();
#endif
    void writeContentToFile(QString path,QByteArray content);
    Q_INVOKABLE void storeContent();
    Q_INVOKABLE void loadContent();
    void loadVirtualContent(QString contentPage,
                           QString newPage,
                           QRegExp urlRegex,
                           QString url);

    QString _currentPage;
    int _currentItem;
    QString _currentContainer;
    QVariantMap _content;

    QString mCacheFolder;
signals:
    void contentChanged();
    void pageListChanged();
    void currentPageChanged();
    void fullEditorChanged();
    void currentItemChanged();
    void currentContainerChanged();


public slots:
#ifndef STANDALONE_VIEWER
    //void configDownloadProgress(qint64 bytesReceived, qint64 bytesTotal);
    void configDownloadFinished();

#endif
    //void contentDownloadProgress(qint64 bytesReceived, qint64 bytesTotal);
    void contentDownloadFinished();

    //void uniqueContentDownloadProgress(qint64 bytesReceived, qint64 bytesTotal);
    void uniqueContentDownloadFinished();

    void finished(QNetworkReply*);
private:
    QString _newPage;
    QVariantMap _config;
    QNetworkAccessManager* networkManager;
};

extern DomParser * domParser;
Q_DECLARE_METATYPE(DomParser *)
#endif // DOMPARSER_H
