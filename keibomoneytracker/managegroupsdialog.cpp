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

#include "managegroupsdialog.h"
#include "ui_managegroupsdialog.h"
#include "addgroupdialog.h"
#include "eraseconfirmation_dialog.h"
#include <QKeyEvent>
#include <QScrollBar>

ManageGroupsDialog::ManageGroupsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ManageGroupsDialog)
{
    ui->setupUi(this);
    this->ui->tableWidgetGroups->installEventFilter(this);
    this->ui->addGroupButton->installEventFilter(this);
    this->ui->editGroupButton->installEventFilter(this);
    this->ui->deleteGroupButton->installEventFilter(this);
    this->ui->acceptButton->installEventFilter(this);

    this->ui->tableWidgetGroups->setTabKeyNavigation(false);
    this->ui->tableWidgetGroups->setEditTriggers(QAbstractItemView::NoEditTriggers);

    this->ui->acceptButton->setAutoDefault(false);
    this->ui->addGroupButton->setAutoDefault(false);
    this->ui->editGroupButton->setAutoDefault(false);
    this->ui->deleteGroupButton->setAutoDefault(false);

    this->setTabOrder(ui->tableWidgetGroups, ui->addGroupButton);
    this->setTabOrder(ui->addGroupButton, ui->editGroupButton);
    this->setTabOrder(ui->editGroupButton, ui->deleteGroupButton);
    this->setTabOrder(ui->deleteGroupButton, ui->acceptButton);
    this->focusPreviousChild();

    this->ui->tableWidgetGroups->setSelectionBehavior( QAbstractItemView::SelectItems );
    this->ui->tableWidgetGroups->setSelectionMode( QAbstractItemView::SingleSelection );
}

ManageGroupsDialog::~ManageGroupsDialog()
{
    delete ui;
}

void ManageGroupsDialog::setLanguage(const Language &accountLanguage)
{
    iLanguage = accountLanguage;
    if (iLanguage == ENGLISH)
    {
        this->ui->addGroupButton->setText("Add group");
        this->ui->editGroupButton->setText("Edit group");
        this->ui->deleteGroupButton->setText("Delete group");
        this->ui->acceptButton->setText("Close");
    }
    else if (iLanguage == GERMAN)
    {
        this->ui->addGroupButton->setText("Gruppe hinzufügen");
        this->ui->editGroupButton->setText("Gruppe ändern");
        this->ui->deleteGroupButton->setText("Gruppe löschen");
        this->ui->acceptButton->setText("Schließen");
    }
    else if (iLanguage == SPANISH)
    {
        this->ui->addGroupButton->setText("Añadir grupo");
        this->ui->editGroupButton->setText("Editar grupo");
        this->ui->deleteGroupButton->setText("Borrar grupo");
        this->ui->acceptButton->setText("Cerrar");
    }
}

void ManageGroupsDialog::setOverallThemeStyleSheet(QString styleSheetString, QString tTableHeaderStyleSheet, bool tUsingDarkTheme)
{
    tableHeaderStyleSheet = tTableHeaderStyleSheet;
    this->ui->tableWidgetGroups->setStyleSheet(tTableHeaderStyleSheet);  //First set the color of the table header!!
    this->ui->tableWidgetGroups->verticalHeader()->setStyleSheet("background-color: rgba(0, 0, 0, 0); border-bottom-style: rgba(255, 255, 255, 0);");
    this->setStyleSheet(styleSheetString);

    this->ui->tableWidgetGroups->verticalScrollBar()->setStyleSheet(
                "QScrollBar:vertical { width: 15px; margin: 0px 0px 0px 0px;}"
                "QScrollBar::add-line:vertical { border: none; background: none;}"
                "QScrollBar::sub-line:vertical { border: none; background: none;}"
                "QScrollBar::handle:vertical {background: rgb(32, 47, 130), min-height: 0px;}");
    overallThemeStyleSheetString = styleSheetString;



    this->ui->acceptButton->updateColorTheme(tUsingDarkTheme);
    this->ui->addGroupButton->updateColorTheme(tUsingDarkTheme);
    this->ui->editGroupButton->updateColorTheme(tUsingDarkTheme);
    this->ui->deleteGroupButton->updateColorTheme(tUsingDarkTheme);
    usingDarkTheme = tUsingDarkTheme;
}

