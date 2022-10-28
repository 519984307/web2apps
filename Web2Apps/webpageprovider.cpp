#include "webpageprovider.h"
#include <qwebpage.h>
#include <QWebFrame>
#include <QWebPage>
#include <QThread>
#include <qeventloop.h>


webPageProvider * g_webPageProvider;


webPageProvider::webPageProvider()
{

}
void webPageProvider::loadFinishedReceived(bool ok){
    status=1;
}

QWebFrame * webPageProvider::getPage(QString url){
    int index=urls.indexOf(url);
    if (index>-1){
        qDebug() << "Already loaded page!";
        return webPages.at(index)->mainFrame();
    } else {
        qDebug() << "first loading of page!";
        // TODO: Put a mutex here for status
        QEventLoop eventloop;
        int counter=0;
        status=0;

        UserAgentWebPage * page=new UserAgentWebPage();
        urls<<url;
        webPages<<page;

        QWebFrame * frame = page->mainFrame();
        frame->load(QUrl(url));

        connect(frame,SIGNAL(loadFinished(bool)),SLOT(loadFinishedReceived(bool)));
        while((status==0)&&(counter!=10)){
            QThread::msleep(10);
            eventloop.processEvents(QEventLoop::ExcludeUserInputEvents,100);
            if(status!=0){
                counter++;
            }
        }

        return frame;
    }
}
