#include "recursivevariantmodifier.h"
#include <uploader.h>
#include <domparser.h>

RecursiveVariantModifier::RecursiveVariantModifier()
{

}
QVariant RecursiveVariantModifier::getValue(QVariant data, QVariantList path){

    if(path.isEmpty()){
        return data;
    }

    switch(data.type())
    {
    case(QVariant::List):
    {
        QVariantList list = data.toList();
        int index=path.at(0).toInt();
        if(list.count()>index){
            path.removeFirst();
            return getValue(list[index],path);
        } else {
            return QVariant();
        }
    }
        break;

    case(QVariant::StringList):
    {
        QStringList list = data.toStringList();
        if(path.length()==1){
            int index=path.at(0).toInt();
            if(list.count()>index){
                path.removeFirst();
                return getValue(list[index],path);
            } else {
                return QVariant();
            }
        } else {
            return QVariant();
        }
    }
        break;

    case(QVariant::Map):
    {
        QVariantMap map = data.toMap();

        QString key=path.at(0).toString();
        path.removeFirst();
        return getValue(map[key],path);

    }
        break;

    case(QVariant::Hash):
    {
        QVariantHash hash = data.toHash();

        QString key=path.at(0).toString();
        path.removeFirst();
        return getValue(hash[key],path);

    }
        break;

    default:
    {
        return QVariant();
    }
        break;
    }
    qDebug()<<"This should never happen!";
}

QVariant RecursiveVariantModifier::changeValue(QVariant data, QVariantList path, QVariant newVal){

    switch(data.type())
    {
    case(QVariant::List):
    {

        if(path.length()>=1){
            QVariantList list = data.toList();
            int index=path.at(0).toInt();
            if(index == -1){
                path.removeFirst();
                list << changeValue(QVariant(),path,newVal);;
                return list;
            } else if(list.count()>index){
                path.removeFirst();
                list[index]=changeValue(data.toList().at(index),path,newVal);
                return list;
            } else {
                qDebug() << "Patch Error: Index out of bounds";
                return QVariant();
            }
        } else {
            return newVal.toList();
        }

    }
        break;

    case(QVariant::StringList):
    {
        QStringList list = data.toStringList();
        if(path.length()==1){
            int index=path.at(0).toInt();
            path.removeFirst();
            if(index==-1){
                list << newVal.toString();;
                return list;
            } else if(list.count()>index){
                list[index]=newVal.toString();
                return list;
            } else {
                qDebug() << "Patch Error: Index out of bounds";
                return QVariant();
            }
        } else if (path.length()==0){
            return newVal.toStringList();
        }else {
            qDebug() <<"Patch Error: Error, invalid path!";
            return QVariant();
        }
    }
        break;

    case(QVariant::Map):
    {
        QVariantMap map = data.toMap();
        if(path.length()>=1){
            QString key=path.at(0).toString();
            path.removeFirst();
            map[key]=changeValue(map[key],path,newVal);
        } else {
            return newVal.toMap();
        }
        return map;
    }
        break;

    case(QVariant::Hash):
    {
        QVariantHash hash = data.toHash();
        if(path.length()>=1){
            QString key=path.at(0).toString();
            path.removeFirst();
            hash[key]=changeValue(hash[key],path,newVal);
        } else {
            return newVal.toHash();
        }
        return hash;
    }
        break;

    default:
    {
        //qDebug() << "Default entry";
        if(path.isEmpty()){

            return newVal;
        } else {
            if(path.at(0).type()==QVariant::String){
                QVariantMap newMap;
                QString key=path.at(0).toString();
                path.removeFirst();
                newMap[key]=changeValue(QVariant(),path,newVal);
                return newMap;
            } else if(path.at(0).type()==QVariant::Int){
                QVariantList newList;
                if(path.at(0).toInt()==-1){
                    path.removeFirst();

                    newList<<changeValue(QVariant(),path,newVal);
                    return newList;

                }  else {
                    qDebug() << "Path error: Unexisting index!";
                    return QVariant();
                }
            }
        }
    }
        break;
    }
}
#ifndef STANDALONE_VIEWER
QVariant RecursiveVariantModifier::uploadAllFiles(QVariant data)
{

    switch(data.type())
    {
    case(QVariant::Bool):
    case(QVariant::Int):
    case(QVariant::UInt):
    case(QVariant::LongLong):
    case(QVariant::ULongLong):
    case(QVariant::Double):
    case(QVariant::ByteArray):
    case(QVariant::Color):
    case(QVariant::Invalid):
        break;

    case(QVariant::Url):
    case(QVariant::String):
    {
        QString dataString = data.toString();
        if(dataString.startsWith("file:")){
            QString newFileName=Uploader::getRandomString()+".jpg";
            QString uploadedName=Uploader::uploadFile(dataString,newFileName);
            // This happens in the __config.
            // Replace also in the _content
            domParser->_content=replaceContent(domParser->_content,dataString,uploadedName).toMap();
            return uploadedName;
        }
    }
        break;


    case(QVariant::List):
    {
        QVariantList list = data.toList();
        QVariantList returnList;
        for(int i = 0; i < list.count(); ++i)
        {
            returnList<<uploadAllFiles(list.at(i));
        }
        return returnList;
    }
        break;

    case(QVariant::StringList):
    {
        QStringList list = data.toStringList();
        QVariantList returnList;
        for(int i = 0; i < list.count(); ++i)
        {
            returnList<<uploadAllFiles(list.at(i));
        }
        return returnList;
    }
        break;

    case(QVariant::Map):
    {
        QVariantMap map = data.toMap();

        QVariantMap::iterator i;
        QVariantMap returnMap;
        for (i = map.begin(); i != map.end(); ++i)
        {
            returnMap[i.key()]=uploadAllFiles(i.value());
        }
        return returnMap;
    }
        break;

    case(QVariant::Hash):
    {
        QVariantHash hash = data.toHash();
        QVariantHash::iterator i;
        QVariantHash returnHash;
        for (i = hash.begin(); i != hash.end(); ++i)
        {
            returnHash[i.key()]=uploadAllFiles(i.value());
        }
        return returnHash;
    }
        break;

    default:
        break;
    }

    return data;
}
#endif

