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
#ifndef TINYMCEEDITOR_H
#define TINYMCEEDITOR_H

#include <QtWebEngineWidgets/QtWebEngineWidgets>
#include <QString>
#include <QStringList>
#include <QHash>

//#define WEBCHANNEL_WEBSOCKET 1

#ifdef WEBCHANNEL_WEBSOCKET
#include <QtWebSockets/QWebSocketServer>
#include "shared/websocketclientwrapper.h"
#endif
#include <QWebChannel>


class HTMLTextEditor : public QWebEngineView
{
    Q_OBJECT
#ifdef WEBCHANNEL_WEBSOCKET
    QWebSocketServer websocketserver;
    WebSocketClientWrapper wrapper;
    static int port;
#endif
    QWebChannel webchannel;
public:
    explicit HTMLTextEditor(QWidget *parent = 0);

    void setupTinyMCE3();
    QString getContent()const;
    void setBasePath(const QString &bp);
private:
    void execJS(const QString& js) const;
};

#endif // TINYMCEEDITOR_H
