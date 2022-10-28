import QtQuick 2.4
import MyDocument 1.0
Item{
    property alias mydoc: document
    DocumentHandler {
        id: document
        target: textEditor
        cursorPosition: textEditor.cursorPosition
        selectionStart: textEditor.selectionStart
        selectionEnd: textEditor.selectionEnd
        //textColor: "black" //colorDialog.color
        //Component.onCompleted: document.fileUrl = "qrc:/example.html"
//        onFontSizeChanged: {
//            fontSizeSpinBox.valueGuard = false
//            fontSizeSpinBox.value = document.fontSize
//            fontSizeSpinBox.valueGuard = true
//        }
//        onFontFamilyChanged: {
//            var index = Qt.fontFamilies().indexOf(document.fontFamily)
//            if (index == -1) {
//                fontFamilyComboBox.currentIndex = 0
//                fontFamilyComboBox.special = true
//            } else {
//                fontFamilyComboBox.currentIndex = index
//                fontFamilyComboBox.special = false
//            }
//        }
        onError: {
            errorDialog.text = message
            errorDialog.visible = true
        }
    }


    Row{
        id:buttonRow
        anchors.fill: parent
        anchors.margins: s.r5


        //            ComboBox {
        //                id: fontFamilyComboBox
        //                implicitWidth: 200
        //                model: Qt.fontFamilies()
        //                property bool special : false
        //                onActivated: {
        //                    if (special == false || index != 0) {
        //                        document.fontFamily = textAt(index)
        //                    }
        //                }
        //            }
        //            SpinBox {
        //                id: fontSizeSpinBox
        //                activeFocusOnPress: false
        //                implicitWidth: 70
        //                value: 0
        //                anchors.margins: 20
        //                property bool valueGuard: true
        //                onValueChanged: if (valueGuard) document.fontSize = value
        //            }


//        IconHolderButton {
//            id: cutIconHolderButton
//            text: "Cut"
//            //shortcut: "ctrl+x"
//            iconSource: "qrc:/images/html-images/editcut.svg"

//            //iconName: "edit-cut"
//            onClicked: textEditor.cut()
//        }

//        IconHolderButton {
//            id: copyIconHolderButton
//            text: "Copy"
//            //shortcut: "Ctrl+C"
//            iconSource: "qrc:/images/html-images/editcopy.svg"
//            //iconName: "edit-copy"
//            onClicked: textEditor.copy()
//        }

//        IconHolderButton {
//            id: pasteIconHolderButton
//            text: "Paste"
//            //shortcut: "ctrl+v"
//            iconSource: "qrc:/images/html-images/editpaste.svg"
//            //iconName: "edit-paste"
//            onClicked: textEditor.paste()
//        }

        IconHolderButton {
            id: alignLeftIconHolderButton
            text: "&Left"
            iconSource: "qrc:/images/html-images/textleft.svg"
            //iconName: "format-justify-left"
            //shortcut: "ctrl+l"
            onClicked: document.alignment = Qt.AlignLeft
            //checkable: true
            checked: document.alignment == Qt.AlignLeft
        }
        IconHolderButton {
            id: alignCenterIconHolderButton
            text: "C&enter"
            iconSource: "qrc:/images/html-images/textcenter.svg"
            //iconName: "format-justify-center"
            onClicked: document.alignment = Qt.AlignHCenter
            //checkable: true
            checked: document.alignment == Qt.AlignHCenter
        }
        IconHolderButton {
            id: alignRightIconHolderButton
            text: "&Right"
            iconSource: "qrc:/images/html-images/textright.svg"
            //iconName: "format-justify-right"
            onClicked: document.alignment = Qt.AlignRight
            //checkable: true
            checked: document.alignment == Qt.AlignRight
        }
        IconHolderButton {
            id: alignJustifyIconHolderButton
            text: "&Justify"
            iconSource: "qrc:/images/html-images/textjustify.svg"
            //iconName: "format-justify-fill"
            onClicked: document.alignment = Qt.AlignJustify
            //checkable: true
            checked: document.alignment == Qt.AlignJustify
        }

        IconHolderButton {
            id: boldIconHolderButton
            text: "&Bold"
            iconSource: "qrc:/images/html-images/textbold.svg"
            //iconName: "format-text-bold"
            onClicked: document.bold = !document.bold
            //checkable: true
            checked: document.bold
        }

        IconHolderButton {
            id: italicIconHolderButton
            text: "&Italic"
            iconSource: "qrc:/images/html-images/textitalic.svg"
            //iconName: "format-text-italic"
            onClicked: document.italic = !document.italic
            //checkable: true
            checked: document.italic
        }
        IconHolderButton {
            id: underlineIconHolderButton
            text: "&Underline"
            iconSource: "qrc:/images/html-images/textunder.svg"
            //iconName: "format-text-underline"
            onClicked: document.underline = !document.underline
            //checkable: true
            checked: document.underline
        }

        IconHolderButton{
            text: "Save and close"
            iconSource: "qrc:/images/html-images/filesave.svg"
            onClicked: textEditor.focus=false
        }


        /* FileDialog {
    id: fileDialog
    nameFilters: ["Text files (*.txt)", "HTML files (*.html, *.htm)"]
    onAccepted: {
        if (fileDialog.selectExisting)
            document.fileUrl = fileUrl
        else
            document.saveAs(fileUrl, selectedNameFilter)
    }
}
FileDialog {
    id: imageDialog
    nameFilters: ["Image files (*.jpg *.jpeg *.svg *.gif)","All files (*)"]
    onAccepted: {

        document.image = [ fileUrl, selectedNameFilter ]

    }
}

ColorDialog {
    id: colorDialog
    color: "black"
}*/

//        IconHolderButton {
//            id: fileOpenIconHolderButton
//            iconSource: "qrc:/images/html-images/fileopen.svg"
//            //iconName: "document-open"
//            text: "Open"
//            onClicked: {
//                fileDialog.selectExisting = true
//                fileDialog.open()
//            }
//        }

//        IconHolderButton {
//            id: fileSaveAsIconHolderButton
//            iconSource: "qrc:/images/html-images/filesave.svg"
//            //iconName: "document-save"
//            text: "Save As…"
//            onClicked: {
//                fileDialog.selectExisting = false
//                fileDialog.open()
//            }
//        }

//        IconHolderButton {
//            id: insertTableIconHolderButton
//            text: "&Table"
//            iconSource: "qrc:/images/html-images/table.svg"
//            //iconName: "insert-table"
//            onClicked: spinboxDialog.open()

//            //checked: document.table
//        }
//        IconHolderButton {
//            id: insertImageIconHolderButton
//            text: "&Image"
//            iconSource: "qrc:/images/html-images/image.svg"
//            //iconName: "insert-image"
//            onClicked: {
//                imageDialog.selectExisting = true
//                imageDialog.open()
//            }
//            //checkable: true
//        }
//        IconHolderButton {
//            id: viewSourceIconHolderButton
//            text: "S&ource"
//            iconSource: "qrc:/images/html-images/source.svg"
//            //iconName: "view-source"
//            onClicked: {
//                document.perform("viewSource","no parameter")
//            }
//            //checkable: true
//        }
    }
}
