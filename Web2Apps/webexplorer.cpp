#include "webexplorer.h"
#include <skinprovider.h>

#ifndef STANDALONE_VIEWER
WebExplorer::WebExplorer()
{

}
QWebElement WebExplorer::findDomElement(QVariantList pathToDom,
                                        QString url){

    QWebFrame * frame= g_webPageProvider->getPage(url);

    QWebElement document = frame->documentElement();
    QWebElement parentDocument;
    int ignoredElements=0;

    QString forcedBaseUrl="";

    /* Search if base href exists */
    QWebElementCollection baseHref=document.findAll("base");
    for(int i=0;i<baseHref.count();i++){
        if(!baseHref.at(i).attribute("href").isEmpty()){
            forcedBaseUrl=baseHref.at(i).attribute("href");
            qDebug() << "Forced base url!" << forcedBaseUrl;
        }
    }

    for(int i=0;i<pathToDom.size();i++){
        QVariantMap currentIndex=pathToDom[i].toMap();
        QString elementId=currentIndex["id"].toString();
        QString elementClass=currentIndex["className"].toString();
        QString elementNode=currentIndex["nodeName"].toString();
        int elementIndex=currentIndex["index"].toInt();

        QString cssSelector=elementNode;

        if(!elementId.isEmpty()){
            cssSelector+="#"+elementId;
        }

        if(!elementClass.isEmpty()){
            cssSelector+="[class=\""+elementClass+"\"]";
        }

        if(elementIndex>-1){
            cssSelector+=":nth-child("+QString::number(elementIndex+1)+")";
        }


        parentDocument=document;


        // TODO: Replace this with something more efficient (No css selector but C++ check)
        QWebElementCollection subEl=document.findAll(cssSelector);
        document=QWebElement();

        for(int i=0;i<subEl.count();i++){
            //Fucking CSS selector may find chils of childs of childs f childs acceptingthe fonction. restrict to direct childs (not possible with CSS)
            if(subEl.at(i).parent()==parentDocument){
                document=subEl.at(i);
                break;
            }
        }

        if(document.isNull()){
            //qDebug() << "Searching for " + cssSelector + " failed";
            qDebug() << "Ignoring class!";

            // If we do not find element, first try to remove the child position (most probably element which changed)
            // TODO: Maybe analyse

            cssSelector=elementNode;

            if(!elementId.isEmpty()){
                cssSelector+="#"+elementId;
            }
            if(elementIndex>-1){
                cssSelector+=":nth-child("+QString::number(elementIndex+1)+")";
            }

            document=parentDocument.findFirst(cssSelector);




            if(document.isNull()){
                //qDebug() << "Searching for " + cssSelector + " failed";
                qDebug() << "Ignoring position!";
                /* Classes may vary dynamically due to fucking javascript...*/

                QString cssSelector=elementNode;
                if(!elementId.isEmpty()){
                    cssSelector+="#"+elementId;
                }
                if(!elementClass.isEmpty()){
                    cssSelector+="[class=\""+elementClass+"\"]";
                }


                document=parentDocument.findFirst(cssSelector);


                if(document.isNull()){
                    //qDebug() << "Searching for " + cssSelector + " failed";
                    qDebug() << "Ignoring classes AND position!";
                    /* Classes may vary dynamically due to fucking javascript...*/

                    QString cssSelector=elementNode;
                    if(!elementId.isEmpty()){
                        cssSelector+="#"+elementId;
                    }

                    document=parentDocument.findFirst(cssSelector);


                    if(document.isNull()){
                        qDebug() << "Search for more simple element failed.";
                        ignoredElements++;
                        document=parentDocument;
                        QWebElementCollection allEl=parentDocument.findAll("*");
                        qDebug() << "Found " + QString::number(allEl.count()) + "subelements";
                        for(int j=0;j<allEl.count();j++){
                            qDebug()<< "Element " + QString::number(j) + ": " +allEl.at(j).tagName()
                                       + " classes: "<< allEl.at(j).classes() << "attributes available: "
                                    << allEl.at(j).attributeNames() <<" id: "<< allEl.at(j).attribute("id") +
                                       + " HTML content: " + QString::number(allEl.at(j).toInnerXml().length());

                        }
                        qDebug() << "Send back parent and abort!";
                        break;
                    }
                }
            }
        } else {
            // qDebug() << "Searching for " + cssSelector + " succeeded: (tag:" + document.tagName() +" id:"+document.attribute("id")+ " classes:"+document.classes().join(";")+" style:"+document.attribute("style")+")";
        }
    }

    if(forcedBaseUrl!=""){
        url=forcedBaseUrl;
    }
    return document;


    /* Find all forms
    QWebElementCollection tables = document.findAll("form");
    int numTables = tables.count();
    for(int i=0;i<numTables;i++){

    }
    */

    /* Find all blocks
    tables = document.findAll("div");
    numTables = tables.count();
    for(int i=0;i<numTables;i++){

    } */

}
QVariantMap WebExplorer::getItemFromUrl(QVariantList pathToDom,
                                        QString url){
    return convertWebElementToItem(
                findDomElement(pathToDom,url),url);
}