void ManageGroupsDialog::setYearData(Account tempYearData, bool showIncomeGroups)
{
    editingIncomeGroups = showIncomeGroups;
    yearData = tempYearData;
    ui->tableWidgetGroups->setColumnCount(1);
    
    if (editingIncomeGroups == false)
    {
        ui->tableWidgetGroups->setRowCount(yearData.ExpensesGroupsNames.size()-1);
        ui->tableWidgetGroups->horizontalHeader()->setStretchLastSection(true);
        QStringList tableHeader;
        if (iLanguage == ENGLISH)
        {
            tableHeader<<"Expenses groups";
        }
        else if (iLanguage == GERMAN)
        {
            tableHeader<<"Gruppen Ausgaben";
        }
        else if (iLanguage == SPANISH)
        {
            tableHeader<<"Grupos de egresos";
        }
        ui->tableWidgetGroups->setHorizontalHeaderLabels(tableHeader);
    
        short itemId = 0;
        for (std::vector<std::string>::iterator it= yearData.ExpensesGroupsNames.begin()+1; it != yearData.ExpensesGroupsNames.end(); ++it)
          {
              ui->tableWidgetGroups->setItem(itemId, 0, new QTableWidgetItem (QString::fromStdString(*it)));
              ui->tableWidgetGroups->setRowHeight(itemId, 22);
              ++itemId;
          }
    }

    else if (editingIncomeGroups == true)
    {
        ui->tableWidgetGroups->setRowCount(yearData.IncomeGroupsNames.size()-1);
        ui->tableWidgetGroups->horizontalHeader()->setStretchLastSection(true);
        QStringList tableHeader;
        if (iLanguage == ENGLISH)
        {
            tableHeader<<"Income groups";
        }
        else if (iLanguage == GERMAN)
        {
            tableHeader<<"Gruppen Einkommen";
        }
        else if (iLanguage == SPANISH)
        {
            tableHeader<<"Grupos de ingresos";
        }
        ui->tableWidgetGroups->setHorizontalHeaderLabels(tableHeader);

        short itemId = 0;
        for (std::vector<std::string>::iterator it= yearData.IncomeGroupsNames.begin()+1; it != yearData.IncomeGroupsNames.end(); ++it)
          {
              ui->tableWidgetGroups->setItem(itemId, 0, new QTableWidgetItem (QString::fromStdString(*it)));
              ui->tableWidgetGroups->setRowHeight(itemId, 22);
              ++itemId;
          }
    }

    if (editingIncomeGroups)
    {
        if (iLanguage == ENGLISH)
        {
            this->setWindowTitle(" Manage income groups");
        }
        else if (iLanguage == GERMAN)
        {
            this->setWindowTitle(" Einkommen Gruppen bearbeiten");
        }
        else if (iLanguage == SPANISH)
        {
            this->setWindowTitle(" Administrar grupos de ingresos");
        }
    }
    else if (!editingIncomeGroups)
    {
        if (iLanguage == ENGLISH)
        {
            this->setWindowTitle(" Manage expenses groups");
        }
        else if (iLanguage == GERMAN)
        {
            this->setWindowTitle(" Ausgaben Gruppen bearbeiten");
        }
        else if (iLanguage == SPANISH)
        {
            this->setWindowTitle(" Administrar grupos de egresos");
        }
    }
}

