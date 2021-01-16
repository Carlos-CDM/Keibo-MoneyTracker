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

#include "checkfaultytransactionsdialog.h"
#include "ui_checkfaultytransactionsdialog.h"

#include <iostream>
#include <eraseconfirmation_dialog.h>
#include <QKeyEvent>

checkFaultyTransactionsDialog::checkFaultyTransactionsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::checkFaultyTransactionsDialog)
{
    ui->setupUi(this);

        Name_   = "";
        Price_  = 0.0;
        Month_  = 0.0;
        Day_    = 0;
        Category_ = 0;
        Repeat_ = DO_NOT_REPEAT;

        ui->textName->installEventFilter(this);
        ui->textPrice->installEventFilter(this);
        ui->comboBoxCategory->installEventFilter(this);
        ui->comboBoxDay->installEventFilter(this);
        ui->comboBoxMonth->installEventFilter(this);
        ui->comboBoxRepeat->installEventFilter(this);
        ui->SetAndNextButton->installEventFilter(this);
        ui->discardButton->installEventFilter(this);
        ui->discardAllButton->installEventFilter(this);
        
        ui->textName->setWordWrapMode(QTextOption::NoWrap);
        ui->textName->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        ui->textName->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

        this->setTabOrder(ui->textName,ui->textPrice);
        this->setTabOrder(ui->textPrice,ui->comboBoxCategory);
        this->setTabOrder(ui->comboBoxCategory,ui->comboBoxDay);
        this->setTabOrder(ui->comboBoxDay,ui->comboBoxMonth);
        this->setTabOrder(ui->comboBoxMonth,ui->comboBoxRepeat);
        this->setTabOrder(ui->comboBoxRepeat,ui->discardAllButton);
        this->setTabOrder(ui->discardAllButton,ui->discardButton);
        this->setTabOrder(ui->discardButton,ui->SetAndNextButton);
}

checkFaultyTransactionsDialog::~checkFaultyTransactionsDialog()
{
    delete ui;
}

void checkFaultyTransactionsDialog::setLanguage(const Language &iLanguage)
{
    currentLanguage = iLanguage;
    for (int monthId = 0; monthId != 12; ++monthId)
    {
        ui->comboBoxMonth->addItem(QString::fromStdString(getMonthInLanguage(monthId, currentLanguage)) );
    }

    if (currentLanguage == ENGLISH)
    {
        this->setWindowTitle(" Verify transactions");
        this->ui->labelName->setText("Name:");
        this->ui->labelAmount->setText("Amount:");
        this->ui->discardButton->setText("Discard");
        this->ui->discardAllButton->setText("Discard all");
        this->ui->SetAndNextButton->setText("Save and next");
        this->ui->labelRepeat->setText("Repeat:");
        this->ui->comboBoxRepeat->addItem("Do not repeat");
        this->ui->comboBoxRepeat->addItem("Every week");
        this->ui->comboBoxRepeat->addItem("Every two weeks");
        this->ui->comboBoxRepeat->addItem("Every month");
    }
    else if (currentLanguage == GERMAN)
    {
        this->setWindowTitle(" Transaktionen überprüfen");
        this->ui->labelName->setText("Name:");
        this->ui->labelAmount->setText("Betrag:");
        this->ui->discardButton->setText("Verwerfen");
        this->ui->discardAllButton->setText("Alles verwerfen");
        this->ui->SetAndNextButton->setText("Speichern und nächste");
        this->ui->labelRepeat->setText("Wiederholen:");
        this->ui->comboBoxRepeat->addItem("Nicht");
        this->ui->comboBoxRepeat->addItem("Jede Woche");
        this->ui->comboBoxRepeat->addItem("Jede zwei Wochen");
        this->ui->comboBoxRepeat->addItem("Jeden Monat");
    }
    else if (currentLanguage == SPANISH)
    {
        this->setWindowTitle(" Verificar transacciones");
        this->ui->labelName->setText("Nombre:");
        this->ui->labelAmount->setText("Monto:");
        this->ui->discardButton->setText("Descartar");
        this->ui->discardAllButton->setText("Descartar todo");
        this->ui->SetAndNextButton->setText("Guardar y siguiente");
        this->ui->labelRepeat->setText("Repetir:");
        this->ui->comboBoxRepeat->addItem("No repetir");
        this->ui->comboBoxRepeat->addItem("Cada semana");
        this->ui->comboBoxRepeat->addItem("Cada dos semanas");
        this->ui->comboBoxRepeat->addItem("Cada mes");
    }
}

void checkFaultyTransactionsDialog::setOverallThemeStyleSheet(QString styleSheetString, bool tUsingDarkTheme)
{
    this->setStyleSheet(styleSheetString);
    overallThemeStyleSheetString = styleSheetString;
    usingDarkTheme = tUsingDarkTheme;
    this->ui->textName->updateColorTheme(usingDarkTheme);
    this->ui->textPrice->updateColorTheme(usingDarkTheme);
    this->ui->textName->updateColorTheme(usingDarkTheme);
    this->ui->comboBoxDay->updateColorTheme(usingDarkTheme);
    this->ui->comboBoxMonth->updateColorTheme(usingDarkTheme);
    this->ui->comboBoxRepeat->updateColorTheme(usingDarkTheme);
    this->ui->comboBoxCategory->updateColorTheme(usingDarkTheme);
    this->ui->discardButton->updateColorTheme(usingDarkTheme);
    this->ui->discardAllButton->updateColorTheme(usingDarkTheme);
    this->ui->SetAndNextButton->updateColorTheme(usingDarkTheme);

}

