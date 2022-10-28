#include "resizer.h"
#include <QObject>
#include <QtGui/QGuiApplication>
#include <QDebug>
#include <QScreen>
//#include "qtquick2applicationviewer.h"
#include <QtQml>
#include <skinprovider.h>
#include <settingsprovider.h>
#include <QApplication>
#include <qmath.h>

resizer *g_Resizer;

resizer::resizer() {
  qreal refDpi = 96;
  qreal refWidth = 1024.;
  qreal refHeight = 768.;
#ifndef CONVERSION_SERVER
  QRect rect = qApp->primaryScreen()->geometry();
  qreal height = qMax(rect.width(), rect.height());
  qreal width = qMin(rect.width(), rect.height());
  // s["defaultdir"] = QString(QStandardPaths::writableLocation(QStandardPaths::AppDataLocation));

  if (g_Settings->getSetting("ratio").toString().isEmpty()) {
    qreal dpi = qApp->primaryScreen()->physicalDotsPerInch();
    qreal dpil = qApp->primaryScreen()->logicalDotsPerInch();
    qDebug() << "! DPI" << QString::number(dpi);
    qDebug() << "! DPIL" << QString::number(dpil);
    s["dpi"] = dpi;
    s["dpil"] = dpil;
    if (dpil < refDpi) {
      if (QSysInfo::productType() == "android") {
        s["ratio"] = (dpi / refDpi) / 1.2;
      } else if (QSysInfo::productType() == "ios") {
        s["ratio"] = 1.10;
      } else {
        s["ratio"] = (dpi / refDpi);
      }
    } else {
      if (QSysInfo::productType() == "android") {
        s["ratio"] = (dpil / refDpi) * 1.2;
      } else if (QSysInfo::productType() == "ios") {
        s["ratio"] = 1.10;
      } else {
        s["ratio"] = (dpil / refDpi);
      }
    }
    qDebug() << "! RATIO" << QString::number(s["ratio"].toFloat());
  } else {
    s["ratio"] = g_Settings->getSetting("ratio").toFloat();
  }
#else
  s["ratio"] = 1 ;
#endif
  float ratio = QString::number(s["ratio"].toFloat(), 'f', 1).toFloat();
  s["ratio"] = ratio;

  if (g_Settings->getSetting("showmenu").toString().isEmpty()) {
    s["showmenu"] = qreal(1);
  } else {
    s["showmenu"] = g_Settings->getSetting("showmenu").toFloat();
  }

  // s["ratioFont"] = 1;//qMin(height*refDpi/(dpi*refHeight), width*refDpi/(dpi*refWidth));
  recalculateSizes();
  connect(&s, SIGNAL(valueChanged(QString, QVariant)), this, SLOT(updateField(QString, QVariant)));
}
void resizer::recalculateSizes() {
    s.insert("r2", QVariant(2));
    s.insert("r3", QVariant(3));
    s.insert("r5", QVariant(5));
    s.insert("r7", QVariant(7));
    s.insert("r10", QVariant(applyRatio(10)));
    s.insert("r15", QVariant(applyRatio(15)));
    s.insert("r20", QVariant(applyRatio(20)));
    s.insert("r25", QVariant(applyRatio(25)));
    s.insert("r30", QVariant(applyRatio(30)));
    s.insert("r35", QVariant(applyRatio(35)));
    s.insert("r40", QVariant(applyRatio(40)));
    s.insert("r50", QVariant(applyRatio(50)));
    s.insert("r55", QVariant(applyRatio(55)));
    s.insert("r60", QVariant(applyRatio(60)));
    s.insert("r70", QVariant(applyRatio(70)));
    s.insert("r80", QVariant(applyRatio(80)));
    s.insert("r85", QVariant(applyRatio(85)));
    s.insert("r90", QVariant(applyRatio(90)));
    s.insert("r100", QVariant(applyRatio(100)));
    s.insert("r110", QVariant(applyRatio(110)));
    s.insert("r120", QVariant(applyRatio(120)));
    s.insert("r123", QVariant(applyRatio(123)));
    s.insert("r140", QVariant(applyRatio(140)));
    s.insert("r150", QVariant(applyRatio(150)));
    s.insert("r160", QVariant(applyRatio(160)));
    s.insert("r170", QVariant(applyRatio(170)));
    s.insert("r180", QVariant(applyRatio(180)));
    s.insert("r200", QVariant(applyRatio(200)));
    s.insert("r225", QVariant(applyRatio(225)));
    s.insert("r250", QVariant(applyRatio(250)));
    s.insert("r280", QVariant(applyRatio(280)));
    s.insert("r288", QVariant(applyRatio(288)));
    s.insert("r300", QVariant(applyRatio(300)));
    s.insert("r320", QVariant(applyRatio(320)));
    s.insert("r350", QVariant(applyRatio(350)));
    s.insert("r400", QVariant(applyRatio(400)));
    s.insert("r500", QVariant(applyRatio(500)));
    s.insert("r512", QVariant(applyRatio(512)));
    s.insert("r600", QVariant(applyRatio(600)));
    s.insert("r650", QVariant(applyRatio(650)));
    s.insert("r700", QVariant(applyRatio(700)));
    s.insert("r800", QVariant(applyRatio(800)));
    s.insert("r900", QVariant(applyRatio(900)));
    s.insert("r1000", QVariant(applyRatio(1000)));
    s.insert("r1200", QVariant(applyRatio(1200)));
    s.insert("r1500", QVariant(applyRatio(1500)));
    s.insert("r2000", QVariant(applyRatio(2000)));

  // For Margin
  s.insert("m2", QVariant(2));
  s.insert("m3", QVariant(3));
  s.insert("m5", QVariant(5));
  s.insert("m10", QVariant(applyRatio(10)));
  s.insert("m15", QVariant(applyRatio(15)));
  s.insert("m20", QVariant(applyRatio(20)));
  s.insert("m25", QVariant(applyRatio(25)));
  s.insert("m30", QVariant(applyRatio(30)));
  s.insert("m35", QVariant(applyRatio(35)));
  s.insert("m40", QVariant(applyRatio(40)));
  s.insert("m50", QVariant(applyRatio(50)));

  // For Icons
  s.insert("icon", QVariant(applyRatio(15)));

  g_Skins->setfontsizemultiplier(s["ratio"].toFloat());
  g_Settings->setSetting("ratio", s["ratio"], true);

  // Should autodetect
  if ((QSysInfo::productType() == "android") || (QSysInfo::productType() == "ios")) {
    //        if(1){
    s.insert("touchscreen", QVariant((1)));
    s.insert("icon", QVariant(applyRatio(20)));
    QScreen *screen = QApplication::screens().at(0);
    qreal screenHeight = screen->physicalSize().height();
    qreal screenWidth = screen->physicalSize().width();
    qreal value = screenHeight * screenHeight + screenWidth * screenWidth;
    qreal screenDiagonal = qSqrt(value);

    // 7 inch equals 177,8 milimeter
    if (screenDiagonal <= 177.8) {
      //            if (1){
      s.insert("smallScreen", bool(true));

      // For removable Margin
      s.insert("rm3", QVariant(0));
      s.insert("rm5", QVariant(0));
      s.insert("rm10", QVariant(0));
      s.insert("rm15", QVariant(0));
      s.insert("rm20", QVariant(0));
      s.insert("rm25", QVariant(0));
      s.insert("rm30", QVariant(0));
      s.insert("rm35", QVariant(0));
      s.insert("rm40", QVariant(0));
      s.insert("rm50", QVariant(0));
    } else {
      s.insert("smallScreen", bool(false));

      // For removable Margin
      s.insert("rm3", QVariant(3));
      s.insert("rm5", QVariant(5));
      s.insert("rm10", QVariant(applyRatio(10)));
      s.insert("rm15", QVariant(applyRatio(15)));
      s.insert("rm20", QVariant(applyRatio(20)));
      s.insert("rm25", QVariant(applyRatio(25)));
      s.insert("rm30", QVariant(applyRatio(30)));
      s.insert("rm35", QVariant(applyRatio(35)));
      s.insert("rm40", QVariant(applyRatio(40)));
      s.insert("rm50", QVariant(applyRatio(50)));
    }

  } else {
    s.insert("smallScreen", bool(false));
    s.insert("touchscreen", QVariant((0)));

    // For removable Margin
    s.insert("rm3", QVariant(3));
    s.insert("rm5", QVariant(5));
    s.insert("rm10", QVariant(applyRatio(10)));
    s.insert("rm15", QVariant(applyRatio(15)));
    s.insert("rm20", QVariant(applyRatio(20)));
    s.insert("rm25", QVariant(applyRatio(25)));
    s.insert("rm30", QVariant(applyRatio(30)));
    s.insert("rm35", QVariant(applyRatio(35)));
    s.insert("rm40", QVariant(applyRatio(40)));
    s.insert("rm50", QVariant(applyRatio(50)));
  }
}

int resizer::applyRatio(const int value) { return qMax(2, int(value * s["ratio"].toFloat())); }

resizer::~resizer() {}
