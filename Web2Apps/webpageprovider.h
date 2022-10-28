#ifndef WEBPAGEPROVIDER_H
#define WEBPAGEPROVIDER_H

#include <qlist.h>
#include <QWebPage>
#include <QObject>


class UserAgentWebPage : public QWebPage {
    QString userAgentForUrl(const QUrl &url ) const {
        return QString("Mozilla/5.0 (Linux; U; Android 4.1.1; en-gb; Build/KLP) AppleWebKit/534.30 (KHTML, like Gecko) Version/4.0 Safari/534.30");
    }
};


class webPageProvider : public QObject
{
    Q_OBJECT
public:
    webPageProvider();
    QWebFrame * getPage(QString url);

public slots:
    void loadFinishedReceived(bool ok);

private:
    QStringList urls;
    QList<QWebPage *> webPages;
    int status;
};


extern webPageProvider * g_webPageProvider;

#endif // WEBPAGEPROVIDER_H