bool ManageGroupsDialog::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::KeyPress)
    {
        if (qobject_cast<QTableWidget*>(obj) == ui->tableWidgetGroups)
        {
            QKeyEvent* key = static_cast<QKeyEvent*>(event);
            if (key->key() == Qt::Key_Enter || (key->key()==Qt::Key_Return))
            {
                this->editSelectedGroup();
                return true;
            }
            else if (key->key() == Qt::Key_Tab)
            {
                this->focusNextChild();
                return true;
            }
            else if (key->key() == Qt::Key_Up)
            {
                int newSelectedRow = ui->tableWidgetGroups->currentRow()-1;
                if (newSelectedRow > 0){
                    TopOfTableReached = false;
                    this->ui->tableWidgetGroups->selectRow(newSelectedRow);
                } else if ( (newSelectedRow == 0) && (TopOfTableReached == false) ) {
                    std::cout<<"Row on the bottom REACHED"<<'\n';
                    this->ui->tableWidgetGroups->selectRow(newSelectedRow);
                    TopOfTableReached = true;
                }
                return true;
            }
            else if (key->key() == Qt::Key_Down)
            {
                int newSelectedRow = ui->tableWidgetGroups->currentRow()+1;
                if (newSelectedRow < (ui->tableWidgetGroups->rowCount()-1)){
                    BottomOfTableReached = false;
                    this->ui->tableWidgetGroups->selectRow(newSelectedRow);
                } else if ((newSelectedRow >= (ui->tableWidgetGroups->rowCount()-1)) && (BottomOfTableReached == false)) {
                    std::cout<<"Row on the top REACHED"<<'\n';
                    this->ui->tableWidgetGroups->selectRow(newSelectedRow);
                    BottomOfTableReached = true;
                }
                return true;
            }
            else if (key->key() == Qt::Key_Delete)
            {
                this->deleteSelectedGroup();
                return true;
            }
        }
        else if (qobject_cast<QPushButton*>(obj) == ui->addGroupButton)
        {
            QKeyEvent* key = static_cast<QKeyEvent*>(event);
            if (key->key() == Qt::Key_Enter || (key->key()==Qt::Key_Return))
            {
                this->createNewGroup();
                return true;
            }
            else if (key->key() == Qt::Key_Tab)
            {
                this->focusNextChild();
                return true;
            }
        }
        else if (qobject_cast<QPushButton*>(obj) == ui->editGroupButton)
        {
            QKeyEvent* key = static_cast<QKeyEvent*>(event);
            if (key->key() == Qt::Key_Enter || (key->key()==Qt::Key_Return))
            {
                this->editSelectedGroup();
                return true;
            }
            else if (key->key() == Qt::Key_Tab)
            {
                this->focusNextChild();
                return true;
            }
        }
        else if (qobject_cast<QPushButton*>(obj) == ui->deleteGroupButton)
        {
            QKeyEvent* key = static_cast<QKeyEvent*>(event);
            if (key->key() == Qt::Key_Enter || (key->key()==Qt::Key_Return))
            {
                this->deleteSelectedGroup();
                return true;
            }
            else if (key->key() == Qt::Key_Tab)
            {
                this->focusNextChild();
                return true;
            }
        }
        else if (qobject_cast<QPushButton*>(obj) == ui->acceptButton)
        {
            QKeyEvent* key = static_cast<QKeyEvent*>(event);
            if (key->key() == Qt::Key_Enter || (key->key()==Qt::Key_Return))
            {
                this->close();
                return true;
            }
        }
    }
    else if (event->type() == QEvent::MouseButtonPress)
    {
        if (qobject_cast<QWidget*>(obj) == ui->acceptButton) {
            this->ui->acceptButton->setColorForMouseButtonPressEvent();
        } else if (qobject_cast<QWidget*>(obj) == ui->addGroupButton) {
            this->ui->addGroupButton->setColorForMouseButtonPressEvent();
        } else if (qobject_cast<QWidget*>(obj) == ui->editGroupButton) {
            this->ui->editGroupButton->setColorForMouseButtonPressEvent();
        } else if (qobject_cast<QWidget*>(obj) == ui->deleteGroupButton) {
            this->ui->deleteGroupButton->setColorForMouseButtonPressEvent();
        }
    }
    else if (event->type() == QEvent::MouseButtonRelease)
    {
        if (qobject_cast<QWidget*>(obj) == ui->acceptButton) {
            this->ui->acceptButton->setColorForEnterEvent();
        } else if (qobject_cast<QWidget*>(obj) == ui->addGroupButton) {
            this->ui->addGroupButton->setColorForEnterEvent();
        } else if (qobject_cast<QWidget*>(obj) == ui->editGroupButton) {
            this->ui->editGroupButton->setColorForEnterEvent();
        } else if (qobject_cast<QWidget*>(obj) == ui->deleteGroupButton) {
            this->ui->deleteGroupButton->setColorForEnterEvent();
        }
    }
    else if (event->type() == QEvent::Enter)
     {
         if (qobject_cast<QPushButton*>(obj) == ui->acceptButton)
         {
             this->ui->acceptButton->setColorForEnterEvent();
         } else if (qobject_cast<QWidget*>(obj) == ui->addGroupButton) {
             this->ui->addGroupButton->setColorForEnterEvent();
         } else if (qobject_cast<QWidget*>(obj) == ui->editGroupButton) {
             this->ui->editGroupButton->setColorForEnterEvent();
         } else if (qobject_cast<QWidget*>(obj) == ui->deleteGroupButton) {
             this->ui->deleteGroupButton->setColorForEnterEvent();
         }
    }
    else if (event->type() == QEvent::Leave)
     {
         if (qobject_cast<QPushButton*>(obj) == ui->acceptButton)
         {
             this->ui->acceptButton->setColorForLeaveEvent();
         } else if (qobject_cast<QWidget*>(obj) == ui->addGroupButton) {
             this->ui->addGroupButton->setColorForLeaveEvent();
         } else if (qobject_cast<QWidget*>(obj) == ui->editGroupButton) {
             this->ui->editGroupButton->setColorForLeaveEvent();
         } else if (qobject_cast<QWidget*>(obj) == ui->deleteGroupButton) {
             this->ui->deleteGroupButton->setColorForLeaveEvent();
         }
    }
    else if (event->type() == QEvent::FocusIn)
     {
        if (qobject_cast<QPushButton*>(obj) == ui->acceptButton)
        {
            this->ui->acceptButton->setColorForEnterEvent();
        } else if (qobject_cast<QWidget*>(obj) == ui->addGroupButton) {
            this->ui->addGroupButton->setColorForEnterEvent();
        } else if (qobject_cast<QWidget*>(obj) == ui->editGroupButton) {
            this->ui->editGroupButton->setColorForEnterEvent();
        } else if (qobject_cast<QWidget*>(obj) == ui->deleteGroupButton) {
            this->ui->deleteGroupButton->setColorForEnterEvent();
        }
     }
    else if (event->type() == QEvent::FocusIn)
     {
        if (qobject_cast<QPushButton*>(obj) == ui->acceptButton)
        {
            this->ui->acceptButton->setColorForLeaveEvent();
        } else if (qobject_cast<QWidget*>(obj) == ui->addGroupButton) {
            this->ui->addGroupButton->setColorForLeaveEvent();
        } else if (qobject_cast<QWidget*>(obj) == ui->editGroupButton) {
            this->ui->editGroupButton->setColorForLeaveEvent();
        } else if (qobject_cast<QWidget*>(obj) == ui->deleteGroupButton) {
            this->ui->deleteGroupButton->setColorForLeaveEvent();
        }
     }
    return false;
}

