Qt.include("OriginalGreen/OriginalGreen.js")
Qt.include("LeanRose/LeanRose.js")
Qt.include("FlowerPower/FlowerPower.js")
Qt.include("BlueBuilding/BlueBuilding.js")
Qt.include("ModernGrey/ModernGrey.js")
Qt.include("BlackAndWhite/BlackAndWhite.js")
Qt.include("Universe/Universe.js")


function addSkins(model){
    model.append(OriginalGreen);
    model.append(BlueBuilding);
    model.append(LeanRose);
	model.append(FlowerPower);
    model.append(ModernGrey);
    model.append(BlackAndWhite);
    model.append(Universe)
}

function loadSkin(name){
    var selectedSkin;
    if(name === "OriginalGreen"){
        selectedSkin=OriginalGreen;
    } else if(name === "LeanRose"){
        selectedSkin=LeanRose;
    } else if(name === "BlueBuilding"){
        selectedSkin=BlueBuilding;
    } else if(name === "ModernGrey"){
        selectedSkin=ModernGrey;
    } else if(name === "FlowerPower"){
        selectedSkin=FlowerPower;		
    } else if(name === "BlackAndWhite"){
        selectedSkin=BlackAndWhite;
    } else if(name === "Universe"){
        selectedSkin=Universe;
    }else {
        selectedSkin=ModernGrey;         // Default Skin
    }

    skin.synnextlogo         =      selectedSkin.m_synnextlogo;
    skin.background          =      selectedSkin.m_background;
    skin.radius       =      selectedSkin.m_radius;
    skin.buttongradient1     =      selectedSkin.m_buttongradient1;
    skin.buttongradient2     =      selectedSkin.m_buttongradient2;
    skin.buttonopacity       =      selectedSkin.m_buttonopacity;
    skin.clickbuttongradient1=      selectedSkin.m_clickbuttongradient1;
    skin.clickbuttongradient2=      selectedSkin.m_clickbuttongradient2;
    skin.clickbuttonopacity  =      selectedSkin.m_clickbuttonopacity;
    skin.tablecolortitle     =      selectedSkin.m_tablecolortitle;
    skin.tableopacitytitle   =      selectedSkin.m_tableopacitytitle;
    skin.tablecolorline1     =      selectedSkin.m_tablecolorline1;
    skin.tableopacityline1   =      selectedSkin.m_tableopacityline1;
    skin.tablecolorline2     =      selectedSkin.m_tablecolorline2;
    skin.tableopacityline2   =      selectedSkin.m_tableopacityline2;
    skin.fastlinkingcolor    =      selectedSkin.m_fastlinkingcolor;
    skin.fastlinkingopacity  =      selectedSkin.m_fastlinkingopacity;
    skin.intelliboxcolor     =      selectedSkin.m_intelliboxcolor;
    skin.intelliboxopacity   =      selectedSkin.m_intelliboxopacity;
    skin.menuboxcolor        =      selectedSkin.m_menuboxcolor;
    skin.menuboxopacity      =      selectedSkin.m_menuboxopacity;
    skin.tabbedmenuboxcolor  =      selectedSkin.m_tabbedmenuboxcolor
    skin.tabbedmenuboxopacity=      selectedSkin.m_tabbedmenuboxopacity;
    skin.titlecolor          =      selectedSkin.m_titlecolor;
    skin.popupcolor          =      selectedSkin.m_popupcolor;
    skin.popupopacity        =      selectedSkin.m_popupopacity;
    skin.inactivetabcolor    =      selectedSkin.m_inactivetabcolor;
    skin.inactivefontcolor   =      selectedSkin.m_inactivefontcolor;
    skin.listbackgroundcolor =      selectedSkin.m_listbackgroundcolor;
    skin.suggestbubbleimage  =      selectedSkin.m_suggestbubbleimage;
    skin.suggestbubbleopacity=      selectedSkin.m_suggestbubbleopacity;
    skin.bordersize          =      selectedSkin.m_bordersize;
    skin.bordercolor         =      selectedSkin.m_bordercolor;
    skin.usedfont            =      selectedSkin.m_usedfont;
    skin.warningcolor        =      selectedSkin.m_warningcolor;
    skin.selectcolor         =      selectedSkin.m_selectcolor;
    skin.lockedinputcolor    =      selectedSkin.m_lockedinputcolor;
    skin.textfontsize        =      selectedSkin.m_textfontsize;
    skin.titlefontsize       =      selectedSkin.m_titlefontsize;
    skin.editBackgroundColor =      selectedSkin.m_editBackgroundColor;
    skin.activetabfontcolor  =      selectedSkin.m_activetabfontcolor;
    skin.inputboxbackground  =      selectedSkin.m_inputboxbackground;
//    skin.inputboxgrey
    //added
    skin.confirmationbuttongradient1                =       selectedSkin.m_confirmationbuttongradient2;
    skin.confirmationbuttongradient2                =       selectedSkin.m_confirmationbuttongradient2;
    skin.confirmationbuttonopacity                  =       selectedSkin.m_confirmationbuttonopacity;
    skin.clickconfirmationbuttongradient1           =       selectedSkin.m_clickconfirmationbuttongradient1;
    skin.clickconfirmationbuttongradient2           =       selectedSkin.m_clickconfirmationbuttongradient2;
    skin.clickconfirmationbuttonopacity             =       selectedSkin.m_clickconfirmationbuttonopacity;
    skin.exitbuttoncolor                            =       selectedSkin.m_exitbuttoncolor;
    skin.exitbuttonhovercolor                       =       selectedSkin.m_exitbuttonhovercolor;
    skin.tableselectentrycolor                      =       selectedSkin.m_tableselectentrycolor;
    skin.switchcoloronactivated                     =       selectedSkin.m_switchcoloronactivated;
    skin.switchcolorondeactivated                   =       selectedSkin.m_switchcolorondeactivated;
    skin.switchhandlecolor                          =       selectedSkin.m_switchhandlecolor;
    skin.switchboxradius                            =       selectedSkin.m_switchboxradius;
    skin.switchhandleradius                         =       selectedSkin.m_switchhandleradius;
    skin.skinpreviewnamebaropacity                  =       selectedSkin.m_skinpreviewnamebaropacity;
    skin.skinpreviewnamebarcolor                    =       selectedSkin.m_skinpreviewnamebarcolor;
    skin.skinpreviewnamebarfontcolor                =       selectedSkin.m_skinpreviewnamebarfontcolor;
    skin.skinpreviewbackgroundselectionmarkcolor    =       selectedSkin.m_skinpreviewbackgroundselectionmarkcolor;
    skin.skinpreviewbackgroundselectionmarkwidth    =       selectedSkin.m_skinpreviewbackgroundselectionmarkwidth;
    skin.thumbnailcontainercolor                     =       selectedSkin.m_thumbnailcontainercolor;
    skin.highlightingtextmouseoveropacity           =       selectedSkin.m_highlightingtextmouseoveropacity;
    skin.highlightingtextmargin                     =       selectedSkin.m_highlightingtextmargin;
    skin.highlightingtextbackgroundcolor        =       selectedSkin.m_highlightingtextbackgroundcolor;
    skin.buttonhovergradient1                       =       selectedSkin.m_buttonhovergradient1;
    skin.buttonhovergradient2                       =       selectedSkin.m_buttonhovergradient2;
    skin.bannermodeiconrectanglebordercolor         =       selectedSkin.m_bannermodeiconrectanglebordercolor;
    skin.bannermodeiconrectangleborderwidth         =       selectedSkin.m_bannermodeiconrectangleborderwidth;
    skin.bannermodeiconrectanglecolor               =       selectedSkin.m_bannermodeiconrectanglecolor;
    skin.bannermodeiconrectanglecolorhighlight      =       selectedSkin.m_bannermodeiconrectanglecolorhighlight;
    skin.bannermodetextrectanglecolorhighlight      =       selectedSkin.m_bannermodetextrectanglecolorhighlight;
    skin.confirmationbuttonhovergradient1           =       selectedSkin.m_confirmationbuttonhovergradient1;
    skin.confirmationbuttonhovergradient2           =       selectedSkin.m_confirmationbuttonhovergradient2;
    skin.radiocheckboxcolor                         =       selectedSkin.m_radiocheckboxcolor;
    skin.bannermodetextalignment                    =       selectedSkin.m_bannermodetextalignment;
    skin.textcolor                                  =       selectedSkin.m_textcolor;
    skin.textcolorhighlight                         =       selectedSkin.m_textcolorhighlight;
    skin.iconcolor                                  =       selectedSkin.m_iconcolor;
    skin.iconcolorhighlight                         =       selectedSkin.m_iconcolorhighlight;
    skin.welcomeboxelementiconcolor                 =       selectedSkin.m_welcomeboxelementiconcolor;
    skin.welcomeboxelementiconcolorbannermode       =       selectedSkin.m_welcomeboxelementiconcolorbannermode;
    skin.buttontextcolor                            =       selectedSkin.m_buttontextcolor;
    skin.confirmationbuttontextcolor                =       selectedSkin.m_confirmationbuttontextcolor;
    skin.menuelementleftbordercolor                 =       selectedSkin.m_menuelementleftbordercolor;
    skin.menuelementleftborderwidth                 =       selectedSkin.m_menuelementleftborderwidth;
    skin.presentationlogo                           =       selectedSkin.m_presentationlogo;
    skin.tablecolortitletext                        =       selectedSkin.m_tablecolortitletext;
    skin.calenderplaceholderdatescolor              =       selectedSkin.m_calenderplaceholderdatescolor;
    skin.calenderselecteddatecolor                  =       selectedSkin.m_calenderselecteddatecolor;
    skin.calenderdatesofselectedmonthcolor          =       selectedSkin.m_calenderdatesofselectedmonthcolor;
    skin.calenderbarofselectedmonthcolor            =       selectedSkin.m_calenderbarofselectedmonthcolor;
    skin.icononbackgroundcolor                      =       selectedSkin.m_icononbackgroundcolor;
    skin.calenderdatebackgroundcolor                =       selectedSkin.m_calenderdatebackgroundcolor;
    skin.calenderselecteddatebackgroundcolor        =       selectedSkin.m_calenderselecteddatebackgroundcolor;
    skin.grouptitlecolor                            =       selectedSkin.m_grouptitlecolor;
    skin.calendarcolor                              =       selectedSkin.m_calendarcolor;
    skin.calendaropacity                            =       selectedSkin.m_calendaropacity;
    skin.calendarbordersize                         =       selectedSkin.m_calendarbordersize;
    skin.calendarbordercolor                        =       selectedSkin.m_calendarbordercolor;
    skin.cancelbuttongradient1                      =       selectedSkin.m_cancelbuttongradient1;
    skin.cancelbuttongradient2                      =       selectedSkin.m_cancelbuttongradient2;
    skin.clickcancelbuttongradient1                 =       selectedSkin.m_clickcancelbuttongradient1;
    skin.clickcancelbuttongradient2                 =       selectedSkin.m_clickcancelbuttongradient2;
    skin.cancelbuttonhovergradient1                 =       selectedSkin.m_cancelbuttonhovergradient1;
    skin.cancelbuttonhovergradient2                 =       selectedSkin.m_cancelbuttonhovergradient2;
    skin.calendarweeknumbercolor                    =       selectedSkin.m_calendarweeknumbercolor;
    skin.radiocheckboxcolorselected                 =       selectedSkin.m_radiocheckboxcolorselected;
    skin.radiocontainerlabelboxcolor                =       selectedSkin.m_radiocontainerlabelboxcolor;
    skin.standaloneiconcolor                        =       selectedSkin.m_standaloneiconcolor;
    skin.standaloneiconcolorhighlight               =       selectedSkin.m_standaloneiconcolorhighlight;
    skin.iconbackgroundhovercolor                   =       selectedSkin.m_iconbackgroundhovercolor;
    skin.filechooserdotscolor                       =       selectedSkin.m_filechooserdotscolor;
    skin.popuptopbarcolor                           =       selectedSkin.m_popuptopbarcolor;
    skin.inputboxtextcolor                          =       selectedSkin.m_inputboxtextcolor;
    skin.inputboxhighlightedtextcolor               =       selectedSkin.m_inputboxhighlightedtextcolor;
    skin.inputboxselectedtextcolor                  =       selectedSkin.m_inputboxselectedtextcolor;
    skin.inputboxtypedtextcolor                     =       selectedSkin.m_inputboxtypedtextcolor;
    skin.inputboxsmalltextcolor                     =       selectedSkin.m_inputboxsmalltextcolor;
    skin.thumbnailcontainertextcolor                =       selectedSkin.m_thumbnailcontainertextcolor;
    skin.thumbnailcontainersmalltextcolor           =       selectedSkin.m_thumbnailcontainersmalltextcolor;
    skin.linkcolor                                  =       selectedSkin.m_linkcolor;
}
