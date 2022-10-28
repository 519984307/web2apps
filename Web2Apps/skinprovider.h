#ifndef SkinProvider_H
#define SkinProvider_H
#include <QObject>
#include <QColor>
#include <QString>
#include <QDebug>
#include <QtQml>
#include <QGuiApplication>
#include <QFont>

/* NOTE : There is an excel file to generate this !!! Use it :-) Look for skinclass_generator.xlsx
 */

class SkinProvider : public QObject {
  Q_OBJECT
  Q_PROPERTY(QString synnextlogo READ synnextlogo WRITE setsynnextlogo NOTIFY synnextlogoChanged)
  Q_PROPERTY(QString background READ background WRITE setbackground NOTIFY backgroundChanged)
  Q_PROPERTY(int radius READ radius WRITE setradius NOTIFY radiusChanged)
  Q_PROPERTY(QColor buttongradient1 READ buttongradient1 WRITE setbuttongradient1 NOTIFY
                 buttongradient1Changed)
  Q_PROPERTY(QColor buttongradient2 READ buttongradient2 WRITE setbuttongradient2 NOTIFY
                 buttongradient2Changed)
  Q_PROPERTY(qreal buttonopacity READ buttonopacity WRITE setbuttonopacity NOTIFY
                 buttonopacityChanged)
  Q_PROPERTY(QColor clickbuttongradient1 READ clickbuttongradient1 WRITE setclickbuttongradient1
                 NOTIFY clickbuttongradient1Changed)
  Q_PROPERTY(QColor clickbuttongradient2 READ clickbuttongradient2 WRITE setclickbuttongradient2
                 NOTIFY clickbuttongradient2Changed)
  Q_PROPERTY(qreal clickbuttonopacity READ clickbuttonopacity WRITE setclickbuttonopacity NOTIFY
                 clickbuttonopacityChanged)
  Q_PROPERTY(QColor tablecolortitle READ tablecolortitle WRITE settablecolortitle NOTIFY
                 tablecolortitleChanged)
  Q_PROPERTY(qreal tableopacitytitle READ tableopacitytitle WRITE settableopacitytitle NOTIFY
                 tableopacitytitleChanged)
  Q_PROPERTY(QColor tablecolorline1 READ tablecolorline1 WRITE settablecolorline1 NOTIFY
                 tablecolorline1Changed)
  Q_PROPERTY(qreal tableopacityline1 READ tableopacityline1 WRITE settableopacityline1 NOTIFY
                 tableopacityline1Changed)
  Q_PROPERTY(QColor tablecolorline2 READ tablecolorline2 WRITE settablecolorline2 NOTIFY
                 tablecolorline2Changed)
  Q_PROPERTY(qreal tableopacityline2 READ tableopacityline2 WRITE settableopacityline2 NOTIFY
                 tableopacityline2Changed)
  Q_PROPERTY(QColor fastlinkingcolor READ fastlinkingcolor WRITE setfastlinkingcolor NOTIFY
                 fastlinkingcolorChanged)
  Q_PROPERTY(qreal fastlinkingopacity READ fastlinkingopacity WRITE setfastlinkingopacity NOTIFY
                 fastlinkingopacityChanged)
  Q_PROPERTY(QColor intelliboxcolor READ intelliboxcolor WRITE setintelliboxcolor NOTIFY
                 intelliboxcolorChanged)
  Q_PROPERTY(qreal intelliboxopacity READ intelliboxopacity WRITE setintelliboxopacity NOTIFY
                 intelliboxopacityChanged)
  Q_PROPERTY(QColor menuboxcolor READ menuboxcolor WRITE setmenuboxcolor NOTIFY menuboxcolorChanged)
  Q_PROPERTY(qreal menuboxopacity READ menuboxopacity WRITE setmenuboxopacity NOTIFY
                 menuboxopacityChanged)
  Q_PROPERTY(QColor tabbedmenuboxcolor READ tabbedmenuboxcolor WRITE settabbedmenuboxcolor NOTIFY
                 tabbedmenuboxcolorChanged)
  Q_PROPERTY(qreal tabbedmenuboxopacity READ tabbedmenuboxopacity WRITE settabbedmenuboxopacity
                 NOTIFY tabbedmenuboxopacityChanged)
  Q_PROPERTY(QColor titlecolor READ titlecolor WRITE settitlecolor NOTIFY titlecolorChanged)
  Q_PROPERTY(QColor popupcolor READ popupcolor WRITE setpopupcolor NOTIFY popupcolorChanged)
  Q_PROPERTY(qreal popupopacity READ popupopacity WRITE setpopupopacity NOTIFY popupopacityChanged)
  Q_PROPERTY(QColor inactivefontcolor READ inactivefontcolor WRITE setinactivefontcolor NOTIFY
                 inactivefontcolorChanged)
  Q_PROPERTY(QColor inactivetabcolor READ inactivetabcolor WRITE setinactivetabcolor NOTIFY
                 inactivetabcolorChanged)
  Q_PROPERTY(QColor listbackgroundcolor READ listbackgroundcolor WRITE setlistbackgroundcolor NOTIFY
                 listbackgroundcolorChanged)
  Q_PROPERTY(QString suggestbubbleimage READ suggestbubbleimage WRITE setsuggestbubbleimage NOTIFY
                 suggestbubbleimageChanged)
  Q_PROPERTY(qreal suggestbubbleopacity READ suggestbubbleopacity WRITE setsuggestbubbleopacity
                 NOTIFY suggestbubbleopacityChanged)
  Q_PROPERTY(QColor tooltipcolor READ tooltipcolor WRITE settooltipcolor NOTIFY tooltipcolorChanged)
  Q_PROPERTY(int bordersize READ bordersize WRITE setbordersize NOTIFY bordersizeChanged)
  Q_PROPERTY(QColor bordercolor READ bordercolor WRITE setbordercolor NOTIFY bordercolorChanged)
  Q_PROPERTY(QString usedfont READ usedfont WRITE setusedfont NOTIFY usedfontChanged)
  Q_PROPERTY(QColor warningcolor READ warningcolor WRITE setwarningcolor NOTIFY warningcolorChanged)
  Q_PROPERTY(QColor selectcolor READ selectcolor WRITE setselectcolor NOTIFY selectcolorChanged)
  Q_PROPERTY(QColor lockedinputcolor READ lockedinputcolor WRITE setlockedinputcolor NOTIFY
                 lockedinputcolorChanged)
  Q_PROPERTY(qreal titlefontsize READ titlefontsize WRITE settitlefontsize NOTIFY
                 titlefontsizeChanged)
  Q_PROPERTY(qreal textfontsize READ textfontsize WRITE settextfontsize NOTIFY textfontsizeChanged)
  Q_PROPERTY(QColor editBackgroundColor READ editBackgroundColor WRITE seteditBackgroundColor NOTIFY
                 editBackgroundColorChanged)
  Q_PROPERTY(QColor activetabfontcolor READ activetabfontcolor WRITE setactivetabfontcolor NOTIFY
                 activetabfontcolorChanged)
  Q_PROPERTY(QColor inputboxbackground READ inputboxbackground WRITE setinputboxbackground NOTIFY
                 inputboxbackgroundChanged)
  // added
  // Confirmation Button
  Q_PROPERTY(QColor confirmationbuttongradient1 READ confirmationbuttongradient1 WRITE
                 setconfirmationbuttongradient1 NOTIFY confirmationbuttongradient1Changed)
  Q_PROPERTY(QColor confirmationbuttongradient2 READ confirmationbuttongradient2 WRITE
                 setconfirmationbuttongradient2 NOTIFY confirmationbuttongradient2Changed)
  Q_PROPERTY(qreal confirmationbuttonopacity READ confirmationbuttonopacity WRITE
                 setconfirmationbuttonopacity NOTIFY confirmationbuttonopacityChanged)
  Q_PROPERTY(QColor clickconfirmationbuttongradient1 READ clickconfirmationbuttongradient1 WRITE
                 setclickconfirmationbuttongradient1 NOTIFY clickconfirmationbuttongradient1Changed)
  Q_PROPERTY(QColor clickconfirmationbuttongradient2 READ clickconfirmationbuttongradient2 WRITE
                 setclickconfirmationbuttongradient2 NOTIFY clickconfirmationbuttongradient2Changed)
  Q_PROPERTY(qreal clickconfirmationbuttonopacity READ clickconfirmationbuttonopacity WRITE
                 setclickconfirmationbuttonopacity NOTIFY clickconfirmationbuttonopacityChanged)

  // Exit Button
  Q_PROPERTY(QColor exitbuttoncolor READ exitbuttoncolor WRITE setexitbuttoncolor NOTIFY
                 exitbuttoncolorChanged)
  Q_PROPERTY(QColor exitbuttonhovercolor READ exitbuttonhovercolor WRITE setexitbuttonhovercolor
                 NOTIFY exitbuttonhovercolorChanged)

  // Table
  Q_PROPERTY(QColor tableselectentrycolor READ tableselectentrycolor WRITE settableselectentrycolor
                 NOTIFY tableselectentrycolorChanged)

