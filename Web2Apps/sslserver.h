#ifndef SSLSERVER_H
#define SSLSERVER_H

#include <QTcpServer>
#include <QSsl>
#include <QSslCertificate>
#include <QSslKey>

class QSslCertificate;
class QSslKey;
class QSslError;

struct SslServerPrivate;

class SslServer : public QTcpServer
{
    Q_OBJECT

public:
    SslServer(const QSslCertificate &cert, const QSslKey &key);
    ~SslServer();

protected slots:
    void ready();
    void showErrors();

protected:
#if QT_VERSION >= 0x050000
    void incomingConnection(qintptr socketDescriptor);
#else
    void incomingConnection(int socketDescriptor);
#endif

private:
    SslServerPrivate *d;
};

#endif // SSLSERVER_H
