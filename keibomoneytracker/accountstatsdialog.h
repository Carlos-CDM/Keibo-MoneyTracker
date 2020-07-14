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

#ifndef ACCOUNTSTATSDIALOG_H
#define ACCOUNTSTATSDIALOG_H

#include <QDialog>

namespace Ui {
class AccountStatsDialog;
}

class AccountStatsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AccountStatsDialog(QWidget *parent = nullptr);
    ~AccountStatsDialog();
    void getAccountStats(std::vector<QString> statNames, std::vector<QString> statValues);
    void setThemeStyleSheet(QString styleSheetString);
private:
    Ui::AccountStatsDialog *ui;
};

#endif // ACCOUNTSTATSDIALOG_H
