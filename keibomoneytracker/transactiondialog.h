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

#ifndef TRANSACTIONDIALOG_H
#define TRANSACTIONDIALOG_H

#include <QDialog>
#include <iostream>
#include "keibomoneytrackerinclude.h"

namespace Ui {
class TransactionDialog;
}

class TransactionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TransactionDialog(QWidget *parent = 0);
    ~TransactionDialog();

    void provideArticleInfo(std::string &Nam, double &Pri, int &Cat, int &Mon, int &Day, RepetitionOption &Repeat, int &Year);
    void setCategoryList(std::vector<std::string> categoryList);
    void setListOfPossibleYears();
    void displayItemInfo(std::string Nam, double Pri, int Cat, int Mon, int Day, RepetitionOption Repeat, int year);
    bool transactionNameOK = false;
    bool transactionAmountOK = false;
    bool usingDarkTheme = false;

    void setOverallThemeStyleSheet(QString styleSheetString, bool tUsingDarkTheme);
    void setNumberOfDaysInSelectedMonth(int selectedMonth, int selectedYear);

    void setLanguage(const Language & accountLanguage);

private slots:
    void on_pushButtonOk_clicked();
    void on_comboBoxMonth_currentIndexChanged(int index);

    void on_comboBoxYear_currentIndexChanged(int index);

private:
    Ui::TransactionDialog *ui;
    RepetitionOption        Repeat_;
    QString     Name_ ;
    QString     Price_;
    int         Year_;
    int         Month_;
    int         Day_;
    int         Category_;

    Language iLanguage = ENGLISH;

    std::vector<int> ListOfPossibleYears;

    bool eventFilter(QObject *obj, QEvent *event);

    void checkAndSetTransaction();

    QString overallThemeStyleSheetString;
};

#endif // TRANSACTIONDIALOG_H
