#import <notificationclientios.h>
#import <UIKit/UIKit.h>
#import <Foundation/Foundation.h>

#ifndef NSFoundationVersionNumber_iOS_8_0
#define NSFoundationVersionNumber_iOS_8_0  1140.11
#endif

void NotificationClientIOS::registerForNotifications() {

    if (floor(NSFoundationVersionNumber) >= NSFoundationVersionNumber_iOS_8_0)
    {
        // An UIUserNotificationSettings Object gets registered to the Application
        // sharedApplication gets the UIApplication object of the app

        //[UIUserNotificationSettings settingsForTypes:UIUserNotificationTypeAlert|UIUserNotificationTypeBadge|UIUserNotificationTypeSound categories:nil]
        // constructs the UIUserNotificationSettings object with the predefined enum for the different kind of notifications

        [[UIApplication sharedApplication] registerUserNotificationSettings:[UIUserNotificationSettings settingsForTypes:UIUserNotificationTypeAlert|UIUserNotificationTypeBadge|UIUserNotificationTypeSound categories:nil]];

    }
}

void NotificationClientIOS::setNotification(const QString &message, const QString &title)
{
    if (floor(NSFoundationVersionNumber) >= NSFoundationVersionNumber_iOS_8_0)
    {
        UILocalNotification *notification = [[UILocalNotification alloc] init];
        notification.fireDate = [[NSDate date] dateByAddingTimeInterval:60];
        notification.alertBody = [NSString stringWithUTF8String: message.toUtf8().data()];
        notification.alertTitle = [NSString stringWithUTF8String: title.toUtf8().data()];
        notification.soundName = UILocalNotificationDefaultSoundName;
        [[UIApplication sharedApplication] scheduleLocalNotification:notification];
    }
}