void checkFaultyTransactionsDialog::checkAndSetTransaction() //Save/Set all variables/information and Verifies that a name and amount is given.
{
    transactionNameOK      = false;
    transactionAmountOK    = false;

    Name_         = ui->textName->toPlainText();
    Price_        = ui->textPrice->toPlainText();
    Month_        = ui->comboBoxMonth->currentIndex();
    Day_          = ui->comboBoxDay->currentIndex();
    Category_     = ui->comboBoxCategory->currentIndex();
    /*if (ui->checkBoxRepeat->isChecked())
       {
           Repeat_ = DO_NOT_REPEAT;
       }*/

    //If Price has a comma instead of a point replace it by a point
    std::string tempString = Price_.toStdString();
    double      tempPrice  = Price_.toDouble();
    bool amountOk = true;
    int numberOfPoints = 0;
    bool ignoreLeftWhiteSpaces = false;
    bool numberRecognized = false;
    bool blockNextNumber = false;
    for (unsigned int i = 0; i != tempString.size(); ++i)
    {
        //Ignore left side white spaces
        if ((tempString[i] == ' ') && (!ignoreLeftWhiteSpaces)){
            continue;
        }
        ignoreLeftWhiteSpaces = true;

        //Block the recognition of further numbers if a number was already recognized and a whiteSpace appears
        if ((tempString[i] == ' ') && (numberRecognized)){
            blockNextNumber = true;
        }

        //Take commas as points and count them to not allow more than one
        if ((tempString[i] == ',') || (tempString[i] == '.')) {
            tempString[i] = '.';
            ++numberOfPoints;
        }

        //Only allow numbers, point, comma and whitespaces in loop
        if ((tempString[i] != '0') && (tempString[i] != '1') && (tempString[i] != '2') && (tempString[i] != '3') && (tempString[i] != '4') &&
            (tempString[i] != '5') && (tempString[i] != '6') && (tempString[i] != '7') && (tempString[i] != '8') && (tempString[i] != '9') &&
            (tempString[i] != ',') && (tempString[i] != '.') && (tempString[i] != ' ')) {
            //std::cout<<"WRONG CHARACTER IN AMOUNT FOUND: "<<tempString[i]<<'\n';
            amountOk = false;
        }

        //A number or valid symbol was recognized
        numberRecognized = true;

        //If a number was recognized after already having whiteSpaces in between, ask for verification
        //But if the symbol is a whiteSpace ignore and keep amountOK=true
        if (blockNextNumber && (tempString[i] != ' ')){
            amountOk = false;
            //std::cout<<"A WHITE SPACE IN BETWEEN WAS FOUND"<<'\n';
        }
    }

    if ((numberOfPoints>1) || (Price_.toStdString().empty())) {amountOk = false;}
    //std::cout<<"Price processed, "<<tempString<<'\n';

    Price_.clear();
    Price_ = QString::fromStdString(tempString);

    if (!Name_.isEmpty()){
        transactionNameOK = true;
    }
    if ((tempPrice > (-0.001)) && amountOk){
        std::cout<<"TRANSACTION AMOUNT OK "<<'\n';
        transactionAmountOK = true;
    }
}

