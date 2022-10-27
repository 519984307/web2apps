import QtQuick 2.0
import QtQuick.Dialogs 1.2

Item{
    FileDialog {
        id: fileDialog
        title: "Please choose a file"
        // folder: shortcuts.home
        onAccepted: {
            imageitem.source=fileDialog.fileUrl
            domParser.updateElementContent(indexOffset,
                                         "html",
                                         fileDialog.fileUrl)
            console.log("You chose: " + fileDialog.fileUrls)
        }
        onRejected: {
            console.log("Canceled")
        }
        Component.onCompleted: visible = true
    }
}

