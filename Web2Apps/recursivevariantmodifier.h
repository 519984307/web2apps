#ifndef RECURSIVEVARIANTMODIFIER_H
#define RECURSIVEVARIANTMODIFIER_H

#include <QVariant>
#include <QStringList>
#include <QMap>
#include <QHash>

class RecursiveVariantModifier
{
public:
    RecursiveVariantModifier();

    static QVariant getValue(QVariant data, QVariantList path);
    static QVariant changeValue(QVariant data, QVariantList path, QVariant newVal);
#ifndef STANDALONE_VIEWER
    static QVariant uploadAllFiles(QVariant data);
#endif
    static QVariant replaceContent(QVariant data, QString oldValue, QString newValue);
};

#endif // RECURSIVEVARIANTMODIFIER_H
