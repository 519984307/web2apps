#include "colorimageresponse.h"
#include <QDebug>
#include <QUrl>
#include <QNetworkRequest>
#include <QNetworkAccessManager>
#include <QFile>
#include <QNetworkReply>
#include <domparser.h>

ColorImageResponse::ColorImageResponse(QString id,const QSize &requestedSize)
{
    wantedSize=requestedSize;
    _id=id;
    _cacheLocation=domParser->mCacheFolder+
            QString::number(requestedSize.width())+urlToFileName(_id);

    QFile copyCache(_cacheLocation);
    if (copyCache.exists()){
        qDebug() << "File already exists. Use cache" << _cacheLocation;
        _myImage=QImage(_cacheLocation);
        QTimer *timer = new QTimer(this);
        connect(timer, SIGNAL(timeout()), this, SLOT(timerFinished()));
        timer->start(10);
    } else {
        qDebug() << "File does not exists. Download." + id;
        QUrl url;
        url.setUrl(id);
        QNetworkRequest request(url);
        QNetworkAccessManager * networkManager = new QNetworkAccessManager();
        QNetworkReply* reply = networkManager->get(request);
        connect(reply,
                SIGNAL(downloadProgress(qint64,qint64)),
                SLOT(downloadProgress(qint64,qint64)));
    }
}

void ColorImageResponse::timerFinished(){
    emit finished();
}


QQuickTextureFactory *ColorImageResponse::textureFactory() const{
    return QQuickTextureFactory::textureFactoryForImage(_myImage);
}

void ColorImageResponse::storeCache(){
    QFile copyCache(_cacheLocation);
    if (!copyCache.exists()){
        _myImage.save(_cacheLocation);
    }
}

QString ColorImageResponse::urlToFileName(QString url){
    url.replace("/","_");
    url.replace("\\","_");
    url.replace(":","_");
    url.replace("?","_");
    url.replace("<","_");
    url.replace(">","_");
    url.replace("|","_");
    url.replace("*","_");
    url.replace("\"","_");
    return url.right(250);
}

void ColorImageResponse::downloadProgress(qint64 bytesReceived, qint64 bytesTotal){

    QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());
    if(bytesTotal==0){
        qDebug() << "Error while downloading image. No cache available."
                 << bytesReceived << bytesTotal << reply->errorString();
    }
    if(bytesReceived==bytesTotal){
        QImage tmp;
        tmp.loadFromData(reply->readAll());
        if(wantedSize.isValid() && wantedSize.width()!=0){
            _myImage=tmp.scaledToWidth(wantedSize.width(),Qt::SmoothTransformation);
        } else {
            qDebug() << "Wanted width of image is 0?";
            _myImage=tmp;
        }
        if(_myImage.isNull()){
            qDebug() << "Error in full image!!!!!!!!"<< _id << bytesReceived << bytesTotal << reply->errorString();
        }
        emit finished();
        storeCache();
    }
}

