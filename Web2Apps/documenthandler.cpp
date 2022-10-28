/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "documenthandler.h"

#include <QtGui/QTextDocument>
#include <QtGui/QTextCursor>
#include <QtGui/QFontDatabase>
#include <QtCore/QFileInfo>
#include <QTextTable>
#include <QTextTableFormat>
#include <QTextImageFormat>
#include <QImage>
#include <QTextDocumentFragment>
#include <QFile>
#include <QApplication>
#include <QTextEdit>
#include <QClipboard>

DocumentHandler::DocumentHandler()
    : m_target(0)
    , m_doc(0)
    , m_cursorPosition(-1)
    , m_selectionStart(0)
    , m_selectionEnd(0)
{
}

void DocumentHandler::setTarget(QQuickItem *target)
{
    m_doc = 0;
    m_target = target;
    if (!m_target)
        return;

    QVariant doc = m_target->property("textDocument");
    if (doc.canConvert<QQuickTextDocument*>()) {
        QQuickTextDocument *qqdoc = doc.value<QQuickTextDocument*>();
        if (qqdoc){
            m_doc = qqdoc->textDocument();
        }

    }
    emit targetChanged();
}

void DocumentHandler::setFileUrl(const QUrl &arg)
{
    if (m_fileUrl != arg) {
        m_fileUrl = arg;
        QString fileName = QQmlFile::urlToLocalFileOrQrc(arg);
        if (QFile::exists(fileName)) {
            QFile file(fileName);
            if (file.open(QFile::ReadOnly)) {
                QByteArray data = file.readAll();
                QTextCodec *codec = QTextCodec::codecForHtml(data);
                setText(codec->toUnicode(data));
                if (m_doc)
                    m_doc->setModified(false);
                if (fileName.isEmpty())
                    m_documentTitle = QStringLiteral("untitled.txt");
                else
                    m_documentTitle = QFileInfo(fileName).fileName();

                emit textChanged();
                emit documentTitleChanged();

                reset();
            }
        }
        emit fileUrlChanged();
    }
}

QString DocumentHandler::documentTitle() const
{
    return m_documentTitle;
}

void DocumentHandler::setDocumentTitle(QString arg)
{
    if (m_documentTitle != arg) {
        m_documentTitle = arg;
        emit documentTitleChanged();
    }
}

void DocumentHandler::setText(const QString &arg)
{
    if (m_text != arg) {
        m_text = arg;
        emit textChanged();
    }
}

void DocumentHandler::saveAs(const QUrl &arg, const QString &fileType)
{
    bool isHtml = fileType.contains(QLatin1String("htm"));
    QLatin1String ext(isHtml ? ".html" : ".txt");
    QString localPath = arg.toLocalFile();
    if (!localPath.endsWith(ext))
        localPath += ext;
    QFile f(localPath);
    if (!f.open(QFile::WriteOnly | QFile::Truncate | (isHtml ? QFile::NotOpen : QFile::Text))) {
        emit error(tr("Cannot save: ") + f.errorString());
        return;
    }
    f.write((isHtml ? m_doc->toHtml() : m_doc->toPlainText()).toLocal8Bit());
    f.close();
    qDebug() << "saved to" << localPath;
    setFileUrl(QUrl::fromLocalFile(localPath));
}

QUrl DocumentHandler::fileUrl() const
{
    return m_fileUrl;
}




QString DocumentHandler::plainText() const
{
    return m_doc->toPlainText();
}
void DocumentHandler::loadText(QString text)
{
    if(plainText()!=text){
        if(cleanHtml(m_text)!=text){
            setText(text);
        }

    }
    //return m_doc->toPlainText();
}
QString DocumentHandler::text() const
{
    return m_text;
}

void DocumentHandler::setCursorPosition(int position)
{
    if (position == m_cursorPosition)
        return;

    m_cursorPosition = position;

    reset();
}

void DocumentHandler::reset()
{
    emit fontFamilyChanged();
    emit alignmentChanged();
    emit boldChanged();
    emit italicChanged();
    emit underlineChanged();
    emit fontSizeChanged();
    emit textColorChanged();
    markup = 0;

}