  // Switches
  Q_PROPERTY(QColor switchcoloronactivated READ switchcoloronactivated WRITE
                 setswitchcoloronactivated NOTIFY switchcoloronactivatedChanged)
  Q_PROPERTY(QColor switchcolorondeactivated READ switchcolorondeactivated WRITE
                 setswitchcolorondeactivated NOTIFY switchcolorondeactivatedChanged)
  Q_PROPERTY(QColor switchhandlecolor READ switchhandlecolor WRITE setswitchhandlecolor NOTIFY
                 switchhandlecolorChanged)
  Q_PROPERTY(qreal switchboxradius READ switchboxradius WRITE setswitchboxradius NOTIFY
                 switchboxradiusChanged)
  Q_PROPERTY(qreal switchhandleradius READ switchhandleradius WRITE setswitchhandleradius NOTIFY
                 switchhandleradiusChanged)

  // Skin Preview
  Q_PROPERTY(qreal skinpreviewnamebaropacity READ skinpreviewnamebaropacity WRITE
                 setskinpreviewnamebaropacity NOTIFY skinpreviewnamebaropacityChanged)
  Q_PROPERTY(QColor skinpreviewnamebarcolor READ skinpreviewnamebarcolor WRITE
                 setskinpreviewnamebarcolor NOTIFY skinpreviewnamebarcolorChanged)
  Q_PROPERTY(QColor skinpreviewnamebarfontcolor READ skinpreviewnamebarfontcolor WRITE
                 setskinpreviewnamebarfontcolor NOTIFY skinpreviewnamebarfontcolorChanged)
  Q_PROPERTY(QColor skinpreviewbackgroundselectionmarkcolor READ
                 skinpreviewbackgroundselectionmarkcolor WRITE
                     setskinpreviewbackgroundselectionmarkcolor NOTIFY
                         skinpreviewbackgroundselectionmarkcolorChanged)
  Q_PROPERTY(qreal skinpreviewbackgroundselectionmarkwidth READ
                 skinpreviewbackgroundselectionmarkwidth WRITE
                     setskinpreviewbackgroundselectionmarkwidth NOTIFY
                         skinpreviewbackgroundselectionmarkwidthChanged)

  // File Element: thumbnailcontainer
  Q_PROPERTY(QColor thumbnailcontainercolor READ thumbnailcontainercolor WRITE
                 setthumbnailcontainercolor NOTIFY thumbnailcontainercolorChanged)

  // HighlightingText (WelcomeBoxElement)
  Q_PROPERTY(qreal highlightingtextmouseoveropacity READ highlightingtextmouseoveropacity WRITE
                 sethighlightingtextmouseoveropacity NOTIFY highlightingtextmouseoveropacityChanged)
  Q_PROPERTY(qreal highlightingtextmargin READ highlightingtextmargin WRITE
                 sethighlightingtextmargin NOTIFY highlightingtextmarginChanged)
  Q_PROPERTY(QColor highlightingtextbackgroundcolor READ highlightingtextbackgroundcolor
                 WRITE sethighlightingtextbackgroundcolor NOTIFY
                     highlightingtextbackgroundcolorChanged)

  // Button hover color
  Q_PROPERTY(QColor buttonhovergradient1 READ buttonhovergradient1 WRITE setbuttonhovergradient1
                 NOTIFY buttonhovergradient1Changed)
  Q_PROPERTY(QColor buttonhovergradient2 READ buttonhovergradient2 WRITE setbuttonhovergradient2
                 NOTIFY buttonhovergradient2Changed)

  // bannermode (TopMenu / WelcomeBoxElement)
  Q_PROPERTY(QColor bannermodeiconrectanglebordercolor READ bannermodeiconrectanglebordercolor WRITE
                 setbannermodeiconrectanglebordercolor NOTIFY
                     bannermodeiconrectanglebordercolorChanged)
  Q_PROPERTY(qreal bannermodeiconrectangleborderwidth READ bannermodeiconrectangleborderwidth WRITE
                 setbannermodeiconrectangleborderwidth NOTIFY
                     bannermodeiconrectangleborderwidthChanged)
  Q_PROPERTY(QColor bannermodeiconrectanglecolor READ bannermodeiconrectanglecolor WRITE
                 setbannermodeiconrectanglecolor NOTIFY bannermodeiconrectanglecolorChanged)
  Q_PROPERTY(QColor bannermodeiconrectanglecolorhighlight READ bannermodeiconrectanglecolorhighlight
                 WRITE setbannermodeiconrectanglecolorhighlight NOTIFY
                     bannermodeiconrectanglecolorhighlightChanged)
  Q_PROPERTY(QColor bannermodetextrectanglecolorhighlight READ bannermodetextrectanglecolorhighlight
                 WRITE setbannermodetextrectanglecolorhighlight NOTIFY
                     bannermodetextrectanglecolorhighlightChanged)

  // Confirmation Button on hover
  Q_PROPERTY(QColor confirmationbuttonhovergradient1 READ confirmationbuttonhovergradient1 WRITE
                 setconfirmationbuttonhovergradient1 NOTIFY confirmationbuttonhovergradient1Changed)
  Q_PROPERTY(QColor confirmationbuttonhovergradient2 READ confirmationbuttonhovergradient2 WRITE
                 setconfirmationbuttonhovergradient2 NOTIFY confirmationbuttonhovergradient2Changed)

  // Checkbox (Radio.qml)
  Q_PROPERTY(QColor radiocheckboxcolor READ radiocheckboxcolor WRITE setradiocheckboxcolor NOTIFY
                 radiocheckboxcolorChanged)

  // bannermode (Text Alignment)
  Q_PROPERTY(qreal bannermodetextalignment READ bannermodetextalignment WRITE
                 setbannermodetextalignment NOTIFY bannermodetextalignmentChanged)

  // textcolor
  Q_PROPERTY(QColor textcolor READ textcolor WRITE settextcolor NOTIFY textcolorChanged)
  Q_PROPERTY(QColor textcolorhighlight READ textcolorhighlight WRITE settextcolorhighlight NOTIFY
                 textcolorhighlightChanged)

  // iconcolor
  Q_PROPERTY(QColor iconcolor READ iconcolor WRITE seticoncolor NOTIFY iconcolorChanged)
  Q_PROPERTY(QColor iconcolorhighlight READ iconcolorhighlight WRITE seticoncolorhighlight NOTIFY
                 iconcolorhighlightChanged)
  Q_PROPERTY(QColor welcomeboxelementiconcolor READ welcomeboxelementiconcolor WRITE
                 setwelcomeboxelementiconcolor NOTIFY welcomeboxelementiconcolorChanged)
  Q_PROPERTY(QColor welcomeboxelementiconcolorbannermode READ welcomeboxelementiconcolorbannermode
                 WRITE setwelcomeboxelementiconcolorbannermode NOTIFY
                     welcomeboxelementiconcolorbannermodeChanged)

  // button text color
  Q_PROPERTY(QColor buttontextcolor READ buttontextcolor WRITE setbuttontextcolor NOTIFY
                 buttontextcolorChanged)
  Q_PROPERTY(QColor confirmationbuttontextcolor READ confirmationbuttontextcolor WRITE
                 setconfirmationbuttontextcolor NOTIFY confirmationbuttontextcolorChanged)

  // Menu Element additional border left hand side
  Q_PROPERTY(QColor menuelementleftbordercolor READ menuelementleftbordercolor WRITE
                 setmenuelementleftbordercolor NOTIFY menuelementleftbordercolorChanged)
  Q_PROPERTY(qreal menuelementleftborderwidth READ menuelementleftborderwidth WRITE
                 setmenuelementleftborderwidth NOTIFY menuelementleftborderwidthChanged)

  // additional Logo for product presentations
  Q_PROPERTY(QString presentationlogo READ presentationlogo WRITE setpresentationlogo NOTIFY
                 presentationlogoChanged)

  // color for table headline (text)
  Q_PROPERTY(QColor tablecolortitletext READ tablecolortitletext WRITE settablecolortitletext NOTIFY
                 tablecolortitletextChanged)

  // Calender (color)
  Q_PROPERTY(QColor calenderplaceholderdatescolor READ calenderplaceholderdatescolor WRITE
                 setcalenderplaceholderdatescolor NOTIFY calenderplaceholderdatescolorChanged)
  Q_PROPERTY(QColor calenderselecteddatecolor READ calenderselecteddatecolor WRITE
                 setcalenderselecteddatecolor NOTIFY calenderselecteddatecolorChanged)
  Q_PROPERTY(QColor calenderdatesofselectedmonthcolor READ calenderdatesofselectedmonthcolor WRITE
                 setcalenderdatesofselectedmonthcolor NOTIFY
                     calenderdatesofselectedmonthcolorChanged)
  Q_PROPERTY(QColor calenderbarofselectedmonthcolor READ calenderbarofselectedmonthcolor WRITE
                 setcalenderbarofselectedmonthcolor NOTIFY calenderbarofselectedmonthcolorChanged)

  // Icons on background (color)
  Q_PROPERTY(QColor icononbackgroundcolor READ icononbackgroundcolor WRITE seticononbackgroundcolor
                 NOTIFY icononbackgroundcolorChanged)

  // Calender (color)
  Q_PROPERTY(QColor calenderdatebackgroundcolor READ calenderdatebackgroundcolor WRITE
                 setcalenderdatebackgroundcolor NOTIFY calenderdatebackgroundcolorChanged)
  Q_PROPERTY(QColor calenderselecteddatebackgroundcolor READ calenderselecteddatebackgroundcolor
                 WRITE setcalenderselecteddatebackgroundcolor NOTIFY
                     calenderselecteddatebackgroundcolorChanged)