bool checkFaultyTransactionsDialog::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::KeyPress)
    {
        if (qobject_cast<QTextEdit*>(obj) == ui->textName)
          {
            QKeyEvent* key = static_cast<QKeyEvent*>(event);
            if ( (key->key()==Qt::Key_Enter) || (key->key()==Qt::Key_Return) ) {
                this->checkAndSetTransaction();
                if(transactionNameOK && transactionAmountOK){ //If a name and amount have been given, close.
                    this->addUpdatedTransactionToList();
                }
                else if (transactionNameOK && !transactionAmountOK) {
                    this->focusNextChild();
                    this->ui->textPrice->selectAll();   //Select all text in Price
                }
                else if (!transactionNameOK && transactionAmountOK) {
                    eraseConfirmation_dialog eraseConfirmationWindow;
                    eraseConfirmationWindow.setModal(true);
                    if (currentLanguage == ENGLISH)
                    {
                        eraseConfirmationWindow.setWindowTitle(" Information");
                        eraseConfirmationWindow.setInfoText("Every transaction needs a name.");
                    }
                    else if (currentLanguage == GERMAN)
                    {
                        eraseConfirmationWindow.setWindowTitle(" Information");
                        eraseConfirmationWindow.setInfoText("Ein Name wird benötigt.");
                    }
                    else if (currentLanguage == SPANISH)
                    {
                        eraseConfirmationWindow.setWindowTitle(" Información");
                        eraseConfirmationWindow.setInfoText("Cada transacción necesita un nombre.");
                    }
                    eraseConfirmationWindow.setOverallThemeStyleSheet(overallThemeStyleSheetString, usingDarkTheme);
                    eraseConfirmationWindow.exec();
                }
                else if (!transactionNameOK && !transactionAmountOK) {
                    eraseConfirmation_dialog eraseConfirmationWindow;
                    eraseConfirmationWindow.setModal(true);
                    if (currentLanguage == ENGLISH)
                    {
                        eraseConfirmationWindow.setWindowTitle(" Information");
                        eraseConfirmationWindow.setInfoText("Every transaction needs a name.");
                    }
                    else if (currentLanguage == GERMAN)
                    {
                        eraseConfirmationWindow.setWindowTitle(" Information");
                        eraseConfirmationWindow.setInfoText("Ein Name wird benötigt.");
                    }
                    else if (currentLanguage == SPANISH)
                    {
                        eraseConfirmationWindow.setWindowTitle(" Información");
                        eraseConfirmationWindow.setInfoText("Cada transacción necesita un nombre.");
                    }
                    eraseConfirmationWindow.setOverallThemeStyleSheet(overallThemeStyleSheetString, usingDarkTheme);
                    eraseConfirmationWindow.exec();
                    }
                return true;
            }
            else if (key->key()==Qt::Key_Tab) {
                this->focusNextChild();
                this->ui->textPrice->selectAll();   //Select all text in Price
                return true;
            }
          }
        else if (qobject_cast<QTextEdit*>(obj) == ui->textPrice)
          {
            QKeyEvent* key = static_cast<QKeyEvent*>(event);
            if ( (key->key()==Qt::Key_Enter) || (key->key()==Qt::Key_Return) ) {
                this->checkAndSetTransaction();
                if(transactionNameOK && transactionAmountOK){ //If a name and amount have been given, close.
                    this->addUpdatedTransactionToList();
                }
                else if (!transactionNameOK && transactionAmountOK){
                    eraseConfirmation_dialog eraseConfirmationWindow;
                    eraseConfirmationWindow.setModal(true);
                    if (currentLanguage == ENGLISH)
                    {
                        eraseConfirmationWindow.setWindowTitle(" Information");
                        eraseConfirmationWindow.setInfoText("Every transaction needs a name.");
                    }
                    else if (currentLanguage == GERMAN)
                    {
                        eraseConfirmationWindow.setWindowTitle(" Information");
                        eraseConfirmationWindow.setInfoText("Ein Name wird benötigt.");
                    }
                    else if (currentLanguage == SPANISH)
                    {
                        eraseConfirmationWindow.setWindowTitle(" Información");
                        eraseConfirmationWindow.setInfoText("Cada transacción necesita un nombre.");
                    }
                    eraseConfirmationWindow.setOverallThemeStyleSheet(overallThemeStyleSheetString, usingDarkTheme);
                    eraseConfirmationWindow.exec();
                    this->focusPreviousChild();
                }
                else if (transactionNameOK && !transactionAmountOK){
                    eraseConfirmation_dialog eraseConfirmationWindow;
                    eraseConfirmationWindow.setModal(true);
                    if (currentLanguage == ENGLISH)
                    {
                        eraseConfirmationWindow.setWindowTitle(" Information");
                        eraseConfirmationWindow.setInfoText("Please enter a valid amount.");
                    }
                    else if (currentLanguage == GERMAN)
                    {
                        eraseConfirmationWindow.setWindowTitle(" Information");
                        eraseConfirmationWindow.setInfoText("Bitte geben Sie einen gültigen Betrag ein.");
                    }
                    else if (currentLanguage == SPANISH)
                    {
                        eraseConfirmationWindow.setWindowTitle(" Información");
                        eraseConfirmationWindow.setInfoText("Por favor introduzca un monto válido.");
                    }
                    eraseConfirmationWindow.setOverallThemeStyleSheet(overallThemeStyleSheetString, usingDarkTheme);
                    eraseConfirmationWindow.exec();
                }
                else if (!transactionNameOK && !transactionAmountOK){
                    eraseConfirmation_dialog eraseConfirmationWindow;
                    eraseConfirmationWindow.setModal(true);
                    if (currentLanguage == ENGLISH)
                    {
                        eraseConfirmationWindow.setWindowTitle(" Information");
                        eraseConfirmationWindow.setInfoText("Every transaction needs a name.");
                    }
                    else if (currentLanguage == GERMAN)
                    {
                        eraseConfirmationWindow.setWindowTitle(" Information");
                        eraseConfirmationWindow.setInfoText("Ein Name wird benötigt.");
                    }
                    else if (currentLanguage == SPANISH)
                    {
                        eraseConfirmationWindow.setWindowTitle(" Información");
                        eraseConfirmationWindow.setInfoText("Cada transacción necesita un nombre.");
                    }
                    eraseConfirmationWindow.setOverallThemeStyleSheet(overallThemeStyleSheetString, usingDarkTheme);
                    eraseConfirmationWindow.exec();
                    this->focusPreviousChild();
                }
                return true;
            }
            else if (key->key()==Qt::Key_Tab) {
                QTextCursor cursor = ui->textPrice->textCursor();
                cursor.movePosition( QTextCursor::End );
                ui->textPrice->setTextCursor( cursor );
                this->focusNextChild();
                return true;
            }
          }
        else if (qobject_cast<QComboBox*>(obj) == ui->comboBoxCategory)
          {
            QKeyEvent* key = static_cast<QKeyEvent*>(event);
            if ( (key->key()==Qt::Key_Enter) || (key->key()==Qt::Key_Return) ) {
                this->checkAndSetTransaction();
                if(transactionNameOK && transactionAmountOK){ //If a name and amount have been given, close.
                    this->addUpdatedTransactionToList();
                }
                else if (!transactionNameOK && transactionAmountOK){
                    eraseConfirmation_dialog eraseConfirmationWindow;
                    eraseConfirmationWindow.setModal(true);
                    if (currentLanguage == ENGLISH)
                    {
                        eraseConfirmationWindow.setWindowTitle(" Information");
                        eraseConfirmationWindow.setInfoText("Every transaction needs a name.");
                    }
                    else if (currentLanguage == GERMAN)
                    {
                        eraseConfirmationWindow.setWindowTitle(" Information");
                        eraseConfirmationWindow.setInfoText("Ein Name wird benötigt.");
                    }
                    else if (currentLanguage == SPANISH)
                    {
                        eraseConfirmationWindow.setWindowTitle(" Información");
                        eraseConfirmationWindow.setInfoText("Cada transacción necesita un nombre.");
                    }
                    eraseConfirmationWindow.setOverallThemeStyleSheet(overallThemeStyleSheetString, usingDarkTheme);
                    eraseConfirmationWindow.exec();
                    this->focusPreviousChild();
                    this->focusPreviousChild();
                }
                else if (transactionNameOK && !transactionAmountOK){
                    eraseConfirmation_dialog eraseConfirmationWindow;
                    eraseConfirmationWindow.setModal(true);
                    if (currentLanguage == ENGLISH)
                    {
                        eraseConfirmationWindow.setWindowTitle(" Information");
                        eraseConfirmationWindow.setInfoText("Please enter a valid amount.");
                    }
                    else if (currentLanguage == GERMAN)
                    {
                        eraseConfirmationWindow.setWindowTitle(" Information");
                        eraseConfirmationWindow.setInfoText("Bitte geben Sie einen gültigen Betrag ein.");
                    }
                    else if (currentLanguage == SPANISH)
                    {
                        eraseConfirmationWindow.setWindowTitle(" Información");
                        eraseConfirmationWindow.setInfoText("Por favor introduzca un monto válido.");
                    }
                    eraseConfirmationWindow.setOverallThemeStyleSheet(overallThemeStyleSheetString, usingDarkTheme);
                    eraseConfirmationWindow.exec();
                    this->focusPreviousChild();
                    this->ui->textPrice->selectAll();   //Select all text in Price
                }
                else if (!transactionNameOK && !transactionAmountOK){
                    eraseConfirmation_dialog eraseConfirmationWindow;
                    eraseConfirmationWindow.setModal(true);
                    if (currentLanguage == ENGLISH)
                    {
                        eraseConfirmationWindow.setWindowTitle(" Information");
                        eraseConfirmationWindow.setInfoText("Every transaction needs a name.");
                    }
                    else if (currentLanguage == GERMAN)
                    {
                        eraseConfirmationWindow.setWindowTitle(" Information");
                        eraseConfirmationWindow.setInfoText("Ein Name wird benötigt.");
                    }
                    else if (currentLanguage == SPANISH)
                    {
                        eraseConfirmationWindow.setWindowTitle(" Información");
                        eraseConfirmationWindow.setInfoText("Cada transacción necesita un nombre.");
                    }
                    eraseConfirmationWindow.setOverallThemeStyleSheet(overallThemeStyleSheetString, usingDarkTheme);
                    eraseConfirmationWindow.exec();
                    this->focusPreviousChild();
                    this->focusPreviousChild();
                }
                return true;
            }
            else if (key->key()==Qt::Key_Tab) {
                this->focusNextChild();
                return true;
            }
          }
        else if (qobject_cast<QComboBox*>(obj) == ui->comboBoxDay)
          {
            QKeyEvent* key = static_cast<QKeyEvent*>(event);
            if ( (key->key()==Qt::Key_Enter) || (key->key()==Qt::Key_Return) ) {
                this->checkAndSetTransaction();
                if(transactionNameOK && transactionAmountOK){ //If a name and amount have been given, close.
                    this->addUpdatedTransactionToList();
                }
                else if (!transactionNameOK && transactionAmountOK){
                    eraseConfirmation_dialog eraseConfirmationWindow;
                    eraseConfirmationWindow.setModal(true);
                    if (currentLanguage == ENGLISH)
                    {
                        eraseConfirmationWindow.setWindowTitle(" Information");
                        eraseConfirmationWindow.setInfoText("Every transaction needs a name.");
                    }
                    else if (currentLanguage == GERMAN)
                    {
                        eraseConfirmationWindow.setWindowTitle(" Information");
                        eraseConfirmationWindow.setInfoText("Ein Name wird benötigt.");
                    }
                    else if (currentLanguage == SPANISH)
                    {
                        eraseConfirmationWindow.setWindowTitle(" Información");
                        eraseConfirmationWindow.setInfoText("Cada transacción necesita un nombre.");
                    }
                    eraseConfirmationWindow.setOverallThemeStyleSheet(overallThemeStyleSheetString, usingDarkTheme);
                    eraseConfirmationWindow.exec();
                    this->focusPreviousChild();
                    this->focusPreviousChild();
                    this->focusPreviousChild();
                }
                else if (transactionNameOK && !transactionAmountOK){
                    eraseConfirmation_dialog eraseConfirmationWindow;
                    eraseConfirmationWindow.setModal(true);
                    if (currentLanguage == ENGLISH)
                    {
                        eraseConfirmationWindow.setWindowTitle(" Information");
                        eraseConfirmationWindow.setInfoText("Please enter a valid amount.");
                    }
                    else if (currentLanguage == GERMAN)
                    {
                        eraseConfirmationWindow.setWindowTitle(" Information");
                        eraseConfirmationWindow.setInfoText("Bitte geben Sie einen gültigen Betrag ein.");
                    }
                    else if (currentLanguage == SPANISH)
                    {
                        eraseConfirmationWindow.setWindowTitle(" Información");
                        eraseConfirmationWindow.setInfoText("Por favor introduzca un monto válido.");
                    }
                    eraseConfirmationWindow.setOverallThemeStyleSheet(overallThemeStyleSheetString, usingDarkTheme);
                    eraseConfirmationWindow.exec();
                    this->focusPreviousChild();
                    this->focusPreviousChild();
                    this->ui->textPrice->selectAll();   //Select all text in Price
                }
                else if (!transactionNameOK && !transactionAmountOK){
                    eraseConfirmation_dialog eraseConfirmationWindow;
                    eraseConfirmationWindow.setModal(true);
                    if (currentLanguage == ENGLISH)
                    {
                        eraseConfirmationWindow.setWindowTitle(" Information");
                        eraseConfirmationWindow.setInfoText("Every transaction needs a name.");
                    }
                    else if (currentLanguage == GERMAN)
                    {
                        eraseConfirmationWindow.setWindowTitle(" Information");
                        eraseConfirmationWindow.setInfoText("Ein Name wird benötigt.");
                    }
                    else if (currentLanguage == SPANISH)
                    {
                        eraseConfirmationWindow.setWindowTitle(" Información");
                        eraseConfirmationWindow.setInfoText("Cada transacción necesita un nombre.");
                    }
                    eraseConfirmationWindow.setOverallThemeStyleSheet(overallThemeStyleSheetString, usingDarkTheme);
                    eraseConfirmationWindow.exec();
                    this->focusPreviousChild();
                    this->focusPreviousChild();
                    this->focusPreviousChild();
                }
                return true;
            }
            else if (key->key()==Qt::Key_Tab) {
                this->focusNextChild();
                return true;
            }
          }
       else if (qobject_cast<QComboBox*>(obj) == ui->comboBoxMonth)
          {
            QKeyEvent* key = static_cast<QKeyEvent*>(event);
            if ( (key->key()==Qt::Key_Enter) || (key->key()==Qt::Key_Return) ) {
                this->checkAndSetTransaction();
                if(transactionNameOK && transactionAmountOK){ //If a name and amount have been given, close.
                    this->addUpdatedTransactionToList();
                }
                else if (!transactionNameOK && transactionAmountOK){
                    eraseConfirmation_dialog eraseConfirmationWindow;
                    eraseConfirmationWindow.setModal(true);
                    if (currentLanguage == ENGLISH)
                    {
                        eraseConfirmationWindow.setWindowTitle(" Information");
                        eraseConfirmationWindow.setInfoText("Every transaction needs a name.");
                    }
                    else if (currentLanguage == GERMAN)
                    {
                        eraseConfirmationWindow.setWindowTitle(" Information");
                        eraseConfirmationWindow.setInfoText("Ein Name wird benötigt.");
                    }
                    else if (currentLanguage == SPANISH)
                    {
                        eraseConfirmationWindow.setWindowTitle(" Información");
                        eraseConfirmationWindow.setInfoText("Cada transacción necesita un nombre.");
                    }
                    eraseConfirmationWindow.setOverallThemeStyleSheet(overallThemeStyleSheetString, usingDarkTheme);
                    eraseConfirmationWindow.exec();
                    this->focusPreviousChild();
                    this->focusPreviousChild();
                    this->focusPreviousChild();
                    this->focusPreviousChild();
                }
                else if (transactionNameOK && !transactionAmountOK){
                    eraseConfirmation_dialog eraseConfirmationWindow;
                    eraseConfirmationWindow.setModal(true);
                    if (currentLanguage == ENGLISH)
                    {
                        eraseConfirmationWindow.setWindowTitle(" Information");
                        eraseConfirmationWindow.setInfoText("Please enter a valid amount.");
                    }
                    else if (currentLanguage == GERMAN)
                    {
                        eraseConfirmationWindow.setWindowTitle(" Information");
                        eraseConfirmationWindow.setInfoText("Bitte geben Sie einen gültigen Betrag ein.");
                    }
                    else if (currentLanguage == SPANISH)
                    {
                        eraseConfirmationWindow.setWindowTitle(" Información");
                        eraseConfirmationWindow.setInfoText("Por favor introduzca un monto válido.");
                    }
                    eraseConfirmationWindow.setOverallThemeStyleSheet(overallThemeStyleSheetString, usingDarkTheme);
                    eraseConfirmationWindow.exec();
                    this->focusPreviousChild();
                    this->focusPreviousChild();
                    this->focusPreviousChild();
                    this->ui->textPrice->selectAll();   //Select all text in Price
                }
                else if (!transactionNameOK && !transactionAmountOK){
                    eraseConfirmation_dialog eraseConfirmationWindow;
                    eraseConfirmationWindow.setModal(true);
                    if (currentLanguage == ENGLISH)
                    {
                        eraseConfirmationWindow.setWindowTitle(" Information");
                        eraseConfirmationWindow.setInfoText("Every transaction needs a name.");
                    }
                    else if (currentLanguage == GERMAN)
                    {
                        eraseConfirmationWindow.setWindowTitle(" Information");
                        eraseConfirmationWindow.setInfoText("Ein Name wird benötigt.");
                    }
                    else if (currentLanguage == SPANISH)
                    {
                        eraseConfirmationWindow.setWindowTitle(" Información");
                        eraseConfirmationWindow.setInfoText("Cada transacción necesita un nombre.");
                    }
                    eraseConfirmationWindow.setOverallThemeStyleSheet(overallThemeStyleSheetString, usingDarkTheme);
                    eraseConfirmationWindow.exec();
                    this->focusPreviousChild();
                    this->focusPreviousChild();
                    this->focusPreviousChild();
                    this->focusPreviousChild();
                }
                return true;
            }
            else if (key->key()==Qt::Key_Tab) {
                this->focusNextChild();
                return true;
            }
          }
        else if (qobject_cast<QComboBox*>(obj) == ui->comboBoxRepeat)
          {
            QKeyEvent* key = static_cast<QKeyEvent*>(event);
            if ( (key->key()==Qt::Key_Enter) || (key->key()==Qt::Key_Return) ) {
                this->checkAndSetTransaction();
                if(transactionNameOK && transactionAmountOK){ //If a name and amount have been given, close.
                    this->addUpdatedTransactionToList();
                }
                else if (!transactionNameOK && transactionAmountOK){
                    eraseConfirmation_dialog eraseConfirmationWindow;
                    eraseConfirmationWindow.setModal(true);
                    if (currentLanguage == ENGLISH)
                    {
                        eraseConfirmationWindow.setWindowTitle(" Information");
                        eraseConfirmationWindow.setInfoText("Every transaction needs a name.");
                    }
                    else if (currentLanguage == GERMAN)
                    {
                        eraseConfirmationWindow.setWindowTitle(" Information");
                        eraseConfirmationWindow.setInfoText("Ein Name wird benötigt.");
                    }
                    else if (currentLanguage == SPANISH)
                    {
                        eraseConfirmationWindow.setWindowTitle(" Información");
                        eraseConfirmationWindow.setInfoText("Cada transacción necesita un nombre.");
                    }
                    eraseConfirmationWindow.setOverallThemeStyleSheet(overallThemeStyleSheetString, usingDarkTheme);
                    eraseConfirmationWindow.exec();
                    this->focusNextChild();
                    this->focusNextChild();
                    this->focusNextChild();
                    this->focusNextChild();
                }
                else if (transactionNameOK && !transactionAmountOK){
                    eraseConfirmation_dialog eraseConfirmationWindow;
                    eraseConfirmationWindow.setModal(true);
                    if (currentLanguage == ENGLISH)
                    {
                        eraseConfirmationWindow.setWindowTitle(" Information");
                        eraseConfirmationWindow.setInfoText("Please enter a valid amount.");
                    }
                    else if (currentLanguage == GERMAN)
                    {
                        eraseConfirmationWindow.setWindowTitle(" Information");
                        eraseConfirmationWindow.setInfoText("Bitte geben Sie einen gültigen Betrag ein.");
                    }
                    else if (currentLanguage == SPANISH)
                    {
                        eraseConfirmationWindow.setWindowTitle(" Información");
                        eraseConfirmationWindow.setInfoText("Por favor introduzca un monto válido.");
                    }
                    eraseConfirmationWindow.setOverallThemeStyleSheet(overallThemeStyleSheetString, usingDarkTheme);
                    eraseConfirmationWindow.exec();
                    this->focusPreviousChild();
                    this->focusPreviousChild();
                    this->focusPreviousChild();
                    this->focusPreviousChild();
                    this->ui->textPrice->selectAll();   //Select all text in Price
                }
                else if (!transactionNameOK && !transactionAmountOK){
                    eraseConfirmation_dialog eraseConfirmationWindow;
                    eraseConfirmationWindow.setModal(true);
                    if (currentLanguage == ENGLISH)
                    {
                        eraseConfirmationWindow.setWindowTitle(" Information");
                        eraseConfirmationWindow.setInfoText("Every transaction needs a name.");
                    }
                    else if (currentLanguage == GERMAN)
                    {
                        eraseConfirmationWindow.setWindowTitle(" Information");
                        eraseConfirmationWindow.setInfoText("Ein Name wird benötigt.");
                    }
                    else if (currentLanguage == SPANISH)
                    {
                        eraseConfirmationWindow.setWindowTitle(" Información");
                        eraseConfirmationWindow.setInfoText("Cada transacción necesita un nombre.");
                    }
                    eraseConfirmationWindow.setOverallThemeStyleSheet(overallThemeStyleSheetString, usingDarkTheme);
                    eraseConfirmationWindow.exec();
                    this->focusNextChild();
                    this->focusNextChild();
                    this->focusNextChild();
                    this->focusNextChild();
                }
                return true;
            }
            else if (key->key()==Qt::Key_Tab) {
                this->focusNextChild();
                std::cout<<"KEY TAB PRESSED FROM CHECK BOX REPEAT"<<'\n';
                return true;
            }
          }
        else if (qobject_cast<QPushButton*>(obj) == ui->discardAllButton)
          {
            QKeyEvent* key = static_cast<QKeyEvent*>(event);
            if ( (key->key()==Qt::Key_Enter) || (key->key()==Qt::Key_Return) ) {
                this->close();
            }
            else if (key->key()==Qt::Key_Tab) {
                this->focusNextChild();
                return true;
            }
          }
        else if (qobject_cast<QPushButton*>(obj) == ui->discardButton)
          {
            QKeyEvent* key = static_cast<QKeyEvent*>(event);
            if ( (key->key()==Qt::Key_Enter) || (key->key()==Qt::Key_Return) ) {
                if ((currentTransaction+1) < listOfFaultyTransactions.size()){
                   ++currentTransaction;
                   this->updateInfo();
                } else if ((currentTransaction+1) == listOfFaultyTransactions.size()) {
                    this->close();
                }
            }
            else if (key->key()==Qt::Key_Tab) {
                this->focusNextChild();
                return true;
            }
          }
        else if (qobject_cast<QPushButton*>(obj) == ui->SetAndNextButton)
          {
            QKeyEvent* key = static_cast<QKeyEvent*>(event);
            if ( (key->key()==Qt::Key_Enter) || (key->key()==Qt::Key_Return) ) {
                this->checkAndSetTransaction();
                if(transactionNameOK && transactionAmountOK){ //If a name and amount have been given, close.
                    this->addUpdatedTransactionToList();
                }
                else if (!transactionNameOK && transactionAmountOK){
                    eraseConfirmation_dialog eraseConfirmationWindow;
                    eraseConfirmationWindow.setModal(true);
                    if (currentLanguage == ENGLISH)
                    {
                        eraseConfirmationWindow.setWindowTitle(" Information");
                        eraseConfirmationWindow.setInfoText("Every transaction needs a name.");
                    }
                    else if (currentLanguage == GERMAN)
                    {
                        eraseConfirmationWindow.setWindowTitle(" Information");
                        eraseConfirmationWindow.setInfoText("Ein Name wird benötigt.");
                    }
                    else if (currentLanguage == SPANISH)
                    {
                        eraseConfirmationWindow.setWindowTitle(" Información");
                        eraseConfirmationWindow.setInfoText("Cada transacción necesita un nombre.");
                    }
                    eraseConfirmationWindow.setOverallThemeStyleSheet(overallThemeStyleSheetString, usingDarkTheme);
                    eraseConfirmationWindow.exec();
                    this->focusNextChild();
                }
                else if (transactionNameOK && !transactionAmountOK){
                    eraseConfirmation_dialog eraseConfirmationWindow;
                    eraseConfirmationWindow.setModal(true);
                    if (currentLanguage == ENGLISH)
                    {
                        eraseConfirmationWindow.setWindowTitle(" Information");
                        eraseConfirmationWindow.setInfoText("Please enter a valid amount.");
                    }
                    else if (currentLanguage == GERMAN)
                    {
                        eraseConfirmationWindow.setWindowTitle(" Information");
                        eraseConfirmationWindow.setInfoText("Bitte geben Sie einen gültigen Betrag ein.");
                    }
                    else if (currentLanguage == SPANISH)
                    {
                        eraseConfirmationWindow.setWindowTitle(" Información");
                        eraseConfirmationWindow.setInfoText("Por favor introduzca un monto válido.");
                    }
                    eraseConfirmationWindow.setOverallThemeStyleSheet(overallThemeStyleSheetString, usingDarkTheme);
                    eraseConfirmationWindow.exec();
                    this->focusNextChild();
                    this->focusNextChild();
                    this->ui->textPrice->selectAll();   //Select all text in Price
                }
                else if (!transactionNameOK && !transactionAmountOK){
                    eraseConfirmation_dialog eraseConfirmationWindow;
                    eraseConfirmationWindow.setModal(true);
                    if (currentLanguage == ENGLISH)
                    {
                        eraseConfirmationWindow.setWindowTitle(" Information");
                        eraseConfirmationWindow.setInfoText("Every transaction needs a name.");
                    }
                    else if (currentLanguage == GERMAN)
                    {
                        eraseConfirmationWindow.setWindowTitle(" Information");
                        eraseConfirmationWindow.setInfoText("Ein Name wird benötigt.");
                    }
                    else if (currentLanguage == SPANISH)
                    {
                        eraseConfirmationWindow.setWindowTitle(" Información");
                        eraseConfirmationWindow.setInfoText("Cada transacción necesita un nombre.");
                    }
                    eraseConfirmationWindow.setOverallThemeStyleSheet(overallThemeStyleSheetString, usingDarkTheme);
                    eraseConfirmationWindow.exec();
                    this->focusNextChild();
                }
                return true;
            }
            else if (key->key()==Qt::Key_Tab) {
                this->focusNextChild();
                return true;
            }
          }
    }
    else if (event->type() == QEvent::MouseButtonPress)
    {
        if (qobject_cast<QWidget*>(obj) == ui->SetAndNextButton) {
            this->ui->SetAndNextButton->setColorForMouseButtonPressEvent();
        } else if (qobject_cast<QWidget*>(obj) == ui->discardButton) {
            this->ui->discardButton->setColorForMouseButtonPressEvent();
        } else if (qobject_cast<QWidget*>(obj) == ui->discardAllButton) {
            this->ui->discardAllButton->setColorForMouseButtonPressEvent();
        } else if (qobject_cast<QWidget*>(obj) == ui->comboBoxDay) {
            this->ui->comboBoxDay->setColorForMouseButtonPressEvent();
        } else if (qobject_cast<QWidget*>(obj) == ui->comboBoxMonth) {
            this->ui->comboBoxMonth->setColorForMouseButtonPressEvent();
        } else if (qobject_cast<QWidget*>(obj) == ui->comboBoxRepeat) {
            this->ui->comboBoxRepeat->setColorForMouseButtonPressEvent();
        } else if (qobject_cast<QWidget*>(obj) == ui->comboBoxCategory) {
            this->ui->comboBoxCategory->setColorForMouseButtonPressEvent();
        } else if (qobject_cast<QWidget*>(obj) == ui->textName) {
            this->ui->textName->setColorForMouseButtonPressEvent();
        } else if (qobject_cast<QWidget*>(obj) == ui->textPrice) {
            this->ui->textPrice->setColorForMouseButtonPressEvent();
        }

    }
    else if (event->type() == QEvent::MouseButtonRelease)
    {
        if (qobject_cast<QWidget*>(obj) == ui->SetAndNextButton) {
            this->ui->SetAndNextButton->setColorForEnterEvent();
        } else if (qobject_cast<QWidget*>(obj) == ui->discardButton) {
            this->ui->discardButton->setColorForEnterEvent();
        } else if (qobject_cast<QWidget*>(obj) == ui->discardAllButton) {
            this->ui->discardAllButton->setColorForEnterEvent();
        } else if (qobject_cast<QWidget*>(obj) == ui->comboBoxDay) {
            this->ui->comboBoxDay->setColorForEnterEvent();
        } else if (qobject_cast<QWidget*>(obj) == ui->comboBoxMonth) {
            this->ui->comboBoxMonth->setColorForEnterEvent();
        } else if (qobject_cast<QWidget*>(obj) == ui->comboBoxRepeat) {
            this->ui->comboBoxRepeat->setColorForEnterEvent();
        } else if (qobject_cast<QWidget*>(obj) == ui->comboBoxCategory) {
            this->ui->comboBoxCategory->setColorForEnterEvent();
        } else if (qobject_cast<QWidget*>(obj) == ui->textName) {
            this->ui->textName->setColorForEnterEvent();
        } else if (qobject_cast<QWidget*>(obj) == ui->textPrice) {
            this->ui->textPrice->setColorForEnterEvent();
        }
    }
    else if (event->type() == QEvent::Enter)
     {
        if (qobject_cast<QWidget*>(obj) == ui->SetAndNextButton) {
            this->ui->SetAndNextButton->setColorForEnterEvent();
        } else if (qobject_cast<QWidget*>(obj) == ui->discardButton) {
            this->ui->discardButton->setColorForEnterEvent();
        } else if (qobject_cast<QWidget*>(obj) == ui->discardAllButton) {
            this->ui->discardAllButton->setColorForEnterEvent();
        } else if (qobject_cast<QWidget*>(obj) == ui->comboBoxDay) {
            this->ui->comboBoxDay->setColorForEnterEvent();
        } else if (qobject_cast<QWidget*>(obj) == ui->comboBoxMonth) {
            this->ui->comboBoxMonth->setColorForEnterEvent();
        } else if (qobject_cast<QWidget*>(obj) == ui->comboBoxRepeat) {
            this->ui->comboBoxRepeat->setColorForEnterEvent();
        } else if (qobject_cast<QWidget*>(obj) == ui->comboBoxCategory) {
            this->ui->comboBoxCategory->setColorForEnterEvent();
        } else if (qobject_cast<QWidget*>(obj) == ui->textName) {
            this->ui->textName->setColorForEnterEvent();
        } else if (qobject_cast<QWidget*>(obj) == ui->textPrice) {
            this->ui->textPrice->setColorForEnterEvent();
        }
    }
    else if (event->type() == QEvent::Leave)
     {
        if (qobject_cast<QWidget*>(obj) == ui->SetAndNextButton) {
            this->ui->SetAndNextButton->setColorForLeaveEvent();
        } else if (qobject_cast<QWidget*>(obj) == ui->discardButton) {
            this->ui->discardButton->setColorForLeaveEvent();
        } else if (qobject_cast<QWidget*>(obj) == ui->discardAllButton) {
            this->ui->discardAllButton->setColorForLeaveEvent();
        } else if (qobject_cast<QWidget*>(obj) == ui->comboBoxDay) {
            this->ui->comboBoxDay->setColorForLeaveEvent();
        } else if (qobject_cast<QWidget*>(obj) == ui->comboBoxMonth) {
            this->ui->comboBoxMonth->setColorForLeaveEvent();
        } else if (qobject_cast<QWidget*>(obj) == ui->comboBoxRepeat) {
            this->ui->comboBoxRepeat->setColorForLeaveEvent();
        } else if (qobject_cast<QWidget*>(obj) == ui->comboBoxCategory) {
            this->ui->comboBoxCategory->setColorForLeaveEvent();
        } else if (qobject_cast<QWidget*>(obj) == ui->textName) {
            this->ui->textName->setColorForLeaveEvent();
        } else if (qobject_cast<QWidget*>(obj) == ui->textPrice) {
            this->ui->textPrice->setColorForLeaveEvent();
        }
     }
    else if (event->type() == QEvent::FocusIn)
     {
        if (qobject_cast<QWidget*>(obj) == ui->SetAndNextButton) {
            this->ui->SetAndNextButton->setColorForEnterEvent();
        } else if (qobject_cast<QWidget*>(obj) == ui->discardButton) {
            this->ui->discardButton->setColorForEnterEvent();
        } else if (qobject_cast<QWidget*>(obj) == ui->discardAllButton) {
            this->ui->discardAllButton->setColorForEnterEvent();
        } else if (qobject_cast<QWidget*>(obj) == ui->comboBoxDay) {
            this->ui->comboBoxDay->setColorForEnterEvent();
        } else if (qobject_cast<QWidget*>(obj) == ui->comboBoxMonth) {
            this->ui->comboBoxMonth->setColorForEnterEvent();
        } else if (qobject_cast<QWidget*>(obj) == ui->comboBoxRepeat) {
            this->ui->comboBoxRepeat->setColorForEnterEvent();
        } else if (qobject_cast<QWidget*>(obj) == ui->comboBoxCategory) {
            this->ui->comboBoxCategory->setColorForEnterEvent();
        } else if (qobject_cast<QWidget*>(obj) == ui->textName) {
            this->ui->textName->setColorForEnterEvent();
        } else if (qobject_cast<QWidget*>(obj) == ui->textPrice) {
            this->ui->textPrice->setColorForEnterEvent();
        }
     }
    else if (event->type() == QEvent::FocusOut)
     {
        if (qobject_cast<QWidget*>(obj) == ui->SetAndNextButton) {
            this->ui->SetAndNextButton->setColorForLeaveEvent();
        } else if (qobject_cast<QWidget*>(obj) == ui->discardButton) {
            this->ui->discardButton->setColorForLeaveEvent();
        } else if (qobject_cast<QWidget*>(obj) == ui->discardAllButton) {
            this->ui->discardAllButton->setColorForLeaveEvent();
        } else if (qobject_cast<QWidget*>(obj) == ui->comboBoxDay) {
            this->ui->comboBoxDay->setColorForLeaveEvent();
        } else if (qobject_cast<QWidget*>(obj) == ui->comboBoxMonth) {
            this->ui->comboBoxMonth->setColorForLeaveEvent();
        } else if (qobject_cast<QWidget*>(obj) == ui->comboBoxRepeat) {
            this->ui->comboBoxRepeat->setColorForLeaveEvent();
        } else if (qobject_cast<QWidget*>(obj) == ui->comboBoxCategory) {
            this->ui->comboBoxCategory->setColorForLeaveEvent();
        } else if (qobject_cast<QWidget*>(obj) == ui->textName) {
            this->ui->textName->setColorForLeaveEvent();
        } else if (qobject_cast<QWidget*>(obj) == ui->textPrice) {
            this->ui->textPrice->setColorForLeaveEvent();
        }
     }
    return false;
}