void ManageGroupsDialog::createNewGroup()
{
    Addgroupdialog addGroupDialog;
    addGroupDialog.setModal(true);
    addGroupDialog.setLanguage(iLanguage);
    if (editingIncomeGroups == true){
        if (iLanguage == ENGLISH){
            addGroupDialog.setWindowTitle(" New Income Group");
        } else if (iLanguage == GERMAN) {
            addGroupDialog.setWindowTitle(" Neue Einkommen Gruppe");
        } else if (iLanguage == SPANISH){
            addGroupDialog.setWindowTitle(" Grupo nuevo de ingresos");
        }
    } else if (editingIncomeGroups == false) {
        if (iLanguage == ENGLISH){
            addGroupDialog.setWindowTitle(" New Expenses Group");
        } else if (iLanguage == GERMAN) {
            addGroupDialog.setWindowTitle(" Neue Ausgabe Gruppe");
        } else if (iLanguage == SPANISH){
            addGroupDialog.setWindowTitle(" Grupo nuevo de egresos");
        }
    }
    ui->labelInfo->setText("");
    addGroupDialog.setOverallThemeStyleSheet(overallThemeStyleSheetString, usingDarkTheme);
    addGroupDialog.exec();

    addGroupDialog.provideGroupName(newGroupName);

    if (!newGroupName.empty())
    {
        groupAdded = true;

        if (editingIncomeGroups == false)
        {
            yearData.addExpensesGroup(newGroupName);
            ui->tableWidgetGroups->setRowCount(yearData.ExpensesGroupsNames.size()-1);
            short itemId = 0;
            for (std::vector<std::string>::iterator it= yearData.ExpensesGroupsNames.begin()+1; it != yearData.ExpensesGroupsNames.end(); ++it)
            {
                ui->tableWidgetGroups->setItem(itemId, 0, new QTableWidgetItem (QString::fromStdString(*it)));
                ++itemId;
            }
            yearData.saveExpensesGroups();
        }
        else
        {
            yearData.addIncomeGroup(newGroupName);
            ui->tableWidgetGroups->setRowCount(yearData.IncomeGroupsNames.size()-1);
            short itemId = 0;
            for (std::vector<std::string>::iterator it= yearData.IncomeGroupsNames.begin()+1; it != yearData.IncomeGroupsNames.end(); ++it)
            {
                ui->tableWidgetGroups->setItem(itemId, 0, new QTableWidgetItem (QString::fromStdString(*it)));
                ++itemId;
            }
            yearData.saveIncomeGroups();
        }
    }
}