  Q_PROPERTY(QColor grouptitlecolor READ grouptitlecolor WRITE setgrouptitlecolor NOTIFY
                 grouptitlecolorChanged)

  // Cancel Button (color)
  Q_PROPERTY(QColor cancelbuttongradient1 READ cancelbuttongradient1 WRITE setcancelbuttongradient1
                 NOTIFY cancelbuttongradient1Changed)
  Q_PROPERTY(QColor cancelbuttongradient2 READ cancelbuttongradient2 WRITE setcancelbuttongradient2
                 NOTIFY cancelbuttongradient2Changed)
  Q_PROPERTY(QColor clickcancelbuttongradient1 READ clickcancelbuttongradient1 WRITE
                 setclickcancelbuttongradient1 NOTIFY clickcancelbuttongradient1Changed)
  Q_PROPERTY(QColor clickcancelbuttongradient2 READ clickcancelbuttongradient2 WRITE
                 setclickcancelbuttongradient2 NOTIFY clickcancelbuttongradient2Changed)
  Q_PROPERTY(QColor cancelbuttonhovergradient1 READ cancelbuttonhovergradient1 WRITE
                 setcancelbuttonhovergradient1 NOTIFY cancelbuttonhovergradient1Changed)
  Q_PROPERTY(QColor cancelbuttonhovergradient2 READ cancelbuttonhovergradient2 WRITE
                 setcancelbuttonhovergradient2 NOTIFY cancelbuttonhovergradient2Changed)

  // Calendar property for week number color
  Q_PROPERTY(QColor calendarweeknumbercolor READ calendarweeknumbercolor WRITE
                 setcalendarweeknumbercolor NOTIFY calendarweeknumbercolorChanged)

  // radio color for selected radio checkbox and label box color
  Q_PROPERTY(QColor radiocheckboxcolorselected READ radiocheckboxcolorselected WRITE
                 setradiocheckboxcolorselected NOTIFY radiocheckboxcolorselectedChanged)
  Q_PROPERTY(QColor radiocontainerlabelboxcolor READ radiocontainerlabelboxcolor WRITE
                 setradiocontainerlabelboxcolor NOTIFY radiocontainerlabelboxcolorChanged)

  // color for standalone icons
  Q_PROPERTY(QColor standaloneiconcolor READ standaloneiconcolor WRITE setstandaloneiconcolor NOTIFY
                 standaloneiconcolorChanged)
  Q_PROPERTY(QColor standaloneiconcolorhighlight READ standaloneiconcolorhighlight WRITE
                 setstandaloneiconcolorhighlight NOTIFY standaloneiconcolorhighlightChanged)

  // color for iconbackgound on hover
  Q_PROPERTY(QColor iconbackgroundhovercolor READ iconbackgroundhovercolor WRITE
                 seticonbackgroundhovercolor NOTIFY iconbackgroundhovercolorChanged)

  // color for dots of filechooser
  Q_PROPERTY(QColor filechooserdotscolor READ filechooserdotscolor WRITE setfilechooserdotscolor
                 NOTIFY filechooserdotscolorChanged)

  // color of topbar in popup.qml
  Q_PROPERTY(QColor popuptopbarcolor READ popuptopbarcolor WRITE setpopuptopbarcolor NOTIFY
                 popuptopbarcolorChanged)

  // text colors for input fields / thumbnailcontainer
  Q_PROPERTY(QColor inputboxtextcolor READ inputboxtextcolor WRITE setinputboxtextcolor NOTIFY
                 inputboxtextcolorChanged)
  Q_PROPERTY(QColor inputboxhighlightedtextcolor READ inputboxhighlightedtextcolor WRITE
                 setinputboxhighlightedtextcolor NOTIFY inputboxhighlightedtextcolorChanged)
  Q_PROPERTY(QColor inputboxselectedtextcolor READ inputboxselectedtextcolor WRITE
                 setinputboxselectedtextcolor NOTIFY inputboxselectedtextcolorChanged)
  Q_PROPERTY(QColor inputboxtypedtextcolor READ inputboxtypedtextcolor WRITE
                 setinputboxtypedtextcolor NOTIFY inputboxtypedtextcolorChanged)
  Q_PROPERTY(QColor inputboxsmalltextcolor READ inputboxsmalltextcolor WRITE
                 setinputboxsmalltextcolor NOTIFY inputboxsmalltextcolorChanged)
  Q_PROPERTY(QColor thumbnailcontainertextcolor READ thumbnailcontainertextcolor WRITE
                 setthumbnailcontainertextcolor NOTIFY thumbnailcontainertextcolorChanged)
  Q_PROPERTY(QColor thumbnailcontainersmalltextcolor READ thumbnailcontainersmalltextcolor WRITE
                 setthumbnailcontainersmalltextcolor NOTIFY thumbnailcontainersmalltextcolorChanged)

 public:
  SkinProvider() {
    _fontsizemultiplier = 1;
    _synnextlogo = "Skins/ModernGrey/logo.png";
    _background = "";
    _radius = 5;
    _buttongradient1 = "#94c600";
    _buttongradient2 = "#94c600";
    _buttonopacity = 1;
    _clickbuttongradient1 = "#8dc4e7";
    _clickbuttongradient2 = "#80b5d7";
    _clickbuttonopacity = 1;
    _tablecolortitle = "#b7ab9c";
    _tableopacitytitle = 1;
    _tablecolorline1 = "#f6f1ed";
    _tableopacityline1 = 1;
    _tablecolorline2 = "transparent";  //"#ffffff";
    _tableopacityline2 = 1;
    _fastlinkingcolor = "#caf278";
    _fastlinkingopacity = 1;
    _intelliboxcolor = "#d4dcb1";
    _intelliboxopacity = 1;
    _menuboxcolor = "#595959";
    _menuboxopacity = 0.89;
    _tabbedmenuboxcolor = "#ffffff";
    _tabbedmenuboxopacity = 0.93;
    _titlecolor = "#ffffff";
    _popupcolor = "#ffffff";
    _popupopacity = 1;
    _inactivetabcolor = "#ffffff";
    _inactivefontcolor = "#c9c7bf";
    _listbackgroundcolor = "#b8bcae";
    _suggestbubbleimage = "Skins/ModernGrey/suggestionbubble.png";
    _suggestbubbleopacity = 0.95;
    _tooltipcolor = "#a3bcd8";
    _bordersize = 1;
    _bordercolor = "#aba8a9";
    _usedfont = "Arial";
    _warningcolor = "#caf278";
    _selectcolor = "#d4dcb1";
    _lockedinputcolor = "#d4dcb1";
    _titlefontsize = 14;
    _textfontsize = 12;
    _titlefontsizebase = 14;
    _textfontsizebase = 12;
    _editBackgroundColor = "#741E3A";
    _activetabfontcolor = "#595959";
    _inputboxbackground = "#f6f1ed";
    // added
    _confirmationbuttongradient1 = "#66B22D";
    _confirmationbuttongradient2 = "#66B22D";
    _confirmationbuttonopacity = 1;
    _clickconfirmationbuttongradient1 = "#5EA12A";
    _clickconfirmationbuttongradient2 = "#5EA12A";
    _clickconfirmationbuttonopacity = 1;
    _exitbuttoncolor = "#2979EF";
    _exitbuttonhovercolor = "#E83C3B";
    _tableselectentrycolor = "#2979EF";
    _switchcoloronactivated = "#8BC63F";
    _switchcolorondeactivated = "#999999";
    _switchhandlecolor = "#FFFFFF";
    _switchboxradius = 10;
    _switchhandleradius = 10;
    _skinpreviewnamebaropacity = 1;
    _skinpreviewnamebarcolor = "#2979EF";
    _skinpreviewnamebarfontcolor = "#FFFFFF";
    _skinpreviewbackgroundselectionmarkcolor = "#2979EF";
    _skinpreviewbackgroundselectionmarkwidth = 10;
    _thumbnailcontainercolor = "tranparent";
    _highlightingtextmouseoveropacity = 0.2;
    _highlightingtextmargin = 5;
    _highlightingtextbackgroundcolor = "#BDBDBD";
    _buttonhovergradient1 = "#0835FF";
    _buttonhovergradient2 = "#0835FF";
    _bannermodeiconrectanglebordercolor = "white";
    _bannermodeiconrectangleborderwidth = 5;
    _bannermodeiconrectanglecolor = "blue";
    _bannermodeiconrectanglecolorhighlight = "red";
    _bannermodetextrectanglecolorhighlight = "yellow";
    _confirmationbuttonhovergradient1 = "darkgreen";
    _confirmationbuttonhovergradient2 = "darkgreen";
    _radiocheckboxcolor = "#E6E6E6";
    _bannermodetextalignment = 128;
    _textcolor = "#000000";
    _textcolorhighlight = "#FFFFFF";
    _iconcolor = "#000000";
    _iconcolorhighlight = "#2979EF";
    _welcomeboxelementiconcolor = "#FFFFFF";
    _welcomeboxelementiconcolorbannermode = "#FFFFFF";
    _buttontextcolor = "#FFFFFF";
    _confirmationbuttontextcolor = "#FFFFFF";
    _menuelementleftbordercolor = "#FFFFFF";
    _menuelementleftborderwidth = 0;
    _presentationlogo = "Skins/Universe/Logoexample.png";
    _tablecolortitletext = "#FFFFFF";
    _calenderplaceholderdatescolor = "#848484";
    _calenderselecteddatecolor = "#2979EF";
    _calenderdatesofselectedmonthcolor = "#000000";
    _calenderbarofselectedmonthcolor = "#2979EF";
    _icononbackgroundcolor = "#FF0000";
    _calenderdatebackgroundcolor = "#000000";
    _calenderselecteddatebackgroundcolor = "#FFFFFF";
    _grouptitlecolor = "#FFFFFF";
    _cancelbuttongradient1 = "#E83C3B";
    _cancelbuttongradient2 = "#E83C3B";
    _clickcancelbuttongradient1 = "#d71919";
    _clickcancelbuttongradient2 = "#d71919";
    _cancelbuttonhovergradient1 = "#b71515";
    _cancelbuttonhovergradient2 = "#b71515";
    _calendarweeknumbercolor = "#000000";
    _radiocheckboxcolorselected = "#000000";
    _radiocontainerlabelboxcolor = "#808080";
    _standaloneiconcolor = "#000000";
    _standaloneiconcolorhighlight = "#2979EF";
    _iconbackgroundhovercolor = "#2979EF";
    _filechooserdotscolor = "#000000";
    _popuptopbarcolor = "#dedede";
    _inputboxtextcolor = "#000000";
    _inputboxhighlightedtextcolor = "#000000";
    _inputboxselectedtextcolor = "#000000";
    _inputboxtypedtextcolor = "#000000";
    _inputboxsmalltextcolor = "#000000";
    _thumbnailcontainertextcolor = "#000000";
    _thumbnailcontainersmalltextcolor = "#000000";
  }
  void registerApp(QGuiApplication *globalapp) {
    app = globalapp;
    app->setFont(QFont(_usedfont, _textfontsize));
    // TODO : Call to QGuiApplication->sync()?
  }