void checkFaultyTransactionsDialog::setCategoryList(std::vector<std::string> categoryList)
{
    ui->comboBoxCategory->clear();
    for (std::vector<std::string>::iterator catIt = categoryList.begin(); catIt != categoryList.end(); ++catIt)
    {
        ui->comboBoxCategory->addItem(QString::fromStdString(*catIt));
    }
}

void checkFaultyTransactionsDialog::displayItemInfo(std::string Nam, double Pri, int Cat, int Mon, int Day, RepetitionOption Repeat)
{
    ui->textName->setText(QString::fromStdString(Nam));
    ui->comboBoxCategory->setCurrentIndex(Cat);
    ui->comboBoxMonth->setCurrentIndex(Mon);
    ui->comboBoxDay->setCurrentIndex(Day-1);
    ui->comboBoxRepeat->setCurrentIndex(static_cast<int>(Repeat));

    if (currentLanguage == GERMAN) {
        ui->textPrice->setText(QString::fromStdString(getAmountAsStringInGermanFormat(Pri)));
    } else {
        ui->textPrice->setText(QString::number(Pri, 0, 2));
    }
}

void checkFaultyTransactionsDialog::on_SetAndNextButton_clicked()
{
    this->checkAndSetTransaction();
    if(transactionNameOK && transactionAmountOK){ //If a name and amount have been given, close.
        this->addUpdatedTransactionToList();
    }
    else if (!transactionNameOK && transactionAmountOK){
        eraseConfirmation_dialog eraseConfirmationWindow;
        eraseConfirmationWindow.setModal(true);
        if (currentLanguage == ENGLISH)
        {
            eraseConfirmationWindow.setWindowTitle(" Information");
            eraseConfirmationWindow.setInfoText("Every transaction needs a name.");
        }
        else if (currentLanguage == GERMAN)
        {
            eraseConfirmationWindow.setWindowTitle(" Information");
            eraseConfirmationWindow.setInfoText("Ein Name wird benötigt.");
        }
        else if (currentLanguage == SPANISH)
        {
            eraseConfirmationWindow.setWindowTitle(" Información");
            eraseConfirmationWindow.setInfoText("Cada transacción necesita un nombre.");
        }
        eraseConfirmationWindow.setOverallThemeStyleSheet(overallThemeStyleSheetString, usingDarkTheme);
        eraseConfirmationWindow.exec();
        this->focusNextChild();
    }
    else if (transactionNameOK && !transactionAmountOK){
        eraseConfirmation_dialog eraseConfirmationWindow;
        eraseConfirmationWindow.setModal(true);
        if (currentLanguage == ENGLISH)
        {
            eraseConfirmationWindow.setWindowTitle(" Information");
            eraseConfirmationWindow.setInfoText("Please enter a valid amount.");
        }
        else if (currentLanguage == GERMAN)
        {
            eraseConfirmationWindow.setWindowTitle(" Information");
            eraseConfirmationWindow.setInfoText("Bitte geben Sie einen gültigen Betrag ein.");
        }
        else if (currentLanguage == SPANISH)
        {
            eraseConfirmationWindow.setWindowTitle(" Información");
            eraseConfirmationWindow.setInfoText("Por favor introduzca un monto válido.");
        }
        eraseConfirmationWindow.setOverallThemeStyleSheet(overallThemeStyleSheetString, usingDarkTheme);
        eraseConfirmationWindow.exec();
        this->focusNextChild();
        this->focusNextChild();
    }
    else if (!transactionNameOK && !transactionAmountOK){
        eraseConfirmation_dialog eraseConfirmationWindow;
        eraseConfirmationWindow.setModal(true);
        if (currentLanguage == ENGLISH)
        {
            eraseConfirmationWindow.setWindowTitle(" Information");
            eraseConfirmationWindow.setInfoText("Every transaction needs a name.");
        }
        else if (currentLanguage == GERMAN)
        {
            eraseConfirmationWindow.setWindowTitle(" Information");
            eraseConfirmationWindow.setInfoText("Ein Name wird benötigt.");
        }
        else if (currentLanguage == SPANISH)
        {
            eraseConfirmationWindow.setWindowTitle(" Información");
            eraseConfirmationWindow.setInfoText("Cada transacción necesita un nombre.");
        }
        eraseConfirmationWindow.setOverallThemeStyleSheet(overallThemeStyleSheetString, usingDarkTheme);
        eraseConfirmationWindow.exec();
        this->focusNextChild();
    }
}

