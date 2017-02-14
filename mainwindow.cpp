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
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "htmltexteditor.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    auto editor = new HTMLTextEditor(this);
    ui->tabWidget->addTab(editor,"htmltexteditor");
    editor->setupTinyMCE3();
}

MainWindow::~MainWindow()
{
    delete ui;
}
