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

#include "newelementsaddedautomaticallydialog.h"
#include "ui_newelementsaddedautomaticallydialog.h"
#include "keibomoneytrackerinclude.h"

newElementsAddedAutomaticallyDialog::newElementsAddedAutomaticallyDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::newElementsAddedAutomaticallyDialog)
{
    ui->setupUi(this);
    ui->tableWidget->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
    ui->pushButtonClose->installEventFilter(this);
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
}

newElementsAddedAutomaticallyDialog::~newElementsAddedAutomaticallyDialog()
{
    delete ui;
}

void newElementsAddedAutomaticallyDialog::setLanguage(const Language &currentLanguage)
{
    iLanguage = currentLanguage;

    if (iLanguage == ENGLISH)
    {
        this->setWindowTitle(" Information");
        this->ui->labelInfo->setText("The following transactions were added automatically:");
        this->ui->pushButtonClose->setText("Close");
    }
    else if (iLanguage == GERMAN)
    {
        this->setWindowTitle(" Information");
        this->ui->labelInfo->setText("Folgende Transaktionen wurden bereits hinzugefügt:");
        this->ui->pushButtonClose->setText("Schlißen");
    }
    else if (iLanguage == SPANISH)
    {
        this->setWindowTitle(" Información");
        this->ui->labelInfo->setText("Las siguientes transacciones se añadieron automaticamente:");
        this->ui->pushButtonClose->setText("Cerrar");
    }
}

void newElementsAddedAutomaticallyDialog::setOverallThemeStyleSheet(QString styleSheetString, bool tUsingDarkTheme)
{
    QString tablesStyleSheet = "QTableCornerButton::section {"+styleSheetString + "border-radius : 6px; }"
                       "QTableWidget{border: 1px solid gray; "+styleSheetString + "border-radius : 3px;}";

    ui->tableWidget->setStyleSheet(tablesStyleSheet);

    QString horizontalHeaderStyleSheet = "QHeaderView::section { "+styleSheetString+" border-radius : 0px; border-bottom: 1px solid gray; }";
    ui->tableWidget->horizontalHeader()->setStyleSheet(horizontalHeaderStyleSheet);

    QString verticalHeaderStyleSheet = "QHeaderView::section {"+styleSheetString+" border-radius : 6px;}";
    ui->tableWidget->verticalHeader()->setStyleSheet(verticalHeaderStyleSheet);

    ui->tableWidget->verticalHeader()->setDefaultAlignment(Qt::AlignBottom | Qt::AlignmentFlag::AlignHCenter);
    this->setStyleSheet(styleSheetString);

    this->setStyleSheet(styleSheetString);
    this->ui->pushButtonClose->updateColorTheme(tUsingDarkTheme);
    usingDarkTheme = tUsingDarkTheme;
}

bool newElementsAddedAutomaticallyDialog::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::MouseButtonPress)
    {
        if (qobject_cast<QWidget*>(obj) == ui->pushButtonClose) {
            this->ui->pushButtonClose->setColorForMouseButtonPressEvent();
        }
    }
    else if (event->type() == QEvent::MouseButtonRelease)
    {
        if (qobject_cast<QWidget*>(obj) == ui->pushButtonClose) {
            this->ui->pushButtonClose->setColorForEnterEvent();
        }
    }
    else if (event->type() == QEvent::Enter)
     {
         if (qobject_cast<QPushButton*>(obj) == ui->pushButtonClose)  {
             this->ui->pushButtonClose->setColorForEnterEvent();
         }
    }
    else if (event->type() == QEvent::Leave)
     {
         if (qobject_cast<QPushButton*>(obj) == ui->pushButtonClose)  {
             this->ui->pushButtonClose->setColorForLeaveEvent();
         }
    }
    return false;
}

