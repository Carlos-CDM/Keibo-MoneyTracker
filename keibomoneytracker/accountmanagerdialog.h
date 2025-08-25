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

#ifndef ACCOUNTMANAGERDIALOG_H
#define ACCOUNTMANAGERDIALOG_H

#include <QDialog>

namespace Ui {
class AccountManagerDialog;
}

class AccountManagerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AccountManagerDialog(QWidget *parent = 0);
    ~AccountManagerDialog();
    bool OpenAccount      = false;
    bool EditAccount      = false;
    bool DeleteAccount    = false;
    bool CreateNewAccount = false;

    bool allowLoadAccountImages = false;

    void fillListWithExistingAccounts(std::vector<std::string> listOfAccounts,
                                      std::vector<std::string> listOfAccountPaths);
    int provideSelectedAccountIdIndex(int &selectedAccountIdIndex);
    void setOverallThemeStyleSheet(QString styleSheetString);

private slots:
    bool eventFilter(QObject *obj, QEvent *event);
    void on_btnOpenAccount_clicked();
    void on_btnEditAccount_clicked();
    void on_btnDeleteAccount_clicked();
    void on_btnCreateNewAccount_clicked();
    void on_tableWidget_itemSelectionChanged();

private:
    Ui::AccountManagerDialog *ui;
    int SELECTED_ACCOUNT_INDEX = 0;
    std::vector<std::string> iListOfAccountPaths;
};

#endif // ACCOUNTMANAGERDIALOG_H
