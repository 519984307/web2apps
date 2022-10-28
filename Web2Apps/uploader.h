#ifndef UPLOADER_H
#define UPLOADER_H

#include <QString>

#define BASE_URL QString("http://localhost/")
#define DOWNLOAD_ADDON QString("/w2a-scripts/")
#define SCRIPTS_URL BASE_URL + DOWNLOAD_ADDON
#define FILE_UPLOAD_SUFFIX QString("x_upload_file.php")
#define PICTURE_UPLOAD_SUFFIX QString("storeBackground.php")
#define VIDEO_UPLOAD_SUFFIX QString("x_upload_video.php")

class Uploader
{
public:
    Uploader();

    static QString uploadFile(QString uploadFileName,
                                QString uniqueFileName);
    static QString getRandomString();
};

#endif // UPLOADER_H
