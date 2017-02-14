/*
 * Copyright Meeting C++
 * Author Jens Weller
 *
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 2.0 or (at your option) the GNU General
** Public license version 3 or any later version approved by the KDE Free
** Qt Foundation. The licenses are as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL2 and LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-2.0.html and
** https://www.gnu.org/licenses/gpl-3.0.html.
 *
*/
#include "htmltexteditor.h"

#include <QCoreApplication>
#include <QWebEnginePage>
#include <QInputDialog>
#include <QDebug>

#ifdef WEBCHANNEL_WEBSOCKET
#include "shared/websockettransport.h"
int HTMLTextEditor::port = 13333;
#endif
#include "endpoint.h"

HTMLTextEditor::HTMLTextEditor(QWidget *parent) :
    QWebEngineView(parent)
#ifdef WEBCHANNEL_WEBSOCKET
  ,websocketserver(QStringLiteral("HTML Editor Server"), QWebSocketServer::NonSecureMode),wrapper(&websocketserver)
#endif
{
    //page()->setLinkDelegationPolicy(QWebPage::DelegateExternalLinks);

#ifndef WEBCHANNEL_WEBSOCKET
    QWebEngineProfile* profile = new QWebEngineProfile("MyWebChannelProfile", this);

    QFile webChannelJsFile(":/qtwebchannel/qwebchannel.js");
    if(!webChannelJsFile.open(QIODevice::ReadOnly) )
          qFatal( QString("Couldn't open qwebchannel.js file: %1").arg(webChannelJsFile.errorString()).toStdString().c_str() );
    else
    {
            QByteArray webChannelJs = webChannelJsFile.readAll();
            webChannelJs.append("\nnew QWebChannel(window.qt.webChannelTransport, function(channel) {window.hostObject = channel.objects.cppeditor;});");
            QWebEngineScript script;
                script.setSourceCode(webChannelJs);
                script.setName("qwebchannel.js");
                script.setWorldId(QWebEngineScript::MainWorld);
                script.setInjectionPoint(QWebEngineScript::DocumentCreation);
                script.setRunsOnSubFrames(false);
            profile->scripts()->insert(script);
     }
    setPage(new QWebEnginePage(profile,this));
#else //WEBCHANNEL_WEBSOCKET
    if (!websocketserver.listen(QHostAddress::LocalHost, port)) {
        qFatal("Failed to open web socket server.");
    }
    connect(&wrapper, &WebSocketClientWrapper::clientConnected,
            &webchannel, &QWebChannel::connectTo);
#endif
}

void HTMLTextEditor::execJS(const QString &js)const
{
    //qDebug() << "exec js" << js;
    page()->runJavaScript(js);
}

void HTMLTextEditor::setupTinyMCE3()
{
    QString editor = QString("file:///")+QCoreApplication::applicationDirPath()+"/tinymce3";
#ifdef WEBCHANNEL_WEBSOCKET
    setUrl(QUrl(editor+"/examples/editor.html?port="+ QString::number(port++)));
#else
    setUrl(QUrl(editor+"/examples/editor.html"));
#endif

    auto endpoint = new EndPoint(page(),this);
    webchannel.registerObject("cppeditor",endpoint);
    page()->setWebChannel(&webchannel);
}

/*
void HTMLTextEditor::insertLink()
{
    qDebug() << "Link Handler called";
    QString link = "https://www.qt.io";
    execJS(QString(R"(ed = tinyMCE.activeEditor;
tinyMCE.execCommand('createlink',false, "%1");
ed.selection.collapse();
ed.nodeChanged();)").arg(relative +link));
}

void HTMLTextEditor::onSelectImage()
{
    qDebug() << "Image Handler called";
    ImageDialog dlg(basepath + "/img/",imagelist,this);
    if(dlg.exec()!= QDialog::Accepted)return;
    QString alt,img;
    dlg.transferData(alt,img);
    QString js = R"(ed = tinyMCE.activeEditor; ed.execCommand('mceInsertContent',false,ed.dom.createHTML('img',{src : "%1",alt : "%2"}), {skip_undo : 1}); ed.undoManager.add();)";
    execJS(js.arg(relative + "img/"+ img,alt));
}*/
