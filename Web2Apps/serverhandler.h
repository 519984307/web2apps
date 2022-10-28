#ifndef SERVERHANDLER_H
#define SERVERHANDLER_H

#include <qobject.h>

#include <qhttpserver.h>
#include <qhttprequest.h>
#include <qhttpresponse.h>
#include <qnetworkreply.h>
#include <qurl.h>
#include <qnetworkaccessmanager.h>
#include <qnetworkrequest.h>
#include <qeventloop.h>

class ServerHandler: public QObject
{
    Q_OBJECT
public:

    ServerHandler();
public slots:
    void handle(QHttpRequest *req, QHttpResponse *resp);
    void slotReadyRead();
    void processPost();

private:
    QHttpRequest *m_req;
    QHttpResponse *m_resp;
};

#endif // SERVERHANDLER_H
