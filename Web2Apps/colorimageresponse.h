#ifndef COLORIMAGERESPONSE_H
#define COLORIMAGERESPONSE_H
#include <QQuickTextureFactory>
#include <QQuickImageResponse>
#include <QTimer>

class ColorImageResponse : public QQuickImageResponse
{
    Q_OBJECT

public:
    ColorImageResponse(QString id,
                       const QSize &requestedSize);
    QQuickTextureFactory *textureFactory() const;
    QString urlToFileName(QString url);
    void storeCache();

    QTimer * activeTimer;
    QSize wantedSize;
    QString _id;

signals:
    void finished();

public slots:
    void downloadProgress(qint64 bytesReceived,
                          qint64 bytesTotal);
    void timerFinished();

private:
    QImage _myImage;
    QString _cacheLocation;
};

#endif // COLORIMAGERESPONSE_H