QTextCursor DocumentHandler::textCursor() const
{
    if(m_doc){
        QTextCursor cursor = QTextCursor(m_doc);
        if (m_selectionStart != m_selectionEnd) {
            cursor.setPosition(m_selectionStart);
            cursor.setPosition(m_selectionEnd, QTextCursor::KeepAnchor);
        } else {
            cursor.setPosition(m_cursorPosition);
        }
        return cursor;
    }
    return QTextCursor();

}


void DocumentHandler::mergeFormatOnWordOrSelection(const QTextCharFormat &format)
{
    QTextCursor cursor = textCursor();
    if (!cursor.hasSelection())
        cursor.select(QTextCursor::WordUnderCursor);
    // If this doesnt workd, maybe they are no words ?
    if (!cursor.hasSelection()){
     //qDebug() << "Still word no selection!!!";
        cursor.select(QTextCursor::Document);
    }
    if (!cursor.hasSelection()){
       qDebug() << "Document selection did no work!!! TODO: Create temporary content to update the textarea mousecursor!!!";
        cursor.select(QTextCursor::Document);
    }
    cursor.mergeCharFormat(format);
}

void DocumentHandler::setSelectionStart(int position)
{
    m_selectionStart = position;
}

void DocumentHandler::setSelectionEnd(int position)
{
    m_selectionEnd = position;
}

void DocumentHandler::setAlignment(Qt::Alignment a)
{
    markup++;
    QTextBlockFormat fmt;
    fmt.setAlignment((Qt::Alignment) a);
    QTextCursor cursor = QTextCursor(m_doc);
    cursor.setPosition(m_selectionStart, QTextCursor::MoveAnchor);
    cursor.setPosition(m_selectionEnd, QTextCursor::KeepAnchor);
    cursor.mergeBlockFormat(fmt);
    convertToHtmlIfNeeded();
    emit alignmentChanged();
}

Qt::Alignment DocumentHandler::alignment() const
{
    QTextCursor cursor = textCursor();
    if (cursor.isNull())
        return Qt::AlignLeft;
    return textCursor().blockFormat().alignment();
}

bool DocumentHandler::bold() const
{
    QTextCursor cursor = textCursor();
    if (cursor.isNull()){
        //qDebug() << "Reading bold. Cursor null!";
        return false;
    }
    //qDebug() << "Reading bold?" << textCursor().charFormat().fontWeight();
    return textCursor().charFormat().fontWeight() == QFont::Bold;
}

bool DocumentHandler::italic() const
{
    QTextCursor cursor = textCursor();
    if (cursor.isNull())
        return false;
    return textCursor().charFormat().fontItalic();
}

bool DocumentHandler::underline() const
{
    QTextCursor cursor = textCursor();
    if (cursor.isNull())
        return false;
    return textCursor().charFormat().fontUnderline();
}

void DocumentHandler::convertToHtmlIfNeeded(){
    // Only convert if it's not already HTML!
    if(!Qt::mightBeRichText(m_text)){
        // Store current cursor
        int start=m_selectionStart;
        int end=m_selectionEnd;


        QString newval=m_doc->toHtml();
        qDebug() << "Converting plain to HTML!" << newval;
        m_target->setProperty("text",newval);

        // Reselect cursor
        QMetaObject::invokeMethod(m_target, "select",
            Q_ARG(int, start),Q_ARG(int, end));
    }
}

void DocumentHandler::setBold(bool arg)
{
    QTextCharFormat fmt;
    fmt.setFontWeight(arg ? QFont::Bold : QFont::Normal);
    mergeFormatOnWordOrSelection(fmt);
    if (arg)
        convertToHtmlIfNeeded();
    //qDebug() << "setting bold to" << arg;
    emit boldChanged();
}

void DocumentHandler::setItalic(bool arg)
{
    QTextCharFormat fmt;
    fmt.setFontItalic(arg);
    mergeFormatOnWordOrSelection(fmt);
    if (arg)
        convertToHtmlIfNeeded();
    emit italicChanged();
}

void DocumentHandler::setUnderline(bool arg)
{
    QTextCharFormat fmt;
    fmt.setFontUnderline(arg);
    mergeFormatOnWordOrSelection(fmt);
    if (arg)
        convertToHtmlIfNeeded();
    emit underlineChanged();
}