  QString synnextlogo() const { return _synnextlogo; }
  QString background() const { return _background; }
  int radius() const { return _radius; }
  QColor buttongradient1() const { return _buttongradient1; }
  QColor buttongradient2() const { return _buttongradient2; }
  qreal buttonopacity() const { return _buttonopacity; }
  QColor clickbuttongradient1() const { return _clickbuttongradient1; }
  QColor clickbuttongradient2() const { return _clickbuttongradient2; }
  qreal clickbuttonopacity() const { return _clickbuttonopacity; }
  QColor tablecolortitle() const { return _tablecolortitle; }
  qreal tableopacitytitle() const { return _tableopacitytitle; }
  QColor tablecolorline1() const { return _tablecolorline1; }
  qreal tableopacityline1() const { return _tableopacityline1; }
  QColor tablecolorline2() const { return _tablecolorline2; }
  qreal tableopacityline2() const { return _tableopacityline2; }
  QColor fastlinkingcolor() const { return _fastlinkingcolor; }
  qreal fastlinkingopacity() const { return _fastlinkingopacity; }
  QColor intelliboxcolor() const { return _intelliboxcolor; }
  qreal intelliboxopacity() const { return _intelliboxopacity; }
  QColor menuboxcolor() const { return _menuboxcolor; }
  qreal menuboxopacity() const { return _menuboxopacity; }
  QColor tabbedmenuboxcolor() const { return _tabbedmenuboxcolor; }
  qreal tabbedmenuboxopacity() const { return _tabbedmenuboxopacity; }
  QColor titlecolor() const { return _titlecolor; }
  QColor popupcolor() const { return _popupcolor; }
  qreal popupopacity() const { return _popupopacity; }
  QColor inactivefontcolor() const { return _inactivefontcolor; }
  QColor inactivetabcolor() const { return _inactivetabcolor; }
  QColor listbackgroundcolor() const { return _listbackgroundcolor; }
  QString suggestbubbleimage() const { return _suggestbubbleimage; }
  qreal suggestbubbleopacity() const { return _suggestbubbleopacity; }
  QColor tooltipcolor() const { return _tooltipcolor; }
  int bordersize() const { return _bordersize; }
  QColor bordercolor() const { return _bordercolor; }
  QString usedfont() const { return _usedfont; }
  QColor warningcolor() const { return _warningcolor; }
  QColor selectcolor() const { return _selectcolor; }
  QColor lockedinputcolor() const { return _lockedinputcolor; }
  QColor inputboxbackground() const { return _inputboxbackground; }
  qreal titlefontsize() const { return _titlefontsize; }
  qreal textfontsize() const { return _textfontsize; }
  QColor editBackgroundColor() const { return _editBackgroundColor; }
  QColor activetabfontcolor() const { return _activetabfontcolor; }
  // added
  QColor confirmationbuttongradient1() const { return _confirmationbuttongradient1; }
  QColor confirmationbuttongradient2() const { return _confirmationbuttongradient2; }
  qreal confirmationbuttonopacity() const { return _confirmationbuttonopacity; }
  QColor clickconfirmationbuttongradient1() const { return _clickconfirmationbuttongradient1; }
  QColor clickconfirmationbuttongradient2() const { return _clickconfirmationbuttongradient2; }
  qreal clickconfirmationbuttonopacity() const { return _clickconfirmationbuttonopacity; }
  QColor exitbuttoncolor() const { return _exitbuttoncolor; }
  QColor exitbuttonhovercolor() const { return _exitbuttonhovercolor; }
  QColor tableselectentrycolor() const { return _tableselectentrycolor; }
  QColor switchcoloronactivated() const { return _switchcoloronactivated; }
  QColor switchcolorondeactivated() const { return _switchcolorondeactivated; }
  QColor switchhandlecolor() const { return _switchhandlecolor; }
  qreal switchboxradius() const { return _switchboxradius; }
  qreal switchhandleradius() const { return _switchhandleradius; }
  qreal skinpreviewnamebaropacity() const { return _skinpreviewnamebaropacity; }
  QColor skinpreviewnamebarcolor() const { return _skinpreviewnamebarcolor; }
  QColor skinpreviewnamebarfontcolor() const { return _skinpreviewnamebarfontcolor; }
  QColor skinpreviewbackgroundselectionmarkcolor() const {
    return _skinpreviewbackgroundselectionmarkcolor;
  }
  qreal skinpreviewbackgroundselectionmarkwidth() const {
    return _skinpreviewbackgroundselectionmarkwidth;
  }
  QColor thumbnailcontainercolor() const { return _thumbnailcontainercolor; }
  qreal highlightingtextmouseoveropacity() const { return _highlightingtextmouseoveropacity; }
  qreal highlightingtextmargin() const { return _highlightingtextmargin; }
  QColor highlightingtextbackgroundcolor() const {
    return _highlightingtextbackgroundcolor;
  }
  QColor buttonhovergradient1() const { return _buttonhovergradient1; }
  QColor buttonhovergradient2() const { return _buttonhovergradient2; }
  QColor bannermodeiconrectanglebordercolor() const { return _bannermodeiconrectanglebordercolor; }
  qreal bannermodeiconrectangleborderwidth() const { return _bannermodeiconrectangleborderwidth; }
  QColor bannermodeiconrectanglecolor() const { return _bannermodeiconrectanglecolor; }
  QColor bannermodeiconrectanglecolorhighlight() const {
    return _bannermodeiconrectanglecolorhighlight;
  }
  QColor bannermodetextrectanglecolorhighlight() const {
    return _bannermodetextrectanglecolorhighlight;
  }
  QColor confirmationbuttonhovergradient1() const { return _confirmationbuttonhovergradient1; }
  QColor confirmationbuttonhovergradient2() const { return _confirmationbuttonhovergradient2; }
  QColor radiocheckboxcolor() const { return _radiocheckboxcolor; }
  qreal bannermodetextalignment() const { return _bannermodetextalignment; }
  QColor textcolor() const { return _textcolor; }
  QColor textcolorhighlight() const { return _textcolorhighlight; }
  QColor iconcolor() const { return _iconcolor; }
  QColor iconcolorhighlight() const { return _iconcolorhighlight; }
  QColor welcomeboxelementiconcolor() const { return _welcomeboxelementiconcolor; }
  QColor welcomeboxelementiconcolorbannermode() const {
    return _welcomeboxelementiconcolorbannermode;
  }
  QColor buttontextcolor() const { return _buttontextcolor; }
  QColor confirmationbuttontextcolor() const { return _confirmationbuttontextcolor; }
  QColor menuelementleftbordercolor() const { return _menuelementleftbordercolor; }
  qreal menuelementleftborderwidth() const { return _menuelementleftborderwidth; }
  QString presentationlogo() const { return _presentationlogo; }
  QColor tablecolortitletext() const { return _tablecolortitletext; }
  QColor calenderplaceholderdatescolor() const { return _calenderplaceholderdatescolor; }
  QColor calenderselecteddatecolor() const { return _calenderselecteddatecolor; }
  QColor calenderdatesofselectedmonthcolor() const { return _calenderdatesofselectedmonthcolor; }
  QColor calenderbarofselectedmonthcolor() const { return _calenderbarofselectedmonthcolor; }
  QColor icononbackgroundcolor() const { return _icononbackgroundcolor; }
  QColor calenderdatebackgroundcolor() const { return _calenderdatebackgroundcolor; }
  QColor calenderselecteddatebackgroundcolor() const {
    return _calenderselecteddatebackgroundcolor;
  }
  QColor grouptitlecolor() const { return _grouptitlecolor; }
  QColor cancelbuttongradient1() const { return _cancelbuttongradient1; }
  QColor cancelbuttongradient2() const { return _cancelbuttongradient2; }
  QColor clickcancelbuttongradient1() const { return _clickcancelbuttongradient1; }
  QColor clickcancelbuttongradient2() const { return _clickcancelbuttongradient2; }
  QColor cancelbuttonhovergradient1() const { return _cancelbuttonhovergradient1; }
  QColor cancelbuttonhovergradient2() const { return _cancelbuttonhovergradient2; }
  QColor calendarweeknumbercolor() const { return _calendarweeknumbercolor; }
  QColor radiocheckboxcolorselected() const { return _radiocheckboxcolorselected; }
  QColor radiocontainerlabelboxcolor() const { return _radiocontainerlabelboxcolor; }
  QColor standaloneiconcolor() const { return _standaloneiconcolor; }
  QColor standaloneiconcolorhighlight() const { return _standaloneiconcolorhighlight; }
  QColor iconbackgroundhovercolor() const { return _iconbackgroundhovercolor; }
  QColor filechooserdotscolor() const { return _filechooserdotscolor; }
  QColor popuptopbarcolor() const { return _popuptopbarcolor; }
  QColor inputboxtextcolor() const { return _inputboxtextcolor; }
  QColor inputboxhighlightedtextcolor() const { return _inputboxhighlightedtextcolor; }
  QColor inputboxselectedtextcolor() const { return _inputboxselectedtextcolor; }
  QColor inputboxtypedtextcolor() const { return _inputboxtypedtextcolor; }
  QColor inputboxsmalltextcolor() const { return _inputboxsmalltextcolor; }
  QColor thumbnailcontainertextcolor() const { return _thumbnailcontainertextcolor; }
  QColor thumbnailcontainersmalltextcolor() const { return _thumbnailcontainersmalltextcolor; }

