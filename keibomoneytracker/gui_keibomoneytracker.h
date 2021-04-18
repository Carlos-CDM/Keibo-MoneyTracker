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

#ifndef GUI_BUYDATA_H
#define GUI_BUYDATA_H

#include <QMainWindow>
#include <QTime>
#include <QStyledItemDelegate>
#include <QTableWidget>
#include <QGLWidget>
#include <QOpenGLWidget>
#include <QOpenGLPaintDevice>
#include <QWheelEvent>
#include <QTableWidget>
#include <QScrollBar>
#include <QDir>

#include <math.h>
#include "keibomoneytracker.h"

namespace Ui {
class Gui_KeiboMoneyTracker;
class TableWidgetMouse;
}

class GridLineDelegate : public QStyledItemDelegate
{
    Q_OBJECT

    public:
    GridLineDelegate(QTableWidget* tableWidget);
    ~GridLineDelegate();

    protected:
    void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const;

    private:
    QPen pen;
    QTableWidget* table;
};

class TableWidgetMouse : public QTableWidget
{

Q_OBJECT

public:
    TableWidgetMouse (QWidget* parent = 0);
    ~TableWidgetMouse();

protected:
    void wheelEvent(QWheelEvent* event)
    {
        int items = (event->angleDelta().y()/event->DefaultDeltasPerStep)*10;
        if (event->angleDelta().y() != 0)
        {
            this->verticalScrollBar()->setValue(this->verticalScrollBar()->value()-items);
        }
    }
};

class Gui_KeiboMoneyTracker : public QMainWindow
{
    Q_OBJECT

public:
    explicit Gui_KeiboMoneyTracker(QWidget *parent = 0);
    ~Gui_KeiboMoneyTracker();

private slots:
    void on_monthBackwardButton_clicked();
    void on_monthForwardButton_clicked();
    void on_yearForwardButton_clicked();
    void on_yearBackwardsButton_clicked();
    void on_groupBackwardsButton_clicked();
    void on_groupForwardButton_clicked();

    void on_addExpenseButton_clicked();
    void on_addIncomeButton_clicked();
    void on_editItemButton_clicked();
    void on_deleteItemButton_clicked();

    void on_tableWidget_cellClicked(int row, int column);
    void on_tableOfGroups_cellClicked(int row, int column);

    void on_actionNew_triggered();
    void on_actionOpen_triggered();
    void on_actionExit_triggered();

    void on_actionManage_Groups_triggered();
    void on_actionManage_Income_Groups_triggered();
    void on_pushButtonToggleGroups_clicked();    

    void on_actionAppearance_triggered();

    void incomeGroupSelection(QAction *action);
    void expensesGroupSelection(QAction * action);


    void on_actionHow_to_use_triggered();
    void on_actionAbout_triggered();
    void on_actionDonate_triggered();

private:
    Ui::Gui_KeiboMoneyTracker *ui;

    bool TopOfTableReached    = false; //To know when a row can be selected
    bool BottomOfTableReached = false;
    bool TopOfGroupTableReached = false;
    bool BottomOfGroupTableReached = false;

    bool usingDarkTheme = false;

    bool eventFilter(QObject *obj, QEvent *event);

    bool focusingOverallIncomeExpenses = false;
    bool focusingGroups = false;
    void focusOverallIncomeExpenses();
    void focusGroups();

    bool APP_DIR_FOUND = false;
    const QString APP_DIR_NAME = "KeiboMoneyTracker";

    Language initialLanguage = ENGLISH;

    int realWorldYear  = 0;
    int realWorldMonth = 0;

    int currentYear                = 2020;
    int currentMonth               = 0;
    unsigned int currentGroupSelected       = 0;
    unsigned int currentIncomeGroupSelected = 0;
    bool showIncome                = true;

    int colorOfIncomeAmount        = 21;  //Default green

    Account currentAccount;
    std::string currentAccountName = "";
    int CURRENT_SELECTED_ACCOUNT = -1;     ///FROM ACCOUNT MANAGER
    int CURRENT_SELECTED_ACCOUNT_INDEX_FROM_MANAGER = 0;
    std::vector<std::string> ListOfExistingAccounts;
    std::vector<std::string> ListOfExistingAccountsPaths;
    bool AccountsExist = false;
    bool ACCOUNT_SET = false;

    QString currentOverallThemeStyleSheet = "color: rgb();";
    QString tablesStyleSheet;
    QString horizontalHeaderStyleSheet;
    QString verticalHeaderStyleSheet;

    void updateToCurrentYear();
    void updateToCurrentMonth();
    void displayArticlesOnTable();
    void displayMonthOnLabel();
    void updateGraph();
    void updateGroups();
    void updateListOfGroups();
    void updateColorsOnScreen(std::vector<ColorConfiguration>::iterator currentColorConfigIt);    
    void updateToClickedMonth(); //Function previously used in timer, therefore it doesn't have to be a slot anymore
    void toggle_IncomeOutcomeGroup();
    void goToNextGroup();
    void goToPreviousGroup();

    QDir homeDir;
    QDir AppDir;

    void searchForExistingAccounts();
    void requestAccountManager();    
    void requestAccountCreation();
    void requestAccountOpening(std::string &accountName, std::string &accountPath);
    void requestAccountEditing(std::string &accountName, std::string &accountPath);
    void requestAccountDeletion(std::string &accountName, std::string &accountPath);
    void verifyAccountInfo(std::string &accountName, std::string &accountPath);

    void setCurrentAccount();

    void addIncome();
    void addOutcome();
    void editSelectedTransaction();  //Change to edit element.
    void deleteSelectedTransaction();    

    void showAccountStats();

    void showGroupsMenu();

    void updateUiToLanguage(const Language &iLanguage);
};

#endif // GUI_BUYDATA_H
