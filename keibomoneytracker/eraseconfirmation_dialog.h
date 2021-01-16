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

#ifndef ERASECONFIRMATION_DIALOG_H
#define ERASECONFIRMATION_DIALOG_H

#include <QDialog>
#include "keibomoneytrackerinclude.h"

namespace Ui {
class eraseConfirmation_dialog;
}

class eraseConfirmation_dialog : public QDialog
{
    Q_OBJECT

public:
    explicit eraseConfirmation_dialog(QWidget *parent = 0);
    ~eraseConfirmation_dialog();

    bool comfirmed(){return Accepted;}
    void setInfoText (const std::string &text);
    void setInfoList (const Language &iLanguage, const std::string &info,
                      const std::vector<int> &listOfYears, const std::vector<int> &listOfNumberOfTransactions,
                      bool showTable);
    void setOverallThemeStyleSheet(QString styleSheetString, bool usingDarkTheme);
    void setTableHeaderStyleSheet(QString tTableHeaderStyleSheet);
    void disableCancelButton();

private slots:
    void on_pushButtonOk_clicked();

    void on_pushButtonCancel_clicked();

private:
    Ui::eraseConfirmation_dialog *ui;
    bool Accepted = false;

    bool eventFilter(QObject *obj, QEvent *event);
};

#endif // ERASECONFIRMATION_DIALOG_H