  void setsynnextlogo(const QString &synnextlogo) {
    QFile custom_logo(":/qml/Skins/customlogo.png");
    if (custom_logo.exists())
      _synnextlogo = "Skins/customlogo.png";
    else
      _synnextlogo = synnextlogo;
    emit synnextlogoChanged();
  }
  void setbackground(const QString &background) {
    _background = background;
    emit backgroundChanged();
  }
  void setradius(const int &radius) {
    _radius = radius;
    emit radiusChanged();
  }
  void setbuttongradient1(const QColor &buttongradient1) {
    _buttongradient1 = buttongradient1;
    emit buttongradient1Changed();
  }
  void setbuttongradient2(const QColor &buttongradient2) {
    _buttongradient2 = buttongradient2;
    emit buttongradient2Changed();
  }
  void setbuttonopacity(const qreal &buttonopacity) {
    _buttonopacity = buttonopacity;
    emit buttonopacityChanged();
  }
  void setclickbuttongradient1(const QColor &clickbuttongradient1) {
    _clickbuttongradient1 = clickbuttongradient1;
    emit clickbuttongradient1Changed();
  }
  void setclickbuttongradient2(const QColor &clickbuttongradient2) {
    _clickbuttongradient2 = clickbuttongradient2;
    emit clickbuttongradient2Changed();
  }
  void setclickbuttonopacity(const qreal &clickbuttonopacity) {
    _clickbuttonopacity = clickbuttonopacity;
    emit clickbuttonopacityChanged();
  }
  void settablecolortitle(const QColor &tablecolortitle) {
    _tablecolortitle = tablecolortitle;
    emit tablecolortitleChanged();
  }
  void settableopacitytitle(const qreal &tableopacitytitle) {
    _tableopacitytitle = tableopacitytitle;
    emit tableopacitytitleChanged();
  }
  void settablecolorline1(const QColor &tablecolorline1) {
    _tablecolorline1 = tablecolorline1;
    emit tablecolorline1Changed();
  }
  void settableopacityline1(const qreal &tableopacityline1) {
    _tableopacityline1 = tableopacityline1;
    emit tableopacityline1Changed();
  }
  void settablecolorline2(const QColor &tablecolorline2) {
    _tablecolorline2 = tablecolorline2;
    emit tablecolorline2Changed();
  }
  void settableopacityline2(const qreal &tableopacityline2) {
    _tableopacityline2 = tableopacityline2;
    emit tableopacityline2Changed();
  }
  void setfastlinkingcolor(const QColor &fastlinkingcolor) {
    _fastlinkingcolor = fastlinkingcolor;
    emit fastlinkingcolorChanged();
  }
  void setfastlinkingopacity(const qreal &fastlinkingopacity) {
    _fastlinkingopacity = fastlinkingopacity;
    emit fastlinkingopacityChanged();
  }
  void setintelliboxcolor(const QColor &intelliboxcolor) {
    _intelliboxcolor = intelliboxcolor;
    emit intelliboxcolorChanged();
  }
  void setintelliboxopacity(const qreal &intelliboxopacity) {
    _intelliboxopacity = intelliboxopacity;
    emit intelliboxopacityChanged();
  }
  void setmenuboxcolor(const QColor &menuboxcolor) {
    _menuboxcolor = menuboxcolor;
    emit menuboxcolorChanged();
  }
  void setmenuboxopacity(const qreal &menuboxopacity) {
    _menuboxopacity = menuboxopacity;
    emit menuboxopacityChanged();
  }
  void settabbedmenuboxcolor(const QColor &tabbedmenuboxcolor) {
    _tabbedmenuboxcolor = tabbedmenuboxcolor;
    emit tabbedmenuboxcolorChanged();
  }
  void settabbedmenuboxopacity(const qreal &tabbedmenuboxopacity) {
    _tabbedmenuboxopacity = tabbedmenuboxopacity;
    emit tabbedmenuboxopacityChanged();
  }
  void settitlecolor(const QColor &titlecolor) {
    _titlecolor = titlecolor;
    emit titlecolorChanged();
  }
  void setpopupcolor(const QColor &popupcolor) {
    _popupcolor = popupcolor;
    emit popupcolorChanged();
  }
  void setpopupopacity(const qreal &popupopacity) {
    _popupopacity = popupopacity;
    emit popupopacityChanged();
  }
  void setinactivefontcolor(const QColor &inactivefontcolor) {
    _inactivefontcolor = inactivefontcolor;
    emit inactivefontcolorChanged();
  }
  void setinactivetabcolor(const QColor &inactivetabcolor) {
    _inactivetabcolor = inactivetabcolor;
    emit inactivetabcolorChanged();
  }
  void setlistbackgroundcolor(const QColor &listbackgroundcolor) {
    _listbackgroundcolor = listbackgroundcolor;
    emit listbackgroundcolorChanged();
  }
  void setsuggestbubbleimage(const QString &suggestbubbleimage) {
    _suggestbubbleimage = suggestbubbleimage;
    emit suggestbubbleimageChanged();
  }
  void setsuggestbubbleopacity(const qreal &suggestbubbleopacity) {
    _suggestbubbleopacity = suggestbubbleopacity;
    emit suggestbubbleopacityChanged();
  }
  void settooltipcolor(const QColor &tooltipcolor) {
    _tooltipcolor = tooltipcolor;
    emit tooltipcolorChanged();
  }
  void setbordersize(const int &bordersize) {
    _bordersize = bordersize;
    emit bordersizeChanged();
  }
  void setbordercolor(const QColor &bordercolor) {
    _bordercolor = bordercolor;
    emit bordercolorChanged();
  }
  void setusedfont(const QString &usedfont) {
    _usedfont = usedfont;
    app->setFont(QFont(_usedfont, _textfontsize));
    emit usedfontChanged();
  }
  void setwarningcolor(const QColor &warningcolor) {
    _warningcolor = warningcolor;
    emit warningcolorChanged();
  }
  void setselectcolor(const QColor &selectcolor) {
    _selectcolor = selectcolor;
    emit selectcolorChanged();
  }
  void setlockedinputcolor(const QColor &lockedinputcolor) {
    _lockedinputcolor = lockedinputcolor;
    emit lockedinputcolorChanged();
  }
  void settitlefontsize(const qreal &titlefontsize) {
    _titlefontsizebase = titlefontsize;
    _titlefontsize = titlefontsize * _fontsizemultiplier;
    emit titlefontsizeChanged();
  }
  void settextfontsize(const qreal &textfontsize) {
    _textfontsizebase = textfontsize;
    _textfontsize = textfontsize * _fontsizemultiplier;
    app->setFont(QFont(_usedfont, _textfontsize));
    emit textfontsizeChanged();
  }
  void seteditBackgroundColor(const QColor &editBackgroundColor) {
    _editBackgroundColor = editBackgroundColor;
    emit editBackgroundColorChanged();
  }
  void setactivetabfontcolor(const QColor &activetabfontcolor) {
    _activetabfontcolor = activetabfontcolor;
    emit activetabfontcolorChanged();
  }
  void setinputboxbackground(const QColor &inputboxbackground) {
    _inputboxbackground = inputboxbackground;
    emit inputboxbackgroundChanged();
  }

