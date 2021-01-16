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

#ifndef CHECKFAULTYTRANSACTIONSDIALOG_H
#define CHECKFAULTYTRANSACTIONSDIALOG_H

#include <QDialog>
#include "keibomoneytracker.h"
#include "keibomoneytrackerinclude.h"

namespace Ui {
class checkFaultyTransactionsDialog;
}

class checkFaultyTransactionsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit checkFaultyTransactionsDialog(QWidget *parent = nullptr);
    ~checkFaultyTransactionsDialog();

    bool transactionNameOK = false;
    bool transactionAmountOK = false;

    void setLanguage(const Language & iLanguage);
    void setCategoryList(std::vector<std::string> categoryList);
    void displayItemInfo(std::string Nam, double Pri, int Cat, int Mon, int Day, RepetitionOption Repeat);

    void updateInfo();
    void getFaultyTransactionsData(std::vector<Transaction> &tempListOfFaultyTransactions, const int &tempYearOfFaultyTransactions);
    void getGroups(std::vector<std::string> &tempIncomeGroups, std::vector<std::string> &tempExpensesGroups) {incomeGroups=tempIncomeGroups; expensesGroups=tempExpensesGroups;}

    void provideUpdatedTransactions(std::vector<Transaction> &tempListOfUpdatedTransactions);
    void provideArticleInfo(Transaction &iTransaction, bool isIncome);

    void addUpdatedTransactionToList();
    void setOverallThemeStyleSheet(QString styleSheetString, bool tUsingDarkTheme);

private slots:
    void on_SetAndNextButton_clicked();
    void on_discardButton_clicked();
    void on_discardAllButton_clicked();
    void on_comboBoxMonth_currentIndexChanged(int index);

private:
    Ui::checkFaultyTransactionsDialog *ui;
    Language currentLanguage = ENGLISH;
    int yearOfFaultyTransactions = 0;
    std::vector<Transaction> listOfFaultyTransactions;
    std::vector<Transaction> listOfUpdatedTransactions;
    unsigned int currentTransaction = 0;

    std::vector<std::string> incomeGroups;
    std::vector<std::string> expensesGroups;

    QString     Name_ ;
    QString     Price_;
    int         Month_;
    int         Day_;
    int         Category_;
    RepetitionOption  Repeat_;


    bool eventFilter(QObject *obj, QEvent *event);

    void checkAndSetTransaction();

    QString overallThemeStyleSheetString;
    bool usingDarkTheme = false;
};

#endif // CHECKFAULTYTRANSACTIONSDIALOG_H