void newElementsAddedAutomaticallyDialog::getInfoToDisplay(std::vector<Transaction> &newElementsAdded,
                                                           std::vector<std::string> &incomeGroups,
                                                           std::vector<std::string> &outcomeGroups,
                                                           const int &colorOfIncomeAmount,
                                                           const Language &currentLanguage)
{
    ui->tableWidget->setColumnCount(5);
    QStringList tableHeader;
    if (iLanguage == ENGLISH)
    {
        tableHeader<<"Name"<<"Amount"<<"Day"<<"Month"<<"Group";
    }
    else if (iLanguage == GERMAN)
    {
        tableHeader<<"Name"<<"Betrag"<<"Tag"<<"Monat"<<"Gruppe";
    }
    else if (iLanguage == SPANISH)
    {
        tableHeader<<"Nombre"<<"Monto"<<"Día"<<"Mes"<<"Grupo";
    }
    ui->tableWidget->setHorizontalHeaderLabels(tableHeader);
    ui->tableWidget->setColumnWidth(0,175);
    ui->tableWidget->setColumnWidth(1,82);
    ui->tableWidget->setColumnWidth(2,40);
    ui->tableWidget->setColumnWidth(3,88);
    ui->tableWidget->setColumnWidth(4,90);

    ui->tableWidget->setRowCount(newElementsAdded.size());
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);

    int item_Id = 0;
    std::vector<std::string>::iterator groupIterator        = outcomeGroups.begin();
    std::vector<std::string>::iterator incomeGroupIterator  = incomeGroups.begin();

    for (std::vector<Transaction>::iterator it = newElementsAdded.begin(); it != newElementsAdded.end(); ++it)
    {
        /////////////////////////////////FIRST COLUMN///////////////////////////////////
        ///--------------------------------------------------------------------------///
        ui->tableWidget->setItem(item_Id,0, new QTableWidgetItem (QString::fromStdString(it->Name)));
        ui->tableWidget->item(item_Id, 0)->setTextAlignment(Qt::AlignLeft);
        ui->tableWidget->item(item_Id, 0)->setTextAlignment(Qt::AlignBottom);
        ui->tableWidget->setWordWrap(false);

        /////////////////////////////////SECOND COLUMN//////////////////////////////////
        ///--------------------------------------------------------------------------///
        if (it->IsIncome){
            if (currentLanguage == GERMAN) {
                ui->tableWidget->setItem(item_Id,1, new QTableWidgetItem (QString("+")+ QString::fromStdString(getAmountAsStringInGermanFormat(it->Amount) )) );
            } else {
                ui->tableWidget->setItem(item_Id,1, new QTableWidgetItem (QString("+")+ QString::number(it->Amount, 0, 2)));
            }
            //Set color of IncomeAmount dynamically
            int r = 0, g = 0, b = 0;
            getColorCode(colorOfIncomeAmount, r, g, b);
            ui->tableWidget->item(item_Id, 1)->setForeground(QColor(r, g, b));
        }
        else if (!(it->IsIncome)){
            if (currentLanguage == GERMAN) {
                ui->tableWidget->setItem(item_Id,1, new QTableWidgetItem (QString("-")+ QString::fromStdString(getAmountAsStringInGermanFormat(it->Amount) )) );
            } else {
                ui->tableWidget->setItem(item_Id,1, new QTableWidgetItem (QString("-")+ QString::number(it->Amount, 0, 2)));
            }
        }
        ui->tableWidget->item(item_Id,1)->setTextAlignment(Qt::AlignmentFlag::AlignRight | Qt::AlignmentFlag::AlignBottom);

        /////////////////////////////////THIRD COLUMN///////////////////////////////////
        ///--------------------------------------------------------------------------///
        ui->tableWidget->setItem(item_Id,2, new QTableWidgetItem (QString::number(it->Day)));
        ui->tableWidget->item(item_Id,2)->setTextAlignment(Qt::AlignmentFlag::AlignHCenter | Qt::AlignmentFlag::AlignBottom);

        /////////////////////////////////FOURTH COLUMN///////////////////////////////////
        ///--------------------------------------------------------------------------///
        ui->tableWidget->setItem(item_Id,3, new QTableWidgetItem (QString::fromStdString(getMonthInLanguage(it->Month, currentLanguage))) );
        ui->tableWidget->item(item_Id,3)->setTextAlignment(Qt::AlignmentFlag::AlignHCenter | Qt::AlignmentFlag::AlignBottom);

        /////////////////////////////////FIFTH COLUMN//////////////////////////////////
        ///--------------------------------------------------------------------------///
        if (it->IsIncome){
            ui->tableWidget->setItem(item_Id,4, new QTableWidgetItem (QString::fromStdString(*(incomeGroupIterator+(it->Group)))));
        }
        else if (!(it->IsIncome)){
            ui->tableWidget->setItem(item_Id,4, new QTableWidgetItem (QString::fromStdString(*(groupIterator+(it->Group)))));
        }
        ui->tableWidget->item(item_Id,4)->setTextAlignment(Qt::AlignmentFlag::AlignHCenter | Qt::AlignmentFlag::AlignBottom);
        ui->tableWidget->setRowHeight(item_Id, 22);
        ++item_Id;
    }
    ui->tableWidget->horizontalHeader()->setVisible(true);
}

void newElementsAddedAutomaticallyDialog::on_pushButtonClose_clicked()
{
    this->close();
}
