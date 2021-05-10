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

#include "gui_keibomoneytracker.h"
#include "ui_gui_keibomoneytracker.h"
#include "transactiondialog.h"
#include "managegroupsdialog.h"
#include "eraseconfirmation_dialog.h"
#include "accountdialog.h"
#include "checkfaultytransactionsdialog.h"
#include "accountstatsdialog.h"
#include "newelementsaddedautomaticallydialog.h"

#include "accountmanagerdialog.h"
#include "themecolorsdialog.h"
#include "requestlanguagedialog.h"
#include "userguide.h"
#include "aboutdialog.h"
#include "weeklyphrases.h"
#include "donatedialog.h"

#include <ctime>
#include <QToolTip> //To enable toast
#include <thread>
#include <QLocale>
#include <QMouseEvent>
#include <QTableWidget>


#include <QMouseEvent>
#include <QKeyEvent>
#include <QEvent>

GridLineDelegate::GridLineDelegate(QTableWidget* tableView)
{
    QColor gridColor(120, 120, 120, 200);
    pen = QPen(gridColor, 0, tableView->gridStyle());
    table = tableView;
}

void GridLineDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option,const QModelIndex& index)const
{
    QStyledItemDelegate::paint(painter, option, index);
    QPen oldPen = painter->pen();
    painter->setPen(pen);

    QPoint p1 = QPoint(option.rect.bottomLeft().x()-1,option.rect.bottomLeft().y());
    QPoint p2 = QPoint(option.rect.bottomRight().x()+1,option.rect.bottomRight().y());
    painter->drawLine(p1, p2);
    painter->setPen(oldPen);
}

GridLineDelegate::~GridLineDelegate()
{
    delete table;
}

TableWidgetMouse::TableWidgetMouse(QWidget *parent) :
    QTableWidget(parent)
{
}

TableWidgetMouse::~TableWidgetMouse()
{
}


Gui_KeiboMoneyTracker::Gui_KeiboMoneyTracker(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Gui_KeiboMoneyTracker)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

    this->ui->tableWidget->installEventFilter(this);
    this->ui->yearForwardButton->installEventFilter(this);
    this->ui->yearBackwardsButton->installEventFilter(this);
    this->ui->addIncomeButton->installEventFilter(this);
    this->ui->addExpenseButton->installEventFilter(this);
    this->ui->editItemButton->installEventFilter(this);
    this->ui->copyButton->installEventFilter(this);
    this->ui->deleteItemButton->installEventFilter(this);
    this->ui->pushButtonToggleGroups->installEventFilter(this);
    this->ui->tableOfGroups->installEventFilter(this);
    this->ui->widget1->installEventFilter(this);
    this->ui->labelAccountIcon->installEventFilter(this);
    this->ui->widget_2->installEventFilter(this);

    //-----------------------------------------------------
    this->ui->tableWidget->setTabKeyNavigation(false);
    this->ui->tableOfGroups->setTabKeyNavigation(false);

    this->ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    this->ui->tableOfGroups->setEditTriggers(QAbstractItemView::NoEditTriggers);

    this->ui->pushButtonToggleGroups->setFocusPolicy(Qt::NoFocus);
    this->ui->monthForwardButton->setFocusPolicy(Qt::NoFocus);
    this->ui->monthBackwardButton->setFocusPolicy(Qt::NoFocus);
    this->ui->groupForwardButton->setFocusPolicy(Qt::NoFocus);
    this->ui->groupBackwardsButton->setFocusPolicy(Qt::NoFocus);
    this->ui->yearForwardButton->setFocusPolicy(Qt::NoFocus);
    this->ui->yearBackwardsButton->setFocusPolicy(Qt::NoFocus);
    this->ui->widget1->setFocusPolicy(Qt::NoFocus);
    this->ui->scrollArea->setFocusPolicy(Qt::NoFocus);

    //----------------------------------------------------------//
    int monthIconWidth  = this->ui->monthForwardButton->width();
    int monthIconHeight = this->ui->monthForwardButton->height();

    this->ui->monthForwardButton->installEventFilter(this);
    this->ui->monthForwardButton->setIcon(QIcon(":/images/ArrowRight.png"));
    this->ui->monthForwardButton->setIconSize(QSize(monthIconWidth, monthIconHeight));
    QString monthForwardButtonStyle = "QPushButton{border: 1px solid white; border-color: rgba(0,0,0,0); border-radius: 5px;}";
    this->ui->monthForwardButton->setStyleSheet(monthForwardButtonStyle);

    this->ui->monthBackwardButton->installEventFilter(this);
    this->ui->monthBackwardButton->setIcon(QIcon(":/images/ArrowLeft.png"));
    this->ui->monthBackwardButton->setIconSize(QSize(monthIconWidth, monthIconHeight));
    QString monthBackwardButtonStyle = "QPushButton{border: 1px solid white; border-color: rgba(0,0,0,0); border-radius: 5px;}";
    this->ui->monthBackwardButton->setStyleSheet(monthBackwardButtonStyle);

    //----------------------------------------------------------//
    int yearIconWidth  = this->ui->monthForwardButton->width();
    int yearIconHeight = this->ui->monthForwardButton->height();

    this->ui->yearForwardButton->installEventFilter(this);
    this->ui->yearForwardButton->setIcon(QIcon(":/images/ArrowRight.png"));
    this->ui->yearForwardButton->setIconSize(QSize(yearIconWidth, yearIconHeight));
    QString yearForwardButtonStyle = "QPushButton{border: 1px solid white; border-color: rgba(0,0,0,0); border-radius: 5px;}";
    this->ui->yearForwardButton->setStyleSheet(yearForwardButtonStyle);

    this->ui->yearBackwardsButton->installEventFilter(this);
    this->ui->yearBackwardsButton->setIcon(QIcon(":/images/ArrowLeft.png"));
    this->ui->yearBackwardsButton->setIconSize(QSize(yearIconWidth, yearIconHeight));
    QString yearBackwardButtonStyle = "QPushButton{border: 1px solid white; border-color: rgba(0,0,0,0); border-radius: 5px;}";
    this->ui->yearBackwardsButton->setStyleSheet(yearBackwardButtonStyle);

    //----------------------------------------------------------//
    int groupIconWidth  = this->ui->monthForwardButton->width();
    int groupIconHeight = this->ui->monthForwardButton->height();

    this->ui->groupForwardButton->installEventFilter(this);
    this->ui->groupForwardButton->setIcon(QIcon(":/images/ArrowRight.png"));
    this->ui->groupForwardButton->setIconSize(QSize(groupIconWidth, groupIconHeight));
    QString groupForwardButtonStyle = "QPushButton{border: 1px solid white; border-color: rgba(0,0,0,0); border-radius: 5px;}";
    this->ui->groupForwardButton->setStyleSheet(groupForwardButtonStyle);

    this->ui->groupBackwardsButton->installEventFilter(this);
    this->ui->groupBackwardsButton->setIcon(QIcon(":/images/ArrowLeft.png"));
    this->ui->groupBackwardsButton->setIconSize(QSize(groupIconWidth, groupIconHeight));
    QString groupBackwardButtonStyle = "QPushButton{border: 1px solid white; border-color: rgba(0,0,0,0); border-radius: 5px;}";
    this->ui->groupBackwardsButton->setStyleSheet(groupBackwardButtonStyle);
    //----------------------------------------------------------//
    this->ui->monthLabel->setAlignment(Qt::AlignCenter);
    this->ui->yearLabel->setAlignment(Qt::AlignCenter);
    this->ui->groupNameLabel->setAlignment(Qt::AlignCenter);


    //----------------------------------------------------------//
    time_t T = time(0);
    struct tm * currentTime = localtime(&T);
    currentYear = (currentTime->tm_year+1900);
    currentMonth = currentTime->tm_mon;
    ui->yearLabel->setText(QString::number(currentYear));

    realWorldYear  = currentYear;
    realWorldMonth = currentMonth;

    //----------------------------------------------------------//
    searchForExistingAccounts();
    if (!AccountsExist)
    {
        if (APP_DIR_FOUND) {//If no account exist, give user option to select language and request account creation.
            requestLanguageDialog languageDialog;
            languageDialog.askUserAboutGuide = false;
            languageDialog.exec();
            initialLanguage = languageDialog.selectedLanguage;
            requestAccountCreation();
        } else {    //If app is being opened for the first time, give user the option to select language and ask if he/she wants to see the user guide.

           requestLanguageDialog languageDialog;
           languageDialog.exec();
           initialLanguage = languageDialog.selectedLanguage;

           if (languageDialog.showHowToUseGuide) {

               //Open guide dialog here!
               UserGuide iUserGuide;
               iUserGuide.setCurrentLanguage(initialLanguage);
               iUserGuide.exec();
               updateUiToLanguage(initialLanguage);
               displayMonthOnLabel();
               requestAccountCreation();

           }
           else {
               updateUiToLanguage(initialLanguage);
               displayMonthOnLabel();
               requestAccountCreation();
           }
        }
    } else if (AccountsExist) {
        if (ListOfExistingAccounts.size() == 1) { //If only one account exists, open and set that account
            ACCOUNT_SET = false;
            CURRENT_SELECTED_ACCOUNT_INDEX_FROM_MANAGER = 0;
            std::vector<std::string>::iterator accountName = ListOfExistingAccounts.begin();
            std::vector<std::string>::iterator accountPath = ListOfExistingAccountsPaths.begin();
            this->requestAccountOpening(*accountName, *accountPath);
        } else if (ListOfExistingAccounts.size() > 1) {
            requestAccountManager();
        }
    }

    this->ui->tableWidget->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    this->ui->tableWidget->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
    this->ui->tableOfGroups->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    this->ui->tableOfGroups->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
    this->ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
    this->ui->tableOfGroups->horizontalHeader()->setStretchLastSection(true);

     if (AccountsExist)
     {
         ThemeColorsDialog iAppearanceDialog;
         //IF CURRENT COLOR THEME IS BIGGER THAN THE NUMBER OF PRESET THEMES, USE CUSTOM THEME (colorConfig Saved on File).
         //numberOfPresetColorsTheme starts from 1, that's why we substract 1.
         if ((iAppearanceDialog.numberOfPresetColorThemes-1) < currentAccount.getAccountCurrentColorTheme())
         {
             //std::cout<<"CURRENT COLOR THEME IS BIGGER THAN THE NUMBER OF PRESET THEMES, USING CUSTOMCOLORCONFIG" <<'\n';
             iAppearanceDialog.addCustomColorConfiguration(currentAccount.getCustomColorConfiguration());
             std::vector<ColorConfiguration>::iterator tempCurrentColorConfigIt = iAppearanceDialog.colorConfigurationList.end()-1;
             this->updateColorsOnScreen(tempCurrentColorConfigIt);
         }

         //ELSE IS CURRENT COLOR THEME IS ONE OF THE PRESETS, COPY FROM THEMECOLORDIALOG THE VALUES OF THE SELECTED PRESET.
         else if ((iAppearanceDialog.numberOfPresetColorThemes-1) >= currentAccount.getAccountCurrentColorTheme())
         {
             //std::cout<<"CURRENT COLOR THEME IS ONE OF THE PRESETS, COPY FROM THEMECOLORDIALOG THE VALUES OF THE SELECTED PRESET" <<'\n';
             std::vector<ColorConfiguration>::iterator tempCurrentColorConfigIt = iAppearanceDialog.colorConfigurationList.begin()
                                                                              +currentAccount.getAccountCurrentColorTheme();
             this->updateColorsOnScreen(tempCurrentColorConfigIt);
         }
     } else if (!AccountsExist)
     {
         ThemeColorsDialog iAppearanceDialog;
         //std::cout<<"NO ACCOUNT EXISTS YET, COPY FROM THEMECOLORDIALOG THE STANDARD COLOR SET" <<'\n';
         std::vector<ColorConfiguration>::iterator tempCurrentColorConfigIt = iAppearanceDialog.colorConfigurationList.begin();
         currentAccount.setAccountCurrentColorTheme(0);
         this->updateColorsOnScreen(tempCurrentColorConfigIt);
     }


     //----------------------------------------------------------//
     //Style sheet for smaller groupboxes inside main GroupBox.
     this->ui->groupBoxAmounts->setStyleSheet("QGroupBox#groupBoxAmounts{border:1px solid gray; border-color:rgb(186, 189, 182); border-radius:0px; border-left-style: rgba(255, 255, 255, 0); border-right-style: rgba(255, 255, 255, 0); border-bottom-style: rgba(255, 255, 255, 0); border-radius : 0px;}");
     this->ui->lineMonthlyBalance->setStyleSheet("QFrame#lineMonthlyBalance{border:1px solid gray; border-color:rgb(186, 189, 182);}");
     this->ui->lineYearlyBalance->setStyleSheet("QFrame#lineYearlyBalance{border:1px solid gray; border-color:rgb(186, 189, 182);}");
     this->ui->lineSeparator->setStyleSheet("QFrame#lineSeparator{border:1px solid gray; border-color:rgb(186, 189, 182);}");
     this->ui->lineSeparator2->setStyleSheet("QFrame#lineSeparator2{border:1px solid gray; border-color:rgb(186, 189, 182);}");

     connect(ui->tableWidget, &QTableWidget::customContextMenuRequested, this, &Gui_KeiboMoneyTracker::showOptionsMenu);
     ui->tableWidget->setSelectionBehavior(QTableWidget::SelectRows);
     ui->tableOfGroups->setSelectionBehavior(QTableWidget::SelectRows);
     ui->tableWidget->setContextMenuPolicy(Qt::CustomContextMenu);
}

Gui_KeiboMoneyTracker::~Gui_KeiboMoneyTracker()
{
    delete ui;
}

void Gui_KeiboMoneyTracker::on_actionAbout_triggered()
{
    AboutDialog iAboutDialog;
    iAboutDialog.exec();
}

bool Gui_KeiboMoneyTracker::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::KeyPress)
    {
        if (qobject_cast<QTableWidget*>(obj) == ui->tableWidget)
        {
            QKeyEvent* key = static_cast<QKeyEvent*>(event);
            if (key->key() == Qt::Key_Enter || (key->key()==Qt::Key_Return))
            {
                this->editSelectedTransaction();
                return true;
            }
            else if (key->key() == Qt::Key_Up)
            {
                int newSelectedRow = ui->tableWidget->currentRow()-1;
                if (newSelectedRow >= 0){
                    TopOfTableReached = false;
                    this->ui->tableWidget->selectRow(newSelectedRow);
                } else if ( (newSelectedRow == 0) && (TopOfTableReached == false) ) {
                    std::cout<<"Row on the bottom REACHED"<<'\n';
                    this->ui->tableWidget->selectRow(newSelectedRow);
                    TopOfTableReached = true;
                }
                return true;
            }
            else if (key->key() == Qt::Key_Down)
            {
                int newSelectedRow = ui->tableWidget->currentRow()+1;
                if (newSelectedRow <= (ui->tableWidget->rowCount()-1)){
                    BottomOfTableReached = false;
                    this->ui->tableWidget->selectRow(newSelectedRow);
                } else if ((newSelectedRow >= (ui->tableWidget->rowCount()-1)) && (BottomOfTableReached == false)) {
                    std::cout<<"Row on the top REACHED"<<'\n';
                    this->ui->tableWidget->selectRow(newSelectedRow);
                    BottomOfTableReached = true;
                }
                return true;
            }
            else if (key->key() == Qt::Key_Right)
            {
                int previousSelectedElement = ui->tableWidget->currentRow();
                std::cout<<"PREVIOUS SELECTED ELEMENT "<<previousSelectedElement<<'\n';
                if (currentMonth>=0 && currentMonth<11) {
                    ++currentMonth;
                    updateToCurrentMonth();
                } else if (currentMonth == 11) {
                    currentMonth = 0;
                    ++currentYear;
                    updateToCurrentYear();
                }
                if (previousSelectedElement > ui->tableWidget->rowCount()-1){
                    std::cout<<"PREVIOUS SELECTED ELEMENT WAS BIGGET THAN CURRENT LIST"<<'\n';
                    this->ui->tableWidget->selectRow(ui->tableWidget->rowCount()-1);
                }
                return true;
            }
            else if (key->key() == Qt::Key_Left)
            {
                int previousSelectedElement = ui->tableWidget->currentRow();
                std::cout<<"PREVIOUS SELECTED ELEMENT "<<previousSelectedElement<<'\n';
                if (currentMonth>0 && currentMonth<=11) {
                   --currentMonth;
                    updateToCurrentMonth();
                } else if (currentMonth == 0) {
                    currentMonth = 11;
                    --currentYear;
                    updateToCurrentYear();
                }                
                if (previousSelectedElement > ui->tableWidget->rowCount()-1){
                    std::cout<<"PREVIOUS SELECTED ELEMENT WAS BIGGET THAN CURRENT LIST"<<'\n';
                    this->ui->tableWidget->selectRow(ui->tableWidget->rowCount()-1);
                }
                return true;
            }
            else if (key->key() == Qt::Key_Delete)
            {
                this->deleteSelectedTransaction();
                return true;
            }
            else if (key->key() == Qt::Key_Tab)
            {
                this->focusNextChild();
                return true;
            }
        }
        else if (qobject_cast<QPushButton*>(obj) == ui->addIncomeButton)
        {
            QKeyEvent* key = static_cast<QKeyEvent*>(event);
            if (key->key() == Qt::Key_Enter || (key->key()==Qt::Key_Return))
            {
                this->addIncome();
            }
        }
        else if (qobject_cast<QPushButton*>(obj) == ui->addExpenseButton)
        {
            QKeyEvent* key = static_cast<QKeyEvent*>(event);
            if (key->key() == Qt::Key_Enter || (key->key()==Qt::Key_Return))
            {
                this->addOutcome();
            }
        }        
        else if (qobject_cast<QPushButton*>(obj) == ui->copyButton)
        {
            QKeyEvent* key = static_cast<QKeyEvent*>(event);
            if (key->key() == Qt::Key_Enter || (key->key()==Qt::Key_Return))
            {
                this->copyTransaction();
            }
        }
        else if (qobject_cast<QPushButton*>(obj) == ui->editItemButton)
        {
            QKeyEvent* key = static_cast<QKeyEvent*>(event);
            if (key->key() == Qt::Key_Enter || (key->key()==Qt::Key_Return))
            {
                this->editSelectedTransaction();
            }
        }
        else if (qobject_cast<QPushButton*>(obj) == ui->deleteItemButton)
        {
            QKeyEvent* key = static_cast<QKeyEvent*>(event);
            if (key->key() == Qt::Key_Enter || (key->key()==Qt::Key_Return))
            {
                deleteSelectedTransaction();
            }
        }

        else if (qobject_cast<QTableWidget*>(obj) == ui->tableOfGroups) //Toggle group types (Income to Outcome and viceversa)
        {
            QKeyEvent* key = static_cast<QKeyEvent*>(event);
            if (key->key() == Qt::Key_Enter || (key->key()==Qt::Key_Return))
            {
                int previousSelectedElement = ui->tableOfGroups->currentRow();
                this->toggle_IncomeOutcomeGroup();
                if (previousSelectedElement > ui->tableOfGroups->rowCount()-1){
                    this->ui->tableOfGroups->selectRow(ui->tableOfGroups->rowCount()-1);
                }
                return true;
            }
            else if (key->key() == Qt::Key_Left)
            {
                int previousSelectedElement = ui->tableOfGroups->currentRow();
                this->goToPreviousGroup();
                if (previousSelectedElement > ui->tableOfGroups->rowCount()-1){
                    this->ui->tableOfGroups->selectRow(ui->tableOfGroups->rowCount()-1);
                }
                return true;
            }
            else if (key->key() == Qt::Key_Right)
            {
                int previousSelectedElement = this->ui->tableOfGroups->currentRow();
                this->goToNextGroup();
                if (previousSelectedElement >= ui->tableOfGroups->rowCount()-1){
                    this->ui->tableOfGroups->selectRow(ui->tableOfGroups->rowCount()-1);
                } else {
                    this->ui->tableOfGroups->selectRow(previousSelectedElement);
                }
                return true;
            }
            else if (key->key() == Qt::Key_Up)
            {
                int newSelectedRow = ui->tableOfGroups->currentRow()-1;
                if (newSelectedRow >= 0){
                    TopOfGroupTableReached = false;
                    this->ui->tableOfGroups->selectRow(newSelectedRow);
                } else if ( (newSelectedRow == 0) && (TopOfGroupTableReached == false) ) {
                    //std::cout<<"Row on the bottom REACHED"<<'\n';
                    this->ui->tableOfGroups->selectRow(newSelectedRow);
                    TopOfGroupTableReached = true;
                }
                return true;
            }
            else if (key->key() == Qt::Key_Down)
            {
                int newSelectedRow = ui->tableOfGroups->currentRow()+1;
                if (newSelectedRow <= (ui->tableOfGroups->rowCount()-1)){
                    BottomOfGroupTableReached = false;
                    this->ui->tableOfGroups->selectRow(newSelectedRow);
                } else if ((newSelectedRow >= (ui->tableOfGroups->rowCount()-1)) && (BottomOfGroupTableReached == false)) {
                    //std::cout<<"Row on the top REACHED"<<'\n';
                    this->ui->tableOfGroups->selectRow(newSelectedRow);
                    BottomOfGroupTableReached = true;
                }
                return true;
            }
        }
    }

    else if (event->type() == QEvent::MouseButtonPress)
    {
        if (qobject_cast<QWidget*>(obj) == ui->widget1) {
                this->updateToClickedMonth();
                if (focusingOverallIncomeExpenses == false){
                    this->focusOverallIncomeExpenses();
                    return true;
            }
        }
        else if (qobject_cast<QLabel*>(obj) == ui->labelAccountIcon){
            this->showAccountStats();
            return true;
        }
        else if (qobject_cast<QWidget*>(obj) == ui->widget_2) {
            this->showGroupsMenu();
            return true;
        }
        else if (qobject_cast<QWidget*>(obj) == ui->addIncomeButton) {
            this->ui->addIncomeButton->setColorForMouseButtonPressEvent();
        }
        else if (qobject_cast<QWidget*>(obj) == ui->addExpenseButton) {
            this->ui->addExpenseButton->setColorForMouseButtonPressEvent();
        }        
        else if (qobject_cast<QWidget*>(obj) == ui->copyButton) {
            this->ui->copyButton->setColorForMouseButtonPressEvent();
        }
        else if (qobject_cast<QWidget*>(obj) == ui->editItemButton) {
            this->ui->editItemButton->setColorForMouseButtonPressEvent();
        }
        else if (qobject_cast<QWidget*>(obj) == ui->deleteItemButton) {
            this->ui->deleteItemButton->setColorForMouseButtonPressEvent();
        }
        else if (qobject_cast<QWidget*>(obj) == ui->pushButtonToggleGroups) {
            this->ui->pushButtonToggleGroups->setColorForMouseButtonPressEvent();
        }
    }

    else if (event->type() == QEvent::MouseButtonRelease)
    {
        if (qobject_cast<QWidget*>(obj) == ui->addIncomeButton) {
            this->ui->addIncomeButton->setColorForEnterEvent();
        }
        else if (qobject_cast<QWidget*>(obj) == ui->addExpenseButton) {
            this->ui->addExpenseButton->setColorForEnterEvent();
        }
        else if (qobject_cast<QWidget*>(obj) == ui->copyButton) {
            this->ui->copyButton->setColorForEnterEvent();
        }
        else if (qobject_cast<QWidget*>(obj) == ui->editItemButton) {
            this->ui->editItemButton->setColorForEnterEvent();
        }
        else if (qobject_cast<QWidget*>(obj) == ui->deleteItemButton) {
            this->ui->deleteItemButton->setColorForEnterEvent();
        }
        else if (qobject_cast<QWidget*>(obj) == ui->pushButtonToggleGroups) {
            this->ui->pushButtonToggleGroups->setColorForEnterEvent();
        }
    }

    else if (event->type() == QEvent::FocusIn)
    {
        if (qobject_cast<QTableWidget*>(obj) == ui->tableWidget){
            if (focusingOverallIncomeExpenses == false){
                this->focusOverallIncomeExpenses();
            }
        }
        else if (qobject_cast<QPushButton*>(obj) == ui->addIncomeButton){
            if (focusingOverallIncomeExpenses == false){
                this->focusOverallIncomeExpenses();
            }
        }
        else if (qobject_cast<QPushButton*>(obj) == ui->addExpenseButton){
            if (focusingOverallIncomeExpenses == false){
                this->focusOverallIncomeExpenses();
            }
        }
        else if (qobject_cast<QPushButton*>(obj) == ui->copyButton){
            if (focusingOverallIncomeExpenses == false){
                this->focusOverallIncomeExpenses();
            }
        }
        else if (qobject_cast<QPushButton*>(obj) == ui->editItemButton){
            if (focusingOverallIncomeExpenses == false){
                this->focusOverallIncomeExpenses();
            }
        }
        else if (qobject_cast<QPushButton*>(obj) == ui->deleteItemButton){
            if (focusingOverallIncomeExpenses == false){
                this->focusOverallIncomeExpenses();
            }
        }        
        else if (qobject_cast<QWidget*>(obj) == ui->widget1){
            if (focusingOverallIncomeExpenses == false){
                this->focusOverallIncomeExpenses();
            }
        }
        else if (qobject_cast<QTableWidget*>(obj) == ui->tableOfGroups){
            if (focusingGroups == false){
                this->focusGroups();
            }
        }
    }

    else if (event->type() == QEvent::FocusOut)
    {
        if (qobject_cast<QTableWidget*>(obj) == ui->tableWidget){
        }
        if (qobject_cast<QPushButton*>(obj) == ui->deleteItemButton){
        }

        if (qobject_cast<QTableWidget*>(obj) == ui->tableOfGroups){
        }
    }

    else if (event->type() == QEvent::Enter)
     {
         if (qobject_cast<QPushButton*>(obj) == ui->monthForwardButton)
         {
             QString buttonStyle = "QPushButton{border: 1px solid white; border-color: rgba(0,0,0,0); background-color:rgba(128, 128, 128, 60); border-radius: 5px;}";
             ui->monthForwardButton->setStyleSheet(buttonStyle);
             return true;
         }
         else if (qobject_cast<QPushButton*>(obj) == ui->monthBackwardButton)
         {
             QString buttonStyle = "QPushButton{border: 1px solid white; border-color: rgba(0,0,0,0); background-color:rgba(128, 128, 128, 60); border-radius: 5px;}";
             ui->monthBackwardButton->setStyleSheet(buttonStyle);
             return true;
         }
         else if (qobject_cast<QPushButton*>(obj) == ui->yearForwardButton)
         {
             QString buttonStyle = "QPushButton{border: 1px solid white; border-color: rgba(0,0,0,0); background-color:rgba(128, 128, 128, 60); border-radius: 5px;}";
             ui->yearForwardButton->setStyleSheet(buttonStyle);
             return true;
         }
         else if (qobject_cast<QPushButton*>(obj) == ui->yearBackwardsButton)
         {
             QString buttonStyle = "QPushButton{border: 1px solid white; border-color: rgba(0,0,0,0); background-color:rgba(128, 128, 128, 60); border-radius: 5px;}";
             ui->yearBackwardsButton->setStyleSheet(buttonStyle);
             return true;
         }
         else if (qobject_cast<QPushButton*>(obj) == ui->groupForwardButton)
         {
             QString buttonStyle = "QPushButton{border: 1px solid white; border-color: rgba(0,0,0,0); background-color:rgba(128, 128, 128, 60); border-radius: 5px;}";
             ui->groupForwardButton->setStyleSheet(buttonStyle);
             return true;
         }
         else if (qobject_cast<QPushButton*>(obj) == ui->groupBackwardsButton)
         {
             QString buttonStyle = "QPushButton{border: 1px solid white; border-color: rgba(0,0,0,0); background-color:rgba(128, 128, 128, 60); border-radius: 5px;}";
             ui->groupBackwardsButton->setStyleSheet(buttonStyle);
             return true;
         }
         else if (qobject_cast<QWidget*>(obj) == ui->addIncomeButton) {
             this->ui->addIncomeButton->setColorForEnterEvent();
         }
         else if (qobject_cast<QWidget*>(obj) == ui->addExpenseButton) {
             this->ui->addExpenseButton->setColorForEnterEvent();
         }
         else if (qobject_cast<QWidget*>(obj) == ui->copyButton) {
             this->ui->copyButton->setColorForEnterEvent();
         }
         else if (qobject_cast<QWidget*>(obj) == ui->editItemButton) {
             this->ui->editItemButton->setColorForEnterEvent();
         }
         else if (qobject_cast<QWidget*>(obj) == ui->deleteItemButton) {
             this->ui->deleteItemButton->setColorForEnterEvent();
         }
         else if (qobject_cast<QWidget*>(obj) == ui->pushButtonToggleGroups) {
             this->ui->pushButtonToggleGroups->setColorForEnterEvent();
         }
     }

    else if (event->type() == QEvent::Leave)
     {
         if (qobject_cast<QPushButton*>(obj) == ui->monthForwardButton)
         {
             QString buttonStyle = "QPushButton{border: 1px solid white; border-color: rgba(0,0,0,0); background-color:rgba(0, 0, 0, 0); border-radius: 5px;}";
             ui->monthForwardButton->setStyleSheet(buttonStyle);
             return true;
         }
         else if (qobject_cast<QPushButton*>(obj) == ui->monthBackwardButton)
         {
             QString buttonStyle = "QPushButton{border: 1px solid white; border-color: rgba(0,0,0,0); background-color:rgba(0, 0, 0, 0); border-radius: 5px;}";
             ui->monthBackwardButton->setStyleSheet(buttonStyle);
             return true;
         }
         else if (qobject_cast<QPushButton*>(obj) == ui->yearForwardButton)
         {
             QString buttonStyle = "QPushButton{border: 1px solid white; border-color: rgba(0,0,0,0); background-color:rgba(0, 0, 0, 0); border-radius: 5px;}";
             ui->yearForwardButton->setStyleSheet(buttonStyle);
             return true;
         }
         else if (qobject_cast<QPushButton*>(obj) == ui->yearBackwardsButton)
         {
             QString buttonStyle = "QPushButton{border: 1px solid white; border-color: rgba(0,0,0,0); background-color:rgba(0, 0, 0, 0); border-radius: 5px;}";
             ui->yearBackwardsButton->setStyleSheet(buttonStyle);
             return true;
         }
         else if (qobject_cast<QPushButton*>(obj) == ui->groupForwardButton)
         {
             QString buttonStyle = "QPushButton{border: 1px solid white; border-color: rgba(0,0,0,0); background-color:rgba(0, 0, 0, 0); border-radius: 5px;}";
             ui->groupForwardButton->setStyleSheet(buttonStyle);
             return true;
         }
         else if (qobject_cast<QPushButton*>(obj) == ui->groupBackwardsButton)
         {
             QString buttonStyle = "QPushButton{border: 1px solid white; border-color: rgba(0,0,0,0); background-color:rgba(0, 0, 0, 0); border-radius: 5px;}";
             ui->groupBackwardsButton->setStyleSheet(buttonStyle);
             return true;
         }
         else if (qobject_cast<QWidget*>(obj) == ui->addIncomeButton) {
             this->ui->addIncomeButton->setColorForLeaveEvent();
         }
         else if (qobject_cast<QWidget*>(obj) == ui->addExpenseButton) {
             this->ui->addExpenseButton->setColorForLeaveEvent();
         }
         else if (qobject_cast<QWidget*>(obj) == ui->copyButton) {
             this->ui->copyButton->setColorForLeaveEvent();
         }
         else if (qobject_cast<QWidget*>(obj) == ui->editItemButton) {
             this->ui->editItemButton->setColorForLeaveEvent();
         }
         else if (qobject_cast<QWidget*>(obj) == ui->deleteItemButton) {
             this->ui->deleteItemButton->setColorForLeaveEvent();
         }
         else if (qobject_cast<QWidget*>(obj) == ui->pushButtonToggleGroups) {
             this->ui->pushButtonToggleGroups->setColorForLeaveEvent();
         }
     }

    else if (event->type() == QEvent::Resize)
     {
        if (qobject_cast<QTableWidget*>(obj) == ui->tableWidget)
        {
            const float tableWidth  = static_cast<float>(ui->tableWidget->width());
            const float nameWidth   = (0.42f)*(tableWidth);
            const float amountWidth = (0.17f)*(tableWidth);
            const float dayWidth    = (0.11f)*(tableWidth);
            ui->tableWidget->setColumnWidth(0,static_cast<int>(nameWidth));
            ui->tableWidget->setColumnWidth(1,static_cast<int>(amountWidth));
            ui->tableWidget->setColumnWidth(2,static_cast<int>(dayWidth));

            if ( (ui->tableWidget->width() > 720 || ui->tableWidget->height() > 650)) {
                if (!usingBiggerFontSize){
                    usingBiggerFontSize = true;
                    QFont fontTable = ui->tableWidget->font();
                    fontTable.setPointSize( 10 );
                    ui->tableWidget->setFont( fontTable );
                    QString tabHeadStyle = ui->tableWidget->horizontalHeader()->styleSheet() + "QHeaderView { font-size: 10pt; }";
                    ui->tableWidget->horizontalHeader()->setStyleSheet(tabHeadStyle);

                    QFont upperMenuFont = ui->menubar->font();
                    upperMenuFont.setPointSize(10);
                    ui->menubar->setFont(upperMenuFont);
                    ui->menuFile->setFont(upperMenuFont);
                    ui->menuEdit->setFont(upperMenuFont);
                    ui->menuOptions->setFont(upperMenuFont);
                    ui->menuHelp->setFont(upperMenuFont);

                    QHeaderView *verticalHeader = ui->tableWidget->verticalHeader();
                    verticalHeader->setDefaultSectionSize(26);

                    QFont font = ui->tableOfGroups->font();
                    font.setPointSize( 9 );
                    ui->tableOfGroups->setFont( font );
                    tabHeadStyle = ui->tableOfGroups->horizontalHeader()->styleSheet() + "QHeaderView { font-size: 9pt; }";
                    ui->tableOfGroups->horizontalHeader()->setStyleSheet(tabHeadStyle);
                    verticalHeader = ui->tableOfGroups->verticalHeader();
                    verticalHeader->setDefaultSectionSize(22);
                }
            } else {
                usingBiggerFontSize = false;
                QFont fontTable = ui->tableWidget->font();
                fontTable.setPointSize( 9 );
                ui->tableWidget->setFont( fontTable );
                QString tabHeadStyle = ui->tableWidget->horizontalHeader()->styleSheet() + "QHeaderView { font-size: 9pt; }";
                ui->tableWidget->horizontalHeader()->setStyleSheet(tabHeadStyle);
                QFont upperMenuFont = ui->menubar->font();
                upperMenuFont.setPointSize(9);
                ui->menubar->setFont(upperMenuFont);
                ui->menuFile->setFont(upperMenuFont);
                ui->menuEdit->setFont(upperMenuFont);
                ui->menuOptions->setFont(upperMenuFont);
                ui->menuHelp->setFont(upperMenuFont);

                QHeaderView *verticalHeader = ui->tableWidget->verticalHeader();
                verticalHeader->setDefaultSectionSize(23);

                QFont font = ui->tableOfGroups->font();
                font.setPointSize( 8 );
                ui->tableOfGroups->setFont( font );
                tabHeadStyle = ui->tableOfGroups->horizontalHeader()->styleSheet() + "QHeaderView { font-size: 8pt; }";
                ui->tableOfGroups->horizontalHeader()->setStyleSheet(tabHeadStyle);
                verticalHeader = ui->tableOfGroups->verticalHeader();
                verticalHeader->setDefaultSectionSize(20);
            }

        }
        else if (qobject_cast<QTableWidget*>(obj) == ui->tableOfGroups)
        {
            const float tableWidth  = static_cast<float>(ui->tableOfGroups->width());
            const float nameWidth   = (0.34f)*(tableWidth);
            const float amountWidth = (0.16f)*(tableWidth);
            const float dayWidth    = (0.08f)*(tableWidth);
            ui->tableOfGroups->setColumnWidth(0,static_cast<int>(nameWidth));
            ui->tableOfGroups->setColumnWidth(1,static_cast<int>(amountWidth));
            ui->tableOfGroups->setColumnWidth(2,static_cast<int>(dayWidth));
        }
     }
    return false;
}

