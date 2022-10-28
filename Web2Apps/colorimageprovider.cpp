#include "colorimageprovider.h"
#include <QDebug>
#include "colorimageresponse.h"


QQuickImageResponse *ColorImageProvider::requestImageResponse(const QString &id,
                                           const QSize &requestedSize){

    ColorImageResponse * response=new ColorImageResponse(id,
                                                         requestedSize);
    return response;
}
/*
QPixmap ColorImageProvider::requestPixmap(const QString &id, QSize *size, const QSize &requestedSize)
{
    int width = 100;
    int height = 50;
    qDebug() << "Requesting image!" << id;

    if (size)
        *size = QSize(width, height);
    QPixmap pixmap(requestedSize.width() > 0 ? requestedSize.width() : width,
                   requestedSize.height() > 0 ? requestedSize.height() : height);
    pixmap.fill(QColor(id).rgba());

    return pixmap;
}
*/
