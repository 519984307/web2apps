import QtQuick 2.0
import "BasicElements"
AutoElement{
    id:thisae

    InputTextMultilineBox{
        y:thisae.wantedMargin
        width:repeaterList.width
        textloaded:valueOfItem["html"]?valueOfItem["html"]:""
        onAccepted: {
            var txt = text;
            var value = richtText(txt)?cleanHtml(txt): plainText();
            console.log(value);
            domParser.updateElementContent(index,
                                           "html",
                                           value)
        }
        function richtText(html) {
            if (html.indexOf("<html") > -1 ) {
                return true;
            }
            return false;
        }
        function cleanHtml(html) {
            html = html.replace("<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\np, li { white-space: pre-wrap; }\n</style></head>","<html>")
            return html;
        }
    }
}
