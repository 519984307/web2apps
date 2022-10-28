#include "domparser.h"
#include <QDebug>

#include <qeventloop.h>
#include <qthread.h>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <qjson.h>
#include <QUrlQuery>
#include <QStandardPaths>
#include <QDesktopServices>
#include <recursivevariantmodifier.h>
#include <skinprovider.h>
#include <QRegExp>
#include <QDir>
#include <uploader.h>
#include <webexplorer.h>


QVariantMap DomParser::defaultPageEntry(QString container, QString name,QStringList urls) {
    QVariantMap page;
    QVariantMap config;
    config["urls"]=urls;
    page["config"]=config;
    page["container"]=container;
    page["name"]=name;
    return page;
}

DomParser::DomParser()
{

    resetProject();
    // Makes sure folders for cache, thumbnails and update are created
    mCacheFolder = QStandardPaths::writableLocation(QStandardPaths::GenericDataLocation) + "/w2a/";
    QDir uploadDir(mCacheFolder);
    if (!uploadDir.exists())
        if (!uploadDir.mkpath(mCacheFolder))
            qDebug() << "Error (File Downloader): Could not create cache directory ";

    networkManager = new QNetworkAccessManager();
    connect(networkManager,SIGNAL(finished(QNetworkReply*)),
                              this,SLOT(finished(QNetworkReply*)));
}

void DomParser::finished(QNetworkReply* reply){
    if(reply->error()!=QNetworkReply::NoError){
        qDebug() << "Warning! Error in reply:"<<reply->errorString();
    }

}
void DomParser::setContent(QVariantList path, QVariant value){
    _content=RecursiveVariantModifier::changeValue(_content,path,value).toMap();
}
QVariant DomParser::getConfig(QVariantList path){
    return RecursiveVariantModifier::getValue(_config,path);
}
QVariant DomParser::getContent(QVariantList path){
    return RecursiveVariantModifier::getValue(_content,path);
}


void DomParser::setCurrentPage(QString page){
    _currentPage=page;
    emit currentPageChanged();

#ifndef STANDALONE_VIEWER
    setCurrentContainer(getConfig(QVariantList()<<"pages"<<page<<"container").toString());
    setCurrentItem(-1);
#endif
}



#ifndef STANDALONE_VIEWER

// Blocking function ! Not good :-)
void DomParser::updateParam(QString field,
                            QVariant value){
    _content[field]=value;
    _config[field]=value;

    emit contentChanged();
}


void DomParser::updatePosition(int position, int offset){
    /* update content */

    QVariantList path;
    path << "container" << _currentContainer << "content";

    QVariantList pageItems = getContent(path).toList();
    if(offset==0){
        pageItems.removeAt(position);
    } else {
        pageItems.move(position,position+offset);
    }
    setContent(path,pageItems);

    pageItems = getConfig(path).toList();
    if(offset==0){
        pageItems.removeAt(position);
    } else {
        pageItems.move(position,position+offset);
    }
    setConfig(path,pageItems);

    emit contentChanged();

}

void DomParser::updateElementContent(int position,
                                     QString field,
                                     QVariant value){
    updateElementForContainer(_currentContainer,position,"content",field,value);
}
void DomParser::updateElementParam(int position,
                                   QString field,
                                   QVariant value){
    updateElementForContainer(_currentContainer,position,"param",field,value);
}


void DomParser::updateElementForContainer(QString container,
                                     int position,
                                     QString part,
                                     QString field,
                                     QVariant value){

    qDebug() << "Changing" << field << "of element"
             << QString::number(position) << " for container "
             << container
             << " to value " << value;


    QVariantList path;
    path << "container" << container << "content" << position << part << field ;
    setContent(path,value);
    setConfig(path,value);

    emit contentChanged();

}


void DomParser::setConfig(QVariantList path, QVariant value){
    _config=RecursiveVariantModifier::changeValue(_config,path,value).toMap();
}