void Gui_KeiboMoneyTracker::showOptionsMenu(const QPoint &pos)
{
    if (ACCOUNT_SET)
    {
        QString menuStyle;
        if (usingDarkTheme) {
            menuStyle = "QMenu{color: rgb(200,200,200); background-color: rgb(60,60,60);} QMenu::item:selected {background-color: rgb(130,130,130);}";
        } else {
            menuStyle = "QMenu{color: rgb(60,60,60); background-color: rgb(230,230,230);} QMenu::item:selected {background-color: rgb(180,180,180);}";
        }

        QMenu optionsMenu;
        optionsMenu.setWindowOpacity(0.9);
        optionsMenu.setStyleSheet(menuStyle);

        if (currentAccount.getAccountLanguage() == ENGLISH) {
            optionsMenu.addAction("Copy");
            optionsMenu.addAction("Edit");
        } else if (currentAccount.getAccountLanguage() == GERMAN) {
            optionsMenu.addAction("Kopieren");
            optionsMenu.addAction("Ändern");
        } else if (currentAccount.getAccountLanguage() == SPANISH) {
            optionsMenu.addAction("Copiar");
            optionsMenu.addAction("Editar");
        }

        QTableWidgetItem *item = ui->tableWidget->itemAt(pos);
        if(item != nullptr)
        {
            int i = item->row();
            ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
            ui->tableWidget->selectRow(i);
            ui->tableWidget->setSelectionMode(QAbstractItemView::ExtendedSelection);
        }

        connect(&optionsMenu, SIGNAL(triggered(QAction*)), this, SLOT(optionsMenuSelection(QAction*)));

        optionsMenu.exec(QCursor::pos());
    }
}

void Gui_KeiboMoneyTracker::optionsMenuSelection(QAction * action)  //Call only if account is set
{
    std::string actionName = action->text().toStdString();
    if (currentAccount.getAccountLanguage() == ENGLISH) {
        if (actionName == "Copy"){
            copyTransaction();
            return;
        } editSelectedTransaction();
    } else if (currentAccount.getAccountLanguage() == GERMAN) {
        if (actionName == "Kopieren"){
            copyTransaction();
            return;
        } editSelectedTransaction();
    } else if (currentAccount.getAccountLanguage() == SPANISH) {
        if (actionName == "Copiar"){
            copyTransaction();
            return;
        } editSelectedTransaction();
    }
}

void Gui_KeiboMoneyTracker::showGroupsMenu()
{
    if (ACCOUNT_SET)
    {
        QString menuStyle;
        if (usingDarkTheme) {
            menuStyle = "QMenu{color: rgb(200,200,200); background-color: rgb(60,60,60);} QMenu::item:selected {background-color: rgb(130,130,130);}";
        } else {
            menuStyle = "QMenu{color: rgb(60,60,60); background-color: rgb(230,230,230);} QMenu::item:selected {background-color: rgb(180,180,180);}";
        }

        QMenu incomeGroupsMenu;
        for (std::vector<std::string>::iterator incomeGroupIt = currentAccount.IncomeGroupsNames.begin();
             incomeGroupIt != currentAccount.IncomeGroupsNames.end(); ++ incomeGroupIt){
            incomeGroupsMenu.addAction(QString::fromStdString(*incomeGroupIt));
        }
        incomeGroupsMenu.setStyleSheet(menuStyle);
        incomeGroupsMenu.setWindowOpacity(0.9);

        QMenu expensesGroupsMenu;
        for (std::vector<std::string>::iterator expensesGroupIt = currentAccount.ExpensesGroupsNames.begin();
             expensesGroupIt != currentAccount.ExpensesGroupsNames.end(); ++ expensesGroupIt){
            expensesGroupsMenu.addAction(QString::fromStdString(*expensesGroupIt));
        }
        expensesGroupsMenu.setStyleSheet(menuStyle);
        expensesGroupsMenu.setWindowOpacity(0.9);

        if (currentAccount.getAccountLanguage() == ENGLISH) {
            incomeGroupsMenu.setTitle("Income Groups");
            expensesGroupsMenu.setTitle("Expenses Groups");
        } else if (currentAccount.getAccountLanguage() == GERMAN) {
            incomeGroupsMenu.setTitle("Gruppen Einkommen");
            expensesGroupsMenu.setTitle("Gruppen Ausgaben");
        } else if (currentAccount.getAccountLanguage() == SPANISH) {
            incomeGroupsMenu.setTitle("Grupos de ingresos");
            expensesGroupsMenu.setTitle("Grupos de egresos");
        }

        connect(&incomeGroupsMenu, SIGNAL(triggered(QAction*)), this, SLOT(incomeGroupSelection(QAction*)));
        connect(&expensesGroupsMenu, SIGNAL(triggered(QAction*)), this, SLOT(expensesGroupSelection(QAction*)));

        QMenu groupsMenu;
        groupsMenu.setWindowOpacity(0.9);
        groupsMenu.addMenu(&incomeGroupsMenu);
        groupsMenu.addMenu(&expensesGroupsMenu);
        groupsMenu.setStyleSheet(menuStyle);

        groupsMenu.exec(QCursor::pos());
    }
}

void Gui_KeiboMoneyTracker::incomeGroupSelection(QAction *action)
{
    std::string groupName = action->text().toStdString();
    int groupId = 0;
    for (std::vector<std::string>::iterator incomeGroupIt = currentAccount.IncomeGroupsNames.begin();
         incomeGroupIt != currentAccount.IncomeGroupsNames.end(); ++ incomeGroupIt){
        if (groupName == *incomeGroupIt) {
            showIncome = true;
            currentIncomeGroupSelected = groupId;
            this->updateGroups();
            this->updateListOfGroups();
        }
        ++groupId;
    }
}

void Gui_KeiboMoneyTracker::expensesGroupSelection(QAction *action)
{
    std::string groupName = action->text().toStdString();
    int groupId = 0;
    for (std::vector<std::string>::iterator expensesGroupIt = currentAccount.ExpensesGroupsNames.begin();
         expensesGroupIt != currentAccount.ExpensesGroupsNames.end(); ++ expensesGroupIt){
        if (groupName == *expensesGroupIt) {
            showIncome = false;
            currentGroupSelected = groupId;
            this->updateGroups();
            this->updateListOfGroups();
        }
        ++groupId;
    }
}

void Gui_KeiboMoneyTracker::focusOverallIncomeExpenses()
{
    this->ui->tableWidget->setFocus();

    this->ui->groupBoxOverall->setStyleSheet("QGroupBox{border:2px solid gray; border-color:rgb(135, 190, 193); border-radius:5px; margin-top: 0.5em;}"
                                             "QGroupBox::title {subcontrol-origin: margin; subcontrol-position: top center; padding: 0px 5px 0px 5px;}");
    this->ui->groupBoxMain->setStyleSheet("QGroupBox{border:2px solid gray; border-color:rgb(135, 190, 193); border-radius:5px; margin-top: 0.5em; }");
    this->ui->groupBoxGroups->setStyleSheet("QGroupBox{border:1px solid gray; border-color:rgb(186, 189, 182); border-radius:5px; margin-top: 0.5em;}"
                                            "QGroupBox::title {subcontrol-origin: margin; subcontrol-position: top center; padding: 0px 5px 0px 5px;}");

    focusingOverallIncomeExpenses = true;
    focusingGroups = false;
}

void Gui_KeiboMoneyTracker::focusGroups()
{
    this->ui->tableOfGroups->setFocus();

    this->ui->groupBoxOverall->setStyleSheet("QGroupBox{border:1px solid gray; border-color:rgb(186, 189, 182); border-radius:5px; margin-top: 0.5em;}"
                                             "QGroupBox::title {subcontrol-origin: margin; subcontrol-position: top center; padding: 0px 5px 0px 5px;}");
    this->ui->groupBoxMain->setStyleSheet("QGroupBox{border:1px solid gray; border-color:rgb(186, 189, 182); border-radius:5px; margin-top: 0.5em; }");
    this->ui->groupBoxGroups->setStyleSheet("QGroupBox{border:2px solid gray; border-color:rgb(135, 190, 193); border-radius:5px; margin-top: 0.5em;}"
                                            "QGroupBox::title {subcontrol-origin: margin; subcontrol-position: top center; padding: 0px 5px 0px 5px;}");

    focusingGroups = true;
    focusingOverallIncomeExpenses = false;
}

void Gui_KeiboMoneyTracker::updateToCurrentYear() //Updates also to the selected month
{
    ui->yearLabel->setText(QString::number(currentYear));
    currentAccount.set_Year(currentYear);
    if (ACCOUNT_SET) {
        displayMonthOnLabel();
        currentAccount.clear_Year();
        bool yearDataExists = currentAccount.load_Data();

        if (yearDataExists && (currentAccount.allTransactionsOk == false)){
            eraseConfirmation_dialog eraseConfirmationWindow;
            eraseConfirmationWindow.setModal(true);
            eraseConfirmationWindow.setOverallThemeStyleSheet(currentOverallThemeStyleSheet, usingDarkTheme);
            if (currentAccount.getAccountLanguage() == ENGLISH)            {
                eraseConfirmationWindow.setWindowTitle(" Information");
                eraseConfirmationWindow.setInfoText("The data file for the current year has been externally modified. Please verify the following transactions.");
            } else if (currentAccount.getAccountLanguage() == GERMAN) {
                eraseConfirmationWindow.setWindowTitle(" Information");
                eraseConfirmationWindow.setInfoText("Die Datei für das gewählte Jahr wurde gerändert. Bitte prüfen Sie die folgenden Transaktionen.");
            } else if (currentAccount.getAccountLanguage() == SPANISH) {
                eraseConfirmationWindow.setWindowTitle(" Información");
                eraseConfirmationWindow.setInfoText("El archivo de datos del año seleccionado ha sido externamente modificado. Por favor verifique las siguientes transacciones.");
            }
            eraseConfirmationWindow.exec();

            //Gather data to be passed to checkFaultyTransactionData
            std::vector<Transaction> listOfFaultyTransactions;
            for (unsigned int i = 0; i != currentAccount.listOfFaultyTransactionsInfo.size(); ++i){
                listOfFaultyTransactions.push_back(currentAccount.Yearly_Articles
                                                       [currentAccount.listOfFaultyTransactionsInfo[i].month]
                                                       [currentAccount.listOfFaultyTransactionsInfo[i].id]
                                                      );
            }

            //Delete all faulty transactions
            for (int xmonth = 0; xmonth != 12; ++xmonth){
                std::vector<int> elementsToDelete;
                for (unsigned int i = 0; i != currentAccount.listOfFaultyTransactionsInfo.size(); ++i){
                    if(currentAccount.listOfFaultyTransactionsInfo[i].month == xmonth ){
                        elementsToDelete.push_back(currentAccount.listOfFaultyTransactionsInfo[i].id);
                    }
                }
                if (elementsToDelete.size()>0){
                    currentAccount.deleteMultipleTransactionsInMonth(xmonth, elementsToDelete);
                }
            }

            //Set data on checkFaultyTransactionsDialog
            checkFaultyTransactionsDialog checkTransactionsDialog;
            checkTransactionsDialog.setModal(true);
            checkTransactionsDialog.setLanguage(currentAccount.getAccountLanguage());
            checkTransactionsDialog.getFaultyTransactionsData(listOfFaultyTransactions, currentAccount.getYear());
            checkTransactionsDialog.getGroups(currentAccount.IncomeGroupsNames, currentAccount.ExpensesGroupsNames);
            checkTransactionsDialog.updateInfo();
            checkTransactionsDialog.setOverallThemeStyleSheet(currentOverallThemeStyleSheet, usingDarkTheme);
            checkTransactionsDialog.exec();

            //Get updated data
            std::vector<Transaction> listOfUpdatedTransactions;
            checkTransactionsDialog.provideUpdatedTransactions(listOfUpdatedTransactions);
            if (listOfUpdatedTransactions.size()>0){
                std::vector<Transaction>::iterator itUpdatedTransactions;
                for (itUpdatedTransactions = listOfUpdatedTransactions.begin(); itUpdatedTransactions != listOfUpdatedTransactions.end(); ++itUpdatedTransactions)
                {
                    this->currentAccount.addTransaction(*itUpdatedTransactions);
                }
                this->currentAccount.save_Data();
            }
        }

        displayArticlesOnTable();
        updateGraph();
        updateGroups();
        updateListOfGroups();
    }
}

void Gui_KeiboMoneyTracker::updateToCurrentMonth()
{
    this->displayMonthOnLabel();
    if (ACCOUNT_SET) {
        this->displayArticlesOnTable();
        this->updateGraph();
    }
}

void Gui_KeiboMoneyTracker::updateColorsOnScreen(std::vector<ColorConfiguration>::iterator currentColorConfigIt)
{
    ui->widget1->activationCounterBarBackgroundColor = 0;
    ui->widget1->setBarWidgetColors(currentColorConfigIt->colorBarIncomeSelected,
                                   currentColorConfigIt->colorBarIncomeUnselected,
                                   currentColorConfigIt->colorBarExpensesSelected,
                                   currentColorConfigIt->colorBarExpensesUnselected,
                                   currentColorConfigIt->colorBarBackground);
    ui->widget1->update();

    ui->widget_2->setGroupWidgetColors(currentColorConfigIt->colorGroupIncomeSelected,
                                       currentColorConfigIt->colorGroupIncomeUnselected,
                                       currentColorConfigIt->colorGroupExpensesSelected,
                                       currentColorConfigIt->colorGroupExpensesUnselected,
                                       currentColorConfigIt->colorGroupIncomeBackground,
                                       currentColorConfigIt->colorGroupExpensesBackground);
    ui->widget_2->update();

    colorOfIncomeAmount = currentColorConfigIt->colorTableIncomeAmount;
    if (currentColorConfigIt->showMonthlyAmountsInColor)
    {
        ///INCOME
        int r= 0, g = 0, b= 0;
        getColorCode(currentColorConfigIt->colorBarIncomeSelected, r, g, b);
        ui->monthlyIncomeLabel->setStyleSheet("QLabel{color: rgb("+
                                              QString::number(r)+
                                              ","+
                                              QString::number(g)+
                                              ","+
                                              QString::number(b)+
                                              ");}");
        ///EXPENSES
        getColorCode(currentColorConfigIt->colorBarExpensesSelected, r, g, b);
        ui->monthlyExpendituresLabel->setStyleSheet("QLabel{color: rgb("+
                                              QString::number(r)+
                                              ","+
                                              QString::number(g)+
                                              ","+
                                              QString::number(b)+
                                              ");}");
    } else if (!currentColorConfigIt->showMonthlyAmountsInColor){
        currentColorConfigIt->setOverallThemeColors();
        int r= 0, g = 0, b= 0;
        getColorCode(currentColorConfigIt->colorOverallText, r, g, b);
        ///INCOME
        ui->monthlyIncomeLabel->setStyleSheet("QLabel{color: rgb("+
                                              QString::number(r)+
                                              ","+
                                              QString::number(g)+
                                              ","+
                                              QString::number(b)+
                                              ");}");
        ///EXPENSES
        ui->monthlyExpendituresLabel->setStyleSheet("QLabel{color: rgb("+
                                              QString::number(r)+
                                              ","+
                                              QString::number(g)+
                                              ","+
                                              QString::number(b)+
                                              ");}");
    }

    ///--------------------------------------------------------------------------///--------------------------------------------------------------------------///
    //Set color for Overall background, text, buttons and borders depending on theme's value (Light/Dark).
    int r_OB= 0, g_OB = 0, b_OB= 0;
    getColorCode(currentColorConfigIt->colorOverallBackground, r_OB, g_OB, b_OB);
    QString overallBackgroundColor = "rgb("+   //Overall background
                                     QString::number(r_OB)+
                                     ","+
                                     QString::number(g_OB)+
                                     ","+
                                     QString::number(b_OB)+
                                     ");";

    getColorCode(currentColorConfigIt->colorOverallText, r_OB, g_OB, b_OB);
    QString overallTextColor = "color: rgb("+   //Overall Text
            QString::number(r_OB)+
            ","+
            QString::number(g_OB)+
            ","+
            QString::number(b_OB)+
            ");";
    currentOverallThemeStyleSheet = "background-color:"+overallBackgroundColor+overallTextColor;
    usingDarkTheme = currentColorConfigIt->useDarkOverallTheme;
    tablesStyleSheet = "QTableCornerButton::section {background-color:"+overallBackgroundColor + "border-radius : 6px; }"
                       "QTableWidget{border: 1px solid gray; background-color: "+ overallBackgroundColor+" border-radius : 3px;}";

    ui->tableWidget->setStyleSheet(tablesStyleSheet);
    ui->tableOfGroups->setStyleSheet(tablesStyleSheet);

    horizontalHeaderStyleSheet = "QHeaderView::section { background-color:"+ overallBackgroundColor+" border-radius : 0px; border-bottom: 1px solid gray; }";
    ui->tableWidget->horizontalHeader()->setStyleSheet(horizontalHeaderStyleSheet);
    ui->tableOfGroups->horizontalHeader()->setStyleSheet(horizontalHeaderStyleSheet);

    verticalHeaderStyleSheet = "QHeaderView::section {background-color:"+ overallBackgroundColor+" border-radius : 6px;}";
    ui->tableWidget->verticalHeader()->setStyleSheet(verticalHeaderStyleSheet);
    ui->tableOfGroups->verticalHeader()->setStyleSheet(verticalHeaderStyleSheet);

    ui->tableWidget->verticalHeader()->setDefaultAlignment(Qt::AlignBottom | Qt::AlignmentFlag::AlignHCenter);
    ui->tableOfGroups->verticalHeader()->setDefaultAlignment(Qt::AlignBottom | Qt::AlignmentFlag::AlignHCenter);


    ui->tableWidget->verticalScrollBar()->setStyleSheet(
                "QScrollBar:vertical { width: 15px; margin: 0px 0px 0px 0px;}"
                "QScrollBar::add-line:vertical { border: none; background: none;}"
                "QScrollBar::sub-line:vertical { border: none; background: none;}"
                "QScrollBar::handle:vertical {background: rgb(32, 47, 130), min-height: 0px;}");
    ui->tableOfGroups->verticalScrollBar()->setStyleSheet(
                "QScrollBar:vertical { width: 15px; margin: 0px 0px 0px 0px;}"
                "QScrollBar::add-line:vertical { border: none; background: none;}"
                "QScrollBar::sub-line:vertical { border: none; background: none;}");
    ui->tableOfGroups->horizontalScrollBar()->setStyleSheet(
                "QScrollBar:horizontal { width: 15px; margin: 0px 0px 0px 0px;}"
                "QScrollBar::add-line:horizontal { border: none; background: none;}"
                "QScrollBar::sub-line:horizontal { border: none; background: none;}");

    this->setStyleSheet(currentOverallThemeStyleSheet);

    this->ui->addIncomeButton->updateColorTheme(usingDarkTheme);
    this->ui->addExpenseButton->updateColorTheme(usingDarkTheme);
    this->ui->editItemButton->updateColorTheme(usingDarkTheme);
    this->ui->copyButton->updateColorTheme(usingDarkTheme);
    this->ui->deleteItemButton->updateColorTheme(usingDarkTheme);
    this->ui->pushButtonToggleGroups->updateColorTheme(usingDarkTheme);


    ///--------------------------------------------------------------------------///--------------------------------------------------------------------------///
    //Style sheet for menus.
    QString menuStyle;
    if (usingDarkTheme) {
        menuStyle = "QMenu{color: rgb(200,200,200); background-color: rgb(60,60,60);} QMenu::item:selected {background-color: rgb(130,130,130);}";
    } else {
        menuStyle = "QMenu{color: rgb(60,60,60); background-color: rgb(230,230,230);} QMenu::item:selected {background-color: rgb(180,180,180);}";
    }
    this->ui->menuFile->setStyleSheet(menuStyle);
    this->ui->menuEdit->setStyleSheet(menuStyle);
    this->ui->menuOptions->setStyleSheet(menuStyle);
    this->ui->menuHelp->setStyleSheet(menuStyle);
}

void Gui_KeiboMoneyTracker::on_actionAppearance_triggered() //TAB Renamed to "Appearance"
{
    if (ACCOUNT_SET == true)
    {
        std::cout<<"OPENNING APPEARANCE 1" <<'\n';
        ThemeColorsDialog iAppearanceDialog;
        iAppearanceDialog.setLanguage(currentAccount.getAccountLanguage());
        iAppearanceDialog.setModal(true);

        iAppearanceDialog.addCustomColorConfiguration(currentAccount.customColorConfiguration); // A vector::push_back is done here.Add here config found in Properties.txt
        iAppearanceDialog.currentColorTheme = currentAccount.getAccountCurrentColorTheme(); //Specify here which of the colorConfigs is being used.
        iAppearanceDialog.setCurrentColorConfiguration(); //Set values
        iAppearanceDialog.exec();

        if (iAppearanceDialog.colorSelectionConfirmed)
        {   //Temporary variables to store color coming from Appearance-Dialog-Widgets
            std::cout<<"iAppearanceDialog.currentColorTheme "<<iAppearanceDialog.currentColorTheme<<'\n';
            currentAccount.setAccountCurrentColorTheme(iAppearanceDialog.currentColorTheme);
            std::vector<ColorConfiguration>::iterator tempCurrentColorConfigIt = iAppearanceDialog.colorConfigurationList.begin()
                                                                             +currentAccount.getAccountCurrentColorTheme();
            this->updateColorsOnScreen(tempCurrentColorConfigIt);

            //ATTENTION!!! getAccountCurrentColorTheme starts from 0 while numberOfPresetColorThemes starts from 1 .
            if (currentAccount.getAccountCurrentColorTheme() == iAppearanceDialog.numberOfPresetColorThemes)
            {
                currentAccount.setCustomColorElements(tempCurrentColorConfigIt->colorBarIncomeSelected,
                                             tempCurrentColorConfigIt->colorBarIncomeUnselected,
                                             tempCurrentColorConfigIt->colorBarExpensesSelected,
                                             tempCurrentColorConfigIt->colorBarExpensesUnselected,
                                             tempCurrentColorConfigIt->colorBarBackground,
                                             tempCurrentColorConfigIt->colorGroupIncomeSelected,
                                             tempCurrentColorConfigIt->colorGroupIncomeUnselected,
                                             tempCurrentColorConfigIt->colorGroupExpensesSelected,
                                             tempCurrentColorConfigIt->colorGroupExpensesUnselected,
                                             tempCurrentColorConfigIt->colorGroupIncomeBackground,
                                             tempCurrentColorConfigIt->colorGroupExpensesBackground,
                                             tempCurrentColorConfigIt->colorTableIncomeAmount,
                                             tempCurrentColorConfigIt->showMonthlyAmountsInColor,
                                             tempCurrentColorConfigIt->useDarkOverallTheme);
            }
            currentAccount.saveAccountProperties();  //it saves custom colors on file
            this->displayArticlesOnTable();
        }
    }
    else {
        eraseConfirmation_dialog iAccountCreationConfirmedDialog;
        iAccountCreationConfirmedDialog.setModal(true);
        iAccountCreationConfirmedDialog.setOverallThemeStyleSheet(currentOverallThemeStyleSheet, usingDarkTheme);
        if (initialLanguage == ENGLISH) {
            iAccountCreationConfirmedDialog.setWindowTitle(" Information");
            iAccountCreationConfirmedDialog.setInfoText("Please create or select an account first.");
        } else if (initialLanguage == GERMAN) {
            iAccountCreationConfirmedDialog.setWindowTitle(" Information");
            iAccountCreationConfirmedDialog.setInfoText("Bitte erstellen/wählen Sie zuerst ein Konto.");
        } else if (initialLanguage == SPANISH) {
            iAccountCreationConfirmedDialog.setWindowTitle(" Información");
            iAccountCreationConfirmedDialog.setInfoText("Por favor cree o seleccione una cuenta primero.");
        }
        iAccountCreationConfirmedDialog.exec();
    }
}

void Gui_KeiboMoneyTracker::on_actionNew_triggered()
{
    requestAccountCreation();
}

void Gui_KeiboMoneyTracker::on_actionOpen_triggered()
{
    searchForExistingAccounts();
    if (AccountsExist)
    {
        requestAccountManager();
    } else {
        requestAccountCreation();
    }
}

