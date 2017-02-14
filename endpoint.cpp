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

#include "endpoint.h"

#include <QWebEnginePage>
#include <QInputDialog>
#include <QDebug>

EndPoint::EndPoint(QWebEnginePage *page, QObject *parent) : QObject(parent),page(page)
{

}

void EndPoint::setContent( QString &html)
{
    execJS(QString(R"(tinyMCE.activeEditor.setContent('%1');)").arg(html.replace("\n","\\n").replace("\"","\\\"")));
}

void EndPoint::insertLink()
{
    qDebug() << "insertLink";
    QString link = "https://www.qt.io";
    //dlg.transferData(link);
    execJS(QString(R"(ed = tinyMCE.activeEditor;
tinyMCE.execCommand('createlink',false, "%1");
ed.selection.collapse();
ed.nodeChanged();)").arg(link));
}

void EndPoint::selectImage()
{
    qDebug() << "selectImage";
}

void EndPoint::showHTML(const QString &html)
{
    QString code = QInputDialog::getMultiLineText((QWidget*)parent(),"Edit HTML","Current HTML content",html);
    if(!code.isEmpty() && html != code)
        setContent(code);
}

void EndPoint::execJS(const QString &js) const
{
    page->runJavaScript(js);
}