void DomParser::addDOMItemToContainer(QString container,
                                 QVariantMap domtreeSpec){
    qDebug() << Q_FUNC_INFO << domtreeSpec;
    if(pageList().isEmpty()){
        resetProject();
    }


    // Add url to page if it's not inside
    QVariantList urlPath;
    urlPath << "container" << container << "config" << "urls";
    QStringList urls = getConfig(urlPath).toStringList();

    QString newUrl=domtreeSpec["url"].toString();
    if(!urls.contains(newUrl)){
        qDebug() << "TODO: Add wildcard check here!!!!";
        urls << newUrl;
        setConfig(urlPath,urls);
    }




    QVariantList path;
    path << "container" << container << "content" << -1;
    QVariantMap itemInPage;
    itemInPage["url"]=newUrl;
    itemInPage["path"]=domtreeSpec["path"].toList();

    setConfig(path,itemInPage);


    insertItemToContainer(container,
                              itemInPage["url"].toString(),
                              WebExplorer::getItemFromUrl(itemInPage["path"].toList(),
                                             newUrl),
                              itemInPage["param"].toMap());

    emit contentChanged();
    emit pageListChanged();
}



void DomParser::addItem(QString type,
                        QString value){
    /* Add item to config */


    QVariantList path;
    //-1 adds elements to lists
    path << "container" << _currentContainer << "content" << -1;


    QVariantMap content;
    QVariantMap itemInPage;
    content["type"]=type;
    content["html"]=value;
    itemInPage["content"]=content;

    setConfig(path,itemInPage);
    setContent(path,itemInPage);


    emit contentChanged();
    emit pageListChanged();

}

void DomParser::insertItemToContainer(QString container,
                                          QString url,
                                          QVariantMap itemInPage,
                                          QVariantMap style){

    qDebug() << "insertWebElementToContent " + url +
                "container:" <<container;


    itemInPage["param"]=style;

    QVariantList path;
    path << "container" << container << "content" << -1;

    setContent(path,itemInPage);

    emit contentChanged();


}


#endif
void DomParser::updatePageConfig(QString page,
                                 QString field,
                                 QVariant value){

    qDebug() << "Changing" << field << " for page "
             << page
             << " to value " << value;
    /* update content */

    QVariantList path;
    path << "pages" << page << "config" << field  ;
    setContent(path,value);

#ifndef STANDALONE_VIEWER
    /* update config */
    setConfig(path,value);
#endif
    emit contentChanged();

}
void DomParser::updateContainerConfig(QString container,
                                 QString field,
                                 QVariant value){

    qDebug() << "Changing" << field << " for container "
             << container
             << " to value " << value;
    /* update content */

    QVariantList path;
    path << "container" << container << "config" << field  ;
    setContent(path,value);

#ifndef STANDALONE_VIEWER
    /* update config */
    setConfig(path,value);
#endif
    emit contentChanged();

}



QString DomParser::createAutoContainerForUrl(QString baseContainer,
                                        QString url,
                                        QRegExp urlRegex){


    QString newContainer=getNewContainer(true);


#ifdef STANDALONE_VIEWER
    loadVirtualContent(baseContainer,newContainer,urlRegex, url);
#else
    createContentContainerBasedOnConfigCOntainer(baseContainer,newContainer,urlRegex,url);
#endif
    return newContainer;
}

QString DomParser::getNewContainer(bool virtualContainer){
    int counter=1;
    QVariantMap existingContainer=getContent(QVariantList() << "container").toMap();
    QString containerName="c"+QString::number(counter);
    while(existingContainer.contains(containerName)){
        counter++;
        containerName="c"+QString::number(counter);
    }


#ifndef STANDALONE_VIEWER
    setConfig(QVariantList() << "container"<<containerName,QVariantMap());
#endif
    setContent(QVariantList() << "container"<<containerName,QVariantMap());

    qDebug() <<  "Returning new containername " << containerName;
    return containerName;
}

Q_INVOKABLE void DomParser::resetProject(){
    _config.clear();
    _content.clear();

    setCurrentPage(getNewPage("/"));
    emit contentChanged();
    emit pageListChanged();
}

QStringList DomParser::pageList(){
    QStringList returnVal;
    QVariantMap configPagesList=_config["pages"].toMap();
    for(QVariantMap::const_iterator i = configPagesList.begin();
        i != configPagesList.end();
        ++i) {

        returnVal<<i.key();
    }
    return returnVal;
}