void Gui_KeiboMoneyTracker::setCurrentAccount() //CALL ONLY AFTER LOADING ACCOUNT PROPERTIES
{
   currentAccount.clear_Year();
   currentAccount.loadExpensesGroups();
   currentAccount.loadIncomeGroups();
   currentAccount.set_Year(currentYear);
   bool yearDataExists = currentAccount.load_Data();

   if (yearDataExists && (currentAccount.allTransactionsOk == false)){
       eraseConfirmation_dialog eraseConfirmationWindow;
       eraseConfirmationWindow.setModal(true);
       eraseConfirmationWindow.setOverallThemeStyleSheet(currentOverallThemeStyleSheet, usingDarkTheme);
       if (currentAccount.getAccountLanguage() == ENGLISH)            {
           eraseConfirmationWindow.setWindowTitle(" Information");
           eraseConfirmationWindow.setInfoText("The data file for the current year has been externally modified. Please verify the following transactions.");
       } else if (currentAccount.getAccountLanguage() == GERMAN) {
           eraseConfirmationWindow.setWindowTitle(" Information");
           eraseConfirmationWindow.setInfoText("Die Datei für das gewählte Jahr wurde gerändert. Bitte prüfen Sie die folgenden Transaktionen.");
       } else if (currentAccount.getAccountLanguage() == SPANISH) {
           eraseConfirmationWindow.setWindowTitle(" Información");
           eraseConfirmationWindow.setInfoText("El archivo de datos del año seleccionado ha sido externamente modificado. Por favor verifique las siguientes transacciones.");
       }
       eraseConfirmationWindow.exec();

       //Gather data to be passed to checkFaultyTransactionData
       std::vector<Transaction> listOfFaultyTransactions;
       for (unsigned int i = 0; i != currentAccount.listOfFaultyTransactionsInfo.size(); ++i){
           listOfFaultyTransactions.push_back(currentAccount.Yearly_Articles
                                                  [currentAccount.listOfFaultyTransactionsInfo[i].month]
                                                  [currentAccount.listOfFaultyTransactionsInfo[i].id]
                                                 );
       }

       //Delete all faulty transactions
       for (int xmonth = 0; xmonth != 12; ++xmonth){
           std::vector<int> elementsToDelete;
           for (unsigned int i = 0; i != currentAccount.listOfFaultyTransactionsInfo.size(); ++i){
               if(currentAccount.listOfFaultyTransactionsInfo[i].month == xmonth ){
                   elementsToDelete.push_back(currentAccount.listOfFaultyTransactionsInfo[i].id);
               }
           }
           if (elementsToDelete.size()>0){
               currentAccount.deleteMultipleTransactionsInMonth(xmonth, elementsToDelete);
           }
       }

       //Set data on checkFaultyTransactionsDialog
       checkFaultyTransactionsDialog checkTransactionsDialog;
       checkTransactionsDialog.setModal(true);
       checkTransactionsDialog.setLanguage(currentAccount.getAccountLanguage());
       checkTransactionsDialog.getFaultyTransactionsData(listOfFaultyTransactions, currentAccount.getYear());
       checkTransactionsDialog.getGroups(currentAccount.IncomeGroupsNames, currentAccount.ExpensesGroupsNames);
       checkTransactionsDialog.updateInfo();
       checkTransactionsDialog.setOverallThemeStyleSheet(currentOverallThemeStyleSheet, usingDarkTheme);
       checkTransactionsDialog.exec();

       //Get updated data
       std::vector<Transaction> listOfUpdatedTransactions;
       checkTransactionsDialog.provideUpdatedTransactions(listOfUpdatedTransactions);
       if (listOfUpdatedTransactions.size()>0){
           std::vector<Transaction>::iterator itUpdatedTransactions;
           for (itUpdatedTransactions = listOfUpdatedTransactions.begin(); itUpdatedTransactions != listOfUpdatedTransactions.end(); ++itUpdatedTransactions)
           {
               this->currentAccount.addTransaction(*itUpdatedTransactions);
           }
       }
   }

   std::vector<Transaction> newElementsAddedAutomatically;   
   currentAccount.setElementsToRepeat(newElementsAddedAutomatically);

       currentAccount.save_Data();

       ThemeColorsDialog iAppearanceDialog;
       //IF CURRENT COLOR THEME IS BIGGER THAN THE NUMBER OF PRESET THEMES, USE CUSTOM THEME (colorConfig Saved on File).
       //numberOfPresetColorsTheme starts from 1, that's why we substract 1.
       if ((iAppearanceDialog.numberOfPresetColorThemes-1) < currentAccount.getAccountCurrentColorTheme())
       {
           iAppearanceDialog.addCustomColorConfiguration(currentAccount.getCustomColorConfiguration());
           std::vector<ColorConfiguration>::iterator tempCurrentColorConfigIt = iAppearanceDialog.colorConfigurationList.end()-1;
           this->updateColorsOnScreen(tempCurrentColorConfigIt);
       }
       //ELSE IS CURRENT COLOR THEME IS ONE OF THE PRESETS, COPY FROM THEMECOLORDIALOG THE VALUES OF THE SELECTED PRESET.
       else if ((iAppearanceDialog.numberOfPresetColorThemes-1) >= currentAccount.getAccountCurrentColorTheme())
       {
           std::vector<ColorConfiguration>::iterator tempCurrentColorConfigIt = iAppearanceDialog.colorConfigurationList.begin()
                                                                            +currentAccount.getAccountCurrentColorTheme();
           this->updateColorsOnScreen(tempCurrentColorConfigIt);
       }

       displayArticlesOnTable();
       updateUiToLanguage(currentAccount.getAccountLanguage());
       initialLanguage = currentAccount.getAccountLanguage();
       displayMonthOnLabel();
       ACCOUNT_SET = true;

       ///Show to user new elements added automatically by repetition if any.
       if (newElementsAddedAutomatically.size() > 0){
           newElementsAddedAutomaticallyDialog iNewElementsAddedAutomatically;
           iNewElementsAddedAutomatically.setModal(true);
           iNewElementsAddedAutomatically.setLanguage(currentAccount.getAccountLanguage());
           iNewElementsAddedAutomatically.getInfoToDisplay(newElementsAddedAutomatically,
                                                           currentAccount.IncomeGroupsNames,
                                                           currentAccount.ExpensesGroupsNames,
                                                           colorOfIncomeAmount,
                                                           currentAccount.getAccountLanguage());
           iNewElementsAddedAutomatically.setOverallThemeStyleSheet(currentOverallThemeStyleSheet, usingDarkTheme);
           iNewElementsAddedAutomatically.exec();
       }

       if ( showIncome  && //When first opening account, show first income group with transactions
            currentAccount.getTotalNumberOfIncomeTransactionsInGroup(currentIncomeGroupSelected) == 0 &&
            currentAccount.getTotalIncomeInYear() > 0.0)
       {
           for (size_t group = 0; group != currentAccount.IncomeGroupsNames.size(); ++group){
               if (currentAccount.IncomeGroupsAmounts[group] != 0.0){
                   break;
               }
               currentIncomeGroupSelected++;
           }
       }

       updateGraph();
       updateGroups();
       updateListOfGroups();

}

void Gui_KeiboMoneyTracker::updateUiToLanguage(const Language &iLanguage)
{
    if (iLanguage == ENGLISH){
        this->ui->groupBoxOverall->setTitle("Income/Expenses");
        if (showIncome){
            ui->groupBoxGroups->setTitle("Income Groups");
        }
        else if (!showIncome) {
            ui->groupBoxGroups->setTitle("Expenses Groups");
        }
        this->ui->addIncomeButton->setText("Add income");
        this->ui->addExpenseButton->setText("Add expense");
        this->ui->copyButton->setText("Copy");
        this->ui->editItemButton->setText("Edit");
        this->ui->deleteItemButton->setText("Delete");
        this->ui->labelTotalYearIncomeText->setText("Total income in year:");
        this->ui->labelTotalYearExpensesText->setText("Total expenses in year:");
        this->ui->labelTotalMonthIncomeText->setText("Total income in month:");
        this->ui->labelTotalMonthExpensesText->setText("Total expenses in month:");
        this->ui->pushButtonToggleGroups->setText("Income/Expenses");
        this->ui->menuFile->setTitle("File");
        this->ui->actionNew->setText("New");
        this->ui->actionOpen->setText("Open");
        this->ui->actionExit->setText("Exit");
        this->ui->menuEdit->setTitle("Edit");
        this->ui->actionManage_Groups->setText("Expenses groups");
        this->ui->actionManage_Income_Groups->setText("Income groups");
        this->ui->menuOptions->setTitle("Options");
        this->ui->actionAppearance->setText("Appareance");
        this->ui->menuHelp->setTitle("Help");
        this->ui->actionHow_to_use->setText("How to use");
        this->ui->actionAbout->setText("About");
        this->ui->actionDonate->setText("Donate");
        WeeklyPhrases weeklyPhrase;
        this->ui->labelPhrase->setText(QString::fromStdString(weeklyPhrase.getPhraseOfTheWeek(ENGLISH)));
    }
    else if (iLanguage == GERMAN){
        this->ui->groupBoxOverall->setTitle("Einkommen/Ausgaben");
        if (showIncome){
            ui->groupBoxGroups->setTitle("Gruppen Einkommen");
        }
        else if (!showIncome) {
            ui->groupBoxGroups->setTitle("Gruppen Ausgaben");
        }
        this->ui->addIncomeButton->setText("Einkommen");
        this->ui->addExpenseButton->setText("Ausgabe");
        this->ui->copyButton->setText("Kopieren");
        this->ui->editItemButton->setText("Ändern");
        this->ui->deleteItemButton->setText("Löschen");
        this->ui->labelTotalYearIncomeText->setText("Jahreseinkommen:");
        this->ui->labelTotalYearExpensesText->setText("Jahresausgabe:");
        this->ui->labelTotalMonthIncomeText->setText("Monatliches Einkommen:");
        this->ui->labelTotalMonthExpensesText->setText("Monatliche Ausgabe:");
        this->ui->pushButtonToggleGroups->setText("Einkommen/Ausgaben");
        this->ui->menuFile->setTitle("Datei");
        this->ui->actionNew->setText("Neu");
        this->ui->actionOpen->setText("Öffnen");
        this->ui->actionExit->setText("Beenden");
        this->ui->menuEdit->setTitle("Bearbeiten");
        this->ui->actionManage_Groups->setText("Gruppen Ausgaben");
        this->ui->actionManage_Income_Groups->setText("Gruppen Einkommen");
        this->ui->menuOptions->setTitle("Optionen");
        this->ui->actionAppearance->setText("Ansicht");
        this->ui->menuHelp->setTitle("Hilfe");
        this->ui->actionHow_to_use->setText("Benutzungserklärung");
        this->ui->actionAbout->setText("Über");
        this->ui->actionDonate->setText("Spenden");
        WeeklyPhrases weeklyPhrase;
        this->ui->labelPhrase->setText(QString::fromStdString(weeklyPhrase.getPhraseOfTheWeek(GERMAN)));
    }
    else if (iLanguage == SPANISH){
        this->ui->groupBoxOverall->setTitle("Ingresos/Egresos");
        if (showIncome){
            ui->groupBoxGroups->setTitle("Grupos de ingresos");
        }
        else if (!showIncome) {
            ui->groupBoxGroups->setTitle("Grupos de egresos");
        }
        this->ui->addIncomeButton->setText("Ingreso");
        this->ui->addExpenseButton->setText("Egreso");
        this->ui->copyButton->setText("Copiar");
        this->ui->editItemButton->setText("Editar");
        this->ui->deleteItemButton->setText("Eliminar");
        this->ui->labelTotalYearIncomeText->setText("Ingreso en el año:");
        this->ui->labelTotalYearExpensesText->setText("Egreso en el año:");
        this->ui->labelTotalMonthIncomeText->setText("Ingreso en el mes:");
        this->ui->labelTotalMonthExpensesText->setText("Egreso en el mes:");
        this->ui->pushButtonToggleGroups->setText("Ingresos/Egresos");
        this->ui->menuFile->setTitle("Archivo");
        this->ui->actionNew->setText("Nuevo");
        this->ui->actionOpen->setText("Abrir");
        this->ui->actionExit->setText("Salir");
        this->ui->menuEdit->setTitle("Editar");
        this->ui->actionManage_Groups->setText("Grupos de egresos");
        this->ui->actionManage_Income_Groups->setText("Grupos de ingresos");
        this->ui->menuOptions->setTitle("Opciones");
        this->ui->actionAppearance->setText("Apariencia");
        this->ui->menuHelp->setTitle("Ayuda");
        this->ui->actionHow_to_use->setText("Como usar");
        this->ui->actionAbout->setText("Acerca de");
        this->ui->actionDonate->setText("Donar");
        WeeklyPhrases weeklyPhrase;
        this->ui->labelPhrase->setText(QString::fromStdString(weeklyPhrase.getPhraseOfTheWeek(SPANISH)));
        this->ui->labelPhrase->setWordWrap(true);
    }
}

void Gui_KeiboMoneyTracker::verifyAccountInfo(std::string &accountName, std::string &accountPath)
{
    QDir accountDir(QString::fromStdString(accountPath));
    //Show information
    eraseConfirmation_dialog iAccountCreationConfirmedDialog;
    if (currentAccount.getAccountLanguage() == ENGLISH)            {
        iAccountCreationConfirmedDialog.setWindowTitle(" Information");
        iAccountCreationConfirmedDialog.setInfoText("Files for this account have been externally modified. Please verify the account information.");
    } else if (currentAccount.getAccountLanguage() == GERMAN) {
        iAccountCreationConfirmedDialog.setWindowTitle(" Information");
        iAccountCreationConfirmedDialog.setInfoText("Dateien für dieses Konto wurden geändert. Bitte prüfen Sie die Kontoinformation.");
    } else if (currentAccount.getAccountLanguage() == SPANISH) {
        iAccountCreationConfirmedDialog.setWindowTitle(" Información");
        iAccountCreationConfirmedDialog.setInfoText("Archivos de esta cuenta han sido externamente modificados. Por favor verifique la información de cuenta.");
    }
    iAccountCreationConfirmedDialog.setModal(true);
    iAccountCreationConfirmedDialog.setOverallThemeStyleSheet(currentOverallThemeStyleSheet, usingDarkTheme);
    iAccountCreationConfirmedDialog.exec();

    //Faulty Properties have to be loaded again, in case a good account was previously opened. Values of current opened account have to be cleaned.
    if (CURRENT_SELECTED_ACCOUNT > -1){ //If an Account was previously opened, clear previous property values.
        std::cout<<"ACCOUNT WAS PREVIOUSLY OPENED, CLEARING PROPERTY VALUES"<<'\n';
        this->currentAccount.clearAccountProperties(true);
        this->currentAccount.loadAccountProperties(accountName,accountPath);
    }

    //Fill Account dialog with information that could be gathered
    std::string tempAccountName         = currentAccount.getAccountName();
    short int tempAccountLanguage       = static_cast<short int>(currentAccount.getAccountLanguage());
    short int tempAccountCurrency       = static_cast<short int>(currentAccount.getAccountCurrency());
    unsigned int tempAccountColorTheme  = currentAccount.getAccountCurrentColorTheme();
    std::string tempAccountImagePath    = currentAccount.getAccountIconPath();
    AccountDialog iAccountDialog;
    iAccountDialog.setToVerifyAccount();
    iAccountDialog.setLanguageList(currentAccount.getLanguageList());
    iAccountDialog.setCurrencyList(currentAccount.getCurrencyList());
    iAccountDialog.receiveAccountProperties(tempAccountName,
                                            tempAccountLanguage,
                                            tempAccountCurrency,
                                            tempAccountImagePath);
    iAccountDialog.getExistingAccounts(ListOfExistingAccounts);
    iAccountDialog.setOverallThemeStyleSheet(currentOverallThemeStyleSheet, usingDarkTheme);

    iAccountDialog.exec();
    //There is a pause at this point for Gui_KeiboMoneyTracker. Waiting for dialog to be closed
    if (iAccountDialog.creationConfirmed)
    {
        iAccountDialog.provideAccountProperties(tempAccountName,
                                                tempAccountLanguage,
                                                tempAccountCurrency);

        // If Account name was changed Change/ReSet name of Account folder and path for AccountImage
        if (accountName != tempAccountName) {
            accountDir.rename(QString::fromStdString(accountPath),
                              AppDir.absolutePath()+QString::fromStdString("/KMT_"+tempAccountName));
            accountPath = AppDir.absolutePath().toStdString()+"/KMT_"+tempAccountName;
        }

        if (iAccountDialog.imageWasSelected()) {
            iAccountDialog.saveImageToAccountPath(accountPath);
            iAccountDialog.provideAccountImagePath(tempAccountImagePath);
        } else if (iAccountDialog.imageWasSelected() == false) {
            QFile imageFile (QString::fromStdString(tempAccountImagePath));
            if (imageFile.exists()){
                imageFile.remove();
                tempAccountImagePath = "No Image Selected";
            }
        }
        currentAccount.clearAccountProperties(false);
        currentAccount.setAccountProperties(tempAccountName,
                                  accountPath,
                                  tempAccountImagePath,
                                  static_cast<Language>(tempAccountLanguage),
                                  static_cast<Currency>(tempAccountCurrency),
                                  tempAccountColorTheme);
        currentAccount.saveAccountProperties();

        eraseConfirmation_dialog iAccountCreationConfirmedDialog;
        if (currentAccount.getAccountLanguage() == ENGLISH)            {
            iAccountCreationConfirmedDialog.setWindowTitle(" Information");
            iAccountCreationConfirmedDialog.setInfoText("Account information updated.");
        } else if (currentAccount.getAccountLanguage() == GERMAN) {
            iAccountCreationConfirmedDialog.setWindowTitle(" Information");
            iAccountCreationConfirmedDialog.setInfoText("Konto Daten wurden aktualisiert.");
        } else if (currentAccount.getAccountLanguage() == SPANISH) {
            iAccountCreationConfirmedDialog.setWindowTitle(" Información");
            iAccountCreationConfirmedDialog.setInfoText("Información de cuenta actualizada.");
        }
        iAccountCreationConfirmedDialog.setModal(true);
        iAccountCreationConfirmedDialog.setOverallThemeStyleSheet(currentOverallThemeStyleSheet, usingDarkTheme);
        iAccountCreationConfirmedDialog.exec();

        this->setCurrentAccount();
        this->setWindowTitle(QString("  ") + QString::fromStdString(tempAccountName));

        if (currentAccount.hasProfileImage()){
            QImage srcImg(QString::fromStdString(tempAccountImagePath));
            QPixmap imagePixmap = QPixmap::fromImage(srcImg);
            int w = ui->labelAccountIcon->width();
            int h = ui->labelAccountIcon->height();
            ui->labelAccountIcon->setPixmap(imagePixmap.scaled(w, h, Qt::KeepAspectRatio, Qt::SmoothTransformation));
            ui->labelAccountIcon->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        }
        CURRENT_SELECTED_ACCOUNT = CURRENT_SELECTED_ACCOUNT_INDEX_FROM_MANAGER;
        std::cout<<"CURRENT SELECTED AFTER EDITION: "<<CURRENT_SELECTED_ACCOUNT<<'\n';
    } else {
        eraseConfirmation_dialog iAccountCreationConfirmedDialog;
        if (currentAccount.getAccountLanguage() == ENGLISH)            {
            iAccountCreationConfirmedDialog.setWindowTitle(" Information");
            iAccountCreationConfirmedDialog.setInfoText("Process canceled.");
        } else if (currentAccount.getAccountLanguage() == GERMAN) {
            iAccountCreationConfirmedDialog.setWindowTitle(" Information");
            iAccountCreationConfirmedDialog.setInfoText("Prozess abgebrochen.");
        } else if (currentAccount.getAccountLanguage() == SPANISH) {
            iAccountCreationConfirmedDialog.setWindowTitle(" Información");
            iAccountCreationConfirmedDialog.setInfoText("Proceso cancelado.");
        }
        iAccountCreationConfirmedDialog.setModal(true);
        iAccountCreationConfirmedDialog.setOverallThemeStyleSheet(currentOverallThemeStyleSheet, usingDarkTheme);
        iAccountCreationConfirmedDialog.exec();

        if (CURRENT_SELECTED_ACCOUNT > -1){ //Allow enableling of controls only if an account has already been set
                std::cout<<"CURRENT SELECTED AFTER CANCELED EDITION: "<<CURRENT_SELECTED_ACCOUNT<<'\n';
                std::string pathOfCurrentSelectedAccount = ListOfExistingAccountsPaths[CURRENT_SELECTED_ACCOUNT];
                std::string nameOfCurrentSelectedAccount = ListOfExistingAccounts[CURRENT_SELECTED_ACCOUNT];
                bool accountPropertiesExist = currentAccount.loadAccountProperties(nameOfCurrentSelectedAccount,pathOfCurrentSelectedAccount);
                if(accountPropertiesExist) //change to if(accountPropertiesOk) THIS VERIFIES THAT Properties are GOOD!!!
                {
                    this->setCurrentAccount();
                    this->setWindowTitle(QString("  ") + QString::fromStdString(currentAccount.getAccountName()));
                    if (currentAccount.hasProfileImage()){
                        QImage srcImg(QString::fromStdString(currentAccount.getAccountIconPath()));
                        QPixmap imagePixmap = QPixmap::fromImage(srcImg);
                        int w = ui->labelAccountIcon->width();
                        int h = ui->labelAccountIcon->height();
                        ui->labelAccountIcon->setPixmap(imagePixmap.scaled(w, h, Qt::KeepAspectRatio, Qt::SmoothTransformation));
                        ui->labelAccountIcon->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
                    }
                }
           }
    }
}

void Gui_KeiboMoneyTracker::requestAccountOpening(std::string &accountName, std::string &accountPath)
{
    //In case a good account was previously opened. Values of previously opened account have to be cleaned.
    if (CURRENT_SELECTED_ACCOUNT > -1){
        //std::cout<<"ACCOUNT WAS PREVIOUSLY OPENED, CLEARING PROPERTY VALUES"<<'\n';
        this->currentAccount.clearAccountProperties(true);
    }
    bool accountPropertiesOk = currentAccount.loadAccountProperties(accountName, accountPath);

    if(accountPropertiesOk)
    {
        std::cout<<"ACCOUNT OPENED - PROPERTIES ARE OK"<<'\n';
        this->setCurrentAccount();
        this->setWindowTitle(QString("  ") + QString::fromStdString(currentAccount.getAccountName()));
        CURRENT_SELECTED_ACCOUNT = CURRENT_SELECTED_ACCOUNT_INDEX_FROM_MANAGER;
        if (currentAccount.hasProfileImage()){
            QImage srcImg(QString::fromStdString(currentAccount.getAccountIconPath()));
            QPixmap imagePixmap = QPixmap::fromImage(srcImg);
            int w = ui->labelAccountIcon->width();
            int h = ui->labelAccountIcon->height();
            ui->labelAccountIcon->setPixmap(imagePixmap.scaled(w, h, Qt::KeepAspectRatio, Qt::SmoothTransformation));
            ui->labelAccountIcon->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        }
    } else{
        std::cout<<"ACCOUNT NOT OPENED BECAUSE PROPERTIES ARE NOK \n PLEASE CHECK ACCOUNT INFORMATION"<<'\n';
        this->verifyAccountInfo(accountName, accountPath);
    }
}

void Gui_KeiboMoneyTracker::requestAccountEditing(std::string &accountName, std::string &accountPath)
{
    QDir accountDir(QString::fromStdString(accountPath));
    bool accountPropertiesOk = currentAccount.loadAccountProperties(accountName, accountPath);
    if (accountPropertiesOk)
    {
        std::string tempAccountName         = currentAccount.getAccountName();
        short int tempAccountLanguage       = static_cast<short int>(currentAccount.getAccountLanguage());
        short int tempAccountCurrency       = static_cast<short int>(currentAccount.getAccountCurrency());
        unsigned int tempAccountColorTheme  = currentAccount.getAccountCurrentColorTheme(); //TO BE USED
        std::string tempAccountImagePath    = currentAccount.getAccountIconPath();

        AccountDialog iAccountDialog;
        iAccountDialog.setToEditAccount();
        iAccountDialog.setLanguageList(currentAccount.getLanguageList());
        iAccountDialog.setCurrencyList(currentAccount.getCurrencyList());
        iAccountDialog.receiveAccountProperties(tempAccountName,
                                                tempAccountLanguage,
                                                tempAccountCurrency,
                                                tempAccountImagePath);
        iAccountDialog.getExistingAccounts(ListOfExistingAccounts);
        iAccountDialog.setOverallThemeStyleSheet(currentOverallThemeStyleSheet, usingDarkTheme);

        //iAccountDialog.setModal(true);
        iAccountDialog.exec();
        //There is a pause at this point for Gui_KeiboMoneyTracker. Waiting for dialog to be closed
        if (iAccountDialog.creationConfirmed)
        {
            iAccountDialog.provideAccountProperties(tempAccountName,
                                                    tempAccountLanguage,
                                                    tempAccountCurrency);
            // If Account name was changed Change/ReSet name of Account folder and path for AccountImage
            if (accountName != tempAccountName) {
                accountDir.rename(QString::fromStdString(accountPath),
                                  AppDir.absolutePath()+QString::fromStdString("/KMT_"+tempAccountName));
                accountPath = AppDir.absolutePath().toStdString()+"/KMT_"+tempAccountName;
            }

            if (iAccountDialog.imageWasSelected()) {
                iAccountDialog.saveImageToAccountPath(accountPath);
                iAccountDialog.provideAccountImagePath(tempAccountImagePath);
            } else if (iAccountDialog.imageWasSelected() == false) {
                QFile imageFile (QString::fromStdString(tempAccountImagePath));
                if (imageFile.exists()){
                    imageFile.remove();
                    tempAccountImagePath = "No Image Selected";
                }
            }

            currentAccount.clearAccountProperties(false);
            currentAccount.setAccountProperties(tempAccountName,
                                      accountPath,
                                      tempAccountImagePath,
                                      static_cast<Language>(tempAccountLanguage),
                                      static_cast<Currency>(tempAccountCurrency),
                                      tempAccountColorTheme);
            currentAccount.saveAccountProperties();
            currentAccount.updateDefaultGroupsToCurrentLanguage();//---------------------------

            eraseConfirmation_dialog iAccountCreationConfirmedDialog;
            if (currentAccount.getAccountLanguage() == ENGLISH){
                iAccountCreationConfirmedDialog.setWindowTitle(" Information");
                iAccountCreationConfirmedDialog.setInfoText("Account information updated.");
            } else if (currentAccount.getAccountLanguage() == GERMAN){
                iAccountCreationConfirmedDialog.setWindowTitle(" Information");
                iAccountCreationConfirmedDialog.setInfoText("Kontoinformation wurde aktualisiert.");
            } else if (currentAccount.getAccountLanguage() == SPANISH){
                iAccountCreationConfirmedDialog.setWindowTitle(" Información");
                iAccountCreationConfirmedDialog.setInfoText("Información de cuenta actualizada.");
            }
            iAccountCreationConfirmedDialog.setModal(true);
            iAccountCreationConfirmedDialog.setOverallThemeStyleSheet(currentOverallThemeStyleSheet, usingDarkTheme);
            iAccountCreationConfirmedDialog.exec();

            this->setCurrentAccount();
            this->setWindowTitle(QString("  ") + QString::fromStdString(tempAccountName));

            if (currentAccount.hasProfileImage()){
                QImage srcImg(QString::fromStdString(tempAccountImagePath));
                QPixmap imagePixmap = QPixmap::fromImage(srcImg);
                int w = ui->labelAccountIcon->width();
                int h = ui->labelAccountIcon->height();
                ui->labelAccountIcon->setPixmap(imagePixmap.scaled(w, h, Qt::KeepAspectRatio, Qt::SmoothTransformation));
                ui->labelAccountIcon->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
            }
            CURRENT_SELECTED_ACCOUNT = CURRENT_SELECTED_ACCOUNT_INDEX_FROM_MANAGER;
            std::cout<<"CURRENT SELECTED AFTER EDITION: "<<CURRENT_SELECTED_ACCOUNT<<'\n';
        } else {
            eraseConfirmation_dialog iAccountCreationConfirmedDialog;
            if (currentAccount.getAccountLanguage() == ENGLISH){
                iAccountCreationConfirmedDialog.setWindowTitle(" Information");
                iAccountCreationConfirmedDialog.setInfoText("No changes were made.");
            } else if (currentAccount.getAccountLanguage() == GERMAN){
                iAccountCreationConfirmedDialog.setWindowTitle(" Information");
                iAccountCreationConfirmedDialog.setInfoText("Keine Änderung wurde gemacht.");
            } else if (currentAccount.getAccountLanguage() == SPANISH){
                iAccountCreationConfirmedDialog.setWindowTitle(" Información");
                iAccountCreationConfirmedDialog.setInfoText("No se realizó ningún cambio.");
            }
            iAccountCreationConfirmedDialog.setModal(true);
            iAccountCreationConfirmedDialog.setOverallThemeStyleSheet(currentOverallThemeStyleSheet, usingDarkTheme);
            iAccountCreationConfirmedDialog.exec();

            if (CURRENT_SELECTED_ACCOUNT > -1){ //Allow enableling of controls only if an account has already been set
                    std::cout<<"CURRENT SELECTED AFTER CANCELED EDITION: "<<CURRENT_SELECTED_ACCOUNT<<'\n';
                    std::string pathOfCurrentSelectedAccount = ListOfExistingAccountsPaths[CURRENT_SELECTED_ACCOUNT];
                    std::string nameOfCurrentSelectedAccount = ListOfExistingAccounts[CURRENT_SELECTED_ACCOUNT];
                    bool accountPropertiesExist = currentAccount.loadAccountProperties(nameOfCurrentSelectedAccount,pathOfCurrentSelectedAccount);
                    if(accountPropertiesExist) //change to if(accountPropertiesOk) THIS VERIFIES THAT Properties are GOOD!!!
                    {
                        this->setCurrentAccount();
                        this->setWindowTitle(QString("  ") + QString::fromStdString(currentAccount.getAccountName()));
                        if (currentAccount.hasProfileImage()){
                            QImage srcImg(QString::fromStdString(currentAccount.getAccountIconPath()));
                            QPixmap imagePixmap = QPixmap::fromImage(srcImg);
                            int w = ui->labelAccountIcon->width();
                            int h = ui->labelAccountIcon->height();
                            ui->labelAccountIcon->setPixmap(imagePixmap.scaled(w, h, Qt::KeepAspectRatio, Qt::SmoothTransformation));
                            ui->labelAccountIcon->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
                        }
                    }
               }
        }
    } else {
            std::cout<<"ACCOUNT NOT OPENED BECAUSE PROPERTIES ARE NOK \n PLEASE CHECK ACCOUNT INFORMATION"<<'\n';
            this->verifyAccountInfo(accountName, accountPath);
    }
}
void Gui_KeiboMoneyTracker::requestAccountDeletion(std::string &accountName, std::string &accountPath)
{
    eraseConfirmation_dialog iDeletionDialog;
    if (currentAccount.getAccountLanguage() == ENGLISH)            {
        iDeletionDialog.setWindowTitle(" Delete Account");
        iDeletionDialog.setInfoText("Are you sure you want to delete the account "+accountName+" ?");
    } else if (currentAccount.getAccountLanguage() == GERMAN) {
        iDeletionDialog.setWindowTitle(" Konto löschen");
        iDeletionDialog.setInfoText("Möchten Sie das Konto "+accountName+ " wirklich löschen?");
    } else if (currentAccount.getAccountLanguage() == SPANISH) {
        iDeletionDialog.setWindowTitle(" Eliminar cuenta");
        iDeletionDialog.setInfoText("¿En realidad desea eliminar la cuenta "+accountName+ " ?");
    }
    iDeletionDialog.setModal(true);
    iDeletionDialog.setOverallThemeStyleSheet(currentOverallThemeStyleSheet, usingDarkTheme);
    iDeletionDialog.exec();

    if (iDeletionDialog.comfirmed())
    {
        ACCOUNT_SET = false;
        QDir accountDir(QString::fromStdString(accountPath));
        accountDir.removeRecursively();

        //If account-deleted is the same account as current (if one account was already opened and it is being seen) clean current data.

        if (CURRENT_SELECTED_ACCOUNT == CURRENT_SELECTED_ACCOUNT_INDEX_FROM_MANAGER)
        {
            currentAccount.clearAccountProperties(true);
            currentAccount.clear_Year();  //->CHeck!
            updateGraph();  //Check if necessary, it may be done in updateColorsOnScreen
            updateGroups(); //Check if necessary, it may be done in updateColorsOnScreen
            updateListOfGroups();
            displayArticlesOnTable();
            ui->labelAccountIcon->clear();
            this->setWindowTitle(QString("  "));
            std::cout<<"CURRENT_SELECTED_ACCOUNT EQUAL TO SELECTED INDEX= "<<CURRENT_SELECTED_ACCOUNT<<'\n';
        } else if (CURRENT_SELECTED_ACCOUNT != CURRENT_SELECTED_ACCOUNT_INDEX_FROM_MANAGER) {//Else if account-deleted is a different account to the current

        }

        searchForExistingAccounts();
        if (!AccountsExist)
        {
            requestAccountCreation();
        } else if (AccountsExist) {
            if (CURRENT_SELECTED_ACCOUNT != CURRENT_SELECTED_ACCOUNT_INDEX_FROM_MANAGER)
            {
                if (CURRENT_SELECTED_ACCOUNT > -1){ //Allow enableling of controls only if an account has already been set
                    ACCOUNT_SET = true;
                    std::cout<<"AN ACCOUNT WAS ALREADY OPENED & KEEPS BEING SET= "<<'\n';
                }
                if (CURRENT_SELECTED_ACCOUNT > CURRENT_SELECTED_ACCOUNT_INDEX_FROM_MANAGER){
                    CURRENT_SELECTED_ACCOUNT-=1;
                    std::cout<<"CURRENT_SELECTED_ACCOUNT IS BIGGER THAN SELECTED INDEX, -1 = "<<CURRENT_SELECTED_ACCOUNT<<'\n';
                }
            }
            requestAccountManager();
        }
        std::cout<<"CURRENT_SELECTED_ACCOUNT FINAL= "<<CURRENT_SELECTED_ACCOUNT<<'\n';
    } else {        
        //searchForExistingAccounts();
        if (!AccountsExist)
        {
            requestAccountCreation();
        } else if (AccountsExist) {
            if (CURRENT_SELECTED_ACCOUNT > -1){ //Allow enableling of controls only if an account has already been set
                ACCOUNT_SET = true;
            }
            requestAccountManager();
        }
    }
}

