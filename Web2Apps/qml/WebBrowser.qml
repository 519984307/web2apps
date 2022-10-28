import QtQuick 2.5
import QtWebEngine 1.1

import QtQuick.Controls 1.4

Rectangle {
    property var model
    property bool editable:true
    property bool storeToApp:true
    property int storeToPage:0
    color:"white"


    property alias web:webview
    property alias url:webview.url
    // Check this
    // https://github.com/liri-project/liri-browser/blob/master/src/qml/BrowserWebView.qml
    WebEngineProfile {
        id:myprofile
        httpUserAgent:"Mozilla/5.0 (Linux; U; Android 4.1.1; en-gb; Build/KLP) AppleWebKit/534.30 (KHTML, like Gecko) Version/4.0 Safari/534.30"

    }
/*WebEngineCertificateError{
    id:mycert
    overridable: true
}*/

    onStoreToAppChanged: {
        if(storeToApp==false){
            webview.runJavaScript("activateScript=false;")
        } else {
            webview.runJavaScript("activateScript=true;")
        }
    }

    WebEngineView {
        id: webview
        onJavaScriptConsoleMessage: {
            console.log(message)
        }


        onCertificateError: {
            console.log("meeeeeeeeeeeeeeeeeeh")
            error.ignoreCertificateError()
        }
        // url: "http://www.stuttgart.de/veranstaltungen/stadtleben"

        // Javascript created elements in head which where not send in the DOM path
        // url: "http://www.bookatable.de/107961/cube-stuttgart"

        // CLick does not send data! (cause: https!!)
        // https://www.tripadvisor.de/Restaurant_Review-g187291-d1087012-Reviews-Cube-Stuttgart_Baden_Wurttemberg.html

        // Original url (Changed website... Only PDFs now... )
        // http://www.vaihinger-drive.de/

        // Post form redirects to GET... WTF seriously...
        // url: "http://www.elefanten-lb.de/"

        // Mittagsmenu dynamically changed using javascript. Note: If selection on first click, this works perfectly! Why?!?
        // url: "http://besitos.de/stuttgart"

        // Fucked up with a lot of javascript everywhere
        // url: "http://www.bookatable.de/107961/cube-stuttgart"

        // Images are inserted, links ignored (Check if external link is available when inserting element)
        // url: "http://www.restaurant-wartberg.de/"

        profile:myprofile
        //certificateError: mycert

        anchors.fill: parent
        anchors.margins: 1
        property int javascriptrun : 0
        onUrlChanged: javascriptrun=0

        onLoadProgressChanged: {
            console.log("loadprogress:" + loadProgress);
            if (loadProgress==100){
                if(javascriptrun==0){
                    javascriptrun=1;
                    console.log("Starting javascript!");


                    runJavaScript("
var activateScript=true;

Web2App = {};

(function(web2app) {
    web2app.DOMInspector = {
        init: init
    };

    return;

    function setSelectorCss(selector) {
        selector.style.background = 'green';
        selector.style.position = 'fixed';
        selector.style.transition = 'all 300ms ease';
        selector.style.zIndex = '99999';
    }

    function setSelectorCssX(selector) {
        setSelectorCss(selector);
        selector.style.width = '2px';
    }
    function setSelectorCssY(selector) {
        setSelectorCss(selector);
        selector.style.height = '2px';
    }

    function init(doc) {
        var elementContainer = document.createElement('div');
        var topElement = document.createElement('div');
        var leftElement = document.createElement('div');
        var rightElement = document.createElement('div');
        var bottomElement = document.createElement('div');
        topElement.id = 'selector-top';
        leftElement.id = 'selector-left';
        rightElement.id = 'selector-right';
        bottomElement.id = 'selector-bottom';

        setSelectorCssX(leftElement);
        setSelectorCssX(rightElement);
        setSelectorCssY(topElement);
        setSelectorCssY(bottomElement);

        elementContainer.appendChild(topElement);
        elementContainer.appendChild(leftElement);
        elementContainer.appendChild(rightElement);
        elementContainer.appendChild(bottomElement);
        doc.body.appendChild(elementContainer);

        var elements = {
            top: doc.getElementById('selector-top'),
            left: doc.getElementById('selector-left'),
            right: doc.getElementById('selector-right'),
            bottom: doc.getElementById('selector-bottom')
        };

        doc.onmousemove = function(event) {

                if(event.target.id.indexOf('selector') !== -1 || event.target.tagName === 'BODY' || event.target.tagName === 'HTML') return;

                targetOffset = event.target.getBoundingClientRect(),
                    targetHeight = targetOffset.height,
                    targetWidth  = targetOffset.width;

                elements.top.style.left = (targetOffset.left - 4) + 'px';
                elements.top.style.top = (targetOffset.top - 4) + 'px';
                elements.top.style.width = (targetWidth + 5) + 'px';

                elements.bottom.style.top = (targetOffset.top + targetHeight + 1) + 'px';
                elements.bottom.style.left = (targetOffset.left  - 3) + 'px';
                elements.bottom.style.width = (targetWidth + 4) + 'px';

                elements.left.style.left = (targetOffset.left  - 5) + 'px';
                elements.left.style.top = (targetOffset.top  - 4) + 'px';
                elements.left.style.height = (targetHeight + 8) + 'px';

                elements.right.style.left = (targetOffset.left + targetWidth + 1) + 'px';
                elements.right.style.top = (targetOffset.top  - 4) + 'px';
                elements.right.style.height = (targetHeight + 8) + 'px';

                event.target.onclick = function(event) {
if(activateScript){
                    event.preventDefault();
                    event.stopPropagation();
                    publishSelectedElementPath(window.location.href, event.path);
}
                };

        };
    }
    function getElemIndex(elm)
    {
        var nodes = elm.parentNode.childNodes, node;
        var i = count = 0;
        while ((node=nodes.item(i++)) && node != elm) {
            count++;
            // ignore the virtual Text nodes for non-well formed HTML #text
            // ignoring comments as well (DOm element unknown but starting with #)
            if (node.nodeName.substring(0, 1) === '#') {
                count--;
            }
        }
        return count;
    }

    function publishSelectedElementPath(pageURL, elemPath) {
        // transform element path parts to easier format for server to consume
        // start with highest path part which should be 'Window' and traverse to current element down
        var contentDescriptor = {
            url: pageURL,
            path: []
        };
        // start when 'body' element is found in path list
        var startAppending = false;
        for (var pathIndex = elemPath.length - 1; pathIndex >= 0; pathIndex--) {
            var currentPath = elemPath[pathIndex];
            if (currentPath.nodeName === 'BODY') {
                startAppending = true;
            }
            if (startAppending) {
                contentDescriptor.path.push({
                    id: currentPath.id,
                    className: currentPath.className,
                    nodeName: currentPath.nodeName,
                    index: getElemIndex(currentPath)
                });
            }
        }

        var xmlhttp = new XMLHttpRequest();
        xmlhttp.onreadystatechange = function() {
            if (xmlhttp.readyState == XMLHttpRequest.DONE ) {
               if(xmlhttp.status == 200){
                   // window.alert('Successfully selected item');
               }
               else if(xmlhttp.status == 400) {
                    //window.alert('There was an error 400');
               }
               else {
                    //window.alert('something else other than 200 was returned:' + xmlhttp.status);
               }
            }
        }

        xmlhttp.open('POST', 'http://localhost:8080/', true);
        xmlhttp.send(JSON.stringify(contentDescriptor));

    }
})(Web2App);
Web2App.DOMInspector.init(document);
                ", function(result) { console.log(result)});
                    if(storeToApp==false){
                        webview.runJavaScript("activateScript=false;")
                    } else {
                        webview.runJavaScript("activateScript=true;")
                    }
                }
            }

        }

    }
}