Q_INVOKABLE QString DomParser::getPageFromUrl(QString url){
    qDebug() << "Todo: DomParser should transform following"
                " url to valid page number" << url;
    QVariantMap pageUrls;
    pageUrls = _content["pages"].toMap();

    for(QVariantMap::const_iterator i = pageUrls.begin();
        i != pageUrls.end();
        ++i) {
        QVariantMap pageDefinition=i.value().toMap();
        QVariantMap pageConfig = pageDefinition["config"].toMap();
        QStringList urlsForPage = pageConfig["urls"].toStringList();

        if(urlsForPage.contains(url)){
            qDebug() << "Found page " << i.key() << "for url" << url;
            return i.key();
        }
    }

#ifndef CONVERSION_SERVER
    for(QVariantMap::const_iterator i = pageUrls.begin();
        i != pageUrls.end();
        ++i) {

        QVariantMap pageDefinition=i.value().toMap();
        QVariantMap pageConfig = pageDefinition["config"].toMap();
        QStringList urlsForPage = pageConfig["urls"].toStringList();

        for(int j=0;j<urlsForPage.count();j++){
            if(urlsForPage.at(j).contains("*")){
                /* May be a regex */
                QRegExp matcher(urlsForPage.at(j),
                                Qt::CaseSensitive,
                                QRegExp::Wildcard);
                if(url.contains(matcher)){
                    qDebug() << url + "matches a qregex!" << i.key();
                    //Create a new container
                    QString container=createAutoContainerForUrl(i.value().toMap()["container"].toString(),url,matcher);
                    qDebug() << "TODO: Implement!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1";
                    return "";
                }
            }
        }
    }



    QString newPageName="";
#ifndef STANDALONE_VIEWER
    qDebug() << "Adding new page";
    newPageName=getNewPage(url);
    emit pageListChanged();
#else
    qDebug() << "Not found page - should open browser";
#endif
    return newPageName;
#else
    return "";
#endif
}



bool DomParser::copyFileToCache(QString uploadFileName, QString uniqueFileName)
{
    qDebug() << "File Downloader : Copying " << uploadFileName
             << " to cache as " << mCacheFolder + "/" + uniqueFileName;
    QString copyPath = mCacheFolder + "/" + uniqueFileName;
    uploadFileName.replace("file:///","");
    uploadFileName.replace("file:",""); /* Usefull when accessing network */
    if (QFile::exists(copyPath)) {
        QFile::remove(copyPath);
    }
    if (QFile::copy(uploadFileName, copyPath)) {
        qDebug() << "File Downloader : Copy success ";
        return true;
    } else {
        qDebug() << "File Downloader : Copy failed ";
        return false;
    }
}
// Downloads a file from the server file system. The name given as argument
// should be the unique file name.
QNetworkReply* DomParser::downloadFile(QString downloadFileName, bool openAfterDownload)
{
    qDebug() << "File Downloader : Downloading file " << downloadFileName;
    QString completeFileName = mCacheFolder + "/" + downloadFileName;
    if (QFile::exists(completeFileName)) {
        qDebug() << "File Downloader : File already exist : " << downloadFileName;
        if (openAfterDownload)
            QDesktopServices::openUrl(QUrl::fromLocalFile(completeFileName));
        return 0;
    }
    QUrl url;
    url.setUrl(BASE_URL + DOWNLOAD_ADDON + "configs/" + downloadFileName);
    QNetworkRequest request(url);
#ifndef _DEBUG
    qDebug() << "File Downloader : download in progress";
#else
    qDebug() << "File Downloader : download in progress from " << url;
#endif
    QNetworkReply* reply = networkManager->get(request);
    connect(reply,
            SIGNAL(downloadProgress(qint64,qint64)),
            SLOT(downloadProgress(qint64,qint64)));

    return reply;
}
#ifndef STANDALONE_VIEWER
QString DomParser::getNewPage(QString url,
                              bool virtualPage){

    int counter=1;
    QString prefix;
    if(virtualPage)
        prefix="v";

    QVariantMap existingPage=getConfig(QVariantList() << "pages").toMap();
    QString pageName=prefix+"p"+QString::number(counter);
    while(existingPage.contains(pageName)){
        counter++;
        pageName=prefix+"p"+QString::number(counter);
    }
    QVariantMap newPage=defaultPageEntry(getNewContainer(),"",QStringList() << url);

    if(!virtualPage){
        setConfig(QVariantList() << "pages"<<pageName,newPage);
    }

    setContent(QVariantList() << "pages"<<pageName,newPage);

    return pageName;
}
#endif


#ifndef STANDALONE_VIEWER


