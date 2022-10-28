#include "settingsprovider.h"
#include <QCryptographicHash>
#ifndef _WEB2APP
#include <custommodelprovider.h>
#endif
#include <resizer.h>
#include <QDebug>
#include <simplecrypt.h>

settingsprovider *g_Settings;

settingsprovider::settingsprovider() {
    offline = 1;
    _localSettings = new QSettings();
    _loginTypeDatabase = -1;
}

settingsprovider::~settingsprovider() {}
Q_INVOKABLE QVariant settingsprovider::getSetting(const QString &key) {
    if (key == "storedpw") {
        SimpleCrypt crypto(Q_UINT64_C(0x0d2bbda4a5b9c011));
        return crypto.decryptToString(_localSettings->value(key).toString());
    }
    if (key == "storedmailpw") {
        SimpleCrypt crypto(Q_UINT64_C(0x0d2bbda4a5b9c011));
        return crypto.decryptToString(_localSettings->value(key).toString());
    }
    if (_localSettings->contains(key)) {
        return _localSettings->value(key);
    }
    return "";
}

Q_INVOKABLE void settingsprovider::setSetting(const QString &key, const QVariant &value,
                                              const bool localOnly) {
    QVariant val = value;
    if (key == "storedpw") {
        SimpleCrypt crypto(Q_UINT64_C(0x0d2bbda4a5b9c011));
        val = crypto.encryptToString(val.toString());
    }
    if (key == "storedmailpw") {
        SimpleCrypt crypto(Q_UINT64_C(0x0d2bbda4a5b9c011));
        val = crypto.encryptToString(val.toString());
    }
    if (key != "Password") {
        _localSettings->setValue(key, val);
    }
    emit settingChanged(key);
    if (!offline && !localOnly) {
        if (key == "Password") {
            QByteArray encrypted = val.toString().toUtf8();
            val = QString(QCryptographicHash::hash(encrypted, QCryptographicHash::Md5).toHex());
        }
#ifndef _WEB2APP
        CustomModel *defaultConfig = g_Models->getModelFromName("_syninternal_defaultconfig");
        if (defaultConfig->getRelatedType()->getObjectfromName(key) != 0) {
            defaultConfig->changeValueOfLabel(key, val, defaultConfig->getValuesFor("id").toInt());
        }
#else
        qDebug() << "TODO: To implement remote storage!!!";
#endif
    }
}
#ifndef _WEB2APP
void settingsprovider::loadSettings(CustomModel *paramModel) {
    if (paramModel->rowCount() == 0) {
        qDebug() << "Unable to load default parameters";
    } else {
        for (int i = 0; i < paramModel->rowCount(); i++) {
            QString key = paramModel->getData(i, 0).toString();
            QVariant value = paramModel->getData(i, 1);
            if ((key != "Password") && (_localSettings->value(key) != value)) {
                _localSettings->setValue(key, value);
                emit settingChanged(key);
            }
        }
    }
    offline = 0;
}
#endif
