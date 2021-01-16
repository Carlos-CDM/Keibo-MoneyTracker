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

#ifndef NEWELEMENTSADDEDAUTOMATICALLYDIALOG_H
#define NEWELEMENTSADDEDAUTOMATICALLYDIALOG_H

#include <QDialog>
#include "keibomoneytracker.h"

namespace Ui {
class newElementsAddedAutomaticallyDialog;
}

class newElementsAddedAutomaticallyDialog : public QDialog
{
    Q_OBJECT

public:
    explicit newElementsAddedAutomaticallyDialog(QWidget *parent = nullptr);
    ~newElementsAddedAutomaticallyDialog();

    void getInfoToDisplay(std::vector<Transaction> &newElementsAdded,
                          std::vector<std::string> &incomeGroups,
                          std::vector<std::string> &outcomeGroups,
                          const int & colorOfIncomeAmount,
                          const Language & currentLanguage);

    void setOverallThemeStyleSheet(QString styleSheetString, bool tUsingDarkTheme, QString tTableHeaderStyleSheet);
    void setLanguage(const Language & currentLanguage);

private slots:
    void on_pushButtonClose_clicked();

private:
    Ui::newElementsAddedAutomaticallyDialog *ui;
    Language iLanguage;
    bool eventFilter(QObject *obj, QEvent *event);

    bool usingDarkTheme = false;
};

#endif // NEWELEMENTSADDEDAUTOMATICALLYDIALOG_H