  void setfontsizemultiplier(qreal mult) {
    _fontsizemultiplier = mult;
    settitlefontsize(_titlefontsizebase);
    settextfontsize(_textfontsizebase);
  }
  // added
  void setconfirmationbuttongradient1(const QColor &confirmationbuttongradient1) {
    _confirmationbuttongradient1 = confirmationbuttongradient1;
    emit confirmationbuttongradient1Changed();
  }
  void setconfirmationbuttongradient2(const QColor &confirmationbuttongradient2) {
    _confirmationbuttongradient2 = confirmationbuttongradient2;
    emit confirmationbuttongradient2Changed();
  }
  void setconfirmationbuttonopacity(const qreal &confirmationbuttonopacity) {
    _confirmationbuttonopacity = confirmationbuttonopacity;
    emit confirmationbuttonopacityChanged();
  }
  void setclickconfirmationbuttongradient1(const QColor &clickconfirmationbuttongradient1) {
    _clickconfirmationbuttongradient1 = clickconfirmationbuttongradient1;
    emit clickconfirmationbuttongradient1Changed();
  }
  void setclickconfirmationbuttongradient2(const QColor &clickconfirmationbuttongradient2) {
    _clickconfirmationbuttongradient2 = clickconfirmationbuttongradient2;
    emit clickconfirmationbuttongradient2Changed();
  }
  void setclickconfirmationbuttonopacity(const qreal &clickconfirmationbuttonopacity) {
    _clickconfirmationbuttonopacity = clickconfirmationbuttonopacity;
    emit clickconfirmationbuttonopacityChanged();
  }
  void setexitbuttoncolor(const QColor &exitbuttoncolor) {
    _exitbuttoncolor = exitbuttoncolor;
    emit exitbuttoncolorChanged();
  }
  void setexitbuttonhovercolor(const QColor &exitbuttonhovercolor) {
    _exitbuttonhovercolor = exitbuttonhovercolor;
    emit exitbuttonhovercolorChanged();
  }
  void settableselectentrycolor(const QColor &tableselectentrycolor) {
    _tableselectentrycolor = tableselectentrycolor;
    emit tableselectentrycolorChanged();
  }
  void setswitchcoloronactivated(const QColor &switchcoloronactivated) {
    _switchcoloronactivated = switchcoloronactivated;
    emit switchcoloronactivatedChanged();
  }
  void setswitchcolorondeactivated(const QColor &switchcolorondeactivated) {
    _switchcolorondeactivated = switchcolorondeactivated;
    emit switchcolorondeactivatedChanged();
  }
  void setswitchhandlecolor(const QColor &switchhandlecolor) {
    _switchhandlecolor = switchhandlecolor;
    emit switchhandlecolorChanged();
  }
  void setswitchboxradius(const qreal &switchboxradius) {
    _switchboxradius = switchboxradius;
    emit switchboxradiusChanged();
  }
  void setswitchhandleradius(const qreal &switchhandleradius) {
    _switchhandleradius = switchhandleradius;
    emit switchhandleradiusChanged();
  }
  void setskinpreviewnamebaropacity(const qreal &skinpreviewnamebaropacity) {
    _skinpreviewnamebaropacity = skinpreviewnamebaropacity;
    emit skinpreviewnamebaropacityChanged();
  }
  void setskinpreviewnamebarcolor(const QColor &skinpreviewnamebarcolor) {
    _skinpreviewnamebarcolor = skinpreviewnamebarcolor;
    emit skinpreviewnamebarcolorChanged();
  }
  void setskinpreviewnamebarfontcolor(const QColor &skinpreviewnamebarfontcolor) {
    _skinpreviewnamebarfontcolor = skinpreviewnamebarfontcolor;
    emit skinpreviewnamebarfontcolorChanged();
  }
  void setskinpreviewbackgroundselectionmarkcolor(
      const QColor &skinpreviewbackgroundselectionmarkcolor) {
    _skinpreviewbackgroundselectionmarkcolor = skinpreviewbackgroundselectionmarkcolor;
    emit skinpreviewbackgroundselectionmarkcolorChanged();
  }
  void setskinpreviewbackgroundselectionmarkwidth(
      const qreal &skinpreviewbackgroundselectionmarkwidth) {
    _skinpreviewbackgroundselectionmarkwidth = skinpreviewbackgroundselectionmarkwidth;
    emit skinpreviewbackgroundselectionmarkwidthChanged();
  }
  void setthumbnailcontainercolor(const QColor &thumbnailcontainercolor) {
    _thumbnailcontainercolor = thumbnailcontainercolor;
    emit thumbnailcontainercolorChanged();
  }
  void sethighlightingtextmouseoveropacity(const qreal &highlightingtextmouseoveropacity) {
    _highlightingtextmouseoveropacity = highlightingtextmouseoveropacity;
    emit highlightingtextmouseoveropacityChanged();
  }
  void sethighlightingtextmargin(const qreal &highlightingtextmargin) {
    _highlightingtextmargin = highlightingtextmargin;
    emit highlightingtextmarginChanged();
  }
  void sethighlightingtextbackgroundcolor(const QColor &highlightingtextbackgroundcolor) {
    _highlightingtextbackgroundcolor = highlightingtextbackgroundcolor;
    emit highlightingtextbackgroundcolorChanged();
  }
  void setbuttonhovergradient1(const QColor &buttonhovergradient1) {
    _buttonhovergradient1 = buttonhovergradient1;
    emit buttonhovergradient1Changed();
  }
  void setbuttonhovergradient2(const QColor &buttonhovergradient2) {
    _buttonhovergradient2 = buttonhovergradient2;
    emit buttonhovergradient2Changed();
  }
  void setbannermodeiconrectanglebordercolor(const QColor &bannermodeiconrectanglebordercolor) {
    _bannermodeiconrectanglebordercolor = bannermodeiconrectanglebordercolor;
    emit bannermodeiconrectanglebordercolorChanged();
  }
  void setbannermodeiconrectangleborderwidth(const qreal &bannermodeiconrectangleborderwidth) {
    _bannermodeiconrectangleborderwidth = bannermodeiconrectangleborderwidth;
    emit bannermodeiconrectangleborderwidthChanged();
  }
  void setbannermodeiconrectanglecolor(const QColor &bannermodeiconrectanglecolor) {
    _bannermodeiconrectanglecolor = bannermodeiconrectanglecolor;
    emit bannermodeiconrectanglecolorChanged();
  }
  void setbannermodeiconrectanglecolorhighlight(
      const QColor &bannermodeiconrectanglecolorhighlight) {
    _bannermodeiconrectanglecolorhighlight = bannermodeiconrectanglecolorhighlight;
    emit bannermodeiconrectanglecolorhighlightChanged();
  }
  void setbannermodetextrectanglecolorhighlight(
      const QColor &bannermodetextrectanglecolorhighlight) {
    _bannermodetextrectanglecolorhighlight = bannermodetextrectanglecolorhighlight;
    emit bannermodetextrectanglecolorhighlightChanged();
  }
  void setconfirmationbuttonhovergradient1(const QColor &confirmationbuttonhovergradient1) {
    _confirmationbuttonhovergradient1 = confirmationbuttonhovergradient1;
    emit confirmationbuttonhovergradient1Changed();
  }
  void setconfirmationbuttonhovergradient2(const QColor &confirmationbuttonhovergradient2) {
    _confirmationbuttonhovergradient2 = confirmationbuttonhovergradient2;
    emit confirmationbuttonhovergradient2Changed();
  }
  void setradiocheckboxcolor(const QColor &radiocheckboxcolor) {
    _radiocheckboxcolor = radiocheckboxcolor;
    emit radiocheckboxcolorChanged();
  }
  void setbannermodetextalignment(const qreal &bannermodetextalignment) {
    _bannermodetextalignment = bannermodetextalignment;
    emit bannermodetextalignmentChanged();
  }
  void settextcolor(const QColor &textcolor) {
    _textcolor = textcolor;
    emit textcolorChanged();
  }
  void settextcolorhighlight(const QColor &textcolorhighlight) {
    _textcolorhighlight = textcolorhighlight;
    emit textcolorhighlightChanged();
  }
  void seticoncolor(const QColor &iconcolor) {
    _iconcolor = iconcolor;
    emit iconcolorChanged();
  }
  void seticoncolorhighlight(const QColor &iconcolorhighlight) {
    _iconcolorhighlight = iconcolorhighlight;
    emit iconcolorhighlightChanged();
  }
  void setwelcomeboxelementiconcolor(const QColor &welcomeboxelementiconcolor) {
    _welcomeboxelementiconcolor = welcomeboxelementiconcolor;
    emit welcomeboxelementiconcolorChanged();
  }
  void setwelcomeboxelementiconcolorbannermode(const QColor &welcomeboxelementiconcolorbannermode) {
    _welcomeboxelementiconcolorbannermode = welcomeboxelementiconcolorbannermode;
    emit welcomeboxelementiconcolorbannermodeChanged();
  }
  void setbuttontextcolor(const QColor &buttontextcolor) {
    _buttontextcolor = buttontextcolor;
    emit buttontextcolorChanged();
  }
  void setconfirmationbuttontextcolor(const QColor &confirmationbuttontextcolor) {
    _confirmationbuttontextcolor = confirmationbuttontextcolor;
    emit confirmationbuttontextcolorChanged();
  }
  void setmenuelementleftbordercolor(const QColor &menuelementleftbordercolor) {
    _menuelementleftbordercolor = menuelementleftbordercolor;
    emit menuelementleftbordercolorChanged();
  }
  void setmenuelementleftborderwidth(const qreal &menuelementleftborderwidth) {
    _menuelementleftborderwidth = menuelementleftborderwidth;
    emit menuelementleftborderwidthChanged();
  }
  void setpresentationlogo(const QString &presentationlogo) {
    _presentationlogo = presentationlogo;
    emit presentationlogoChanged();
  }
  void settablecolortitletext(const QColor &tablecolortitletext) {
    _tablecolortitletext = tablecolortitletext;
    emit tablecolortitletextChanged();
  }
  void setcalenderplaceholderdatescolor(const QColor &calenderplaceholderdatescolor) {
    _calenderplaceholderdatescolor = calenderplaceholderdatescolor;
    emit calenderplaceholderdatescolorChanged();
  }
  void setcalenderselecteddatecolor(const QColor &calenderselecteddatecolor) {
    _calenderselecteddatecolor = calenderselecteddatecolor;
    emit calenderselecteddatecolorChanged();
  }
  void setcalenderdatesofselectedmonthcolor(const QColor &calenderdatesofselectedmonthcolor) {
    _calenderdatesofselectedmonthcolor = calenderdatesofselectedmonthcolor;
    emit calenderdatesofselectedmonthcolorChanged();
  }
  void setcalenderbarofselectedmonthcolor(const QColor &calenderbarofselectedmonthcolor) {
    _calenderbarofselectedmonthcolor = calenderbarofselectedmonthcolor;
    emit calenderbarofselectedmonthcolorChanged();
  }
  void seticononbackgroundcolor(const QColor &icononbackgroundcolor) {
    _icononbackgroundcolor = icononbackgroundcolor;
    emit icononbackgroundcolorChanged();
  }
  void setcalenderdatebackgroundcolor(const QColor &calenderdatebackgroundcolor) {
    _calenderdatebackgroundcolor = calenderdatebackgroundcolor;
    emit calenderdatebackgroundcolorChanged();
  }
  void setcalenderselecteddatebackgroundcolor(const QColor &calenderselecteddatebackgroundcolor) {
    _calenderselecteddatebackgroundcolor = calenderselecteddatebackgroundcolor;
    emit calenderselecteddatebackgroundcolorChanged();
  }
  void setgrouptitlecolor(const QColor &grouptitlecolor) {
    _grouptitlecolor = grouptitlecolor;
    emit grouptitlecolorChanged();
  }
  void setcancelbuttongradient1(const QColor &cancelbuttongradient1) {
    _cancelbuttongradient1 = cancelbuttongradient1;
    emit cancelbuttongradient1Changed();
  }
  void setcancelbuttongradient2(const QColor &cancelbuttongradient2) {
    _cancelbuttongradient2 = cancelbuttongradient2;
    emit cancelbuttongradient2Changed();
  }
  void setclickcancelbuttongradient1(const QColor &clickcancelbuttongradient1) {
    _clickcancelbuttongradient1 = clickcancelbuttongradient1;
    emit clickcancelbuttongradient1Changed();
  }
  void setclickcancelbuttongradient2(const QColor &clickcancelbuttongradient2) {
    _clickcancelbuttongradient2 = clickcancelbuttongradient2;
    emit clickcancelbuttongradient2Changed();
  }
  void setcancelbuttonhovergradient1(const QColor &cancelbuttonhovergradient1) {
    _cancelbuttonhovergradient1 = cancelbuttonhovergradient1;
    emit cancelbuttonhovergradient1Changed();
  }
  void setcancelbuttonhovergradient2(const QColor &cancelbuttonhovergradient2) {
    _cancelbuttonhovergradient2 = cancelbuttonhovergradient2;
    emit cancelbuttonhovergradient2Changed();
  }
  void setcalendarweeknumbercolor(const QColor &calendarweeknumbercolor) {
    _calendarweeknumbercolor = calendarweeknumbercolor;
    emit calendarweeknumbercolorChanged();
  }
  void setradiocheckboxcolorselected(const QColor &radiocheckboxcolorselected) {
    _radiocheckboxcolorselected = radiocheckboxcolorselected;
    emit radiocheckboxcolorselectedChanged();
  }
  void setradiocontainerlabelboxcolor(const QColor &radiocontainerlabelboxcolor) {
    _radiocontainerlabelboxcolor = radiocontainerlabelboxcolor;
    emit radiocontainerlabelboxcolorChanged();
  }
  void setstandaloneiconcolor(const QColor &standaloneiconcolor) {
    _standaloneiconcolor = standaloneiconcolor;
    emit standaloneiconcolorChanged();
  }
  void setstandaloneiconcolorhighlight(const QColor &standaloneiconcolorhighlight) {
    _standaloneiconcolorhighlight = standaloneiconcolorhighlight;
    emit standaloneiconcolorhighlightChanged();
  }
  void seticonbackgroundhovercolor(const QColor &iconbackgroundhovercolor) {
    _iconbackgroundhovercolor = iconbackgroundhovercolor;
    emit iconbackgroundhovercolorChanged();
  }
  void setfilechooserdotscolor(const QColor &filechooserdotscolor) {
    _filechooserdotscolor = filechooserdotscolor;
    emit filechooserdotscolorChanged();
  }
  void setpopuptopbarcolor(const QColor &popuptopbarcolor) {
    _popuptopbarcolor = popuptopbarcolor;
    emit popuptopbarcolorChanged();
  }
  void setinputboxtextcolor(const QColor &inputboxtextcolor) {
    _inputboxtextcolor = inputboxtextcolor;
    emit inputboxtextcolorChanged();
  }
  void setinputboxhighlightedtextcolor(const QColor &inputboxhighlightedtextcolor) {
    _inputboxhighlightedtextcolor = inputboxhighlightedtextcolor;
    emit inputboxhighlightedtextcolorChanged();
  }
  void setinputboxselectedtextcolor(const QColor &inputboxselectedtextcolor) {
    _inputboxselectedtextcolor = inputboxselectedtextcolor;
    emit inputboxselectedtextcolorChanged();
  }
  void setinputboxtypedtextcolor(const QColor &inputboxtypedtextcolor) {
    _inputboxtypedtextcolor = inputboxtypedtextcolor;
    emit inputboxtypedtextcolorChanged();
  }
  void setinputboxsmalltextcolor(const QColor &inputboxsmalltextcolor) {
    _inputboxsmalltextcolor = inputboxsmalltextcolor;
    emit inputboxsmalltextcolorChanged();
  }
  void setthumbnailcontainertextcolor(const QColor &thumbnailcontainertextcolor) {
    _thumbnailcontainertextcolor = thumbnailcontainertextcolor;
    emit thumbnailcontainertextcolorChanged();
  }
  void setthumbnailcontainersmalltextcolor(const QColor &thumbnailcontainersmalltextcolor) {
    _thumbnailcontainersmalltextcolor = thumbnailcontainersmalltextcolor;
    emit thumbnailcontainersmalltextcolorChanged();
  }