QVariant RecursiveVariantModifier::replaceContent(QVariant data,
                                                  QString oldValue,
                                                  QString newValue)
{
    switch(data.type())
    {
    case(QVariant::Bool):
    case(QVariant::Int):
    case(QVariant::UInt):
    case(QVariant::LongLong):
    case(QVariant::ULongLong):
    case(QVariant::Double):
    case(QVariant::ByteArray):
    case(QVariant::Color):
    case(QVariant::Invalid):
        break;

    case(QVariant::Url):
    case(QVariant::String):
    {
        QString dataString = data.toString();
        if(dataString == oldValue){
            return newValue;
        }
    }
        break;


    case(QVariant::List):
    {
        QVariantList list = data.toList();
        QVariantList returnList;
        for(int i = 0; i < list.count(); ++i)
        {
            returnList<<replaceContent(list.at(i),
                                       oldValue,
                                       newValue);
        }
        return returnList;
    }
        break;

    case(QVariant::StringList):
    {
        QStringList list = data.toStringList();
        QVariantList returnList;
        for(int i = 0; i < list.count(); ++i)
        {
            returnList<<replaceContent(list.at(i),
                                       oldValue,
                                       newValue);
        }
        return returnList;
    }
        break;

    case(QVariant::Map):
    {
        QVariantMap map = data.toMap();

        QVariantMap::iterator i;
        QVariantMap returnMap;
        for (i = map.begin(); i != map.end(); ++i)
        {
            returnMap[i.key()]=replaceContent(i.value(),
                                              oldValue,
                                              newValue);
        }
        return returnMap;
    }
        break;

    case(QVariant::Hash):
    {
        QVariantHash hash = data.toHash();
        QVariantHash::iterator i;
        QVariantHash returnHash;
        for (i = hash.begin(); i != hash.end(); ++i)
        {
            returnHash[i.key()]=replaceContent(i.value(),
                                               oldValue,
                                               newValue);
        }
        return returnHash;
    }
        break;

    default:
        break;
    }
    return data;
}