void checkFaultyTransactionsDialog::getFaultyTransactionsData(std::vector<Transaction> &tempListOfFaultyTransactions, const int &tempYearOfFaultyTransactions)
{
    listOfFaultyTransactions = tempListOfFaultyTransactions;
    yearOfFaultyTransactions = tempYearOfFaultyTransactions;
}

void checkFaultyTransactionsDialog::provideArticleInfo(Transaction &transaction, bool isIncome)
{
    std::string tempName        = Name_.toStdString();
    double      tempPrice       = Price_.toDouble();
    int         tempMonth       = Month_;
    int         tempDay         = Day_+1;
    int         tempGroup       = Category_;
    RepetitionOption tempRepeat = Repeat_;

    if (isIncome) {
        Transaction tempTransaction(tempName, tempPrice, tempMonth, tempDay, tempGroup, tempRepeat, true);
        transaction = tempTransaction;
        std::cout<<"INCOME TRANSACTION UPDATED"<<tempName<<'\n';
    } else if (!isIncome) {
        Transaction tempTransaction(tempName, tempPrice, tempMonth, tempDay, tempGroup, tempRepeat);
        transaction = tempTransaction;
        std::cout<<"EXPENSE TRANSACTION UPDATED"<<tempName<<'\n';
    }
}

void checkFaultyTransactionsDialog::updateInfo()
{
    std::vector<Transaction>::iterator transactionIterator = listOfFaultyTransactions.begin()+currentTransaction;

    if (transactionIterator->IsIncome){
        this->setCategoryList(incomeGroups);
    } else if (transactionIterator->IsIncome == false){
        this->setCategoryList(expensesGroups);
    }

    this->displayItemInfo(transactionIterator->Name,
                          transactionIterator->Amount,
                          transactionIterator->Group,
                          transactionIterator->Month,
                          transactionIterator->Day,
                          transactionIterator->Repetition_Option);

        if (currentLanguage == ENGLISH)
        {
            this->ui->labelInfo->setText("Verify transaction "+QString::number(currentTransaction+1)+" of "+QString::number(listOfFaultyTransactions.size())+".");
            this->ui->labelInfo->setAlignment(Qt::AlignCenter);

            if ((currentTransaction+1) == listOfFaultyTransactions.size()){
                this->ui->SetAndNextButton->setText("Save and Close");
                this->ui->discardButton->setText("Discard and Close");
                this->ui->discardAllButton->setDisabled(true);
            }
        }
        else if (currentLanguage == GERMAN)
        {
            this->ui->labelInfo->setText("Transaktion " +QString::number(currentTransaction+1)+" von "+QString::number(listOfFaultyTransactions.size())+" prüfen.");
            this->ui->labelInfo->setAlignment(Qt::AlignCenter);

            if ((currentTransaction+1) == listOfFaultyTransactions.size()){
                this->ui->SetAndNextButton->setText("Speichern und schließen");
                this->ui->discardButton->setText("Verwerfen und schließen");
                this->ui->discardAllButton->setDisabled(true);
            }
        }
        else if (currentLanguage == SPANISH)
        {
            this->ui->labelInfo->setText("Verificar transacción "+QString::number(currentTransaction+1)+" de "+QString::number(listOfFaultyTransactions.size())+".");
            this->ui->labelInfo->setAlignment(Qt::AlignCenter);

            if ((currentTransaction+1) == listOfFaultyTransactions.size()){
                this->ui->SetAndNextButton->setText("Guardar y cerrar");
                this->ui->discardButton->setText("Descartar y cerrar");
                this->ui->discardAllButton->setDisabled(true);
            }
        }
}

