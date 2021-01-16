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

#include "eraseconfirmation_dialog.h"
#include "ui_eraseconfirmation_dialog.h"
#include "sstream"

eraseConfirmation_dialog::eraseConfirmation_dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::eraseConfirmation_dialog)
{
    ui->setupUi(this);
    ui->label->setWordWrap(true);
    ui->tableWidget->setFrameStyle(QFrame::NoFrame);
    ui->groupBoxButtons->setStyleSheet("QGroupBox#groupBoxButtons{border:1px solid gray; border-color:rgba(255, 255, 255, 0); }");
    ui->pushButtonOk->installEventFilter(this);
    ui->pushButtonCancel->installEventFilter(this);
}

eraseConfirmation_dialog::~eraseConfirmation_dialog()
{
    delete ui;
}

bool eraseConfirmation_dialog::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::MouseButtonPress)
    {
        if (qobject_cast<QWidget*>(obj) == ui->pushButtonOk) {
            this->ui->pushButtonOk->setColorForMouseButtonPressEvent();
        }
        else if (qobject_cast<QWidget*>(obj) == ui->pushButtonCancel) {
            this->ui->pushButtonCancel->setColorForMouseButtonPressEvent();
        }
    }
    else if (event->type() == QEvent::MouseButtonRelease)
    {
        if (qobject_cast<QWidget*>(obj) == ui->pushButtonOk) {
            this->ui->pushButtonOk->setColorForEnterEvent();
        }
        else if (qobject_cast<QWidget*>(obj) == ui->pushButtonCancel) {
            this->ui->pushButtonCancel->setColorForEnterEvent();
        }
    }
    else if (event->type() == QEvent::Enter)
     {
         if (qobject_cast<QPushButton*>(obj) == ui->pushButtonOk)
         {
             this->ui->pushButtonOk->setColorForEnterEvent();
         }
         else if (qobject_cast<QWidget*>(obj) == ui->pushButtonCancel) {
             this->ui->pushButtonCancel->setColorForEnterEvent();
         }
    }
    else if (event->type() == QEvent::Leave)
     {
         if (qobject_cast<QPushButton*>(obj) == ui->pushButtonOk)
         {
             this->ui->pushButtonOk->setColorForLeaveEvent();
         }
         else if (qobject_cast<QWidget*>(obj) == ui->pushButtonCancel) {
             this->ui->pushButtonCancel->setColorForLeaveEvent();
         }
    }
    return false;
}

void eraseConfirmation_dialog::setOverallThemeStyleSheet(QString styleSheetString, bool usingDarkTheme)
{
    this->setStyleSheet(styleSheetString);
    //this->ui->tableWidget->setStyleSheet(styleSheetString);
    this->ui->pushButtonOk->updateColorTheme(usingDarkTheme);
    this->ui->pushButtonCancel->updateColorTheme(usingDarkTheme);
}

void eraseConfirmation_dialog::setTableHeaderStyleSheet(QString tTableHeaderStyleSheet)
{
    this->ui->tableWidget->setStyleSheet(tTableHeaderStyleSheet);
}

void eraseConfirmation_dialog::setInfoText(const std::string &text)
{
    ui->tableWidget->setVisible(false);
    ui->label->setText(QString::fromStdString(text));
    ui->label->setAlignment(Qt::AlignTop);

    this->setFixedSize(this->width(), this->height());
}

void eraseConfirmation_dialog::setInfoList(const Language &iLanguage, const std::string &info,
                                           const std::vector<int> &listOfYears, const std::vector<int> &listOfNumberOfTransactions,
                                           bool showTable)
{
    std::vector<int>::const_iterator listOfYearsIterator                  = listOfYears.begin();
    std::vector<int>::const_iterator listOfNumberOfTransactionsIterator   = listOfNumberOfTransactions.begin();

    this->ui->label->setText(QString::fromStdString(info));
    this->ui->tableWidget->setTabKeyNavigation(false);

    if (showTable)
    {
        ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
        ui->tableWidget->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);

        if (listOfYears.size() < 3) {
            this->ui->groupBoxButtons->setGeometry(290,95,190,44);
        } else if (listOfYears.size() == 3) {
            this->ui->groupBoxButtons->setGeometry(290,110,190,44);
        } else {
            this->ui->groupBoxButtons->setGeometry(290,130,190,44);
        }
        this->ui->tableWidget->setVisible(true);

        this->ui->tableWidget->setColumnCount(2);
        QStringList tableHeader;
        if (iLanguage == ENGLISH){
            tableHeader<<"Year"<<"Transactions";
            this->ui->pushButtonCancel->setText("Cancel");

        } else if (iLanguage == GERMAN){
            tableHeader<<"Jahr"<<"Transaktionen";
            this->ui->pushButtonCancel->setText("Abbrechen");
        } else if (iLanguage == SPANISH){
            tableHeader<<"Año"<<"Transacciones";
            this->ui->pushButtonCancel->setText("Cancelar");
        }
        this->ui->tableWidget->setHorizontalHeaderLabels(tableHeader);
        this->ui->tableWidget->setColumnWidth(0,this->ui->tableWidget->width()/3);
        this->ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
        this->ui->tableWidget->setRowCount(listOfYears.size());

        for (size_t currentRow = 0; currentRow != listOfYears.size(); ++currentRow)
        {
            /////////////////////////////////FIRST COLUMN///////////////////////////////////
            ///--------------------------------------------------------------------------///
            this->ui->tableWidget->setItem(currentRow, 0, new QTableWidgetItem (QString::number(*listOfYearsIterator)));
            this->ui->tableWidget->item(currentRow, 0)->setTextAlignment(Qt::AlignBottom | Qt::AlignHCenter);

            /////////////////////////////////SECOND COLUMN//////////////////////////////////
            ///--------------------------------------------------------------------------///
            this->ui->tableWidget->setItem(currentRow, 1, new QTableWidgetItem (QString::number(*listOfNumberOfTransactionsIterator)));
            this->ui->tableWidget->item(currentRow, 1)->setTextAlignment(Qt::AlignBottom | Qt::AlignHCenter);

            ///--------------------------------------------------------------------------///
            ++listOfYearsIterator;
            ++listOfNumberOfTransactionsIterator;

            this->ui->tableWidget->setRowHeight(currentRow, 22);
        }

        if (listOfYears.size() < 3) {
            this->setFixedHeight(150);
        } else if (listOfYears.size() == 3) {
            this->setFixedHeight(165);
        } else {
            this->setFixedHeight(185);
        }
        this->setFixedWidth(this->width());
    }
}

void eraseConfirmation_dialog::on_pushButtonOk_clicked()
{
    Accepted = true;
    this->close();
}

void eraseConfirmation_dialog::on_pushButtonCancel_clicked()
{
    Accepted = false;
    this->close();
}

void eraseConfirmation_dialog::disableCancelButton()
{
    this->ui->pushButtonCancel->setVisible(false);
    this->setFixedWidth(this->width()-90);
}
