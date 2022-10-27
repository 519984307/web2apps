#ifndef NOTIFICATIONCLIENT_IOS_H
#define NOTIFICATIONCLIENT_IOS_H

#include <QObject>

class NotificationClientIOS {
public:

    static void registerForNotifications();
    static void setNotification(const QString &message, const QString &title);

};

#endif // NOTIFICATIONCLIENT_IOS_H
