#ifndef WEBEXPLORER_H
#define WEBEXPLORER_H

#ifndef STANDALONE_VIEWER

#include <QWebFrame>
#include <QWebElement>
#include <webpageprovider.h>


class WebExplorer
{
public:
    WebExplorer();
    static QWebElement findDomElement(QVariantList pathToDom,
                                          QString url);
    static QVariantMap convertWebElementToItem(QWebElement element,QString url);
    static QVariantMap getItemFromUrl(QVariantList pathToDom,
                               QString url);

};

#endif
#endif // WEBEXPLORER_H
