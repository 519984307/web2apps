#include <QSslCertificate>
#include <QSslKey>
#include <QSslSocket>
#include <QStringList>

#include "sslserver.h"

struct SslServerPrivate
{
    QSslCertificate cert;
    QSslKey key;
    QSslSocket *sock;
};

SslServer::SslServer(const QSslCertificate &cert, const QSslKey &key)
    : QTcpServer(),
      d(new SslServerPrivate)
{
    qDebug() << "Cert" << cert;
    qDebug() << "Key" << key;
    d->cert = cert;
    d->key = key;
    d->sock = 0;

    //listen(QHostAddress::Any, port);
}

SslServer::~SslServer()
{
    delete d;
}

void SslServer::ready()
{
    qDebug() << Q_FUNC_INFO;

    //d->sock->write("This message is encrypted\n");

    // Slightly evil, but since want to close immediately in this example
    // we aren't going to wait for the main event loop.
    //d->sock->waitForBytesWritten(1000);
   // d->sock->close();
}

#if QT_VERSION >= 0x050000
void SslServer::incomingConnection(qintptr socketDescriptor)
#else
void SslServer::incomingConnection(int socketDescriptor)
#endif
{
    qDebug() << Q_FUNC_INFO;

    d->sock = new QSslSocket(this);


    if (!d->sock->setSocketDescriptor(socketDescriptor)) {

        qDebug() << "Unable set socket descriptor";

        delete d->sock;
        d->sock = 0;
        return;
    }
    addPendingConnection(d->sock);
    connect(d->sock, SIGNAL(sslErrors(QList<QSslError>)), this, SLOT(showErrors()));
   // connect(d->sock, SIGNAL(encrypted()), this, SLOT(ready()));
    //connect(d->sock, SIGNAL(readyRead()), this, SLOT(readChannel()));
    connect(d->sock, SIGNAL(encrypted()), this, SLOT(ready()));
    //d->sock->addCaCertificate(d->cert);
    d->sock->setLocalCertificate(d->cert);
    d->sock->setPrivateKey(d->key);

    // Select DH suite
    //    d->sock->setCiphers("DHE-RSA-AES256-SHA:DHE-DSS-AES256-SHA");
    // Select ECDH suite
    //    d->sock->setCiphers("ECDHE-RSA-AES128-SHA:AES128-SHA:RC4-SHA");

    d->sock->startServerEncryption();
    if (d->sock->isEncrypted())
        emit d->sock->encrypted();

    if(!d->sock->waitForEncrypted(3000)) {
        qDebug() << "Wait for encrypted!!!!" << d->sock->errorString();
        return;
    }
}
void SslServer::showErrors()
{

    qDebug() << Q_FUNC_INFO;
    QList<QSslError>  err = d->sock->sslErrors();
    for(int i=0;i<err.size();i++)
        qDebug() << err[i];
}