void Gui_KeiboMoneyTracker::requestAccountCreation()
{
    //If after checking existing accounts, no account is found => Then open AccountCreationDialog
    //A new account must be created.
        AccountDialog iAccountDialog;
        iAccountDialog.setToCreateAccount();
        //Fill up Lists (comboBoxes) with available options for language, currency and colorTheme
        iAccountDialog.setLanguageList(currentAccount.getLanguageList());
        iAccountDialog.setCurrencyList(currentAccount.getCurrencyList());
        iAccountDialog.getExistingAccounts(ListOfExistingAccounts);
        iAccountDialog.setOverallThemeStyleSheet(currentOverallThemeStyleSheet, usingDarkTheme);

        iAccountDialog.setInitialLanguage(initialLanguage);

        iAccountDialog.exec();
        //There is a pause at this point for Gui_KeiboMoneyTracker. Waiting for dialog to be closed
        std::string tempAccountName      = "";
        short int tempAccountLanguage    = 0;
        short int tempAccountCurrency    = 0;
        unsigned int tempAccountColorTheme  = 0;  //DURING CREATION ALWAYS SET TO ZERO
        std::string tempAccountImagePath = "No Image Selected";

        ///OPTIMIZE THIS PART!!!!!!!!
        if (iAccountDialog.creationConfirmed)
        {
            iAccountDialog.provideAccountProperties(tempAccountName,
                                                    tempAccountLanguage,
                                                    tempAccountCurrency);

            AppDir.mkdir(QString::fromStdString("KMT_"+tempAccountName));
            std::string accountPath = AppDir.absolutePath().toStdString()+"/KMT_"+tempAccountName;
            if (iAccountDialog.imageWasSelected()) {
                iAccountDialog.saveImageToAccountPath(accountPath);
                iAccountDialog.provideAccountImagePath(tempAccountImagePath);
            }
            //std::cout<<"COLOR THEME ACCOUNT CREATION "<<tempAccountColorTheme<<'\n';
            currentAccount.clearAccountProperties(true);
            currentAccount.setAccountProperties(tempAccountName,
                                      accountPath,
                                      tempAccountImagePath,
                                      static_cast<Language>(tempAccountLanguage),
                                      static_cast<Currency>(tempAccountCurrency),
                                      tempAccountColorTheme);
            currentAccount.saveAccountProperties();

            eraseConfirmation_dialog iAccountCreationConfirmedDialog;
            if (currentAccount.getAccountLanguage() == ENGLISH){
                iAccountCreationConfirmedDialog.setWindowTitle(" Information");
                iAccountCreationConfirmedDialog.setInfoText("Account Created.");
            } else if (currentAccount.getAccountLanguage() == GERMAN){
                iAccountCreationConfirmedDialog.setWindowTitle(" Information");
                iAccountCreationConfirmedDialog.setInfoText("Konto wurde erstellt.");
            } else if (currentAccount.getAccountLanguage() == SPANISH){
                iAccountCreationConfirmedDialog.setWindowTitle(" Información");
                iAccountCreationConfirmedDialog.setInfoText("Cuenta creada.");
            }
            iAccountCreationConfirmedDialog.setModal(true);
            iAccountCreationConfirmedDialog.setOverallThemeStyleSheet(currentOverallThemeStyleSheet, usingDarkTheme);
            iAccountCreationConfirmedDialog.exec();

            this->setCurrentAccount(); //Sets ACCOUNT_SET = true;
            CURRENT_SELECTED_ACCOUNT = ListOfExistingAccounts.size(); //It is zero because even if an account was just created List of existing accounts hasn't been pushed back by searchForExistingAccounts

            this->setWindowTitle(QString("  ") + QString::fromStdString(tempAccountName));
            if (currentAccount.hasProfileImage()){
                QImage srcImg(QString::fromStdString(tempAccountImagePath));
                QPixmap imagePixmap = QPixmap::fromImage(srcImg);
                int w = ui->labelAccountIcon->width();
                int h = ui->labelAccountIcon->height();
                ui->labelAccountIcon->setPixmap(imagePixmap.scaled(w, h, Qt::KeepAspectRatio, Qt::SmoothTransformation));
                ui->labelAccountIcon->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
            }
        } else {
            eraseConfirmation_dialog iAccountCreationConfirmedDialog;
            if (initialLanguage == ENGLISH){
                iAccountCreationConfirmedDialog.setWindowTitle(" Information");
                iAccountCreationConfirmedDialog.setInfoText("Account Creation Canceled.");
            } else if (initialLanguage == GERMAN){
                iAccountCreationConfirmedDialog.setWindowTitle(" Information");
                iAccountCreationConfirmedDialog.setInfoText("Konto Erstellung wurde abgebrochen.");
            } else if (initialLanguage == SPANISH){
                iAccountCreationConfirmedDialog.setWindowTitle(" Información");
                iAccountCreationConfirmedDialog.setInfoText("Creación de cuenta cancelada.");
            }
            iAccountCreationConfirmedDialog.setModal(true);
            iAccountCreationConfirmedDialog.setOverallThemeStyleSheet(currentOverallThemeStyleSheet, usingDarkTheme);
            iAccountCreationConfirmedDialog.exec();

            std::cout<<"CURRENT SELECTED AFTER CANCELING  CREATION: "<<CURRENT_SELECTED_ACCOUNT<<'\n';
            if (AccountsExist)
            {
                if (CURRENT_SELECTED_ACCOUNT > -1){ //Restore of controls only if an account has already been set
                    std::string pathOfSelectedAccount = ListOfExistingAccountsPaths[CURRENT_SELECTED_ACCOUNT];
                    std::string nameOfSelectedAccount = ListOfExistingAccounts[CURRENT_SELECTED_ACCOUNT];
                    bool accountPropertiesExist = currentAccount.loadAccountProperties(nameOfSelectedAccount,pathOfSelectedAccount);
                    if(accountPropertiesExist) //change to if(accountPropertiesOk) THIS VERIFIES THAT Properties are GOOD!!!
                    {
                        this->setCurrentAccount();
                        this->setWindowTitle(QString("  ") + QString::fromStdString(currentAccount.getAccountName()));
                        if (currentAccount.hasProfileImage()){
                            QImage srcImg(QString::fromStdString(currentAccount.getAccountIconPath()));
                            QPixmap imagePixmap = QPixmap::fromImage(srcImg);
                            int w = ui->labelAccountIcon->width();
                            int h = ui->labelAccountIcon->height();
                            ui->labelAccountIcon->setPixmap(imagePixmap.scaled(w, h, Qt::KeepAspectRatio, Qt::SmoothTransformation));
                            ui->labelAccountIcon->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
                        }
                    }
                }
            }

        }
}

void Gui_KeiboMoneyTracker::requestAccountManager()
{
    //Else if there is at least one account (folder and properties file), open AccountManagerDialog
        AccountManagerDialog iAccountManagerDialog;
        iAccountManagerDialog.setModal(true);
        iAccountManagerDialog.setWindowTitle(QString("  "));
        iAccountManagerDialog.setOverallThemeStyleSheet(currentOverallThemeStyleSheet);
        iAccountManagerDialog.fillListWithExistingAccounts(ListOfExistingAccounts,
                                                           ListOfExistingAccountsPaths);
        //Retrieve Account Information from Dialog here.
        iAccountManagerDialog.exec();

        //Check which option was selected by user and call corresponding function
                if (iAccountManagerDialog.OpenAccount)
                {
                    ACCOUNT_SET = false;
                    //Get selected account name from manager and set it.
                    iAccountManagerDialog.provideSelectedAccountIdIndex(CURRENT_SELECTED_ACCOUNT_INDEX_FROM_MANAGER);
                    std::vector<std::string>::iterator accountName = ListOfExistingAccounts.begin()+CURRENT_SELECTED_ACCOUNT_INDEX_FROM_MANAGER;
                    std::vector<std::string>::iterator accountPath = ListOfExistingAccountsPaths.begin()+CURRENT_SELECTED_ACCOUNT_INDEX_FROM_MANAGER;
                    this->requestAccountOpening(*accountName, *accountPath);
                }
                else if (iAccountManagerDialog.EditAccount)
                {
                    ACCOUNT_SET = false;
                    //Get selected account name from manager and set it to a new accountDialog instance to be edited.
                    iAccountManagerDialog.provideSelectedAccountIdIndex(CURRENT_SELECTED_ACCOUNT_INDEX_FROM_MANAGER);
                    std::vector<std::string>::iterator accountName = ListOfExistingAccounts.begin()+CURRENT_SELECTED_ACCOUNT_INDEX_FROM_MANAGER;
                    std::vector<std::string>::iterator accountPath = ListOfExistingAccountsPaths.begin()+CURRENT_SELECTED_ACCOUNT_INDEX_FROM_MANAGER;
                    this->requestAccountEditing(*accountName, *accountPath);
                }
                else if (iAccountManagerDialog.DeleteAccount)
                {
                    //ACCOUNT_SET = false;
                    //Get selected account name from manager and perform deletion.
                    iAccountManagerDialog.provideSelectedAccountIdIndex(CURRENT_SELECTED_ACCOUNT_INDEX_FROM_MANAGER);
                    std::vector<std::string>::iterator accountName = ListOfExistingAccounts.begin()+CURRENT_SELECTED_ACCOUNT_INDEX_FROM_MANAGER;
                    std::vector<std::string>::iterator accountPath = ListOfExistingAccountsPaths.begin()+CURRENT_SELECTED_ACCOUNT_INDEX_FROM_MANAGER;
                    this->requestAccountDeletion(*accountName, *accountPath);
                }
                else if (iAccountManagerDialog.CreateNewAccount)
                {
                    ACCOUNT_SET = false;
                    this->requestAccountCreation();
                }
}

void Gui_KeiboMoneyTracker::searchForExistingAccounts()//this function also creates app directory if no app directory is found.
{
    homeDir.setPath(QDir::homePath());
    std::cout<<"homeDir is: "<<homeDir.dirName().toStdString()<<'\n';

    //Clean Global Info of existing accounts
    AccountsExist = false;
    ListOfExistingAccounts.clear();
    ListOfExistingAccountsPaths.clear();

    QFileInfoList ListOfElementsInHome;
    ListOfElementsInHome= homeDir.entryInfoList();

    bool MainAppDirectoryExists = false;
    //Check here if main App folder exists.
    for (int i = 0; i != ListOfElementsInHome.size(); ++i)
    {
        if ((ListOfElementsInHome[i].isDir())){
            if (ListOfElementsInHome[i].baseName() == APP_DIR_NAME) {
                APP_DIR_FOUND = true;
                MainAppDirectoryExists = true;
                AppDir.setCurrent(ListOfElementsInHome[i].absoluteFilePath());
                std::cout<<"Directoy My Money already exists, setting it as App Directoty "<<'\n';
                AppDir.setPath(homeDir.absolutePath() + "/"+APP_DIR_NAME);
                break;
            }
        }
    }    

    if (MainAppDirectoryExists == true)
    {
        //In this case, look for all folders inside main App folder APP_DIR_NAME.
        //Each account should be a folder starting with prefix
        QFileInfoList ListOfElementsInAppFolder;
        QStringList prefix;
        prefix<< "KMT_*";
        ListOfElementsInAppFolder = AppDir.entryInfoList(prefix, QDir::Dirs);
        std::cout<<"APP DIR: "<<AppDir.absolutePath().toStdString()<<'\n';
        for (int i = 0; i != ListOfElementsInAppFolder.size(); ++i)
        {
            if ((ListOfElementsInAppFolder[i].isDir())){
               //Get path for each account.
               ListOfExistingAccountsPaths.push_back(ListOfElementsInAppFolder[i].absoluteFilePath().toStdString());
               //Get name for each account.
               std::string accountName;
               std::string folderName = ListOfElementsInAppFolder[i].baseName().toStdString();
                  //Take account name from folder name. Ignore prexix (first four elements)
               for (std::string::iterator it = folderName.begin()+4; it != folderName.end(); ++it)
                 {
                   accountName += *it;
                 }
               ListOfExistingAccounts.push_back(accountName);
               AccountsExist = true;
            }
        }
    }  else   {
        //In this case the main APP folder has to be created
        std::cout<<"Directoy My Money does not exist."<<'\n';
        homeDir.mkdir(APP_DIR_NAME);
        AppDir.setPath(homeDir.absolutePath() + "/"+APP_DIR_NAME);
        std::cout<<"Directoy My Money has been created and set as App directory"<<'\n';
        //A new account must be created. Account Dialog must be opened.
    }

}

void Gui_KeiboMoneyTracker::addOutcome()
{
    if (ACCOUNT_SET)
    {
        std::string tname; double tprice; int tcategory; int tmonth; int tday; RepetitionOption trepeat = DO_NOT_REPEAT;  //Temporary variables
        TransactionDialog newArticleWindow;                                    //Open QDialog
        if (currentAccount.getAccountLanguage() == ENGLISH) {
            newArticleWindow.setWindowTitle(" Add expense");
        } else if (currentAccount.getAccountLanguage() == GERMAN) {
            newArticleWindow.setWindowTitle(" Ausgabe hinzufügen");
        } else if (currentAccount.getAccountLanguage() == SPANISH) {
            newArticleWindow.setWindowTitle(" Añadir egreso");
        }
        newArticleWindow.setLanguage(currentAccount.getAccountLanguage());
        newArticleWindow.setCategoryList(currentAccount.ExpensesGroupsNames);
        newArticleWindow.setModal(true);

        time_t T = time(0);
        struct tm * currentTime = localtime(&T);
        newArticleWindow.displayItemInfo("", 0.0, 0, currentTime->tm_mon, currentTime->tm_mday-1, DO_NOT_REPEAT, currentYear);
        newArticleWindow.setOverallThemeStyleSheet(currentOverallThemeStyleSheet, usingDarkTheme);

        newArticleWindow.exec();
        newArticleWindow.provideArticleInfo(tname, tprice, tcategory, tmonth, tday, trepeat);  //Assign values fetching temp variables
        //rename "provide" to "submit" (coming from object).
        if (newArticleWindow.transactionNameOK && newArticleWindow.transactionAmountOK)
        {
            Transaction tArticle(tname, tprice, tmonth, tday, tcategory, trepeat);              //Create temp article!!! ORDER OF INITIALIZERS

            std::vector<Transaction> newElementsAddedAutomatically;
            currentAccount.addTransaction(tArticle);
            currentMonth = tmonth;
            displayMonthOnLabel();
            currentAccount.setElementsToRepeat(newElementsAddedAutomatically);
            currentAccount.save_Data();
            std::cout<<"Data saved"<<'\n';
            displayArticlesOnTable();
            updateGraph();
            updateGroups();
            updateListOfGroups();

            ///Show to user new elements added automatically by repetition if any.
            if (newElementsAddedAutomatically.size() > 0){
                newElementsAddedAutomaticallyDialog iNewElementsAddedAutomatically;
                iNewElementsAddedAutomatically.setModal(true);
                iNewElementsAddedAutomatically.setLanguage(currentAccount.getAccountLanguage());
                iNewElementsAddedAutomatically.getInfoToDisplay(newElementsAddedAutomatically,
                                                                currentAccount.IncomeGroupsNames,
                                                                currentAccount.ExpensesGroupsNames,
                                                                colorOfIncomeAmount,
                                                                currentAccount.getAccountLanguage());
                iNewElementsAddedAutomatically.setOverallThemeStyleSheet(currentOverallThemeStyleSheet, usingDarkTheme);
                iNewElementsAddedAutomatically.exec();
            }
        }
    }
}

void Gui_KeiboMoneyTracker::on_addExpenseButton_clicked()
{
    this->addOutcome();
}

void Gui_KeiboMoneyTracker::addIncome()
{
    if (ACCOUNT_SET)
    {
        TransactionDialog newIncomeWindow;
        newIncomeWindow.setCategoryList(currentAccount.IncomeGroupsNames);
        if (currentAccount.getAccountLanguage() == ENGLISH) {
            newIncomeWindow.setWindowTitle(" Add income");
        } else if (currentAccount.getAccountLanguage() == GERMAN) {
            newIncomeWindow.setWindowTitle(" Einkommen hinzufügen");
        } else if (currentAccount.getAccountLanguage() == SPANISH) {
            newIncomeWindow.setWindowTitle(" Añadir ingreso");
        }
        newIncomeWindow.setLanguage(currentAccount.getAccountLanguage());
        newIncomeWindow.setModal(true);

        time_t T = time(0);
        struct tm * currentTime = localtime(&T);
        newIncomeWindow.displayItemInfo("", 0.0, 0, currentTime->tm_mon, currentTime->tm_mday-1, DO_NOT_REPEAT, currentYear);
        newIncomeWindow.setOverallThemeStyleSheet(currentOverallThemeStyleSheet, usingDarkTheme);

        newIncomeWindow.exec();
        std::string tname; double tprice; int tcategory; int tmonth; int tday; RepetitionOption trepeat = DO_NOT_REPEAT;  //Temporary variables
        newIncomeWindow.provideArticleInfo(tname, tprice, tcategory, tmonth, tday, trepeat);

        if (newIncomeWindow.transactionNameOK && newIncomeWindow.transactionAmountOK)
        {
            std::vector<Transaction> newElementsAddedAutomatically;
            Transaction tArticle(tname, tprice, tmonth, tday, tcategory, trepeat, true);
            currentAccount.addTransaction(tArticle);
            currentMonth = tmonth;
            displayMonthOnLabel();
            currentAccount.setElementsToRepeat(newElementsAddedAutomatically);
            currentAccount.save_Data();
            displayArticlesOnTable();
            updateGraph();
            updateGroups();
            updateListOfGroups();
            ///Show to user new elements added automatically by repetition if any.
            if (newElementsAddedAutomatically.size() > 0){
                newElementsAddedAutomaticallyDialog iNewElementsAddedAutomatically;
                iNewElementsAddedAutomatically.setModal(true);
                iNewElementsAddedAutomatically.setLanguage(currentAccount.getAccountLanguage());
                iNewElementsAddedAutomatically.getInfoToDisplay(newElementsAddedAutomatically,
                                                                currentAccount.IncomeGroupsNames,
                                                                currentAccount.ExpensesGroupsNames,
                                                                colorOfIncomeAmount,
                                                                currentAccount.getAccountLanguage());
                iNewElementsAddedAutomatically.setOverallThemeStyleSheet(currentOverallThemeStyleSheet, usingDarkTheme);
                iNewElementsAddedAutomatically.exec();
            }
        }
    }
}

void Gui_KeiboMoneyTracker::on_addIncomeButton_clicked()
{
    this->addIncome();
}

void Gui_KeiboMoneyTracker::deleteSelectedTransaction()
{
    if (ACCOUNT_SET)
    {
       QItemSelectionModel * selection = ui->tableWidget->selectionModel();
       QModelIndexList highlightedRows =  selection->selectedRows();
       if (highlightedRows.count()>0)
       {
           eraseConfirmation_dialog eraseConfirmationWindow; //Are you sure you want to delete the selected items?
           eraseConfirmationWindow.setModal(true);
           eraseConfirmationWindow.setOverallThemeStyleSheet(currentOverallThemeStyleSheet, usingDarkTheme);
           if (currentAccount.getAccountLanguage() == ENGLISH){
               eraseConfirmationWindow.setWindowTitle(" Confirmation");
               eraseConfirmationWindow.setInfoText("Are you sure you want to delete the selected items?");
           } else if (currentAccount.getAccountLanguage() == GERMAN){
               eraseConfirmationWindow.setWindowTitle(" Bestätigung");
               eraseConfirmationWindow.setInfoText("Möchten Sie die gewählten Transaktionen löschen?");
           } else if (currentAccount.getAccountLanguage() == SPANISH){
               eraseConfirmationWindow.setWindowTitle(" Confirmación");
               eraseConfirmationWindow.setInfoText("¿Desea eliminar las transacciones seleccionadas?");
           }
           eraseConfirmationWindow.exec();

           if (eraseConfirmationWindow.comfirmed())
           {
               std::vector<int> listOfItemsToDelete;
               listOfItemsToDelete.clear();
               for (int i = 0; i!=highlightedRows.count(); ++i)
               {
                   QModelIndex index = highlightedRows.at(i);
                   int row = index.row();
                   //std::cout<<"Element Row to delete: "<<row<<'\n';
                   listOfItemsToDelete.push_back( row);
               }
               currentAccount.deleteMultipleTransactionsInMonth(currentMonth, listOfItemsToDelete); //THIS FUNCTION ARRANGES ELEMENTS BY ITS OWN, IN CASE LIST IDs PROVIDED BY QT DOES NOT MATCH THE DATA IN BUY_DATA CLASS
               currentAccount.save_Data();
               displayArticlesOnTable();
               updateGraph();
               updateGroups();
               updateListOfGroups();
               this->ui->tableWidget->clearSelection();
           }
       }
    }
}

void Gui_KeiboMoneyTracker::on_deleteItemButton_clicked()
{
    this->deleteSelectedTransaction();
}

void Gui_KeiboMoneyTracker::editSelectedTransaction()
{
    if (ACCOUNT_SET)
    {
        QItemSelectionModel *selection = ui->tableWidget->selectionModel();
        QModelIndexList highlightedRows = selection->selectedRows();
        if (highlightedRows.count()>0 && highlightedRows.count()<2)
        {
            TransactionDialog newArticleWindow;
            if (currentAccount.getAccountLanguage() == ENGLISH) {
                newArticleWindow.setWindowTitle(" Edit transaction");
            } else if (currentAccount.getAccountLanguage() == GERMAN) {
                newArticleWindow.setWindowTitle(" Transaktion ändern");
            } else if (currentAccount.getAccountLanguage() == SPANISH) {
                newArticleWindow.setWindowTitle(" Editar transacción");
            }
            newArticleWindow.setLanguage(currentAccount.getAccountLanguage());

            QModelIndex index = highlightedRows.at(0);
            std::vector<Transaction>::iterator it = currentAccount.Yearly_Articles[currentMonth].begin();
            it+=index.row(); //Point to selected element

            std::string tname;
            double      tprice      = 0.0;
            int         tcategory   = 0;
            int         tmonth      = 0;
            int         tday        = 0;
            bool        tisincome   = false;
            RepetitionOption trepeat = DO_NOT_REPEAT;

            if (it->IsIncome){
                newArticleWindow.setCategoryList(currentAccount.IncomeGroupsNames);     ////Assign list of groups
                tisincome = true;
            }
            else if (!it->IsIncome){
                newArticleWindow.setCategoryList(currentAccount.ExpensesGroupsNames);     ////Assign list of groups
            }
            newArticleWindow.displayItemInfo(it->Name,
                                             it->Amount,
                                             it->Group,
                                             it->Month,
                                             it->Day-1,
                                             it->Repetition_Option,
                                             currentYear);

            newArticleWindow.setModal(true);
            newArticleWindow.setOverallThemeStyleSheet(currentOverallThemeStyleSheet, usingDarkTheme);
            newArticleWindow.exec();

            newArticleWindow.provideArticleInfo(tname, tprice, tcategory, tmonth, tday, trepeat);

            bool editionPossible  = false;

            if ( ((it->Name      != tname)       ||
                  (it->Amount     != tprice)      ||
                  (it->Group  != tcategory)   ||
                  (it->Month     != tmonth)      ||
                  (it->Day       != tday)        ||
                  (it->Repetition_Option != trepeat))   &&
                 newArticleWindow.transactionNameOK     &&
                 newArticleWindow.transactionAmountOK)
            {
                editionPossible = true;
            }

            ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            ///--------------------------------------------------------------------------//////--------------------------------------------------------------------------///


            if (!tname.empty() && editionPossible)
            {
                if (tisincome){
                    Transaction tArticle(tname, tprice, tmonth, tday, tcategory, trepeat, true);
                    currentAccount.editTransaction((*it), tArticle);
                }
                else if (!tisincome){
                    Transaction tArticle(tname, tprice, tmonth, tday, tcategory, trepeat);
                    currentAccount.editTransaction((*it), tArticle);
                }

                std::vector<Transaction> newElementsAddedAutomatically;
                currentAccount.setElementsToRepeat(newElementsAddedAutomatically);
                currentAccount.save_Data();
                displayArticlesOnTable();
                updateGraph();
                updateGroups();
                updateListOfGroups();

                ///Show to user new elements added automatically by repetition if any.
                if (newElementsAddedAutomatically.size() > 0){
                    newElementsAddedAutomaticallyDialog iNewElementsAddedAutomatically;
                    iNewElementsAddedAutomatically.setModal(true);
                    iNewElementsAddedAutomatically.setLanguage(currentAccount.getAccountLanguage());
                    iNewElementsAddedAutomatically.getInfoToDisplay(newElementsAddedAutomatically,
                                                                    currentAccount.IncomeGroupsNames,
                                                                    currentAccount.ExpensesGroupsNames,
                                                                    colorOfIncomeAmount,
                                                                    currentAccount.getAccountLanguage());
                    iNewElementsAddedAutomatically.setOverallThemeStyleSheet(currentOverallThemeStyleSheet, usingDarkTheme);
                    iNewElementsAddedAutomatically.exec();
                }
            }
        }

        else if (highlightedRows.count() > 1)
        {
            eraseConfirmation_dialog eraseConfirmationWindow;
            eraseConfirmationWindow.setModal(true);
            if (currentAccount.getAccountLanguage() == ENGLISH) {
                eraseConfirmationWindow.setWindowTitle(" Information");
                eraseConfirmationWindow.setInfoText(" Only one Item can be edited at a time.");
            } else if (currentAccount.getAccountLanguage() == GERMAN) {
                eraseConfirmationWindow.setWindowTitle(" Information");
                eraseConfirmationWindow.setInfoText(" Nur eine Transaktion kann gleichzeitig geändert werden.");
            } else if (currentAccount.getAccountLanguage() == SPANISH) {
                eraseConfirmationWindow.setWindowTitle(" Información");
                eraseConfirmationWindow.setInfoText("Solo una transacción puede ser editada a la vez.");
            }
            eraseConfirmationWindow.setOverallThemeStyleSheet(currentOverallThemeStyleSheet, usingDarkTheme);
            eraseConfirmationWindow.exec();
        }
    }
}

void Gui_KeiboMoneyTracker::on_copyButton_clicked()
{
    this->copyTransaction();
}