  Q_INVOKABLE QColor returnRandomColor(float unused1) {
    float r = 0.0f, g = 0.0f, b = 0.0f, a = 0.0f;
    QColor color;
    /* Mix one, two or three colors */
    int colorstomix = (qrand() % 3) + 1;

    for (int j = 0; j < colorstomix; j++) {
      int maxquotenumber = 18;
      // qsrand(QDateTime::currentDateTime ().toTime_t ());
      int i = qrand() % (maxquotenumber) + 1;

      if (i == 1) {
        color = _tablecolortitle;
      } else if (i == 2) {
        color = _tablecolorline1;
      } else if (i == 3) {
        color = _tablecolorline2;
      } else if (i == 4) {
        color = _fastlinkingcolor;
      } else if (i == 5) {
        color = _intelliboxcolor;
      } else if (i == 6) {
        color = _menuboxcolor;
      } else if (i == 7) {
        color = _tabbedmenuboxcolor;
      } else if (i == 8) {
        color = _titlecolor;
      } else if (i == 9) {
        color = _popupcolor;
      } else if (i == 10) {
        color = _inactivefontcolor;
      } else if (i == 11) {
        color = _inactivetabcolor;
      } else if (i == 12) {
        color = _listbackgroundcolor;
      } else if (i == 13) {
        color = _tooltipcolor;
      } else if (i == 14) {
        color = _bordercolor;
      } else if (i == 15) {
        color = _warningcolor;
      } else if (i == 16) {
        color = _selectcolor;
      } else if (i == 17) {
        color = _lockedinputcolor;
      } else if (i == 18) {
        color = _inputboxbackground;
      }

      r += color.redF();
      g += color.greenF();
      b += color.blueF();
      a += color.alphaF();
    }
    return QColor::fromRgbF(r / colorstomix, g / colorstomix, b / colorstomix, a / colorstomix)
        .rgba();
  }

signals:
  void synnextlogoChanged();
  void backgroundChanged();
  void radiusChanged();
  void buttongradient1Changed();
  void buttongradient2Changed();
  void buttonopacityChanged();
  void clickbuttongradient1Changed();
  void clickbuttongradient2Changed();
  void clickbuttonopacityChanged();
  void tablecolortitleChanged();
  void tableopacitytitleChanged();
  void tablecolorline1Changed();
  void tableopacityline1Changed();
  void tablecolorline2Changed();
  void tableopacityline2Changed();
  void fastlinkingcolorChanged();
  void fastlinkingopacityChanged();
  void intelliboxcolorChanged();
  void intelliboxopacityChanged();
  void menuboxcolorChanged();
  void menuboxopacityChanged();
  void tabbedmenuboxcolorChanged();
  void tabbedmenuboxopacityChanged();
  void titlecolorChanged();
  void popupcolorChanged();
  void popupopacityChanged();
  void inactivefontcolorChanged();
  void inactivetabcolorChanged();
  void listbackgroundcolorChanged();
  void suggestbubbleimageChanged();
  void suggestbubbleopacityChanged();
  void tooltipcolorChanged();
  void bordersizeChanged();
  void bordercolorChanged();
  void usedfontChanged();
  void warningcolorChanged();
  void selectcolorChanged();
  void lockedinputcolorChanged();
  void titlefontsizeChanged();
  void textfontsizeChanged();
  void editBackgroundColorChanged();
  void activetabfontcolorChanged();
  void inputboxbackgroundChanged();
  // added
  void confirmationbuttongradient1Changed();
  void confirmationbuttongradient2Changed();
  void confirmationbuttonopacityChanged();
  void clickconfirmationbuttongradient1Changed();
  void clickconfirmationbuttongradient2Changed();
  void clickconfirmationbuttonopacityChanged();
  void exitbuttoncolorChanged();
  void exitbuttonhovercolorChanged();
  void tableselectentrycolorChanged();
  void switchcoloronactivatedChanged();
  void switchcolorondeactivatedChanged();
  void switchhandlecolorChanged();
  void switchboxradiusChanged();
  void switchhandleradiusChanged();
  void skinpreviewnamebaropacityChanged();
  void skinpreviewnamebarcolorChanged();
  void skinpreviewnamebarfontcolorChanged();
  void skinpreviewbackgroundselectionmarkcolorChanged();
  void skinpreviewbackgroundselectionmarkwidthChanged();
  void thumbnailcontainercolorChanged();
  void highlightingtextmouseoveropacityChanged();
  void highlightingtextmarginChanged();
  void highlightingtextbackgroundcolorChanged();
  void buttonhovergradient1Changed();
  void buttonhovergradient2Changed();
  void bannermodeiconrectanglebordercolorChanged();
  void bannermodeiconrectangleborderwidthChanged();
  void bannermodeiconrectanglecolorChanged();
  void bannermodeiconrectanglecolorhighlightChanged();
  void bannermodetextrectanglecolorhighlightChanged();
  void confirmationbuttonhovergradient1Changed();
  void confirmationbuttonhovergradient2Changed();
  void radiocheckboxcolorChanged();
  void bannermodetextalignmentChanged();
  void textcolorChanged();
  void textcolorhighlightChanged();
  void iconcolorChanged();
  void iconcolorhighlightChanged();
  void welcomeboxelementiconcolorChanged();
  void welcomeboxelementiconcolorbannermodeChanged();
  void buttontextcolorChanged();
  void confirmationbuttontextcolorChanged();
  void menuelementleftbordercolorChanged();
  void menuelementleftborderwidthChanged();
  void presentationlogoChanged();
  void tablecolortitletextChanged();
  void calenderplaceholderdatescolorChanged();
  void calenderselecteddatecolorChanged();
  void calenderdatesofselectedmonthcolorChanged();
  void calenderbarofselectedmonthcolorChanged();
  void icononbackgroundcolorChanged();
  void calenderdatebackgroundcolorChanged();
  void calenderselecteddatebackgroundcolorChanged();
  void grouptitlecolorChanged();
  void cancelbuttongradient1Changed();
  void cancelbuttongradient2Changed();
  void clickcancelbuttongradient1Changed();
  void clickcancelbuttongradient2Changed();
  void cancelbuttonhovergradient1Changed();
  void cancelbuttonhovergradient2Changed();
  void calendarweeknumbercolorChanged();
  void radiocheckboxcolorselectedChanged();
  void radiocontainerlabelboxcolorChanged();
  void standaloneiconcolorChanged();
  void standaloneiconcolorhighlightChanged();
  void iconbackgroundhovercolorChanged();
  void filechooserdotscolorChanged();
  void popuptopbarcolorChanged();
  void inputboxtextcolorChanged();
  void inputboxhighlightedtextcolorChanged();
  void inputboxselectedtextcolorChanged();
  void inputboxtypedtextcolorChanged();
  void inputboxsmalltextcolorChanged();
  void thumbnailcontainertextcolorChanged();
  void thumbnailcontainersmalltextcolorChanged();

