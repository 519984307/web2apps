#ifndef COLORIMAGEPROVIDER_H
#define COLORIMAGEPROVIDER_H
#include <QQuickAsyncImageProvider>

class ColorImageProvider : public QQuickAsyncImageProvider
{
public:
    ColorImageProvider()
        : QQuickAsyncImageProvider()
    {
    }
    QQuickImageResponse *requestImageResponse(const QString &id,
                                              const QSize &requestedSize);

};
#endif // COLORIMAGEPROVIDER_H