void Gui_KeiboMoneyTracker::copyTransaction()
{
    QItemSelectionModel *selection = ui->tableWidget->selectionModel();
    QModelIndexList highlightedRows = selection->selectedRows();
    if (highlightedRows.count()>0 && highlightedRows.count()<2)
    {
        TransactionDialog newArticleWindow;
        if (currentAccount.getAccountLanguage() == ENGLISH) {
            newArticleWindow.setWindowTitle(" Copy transaction");
        } else if (currentAccount.getAccountLanguage() == GERMAN) {
            newArticleWindow.setWindowTitle(" Transaktion kopieren");
        } else if (currentAccount.getAccountLanguage() == SPANISH) {
            newArticleWindow.setWindowTitle(" Copiar transacción");
        }
        newArticleWindow.setLanguage(currentAccount.getAccountLanguage());

        QModelIndex index = highlightedRows.at(0);
        std::vector<Transaction>::iterator it = currentAccount.Yearly_Articles[currentMonth].begin();
        it+=index.row(); //Point to selected element

        std::string tname;
        double      tprice      = 0.0;
        int         tcategory   = 0;
        int         tmonth      = 0;
        int         tday        = 0;
        bool        tisincome   = false;
        RepetitionOption trepeat = DO_NOT_REPEAT;

        if (it->IsIncome){
            newArticleWindow.setCategoryList(currentAccount.IncomeGroupsNames);     ////Assign list of groups
            tisincome = true;
        }
        else if (!it->IsIncome){
            newArticleWindow.setCategoryList(currentAccount.ExpensesGroupsNames);     ////Assign list of groups
        }
        time_t T = time(0);
        struct tm * currentTime = localtime(&T);
        newArticleWindow.displayItemInfo(it->Name,
                                         it->Amount,
                                         it->Group,
                                         currentTime->tm_mon,
                                         currentTime->tm_mday-1,
                                         it->Repetition_Option,
                                         currentYear);

        newArticleWindow.setModal(true);
        newArticleWindow.setOverallThemeStyleSheet(currentOverallThemeStyleSheet, usingDarkTheme);
        newArticleWindow.exec();

        newArticleWindow.provideArticleInfo(tname, tprice, tcategory, tmonth, tday, trepeat);

        bool copyPossible  = false;
        if ( ((it->Name      != tname)       ||
              (it->Amount     != tprice)      ||
              (it->Group  != tcategory)   ||
              (it->Month     != tmonth)      ||
              (it->Day       != tday)        ||
              (it->Repetition_Option != trepeat))   &&
             newArticleWindow.transactionNameOK     &&
             newArticleWindow.transactionAmountOK)
        {
            copyPossible = true;
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        ///--------------------------------------------------------------------------//////--------------------------------------------------------------------------///
        if (copyPossible)
        {
            if (tisincome){
                Transaction tArticle(tname, tprice, tmonth, tday, tcategory, trepeat, true);
                currentAccount.addTransaction(tArticle);
            }
            else if (!tisincome){
                Transaction tArticle(tname, tprice, tmonth, tday, tcategory, trepeat);
                currentAccount.addTransaction(tArticle);
            }

            std::vector<Transaction> newElementsAddedAutomatically;
            currentAccount.setElementsToRepeat(newElementsAddedAutomatically);
            currentAccount.save_Data();
            currentMonth = tmonth;
            updateToCurrentMonth();
            updateGroups();
            updateListOfGroups();

            ///Show to user new elements added automatically by repetition if any.
            if (newElementsAddedAutomatically.size() > 0){
                newElementsAddedAutomaticallyDialog iNewElementsAddedAutomatically;
                iNewElementsAddedAutomatically.setModal(true);
                iNewElementsAddedAutomatically.setLanguage(currentAccount.getAccountLanguage());
                iNewElementsAddedAutomatically.getInfoToDisplay(newElementsAddedAutomatically,
                                                                currentAccount.IncomeGroupsNames,
                                                                currentAccount.ExpensesGroupsNames,
                                                                colorOfIncomeAmount,
                                                                currentAccount.getAccountLanguage());
                iNewElementsAddedAutomatically.setOverallThemeStyleSheet(currentOverallThemeStyleSheet, usingDarkTheme);
                iNewElementsAddedAutomatically.exec();
            }
        }
    }
    else if (highlightedRows.count() > 1)
    {
        eraseConfirmation_dialog eraseConfirmationWindow;
        eraseConfirmationWindow.setModal(true);
        if (currentAccount.getAccountLanguage() == ENGLISH) {
            eraseConfirmationWindow.setWindowTitle(" Information");
            eraseConfirmationWindow.setInfoText(" Only one Item can be copied at a time.");
        } else if (currentAccount.getAccountLanguage() == GERMAN) {
            eraseConfirmationWindow.setWindowTitle(" Information");
            eraseConfirmationWindow.setInfoText(" Nur eine Transaktion kann gleichzeitig kopiert werden.");
        } else if (currentAccount.getAccountLanguage() == SPANISH) {
            eraseConfirmationWindow.setWindowTitle(" Información");
            eraseConfirmationWindow.setInfoText("Solo una transacción puede ser copiada a la vez.");
        }
        eraseConfirmationWindow.setOverallThemeStyleSheet(currentOverallThemeStyleSheet, usingDarkTheme);
        eraseConfirmationWindow.exec();
    }
}

void Gui_KeiboMoneyTracker::on_editItemButton_clicked()
{
    this->editSelectedTransaction();
}

void Gui_KeiboMoneyTracker::displayArticlesOnTable()
{
    if (currentAccount.getBalanceInMonth(currentMonth) >= abs(10000.0)  ){
        ui->lineMonthlyBalance->setFixedWidth(90);
    } else {
        ui->lineMonthlyBalance->setFixedWidth(82);
    }
    if (currentAccount.getBalanceInYear() >= abs(10000.0)  ){
        ui->lineYearlyBalance->setFixedWidth(90);
    } else {
        ui->lineYearlyBalance->setFixedWidth(82);
    }

    ui->tableWidget->setColumnCount(4);
    QStringList tableHeader;
    if (currentAccount.getAccountLanguage() == ENGLISH){
        tableHeader<<"Name"<<"Amount"<<"Day"<<"Group";
    } else if (currentAccount.getAccountLanguage() == GERMAN){
        tableHeader<<"Name"<<"Betrag"<<"Tag"<<"Gruppe";
    } else if (currentAccount.getAccountLanguage() == SPANISH){
        tableHeader<<"Nombre"<<"Monto"<<"Día"<<"Grupo";
    }
    ui->tableWidget->setHorizontalHeaderLabels(tableHeader);

    ui->tableWidget->setRowCount(currentAccount.getNumberOfTransactionsInMonth(currentMonth));
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);

    int item_Id = 0;
    std::vector<std::string>::iterator groupIterator        = currentAccount.ExpensesGroupsNames.begin();
    std::vector<std::string>::iterator incomeGroupIterator  = currentAccount.IncomeGroupsNames.begin();
    for (std::vector<Transaction>::iterator it = currentAccount.Yearly_Articles[currentMonth].begin(); it != currentAccount.Yearly_Articles[currentMonth].end(); ++it)
    {
        /////////////////////////////////FIRST COLUMN///////////////////////////////////
        ///--------------------------------------------------------------------------///
        ui->tableWidget->setItem(item_Id,0, new QTableWidgetItem (QString::fromStdString(it->Name)));
        ui->tableWidget->item(item_Id, 0)->setTextAlignment(Qt::AlignBottom);
        ui->tableWidget->setWordWrap(false);

        /////////////////////////////////SECOND COLUMN//////////////////////////////////
        ///--------------------------------------------------------------------------///
        if (it->IsIncome){
            if (currentAccount.getAccountLanguage() == GERMAN){
                ui->tableWidget->setItem(item_Id,1, new QTableWidgetItem (QString("+")+ QString::fromStdString(getAmountAsStringInGermanFormat(it->Amount))  + QString("  ")));
            } else {
                ui->tableWidget->setItem(item_Id,1, new QTableWidgetItem (QString("+")+ QString::fromStdString(getAmountAsStringFormatted(it->Amount))  + QString("  ")));
            }
            //Set color of IncomeAmount
            int r = 0, g = 0, b = 0;
            getColorCode(colorOfIncomeAmount, r, g, b);
            ui->tableWidget->item(item_Id, 1)->setForeground(QColor(r, g, b));
        }
        else if (!(it->IsIncome)){
            if (currentAccount.getAccountLanguage() == GERMAN){
                ui->tableWidget->setItem(item_Id,1, new QTableWidgetItem (QString("-")+ QString::fromStdString(getAmountAsStringInGermanFormat(it->Amount))  + QString("  ")) );
            } else {
                ui->tableWidget->setItem(item_Id,1, new QTableWidgetItem (QString("-")+ QString::fromStdString(getAmountAsStringFormatted(it->Amount)) + QString("  ")));
            }
        }
        ui->tableWidget->item(item_Id,1)->setTextAlignment(Qt::AlignmentFlag::AlignRight | Qt::AlignmentFlag::AlignBottom);

        /////////////////////////////////THIRD COLUMN///////////////////////////////////
        ///--------------------------------------------------------------------------///
        ui->tableWidget->setItem(item_Id,2, new QTableWidgetItem (QString::number(it->Day)));
        ui->tableWidget->item(item_Id,2)->setTextAlignment(Qt::AlignmentFlag::AlignHCenter | Qt::AlignmentFlag::AlignBottom);

        /////////////////////////////////FOURTH COLUMN//////////////////////////////////
        ///--------------------------------------------------------------------------///
        if (it->IsIncome){
            ui->tableWidget->setItem(item_Id,3, new QTableWidgetItem (QString::fromStdString(*(incomeGroupIterator+(it->Group)))));
        }
        else if (!(it->IsIncome)){
            ui->tableWidget->setItem(item_Id,3, new QTableWidgetItem (QString::fromStdString(*(groupIterator+(it->Group)))));
        }
        ui->tableWidget->item(item_Id,3)->setTextAlignment(Qt::AlignBottom | Qt::AlignmentFlag::AlignHCenter);
        ++item_Id;
    }

    /////////////////////////////--AMOUNTS AND BALANCES--////////////////////////////
    ///--------------------------------------------------------------------------///
    QString currencySymbol = QString::fromStdString(getCurrenySymbol(currentAccount.getAccountCurrency()));
    if (currentAccount.getAccountLanguage() == GERMAN){
        ui->monthlyExpendituresLabel->setText(QString::fromStdString(getAmountAsStringInGermanFormat((currentAccount.getExpensesInMonth(currentMonth))))+" "+ currencySymbol+" ");
        ui->yearlyExpendituresLabel->setText(QString::fromStdString(getAmountAsStringInGermanFormat(currentAccount.getTotalExpensesInYear())) + " "+ currencySymbol+" ");
        ui->monthlyIncomeLabel->setText(QString::fromStdString(getAmountAsStringInGermanFormat(currentAccount.getIncomeInMonth(currentMonth)))+ " "+ currencySymbol+" ");
        ui->yearlyIncomeLabel->setText(QString::fromStdString(getAmountAsStringInGermanFormat(currentAccount.getTotalIncomeInYear())) + " "+ currencySymbol+" ");
        if (currentAccount.getBalanceInYear()>0){
            ui->yearlyBalanceLabel->setText(QString("+")+QString::fromStdString(getAmountAsStringInGermanFormat(currentAccount.getBalanceInYear()))+ " "+ currencySymbol+" ");
        } else {
            ui->yearlyBalanceLabel->setText(QString::fromStdString(getAmountAsStringInGermanFormat(currentAccount.getBalanceInYear()))+ " "+ currencySymbol+" ");
        }
        if (currentAccount.getBalanceInMonth(currentMonth)>0){
            ui->monthlyBalanceLabel->setText(QString("+")+QString::fromStdString(getAmountAsStringInGermanFormat(currentAccount.getBalanceInMonth(currentMonth)))+ " "+ currencySymbol+" ");
        } else {
            ui->monthlyBalanceLabel->setText(QString::fromStdString(getAmountAsStringInGermanFormat(currentAccount.getBalanceInMonth(currentMonth)))+ " "+ currencySymbol+" ");
        }

    } else {
        ui->monthlyExpendituresLabel->setText(QString::fromStdString(getAmountAsStringFormatted(currentAccount.getExpensesInMonth(currentMonth)))+ " "+ currencySymbol+" ");
        ui->yearlyExpendituresLabel->setText(QString::fromStdString(getAmountAsStringFormatted(currentAccount.getTotalExpensesInYear())) + " "+ currencySymbol+" ");
        ui->monthlyIncomeLabel->setText(QString::fromStdString(getAmountAsStringFormatted(currentAccount.getIncomeInMonth(currentMonth)))+ " "+ currencySymbol+" ");
        ui->yearlyIncomeLabel->setText(QString::fromStdString(getAmountAsStringFormatted(currentAccount.getTotalIncomeInYear())) + " "+ currencySymbol+" ");

        if (currentAccount.getBalanceInYear()>0){
            ui->yearlyBalanceLabel->setText(QString("+")+QString::fromStdString(getAmountAsStringFormatted(currentAccount.getBalanceInYear()))+ " "+ currencySymbol+" ");
        } else {
            ui->yearlyBalanceLabel->setText(QString::fromStdString(getAmountAsStringFormatted(currentAccount.getBalanceInYear()))+ " "+ currencySymbol+" ");
        }

        if (currentAccount.getBalanceInMonth(currentMonth)>0){
            ui->monthlyBalanceLabel->setText(QString("+")+QString::fromStdString(getAmountAsStringFormatted(currentAccount.getBalanceInMonth(currentMonth)))+ " "+ currencySymbol+" ");
        } else {
            ui->monthlyBalanceLabel->setText(QString::fromStdString(getAmountAsStringFormatted(currentAccount.getBalanceInMonth(currentMonth)))+ " "+ currencySymbol+" ");
        }
    }
    ui->monthlyExpendituresLabel->setAlignment(Qt::AlignRight);
    ui->yearlyExpendituresLabel->setAlignment(Qt::AlignRight);
    ui->monthlyIncomeLabel->setAlignment(Qt::AlignRight);
    ui->yearlyIncomeLabel->setAlignment(Qt::AlignRight);
    ui->yearlyBalanceLabel->setAlignment(Qt::AlignRight);
    ui->monthlyBalanceLabel->setAlignment(Qt::AlignRight);

    ui->tableWidget->horizontalHeader()->setVisible(true);

    ui->tableWidget->setShowGrid(false);
    ui->tableWidget->setItemDelegate(new GridLineDelegate(ui->tableWidget));
}

void Gui_KeiboMoneyTracker::on_monthBackwardButton_clicked()
{
    if (currentMonth>0 && currentMonth<=11) {
       --currentMonth;
        updateToCurrentMonth();
    } else if (currentMonth == 0) {
        currentMonth = 11;
        --currentYear;
        updateToCurrentYear();
    }
    if (focusingOverallIncomeExpenses == false){
        this->focusOverallIncomeExpenses();
    }
}

void Gui_KeiboMoneyTracker::on_monthForwardButton_clicked()
{
    if (currentMonth>=0 && currentMonth<11) {
        ++currentMonth;
        updateToCurrentMonth();
    } else if (currentMonth == 11) {
        currentMonth = 0;
        ++currentYear;
        updateToCurrentYear();
    }
    if (focusingOverallIncomeExpenses == false){
        this->focusOverallIncomeExpenses();
    }
}

void Gui_KeiboMoneyTracker::displayMonthOnLabel()
{
    if (ACCOUNT_SET)
    {
        this->ui->monthLabel->setText(QString::fromStdString(getMonthInLanguage(currentMonth, currentAccount.getAccountLanguage()) ));
    }
    else {
        this->ui->monthLabel->setText(QString::fromStdString(getMonthInLanguage(currentMonth, initialLanguage)) );
    }
}

void Gui_KeiboMoneyTracker::on_yearForwardButton_clicked()
{
    ++currentYear;
    updateToCurrentYear();
    if (focusingOverallIncomeExpenses == false){
        this->focusOverallIncomeExpenses();
    }
}

void Gui_KeiboMoneyTracker::on_yearBackwardsButton_clicked()
{
    --currentYear;
    updateToCurrentYear();
    if (focusingOverallIncomeExpenses == false){
        this->focusOverallIncomeExpenses();
    }
}

void Gui_KeiboMoneyTracker::updateGraph()   ///SCALE TO MAXIMUM AMOUNT IN A MONTH
{
        ui->widget1->currentLanguage = currentAccount.getAccountLanguage();
        ui->widget1->currentCurrency = currentAccount.getAccountCurrency();

        double highestValue = currentAccount.getHighestMonthlyIncome();//Get highest monthly amount, either income or expense
        if (currentAccount.getHighestMonthlyExpenses() > highestValue){
            highestValue = currentAccount.getHighestMonthlyExpenses();
        }

        ui->widget1->Highlighted   = currentMonth;

        double oneStage = highestValue/5;   ////Calculate values of scale board
        for (int i = 1; i != 6; ++i){
            ui->widget1->scaleValues[i-1] = (oneStage * i); //-(highestValue*0.01);
        }

        for (int month = 0; month!=12; ++month)
        {
            if (currentAccount.getIncomeInMonth(month) != 0.0){
                ui->widget1->monthYpFinalIncome[month] = ((currentAccount.getIncomeInMonth(month)/highestValue));
                ui->widget1->validYpFinalIncome[month] = true;
            } else {
                ui->widget1->validYpFinalIncome[month] = false;
            }

            if (currentAccount.getExpensesInMonth(month) != 0.0){
                ui->widget1->monthYpFinalOutcome[month] = ( (currentAccount.getExpensesInMonth(month)/highestValue));
                ui->widget1->validYpFinalOutcome[month] = true;
            } else {
                ui->widget1->validYpFinalOutcome[month] = false;
            }
        }
        ui->widget1->resetFLags();
}

void Gui_KeiboMoneyTracker::updateGroups()
{
    ui->widget_2->setProperties(currentAccount.getAccountLanguage(), currentAccount.getAccountCurrency());

        ui->widget_2->finalPercentageStart = 0.0f;
        ui->widget_2->finalPercentageEnd   = 0.0f;
        ui->widget_2->amountOfSelectedGroup = 0.0;
        ui->widget_2->finalPercentageOfEachGroup.clear();

        float percentageOffSetArc = 0.0f;

        if (!showIncome)
        {
            ui->widget_2->showingIncome = false;
            if (currentGroupSelected > 0)
            {
                if (this->currentAccount.getTotalExpensesOfGroup(currentGroupSelected) != 0){
                    for (unsigned int i = 0; i != currentGroupSelected; ++i){  ///Calculate offset.
                        percentageOffSetArc = percentageOffSetArc + (this->currentAccount.getTotalExpensesOfGroup(i)/this->currentAccount.getTotalExpensesInYear());
                    }

                    ///Calculate arc relative to expense.
                    ui->widget_2->finalPercentageStart =   percentageOffSetArc;
                    ui->widget_2->finalPercentageEnd   =  (percentageOffSetArc
                                                        + (this->currentAccount.getTotalExpensesOfGroup(currentGroupSelected)/this->currentAccount.getTotalExpensesInYear()) );
                } else {
                    ui->widget_2->finalPercentageStart =   0;
                    ui->widget_2->finalPercentageEnd   =   0.0f;
                }
            }

            else
            {
                if (this->currentAccount.getTotalExpensesOfGroup(0) != 0) {
                    ui->widget_2->finalPercentageEnd = this->currentAccount.getTotalExpensesOfGroup(0)/this->currentAccount.getTotalExpensesInYear();
                } else {
                    ui->widget_2->finalPercentageEnd = 0.0f;
                }
            }

            for (unsigned int i = 0; i != currentAccount.ExpensesGroupsAmounts.size(); ++i)
            {
                ui->widget_2->finalPercentageOfEachGroup.push_back(currentAccount.getPercentageOfExpensesGroup(i));
            }

            std::vector<std::string>::iterator groupIteratorName = currentAccount.ExpensesGroupsNames.begin();
            //ui->groupNameLabel->setText(QString::fromStdString(*(groupIteratorName+currentGroupSelected)));
            ui->groupNameLabel->setText(QString::fromStdString(*(groupIteratorName+currentGroupSelected)));

            std::vector<double>::iterator groupExpensesIterator = currentAccount.ExpensesGroupsAmounts.begin();
            //ui->groupAmountLabel->setText(QString::number( (*(groupExpensesIterator+currentGroupSelected)), 0, 2) + QString(" €") );


            ui->widget_2->amountOfSelectedGroup = *(groupExpensesIterator+currentGroupSelected);
        }

        else if (showIncome)
        {
            ui->widget_2->showingIncome = true;
            if (currentIncomeGroupSelected > 0)
            {
                if (this->currentAccount.getTotalIncomeOfGroup(currentIncomeGroupSelected) != 0) {
                    for (unsigned int i = 0; i !=currentIncomeGroupSelected; ++i){
                        percentageOffSetArc = percentageOffSetArc + (this->currentAccount.getTotalIncomeOfGroup(i)/this->currentAccount.getTotalIncomeInYear());
                    }

                    ui->widget_2->finalPercentageStart =  percentageOffSetArc;
                    ui->widget_2->finalPercentageEnd   = (percentageOffSetArc
                                                        +(this->currentAccount.getTotalIncomeOfGroup(currentIncomeGroupSelected)/this->currentAccount.getTotalIncomeInYear()) );
                } else {
                    ui->widget_2->finalPercentageStart = 0.0f;
                    ui->widget_2->finalPercentageEnd   = 0.0f;
                }
            }

            else
            {
                if (this->currentAccount.getTotalIncomeOfGroup(0) != 0){
                    ui->widget_2->finalPercentageEnd = (this->currentAccount.getTotalIncomeOfGroup(0)/this->currentAccount.getTotalIncomeInYear());
                } else {
                    ui->widget_2->finalPercentageEnd = 0.0f;
                }
            }

            for (unsigned int i = 0; i != currentAccount.IncomeGroupsAmounts.size(); ++i)
            {
                ui->widget_2->finalPercentageOfEachGroup.push_back(currentAccount.getPercentageOfIncomeGroup(i));
            }

            std::vector<std::string>::iterator groupIterator = currentAccount.IncomeGroupsNames.begin();
            ui->groupNameLabel->setText(QString::fromStdString(*(groupIterator+currentIncomeGroupSelected)));

            std::vector<double>::iterator groupIncomeIterator = currentAccount.IncomeGroupsAmounts.begin();

            ui->widget_2->amountOfSelectedGroup = *(groupIncomeIterator+currentIncomeGroupSelected);
        }

        ui->widget_2->resetFLags();
}

void Gui_KeiboMoneyTracker::updateListOfGroups()
{
        ui->tableOfGroups->setColumnCount(4);
        QStringList tableHeader;
        if (currentAccount.getAccountLanguage() == ENGLISH){
            tableHeader<<"Name"<<"Amount"<<"Day"<<"Month";
        } else if (currentAccount.getAccountLanguage() == GERMAN){
            tableHeader<<"Name"<<"Betrag"<<"Tag"<<"Monat";
        } else if (currentAccount.getAccountLanguage() == SPANISH){
            tableHeader<<"Nombre"<<"Monto"<<"Día"<<"Mes";
        }

        ui->tableOfGroups->setHorizontalHeaderLabels(tableHeader);
        ui->tableOfGroups->setWordWrap(false);

        std::vector<Transaction> listOfArticles;
        listOfArticles.clear();

        if (!showIncome){
            listOfArticles = currentAccount.getListOfExpensesItemsOfGroup(currentGroupSelected);
            ui->tableOfGroups->setRowCount(listOfArticles.size());
        }
        else if (showIncome){
            listOfArticles = currentAccount.getListOfIncomeItemsOfGroup(currentIncomeGroupSelected);
            ui->tableOfGroups->setRowCount(listOfArticles.size());
        }

        int itemId = 0;
        for (std::vector<Transaction>::iterator listIterator = listOfArticles.begin();
             listIterator != listOfArticles.end(); ++listIterator)
            {
                ui->tableOfGroups->setItem(itemId, 0, new QTableWidgetItem(QString::fromStdString(listIterator->Name)));
                ui->tableOfGroups->item(itemId, 0)->setTextAlignment(Qt::AlignBottom);

                if (currentAccount.getAccountLanguage() == GERMAN){
                    ui->tableOfGroups->setItem(itemId, 1, new QTableWidgetItem(QString::fromStdString(getAmountAsStringInGermanFormat(listIterator->Amount)) + " " ) );
                } else {
                   ui->tableOfGroups->setItem(itemId, 1, new QTableWidgetItem(QString::fromStdString(getAmountAsStringFormatted(listIterator->Amount))  + " " ));
                }
                ui->tableOfGroups->item(itemId,1)->setTextAlignment(Qt::AlignmentFlag::AlignRight | Qt::AlignmentFlag::AlignBottom);

                ui->tableOfGroups->setItem(itemId, 2, new QTableWidgetItem(QString::number(listIterator->Day)));
                ui->tableOfGroups->item(itemId,2)->setTextAlignment(Qt::AlignmentFlag::AlignHCenter | Qt::AlignmentFlag::AlignBottom);

                ui->tableOfGroups->setItem(itemId, 3, new QTableWidgetItem(QString::fromStdString(getMonthInLanguage(listIterator->Month, currentAccount.getAccountLanguage()))) );
                ui->tableOfGroups->item(itemId, 3)->setTextAlignment(Qt::AlignmentFlag::AlignHCenter | Qt::AlignmentFlag::AlignBottom);
                ++itemId;
            }

        ui->tableOfGroups->horizontalHeader()->setVisible(true);
        ui->tableOfGroups->setShowGrid(false);
        ui->tableOfGroups->setItemDelegate(new GridLineDelegate(ui->tableOfGroups));
}

void Gui_KeiboMoneyTracker::goToPreviousGroup()
{
    if (ACCOUNT_SET)
    {
        if (!showIncome)
        {
            if (currentGroupSelected <= 0)
            {
                currentGroupSelected = currentAccount.ExpensesGroupsNames.size()-1;
                updateGroups();
                updateListOfGroups();
            }

            else if (currentGroupSelected >= 1){
                --currentGroupSelected;
                updateGroups();
                updateListOfGroups();
            }
        }
        else if (showIncome)
        {
            if (currentIncomeGroupSelected <= 0)
            {
                currentIncomeGroupSelected = currentAccount.IncomeGroupsNames.size()-1;
                updateGroups();
                updateListOfGroups();
            }

            else if (currentIncomeGroupSelected >= 1){
                --currentIncomeGroupSelected;
                updateGroups();
                updateListOfGroups();
            }
        }
    }
    if (focusingGroups == false){
        this->focusGroups();
    }
}

void Gui_KeiboMoneyTracker::on_groupBackwardsButton_clicked()
{
    this->goToPreviousGroup();
}

void Gui_KeiboMoneyTracker::goToNextGroup()
{
    if (ACCOUNT_SET)
    {
        if (!showIncome)
        {
            if (currentGroupSelected >= currentAccount.ExpensesGroupsNames.size()-1)
            {
                currentGroupSelected = 0;
                updateGroups();
                updateListOfGroups();
            }

            else if (currentGroupSelected != (currentAccount.ExpensesGroupsNames.size()-1)){  ///Current number of groups
                ++currentGroupSelected;
                updateGroups();
                updateListOfGroups();
            }
        }
        else if (showIncome)
        {
            if (currentIncomeGroupSelected >= currentAccount.IncomeGroupsNames.size()-1)
            {
                currentIncomeGroupSelected = 0;
                updateGroups();
                updateListOfGroups();
            }

            else if (currentIncomeGroupSelected != (currentAccount.IncomeGroupsNames.size()-1)){  ///Current number of groups
                ++currentIncomeGroupSelected;
                updateGroups();
                updateListOfGroups();
            }
        }
    }
    if (focusingGroups == false){
        this->focusGroups();
    }
}

void Gui_KeiboMoneyTracker::on_groupForwardButton_clicked()
{
    this->goToNextGroup();
}

void Gui_KeiboMoneyTracker::toggle_IncomeOutcomeGroup()
{
    if (ACCOUNT_SET)
    {
        if (showIncome){
            showIncome = false;
            if (currentAccount.getTotalExpensesInYear() > 0.0 && currentGroupSelected == 0)//If "not classified" group is selected and amount of that group is zero go to first named group
            {
                std::vector<double>::iterator amountNotClassifiedExpenses = currentAccount.ExpensesGroupsAmounts.begin();
                if (*amountNotClassifiedExpenses == 0.0 && currentAccount.ExpensesGroupsAmounts.size() > 0)
                {
                    currentGroupSelected++;
                }
            }
            updateGroups();
            updateListOfGroups();
            if (currentAccount.getAccountLanguage() == ENGLISH) {
                ui->groupBoxGroups->setTitle("Expenses Groups");
            } else if (currentAccount.getAccountLanguage() == GERMAN) {
                ui->groupBoxGroups->setTitle("Gruppen Ausgaben");
            } else if (currentAccount.getAccountLanguage() == SPANISH) {
                ui->groupBoxGroups->setTitle("Grupos de egresos");
            }
        } else if (!showIncome) {
            showIncome = true;
            if (currentAccount.getTotalIncomeInYear() > 0.0 && currentIncomeGroupSelected == 0) //If "not classified" group is selected and amount of that group is zero go to first named group
            {
                std::vector<double>::iterator amountNotClassifiedIncomes = currentAccount.IncomeGroupsAmounts.begin();
                if (*amountNotClassifiedIncomes == 0.0 && currentAccount.IncomeGroupsAmounts.size() > 0)
                {
                    currentIncomeGroupSelected++;
                }
            }
            updateGroups();
            updateListOfGroups();
            if (currentAccount.getAccountLanguage() == ENGLISH) {
                ui->groupBoxGroups->setTitle("Income Groups");
            } else if (currentAccount.getAccountLanguage() == GERMAN) {
                ui->groupBoxGroups->setTitle("Gruppen Einkommen");
            } else if (currentAccount.getAccountLanguage() == SPANISH) {
                ui->groupBoxGroups->setTitle("Grupos de ingresos");
            }
        }
    }    
    if (focusingGroups == false){
        this->focusGroups();
    }
}

void Gui_KeiboMoneyTracker::on_pushButtonToggleGroups_clicked()  //Switch show Income/Outcome Groups
{
    this->toggle_IncomeOutcomeGroup();
}

