#ifndef RESIZER_H
#define RESIZER_H
#include <QQmlPropertyMap>

class resizer : public QObject {
  Q_OBJECT
 public:
  resizer();
  ~resizer();
  QQmlPropertyMap s;

  int applyFontRatio(const int value);
  int applyRatio(const int value);
  void recalculateSizes();

 private slots:
  void updateField(const QString& key, const QVariant& value) {
    if (key == "ratio") {
      recalculateSizes();
    }
  }
};

extern resizer* g_Resizer;

#endif  // RESIZER_H
