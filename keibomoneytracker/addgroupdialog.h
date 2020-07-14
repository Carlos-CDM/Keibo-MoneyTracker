/*
* Copyright © 2020 Carlos Constancio Dominguez Martinez
*
* This file is part of Keibo-MoneyTracker
*
* Keibo-MoneyTracker is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* Keibo-MoneyTracker is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <https://www.gnu.org/licenses/>.
*
* Authored by: Carlos Constancio Dominguez Martinez <dmartinez.carlos@gmail.com>
*/

#ifndef ADDGROUPDIALOG_H
#define ADDGROUPDIALOG_H

#include <QDialog>
#include "keibomoneytrackerinclude.h"

namespace Ui {
class Addgroupdialog;
}

class Addgroupdialog : public QDialog
{
    Q_OBJECT

public:
    explicit Addgroupdialog(QWidget *parent = 0);
    ~Addgroupdialog();

    void setLanguage(const Language &iLanguage);

    void provideGroupName(std::string &groupName);
    void setGroupName(std::string &groupName);
    void setOverallThemeStyleSheet(QString styleSheetString);

private slots:
    void on_acceptButton_clicked();
    void on_cancelButton_clicked();

    bool eventFilter(QObject *obj, QEvent *event);

private:
    Ui::Addgroupdialog *ui;
    QString tempGroupName;
};

#endif // ADDGROUPDIALOG_H