int DocumentHandler::fontSize() const
{
    QTextCursor cursor = textCursor();
    if (cursor.isNull())
        return 0;
    QTextCharFormat format = cursor.charFormat();
    return format.font().pointSize();
}

void DocumentHandler::setFontSize(int arg)
{
    QTextCursor cursor = textCursor();
    if (cursor.isNull())
        return;
    QTextCharFormat format;
    format.setFontPointSize(arg);
    mergeFormatOnWordOrSelection(format);
    convertToHtmlIfNeeded();
    emit fontSizeChanged();
}

QColor DocumentHandler::textColor() const
{
    QTextCursor cursor = textCursor();
    if (cursor.isNull())
        return QColor(Qt::black);
    QTextCharFormat format = cursor.charFormat();
    return format.foreground().color();
}

void DocumentHandler::setTextColor(const QColor &c)
{
    QTextCursor cursor = textCursor();
    if (cursor.isNull())
        return;
    QTextCharFormat format;
    format.setForeground(QBrush(c));
    mergeFormatOnWordOrSelection(format);
     convertToHtmlIfNeeded();
    emit textColorChanged();
}

QString DocumentHandler::fontFamily() const
{
    QTextCursor cursor = textCursor();
    if (cursor.isNull())
        return QString();
    QTextCharFormat format = cursor.charFormat();
    return format.font().family();
}

void DocumentHandler::setFontFamily(const QString &arg)
{
    QTextCursor cursor = textCursor();
    if (cursor.isNull())
        return;
    QTextCharFormat format;
    format.setFontFamily(arg);
    mergeFormatOnWordOrSelection(format);
     convertToHtmlIfNeeded();
    emit fontFamilyChanged();
}

QStringList DocumentHandler::defaultFontSizes() const
{
    // uhm... this is quite ugly
    QStringList sizes;
    QFontDatabase db;
    foreach (int size, db.standardSizes())
        sizes.append(QString::number(size));
    return sizes;
}


QVariantList DocumentHandler::table() const
{
    QVariantList arg;

    arg<<10;
    return arg;

}

void DocumentHandler::setTable(QVariantList arg)
{

    int columns = arg[0].toInt();
    int rows = arg[1].toInt();

    QTextTableFormat tableFormat;
    tableFormat.setBorderStyle(QTextFrameFormat::BorderStyle_Solid);
    tableFormat.setAlignment(Qt::AlignTop);
    tableFormat.setWidth(400);


    QTextCursor cursor = textCursor();
    cursor.insertTable(rows, columns, tableFormat);
    convertToHtmlIfNeeded();
    emit tableChanged();
}
QVariantList DocumentHandler::image() const
{
    QVariantList arg;

    arg<<10;
    return arg;

}
void DocumentHandler::setImage(QVariantList arg)
{

    QString pictureUrl  = arg[0].toUrl().toString();

    QTextDocumentFragment fragment;
    fragment = QTextDocumentFragment::fromHtml("<img src='"+pictureUrl+"'>");
    QTextCursor cursor = textCursor();
    cursor.insertFragment(fragment);
    convertToHtmlIfNeeded();

    emit imageChanged();
}
Q_INVOKABLE QVariant  DocumentHandler::perform(QString action, QVariant parameter) {

    qDebug() << "DocumentHandler received " + action + ": " << parameter;

    QVariant returnval;
    //if(!m_doc) return "no document ";
    if(action == "viewSource"){
        QClipboard *clipboard = QApplication::clipboard();


        clipboard->setText(cleanHtml(m_doc->toHtml()));


    }
    if(action == "getHtml"){

        returnval = cleanHtml(m_doc->toHtml());

    }
    return returnval;
}

QString DocumentHandler::cleanHtml(QString html){

    if(!html.isEmpty()){
        html=html.replace("<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\np, li { white-space: pre-wrap; }\n</style></head>","<html>");
        //int be = html.indexOf("<p");
        //int end = html.indexOf("</body>");

        //return html.mid(be,end-be);
    }
    return html;
}
