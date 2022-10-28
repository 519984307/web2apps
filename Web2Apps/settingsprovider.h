#ifndef SETTINGSPROVIDER_H
#define SETTINGSPROVIDER_H
#include <QObject>
#include <QMap>
#include <QString>
#ifndef _WEB2APP
#include <custommodel.h>
#endif
#include <QSettings>

class settingsprovider : public QObject {
  Q_OBJECT
  Q_PROPERTY(QString me READ me WRITE setMe NOTIFY meChanged)

 public:
  Q_INVOKABLE void setSetting(const QString &key, const QVariant &value,
                              const bool localOnly = false);
  Q_INVOKABLE QVariant getSetting(const QString &key);

  settingsprovider();
  ~settingsprovider();
#ifndef _WEB2APP
  void loadSettings(CustomModel *paramModel);
#endif
  int settingsChangeNotify() { return 1; }

  QString me() { return _userSqlId; }
  void setMe(QString me) {
    _userSqlId = me;
    emit meChanged();
  }

  QString username() { return _userName; }
  void setUsername(QString user) { _userName = user; }

  int loginType() { return _loginTypeDatabase; }
  void setLoginType(int sqlid) { _loginTypeDatabase = sqlid; }

  QString password() { return _userPassword; }
  void setPassword(QString pass) { _userPassword = pass; }
  void setPasswordOf(const QString &user, const QString &password);
  int offline;
signals:
  void settingChanged(QString);
  void meChanged();

 private:
  int _loginTypeDatabase;

  QString _userSqlId;
  QString _userName;
  QString _userPassword;
  QSettings *_localSettings;
};

extern settingsprovider *g_Settings;

#endif  // SETTINGSPROVIDER_H
