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

#ifndef MANAGEGROUPSDIALOG_H
#define MANAGEGROUPSDIALOG_H

#include <QDialog>
#include "keibomoneytracker.h"

namespace Ui {
class ManageGroupsDialog;
}

class ManageGroupsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ManageGroupsDialog(QWidget *parent = 0);
    ~ManageGroupsDialog();

    void setYearData (Account tempYearData, bool showIncomeGroups); //For Income set true - For Outcome set false
    bool groupWasAdded()    {return groupAdded;   }
    bool groupWasEdited()   {return groupEdited;  }
    bool groupWasDeleted()  {return groupDeleted; }

    std::string newGroupName = "";
    int         itemIdNumber = 0;

    void setOverallThemeStyleSheet(QString styleSheetString, QString tTableHeaderStyleSheet, bool tUsingDarkTheme);
    void setLanguage(const Language & accountLanguage);

private slots:
    void on_acceptButton_clicked();
    void on_addGroupButton_clicked();
    void on_editGroupButton_clicked();
    void on_deleteGroupButton_clicked();

private:
    Ui::ManageGroupsDialog *ui;
    bool eventFilter(QObject *obj, QEvent *event);
    Language iLanguage = ENGLISH;

    bool TopOfTableReached    = false; //To know when a row can be selected
    bool BottomOfTableReached = false;
    void createNewGroup();
    void editSelectedGroup();
    void deleteSelectedGroup();

    Account yearData;
    std::vector<int> YearsIncludingTransactionOfGroupToDelete;
    std::vector<int> NumberOfTransactionPerYearOfGroupToDelete;
    
    bool editingIncomeGroups = false; //For Income set true - For Outcome set false

    bool groupAdded    = false;
    bool groupEdited   = false;
    bool groupDeleted  = false;

    bool usingDarkTheme = false;
    QString overallThemeStyleSheetString;
    QString tableHeaderStyleSheet;
};

#endif // MANAGEGROUPSDIALOG_H