void checkFaultyTransactionsDialog::addUpdatedTransactionToList()
{
    if ((currentTransaction+1) == listOfFaultyTransactions.size()){
        std::vector<Transaction>::iterator itUpdatedTransaction = listOfFaultyTransactions.begin()+currentTransaction;
        //Create new Article with updated values here
        if (itUpdatedTransaction->IsIncome){
            Transaction updatedTransaction;
            this->provideArticleInfo(updatedTransaction, true);
            listOfUpdatedTransactions.push_back(updatedTransaction);

        } else if (itUpdatedTransaction->IsIncome == false) {
            Transaction updatedTransaction;
            this->provideArticleInfo(updatedTransaction, false);
            listOfUpdatedTransactions.push_back(updatedTransaction);
        }
        this->close();
    } else {
        std::vector<Transaction>::iterator itUpdatedTransaction = listOfFaultyTransactions.begin()+currentTransaction;
        //Create new Article with updated values here
        if (itUpdatedTransaction->IsIncome){
            Transaction updatedTransaction;
            this->provideArticleInfo(updatedTransaction, true);
            listOfUpdatedTransactions.push_back(updatedTransaction);

        } else if (itUpdatedTransaction->IsIncome == false) {
            Transaction updatedTransaction;
            this->provideArticleInfo(updatedTransaction, false);
            listOfUpdatedTransactions.push_back(updatedTransaction);
        }
        ++currentTransaction;
        this->updateInfo();
    }
}

