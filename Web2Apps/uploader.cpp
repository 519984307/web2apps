#include "uploader.h"
#include <QFile>
#include <QUrl>
#include <QDebug>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QMimeDatabase>



Uploader::Uploader()
{

}


// Uploads a file to the server. uploadFileName is the original name of the
// file as displayed in the interface. uniqueFileName is the unique file
// name used in cache and server storage. newFile defines if the upload is
// for a new file (use uploadFileName) or an update from cache directory
// (use uniqueFileName).
QString Uploader::uploadFile(QString uploadFileName,
                           QString uniqueFileName)
{

    qDebug() << "File Downloader : Uploading file " << uploadFileName << " as " << uniqueFileName;


    uploadFileName.replace("file:///","");
    uploadFileName.replace("file:",""); /* Usefull when accessing network */
    QFile* uploadedFile = new QFile(uploadFileName);
    //uploadedFile->setFileName(uniqueFileName);

    if (uploadedFile->open(QIODevice::ReadOnly)) {
        QString boundary = "AaBbCc";
        QMimeDatabase db;
        QMimeType mimeType = db.mimeTypeForFile(uploadFileName);
        QByteArray data;
        QString mServerName="configs";
        data += "--" + boundary + "\r\n";
        data += "Content-Disposition: form-data; name=\"server-name\"\r\n";
        data += "\r\n";
        data += mServerName;
        data += "\r\n";
        data += "--" + boundary + "\r\n";
        data += "Content-Disposition: form-data; name=\"userfile\"; ";
        data += "filename=\"" + uniqueFileName + "\"\r\n";
        data += "Content-Type: " + mimeType.name() + "\r\n";
        data += "\r\n";
        data += uploadedFile->readAll();
        data += "\r\n";
        data += "--" + boundary + "\r\n";
        QStringList splitedName = uniqueFileName.split(".");
        QString fileExtension = splitedName[splitedName.length() - 1].toLower();
        QUrl uploadUrl;
        if (mimeType.name().startsWith("image"))
            uploadUrl = BASE_URL + DOWNLOAD_ADDON+ PICTURE_UPLOAD_SUFFIX;
        else if (mimeType.name().startsWith("video"))
            uploadUrl = BASE_URL + DOWNLOAD_ADDON+ VIDEO_UPLOAD_SUFFIX;
        else
            uploadUrl = BASE_URL + DOWNLOAD_ADDON+ FILE_UPLOAD_SUFFIX;
        QNetworkRequest request(uploadUrl);
        request.setRawHeader(QString("Content-Type").toStdString().c_str(),
                             QString("multipart/form-data; boundary=" + boundary).toStdString().c_str());
        request.setRawHeader(QString("Content-Length").toStdString().c_str(),
                             QString::number(data.length()).toStdString().c_str());
        request.setRawHeader(QString("Uploaded-File-Name").toStdString().c_str(),
                             uniqueFileName.toStdString().c_str());
        qDebug() << "File Downloader : Upload in progress";
        QNetworkAccessManager * networkManager = new QNetworkAccessManager();
        QNetworkReply* reply = networkManager->post(request, data);

        return QString(BASE_URL) + DOWNLOAD_ADDON + "configs/"+ uniqueFileName;
    } else {
        qDebug() << "Error (File Downloader): Could not open file for upload";
        return "";
    }
}


QString Uploader::getRandomString()
{
   const QString possibleCharacters("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789");
   const int randomStringLength = 12; // assuming you want random strings of 12 characters

   QString randomString;
   for(int i=0; i<randomStringLength; ++i)
   {
       int index = qrand() % possibleCharacters.length();
       QChar nextChar = possibleCharacters.at(index);
       randomString.append(nextChar);
   }
   return randomString;
}