void Gui_KeiboMoneyTracker::on_actionManage_Groups_triggered()
{
    if (ACCOUNT_SET) {
        ManageGroupsDialog manageGroupDialog;
        manageGroupDialog.setLanguage(currentAccount.getAccountLanguage());

        manageGroupDialog.setYearData(currentAccount, false);

        std::cout<<"All groups size: "<<currentAccount.ExpensesGroupsNames.size()<<'\n';
        manageGroupDialog.setModal(true);
        manageGroupDialog.setOverallThemeStyleSheet(currentOverallThemeStyleSheet, tablesStyleSheet, usingDarkTheme);
        manageGroupDialog.exec();

        currentAccount.clear_Year();
        currentAccount.loadExpensesGroups();
        currentAccount.set_Year(currentYear);
        bool yearDataExists = currentAccount.load_Data();

        if (yearDataExists && (currentAccount.allTransactionsOk == false)){
            eraseConfirmation_dialog eraseConfirmationWindow;
            eraseConfirmationWindow.setModal(true);
            eraseConfirmationWindow.setOverallThemeStyleSheet(currentOverallThemeStyleSheet, usingDarkTheme);
            if (currentAccount.getAccountLanguage() == ENGLISH)            {
                eraseConfirmationWindow.setWindowTitle(" Information");
                eraseConfirmationWindow.setInfoText("The data file for the current year has been externally modified. Please verify the following transactions.");
            } else if (currentAccount.getAccountLanguage() == GERMAN) {
                eraseConfirmationWindow.setWindowTitle(" Information");
                eraseConfirmationWindow.setInfoText("Die Datei für das gewählte Jahr wurde gerändert. Bitte prüfen Sie die folgenden Transaktionen.");
            } else if (currentAccount.getAccountLanguage() == SPANISH) {
                eraseConfirmationWindow.setWindowTitle(" Información");
                eraseConfirmationWindow.setInfoText("El archivo de datos del año seleccionado ha sido externamente modificado. Por favor verifique las siguientes transacciones.");
            }
            eraseConfirmationWindow.exec();

            //Gather data to be passed to checkFaultyTransactionData
            std::vector<Transaction> listOfFaultyTransactions;
            for (unsigned int i = 0; i != currentAccount.listOfFaultyTransactionsInfo.size(); ++i){
                listOfFaultyTransactions.push_back(currentAccount.Yearly_Articles
                                                       [currentAccount.listOfFaultyTransactionsInfo[i].month]
                                                       [currentAccount.listOfFaultyTransactionsInfo[i].id]
                                                      );
            }

            //Delete all faulty transactions
            for (int xmonth = 0; xmonth != 12; ++xmonth){
                std::vector<int> elementsToDelete;
                for (unsigned int i = 0; i != currentAccount.listOfFaultyTransactionsInfo.size(); ++i){
                    if(currentAccount.listOfFaultyTransactionsInfo[i].month == xmonth ){
                        elementsToDelete.push_back(currentAccount.listOfFaultyTransactionsInfo[i].id);
                    }
                }
                if (elementsToDelete.size()>0){
                    currentAccount.deleteMultipleTransactionsInMonth(xmonth, elementsToDelete);
                }
            }

            //Set data on checkFaultyTransactionsDialog
            checkFaultyTransactionsDialog checkTransactionsDialog;
            checkTransactionsDialog.setModal(true);
            checkTransactionsDialog.setLanguage(currentAccount.getAccountLanguage());
            checkTransactionsDialog.getFaultyTransactionsData(listOfFaultyTransactions, currentAccount.getYear());
            checkTransactionsDialog.getGroups(currentAccount.IncomeGroupsNames, currentAccount.ExpensesGroupsNames);
            checkTransactionsDialog.updateInfo();
            checkTransactionsDialog.setOverallThemeStyleSheet(currentOverallThemeStyleSheet, usingDarkTheme);
            checkTransactionsDialog.exec();

            //Get updated data
            std::vector<Transaction> listOfUpdatedTransactions;
            checkTransactionsDialog.provideUpdatedTransactions(listOfUpdatedTransactions);
            if (listOfUpdatedTransactions.size()>0){
                std::vector<Transaction>::iterator itUpdatedTransactions;
                for (itUpdatedTransactions = listOfUpdatedTransactions.begin(); itUpdatedTransactions != listOfUpdatedTransactions.end(); ++itUpdatedTransactions)
                {
                    this->currentAccount.addTransaction(*itUpdatedTransactions);
                }
                this->currentAccount.save_Data();
            }
        }

        if (manageGroupDialog.groupWasAdded())
        {
            updateGroups();
            updateListOfGroups();
        }

        else if (manageGroupDialog.groupWasEdited())
        {
            updateGroups();
            displayArticlesOnTable();
            updateListOfGroups();
        }

        else if (manageGroupDialog.groupWasDeleted())
        {
            //--currentGroupSelected; //If more than one group is deleted a -1 decrement will make the program crash.
            currentGroupSelected = 0;
            updateGroups();
            displayArticlesOnTable();
            updateListOfGroups();
        }
    }   else {
        eraseConfirmation_dialog iAccountCreationConfirmedDialog;
        iAccountCreationConfirmedDialog.setModal(true);
        iAccountCreationConfirmedDialog.setOverallThemeStyleSheet(currentOverallThemeStyleSheet, usingDarkTheme);
        if (initialLanguage == ENGLISH) {
            iAccountCreationConfirmedDialog.setWindowTitle(" Information");
            iAccountCreationConfirmedDialog.setInfoText("Please create or select an account first.");
        } else if (initialLanguage == GERMAN) {
            iAccountCreationConfirmedDialog.setWindowTitle(" Information");
            iAccountCreationConfirmedDialog.setInfoText("Bitte erstellen/wählen Sie zuerst ein Konto.");
        } else if (initialLanguage == SPANISH) {
            iAccountCreationConfirmedDialog.setWindowTitle(" Información");
            iAccountCreationConfirmedDialog.setInfoText("Por favor cree o seleccione una cuenta primero.");
        }

        iAccountCreationConfirmedDialog.exec();
    }
}

void Gui_KeiboMoneyTracker::on_actionManage_Income_Groups_triggered()
{
    if (ACCOUNT_SET) {
        ManageGroupsDialog manageGroupDialog;
        manageGroupDialog.setLanguage(currentAccount.getAccountLanguage());

        manageGroupDialog.setYearData(currentAccount, true);

        std::cout<<"All groups size: "<<currentAccount.IncomeGroupsNames.size()<<'\n';
        manageGroupDialog.setModal(true);
        manageGroupDialog.setOverallThemeStyleSheet(currentOverallThemeStyleSheet, tablesStyleSheet, usingDarkTheme);
        manageGroupDialog.exec();

        currentAccount.clear_Year();
        currentAccount.loadIncomeGroups();
        currentAccount.set_Year(currentYear);
        bool yearDataExists = currentAccount.load_Data();

        if (yearDataExists && (currentAccount.allTransactionsOk == false)){
            eraseConfirmation_dialog eraseConfirmationWindow;
            eraseConfirmationWindow.setModal(true);
            eraseConfirmationWindow.setOverallThemeStyleSheet(currentOverallThemeStyleSheet, usingDarkTheme);
            if (currentAccount.getAccountLanguage() == ENGLISH)            {
                eraseConfirmationWindow.setWindowTitle(" Information");
                eraseConfirmationWindow.setInfoText("The data file for the current year has been externally modified. Please verify the following transactions.");
            } else if (currentAccount.getAccountLanguage() == GERMAN) {
                eraseConfirmationWindow.setWindowTitle(" Information");
                eraseConfirmationWindow.setInfoText("Die Datei für das gewählte Jahr wurde gerändert. Bitte prüfen Sie die folgenden Transaktionen.");
            } else if (currentAccount.getAccountLanguage() == SPANISH) {
                eraseConfirmationWindow.setWindowTitle(" Información");
                eraseConfirmationWindow.setInfoText("El archivo de datos del año seleccionado ha sido externamente modificado. Por favor verifique las siguientes transacciones.");
            }
            eraseConfirmationWindow.exec();

            //Gather data to be passed to checkFaultyTransactionData
            std::vector<Transaction> listOfFaultyTransactions;
            for (unsigned int i = 0; i != currentAccount.listOfFaultyTransactionsInfo.size(); ++i){
                listOfFaultyTransactions.push_back(currentAccount.Yearly_Articles
                                                       [currentAccount.listOfFaultyTransactionsInfo[i].month]
                                                       [currentAccount.listOfFaultyTransactionsInfo[i].id]
                                                      );
            }

            //Delete all faulty transactions
            for (int xmonth = 0; xmonth != 12; ++xmonth){
                std::vector<int> elementsToDelete;
                for (unsigned int i = 0; i != currentAccount.listOfFaultyTransactionsInfo.size(); ++i){
                    if(currentAccount.listOfFaultyTransactionsInfo[i].month == xmonth ){
                        elementsToDelete.push_back(currentAccount.listOfFaultyTransactionsInfo[i].id);
                    }
                }
                if (elementsToDelete.size()>0){
                    currentAccount.deleteMultipleTransactionsInMonth(xmonth, elementsToDelete);
                }
            }

            //Set data on checkFaultyTransactionsDialog
            checkFaultyTransactionsDialog checkTransactionsDialog;
            checkTransactionsDialog.setModal(true);
            checkTransactionsDialog.setLanguage(currentAccount.getAccountLanguage());
            checkTransactionsDialog.getFaultyTransactionsData(listOfFaultyTransactions, currentAccount.getYear());
            checkTransactionsDialog.getGroups(currentAccount.IncomeGroupsNames, currentAccount.ExpensesGroupsNames);
            checkTransactionsDialog.updateInfo();
            checkTransactionsDialog.setOverallThemeStyleSheet(currentOverallThemeStyleSheet, usingDarkTheme);
            checkTransactionsDialog.exec();

            //Get updated data
            std::vector<Transaction> listOfUpdatedTransactions;
            checkTransactionsDialog.provideUpdatedTransactions(listOfUpdatedTransactions);
            if (listOfUpdatedTransactions.size()>0){
                std::vector<Transaction>::iterator itUpdatedTransactions;
                for (itUpdatedTransactions = listOfUpdatedTransactions.begin(); itUpdatedTransactions != listOfUpdatedTransactions.end(); ++itUpdatedTransactions)
                {
                    this->currentAccount.addTransaction(*itUpdatedTransactions);
                }
                this->currentAccount.save_Data();
            }
        }

        if (manageGroupDialog.groupWasAdded())
        {
            updateGroups();
            updateListOfGroups();
        }

        else if (manageGroupDialog.groupWasEdited())
        {
            updateGroups();
            displayArticlesOnTable();
            updateListOfGroups();
        }

        else if (manageGroupDialog.groupWasDeleted())
        {
            currentIncomeGroupSelected = 0;
            updateGroups();
            displayArticlesOnTable();
            updateListOfGroups();
        }
    } else {
        eraseConfirmation_dialog iAccountCreationConfirmedDialog;
        iAccountCreationConfirmedDialog.setModal(true);
        iAccountCreationConfirmedDialog.setOverallThemeStyleSheet(currentOverallThemeStyleSheet, usingDarkTheme);
        if (initialLanguage == ENGLISH) {
            iAccountCreationConfirmedDialog.setWindowTitle(" Information");
            iAccountCreationConfirmedDialog.setInfoText("Please create or select an account first.");
        } else if (initialLanguage == GERMAN) {
            iAccountCreationConfirmedDialog.setWindowTitle(" Information");
            iAccountCreationConfirmedDialog.setInfoText("Bitte erstellen/wählen Sie zuerst ein Konto.");
        } else if (initialLanguage == SPANISH) {
            iAccountCreationConfirmedDialog.setWindowTitle(" Información");
            iAccountCreationConfirmedDialog.setInfoText("Por favor cree o seleccione una cuenta primero.");
        }
        iAccountCreationConfirmedDialog.exec();
    }
}

void Gui_KeiboMoneyTracker::updateToClickedMonth()
{
    //std::cout<<"START updateToClickedMonth"<<'\n';
    this->ui->widget1->processMouseClick();
    int x = this->ui->widget1->getSelectedMonthByClick(); //If click was done on any Area belonging to a month returns the month number, otherwise it returns -1
    if (x >= 0){
        this->currentMonth = x;
        this->updateToCurrentMonth();
    }
    //std::cout<<"END updateToClickedMonth"<<'\n';
}

void Gui_KeiboMoneyTracker::on_actionExit_triggered()
{
    this->close();
}

void Gui_KeiboMoneyTracker::on_actionHow_to_use_triggered()
{
    UserGuide iUserGuide;
    iUserGuide.setCurrentLanguage(initialLanguage);
    iUserGuide.exec();
}