QVariantMap WebExplorer::convertWebElementToItem(QWebElement element,QString url){
    QVariantMap itemInPage;

    QString tagName=element.tagName().toLower();

    /* Found form, analyse environement */
    if(tagName=="form"){
        QWebElementCollection inputs=element.findAll("input");

        QVariantList elementsOfForm;
        QVariantMap value;
        value["type"]="form";
        value["action"]=element.attribute("action");
        value["method"]=element.attribute("method");
        for(int j=0;j<inputs.count();j++){
            QVariantMap subitemInPage;
            subitemInPage["type"]=inputs.at(j).attribute("type");
            subitemInPage["name"]=inputs.at(j).attribute("name");
            subitemInPage["content"]=inputs.at(j).attribute("content");
            elementsOfForm<<subitemInPage;
        }
        value["elements"]=elementsOfForm;
        itemInPage["content"]=value; // other value

    }

    /* Found link, insert button */
    else if(tagName=="a"){
        /* Link! Create Button for it */
        QVariantMap value;
        value["type"]="button";
        value["baseUrl"]=url;
        value["html"]=element.toInnerXml();
        value["linkToUrl"]=element.attribute("href");
        itemInPage["content"]=value;
    }

    /* Found image, insert it, optionally with link */
    else if(tagName=="img"){
        qDebug() << "Imageeeee!!!!";
        QVariantMap value;

        if(element.attribute("src").startsWith("/")){
            QString myurl=url;
            int pos=myurl.indexOf("/",9);
            myurl=myurl.left(pos);
            value["html"]=myurl + element.attribute("src");
        } else {
            if(element.attribute("src").startsWith("http")){

                value["html"]=element.attribute("src");
            } else {
                QString myurl;
                int lastSlash=url.lastIndexOf("/");
                if(lastSlash>9){
                    myurl=url.mid(0,lastSlash+1);
                } else {
                    myurl=url+"/";
                }
                value["html"]=myurl+ element.attribute("src");
            }
        }
        if(element.parent().tagName().toLower()=="a"){
            qDebug() << "Parent of image is a link";
            value["linkToUrl"]=element.parent().attribute("href");
            qDebug() << value["linkToUrl"];
        }
        value["type"]="image";
        value["baseUrl"]=url;
        itemInPage["content"]=value;

        qDebug() << value;
    }

    /* Found something else, insert richtext */
    else {
        QVariantMap value;
        value["html"]="<style type=\"text/css\">\
                h1 {font-size: large; }\
                A { text-align: center;  color: "+g_Skins->buttontextcolor().name()+"; }\
                A:link {background: " + g_Skins->buttongradient1().name() + "; text-decoration: none}\
                A:visited {background: " + g_Skins->buttongradient1().name() + "; text-decoration: none}\
                A:active {background: " + g_Skins->buttongradient1().name() + "; text-decoration: none}\
                </style>" + element.toOuterXml();
                value["baseUrl"]=url;
        value["type"]="block";
        itemInPage["content"]=value;
    }

     return itemInPage;
}

#endif