void ManageGroupsDialog::on_addGroupButton_clicked()
{
    this->createNewGroup();
}

void ManageGroupsDialog::editSelectedGroup()
{
    QItemSelectionModel *selection = ui->tableWidgetGroups->selectionModel();
    QModelIndexList highlightedRows = selection->selectedRows();
    if (highlightedRows.count()>0 && highlightedRows.count()<2)
    {
        ui->labelInfo->setText("");
        if (editingIncomeGroups == false)
        {
            QModelIndex index = highlightedRows.at(0);
            std::vector<std::string>::iterator it = yearData.ExpensesGroupsNames.begin()+1;  //Group "Not Classified" shall not be changed/deleted
            it+=index.row();                            ///Point to group selected

            Addgroupdialog editGroupDialog;
            editGroupDialog.setModal(true);
            editGroupDialog.setLanguage(iLanguage);
            if (iLanguage == ENGLISH){
                editGroupDialog.setWindowTitle(" Edit group name");
            } else if (iLanguage == GERMAN) {
                editGroupDialog.setWindowTitle(" Gruppe Name ändern");
            } else if (iLanguage == SPANISH){
                editGroupDialog.setWindowTitle(" Cambiar nombre de grupo");
            }
            editGroupDialog.setGroupName(*it);
            editGroupDialog.setOverallThemeStyleSheet(overallThemeStyleSheetString, usingDarkTheme);
            editGroupDialog.exec();

            editGroupDialog.provideGroupName(newGroupName);  ///Take new name from Dialog

            if ((*it != newGroupName) && (!newGroupName.empty()) ) ///If previous name is different to new one
            {                                                      ///And new name is not empty
                itemIdNumber = index.row()+1;
                groupEdited = true;                     ///Now "newGroupName" can be retrieved to gui_buydata
                *it = newGroupName;

                short itemId = 0;
                for (std::vector<std::string>::iterator it2= yearData.ExpensesGroupsNames.begin()+1; it2 != yearData.ExpensesGroupsNames.end(); ++it2)
                {
                    ui->tableWidgetGroups->setItem(itemId, 0, new QTableWidgetItem (QString::fromStdString(*it2)));
                    ++itemId;
                }

                yearData.saveExpensesGroups();
            }
        }
        else if (editingIncomeGroups == true)
        {
            QModelIndex index = highlightedRows.at(0);
            std::vector<std::string>::iterator it = yearData.IncomeGroupsNames.begin()+1;  //Because "Not Classified" shouldn't be touched
            it+=index.row();                            ///Point to group selected

            Addgroupdialog editGroupDialog;
            editGroupDialog.setModal(true);
            editGroupDialog.setLanguage(iLanguage);
            if (iLanguage == ENGLISH){
                editGroupDialog.setWindowTitle(" Edit group name");
            } else if (iLanguage == GERMAN) {
                editGroupDialog.setWindowTitle(" Gruppe Name ändern");
            } else if (iLanguage == SPANISH){
                editGroupDialog.setWindowTitle(" Cambiar nombre de grupo");
            }
            editGroupDialog.setGroupName(*it);
            editGroupDialog.setOverallThemeStyleSheet(overallThemeStyleSheetString, usingDarkTheme);
            editGroupDialog.exec();

            editGroupDialog.provideGroupName(newGroupName);  ///Take new name from Dialog

            if ((*it != newGroupName) && (!newGroupName.empty()) ) ///If previous name is different to new one
            {                                                      ///And new name is not empty
                itemIdNumber = index.row()+1;
                groupEdited = true;                     ///Now "newGroupName" can be retrieved to gui_buydata
                *it = newGroupName;

                short itemId = 0;
                for (std::vector<std::string>::iterator it2= yearData.IncomeGroupsNames.begin()+1; it2 != yearData.IncomeGroupsNames.end(); ++it2)
                {
                    ui->tableWidgetGroups->setItem(itemId, 0, new QTableWidgetItem (QString::fromStdString(*it2)));
                    ++itemId;
                }

                yearData.saveIncomeGroups();
            }
        }
    }
    else if (highlightedRows.count() == 0) {        
        if (iLanguage == ENGLISH)
        {
            ui->labelInfo->setText("Please select a group to edit first.");
        }
        else if (iLanguage == GERMAN)
        {
            ui->labelInfo->setText("Bitte wählen Sie zuerst eine Gruppe.");
        }
        else if (iLanguage == SPANISH)
        {
            ui->labelInfo->setText("Por favor, seleccione primero un grupo a editar.");
        }
    }
}

