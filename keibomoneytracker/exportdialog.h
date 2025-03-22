#ifndef EXPORTDIALOG_H
#define EXPORTDIALOG_H

#include <QDialog>
/*
* Copyright © 2020-2025 Carlos Constancio Dominguez Martinez
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

#include "keibomoneytracker.h"

namespace Ui {
class ExportDialog;
}

class ExportDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ExportDialog(QWidget *parent = nullptr);
    ~ExportDialog();

    void setAccount(Account *tAccount);
    void setListOfYearsWithData(std::vector<int>& listOfYearsWithData);
    void setOverallThemeStyleSheet(QString styleSheetString, bool useDarkTheme);

private slots:
    void on_exportButton_clicked();
    void on_cancelButton_clicked();

private:
    Ui::ExportDialog *ui;
    Account *mainAccount = nullptr;
    QString homeFolder   = "/home";
    bool eventFilter(QObject *obj, QEvent *event);
    QString styleSheetStr;
    bool usingDarkTheme = false;


};

#endif // EXPORTDIALOG_H
