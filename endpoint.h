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
#ifndef ENDPOINT_H
#define ENDPOINT_H

#include <QObject>

class QWebEnginePage;

class EndPoint : public QObject
{
    Q_OBJECT
    QWebEnginePage* page;
public:
    explicit EndPoint(QWebEnginePage* page,QObject *parent = 0);
    void setContent(QString &html);

signals:

public slots:
    void insertLink();
    void selectImage();
    void showHTML(const QString& html);
private:

    void execJS(const QString& js) const;

};

#endif // ENDPOINT_H