void ManageGroupsDialog::on_editGroupButton_clicked()
{
    this->editSelectedGroup();
}

void ManageGroupsDialog::deleteSelectedGroup() ///CHECK VALUES AFTER SECOND ITERATION!!!!
{
    QItemSelectionModel *selection = ui->tableWidgetGroups->selectionModel();
    QModelIndexList highlightedRows = selection->selectedRows();
    YearsIncludingTransactionOfGroupToDelete.clear();
    NumberOfTransactionPerYearOfGroupToDelete.clear();
    if (highlightedRows.count()>0 && highlightedRows.count()<2)
    {
        int currentYear = yearData.getYear();
        ui->labelInfo->setText("");
        QModelIndex index = highlightedRows.at(0);
        int totalTransactionsToChange = 0;

        ///SEARCH FOR CORRESPONDING DATA TO CHANGE
        for (int i= 0; i != 150; ++i){    ///Search in 150 years 1950-2100
            yearData.clear_Year();
            yearData.set_Year(1950+i);
            yearData.load_Data();
            std::vector<double>::iterator GroupTransactionsIterator;

                    if (editingIncomeGroups == false){
                        GroupTransactionsIterator = yearData.ExpensesGroupsAmounts.begin()+1; ///Don't count "Not Classified"
                        if (*(GroupTransactionsIterator+index.row()) > 0) ///If group in that year has expenses
                        {
                            YearsIncludingTransactionOfGroupToDelete.push_back(yearData.getYear());
                            NumberOfTransactionPerYearOfGroupToDelete.push_back(yearData.getTotalNumberOfExpensesTransactionsInGroup(index.row()+1));
                            totalTransactionsToChange += yearData.getTotalNumberOfExpensesTransactionsInGroup(index.row()+1);
                        }
                    }
                    else if (editingIncomeGroups == true){
                        GroupTransactionsIterator = yearData.IncomeGroupsAmounts.begin()+1;
                        if (*(GroupTransactionsIterator+index.row()) > 0) ///If group in that year has incomes
                        {
                            YearsIncludingTransactionOfGroupToDelete.push_back(yearData.getYear());
                            NumberOfTransactionPerYearOfGroupToDelete.push_back(yearData.getTotalNumberOfIncomeTransactionsInGroup(index.row()+1));
                            totalTransactionsToChange += yearData.getTotalNumberOfIncomeTransactionsInGroup(index.row()+1);
                        }
                    }
        }

        ///ASK FOR CONFIRMATION AND PROVIDE INFO TO CONFIRMATION DIALOG
        eraseConfirmation_dialog eraseConfirmation;
        eraseConfirmation.setModal(true);
        QString confirmationText;
        bool showTable = false;

        {
          if (totalTransactionsToChange > 0){
              showTable = true;
              if (iLanguage == ENGLISH)
              {
                  eraseConfirmation.setWindowTitle(" Confirmation");
                  confirmationText = "There is a total of "
                                         + QString::number(YearsIncludingTransactionOfGroupToDelete.size())
                                         +" year/s including transaction/s in this group. "
                                         + QString::number(totalTransactionsToChange)
                                         +" transaction/s will be set as not classified. Are you sure you want to proceed?";
              }
              else if (iLanguage == GERMAN)
              {
                  eraseConfirmation.setWindowTitle(" Bestätigung");
                  confirmationText = "Es gibt insgesamt "
                                         + QString::number(YearsIncludingTransactionOfGroupToDelete.size())
                                         +" Jahr/e mit Transaktion/en in dieser Gruppe. "
                                         + QString::number(totalTransactionsToChange)
                                         +" Transaktion/en werden geändert zu: Nicht klassifiziert. Möchten Sie fortfahren?";
              }
              else if (iLanguage == SPANISH)
              {
                  eraseConfirmation.setWindowTitle(" Confirmación");
                  confirmationText = "Hay un total de "
                                         + QString::number(YearsIncludingTransactionOfGroupToDelete.size())
                                         +" año/s que incluyen transaccion/es en este grupo. "
                                         + QString::number(totalTransactionsToChange)
                                         +" transaccion/es cambiaran a no clasificadas. ¿Desea proceder?";
              }
           }

          else {
              if (iLanguage == ENGLISH) {
                  eraseConfirmation.setWindowTitle(" Confirmation");
                  confirmationText = "Group will be deleted.";
              }  else if (iLanguage == GERMAN) {
                  eraseConfirmation.setWindowTitle(" Bestätigung");
                  confirmationText = "Gruppe wird gelöscht.";
              }  else if (iLanguage == SPANISH) {
                  eraseConfirmation.setWindowTitle(" Confirmación");
                  confirmationText = "El grupo será eliminado.";
              }
          }
        }

        /// PASS HERE THE VECTORS OF YEARS AND TRANSACTIONS INCLUDING/BELONGING TO THE GROUP TO DELETE TO DIALOG FOR THE LIST
        /// SET CORRECT DIMENSIONS TOO
        eraseConfirmation.setInfoList(iLanguage, confirmationText.toStdString() , YearsIncludingTransactionOfGroupToDelete, NumberOfTransactionPerYearOfGroupToDelete, showTable);
        eraseConfirmation.setOverallThemeStyleSheet(overallThemeStyleSheetString, usingDarkTheme);
        eraseConfirmation.setTableHeaderStyleSheet(tableHeaderStyleSheet);
        eraseConfirmation.exec();

        if (eraseConfirmation.comfirmed())
        {
            groupDeleted = true;

            for (int i= 0; i != 150; ++i){    ///Search in 150 years 1950-2100
                yearData.clear_Year();
                yearData.set_Year(1950+i);
                if (yearData.load_Data()) {
                    if (editingIncomeGroups){
                        yearData.swapGroupForIncomeTransactions(index.row()+1, 0);
                    } else{
                        yearData.swapGroupsForExpensesTransactions((index.row()+1), 0); /// 0 (Zero as new group) Not classified
                    }
                    yearData.save_Data();
                }
            }
            ui->tableWidgetGroups->removeRow(index.row());

            //RELOAD INFORMATION AND DISPLAY IT ON TABLE//
            yearData.clear_Year();
            yearData.set_Year(currentYear);

            //yearData.loadGroups();          ///Always load groups first
            if (editingIncomeGroups == false){
                yearData.deleteExpensesGroup(index.row()+1);
                yearData.saveExpensesGroups();
                yearData.load_Data();
                std::cout<<"EXPENSE GROUP DELETED"<<'\n';

                short itemId = 0;
                for (std::vector<std::string>::iterator it2= yearData.ExpensesGroupsNames.begin()+1; it2 != yearData.ExpensesGroupsNames.end(); ++it2)
                {
                    ui->tableWidgetGroups->setItem(itemId, 0, new QTableWidgetItem (QString::fromStdString(*it2)));
                    std::cout<<"List item id: "<<++itemId<<" Name: "<<*it2<<'\n';
                }
            }
            else if (editingIncomeGroups == true){
                yearData.deleteIncomeGroup(index.row()+1);///PROBLEM OCCURS AT THIS POINT!!!! AFTER ADDING AN ELEMENT AND THEN DELETING ONE, OR DELETING THE SAME.
                yearData.saveIncomeGroups();
                yearData.load_Data();
                yearData.loadIncomeGroups();
                std::cout<<"INCOME GROUP DELETED"<<'\n';

                short itemId = 0;
                for (std::vector<std::string>::iterator it2= yearData.IncomeGroupsNames.begin()+1; it2 != yearData.IncomeGroupsNames.end(); ++it2)
                {
                    ui->tableWidgetGroups->setItem(itemId, 0, new QTableWidgetItem (QString::fromStdString(*it2)));
                    std::cout<<"List item id: "<<++itemId<<" Name: "<<*it2<<'\n';
                }
                this->ui->tableWidgetGroups->clearSelection();
            }

        }
    }
    else if (highlightedRows.count() == 0) {
        if (iLanguage == ENGLISH)
        {
            ui->labelInfo->setText("Please select an group to delete first.");
        }
        else if (iLanguage == GERMAN)
        {
            ui->labelInfo->setText("BItte, wählen Sie zuerst eine Gruppe.");
        }
        else if (iLanguage == SPANISH)
        {
            ui->labelInfo->setText("Por favor, seleccione un grupo primero.");
        }
    }
}

void ManageGroupsDialog::on_deleteGroupButton_clicked()
{
    this->deleteSelectedGroup();
}

void ManageGroupsDialog::on_acceptButton_clicked()
{
    this->close();
}