 private:
  QString _synnextlogo;
  QString _background;
  int _radius;
  QColor _buttongradient1;
  QColor _buttongradient2;
  qreal _buttonopacity;
  QColor _clickbuttongradient1;
  QColor _clickbuttongradient2;
  qreal _clickbuttonopacity;
  QColor _tablecolortitle;
  qreal _tableopacitytitle;
  QColor _tablecolorline1;
  qreal _tableopacityline1;
  QColor _tablecolorline2;
  qreal _tableopacityline2;
  QColor _fastlinkingcolor;
  qreal _fastlinkingopacity;
  QColor _intelliboxcolor;
  qreal _intelliboxopacity;
  QColor _menuboxcolor;
  qreal _menuboxopacity;
  QColor _tabbedmenuboxcolor;
  qreal _tabbedmenuboxopacity;
  QColor _titlecolor;
  QColor _popupcolor;
  qreal _popupopacity;
  QColor _inactivefontcolor;
  QColor _inactivetabcolor;
  QColor _listbackgroundcolor;
  QString _suggestbubbleimage;
  qreal _suggestbubbleopacity;
  QColor _tooltipcolor;
  int _bordersize;
  QColor _bordercolor;
  QString _usedfont;
  QColor _warningcolor;
  QColor _selectcolor;
  QColor _lockedinputcolor;
  qreal _titlefontsize;
  qreal _textfontsize;
  qreal _titlefontsizebase;
  qreal _textfontsizebase;
  qreal _fontsizemultiplier;
  QColor _editBackgroundColor;
  QColor _activetabfontcolor;
  QColor _inputboxbackground;
  // added
  QColor _confirmationbuttongradient1;
  QColor _confirmationbuttongradient2;
  qreal _confirmationbuttonopacity;
  QColor _clickconfirmationbuttongradient1;
  QColor _clickconfirmationbuttongradient2;
  qreal _clickconfirmationbuttonopacity;
  QColor _exitbuttoncolor;
  QColor _exitbuttonhovercolor;
  QColor _tableselectentrycolor;
  QColor _switchcoloronactivated;
  QColor _switchcolorondeactivated;
  QColor _switchhandlecolor;
  qreal _switchboxradius;
  qreal _switchhandleradius;
  qreal _skinpreviewnamebaropacity;
  QColor _skinpreviewnamebarcolor;
  QColor _skinpreviewnamebarfontcolor;
  QColor _skinpreviewbackgroundselectionmarkcolor;
  qreal _skinpreviewbackgroundselectionmarkwidth;
  QColor _thumbnailcontainercolor;
  qreal _highlightingtextmouseoveropacity;
  qreal _highlightingtextmargin;
  QColor _highlightingtextbackgroundcolor;
  QColor _buttonhovergradient1;
  QColor _buttonhovergradient2;
  QColor _bannermodeiconrectanglebordercolor;
  qreal _bannermodeiconrectangleborderwidth;
  QColor _bannermodeiconrectanglecolor;
  QColor _bannermodeiconrectanglecolorhighlight;
  QColor _bannermodetextrectanglecolorhighlight;
  QColor _confirmationbuttonhovergradient1;
  QColor _confirmationbuttonhovergradient2;
  QColor _radiocheckboxcolor;
  qreal _bannermodetextalignment;
  QColor _textcolor;
  QColor _textcolorhighlight;
  QColor _iconcolor;
  QColor _iconcolorhighlight;
  QColor _welcomeboxelementiconcolor;
  QColor _welcomeboxelementiconcolorbannermode;
  QColor _buttontextcolor;
  QColor _confirmationbuttontextcolor;
  QColor _menuelementleftbordercolor;
  qreal _menuelementleftborderwidth;
  QString _presentationlogo;
  QColor _tablecolortitletext;
  QColor _calenderplaceholderdatescolor;
  QColor _calenderselecteddatecolor;
  QColor _calenderdatesofselectedmonthcolor;
  QColor _calenderbarofselectedmonthcolor;
  QColor _icononbackgroundcolor;
  QColor _calenderdatebackgroundcolor;
  QColor _calenderselecteddatebackgroundcolor;
  QColor _grouptitlecolor;
  QColor _cancelbuttongradient1;
  QColor _cancelbuttongradient2;
  QColor _clickcancelbuttongradient1;
  QColor _clickcancelbuttongradient2;
  QColor _cancelbuttonhovergradient1;
  QColor _cancelbuttonhovergradient2;
  QColor _calendarweeknumbercolor;
  QColor _radiocheckboxcolorselected;
  QColor _radiocontainerlabelboxcolor;
  QColor _standaloneiconcolor;
  QColor _standaloneiconcolorhighlight;
  QColor _iconbackgroundhovercolor;
  QColor _filechooserdotscolor;
  QColor _popuptopbarcolor;
  QColor _inputboxtextcolor;
  QColor _inputboxhighlightedtextcolor;
  QColor _inputboxselectedtextcolor;
  QColor _inputboxtypedtextcolor;
  QColor _inputboxsmalltextcolor;
  QColor _thumbnailcontainertextcolor;
  QColor _thumbnailcontainersmalltextcolor;

  QGuiApplication *app;
};

extern SkinProvider *g_Skins;

#endif  // SkinProvider_H