Q_INVOKABLE void DomParser::storeConfig(){
    QByteArray bodyContent2;

    qDebug()  << "Sending Images to server and updating path of images";

    _config=RecursiveVariantModifier::uploadAllFiles(_config).toMap();


    qDebug()  << "Sending config to server!" << _config;
    bodyContent2=QJson::encode(_config).toUtf8();
    /* Send data to the Server*/
    QUrl qUrl = QUrl::fromEncoded(QString(SCRIPTS_URL + "storeConfig.php").toUtf8());
    QUrlQuery postData;
    postData.addQueryItem("json", bodyContent2);
    QNetworkRequest request = QNetworkRequest(qUrl);
    request.setHeader(QNetworkRequest::ContentTypeHeader,
                      "application/x-www-form-urlencoded");

    networkManager->post(request, postData.toString(QUrl::FullyEncoded).toUtf8());

    qDebug()  << "Done!";
    storeContent();
}
#endif


void DomParser::writeContentToFile(QString path,QByteArray content){
    QFile *file = new QFile(path);
    if(file->open(QIODevice::ReadWrite)) {
        QTextStream stream(file);
        stream << content;
        stream.flush();
        file->close();
    }else {
        qDebug() << "Fatala: Unable to open file for writing" << path << file->errorString();
    }
    return ;
}


Q_INVOKABLE void DomParser::storeContent(){
    QByteArray bodyContent2;
    qDebug()  << "Sending content to server!";
    bodyContent2=QJson::encode(_content).toUtf8();
    writeContentToFile("output.js",bodyContent2);
    /* Send data to the Server*/
    QUrl qUrl = QUrl::fromEncoded(QString(SCRIPTS_URL + "storeContent.php").toUtf8());
    QUrlQuery postData;
    postData.addQueryItem("json", bodyContent2);
    QNetworkRequest request = QNetworkRequest(qUrl);
    request.setHeader(QNetworkRequest::ContentTypeHeader,
                      "application/x-www-form-urlencoded");


    networkManager->post(request, postData.toString(QUrl::FullyEncoded).toUtf8());
    qDebug()  << "Done!";
}



#ifndef STANDALONE_VIEWER
void DomParser::createContentContainerBasedOnConfigCOntainer(
        QString configContainer,
        QString contentContainer,
        QRegExp overrideUrlsFor,
        QString overidingUrl){
    qDebug() << "Creating content container" << contentContainer << "based on config " << configContainer;



    QVariantList contentPath;
    contentPath << "container" << configContainer << "content";

    QVariantList configPath;
    configPath << "container"<<configContainer<<"config";

    QVariantList configPageItems=getConfig(contentPath).toList();


   // setContent(contentPath);

    for(int j=0;j<configPageItems.count();j++){
        /* TODO: Replace this */
        QVariantMap itemInPage=configPageItems.at(j).toMap();

        QString url=itemInPage["url"].toString();
        if(overrideUrlsFor.isValid()){
            if(url.contains(overrideUrlsFor)){
                qDebug() << "overriden url for config!!!" << url << overidingUrl;
                url=overidingUrl;
            }
        }
        QVariantList pathToDom=itemInPage["path"].toList();
        QVariantMap style=itemInPage["param"].toMap();

        if(pathToDom.isEmpty()){
            /* Static element ! */
            setContent(QVariantList() << contentPath << -1,itemInPage);

        } else {
            insertItemToContainer(contentContainer,
                                      url,
                                      WebExplorer::getItemFromUrl(pathToDom,
                                                     url),
                                      style);
        }
    }

}

//void DomParser::configDownloadProgress(qint64 bytesReceived, qint64 bytesTotal){
    //QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());
//}


void DomParser::configDownloadFinished(){
    QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());
    if(reply->error()!=QNetworkReply::NoError){
        qDebug() << "Error while downloading config" << reply->errorString();
        return;
    } else{
        QString response=QString::fromUtf8(reply->readAll());
        QString error;
        _config=QJson::decode(response,&error).toMap();
        qDebug() << "Received config with lenght:"<< response.length() << "Conversion: " << error;

        /* Convert config to content */
        _content["structure"]=_config["structure"];
        _content["structureWidth"]=_config["structureWidth"];
        _content["pages"]=_config["pages"];
        QVariantMap configContainerList=_config["container"].toMap();

        for(QVariantMap::const_iterator i = configContainerList.begin();
            i != configContainerList.end();
            ++i) {

            QString container=i.key();
            createContentContainerBasedOnConfigCOntainer(container,container);
        }
        emit contentChanged();
        emit pageListChanged();
    }
}