void checkFaultyTransactionsDialog::provideUpdatedTransactions(std::vector<Transaction> &tempListOfUpdatedTransactions)
{
    tempListOfUpdatedTransactions = listOfUpdatedTransactions;
}

void checkFaultyTransactionsDialog::on_discardButton_clicked()
{
     if ((currentTransaction+1) < listOfFaultyTransactions.size()){
        ++currentTransaction;
        this->updateInfo();
     } else if ((currentTransaction+1) == listOfFaultyTransactions.size()) {
         this->close();
     }
}

void checkFaultyTransactionsDialog::on_discardAllButton_clicked()
{
    this->close();
}

void checkFaultyTransactionsDialog::on_comboBoxMonth_currentIndexChanged(int index)
{
    int selectedDay = this->ui->comboBoxDay->currentIndex();
    this->ui->comboBoxDay->clear();

    int Month = index;
    int NumberOfDaysInMonth = 0;

    if( Month == 1)
    {
        if((yearOfFaultyTransactions%400==0) || (yearOfFaultyTransactions%4==0 && yearOfFaultyTransactions%100!=0))
            NumberOfDaysInMonth = 29;
        else
            NumberOfDaysInMonth = 28;
    }
    else if (Month == 0 || Month == 2 || Month == 4 || Month == 6 || Month == 7 || Month == 9 || Month==11)	{
        NumberOfDaysInMonth = 31;
    }
    else {
        NumberOfDaysInMonth= 30;
    }

    for (int i = 1; i!=NumberOfDaysInMonth+1; ++i)
    {
        this->ui->comboBoxDay->addItem(QString::number(i));
    }

    if (selectedDay > (NumberOfDaysInMonth-1)){
        selectedDay = NumberOfDaysInMonth-1; //-1 Because Index starts from zero and NumberOfDaysInMonth doesn't.
    }
    this->ui->comboBoxDay->setCurrentIndex(selectedDay); //Index starts from zero
}