void Gui_KeiboMoneyTracker::showAccountStats()
{
    //Create Account info text
    QString accountName = QString::fromStdString(currentAccount.getAccountName());
    QString accountCurrency = QString::fromStdString(currentAccount.getAccountCurrencyString());
    QString accountLanguage = QString::fromStdString(currentAccount.getAccountLanguageString());

    ////////////////////////////////////////////// Gather all years containing data //////////////////////////////////////////////////////////////////////
    std::vector<Account> listOfYearsWithData;

    //Search from 1900 until 2100
    bool dataExists = false;
    Account tempAccount;
    tempAccount.setAccountFolderPath(currentAccount.getAccountFolderPath());
    tempAccount.loadIncomeGroups();
    tempAccount.loadExpensesGroups();
    for (int x = 1900; x != 2201; ++x)
    {
        tempAccount.clear_Year();
        tempAccount.set_Year(x);
        if (tempAccount.load_Data()){
            if (tempAccount.getTotalNumberOfElements() > 0) {
                //std::cout<<"YEAR "<<x<<" HAS DATA"<<'\n';
                listOfYearsWithData.push_back(tempAccount);
                dataExists = true;
                }
        }
    }

    if (dataExists)
    {
        //Declare temporary variables
        Language accountLanguage = this->currentAccount.getAccountLanguage();

        int totalNumberOfElements           = 0;
        int totalNumberOfIncomeElements     = 0;
        int totalNumberOfExpensesElements   = 0;

        double totalLifetimeIncome   = 0.0;
        double totalLifetimeExpenses = 0.0;
        double averageMonthlyIncomeAmount   = 0.0f;
        double averageMonthlyExpensesAmount = 0.0f;

        bool firstElementFound = false;
        Transaction firstElement; int firstElementYear = 0;
        Transaction lastElement;  int lastElementYear = 0;

        Transaction highestIncomeElement;  int highestIncomeElementYear  = 0;
        Transaction highestExpenseElement; int highestExpenseElementYear = 0;

        double highestYearlyIncome   = 0.0; int highestYearlyIncome_Year   = 0;
        double highestYearlyExpenses = 0.0; int highestYearlyExpenses_Year = 0;
        double lowestYearlyIncome    = 0.0; bool firstYearlyIncomeAsLowestSet   = false; int lowestYearlyIncome_Year   = 0;
        double lowestYearlyExpenses  = 0.0; bool firstYearlyExpensesAsLowestSet = false; int lowestYearlyExpenses_Year = 0;

        double highestMonthlyIncome   = 0.0; int highestMonthlyIncome_Month   = 0; int highestMonthlyIncome_Year   = 0;
        double highestMonthlyExpenses = 0.0; int highestMonthlyExpenses_Month = 0; int highestMonthlyExpenses_Year = 0;

        double lowestMonthlyIncome   = 0.0; int lowestMonthlyIncome_Month   = 0; int lowestMonthlyIncome_Year   = 0; bool firstMonthlyIncomeAsLowestSet     = false;
        double lowestMonthlyExpenses = 0.0; int lowestMonthlyExpenses_Month = 0; int lowestMonthlyExpenses_Year = 0; bool firstMonthlyExpensesAsLowestSet   = false;

        std::string groupWithHighestYearlyIncome;    double groupWithHighestYearlyIncome_Amount;   int groupWithHighestYearlyIncome_Year;
        std::string groupWithHighestYearlyExpenses;  double groupWithHighestYearlyExpenses_Amount; int groupWithHighestYearlyExpenses_Year;
        std::string groupWithLowestYearlyIncome;     double groupWithLowestYearlyIncome_Amount;    int groupWithLowestYearlyIncome_Year;    bool firstGroupsWithLowestYearlyIncomeSet    = false;
        std::string groupWithLowestYearlyExpenses;   double groupWithLowestYearlyExpenses_Amount;  int groupWithLowestYearlyExpenses_Year;  bool firstGroupsWithLowestYearlyExpensesSet  = false;

        int yearWithHighestNumberOfTransactions = 0; int yearWithHighestNumberOfTransactions_NumberOfTransactions = 0;
        int yearWithLowestNumberOfTransactions  = 0; int yearWithLowestNumberOfTransactions_NumberOfTransactions  = 0; bool firstYearWithLowestNumberOfTransactionsSet = false;

        ///////////////////////////////////////////////// Search in all years with data to calculate and fetch Values //////////////////////////////////////////////////////////
        std::vector<Account>::iterator yearIterator;
        for (yearIterator = listOfYearsWithData.begin(); yearIterator != listOfYearsWithData.end(); ++yearIterator)
        {
            //Number of elements
            totalNumberOfElements           += yearIterator->getTotalNumberOfElements();
            totalNumberOfIncomeElements     += yearIterator->getTotalNumberOfIncomeElements();
            totalNumberOfExpensesElements   += yearIterator->getTotalNumberOfExpensesElements();

            //Get year with highest number of elements
            if (yearWithHighestNumberOfTransactions_NumberOfTransactions < yearIterator->getTotalNumberOfElements()){
                yearWithHighestNumberOfTransactions_NumberOfTransactions = yearIterator->getTotalNumberOfElements();
                yearWithHighestNumberOfTransactions = yearIterator->getYear();
            }

            //Get year with lowest number of elements
            if (!firstYearWithLowestNumberOfTransactionsSet) {
                if (yearIterator->getTotalNumberOfElements() > 0){
                    yearWithLowestNumberOfTransactions_NumberOfTransactions = yearIterator->getTotalNumberOfElements();
                    yearWithLowestNumberOfTransactions = yearIterator->getYear();
                    firstYearWithLowestNumberOfTransactionsSet = true;
                }
            }else if (firstYearWithLowestNumberOfTransactionsSet){
                if (yearIterator->getTotalNumberOfElements() < yearWithLowestNumberOfTransactions_NumberOfTransactions){
                    yearWithLowestNumberOfTransactions_NumberOfTransactions = yearIterator->getTotalNumberOfElements();
                    yearWithLowestNumberOfTransactions = yearIterator->getYear();
                }
            }

            //Find first element (according to date)
            if (!firstElementFound){
                yearIterator->getFirstElement(firstElement);
                firstElementYear = yearIterator->getYear();
                firstElementFound = true;
            }

            //Find last element (according to date)
            if (yearIterator == (listOfYearsWithData.end()-1)){//Check only last year with data
                yearIterator->getLastElement(lastElement);
                lastElementYear = yearIterator->getYear();
            }

            //Highest Overall(Lifetime) Income/Expense Element/Transaction
            Transaction tempHighestIncomeInYearElement;
            yearIterator->getHighestIncomeInYear_Transaction(tempHighestIncomeInYearElement);
            if (highestIncomeElement.Amount < tempHighestIncomeInYearElement.Amount){
                highestIncomeElement = tempHighestIncomeInYearElement;
                highestIncomeElementYear = yearIterator->getYear();
            }
            Transaction tempHighestExpenseInYearElement;
            yearIterator->getHighestExpenseInYear_Transaction(tempHighestExpenseInYearElement);
            if (highestExpenseElement.Amount < tempHighestExpenseInYearElement.Amount){
                highestExpenseElement = tempHighestExpenseInYearElement;
                highestExpenseElementYear = yearIterator->getYear();
            }

            //Highest Yearly Income and Expenses (Lifetime)
            if (yearIterator->getTotalIncomeInYear() > highestYearlyIncome){
                highestYearlyIncome = yearIterator->getTotalIncomeInYear();
                highestYearlyIncome_Year = yearIterator->getYear();
            }
            if (yearIterator->getTotalExpensesInYear() > highestYearlyExpenses){
                highestYearlyExpenses = yearIterator->getTotalExpensesInYear();
                highestYearlyExpenses_Year = yearIterator->getYear();
            }

            //Lowest Yearly Income and Expenses (Lifetime)
            if (yearIterator->getTotalNumberOfIncomeElements() > 0){
                if (firstYearlyIncomeAsLowestSet && (yearIterator->getTotalIncomeInYear() < lowestYearlyIncome)){
                    lowestYearlyIncome = yearIterator->getTotalIncomeInYear();
                    lowestYearlyIncome_Year = yearIterator->getYear();
                }
                else if ( (firstYearlyIncomeAsLowestSet == false) && (yearIterator->getTotalIncomeInYear() > 0.00)){
                    lowestYearlyIncome = yearIterator->getTotalIncomeInYear();
                    lowestYearlyIncome_Year = yearIterator->getYear();
                    firstYearlyIncomeAsLowestSet = true;
                }
            }

            if (yearIterator->getTotalNumberOfExpensesElements() > 0)
            {
                if (firstYearlyExpensesAsLowestSet && (yearIterator->getTotalExpensesInYear() < lowestYearlyExpenses)){
                    lowestYearlyExpenses = yearIterator->getTotalExpensesInYear();
                    lowestYearlyExpenses_Year = yearIterator->getYear();
                }
                else if ( (firstYearlyExpensesAsLowestSet == false ) && (yearIterator->getTotalExpensesInYear() > 0.00)){
                    lowestYearlyExpenses = yearIterator->getTotalExpensesInYear();
                    lowestYearlyExpenses_Year = yearIterator->getYear();
                    firstYearlyExpensesAsLowestSet = true;
                }
            }

            //Highest Monthly Income and Expenses (Lifetime)
            double tempHighestMonthlyIncome = 0.0;
            int    tempHighestMonthlyIncome_Month = 0;
            yearIterator->getHighestMonthlyIncomeInYear(tempHighestMonthlyIncome, tempHighestMonthlyIncome_Month);
            if (tempHighestMonthlyIncome > highestMonthlyIncome){
                highestMonthlyIncome = tempHighestMonthlyIncome;
                highestMonthlyIncome_Month = tempHighestMonthlyIncome_Month;
                highestMonthlyIncome_Year = yearIterator->getYear();
            }

            double tempHighestMonthlyExpenses = 0.0;
            int    tempHighestMonthlyExpenses_Month = 0;
            yearIterator->getHighestMonthlyExpensesInYear(tempHighestMonthlyExpenses, tempHighestMonthlyExpenses_Month);
            if (tempHighestMonthlyExpenses > highestMonthlyExpenses){
                highestMonthlyExpenses = tempHighestMonthlyExpenses;
                highestMonthlyExpenses_Month = tempHighestMonthlyExpenses_Month;
                highestMonthlyExpenses_Year = yearIterator->getYear();
            }

            //Lowest Monthly Income and Expenses (Lifetime)
            double tempLowestMonthlyIncome = 0.0;
            int    tempLowestMonthlyIncome_Month = 0;
            if (firstMonthlyIncomeAsLowestSet){
                yearIterator->getLowestMonthlyIncomeInYear(tempLowestMonthlyIncome, tempLowestMonthlyIncome_Month);
                if ((tempLowestMonthlyIncome < lowestMonthlyIncome) && (tempLowestMonthlyIncome > 0.0)){
                    lowestMonthlyIncome = tempLowestMonthlyIncome;
                    lowestMonthlyIncome_Month = tempLowestMonthlyIncome_Month;
                    lowestMonthlyIncome_Year  = yearIterator->getYear();
                }
            }  else if (!firstMonthlyIncomeAsLowestSet){
                yearIterator->getLowestMonthlyIncomeInYear(lowestMonthlyIncome, lowestMonthlyIncome_Month);
                if (lowestMonthlyIncome > 0.0){
                    lowestMonthlyIncome_Year = yearIterator->getYear();
                    firstMonthlyIncomeAsLowestSet = true;
                }
            }

            double tempLowestMonthlyExpenses = 0.0;
            int    tempLowestMonthlyExpenses_Month = 0;
            if (firstMonthlyExpensesAsLowestSet){
                yearIterator->getLowestMonthlyExpensesInYear(tempLowestMonthlyExpenses, tempLowestMonthlyExpenses_Month);
                if ((tempLowestMonthlyExpenses < lowestMonthlyExpenses) && (tempLowestMonthlyExpenses > 0.0)){
                    lowestMonthlyExpenses = tempLowestMonthlyExpenses;
                    lowestMonthlyExpenses_Month = tempLowestMonthlyExpenses_Month;
                    lowestMonthlyExpenses_Year  = yearIterator->getYear();
                }
            }  else if (!firstMonthlyExpensesAsLowestSet){
                yearIterator->getLowestMonthlyExpensesInYear(lowestMonthlyExpenses, lowestMonthlyExpenses_Month);
                if (lowestMonthlyExpenses > 0.0){
                    lowestMonthlyExpenses_Year = yearIterator->getYear();
                    firstMonthlyExpensesAsLowestSet = true;
                }
            }

            //Group with Highest Yearly Income and Expenses  (Lifetime)
            std::string tempGroupWithHighestYearlyIncome;
            double tempGroupWithHighestYearlyIncome_Amount = 0.0;
                yearIterator->getGroupWithHighestIncomeInYear(tempGroupWithHighestYearlyIncome, tempGroupWithHighestYearlyIncome_Amount);
                if ( (groupWithHighestYearlyIncome_Amount < tempGroupWithHighestYearlyIncome_Amount) && (tempGroupWithHighestYearlyIncome != "N/A")){
                    groupWithHighestYearlyIncome_Amount = tempGroupWithHighestYearlyIncome_Amount;
                    groupWithHighestYearlyIncome = tempGroupWithHighestYearlyIncome;
                    groupWithHighestYearlyIncome_Year = yearIterator->getYear();
                }

            std::string tempGroupWithHighestYearlyExpenses;
            double tempGroupWithHighestYearlyExpenses_Amount = 0.0;
                yearIterator->getGroupWithHighestExpensesInYear(tempGroupWithHighestYearlyExpenses, tempGroupWithHighestYearlyExpenses_Amount);
                if ( (groupWithHighestYearlyExpenses_Amount < tempGroupWithHighestYearlyExpenses_Amount) && (tempGroupWithHighestYearlyExpenses != "N/A")){
                    groupWithHighestYearlyExpenses_Amount = tempGroupWithHighestYearlyExpenses_Amount;
                    groupWithHighestYearlyExpenses = tempGroupWithHighestYearlyExpenses;
                    groupWithHighestYearlyExpenses_Year = yearIterator->getYear();
                }

            //Group with Lowest Yearly Income and Expenses  (Lifetime)
            std::string tempGroupWithLowestYearlyIncome = "N/A";
            double tempGroupWithLowestYearlyIncome_Amount = 0.0;
            if (firstGroupsWithLowestYearlyIncomeSet) {
                yearIterator->getGroupWithLowestIncomeInYear(tempGroupWithLowestYearlyIncome, tempGroupWithLowestYearlyIncome_Amount);
                if ((groupWithLowestYearlyIncome_Amount > tempGroupWithLowestYearlyIncome_Amount) && (tempGroupWithLowestYearlyIncome != "N/A")){
                    groupWithLowestYearlyIncome_Amount = tempGroupWithLowestYearlyIncome_Amount;
                    groupWithLowestYearlyIncome = tempGroupWithLowestYearlyIncome;
                    groupWithLowestYearlyIncome_Year = yearIterator->getYear();
                }
            } else if (!firstGroupsWithLowestYearlyIncomeSet) {
                yearIterator->getGroupWithLowestIncomeInYear(tempGroupWithLowestYearlyIncome, tempGroupWithLowestYearlyIncome_Amount);
                if (tempGroupWithLowestYearlyIncome != "N/A")
                {
                    groupWithLowestYearlyIncome = tempGroupWithLowestYearlyIncome;
                    groupWithLowestYearlyIncome_Amount = tempGroupWithLowestYearlyIncome_Amount;
                    groupWithLowestYearlyIncome_Year = yearIterator->getYear();
                    firstGroupsWithLowestYearlyIncomeSet = true;
                }
            }
            std::string tempGroupWithLowestYearlyExpenses = "N/A";
            double tempGroupWithLowestYearlyExpenses_Amount = 0.0;
            if (firstGroupsWithLowestYearlyExpensesSet) {
                yearIterator->getGroupWithLowestExpensesInYear(tempGroupWithLowestYearlyExpenses, tempGroupWithLowestYearlyExpenses_Amount);
                if ((groupWithLowestYearlyExpenses_Amount > tempGroupWithLowestYearlyExpenses_Amount) && (tempGroupWithLowestYearlyExpenses != "N/A")){
                    groupWithLowestYearlyExpenses_Amount = tempGroupWithLowestYearlyExpenses_Amount;
                    groupWithLowestYearlyExpenses = tempGroupWithLowestYearlyExpenses;
                    groupWithLowestYearlyExpenses_Year = yearIterator->getYear();
                }
            } else if (!firstGroupsWithLowestYearlyExpensesSet) {
                yearIterator->getGroupWithLowestExpensesInYear(tempGroupWithLowestYearlyExpenses, tempGroupWithLowestYearlyExpenses_Amount);
                if (tempGroupWithLowestYearlyExpenses != "N/A")
                {
                    groupWithLowestYearlyExpenses = tempGroupWithLowestYearlyExpenses;
                    groupWithLowestYearlyExpenses_Amount = tempGroupWithLowestYearlyExpenses_Amount;
                    groupWithLowestYearlyExpenses_Year = yearIterator->getYear();
                    firstGroupsWithLowestYearlyExpensesSet = true;
                }
            }

            //Total lifetime income and expenses
            totalLifetimeIncome   += yearIterator->getTotalIncomeInYear();
            totalLifetimeExpenses += yearIterator->getTotalExpensesInYear();
        }

        //Averages, this is considered for the interval of time.
        int firstMonth = firstElement.Month;
        int lastMonth  = lastElement.Month;
        averageMonthlyIncomeAmount   = getAveragePerMonthInInterval(totalLifetimeIncome, firstMonth, firstElementYear,
                                                                                       lastMonth, lastElementYear);
        averageMonthlyExpensesAmount = getAveragePerMonthInInterval(totalLifetimeExpenses, firstMonth, firstElementYear,
                                                                    lastMonth, lastElementYear);


        //////////////////////////////////////////////////////////////// Create Text ////////////////////////////////////////////////////////////////////////////////
        std::vector<QString> statsNames;
        std::vector<QString> statsValues;

        //Create Text for time interval: Date first transactions - Date last transaction
        QString textTimeInterval;

        //Create text for total number of elements
        QString textTotalNumberOfTransactions     = QString::number(totalNumberOfElements);
        QString textTotalNumberOfIncomeElements   = QString::number(totalNumberOfIncomeElements);
        QString textTotalNumberOfExpensesElements = QString::number(totalNumberOfExpensesElements);

        //Create text for monthly averages
        QString textAverageMonthlyIncome;
        QString textAverageMonthlyExpenses;

        //Create text for highest overall (lifetime) income and expense elements
        QString textHighestOverallIncome;
        QString textHighestOverallExpense;

        //Create text for highest/lowest yearly income/expenses
        QString textHighestYearlyIncome;
        QString textHighestYearlyExpenses;
        QString textLowestYearlyIncome;
        QString textLowestYearlyExpenses;

        //Create text for highest monthly income/expenses
        QString textHighestMonthlyIncome;
        QString textHighestMonthlyExpenses;

        //Create text for lowest monthly income/expenses
        QString textLowestMonthlyIncome;
        QString textLowestMonthlyExpenses;

        //Create text for highest yearly income/expenses groups
        QString textGroupWithHighestYearlyIncome;
        QString textGroupWithHighestYearlyExpenses;
        QString textGroupWithLowestYearlyIncome;
        QString textGroupWithLowestYearlyExpenses;

        //Create text for year with highest number of elements
        QString textYearWithHighestNumberOfTransactions;

        //Create text for year with lowest number of elements
        QString textYearWithLowestNumberOfTransactions;

        AccountStatsDialog iAccountStatsDialog;
        iAccountStatsDialog.setModal(true);
        iAccountStatsDialog.setThemeStyleSheet(currentOverallThemeStyleSheet);

        //////////////////////////////////////////////////////////////// ENGLISH ////////////////////////////////////////////////////////////////////////////////
        if (accountLanguage == ENGLISH){
            statsNames.push_back("Name:");
            statsNames.push_back("Currency:");
            statsNames.push_back("Language:");
            statsNames.push_back("Image Path");
            statsValues.push_back(QString::fromStdString(currentAccount.getAccountName()));
            statsValues.push_back(QString::fromStdString(currentAccount.getAccountCurrencyString()));
            statsValues.push_back(QString::fromStdString(currentAccount.getAccountLanguageString()));
            statsValues.push_back(QString::fromStdString(currentAccount.getAccountIconPath()));

            textTimeInterval = QString("From   "
                              +QString::fromStdString(getDateInLanguageFormat(firstElement.Day, firstElement.Month, firstElementYear, ENGLISH))
                              +"   until   "
                              +QString::fromStdString(getDateInLanguageFormat(lastElement.Day, lastElement.Month, lastElementYear, ENGLISH)) );
            statsNames.push_back("Time interval:");
            statsValues.push_back(textTimeInterval);

            statsNames.push_back("Total number of transactions:");
            statsNames.push_back("Number of income elements:");
            statsNames.push_back("Number of expenses elements:");
            statsValues.push_back(textTotalNumberOfTransactions);
            statsValues.push_back(textTotalNumberOfIncomeElements);
            statsValues.push_back(textTotalNumberOfExpensesElements);

            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            if (this->currentAccount.getAccountCurrencySymbol() == "$")
            {
                textAverageMonthlyIncome    = QString::fromStdString(this->currentAccount.getAccountCurrencySymbol())+QString::fromStdString(getAmountAsStringFormatted(averageMonthlyIncomeAmount));
                textAverageMonthlyExpenses  = QString::fromStdString(this->currentAccount.getAccountCurrencySymbol())+QString::fromStdString(getAmountAsStringFormatted(averageMonthlyExpensesAmount));
            } else {
                textAverageMonthlyIncome    = QString::fromStdString(getAmountAsStringFormatted(averageMonthlyIncomeAmount))+" "+QString::fromStdString(this->currentAccount.getAccountCurrencySymbol());
                textAverageMonthlyExpenses  = QString::fromStdString(getAmountAsStringFormatted(averageMonthlyExpensesAmount))+" "+QString::fromStdString(this->currentAccount.getAccountCurrencySymbol());
            }
            statsNames.push_back("Average monthly income:");
            statsNames.push_back("Average monthly expenses:");
            statsValues.push_back(textAverageMonthlyIncome);
            statsValues.push_back(textAverageMonthlyExpenses);

            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            if (highestIncomeElement.Name.empty()){
                textHighestOverallIncome = "Not available.";
            } else {
                if (this->currentAccount.getAccountCurrencySymbol() == "$")
                {
                    textHighestOverallIncome  = QString( QString::fromStdString(highestIncomeElement.Name)+"  "
                                                    +QString::fromStdString(this->currentAccount.getAccountCurrencySymbol())
                                                    +QString::fromStdString(getAmountAsStringFormatted(highestIncomeElement.Amount))
                                                    +"  on  "
                                                    +QString::fromStdString(getDateInLanguageFormat(highestIncomeElement.Day, highestIncomeElement.Month, highestIncomeElementYear, ENGLISH)) );
                } else {
                    textHighestOverallIncome  = QString( QString::fromStdString(highestIncomeElement.Name)+"  "
                                                    +QString::fromStdString(getAmountAsStringFormatted(highestIncomeElement.Amount))+" "
                                                    +QString::fromStdString(this->currentAccount.getAccountCurrencySymbol())+"  on  "
                                                    +QString::fromStdString(getDateInLanguageFormat(highestIncomeElement.Day, highestIncomeElement.Month, highestIncomeElementYear, ENGLISH)) );
                }
            }
            if (highestExpenseElement.Name.empty()){
                textHighestOverallExpense = "Not available.";
            } else {
                if (this->currentAccount.getAccountCurrencySymbol() == "$")
                {
                    textHighestOverallExpense = QString( QString::fromStdString(highestExpenseElement.Name)+"  "
                                                     +QString::fromStdString(this->currentAccount.getAccountCurrencySymbol())
                                                     +QString::fromStdString(getAmountAsStringFormatted(highestExpenseElement.Amount))
                                                     +"  on  "
                                                     +QString::fromStdString(getDateInLanguageFormat(highestExpenseElement.Day, highestExpenseElement.Month, highestExpenseElementYear, ENGLISH)) );
                } else {
                    textHighestOverallExpense = QString( QString::fromStdString(highestExpenseElement.Name)+"  "
                                                     +QString::fromStdString(getAmountAsStringFormatted(highestExpenseElement.Amount))+" "
                                                     +QString::fromStdString(this->currentAccount.getAccountCurrencySymbol())+"  on  "
                                                     +QString::fromStdString(getDateInLanguageFormat(highestExpenseElement.Day, highestExpenseElement.Month, highestExpenseElementYear, ENGLISH)) );
                }
            }
            statsNames.push_back("Highest income (single transaction):");
            statsNames.push_back("Highest expense (single transaction):");
            statsValues.push_back(textHighestOverallIncome);
            statsValues.push_back(textHighestOverallExpense);

            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            if (highestYearlyIncome_Year <= 0){
                textHighestYearlyIncome = "Not available.";
            } else {
                if (this->currentAccount.getAccountCurrencySymbol() == "$")
                {
                    textHighestYearlyIncome = QString::fromStdString(this->currentAccount.getAccountCurrencySymbol())
                                             +QString( QString::fromStdString(getAmountAsStringFormatted(highestYearlyIncome))
                                             +"  in  "
                                             +QString::number(highestYearlyIncome_Year) );
                } else {
                    textHighestYearlyIncome = QString( QString::fromStdString(getAmountAsStringFormatted(highestYearlyIncome))+" "
                                             +QString::fromStdString(this->currentAccount.getAccountCurrencySymbol())+"  in  "
                                             +QString::number(highestYearlyIncome_Year) );
                }

            }

            if (highestYearlyExpenses_Year <= 0){
                textHighestYearlyExpenses = "Not available.";
            } else {
                if (this->currentAccount.getAccountCurrencySymbol() == "$")
                {
                    textHighestYearlyExpenses = QString::fromStdString(this->currentAccount.getAccountCurrencySymbol())
                                               +QString( QString::fromStdString(getAmountAsStringFormatted(highestYearlyExpenses))
                                               +"  in  "
                                               +QString::number(highestYearlyExpenses_Year) );
                } else {
                    textHighestYearlyExpenses = QString( QString::fromStdString(getAmountAsStringFormatted(highestYearlyExpenses))+" "
                                               +QString::fromStdString(this->currentAccount.getAccountCurrencySymbol())+"  in  "
                                               +QString::number(highestYearlyExpenses_Year) );
                }
            }

            if (lowestYearlyIncome_Year <= 0){
                textLowestYearlyIncome = "Not available.";
            } else {
                if (this->currentAccount.getAccountCurrencySymbol() == "$")
                {
                    textLowestYearlyIncome = QString::fromStdString(this->currentAccount.getAccountCurrencySymbol())
                                            +QString( QString::fromStdString(getAmountAsStringFormatted(lowestYearlyIncome))
                                            +"  in  "
                                            +QString::number(lowestYearlyIncome_Year) );
                } else {
                    textLowestYearlyIncome = QString( QString::fromStdString(getAmountAsStringFormatted(lowestYearlyIncome))+" "
                                            +QString::fromStdString(this->currentAccount.getAccountCurrencySymbol())+"  in  "
                                            +QString::number(lowestYearlyIncome_Year) );
                }
            }

            if (lowestYearlyExpenses_Year <= 0){
                textLowestYearlyExpenses = "Not available.";
            } else {
                if (this->currentAccount.getAccountCurrencySymbol() == "$")
                {
                    textLowestYearlyExpenses = QString::fromStdString(this->currentAccount.getAccountCurrencySymbol())
                                              +QString( QString::fromStdString(getAmountAsStringFormatted(lowestYearlyExpenses))
                                              +"  in  "
                                              +QString::number(lowestYearlyExpenses_Year) );
                } else {
                    textLowestYearlyExpenses = QString( QString::fromStdString(getAmountAsStringFormatted(lowestYearlyExpenses))+" "
                                              +QString::fromStdString(this->currentAccount.getAccountCurrencySymbol())+"  in  "
                                              +QString::number(lowestYearlyExpenses_Year) );
                }
            }
            statsNames.push_back("Highest yearly income:");
            statsNames.push_back("Highest yearly expenses:");
            statsValues.push_back(textHighestYearlyIncome);
            statsValues.push_back(textHighestYearlyExpenses);
            statsNames.push_back("Lowest yearly income:");
            statsNames.push_back("Lowest yearly expenses:");
            statsValues.push_back(textLowestYearlyIncome);
            statsValues.push_back(textLowestYearlyExpenses);

            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            if (highestMonthlyIncome_Year > 0){
                if (this->currentAccount.getAccountCurrencySymbol() == "$")
                {
                    textHighestMonthlyIncome = QString::fromStdString(this->currentAccount.getAccountCurrencySymbol())
                                              +QString( QString::fromStdString(getAmountAsStringFormatted(highestMonthlyIncome))
                                              +"  in  "
                                              +QString::fromStdString(getMonthInLanguage(highestMonthlyIncome_Month, accountLanguage))+"  "
                                              +QString::number(highestMonthlyIncome_Year) );
                } else {
                    textHighestMonthlyIncome = QString( QString::fromStdString(getAmountAsStringFormatted(highestMonthlyIncome))+" "
                                              +QString::fromStdString(this->currentAccount.getAccountCurrencySymbol())+"  in  "
                                              +QString::fromStdString(getMonthInLanguage(highestMonthlyIncome_Month, accountLanguage))+"  "
                                              +QString::number(highestMonthlyIncome_Year) );
                }

            } else {
                textHighestMonthlyIncome = "Not available.";
            }

            if (highestMonthlyExpenses_Year > 0){
                if (this->currentAccount.getAccountCurrencySymbol() == "$")
                {
                    textHighestMonthlyExpenses = QString::fromStdString(this->currentAccount.getAccountCurrencySymbol())
                                                +QString( QString::fromStdString(getAmountAsStringFormatted(highestMonthlyExpenses))
                                                +"  in  "
                                                +QString::fromStdString(getMonthInLanguage(highestMonthlyExpenses_Month, accountLanguage))+"  "
                                                +QString::number(highestMonthlyExpenses_Year) );
                } else {
                    textHighestMonthlyExpenses = QString( QString::fromStdString(getAmountAsStringFormatted(highestMonthlyExpenses))+" "
                                                +QString::fromStdString(this->currentAccount.getAccountCurrencySymbol())+"  in  "
                                                +QString::fromStdString(getMonthInLanguage(highestMonthlyExpenses_Month, accountLanguage))+"  "
                                                +QString::number(highestMonthlyExpenses_Year) );
                }

            } else {
                textHighestMonthlyExpenses = "Not available.";
            }
            statsNames.push_back("Highest monthly income:");
            statsNames.push_back("Highest monthly expenses:");
            statsValues.push_back(textHighestMonthlyIncome);
            statsValues.push_back(textHighestMonthlyExpenses);

            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            if (lowestMonthlyIncome_Year > 0){
                if (this->currentAccount.getAccountCurrencySymbol() == "$")
                {
                    textLowestMonthlyIncome = QString::fromStdString(this->currentAccount.getAccountCurrencySymbol())
                                              +QString( QString::fromStdString(getAmountAsStringFormatted(lowestMonthlyIncome))
                                              +"  in  "
                                              +QString::fromStdString(getMonthInLanguage(lowestMonthlyIncome_Month, accountLanguage))+"  "
                                              +QString::number(lowestMonthlyIncome_Year) );
                } else {
                    textLowestMonthlyIncome = QString( QString::fromStdString(getAmountAsStringFormatted(lowestMonthlyIncome))+" "
                                              +QString::fromStdString(this->currentAccount.getAccountCurrencySymbol())+"  in  "
                                              +QString::fromStdString(getMonthInLanguage(lowestMonthlyIncome_Month, accountLanguage))+"  "
                                              +QString::number(lowestMonthlyIncome_Year) );
                }

            } else {
                textLowestMonthlyIncome = "Not available.";
            }

            if (lowestMonthlyExpenses_Year > 0){
                if (this->currentAccount.getAccountCurrencySymbol() == "$")
                {
                    textLowestMonthlyExpenses = QString::fromStdString(this->currentAccount.getAccountCurrencySymbol())
                                                +QString( QString::fromStdString(getAmountAsStringFormatted(lowestMonthlyExpenses))
                                                +"  in  "
                                                +QString::fromStdString(getMonthInLanguage(lowestMonthlyExpenses_Month, accountLanguage))+"  "
                                                +QString::number(lowestMonthlyExpenses_Year) );
                } else {
                    textLowestMonthlyExpenses = QString( QString::fromStdString(getAmountAsStringFormatted(lowestMonthlyExpenses))+" "
                                                +QString::fromStdString(this->currentAccount.getAccountCurrencySymbol())+"  in  "
                                                +QString::fromStdString(getMonthInLanguage(lowestMonthlyExpenses_Month, accountLanguage))+"  "
                                                +QString::number(lowestMonthlyExpenses_Year) );
                }

            } else {
                textLowestMonthlyExpenses = "Not available.";
            }
            statsNames.push_back("Lowest monthly income:");
            statsNames.push_back("Lowest monthly expenses:");
            statsValues.push_back(textLowestMonthlyIncome);
            statsValues.push_back(textLowestMonthlyExpenses);

            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            if (!groupWithHighestYearlyIncome.empty()){
                if (this->currentAccount.getAccountCurrencySymbol() == "$")
                {
                    textGroupWithHighestYearlyIncome = QString( QString::fromStdString(groupWithHighestYearlyIncome)+"  "   //group name
                                                      +QString::fromStdString(this->currentAccount.getAccountCurrencySymbol())
                                                      + QString::fromStdString(getAmountAsStringFormatted(groupWithHighestYearlyIncome_Amount))            //group amount
                                                      +"  in  "
                                                      +QString::number(groupWithHighestYearlyIncome_Year) );
                } else {
                    textGroupWithHighestYearlyIncome = QString( QString::fromStdString(groupWithHighestYearlyIncome)+"  "   //group name
                                                      + QString::fromStdString(getAmountAsStringFormatted(groupWithHighestYearlyIncome_Amount))+" "            //group amount
                                                      +QString::fromStdString(this->currentAccount.getAccountCurrencySymbol())+"  in  "
                                                      +QString::number(groupWithHighestYearlyIncome_Year) );
                }

            } else {
               textGroupWithHighestYearlyIncome = "Not available.";
            }

            if (!groupWithHighestYearlyExpenses.empty()){
                if (this->currentAccount.getAccountCurrencySymbol() == "$")
                {
                    textGroupWithHighestYearlyExpenses = QString( QString::fromStdString(groupWithHighestYearlyExpenses)+"  "   //group name
                                                        +QString::fromStdString(this->currentAccount.getAccountCurrencySymbol())
                                                        +QString::fromStdString(getAmountAsStringFormatted(groupWithHighestYearlyExpenses_Amount))          //group amount
                                                        +"  in  "
                                                        +QString::number(groupWithHighestYearlyExpenses_Year) );
                } else {
                    textGroupWithHighestYearlyExpenses = QString( QString::fromStdString(groupWithHighestYearlyExpenses)+"  "   //group name
                                                        +QString::fromStdString(getAmountAsStringFormatted(groupWithHighestYearlyExpenses_Amount))+" "            //group amount
                                                        +QString::fromStdString(this->currentAccount.getAccountCurrencySymbol())+"  in  "
                                                        +QString::number(groupWithHighestYearlyExpenses_Year) );
                }

            } else {
               textGroupWithHighestYearlyExpenses = "Not available.";
            }

            if (!groupWithLowestYearlyIncome.empty()){
                if (this->currentAccount.getAccountCurrencySymbol() == "$")
                {
                    textGroupWithLowestYearlyIncome = QString( QString::fromStdString(groupWithLowestYearlyIncome)+"  "   //group name
                                                     +QString::fromStdString(this->currentAccount.getAccountCurrencySymbol())
                                                     +QString::fromStdString(getAmountAsStringFormatted(groupWithLowestYearlyIncome_Amount))                //group amount
                                                     +"  in  "
                                                     +QString::number(groupWithLowestYearlyIncome_Year) );
                } else {
                    textGroupWithLowestYearlyIncome = QString( QString::fromStdString(groupWithLowestYearlyIncome)+"  "   //group name
                                                     +QString::fromStdString(getAmountAsStringFormatted(groupWithLowestYearlyIncome_Amount))+" "                //group amount
                                                     +QString::fromStdString(this->currentAccount.getAccountCurrencySymbol())+"  in  "
                                                     +QString::number(groupWithLowestYearlyIncome_Year) );
                }

            } else {
               textGroupWithLowestYearlyIncome = "Not available.";
            }

            if (!groupWithLowestYearlyExpenses.empty()){
                if (this->currentAccount.getAccountCurrencySymbol() == "$")
                {
                    textGroupWithLowestYearlyExpenses = QString( QString::fromStdString(groupWithLowestYearlyExpenses)+"  "   //group name
                                                       +QString::fromStdString(this->currentAccount.getAccountCurrencySymbol())
                                                       +QString::fromStdString(getAmountAsStringFormatted(groupWithLowestYearlyExpenses_Amount))               //group amount
                                                       +"  in  "
                                                       +QString::number(groupWithLowestYearlyExpenses_Year) );
                } else {
                    textGroupWithLowestYearlyExpenses = QString( QString::fromStdString(groupWithLowestYearlyExpenses)+"  "   //group name
                                                       +QString::fromStdString(getAmountAsStringFormatted(groupWithLowestYearlyExpenses_Amount))+" "                //group amount
                                                       +QString::fromStdString(this->currentAccount.getAccountCurrencySymbol())+"  in  "
                                                       +QString::number(groupWithLowestYearlyExpenses_Year) );
                }
            } else {
               textGroupWithLowestYearlyExpenses = "Not available.";
            }
            statsNames.push_back("Group with highest yearly income*:");
            statsNames.push_back("Group with highest yearly expenses*:");
            statsValues.push_back(textGroupWithHighestYearlyIncome);
            statsValues.push_back(textGroupWithHighestYearlyExpenses);
            statsNames.push_back("Group with lowest yearly income*:");
            statsNames.push_back("Group with lowest yearly expenses*:");
            statsValues.push_back(textGroupWithLowestYearlyIncome);
            statsValues.push_back(textGroupWithLowestYearlyExpenses);

            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            textYearWithHighestNumberOfTransactions = QString( QString::number(yearWithHighestNumberOfTransactions_NumberOfTransactions)+"  in  "
                                      +QString::number(yearWithHighestNumberOfTransactions) );
            statsNames.push_back("Year with highest number of transactions:");
            statsValues.push_back(textYearWithHighestNumberOfTransactions);

            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            textYearWithLowestNumberOfTransactions = QString( QString::number(yearWithLowestNumberOfTransactions_NumberOfTransactions)+"  in  "
                                      +QString::number(yearWithLowestNumberOfTransactions) );
            statsNames.push_back("Year with lowest number of transactions:");
            statsValues.push_back(textYearWithLowestNumberOfTransactions);

            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            statsNames.push_back("* Additional information.");
            statsValues.push_back("*Only classified transactions with amounts other than zero are considered.");
            iAccountStatsDialog.getAccountStats(statsNames, statsValues);
            iAccountStatsDialog.setWindowTitle(" Account");
        }


        //////////////////////////////////////////////////////////////// GERMAN ////////////////////////////////////////////////////////////////////////////////
        else if (accountLanguage == GERMAN){
            statsNames.push_back("Name:");
            statsNames.push_back("Währung:");
            statsNames.push_back("Sprache:");
            statsNames.push_back("Bild Pfad");
            statsValues.push_back(QString::fromStdString(currentAccount.getAccountName()));
            statsValues.push_back(QString::fromStdString(currentAccount.getAccountCurrencyString()));
            statsValues.push_back(QString::fromStdString(currentAccount.getAccountLanguageString()));
            statsValues.push_back(QString::fromStdString(currentAccount.getAccountIconPath()));

            textTimeInterval = QString("Von   "
                              +QString::fromStdString(getDateInLanguageFormat(firstElement.Day, firstElement.Month, firstElementYear, GERMAN))
                              +"   bis   "
                              +QString::fromStdString(getDateInLanguageFormat(lastElement.Day, lastElement.Month, lastElementYear, GERMAN)) );
            statsNames.push_back("Zeitraum:");
            statsValues.push_back(textTimeInterval);


            statsNames.push_back("Anzahl aller Transaktionen:");
            statsNames.push_back("Anzahl Transaktionen Einkommen:");
            statsNames.push_back("Anzahl Transaktionen Ausgabe:");
            statsValues.push_back(textTotalNumberOfTransactions);
            statsValues.push_back(textTotalNumberOfIncomeElements);
            statsValues.push_back(textTotalNumberOfExpensesElements);

            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            if (this->currentAccount.getAccountCurrencySymbol() == "$")
            {
                textAverageMonthlyIncome    = QString::fromStdString(this->currentAccount.getAccountCurrencySymbol())+QString::fromStdString(getAmountAsStringInGermanFormat(averageMonthlyIncomeAmount));
                textAverageMonthlyExpenses  = QString::fromStdString(this->currentAccount.getAccountCurrencySymbol())+QString::fromStdString(getAmountAsStringInGermanFormat(averageMonthlyExpensesAmount));
            } else {
                textAverageMonthlyIncome    = QString::fromStdString(getAmountAsStringInGermanFormat(averageMonthlyIncomeAmount))+" "+QString::fromStdString(this->currentAccount.getAccountCurrencySymbol());
                textAverageMonthlyExpenses  = QString::fromStdString(getAmountAsStringInGermanFormat(averageMonthlyExpensesAmount))+" "+QString::fromStdString(this->currentAccount.getAccountCurrencySymbol());
            }
            statsNames.push_back("Durchnittliches monatilches Einkommen:");
            statsNames.push_back("Durchnittliche monatilche Ausgabe:");
            statsValues.push_back(textAverageMonthlyIncome);
            statsValues.push_back(textAverageMonthlyExpenses);

            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            if (highestIncomeElement.Name.empty()){
                textHighestOverallIncome = "Nicht verfügbar.";
            } else {
                if (this->currentAccount.getAccountCurrencySymbol() == "$")
                {
                    textHighestOverallIncome  = QString( QString::fromStdString(highestIncomeElement.Name)+"  "
                                                    +QString::fromStdString(this->currentAccount.getAccountCurrencySymbol())
                                                    +QString::fromStdString(getAmountAsStringInGermanFormat(highestIncomeElement.Amount))
                                                    +"  am  "
                                                    +QString::fromStdString(getDateInLanguageFormat(highestIncomeElement.Day, highestIncomeElement.Month, highestIncomeElementYear, GERMAN)) );
                } else {
                    textHighestOverallIncome  = QString( QString::fromStdString(highestIncomeElement.Name)+"  "
                                                    +QString::fromStdString(getAmountAsStringInGermanFormat(highestIncomeElement.Amount))+" "
                                                    +QString::fromStdString(this->currentAccount.getAccountCurrencySymbol())+"  am  "
                                                    +QString::fromStdString(getDateInLanguageFormat(highestIncomeElement.Day, highestIncomeElement.Month, highestIncomeElementYear, GERMAN)) );
                }
            }
            if (highestExpenseElement.Name.empty()){
                textHighestOverallExpense = "Nicht verfügbar.";
            } else {
                if (this->currentAccount.getAccountCurrencySymbol() == "$")
                {
                    textHighestOverallExpense = QString( QString::fromStdString(highestExpenseElement.Name)+"  "
                                                     +QString::fromStdString(this->currentAccount.getAccountCurrencySymbol())
                                                     +QString::fromStdString(getAmountAsStringInGermanFormat(highestExpenseElement.Amount))
                                                     +"  am  "
                                                     +QString::fromStdString(getDateInLanguageFormat(highestExpenseElement.Day, highestExpenseElement.Month, highestExpenseElementYear, GERMAN)) );
                } else {
                    textHighestOverallExpense = QString( QString::fromStdString(highestExpenseElement.Name)+"  "
                                                     +QString::fromStdString(getAmountAsStringInGermanFormat(highestExpenseElement.Amount))+" "
                                                     +QString::fromStdString(this->currentAccount.getAccountCurrencySymbol())+"  am  "
                                                     +QString::fromStdString(getDateInLanguageFormat(highestExpenseElement.Day, highestExpenseElement.Month, highestExpenseElementYear, GERMAN)) );
                }
            }
            statsNames.push_back("Höchstes Einkommen (eine Transaktion):");
            statsNames.push_back("Höchste Ausgabe (eine Transaktion):");
            statsValues.push_back(textHighestOverallIncome);
            statsValues.push_back(textHighestOverallExpense);

            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            if (highestYearlyIncome_Year <= 0){
                textHighestYearlyIncome = "Nicht verfügbar.";
            } else {
                if (this->currentAccount.getAccountCurrencySymbol() == "$")
                {
                    textHighestYearlyIncome = QString::fromStdString(this->currentAccount.getAccountCurrencySymbol())
                                             +QString(QString::fromStdString(getAmountAsStringInGermanFormat(highestYearlyIncome))
                                             +"  in  "
                                             +QString::number(highestYearlyIncome_Year));
                } else {
                    textHighestYearlyIncome = QString(QString::fromStdString(getAmountAsStringInGermanFormat(highestYearlyIncome))+" "
                                             +QString::fromStdString(this->currentAccount.getAccountCurrencySymbol())+"  in  "
                                             +QString::number(highestYearlyIncome_Year));
                }
            }

            if (highestYearlyExpenses_Year <= 0){
                textHighestYearlyExpenses = "Nicht verfügbar.";
            } else {
                if (this->currentAccount.getAccountCurrencySymbol() == "$")
                {
                    textHighestYearlyExpenses = QString::fromStdString(this->currentAccount.getAccountCurrencySymbol())
                                               +QString(QString::fromStdString(getAmountAsStringInGermanFormat(highestYearlyExpenses))
                                               +"  in  "
                                               +QString::number(highestYearlyExpenses_Year));
                } else {
                    textHighestYearlyExpenses = QString(QString::fromStdString(getAmountAsStringInGermanFormat(highestYearlyExpenses))+" "
                                               +QString::fromStdString(this->currentAccount.getAccountCurrencySymbol())+"  in  "
                                               +QString::number(highestYearlyExpenses_Year));
                }
            }

            if (lowestYearlyIncome_Year <= 0){
                textLowestYearlyIncome = "Nicht verfügbar.";
            } else {
                if (this->currentAccount.getAccountCurrencySymbol() == "$")
                {
                    textLowestYearlyIncome = QString::fromStdString(this->currentAccount.getAccountCurrencySymbol())
                                            +QString(QString::fromStdString(getAmountAsStringInGermanFormat(lowestYearlyIncome))
                                            +"  in  "
                                            +QString::number(lowestYearlyIncome_Year));
                } else {
                    textLowestYearlyIncome = QString(QString::fromStdString(getAmountAsStringInGermanFormat(lowestYearlyIncome))+" "
                                            +QString::fromStdString(this->currentAccount.getAccountCurrencySymbol())+"  in  "
                                            +QString::number(lowestYearlyIncome_Year));
                }
            }

            if (lowestYearlyExpenses_Year <= 0){
                textLowestYearlyExpenses = "Nicht verfügbar.";
            } else {
                if (this->currentAccount.getAccountCurrencySymbol() == "$")
                {
                    textLowestYearlyExpenses = QString::fromStdString(this->currentAccount.getAccountCurrencySymbol())
                                              +QString(QString::fromStdString(getAmountAsStringInGermanFormat(lowestYearlyExpenses))
                                              +"  in  "
                                              +QString::number(lowestYearlyExpenses_Year));
                } else {
                    textLowestYearlyExpenses = QString(QString::fromStdString(getAmountAsStringInGermanFormat(lowestYearlyExpenses))+" "
                                              +QString::fromStdString(this->currentAccount.getAccountCurrencySymbol())+"  in  "
                                              +QString::number(lowestYearlyExpenses_Year));
                }

            }
            statsNames.push_back("Höchstes Jahreseinkommen:");
            statsNames.push_back("Höchste Jahresausgabe:");
            statsValues.push_back(textHighestYearlyIncome);
            statsValues.push_back(textHighestYearlyExpenses);
            statsNames.push_back("Niedrigstes Jahreseinkommen:");
            statsNames.push_back("Niedrigste Jahresausgabe:");
            statsValues.push_back(textLowestYearlyIncome);
            statsValues.push_back(textLowestYearlyExpenses);

            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            if (highestMonthlyIncome_Year > 0){
                if (this->currentAccount.getAccountCurrencySymbol() == "$")
                {
                    textHighestMonthlyIncome = QString::fromStdString(this->currentAccount.getAccountCurrencySymbol())
                                              +QString(QString::fromStdString(getAmountAsStringInGermanFormat(highestMonthlyIncome))
                                              +"  in  "
                                              +QString::fromStdString(getMonthInLanguage(highestMonthlyIncome_Month, accountLanguage))+"  "
                                              +QString::number(highestMonthlyIncome_Year));
                } else {
                    textHighestMonthlyIncome = QString(QString::fromStdString(getAmountAsStringInGermanFormat(highestMonthlyIncome))+" "
                                              +QString::fromStdString(this->currentAccount.getAccountCurrencySymbol())+"  in  "
                                              +QString::fromStdString(getMonthInLanguage(highestMonthlyIncome_Month, accountLanguage))+"  "
                                              +QString::number(highestMonthlyIncome_Year));
                }

            } else {
                textHighestMonthlyIncome = "Nicht verfügbar.";
            }

            if (highestMonthlyExpenses_Year > 0){
                if (this->currentAccount.getAccountCurrencySymbol() == "$")
                {
                    textHighestMonthlyExpenses = QString::fromStdString(this->currentAccount.getAccountCurrencySymbol())
                                                +QString(QString::fromStdString(getAmountAsStringInGermanFormat(highestMonthlyExpenses))
                                                +"  in  "
                                                +QString::fromStdString(getMonthInLanguage(highestMonthlyExpenses_Month, accountLanguage))+"  "
                                                +QString::number(highestMonthlyExpenses_Year));
                } else {
                    textHighestMonthlyExpenses = QString(QString::fromStdString(getAmountAsStringInGermanFormat(highestMonthlyExpenses))+" "
                                                +QString::fromStdString(this->currentAccount.getAccountCurrencySymbol())+"  in  "
                                                +QString::fromStdString(getMonthInLanguage(highestMonthlyExpenses_Month, accountLanguage))+"  "
                                                +QString::number(highestMonthlyExpenses_Year));
                }

            } else {
                textHighestMonthlyExpenses = "Nicht verfügbar.";
            }
            statsNames.push_back("Höchstes monatliches Einkommen:");
            statsNames.push_back("Höchste monatliche Ausgabe:");
            statsValues.push_back(textHighestMonthlyIncome);
            statsValues.push_back(textHighestMonthlyExpenses);

            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            if (lowestMonthlyIncome_Year > 0){
                if (this->currentAccount.getAccountCurrencySymbol() == "$")
                {
                    textLowestMonthlyIncome = QString::fromStdString(this->currentAccount.getAccountCurrencySymbol())
                                              +QString(QString::fromStdString(getAmountAsStringInGermanFormat(lowestMonthlyIncome))
                                              +"  in  "
                                              +QString::fromStdString(getMonthInLanguage(lowestMonthlyIncome_Month, accountLanguage))+"  "
                                              +QString::number(lowestMonthlyIncome_Year));
                } else {
                    textLowestMonthlyIncome = QString(QString::fromStdString(getAmountAsStringInGermanFormat(lowestMonthlyIncome))+" "
                                              +QString::fromStdString(this->currentAccount.getAccountCurrencySymbol())+"  in  "
                                              +QString::fromStdString(getMonthInLanguage(lowestMonthlyIncome_Month, accountLanguage))+"  "
                                              +QString::number(lowestMonthlyIncome_Year));
                }

            } else {
                textLowestMonthlyIncome = "Nicht verfügbar.";
            }

            if (lowestMonthlyExpenses_Year > 0){
                if (this->currentAccount.getAccountCurrencySymbol() == "$")
                {
                    textLowestMonthlyExpenses = QString::fromStdString(this->currentAccount.getAccountCurrencySymbol())
                                                +QString(QString::fromStdString(getAmountAsStringInGermanFormat(lowestMonthlyExpenses))
                                                +"  in  "
                                                +QString::fromStdString(getMonthInLanguage(lowestMonthlyExpenses_Month, accountLanguage))+"  "
                                                +QString::number(lowestMonthlyExpenses_Year));
                } else {
                    textLowestMonthlyExpenses = QString(QString::fromStdString(getAmountAsStringInGermanFormat(lowestMonthlyExpenses))+" "
                                                +QString::fromStdString(this->currentAccount.getAccountCurrencySymbol())+"  in  "
                                                +QString::fromStdString(getMonthInLanguage(lowestMonthlyExpenses_Month, accountLanguage))+"  "
                                                +QString::number(lowestMonthlyExpenses_Year));
                }

            } else {
                textLowestMonthlyExpenses = "Nicht verfügbar.";
            }
            statsNames.push_back("Niedrigstes monatliches Einkommen:");
            statsNames.push_back("Niedrigste monatliche Ausgabe:");
            statsValues.push_back(textLowestMonthlyIncome);
            statsValues.push_back(textLowestMonthlyExpenses);

            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            if (!groupWithHighestYearlyIncome.empty()){
                if (this->currentAccount.getAccountCurrencySymbol() == "$")
                {
                    textGroupWithHighestYearlyIncome = QString(QString::fromStdString(groupWithHighestYearlyIncome)+"  "   //group name
                                                      +QString::fromStdString(this->currentAccount.getAccountCurrencySymbol())
                                                      +QString::fromStdString(getAmountAsStringInGermanFormat(groupWithHighestYearlyIncome_Amount))                //group amount
                                                      +"  in  "
                                                      +QString::number(groupWithHighestYearlyIncome_Year));
                } else {
                    textGroupWithHighestYearlyIncome = QString(QString::fromStdString(groupWithHighestYearlyIncome)+"  "   //group name
                                                      +QString::fromStdString(getAmountAsStringInGermanFormat(groupWithHighestYearlyIncome_Amount))+" "                //group amount
                                                      +QString::fromStdString(this->currentAccount.getAccountCurrencySymbol())+"  in  "
                                                      +QString::number(groupWithHighestYearlyIncome_Year));
                }

            } else {
               textGroupWithHighestYearlyIncome = "Nicht verfügbar.";
            }

            if (!groupWithHighestYearlyExpenses.empty()){
                if (this->currentAccount.getAccountCurrencySymbol() == "$")
                {
                    textGroupWithHighestYearlyExpenses = QString(QString::fromStdString(groupWithHighestYearlyExpenses)+"  "   //group name
                                                        +QString::fromStdString(this->currentAccount.getAccountCurrencySymbol())
                                                        +QString::fromStdString(getAmountAsStringInGermanFormat(groupWithHighestYearlyExpenses_Amount))                //group amount
                                                        +"  in  "
                                                        +QString::number(groupWithHighestYearlyExpenses_Year));
                } else {
                    textGroupWithHighestYearlyExpenses = QString(QString::fromStdString(groupWithHighestYearlyExpenses)+"  "   //group name
                                                        +QString::fromStdString(getAmountAsStringInGermanFormat(groupWithHighestYearlyExpenses_Amount))+" "                //group amount
                                                        +QString::fromStdString(this->currentAccount.getAccountCurrencySymbol())+"  in  "
                                                        +QString::number(groupWithHighestYearlyExpenses_Year));
                }

            } else {
               textGroupWithHighestYearlyExpenses = "Nicht verfügbar.";
            }

            if (!groupWithLowestYearlyIncome.empty()){
                if (this->currentAccount.getAccountCurrencySymbol() == "$")
                {
                    textGroupWithLowestYearlyIncome = QString(QString::fromStdString(groupWithLowestYearlyIncome)+"  "   //group name
                                                     +QString::fromStdString(this->currentAccount.getAccountCurrencySymbol())
                                                     +QString::fromStdString(getAmountAsStringInGermanFormat(groupWithLowestYearlyIncome_Amount))                //group amount
                                                     +"  in  "
                                                     +QString::number(groupWithLowestYearlyIncome_Year));
                } else {
                    textGroupWithLowestYearlyIncome = QString(QString::fromStdString(groupWithLowestYearlyIncome)+"  "   //group name
                                                     +QString::fromStdString(getAmountAsStringInGermanFormat(groupWithLowestYearlyIncome_Amount))+" "                //group amount
                                                     +QString::fromStdString(this->currentAccount.getAccountCurrencySymbol())+"  in  "
                                                     +QString::number(groupWithLowestYearlyIncome_Year));
                }

            } else {
               textGroupWithLowestYearlyIncome = "Nicht verfügbar.";
            }

            if (!groupWithLowestYearlyExpenses.empty()){
                if (this->currentAccount.getAccountCurrencySymbol() == "$")
                {
                    textGroupWithLowestYearlyExpenses = QString(QString::fromStdString(groupWithLowestYearlyExpenses)+"  "   //group name
                                                       +QString::fromStdString(this->currentAccount.getAccountCurrencySymbol())
                                                       +QString::fromStdString(getAmountAsStringInGermanFormat(groupWithLowestYearlyExpenses_Amount))                //group amount
                                                       +"  in  "
                                                       +QString::number(groupWithLowestYearlyExpenses_Year));
                } else {
                    textGroupWithLowestYearlyExpenses = QString(QString::fromStdString(groupWithLowestYearlyExpenses)+"  "   //group name
                                                       +QString::fromStdString(getAmountAsStringInGermanFormat(groupWithLowestYearlyExpenses_Amount))+" "                //group amount
                                                       +QString::fromStdString(this->currentAccount.getAccountCurrencySymbol())+"  in  "
                                                       +QString::number(groupWithLowestYearlyExpenses_Year));
                }

            } else {
               textGroupWithLowestYearlyExpenses = "Nicht verfügbar.";
            }
            statsNames.push_back("Gruppe mit höchstem Jahreseinkommen*:");
            statsNames.push_back("Gruppe mit höchster Jahresausgabe*:");
            statsValues.push_back(textGroupWithHighestYearlyIncome);
            statsValues.push_back(textGroupWithHighestYearlyExpenses);
            statsNames.push_back("Gruppe mit niedrigstem Jahreseinkommen*:");
            statsNames.push_back("Gruppe mit niedrigster Jahresausgabe*:");
            statsValues.push_back(textGroupWithLowestYearlyIncome);
            statsValues.push_back(textGroupWithLowestYearlyExpenses);

            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            textYearWithHighestNumberOfTransactions = QString(QString::number(yearWithHighestNumberOfTransactions_NumberOfTransactions)+"  in  "
                                      +QString::number(yearWithHighestNumberOfTransactions));
            statsNames.push_back("Jahr mit höchster Transaktionenanzahl:");
            statsValues.push_back(textYearWithHighestNumberOfTransactions);

            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            textYearWithLowestNumberOfTransactions = QString(QString::number(yearWithLowestNumberOfTransactions_NumberOfTransactions)+"  in  "
                                      +QString::number(yearWithLowestNumberOfTransactions));
            statsNames.push_back("Jahr mit niedrigster Transaktionenanzahl:");
            statsValues.push_back(textYearWithLowestNumberOfTransactions);

            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            statsNames.push_back("* Zusätzliche Information.");
            statsValues.push_back("*Es werden nur klassifizierte Transaktionen mit Beträgen größer als Null betrachtet.");
            iAccountStatsDialog.getAccountStats(statsNames, statsValues);
            iAccountStatsDialog.setWindowTitle(" Konto");
        }


        //////////////////////////////////////////////////////////////// SPANISH ////////////////////////////////////////////////////////////////////////////////
        else if (accountLanguage == SPANISH){
            statsNames.push_back("Nombre:");
            statsNames.push_back("Moneda:");
            statsNames.push_back("Idioma:");
            statsNames.push_back("Ruta de imágen");
            statsValues.push_back(QString::fromStdString(currentAccount.getAccountName()));
            statsValues.push_back(QString::fromStdString(currentAccount.getAccountCurrencyString()));
            statsValues.push_back(QString::fromStdString(currentAccount.getAccountLanguageString()));
            statsValues.push_back(QString::fromStdString(currentAccount.getAccountIconPath()));

            textTimeInterval = QString("Desde   "
                              +QString::fromStdString(getDateInLanguageFormat(firstElement.Day, firstElement.Month, firstElementYear, SPANISH))
                              +"   hasta   "
                              +QString::fromStdString(getDateInLanguageFormat(lastElement.Day, lastElement.Month, lastElementYear, SPANISH)) );
            statsNames.push_back("Intervalo de tiempo:");
            statsValues.push_back(textTimeInterval);


            statsNames.push_back("Número total de transacciones:");
            statsNames.push_back("Número de ingresos:");
            statsNames.push_back("Número de egresos:");
            statsValues.push_back(textTotalNumberOfTransactions);
            statsValues.push_back(textTotalNumberOfIncomeElements);
            statsValues.push_back(textTotalNumberOfExpensesElements);

            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            if (this->currentAccount.getAccountCurrencySymbol() == "$")
            {
                textAverageMonthlyIncome    = QString::fromStdString(this->currentAccount.getAccountCurrencySymbol())+QString::fromStdString(getAmountAsStringFormatted(averageMonthlyIncomeAmount));
                textAverageMonthlyExpenses  = QString::fromStdString(this->currentAccount.getAccountCurrencySymbol())+QString::fromStdString(getAmountAsStringFormatted(averageMonthlyExpensesAmount));
            } else {
                textAverageMonthlyIncome    = QString::fromStdString(getAmountAsStringFormatted(averageMonthlyIncomeAmount))+" "+QString::fromStdString(this->currentAccount.getAccountCurrencySymbol());
                textAverageMonthlyExpenses  = QString::fromStdString(getAmountAsStringFormatted(averageMonthlyExpensesAmount))+" "+QString::fromStdString(this->currentAccount.getAccountCurrencySymbol());
            }
            statsNames.push_back("Promedio de ingresos mensuales:");
            statsNames.push_back("Promedio de egresos mensuales:");
            statsValues.push_back(textAverageMonthlyIncome);
            statsValues.push_back(textAverageMonthlyExpenses);

            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            if (highestIncomeElement.Name.empty()){
                textHighestOverallIncome = "No disponible.";
            } else {
                if (this->currentAccount.getAccountCurrencySymbol() == "$")
                {
                    textHighestOverallIncome  = QString( QString::fromStdString(highestIncomeElement.Name)+"  "
                                                    +QString::fromStdString(this->currentAccount.getAccountCurrencySymbol())
                                                    +QString::fromStdString(getAmountAsStringFormatted(highestIncomeElement.Amount))
                                                    +"  el  "
                                                    +QString::fromStdString(getDateInLanguageFormat(highestIncomeElement.Day, highestIncomeElement.Month, highestIncomeElementYear, SPANISH)) );
                } else {
                    textHighestOverallIncome  = QString( QString::fromStdString(highestIncomeElement.Name)+"  "
                                                    +QString::fromStdString(getAmountAsStringFormatted(highestIncomeElement.Amount))+" "
                                                    +QString::fromStdString(this->currentAccount.getAccountCurrencySymbol())+"  el  "
                                                    +QString::fromStdString(getDateInLanguageFormat(highestIncomeElement.Day, highestIncomeElement.Month, highestIncomeElementYear, SPANISH)) );
                }

            }

            if (highestExpenseElement.Name.empty()){
                textHighestOverallExpense = "No disponible.";
            } else {
                if (this->currentAccount.getAccountCurrencySymbol() == "$")
                {
                    textHighestOverallExpense = QString( QString::fromStdString(highestExpenseElement.Name)+"  "
                                                     +QString::fromStdString(this->currentAccount.getAccountCurrencySymbol())
                                                     +QString::fromStdString(getAmountAsStringFormatted(highestExpenseElement.Amount))
                                                     +"  el  "
                                                     +QString::fromStdString(getDateInLanguageFormat(highestExpenseElement.Day, highestExpenseElement.Month, highestExpenseElementYear, SPANISH)) );
                } else {
                    textHighestOverallExpense = QString( QString::fromStdString(highestExpenseElement.Name)+"  "
                                                     +QString::fromStdString(getAmountAsStringFormatted(highestExpenseElement.Amount))+" "
                                                     +QString::fromStdString(this->currentAccount.getAccountCurrencySymbol())+"  el  "
                                                     +QString::fromStdString(getDateInLanguageFormat(highestExpenseElement.Day, highestExpenseElement.Month, highestExpenseElementYear, SPANISH)) );
                }
            }
            statsNames.push_back("Mayor ingreso (una transacción):");
            statsNames.push_back("Mayor egreso (una transacción):");
            statsValues.push_back(textHighestOverallIncome);
            statsValues.push_back(textHighestOverallExpense);

            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            if (highestYearlyIncome_Year <= 0){
                textHighestYearlyIncome = "No disponible.";
            } else {
                if (this->currentAccount.getAccountCurrencySymbol() == "$")
                {
                    textHighestYearlyIncome = QString::fromStdString(this->currentAccount.getAccountCurrencySymbol())
                                             +QString( QString::fromStdString(getAmountAsStringFormatted(highestYearlyIncome))
                                             +"  en  "
                                             +QString::number(highestYearlyIncome_Year) );
                } else {
                    textHighestYearlyIncome = QString( QString::fromStdString(getAmountAsStringFormatted(highestYearlyIncome))+" "
                                             +QString::fromStdString(this->currentAccount.getAccountCurrencySymbol())+"  en  "
                                             +QString::number(highestYearlyIncome_Year) );
                }
            }

            if (highestYearlyExpenses_Year <= 0){
                textHighestYearlyExpenses = "No disponible.";
            } else {
                if (this->currentAccount.getAccountCurrencySymbol() == "$")
                {
                    textHighestYearlyExpenses = QString::fromStdString(this->currentAccount.getAccountCurrencySymbol())
                                               +QString( QString::fromStdString(getAmountAsStringFormatted(highestYearlyExpenses))
                                               +"  en  "
                                               +QString::number(highestYearlyExpenses_Year) );
                } else {
                    textHighestYearlyExpenses = QString( QString::fromStdString(getAmountAsStringFormatted(highestYearlyExpenses))+" "
                                               +QString::fromStdString(this->currentAccount.getAccountCurrencySymbol())+"  en  "
                                               +QString::number(highestYearlyExpenses_Year) );
                }
            }

            if (lowestYearlyIncome_Year <= 0){
                textLowestYearlyIncome = "No disponible.";
            } else {
                if (this->currentAccount.getAccountCurrencySymbol() == "$")
                {
                    textLowestYearlyIncome = QString::fromStdString(this->currentAccount.getAccountCurrencySymbol())
                                            +QString( QString::fromStdString(getAmountAsStringFormatted(lowestYearlyIncome))
                                            +"  en  "
                                            +QString::number(lowestYearlyIncome_Year) );
                } else {
                    textLowestYearlyIncome = QString( QString::fromStdString(getAmountAsStringFormatted(lowestYearlyIncome))+" "
                                            +QString::fromStdString(this->currentAccount.getAccountCurrencySymbol())+"  en  "
                                            +QString::number(lowestYearlyIncome_Year) );
                }
            }

            if (lowestYearlyExpenses_Year <= 0){
                textLowestYearlyExpenses = "No disponible.";
            } else {
                if (this->currentAccount.getAccountCurrencySymbol() == "$")
                {
                    textLowestYearlyExpenses = QString::fromStdString(this->currentAccount.getAccountCurrencySymbol())
                                              +QString( QString::fromStdString(getAmountAsStringFormatted(lowestYearlyExpenses))
                                              +"  en  "
                                              +QString::number(lowestYearlyExpenses_Year) );
                } else {
                    textLowestYearlyExpenses = QString( QString::fromStdString(getAmountAsStringFormatted(lowestYearlyExpenses))+" "
                                              +QString::fromStdString(this->currentAccount.getAccountCurrencySymbol())+"  en  "
                                              +QString::number(lowestYearlyExpenses_Year) );
                }
            }
            statsNames.push_back("Mayor ingreso anual:");
            statsNames.push_back("Mayor egreso anual:");
            statsValues.push_back(textHighestYearlyIncome);
            statsValues.push_back(textHighestYearlyExpenses);
            statsNames.push_back("Menor ingreso anual:");
            statsNames.push_back("Menor egreso anual:");
            statsValues.push_back(textLowestYearlyIncome);
            statsValues.push_back(textLowestYearlyExpenses);

            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            if (highestMonthlyIncome_Year > 0){
                if (this->currentAccount.getAccountCurrencySymbol() == "$")
                {
                    textHighestMonthlyIncome = QString::fromStdString(this->currentAccount.getAccountCurrencySymbol())
                                              +QString( QString::fromStdString(getAmountAsStringFormatted(highestMonthlyIncome))
                                              +"  en  "
                                              +QString::fromStdString(getMonthInLanguage(highestMonthlyIncome_Month, accountLanguage))+"  "
                                              +QString::number(highestMonthlyIncome_Year) );
                } else {
                    textHighestMonthlyIncome = QString( QString::fromStdString(getAmountAsStringFormatted(highestMonthlyIncome))+" "
                                              +QString::fromStdString(this->currentAccount.getAccountCurrencySymbol())+"  en  "
                                              +QString::fromStdString(getMonthInLanguage(highestMonthlyIncome_Month, accountLanguage))+"  "
                                              +QString::number(highestMonthlyIncome_Year) );
                }

            } else {
                textHighestMonthlyIncome = "No disponible.";
            }

            if (highestMonthlyExpenses_Year > 0){
                if (this->currentAccount.getAccountCurrencySymbol() == "$")
                {
                    textHighestMonthlyExpenses = QString::fromStdString(this->currentAccount.getAccountCurrencySymbol())
                                                +QString( QString::fromStdString(getAmountAsStringFormatted(highestMonthlyExpenses))
                                                +"  en  "
                                                +QString::fromStdString(getMonthInLanguage(highestMonthlyExpenses_Month, accountLanguage))+"  "
                                                +QString::number(highestMonthlyExpenses_Year) );
                } else {
                    textHighestMonthlyExpenses = QString( QString::fromStdString(getAmountAsStringFormatted(highestMonthlyExpenses))+" "
                                                +QString::fromStdString(this->currentAccount.getAccountCurrencySymbol())+"  en  "
                                                +QString::fromStdString(getMonthInLanguage(highestMonthlyExpenses_Month, accountLanguage))+"  "
                                                +QString::number(highestMonthlyExpenses_Year) );
                }

            } else {
                textHighestMonthlyExpenses = "No disponible.";
            }
            statsNames.push_back("Mayor ingreso mensual:");
            statsNames.push_back("Mayor egreso mensual:");
            statsValues.push_back(textHighestMonthlyIncome);
            statsValues.push_back(textHighestMonthlyExpenses);

            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            if (lowestMonthlyIncome_Year > 0){
                if (this->currentAccount.getAccountCurrencySymbol() == "$")
                {
                    textLowestMonthlyIncome = QString::fromStdString(this->currentAccount.getAccountCurrencySymbol())
                                              +QString( QString::fromStdString(getAmountAsStringFormatted(lowestMonthlyIncome))
                                              +"  en  "
                                              +QString::fromStdString(getMonthInLanguage(lowestMonthlyIncome_Month, accountLanguage))+"  "
                                              +QString::number(lowestMonthlyIncome_Year) );
                } else {
                    textLowestMonthlyIncome = QString( QString::fromStdString(getAmountAsStringFormatted(lowestMonthlyIncome))+" "
                                              +QString::fromStdString(this->currentAccount.getAccountCurrencySymbol())+"  en  "
                                              +QString::fromStdString(getMonthInLanguage(lowestMonthlyIncome_Month, accountLanguage))+"  "
                                              +QString::number(lowestMonthlyIncome_Year) );
                }

            } else {
                textLowestMonthlyIncome = "No disponible.";
            }

            if (lowestMonthlyExpenses_Year > 0){
                if (this->currentAccount.getAccountCurrencySymbol() == "$")
                {
                    textLowestMonthlyExpenses = QString::fromStdString(this->currentAccount.getAccountCurrencySymbol())
                                                +QString( QString::fromStdString(getAmountAsStringFormatted(lowestMonthlyExpenses))
                                                +"  en  "
                                                +QString::fromStdString(getMonthInLanguage(lowestMonthlyExpenses_Month, accountLanguage))+"  "
                                                +QString::number(lowestMonthlyExpenses_Year) );
                } else {
                    textLowestMonthlyExpenses = QString( QString::fromStdString(getAmountAsStringFormatted(lowestMonthlyExpenses))+" "
                                                +QString::fromStdString(this->currentAccount.getAccountCurrencySymbol())+"  en  "
                                                +QString::fromStdString(getMonthInLanguage(lowestMonthlyExpenses_Month, accountLanguage))+"  "
                                                +QString::number(lowestMonthlyExpenses_Year) );
                }

            } else {
                textLowestMonthlyExpenses = "No disponible.";
            }
            statsNames.push_back("Menor ingreso mensual:");
            statsNames.push_back("Menor egreso mensual:");
            statsValues.push_back(textLowestMonthlyIncome);
            statsValues.push_back(textLowestMonthlyExpenses);

            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            if (!groupWithHighestYearlyIncome.empty()){
                if (this->currentAccount.getAccountCurrencySymbol() == "$")
                {
                    textGroupWithHighestYearlyIncome = QString(QString::fromStdString(groupWithHighestYearlyIncome)+"  "   //group name
                                                      +QString::fromStdString(this->currentAccount.getAccountCurrencySymbol())
                                                      +QString::fromStdString(getAmountAsStringFormatted(groupWithHighestYearlyIncome_Amount))                //group amount
                                                      +"  en  "
                                                      +QString::number(groupWithHighestYearlyIncome_Year));
                } else {
                    textGroupWithHighestYearlyIncome = QString(QString::fromStdString(groupWithHighestYearlyIncome)+"  "   //group name
                                                      +QString::fromStdString(getAmountAsStringFormatted(groupWithHighestYearlyIncome_Amount))+" "                //group amount
                                                      +QString::fromStdString(this->currentAccount.getAccountCurrencySymbol())+"  en  "
                                                      +QString::number(groupWithHighestYearlyIncome_Year));
                }

            } else {
               textGroupWithHighestYearlyIncome = "No disponible.";
            }

            if (!groupWithHighestYearlyExpenses.empty()){
                if (this->currentAccount.getAccountCurrencySymbol() == "$")
                {
                    textGroupWithHighestYearlyExpenses = QString(QString::fromStdString(groupWithHighestYearlyExpenses)+"  "   //group name
                                                        +QString::fromStdString(this->currentAccount.getAccountCurrencySymbol())
                                                        +QString::fromStdString(getAmountAsStringFormatted(groupWithHighestYearlyExpenses_Amount))                //group amount
                                                        +"  en  "
                                                        +QString::number(groupWithHighestYearlyExpenses_Year));
                } else {
                    textGroupWithHighestYearlyExpenses = QString(QString::fromStdString(groupWithHighestYearlyExpenses)+"  "   //group name
                                                        +QString::fromStdString(getAmountAsStringFormatted(groupWithHighestYearlyExpenses_Amount))+" "                //group amount
                                                        +QString::fromStdString(this->currentAccount.getAccountCurrencySymbol())+"  en  "
                                                        +QString::number(groupWithHighestYearlyExpenses_Year));
                }

            } else {
               textGroupWithHighestYearlyExpenses = "No disponible.";
            }

            if (!groupWithLowestYearlyIncome.empty()){
                if (this->currentAccount.getAccountCurrencySymbol() == "$")
                {
                    textGroupWithLowestYearlyIncome = QString(QString::fromStdString(groupWithLowestYearlyIncome)+"  "   //group name
                                                     +QString::fromStdString(this->currentAccount.getAccountCurrencySymbol())
                                                     +QString::fromStdString(getAmountAsStringFormatted(groupWithLowestYearlyIncome_Amount))                //group amount
                                                     +"  en  "
                                                     +QString::number(groupWithLowestYearlyIncome_Year));
                } else {
                    textGroupWithLowestYearlyIncome = QString(QString::fromStdString(groupWithLowestYearlyIncome)+"  "   //group name
                                                     +QString::fromStdString(getAmountAsStringFormatted(groupWithLowestYearlyIncome_Amount))+" "                //group amount
                                                     +QString::fromStdString(this->currentAccount.getAccountCurrencySymbol())+"  en  "
                                                     +QString::number(groupWithLowestYearlyIncome_Year));
                }

            } else {
               textGroupWithLowestYearlyIncome = "No disponible.";
            }

            if (!groupWithLowestYearlyExpenses.empty()){
                if (this->currentAccount.getAccountCurrencySymbol() == "$")
                {
                    textGroupWithLowestYearlyExpenses = QString(QString::fromStdString(groupWithLowestYearlyExpenses)+"  "   //group name
                                                       +QString::fromStdString(this->currentAccount.getAccountCurrencySymbol())
                                                       +QString::fromStdString(getAmountAsStringFormatted(groupWithLowestYearlyExpenses_Amount))                //group amount
                                                       +"  en  "
                                                       +QString::number(groupWithLowestYearlyExpenses_Year));
                } else {
                    textGroupWithLowestYearlyExpenses = QString(QString::fromStdString(groupWithLowestYearlyExpenses)+"  "   //group name
                                                       +QString::fromStdString(getAmountAsStringFormatted(groupWithLowestYearlyExpenses_Amount))+" "                //group amount
                                                       +QString::fromStdString(this->currentAccount.getAccountCurrencySymbol())+"  en  "
                                                       +QString::number(groupWithLowestYearlyExpenses_Year));
                }

            } else {
               textGroupWithLowestYearlyExpenses = "No disponible.";
            }
            statsNames.push_back("Grupo con mayor ingreso anual*:");
            statsNames.push_back("Grupo con mayor egreso anual*:");
            statsValues.push_back(textGroupWithHighestYearlyIncome);
            statsValues.push_back(textGroupWithHighestYearlyExpenses);
            statsNames.push_back("Grupo con menor ingreso anual*:");
            statsNames.push_back("Grupo con menor egreso anual*:");
            statsValues.push_back(textGroupWithLowestYearlyIncome);
            statsValues.push_back(textGroupWithLowestYearlyExpenses);

            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            textYearWithHighestNumberOfTransactions = QString(QString::number(yearWithHighestNumberOfTransactions_NumberOfTransactions)+"  en  "
                                      +QString::number(yearWithHighestNumberOfTransactions));
            statsNames.push_back("Año con mayor número de transacciones:");
            statsValues.push_back(textYearWithHighestNumberOfTransactions);

            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            textYearWithLowestNumberOfTransactions = QString(QString::number(yearWithLowestNumberOfTransactions_NumberOfTransactions)+"  en  "
                                      +QString::number(yearWithLowestNumberOfTransactions));
            statsNames.push_back("Año con menor número de transacciones:");
            statsValues.push_back(textYearWithLowestNumberOfTransactions);

            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            statsNames.push_back("* Información adicional.");
            statsValues.push_back("*Solo transacciones clasificadas con montos mayores a cero son consideradas.");
            iAccountStatsDialog.getAccountStats(statsNames, statsValues);
            iAccountStatsDialog.setWindowTitle(" Cuenta");
        }

        iAccountStatsDialog.exec();
    }
}

void Gui_KeiboMoneyTracker::on_actionDonate_triggered()
{
    if (ACCOUNT_SET)
    {
        DonateDialog iDonateDialog;
        iDonateDialog.setLanguageAndStyleSheet(currentAccount.getAccountLanguage(), currentOverallThemeStyleSheet, usingDarkTheme);
        iDonateDialog.exec();
    }
}