#endif
//void DomParser::contentDownloadProgress(qint64 bytesReceived, qint64 bytesTotal){
    //Not used, not connected
//}

void DomParser::contentDownloadFinished(){
    QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());
    if(reply->error()!=QNetworkReply::NoError){
        qDebug() << "Error while downloading content" << reply->errorString();
        return;
    } else {
        QByteArray sentResponse= reply->readAll();
        QString response=QString::fromUtf8(sentResponse);
        QVariant definition=QJson::decode(response);
        qDebug() << "Received content:" << response << "converted to "<< definition;
        _content=definition.toMap();
        emit contentChanged();
        qDebug() << "Writing config file cache!";
        writeContentToFile(mCacheFolder+"content.js",sentResponse);
    }
}
//void DomParser::uniqueContentDownloadProgress(qint64 bytesReceived, qint64 bytesTotal){
    //Not used, not connected
//}
void DomParser::uniqueContentDownloadFinished(){
    QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());
    if(reply->error()!=QNetworkReply::NoError){
        qDebug() << "Error while downloading content" << reply->errorString();
        return;
    } else {
        QString response=QString::fromUtf8(reply->readAll());
        QVariant definition=QJson::decode(response);
        if(definition.isValid() && response != "null"){
            qDebug() << "Received content:" << response << "converted to "<< definition;
            QVariantMap pages=_content["pages"].toMap();
            pages[_newPage]=definition;
            _content["pages"]=pages;

            emit contentChanged();
        } else {
            qDebug() << "Fatal creation of dynamic content";
        }
    }
}



#ifndef STANDALONE_VIEWER
Q_INVOKABLE void DomParser::loadConfig(){
    /* Get data from Server */

    qDebug()  << "Getting config from server";
    QByteArray bodyContent;
    QUrl qUrl = QUrl::fromEncoded(QString(SCRIPTS_URL + "configs/config2.js").toUtf8());
    QByteArray postDataSize = QByteArray::number(bodyContent.size());

    QNetworkRequest request = QNetworkRequest(qUrl);
    request.setRawHeader("Content-Length", postDataSize);

    QNetworkReply *reply = networkManager->get(request);
    connect(reply,SIGNAL(finished()),
            SLOT(configDownloadFinished()));
}
#endif

Q_INVOKABLE void DomParser::loadContent(){
    /* Get data from Server */

    qDebug()  << "Getting app content from server";
    QByteArray bodyContent;
    QUrl qUrl = QUrl::fromEncoded(QString(SCRIPTS_URL + "configs/content2.js").toUtf8());
    QByteArray postDataSize = QByteArray::number(bodyContent.size());

    QNetworkRequest request = QNetworkRequest(qUrl);
    request.setRawHeader("Content-Length", postDataSize);

    QNetworkReply *reply = networkManager->get(request);
    connect(reply,SIGNAL(finished()),SLOT(contentDownloadFinished()));
}

void DomParser::loadVirtualContent(QString baseContainer,
                                  QString newContainer,
                                  QRegExp urlRegex,
                                  QString url){

    /* Page preloader */

    QVariantMap loaderGifContent;
    loaderGifContent["html"]="qrc:/images/imggurloader.gif";
    loaderGifContent["type"]="image";


    setContent(QVariantList()<<"container"<<newContainer<<"config",
               getContent(QVariantList()<<"container"<<baseContainer<<"config"));

    setContent(QVariantList()<<"container"<<newContainer<<"content"<<-1<<"content",loaderGifContent);
    emit contentChanged();



    /* Get data from Server */

    qDebug()  << "Getting Unique content from server";
    QVariantMap content;
    content["o"]=baseContainer;
    content["r"]=urlRegex.pattern();
    content["u"]=url;

    QByteArray bodyContent=QJson::encode(content).toUtf8();
    QUrlQuery postData;
    postData.addQueryItem("json", bodyContent);

    QUrl qUrl = QUrl::fromEncoded("BASE_URL:8181");

    QNetworkRequest request = QNetworkRequest(qUrl);
    request.setHeader(QNetworkRequest::ContentTypeHeader,
                      "application/x-www-form-urlencoded");

    QNetworkReply *reply = networkManager->post(request,
                                                postData.toString(QUrl::FullyDecoded).toUtf8());

    connect(reply,SIGNAL(finished()),
            SLOT(uniqueContentDownloadFinished()));
}
