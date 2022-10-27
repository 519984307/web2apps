#include "serverhandler.h"
#include "qjson.h"
#include <domparser.h>

void ServerHandler::handle(QHttpRequest *req, QHttpResponse *resp)
{
    m_req = req;
    m_resp = resp;
    qDebug() << "Received something on C++ side!";

    connect(req, SIGNAL(end()), this, SLOT(processPost()));
    req->storeBody();
}

void ServerHandler::slotReadyRead()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());
    qDebug() << reply->readAll();
}

void ServerHandler::processPost() {
    QByteArray bodyContent = m_req->body();
    // TODO use bodyContent to publish in App preview

    QString stringjson =bodyContent;
    stringjson.remove("json=");
    qDebug() << "received" << stringjson;
    QVariantMap postData=QJson::decode(stringjson).toMap();
#ifndef CONVERSION_SERVER
    domParser->addDOMItemToContainer(domParser->_currentContainer,
                                QJson::decode(stringjson).toMap());
    m_resp->writeHead(200); // everything is OK
    m_resp->write("Hello World");
#else
    qDebug() << "Received" << QJson::decode(stringjson);
    m_resp->writeHead(200); // everything is OK

    QString page=domParser->getPageFromUrl(postData["u"].toString());
    QString newPageName;
    if(page!=""){
        newPageName=page;
    } else {

        int currentPageAmount=domParser->pageList().count();
        newPageName="AUTOPage " + QString::number(currentPageAmount+1);
        domParser->getNewPage(newPageName,postData["u"].toString());
        domParser->createContentPageBasedOnConfigPage(postData["o"].toString(),
                newPageName,QRegExp(postData["r"].toString(),
                Qt::CaseSensitive,
                QRegExp::Wildcard),postData["u"].toString());
    }
    bodyContent=QJson::encode(domParser->content()["pages"].toMap()[newPageName]).toUtf8();
    m_resp->write(bodyContent);

#endif
    m_resp->end();
}

ServerHandler::ServerHandler()
{

}

