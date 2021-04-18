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

#include "transactiondialog.h"
#include "ui_transactiondialog.h"
#include "eraseconfirmation_dialog.h"
#include <QKeyEvent>

TransactionDialog::TransactionDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TransactionDialog)
{
    ui->setupUi(this);

        transactionNameOK = false;
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
        ui->pushButtonOk->installEventFilter(this);

        ui->textName->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        ui->textPrice->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        ui->textName->setWordWrapMode(QTextOption::NoWrap);
        ui->textPrice->setWordWrapMode(QTextOption::NoWrap);

        this->setTabOrder(ui->textName,ui->textPrice);
        this->setTabOrder(ui->textPrice,ui->comboBoxCategory);
        this->setTabOrder(ui->comboBoxCategory,ui->comboBoxDay);
        this->setTabOrder(ui->comboBoxDay,ui->comboBoxMonth);
        this->setTabOrder(ui->comboBoxMonth,ui->comboBoxRepeat);
        this->setTabOrder(ui->comboBoxRepeat,ui->pushButtonOk);

        this->setFixedSize(this->width(), this->height());        

        ui->textName->setAlignment(Qt::AlignBottom);
        ui->textPrice->setAlignment(Qt::AlignBottom);
        setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
}

TransactionDialog::~TransactionDialog()
{
    delete ui;
}

void TransactionDialog::setLanguage(const Language &accountLanguage)
{
    iLanguage = accountLanguage;

    if (iLanguage == ENGLISH)
    {
        ui->comboBoxMonth->addItem("January");
        ui->comboBoxMonth->addItem("February");
        ui->comboBoxMonth->addItem("March");
        ui->comboBoxMonth->addItem("April");
        ui->comboBoxMonth->addItem("May");
        ui->comboBoxMonth->addItem("June");
        ui->comboBoxMonth->addItem("July");
        ui->comboBoxMonth->addItem("August");
        ui->comboBoxMonth->addItem("September");
        ui->comboBoxMonth->addItem("October");
        ui->comboBoxMonth->addItem("November");
        ui->comboBoxMonth->addItem("December");
        ui->labelName->setText("Name:");
        ui->labelAmount->setText("Amount:");
        ui->labelRepeat->setText("Repeat:");
        ui->comboBoxRepeat->addItem("Do not repeat");
        ui->comboBoxRepeat->addItem("Every week");
        ui->comboBoxRepeat->addItem("Every two weeks");
        ui->comboBoxRepeat->addItem("Every month");
    }
    else if (iLanguage == GERMAN)
    {
        ui->comboBoxMonth->addItem("Januar");
        ui->comboBoxMonth->addItem("Februar");
        ui->comboBoxMonth->addItem("März");
        ui->comboBoxMonth->addItem("April");
        ui->comboBoxMonth->addItem("Mai");
        ui->comboBoxMonth->addItem("Juni");
        ui->comboBoxMonth->addItem("Juli");
        ui->comboBoxMonth->addItem("August");
        ui->comboBoxMonth->addItem("September");
        ui->comboBoxMonth->addItem("Oktober");
        ui->comboBoxMonth->addItem("November");
        ui->comboBoxMonth->addItem("Dezember");
        ui->labelName->setText("Name");
        ui->labelAmount->setText("Betrag");
        ui->labelRepeat->setText("Wiederholen:");
        ui->comboBoxRepeat->addItem("Nein");
        ui->comboBoxRepeat->addItem("Jede Woche");
        ui->comboBoxRepeat->addItem("Jede zwei Wochen");
        ui->comboBoxRepeat->addItem("Jeden Monat");
    }
    else if (iLanguage == SPANISH)
    {
        ui->comboBoxMonth->addItem("Enero");
        ui->comboBoxMonth->addItem("Febrero");
        ui->comboBoxMonth->addItem("Marzo");
        ui->comboBoxMonth->addItem("Abril");
        ui->comboBoxMonth->addItem("Mayo");
        ui->comboBoxMonth->addItem("Junio");
        ui->comboBoxMonth->addItem("Julio");
        ui->comboBoxMonth->addItem("Agosto");
        ui->comboBoxMonth->addItem("Septiembre");
        ui->comboBoxMonth->addItem("Octubre");
        ui->comboBoxMonth->addItem("Noviembre");
        ui->comboBoxMonth->addItem("Diciembre");
        ui->labelName->setText("Nombre:");
        ui->labelAmount->setText("Monto:");
        ui->labelRepeat->setText("Repetir:");
        ui->comboBoxRepeat->addItem("No repetir");
        ui->comboBoxRepeat->addItem("Cada semana");
        ui->comboBoxRepeat->addItem("Cada dos semanas");
        ui->comboBoxRepeat->addItem("Cada mes");
    }

}

void TransactionDialog::setOverallThemeStyleSheet(QString styleSheetString, bool tUsingDarkTheme)
{
    this->setStyleSheet(styleSheetString);
    overallThemeStyleSheetString = styleSheetString;
    usingDarkTheme = tUsingDarkTheme;
    this->ui->pushButtonOk->updateColorTheme(usingDarkTheme);
    this->ui->comboBoxDay->updateColorTheme(usingDarkTheme);
    this->ui->comboBoxMonth->updateColorTheme(usingDarkTheme);
    this->ui->comboBoxRepeat->updateColorTheme(usingDarkTheme);
    this->ui->comboBoxCategory->updateColorTheme(usingDarkTheme);
    this->ui->textName->updateColorTheme(usingDarkTheme);
    this->ui->textPrice->updateColorTheme(usingDarkTheme);
}

void TransactionDialog::checkAndSetTransaction() //Save/Set all variables/information and Verifies that a name and amount is given.
{
    transactionNameOK      = false;
    transactionAmountOK    = false;

    Name_         = ui->textName->toPlainText();
    Price_        = ui->textPrice->toPlainText();
    Month_        = ui->comboBoxMonth->currentIndex();
    Day_          = ui->comboBoxDay->currentIndex();
    Category_     = ui->comboBoxCategory->currentIndex();
    Repeat_       = static_cast<RepetitionOption>(ui->comboBoxRepeat->currentIndex());

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
    if ((tempPrice >= (0.00)) && amountOk){
        std::cout<<"TRANSACTION AMOUNT OK "<<'\n';
        transactionAmountOK = true;
    }
}

bool TransactionDialog::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::KeyPress)
    {
        if (qobject_cast<QTextEdit*>(obj) == ui->textName)
          {
            QKeyEvent* key = static_cast<QKeyEvent*>(event);
            if ( (key->key()==Qt::Key_Enter) || (key->key()==Qt::Key_Return) ) {
                this->checkAndSetTransaction();
                if(transactionNameOK && transactionAmountOK){ //If a name and amount have been given, close.
                    this->close();
                } else if (transactionNameOK && !transactionAmountOK) {
                    this->focusNextChild();
                    this->ui->textPrice->selectAll();   //Select all text in Price
                } else if (!transactionNameOK && transactionAmountOK) {
                    eraseConfirmation_dialog eraseConfirmationWindow;
                    eraseConfirmationWindow.setModal(true);
                    eraseConfirmationWindow.setOverallThemeStyleSheet(overallThemeStyleSheetString, usingDarkTheme);
                    if (iLanguage == ENGLISH)
                    {
                        eraseConfirmationWindow.setWindowTitle(" Information");
                        eraseConfirmationWindow.setInfoText("Every transaction needs a name.");
                    }
                    else if (iLanguage == GERMAN)
                    {
                        eraseConfirmationWindow.setWindowTitle(" Information");
                        eraseConfirmationWindow.setInfoText("Ein Name wird benötigt.");
                    }
                    else if (iLanguage == SPANISH)
                    {
                        eraseConfirmationWindow.setWindowTitle(" Información");
                        eraseConfirmationWindow.setInfoText("Cada transacción necesita un nombre.");
                    }
                    eraseConfirmationWindow.exec();
                    }
                else if (!transactionNameOK && !transactionAmountOK) {
                    eraseConfirmation_dialog eraseConfirmationWindow;
                    eraseConfirmationWindow.setModal(true);
                    eraseConfirmationWindow.setOverallThemeStyleSheet(overallThemeStyleSheetString, usingDarkTheme);
                    if (iLanguage == ENGLISH)
                    {
                        eraseConfirmationWindow.setWindowTitle(" Information");
                        eraseConfirmationWindow.setInfoText("Every transaction needs a name.");
                    }
                    else if (iLanguage == GERMAN)
                    {
                        eraseConfirmationWindow.setWindowTitle(" Information");
                        eraseConfirmationWindow.setInfoText("Ein Name wird benötigt.");
                    }
                    else if (iLanguage == SPANISH)
                    {
                        eraseConfirmationWindow.setWindowTitle(" Información");
                        eraseConfirmationWindow.setInfoText("Cada transacción necesita un nombre.");
                    }
                    eraseConfirmationWindow.exec();
                    }
                return true;
            }
            else if (key->key()==Qt::Key_Tab) {
                this->focusNextChild();
                //std::cout<<"KEY TAB PRESSED FROM NAME"<<'\n';
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
                    this->close();
                } else if (!transactionNameOK && transactionAmountOK){
                    eraseConfirmation_dialog eraseConfirmationWindow;
                    eraseConfirmationWindow.setModal(true);
                    eraseConfirmationWindow.setOverallThemeStyleSheet(overallThemeStyleSheetString, usingDarkTheme);
                    if (iLanguage == ENGLISH)
                    {
                        eraseConfirmationWindow.setWindowTitle(" Information");
                        eraseConfirmationWindow.setInfoText("Every transaction needs a name.");
                    }
                    else if (iLanguage == GERMAN)
                    {
                        eraseConfirmationWindow.setWindowTitle(" Information");
                        eraseConfirmationWindow.setInfoText("Ein Name wird benötigt.");
                    }
                    else if (iLanguage == SPANISH)
                    {
                        eraseConfirmationWindow.setWindowTitle(" Información");
                        eraseConfirmationWindow.setInfoText("Cada transacción necesita un nombre.");
                    }
                    eraseConfirmationWindow.exec();
                    this->focusPreviousChild();
                }
                else if (transactionNameOK && !transactionAmountOK){
                    eraseConfirmation_dialog eraseConfirmationWindow;
                    eraseConfirmationWindow.setModal(true);
                    eraseConfirmationWindow.setOverallThemeStyleSheet(overallThemeStyleSheetString, usingDarkTheme);
                    if (iLanguage == ENGLISH)
                    {
                        eraseConfirmationWindow.setWindowTitle(" Information");
                        eraseConfirmationWindow.setInfoText("Please enter a valid amount.");
                    }
                    else if (iLanguage == GERMAN)
                    {
                        eraseConfirmationWindow.setWindowTitle(" Information");
                        eraseConfirmationWindow.setInfoText("Bitte geben Sie einen gültigen Betrag ein.");
                    }
                    else if (iLanguage == SPANISH)
                    {
                        eraseConfirmationWindow.setWindowTitle(" Información");
                        eraseConfirmationWindow.setInfoText("Por favor introduzca un monto válido.");
                    }
                    eraseConfirmationWindow.exec();
                    this->ui->textPrice->selectAll();   //Select all text in Price
                }
                else if (!transactionNameOK && !transactionAmountOK){
                    eraseConfirmation_dialog eraseConfirmationWindow;
                    eraseConfirmationWindow.setModal(true);
                    eraseConfirmationWindow.setOverallThemeStyleSheet(overallThemeStyleSheetString, usingDarkTheme);
                    if (iLanguage == ENGLISH)
                    {
                        eraseConfirmationWindow.setWindowTitle(" Information");
                        eraseConfirmationWindow.setInfoText("Every transaction needs a name.");
                    }
                    else if (iLanguage == GERMAN)
                    {
                        eraseConfirmationWindow.setWindowTitle(" Information");
                        eraseConfirmationWindow.setInfoText("Ein Name wird benötigt.");
                    }
                    else if (iLanguage == SPANISH)
                    {
                        eraseConfirmationWindow.setWindowTitle(" Información");
                        eraseConfirmationWindow.setInfoText("Cada transacción necesita un nombre.");
                    }
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
                //std::cout<<"KEY TAB PRESSED PRICE"<<'\n';
                return true;
            }
          }
        else if (qobject_cast<QComboBox*>(obj) == ui->comboBoxCategory)
          {
            QKeyEvent* key = static_cast<QKeyEvent*>(event);
            if ( (key->key()==Qt::Key_Enter) || (key->key()==Qt::Key_Return) ) {
                this->checkAndSetTransaction();
                if(transactionNameOK && transactionAmountOK){ //If a name and amount have been given, close.
                    this->close();
                } else if (!transactionNameOK && transactionAmountOK){
                    eraseConfirmation_dialog eraseConfirmationWindow;
                    eraseConfirmationWindow.setModal(true);
                    eraseConfirmationWindow.setOverallThemeStyleSheet(overallThemeStyleSheetString, usingDarkTheme);
                    if (iLanguage == ENGLISH)
                    {
                        eraseConfirmationWindow.setWindowTitle(" Information");
                        eraseConfirmationWindow.setInfoText("Every transaction needs a name.");
                    }
                    else if (iLanguage == GERMAN)
                    {
                        eraseConfirmationWindow.setWindowTitle(" Information");
                        eraseConfirmationWindow.setInfoText("Ein Name wird benötigt.");
                    }
                    else if (iLanguage == SPANISH)
                    {
                        eraseConfirmationWindow.setWindowTitle(" Información");
                        eraseConfirmationWindow.setInfoText("Cada transacción necesita un nombre.");
                    }
                    eraseConfirmationWindow.exec();
                    this->focusPreviousChild();
                    this->focusPreviousChild();
                }
                else if (transactionNameOK && !transactionAmountOK){
                    eraseConfirmation_dialog eraseConfirmationWindow;
                    eraseConfirmationWindow.setModal(true);
                    eraseConfirmationWindow.setOverallThemeStyleSheet(overallThemeStyleSheetString, usingDarkTheme);
                    if (iLanguage == ENGLISH)
                    {
                        eraseConfirmationWindow.setWindowTitle(" Information");
                        eraseConfirmationWindow.setInfoText("Please enter a valid amount.");
                    }
                    else if (iLanguage == GERMAN)
                    {
                        eraseConfirmationWindow.setWindowTitle(" Information");
                        eraseConfirmationWindow.setInfoText("Bitte geben Sie einen gültigen Betrag ein.");
                    }
                    else if (iLanguage == SPANISH)
                    {
                        eraseConfirmationWindow.setWindowTitle(" Información");
                        eraseConfirmationWindow.setInfoText("Por favor introduzca un monto válido.");
                    }
                    eraseConfirmationWindow.exec();
                    this->focusPreviousChild();
                    this->ui->textPrice->selectAll();   //Select all text in Price
                }
                else if (!transactionNameOK && !transactionAmountOK){
                    eraseConfirmation_dialog eraseConfirmationWindow;
                    eraseConfirmationWindow.setModal(true);
                    eraseConfirmationWindow.setOverallThemeStyleSheet(overallThemeStyleSheetString, usingDarkTheme);
                    if (iLanguage == ENGLISH)
                    {
                        eraseConfirmationWindow.setWindowTitle(" Information");
                        eraseConfirmationWindow.setInfoText("Every transaction needs a name.");
                    }
                    else if (iLanguage == GERMAN)
                    {
                        eraseConfirmationWindow.setWindowTitle(" Information");
                        eraseConfirmationWindow.setInfoText("Ein Name wird benötigt.");
                    }
                    else if (iLanguage == SPANISH)
                    {
                        eraseConfirmationWindow.setWindowTitle(" Información");
                        eraseConfirmationWindow.setInfoText("Cada transacción necesita un nombre.");
                    }
                    eraseConfirmationWindow.exec();
                    this->focusPreviousChild();
                    this->focusPreviousChild();
                }
                return true;
            }
            else if (key->key()==Qt::Key_Tab) {
                this->focusNextChild();
                //std::cout<<"KEY TAB PRESSED FROM CATEGORY"<<'\n';
                return true;
            }
          }
        else if (qobject_cast<QComboBox*>(obj) == ui->comboBoxDay)
          {
            QKeyEvent* key = static_cast<QKeyEvent*>(event);
            if ( (key->key()==Qt::Key_Enter) || (key->key()==Qt::Key_Return) ) {
                this->checkAndSetTransaction();
                if(transactionNameOK && transactionAmountOK){ //If a name and amount have been given, close.
                    this->close();
                } else if (!transactionNameOK && transactionAmountOK){
                    eraseConfirmation_dialog eraseConfirmationWindow;
                    eraseConfirmationWindow.setModal(true);
                    eraseConfirmationWindow.setOverallThemeStyleSheet(overallThemeStyleSheetString, usingDarkTheme);
                    if (iLanguage == ENGLISH)
                    {
                        eraseConfirmationWindow.setWindowTitle(" Information");
                        eraseConfirmationWindow.setInfoText("Every transaction needs a name.");
                    }
                    else if (iLanguage == GERMAN)
                    {
                        eraseConfirmationWindow.setWindowTitle(" Information");
                        eraseConfirmationWindow.setInfoText("Ein Name wird benötigt.");
                    }
                    else if (iLanguage == SPANISH)
                    {
                        eraseConfirmationWindow.setWindowTitle(" Información");
                        eraseConfirmationWindow.setInfoText("Cada transacción necesita un nombre.");
                    }
                    eraseConfirmationWindow.exec();
                    this->focusPreviousChild();
                    this->focusPreviousChild();
                    this->focusPreviousChild();
                }
                else if (transactionNameOK && !transactionAmountOK){
                    eraseConfirmation_dialog eraseConfirmationWindow;
                    eraseConfirmationWindow.setModal(true);
                    eraseConfirmationWindow.setOverallThemeStyleSheet(overallThemeStyleSheetString, usingDarkTheme);
                    if (iLanguage == ENGLISH)
                    {
                        eraseConfirmationWindow.setWindowTitle(" Information");
                        eraseConfirmationWindow.setInfoText("Please enter a valid amount.");
                    }
                    else if (iLanguage == GERMAN)
                    {
                        eraseConfirmationWindow.setWindowTitle(" Information");
                        eraseConfirmationWindow.setInfoText("Bitte geben Sie einen gültigen Betrag ein.");
                    }
                    else if (iLanguage == SPANISH)
                    {
                        eraseConfirmationWindow.setWindowTitle(" Información");
                        eraseConfirmationWindow.setInfoText("Por favor introduzca un monto válido.");
                    }
                    eraseConfirmationWindow.exec();
                    this->focusPreviousChild();
                    this->focusPreviousChild();
                    this->ui->textPrice->selectAll();   //Select all text in Price
                }
                else if (!transactionNameOK && !transactionAmountOK){
                    eraseConfirmation_dialog eraseConfirmationWindow;
                    eraseConfirmationWindow.setModal(true);
                    eraseConfirmationWindow.setOverallThemeStyleSheet(overallThemeStyleSheetString, usingDarkTheme);
                    if (iLanguage == ENGLISH)
                    {
                        eraseConfirmationWindow.setWindowTitle(" Information");
                        eraseConfirmationWindow.setInfoText("Every transaction needs a name.");
                    }
                    else if (iLanguage == GERMAN)
                    {
                        eraseConfirmationWindow.setWindowTitle(" Information");
                        eraseConfirmationWindow.setInfoText("Ein Name wird benötigt.");
                    }
                    else if (iLanguage == SPANISH)
                    {
                        eraseConfirmationWindow.setWindowTitle(" Información");
                        eraseConfirmationWindow.setInfoText("Cada transacción necesita un nombre.");
                    }
                    eraseConfirmationWindow.exec();
                    this->focusPreviousChild();
                    this->focusPreviousChild();
                    this->focusPreviousChild();
                }
                return true;
            }
            else if (key->key()==Qt::Key_Tab) {
                this->focusNextChild();
                //std::cout<<"KEY TAB PRESSED FROM DAY"<<'\n';
                return true;
            }
          }
       else if (qobject_cast<QComboBox*>(obj) == ui->comboBoxMonth)
          {
            QKeyEvent* key = static_cast<QKeyEvent*>(event);
            if ( (key->key()==Qt::Key_Enter) || (key->key()==Qt::Key_Return) ) {
                this->checkAndSetTransaction();
                if(transactionNameOK && transactionAmountOK){ //If a name and amount have been given, close.
                    this->close();
                } else if (!transactionNameOK && transactionAmountOK){
                    eraseConfirmation_dialog eraseConfirmationWindow;
                    eraseConfirmationWindow.setModal(true);
                    eraseConfirmationWindow.setOverallThemeStyleSheet(overallThemeStyleSheetString, usingDarkTheme);
                    if (iLanguage == ENGLISH)
                    {
                        eraseConfirmationWindow.setWindowTitle(" Information");
                        eraseConfirmationWindow.setInfoText("Every transaction needs a name.");
                    }
                    else if (iLanguage == GERMAN)
                    {
                        eraseConfirmationWindow.setWindowTitle(" Information");
                        eraseConfirmationWindow.setInfoText("Ein Name wird benötigt.");
                    }
                    else if (iLanguage == SPANISH)
                    {
                        eraseConfirmationWindow.setWindowTitle(" Información");
                        eraseConfirmationWindow.setInfoText("Cada transacción necesita un nombre.");
                    }
                    eraseConfirmationWindow.exec();
                    this->focusNextChild();
                    this->focusNextChild();
                    this->focusNextChild();
                }
                else if (transactionNameOK && !transactionAmountOK){
                    eraseConfirmation_dialog eraseConfirmationWindow;
                    eraseConfirmationWindow.setModal(true);
                    eraseConfirmationWindow.setOverallThemeStyleSheet(overallThemeStyleSheetString, usingDarkTheme);
                    if (iLanguage == ENGLISH)
                    {
                        eraseConfirmationWindow.setWindowTitle(" Information");
                        eraseConfirmationWindow.setInfoText("Please enter a valid amount.");
                    }
                    else if (iLanguage == GERMAN)
                    {
                        eraseConfirmationWindow.setWindowTitle(" Information");
                        eraseConfirmationWindow.setInfoText("Bitte geben Sie einen gültigen Betrag ein.");
                    }
                    else if (iLanguage == SPANISH)
                    {
                        eraseConfirmationWindow.setWindowTitle(" Información");
                        eraseConfirmationWindow.setInfoText("Por favor introduzca un monto válido.");
                    }
                    eraseConfirmationWindow.exec();
                    this->focusPreviousChild();
                    this->focusPreviousChild();
                    this->focusPreviousChild();
                    this->ui->textPrice->selectAll();   //Select all text in Price
                }
                else if (!transactionNameOK && !transactionAmountOK){
                    eraseConfirmation_dialog eraseConfirmationWindow;
                    eraseConfirmationWindow.setModal(true);
                    eraseConfirmationWindow.setOverallThemeStyleSheet(overallThemeStyleSheetString, usingDarkTheme);
                    if (iLanguage == ENGLISH)
                    {
                        eraseConfirmationWindow.setWindowTitle(" Information");
                        eraseConfirmationWindow.setInfoText("Every transaction needs a name.");
                    }
                    else if (iLanguage == GERMAN)
                    {
                        eraseConfirmationWindow.setWindowTitle(" Information");
                        eraseConfirmationWindow.setInfoText("Ein Name wird benötigt.");
                    }
                    else if (iLanguage == SPANISH)
                    {
                        eraseConfirmationWindow.setWindowTitle(" Información");
                        eraseConfirmationWindow.setInfoText("Cada transacción necesita un nombre.");
                    }
                    eraseConfirmationWindow.exec();
                    this->focusNextChild();
                    this->focusNextChild();
                    this->focusNextChild();
                }
                return true;
            }
            else if (key->key()==Qt::Key_Tab) {
                this->focusNextChild();
                std::cout<<"KEY TAB PRESSED FROM MONTH"<<'\n';
                return true;
            }
          }
        else if (qobject_cast<QComboBox*>(obj) == ui->comboBoxRepeat)
          {
            QKeyEvent* key = static_cast<QKeyEvent*>(event);
            if ( (key->key()==Qt::Key_Enter) || (key->key()==Qt::Key_Return) ) {
                this->checkAndSetTransaction();
                if(transactionNameOK && transactionAmountOK){ //If a name and amount have been given, close.
                    this->close();
                } else if (!transactionNameOK && transactionAmountOK){
                    eraseConfirmation_dialog eraseConfirmationWindow;
                    eraseConfirmationWindow.setModal(true);
                    eraseConfirmationWindow.setOverallThemeStyleSheet(overallThemeStyleSheetString, usingDarkTheme);
                    if (iLanguage == ENGLISH)
                    {
                        eraseConfirmationWindow.setWindowTitle(" Information");
                        eraseConfirmationWindow.setInfoText("Every transaction needs a name.");
                    }
                    else if (iLanguage == GERMAN)
                    {
                        eraseConfirmationWindow.setWindowTitle(" Information");
                        eraseConfirmationWindow.setInfoText("Ein Name wird benötigt.");
                    }
                    else if (iLanguage == SPANISH)
                    {
                        eraseConfirmationWindow.setWindowTitle(" Información");
                        eraseConfirmationWindow.setInfoText("Cada transacción necesita un nombre.");
                    }
                    eraseConfirmationWindow.exec();
                    this->focusNextChild();
                    this->focusNextChild();
                }
                else if (transactionNameOK && !transactionAmountOK){
                    eraseConfirmation_dialog eraseConfirmationWindow;
                    eraseConfirmationWindow.setModal(true);
                    eraseConfirmationWindow.setOverallThemeStyleSheet(overallThemeStyleSheetString, usingDarkTheme);
                    if (iLanguage == ENGLISH)
                    {
                        eraseConfirmationWindow.setWindowTitle(" Information");
                        eraseConfirmationWindow.setInfoText("Please enter a valid amount.");
                    }
                    else if (iLanguage == GERMAN)
                    {
                        eraseConfirmationWindow.setWindowTitle(" Information");
                        eraseConfirmationWindow.setInfoText("Bitte geben Sie einen gültigen Betrag ein.");
                    }
                    else if (iLanguage == SPANISH)
                    {
                        eraseConfirmationWindow.setWindowTitle(" Información");
                        eraseConfirmationWindow.setInfoText("Por favor introduzca un monto válido.");
                    }
                    eraseConfirmationWindow.exec();
                    this->focusNextChild();
                    this->focusNextChild();
                    this->focusNextChild();
                    this->ui->textPrice->selectAll();   //Select all text in Price
                }
                else if (!transactionNameOK && !transactionAmountOK){
                    eraseConfirmation_dialog eraseConfirmationWindow;
                    eraseConfirmationWindow.setModal(true);
                    eraseConfirmationWindow.setOverallThemeStyleSheet(overallThemeStyleSheetString, usingDarkTheme);
                    if (iLanguage == ENGLISH)
                    {
                        eraseConfirmationWindow.setWindowTitle(" Information");
                        eraseConfirmationWindow.setInfoText("Every transaction needs a name.");
                    }
                    else if (iLanguage == GERMAN)
                    {
                        eraseConfirmationWindow.setWindowTitle(" Information");
                        eraseConfirmationWindow.setInfoText("Ein Name wird benötigt.");
                    }
                    else if (iLanguage == SPANISH)
                    {
                        eraseConfirmationWindow.setWindowTitle(" Información");
                        eraseConfirmationWindow.setInfoText("Cada transacción necesita un nombre.");
                    }
                    eraseConfirmationWindow.exec();
                    this->focusNextChild();
                    this->focusNextChild();
                }
                return true;
            }
            else if (key->key()==Qt::Key_Tab) {
                this->focusNextChild();
                std::cout<<"KEY TAB PRESSED FROM COMBO BOX REPEAT"<<'\n';
                return true;
            }
          }
        else if (qobject_cast<QPushButton*>(obj) == ui->pushButtonOk)
          {
            QKeyEvent* key = static_cast<QKeyEvent*>(event);
            if ( (key->key()==Qt::Key_Enter) || (key->key()==Qt::Key_Return) ) {
                this->checkAndSetTransaction();
                if(transactionNameOK && transactionAmountOK){ //If a name and amount have been given, close.
                    this->close();
                } else if (!transactionNameOK && transactionAmountOK){
                    eraseConfirmation_dialog eraseConfirmationWindow;
                    eraseConfirmationWindow.setModal(true);
                    eraseConfirmationWindow.setOverallThemeStyleSheet(overallThemeStyleSheetString, usingDarkTheme);
                    if (iLanguage == ENGLISH)
                    {
                        eraseConfirmationWindow.setWindowTitle(" Information");
                        eraseConfirmationWindow.setInfoText("Every transaction needs a name.");
                    }
                    else if (iLanguage == GERMAN)
                    {
                        eraseConfirmationWindow.setWindowTitle(" Information");
                        eraseConfirmationWindow.setInfoText("Ein Name wird benötigt.");
                    }
                    else if (iLanguage == SPANISH)
                    {
                        eraseConfirmationWindow.setWindowTitle(" Información");
                        eraseConfirmationWindow.setInfoText("Cada transacción necesita un nombre.");
                    }
                    eraseConfirmationWindow.exec();
                    this->focusNextChild();
                }
                else if (transactionNameOK && !transactionAmountOK){
                    eraseConfirmation_dialog eraseConfirmationWindow;
                    eraseConfirmationWindow.setModal(true);
                    eraseConfirmationWindow.setOverallThemeStyleSheet(overallThemeStyleSheetString, usingDarkTheme);
                    if (iLanguage == ENGLISH)
                    {
                        eraseConfirmationWindow.setWindowTitle(" Information");
                        eraseConfirmationWindow.setInfoText("Please enter a valid amount.");
                    }
                    else if (iLanguage == GERMAN)
                    {
                        eraseConfirmationWindow.setWindowTitle(" Information");
                        eraseConfirmationWindow.setInfoText("Bitte geben Sie einen gültigen Betrag ein.");
                    }
                    else if (iLanguage == SPANISH)
                    {
                        eraseConfirmationWindow.setWindowTitle(" Información");
                        eraseConfirmationWindow.setInfoText("Por favor introduzca un monto válido.");
                    }
                    eraseConfirmationWindow.exec();
                    this->focusNextChild();
                    this->focusNextChild();
                    this->ui->textPrice->selectAll();   //Select all text in Price
                }
                else if (!transactionNameOK && !transactionAmountOK){
                    eraseConfirmation_dialog eraseConfirmationWindow;
                    eraseConfirmationWindow.setModal(true);
                    eraseConfirmationWindow.setOverallThemeStyleSheet(overallThemeStyleSheetString, usingDarkTheme);
                    if (iLanguage == ENGLISH)
                    {
                        eraseConfirmationWindow.setWindowTitle(" Information");
                        eraseConfirmationWindow.setInfoText("Every transaction needs a name.");
                    }
                    else if (iLanguage == GERMAN)
                    {
                        eraseConfirmationWindow.setWindowTitle(" Information");
                        eraseConfirmationWindow.setInfoText("Ein Name wird benötigt.");
                    }
                    else if (iLanguage == SPANISH)
                    {
                        eraseConfirmationWindow.setWindowTitle(" Información");
                        eraseConfirmationWindow.setInfoText("Cada transacción necesita un nombre.");
                    }
                    eraseConfirmationWindow.exec();
                    this->focusNextChild();
                }
                return true;
            }
            else if (key->key()==Qt::Key_Tab) {
                this->focusNextChild();
                //std::cout<<"KEY TAB PRESSED FROM BUTTON OK"<<'\n';
                return true;
            }
          }
    }
    else if (event->type() == QEvent::MouseButtonPress)
    {
        if (qobject_cast<QWidget*>(obj) == ui->pushButtonOk) {
            this->ui->pushButtonOk->setColorForMouseButtonPressEvent();
        } else if (qobject_cast<QWidget*>(obj) == ui->comboBoxDay) {
            this->ui->comboBoxDay->setColorForMouseButtonPressEvent();
        } else if (qobject_cast<QWidget*>(obj) == ui->comboBoxMonth) {
            this->ui->comboBoxMonth->setColorForMouseButtonPressEvent();
        } else if (qobject_cast<QWidget*>(obj) == ui->comboBoxCategory) {
            this->ui->comboBoxCategory->setColorForMouseButtonPressEvent();
        } else if (qobject_cast<QWidget*>(obj) == ui->comboBoxRepeat) {
            this->ui->comboBoxRepeat->setColorForMouseButtonPressEvent();
        } else if (qobject_cast<QWidget*>(obj) == ui->textName) {
            this->ui->textName->setColorForMouseButtonPressEvent();
        } else if (qobject_cast<QWidget*>(obj) == ui->textPrice) {
            this->ui->textPrice->setColorForMouseButtonPressEvent();
        }
    }
    else if (event->type() == QEvent::MouseButtonRelease)
    {
        if (qobject_cast<QWidget*>(obj) == ui->pushButtonOk) {
            this->ui->pushButtonOk->setColorForEnterEvent();
        } else if (qobject_cast<QWidget*>(obj) == ui->comboBoxDay) {
            this->ui->comboBoxDay->setColorForEnterEvent();
        } else if (qobject_cast<QWidget*>(obj) == ui->comboBoxMonth) {
            this->ui->comboBoxMonth->setColorForEnterEvent();
        } else if (qobject_cast<QWidget*>(obj) == ui->comboBoxCategory) {
            this->ui->comboBoxCategory->setColorForEnterEvent();
        } else if (qobject_cast<QWidget*>(obj) == ui->comboBoxRepeat) {
            this->ui->comboBoxRepeat->setColorForEnterEvent();
        } else if (qobject_cast<QWidget*>(obj) == ui->textName) {
            this->ui->textName->setColorForEnterEvent();
        } else if (qobject_cast<QWidget*>(obj) == ui->textPrice) {
            this->ui->textPrice->setColorForEnterEvent();
        }
    }
    else if (event->type() == QEvent::Enter)
     {
         if (qobject_cast<QPushButton*>(obj) == ui->pushButtonOk)  {
             this->ui->pushButtonOk->setColorForEnterEvent();
         } else if (qobject_cast<QWidget*>(obj) == ui->comboBoxDay) {
             this->ui->comboBoxDay->setColorForEnterEvent();
         } else if (qobject_cast<QWidget*>(obj) == ui->comboBoxMonth) {
             this->ui->comboBoxMonth->setColorForEnterEvent();
         } else if (qobject_cast<QWidget*>(obj) == ui->comboBoxCategory) {
             this->ui->comboBoxCategory->setColorForEnterEvent();
         } else if (qobject_cast<QWidget*>(obj) == ui->comboBoxRepeat) {
             this->ui->comboBoxRepeat->setColorForEnterEvent();
         } else if (qobject_cast<QWidget*>(obj) == ui->textName) {
             this->ui->textName->setColorForEnterEvent();
         } else if (qobject_cast<QWidget*>(obj) == ui->textPrice) {
             this->ui->textPrice->setColorForEnterEvent();
         }
    }
    else if (event->type() == QEvent::Leave)
     {
         if (qobject_cast<QPushButton*>(obj) == ui->pushButtonOk)  {
             this->ui->pushButtonOk->setColorForLeaveEvent();
         } else if (qobject_cast<QWidget*>(obj) == ui->comboBoxDay) {
             this->ui->comboBoxDay->setColorForLeaveEvent();
         } else if (qobject_cast<QWidget*>(obj) == ui->comboBoxMonth) {
             this->ui->comboBoxMonth->setColorForLeaveEvent();
         } else if (qobject_cast<QWidget*>(obj) == ui->comboBoxCategory) {
             this->ui->comboBoxCategory->setColorForLeaveEvent();
         } else if (qobject_cast<QWidget*>(obj) == ui->comboBoxRepeat) {
             this->ui->comboBoxRepeat->setColorForLeaveEvent();
         } else if (qobject_cast<QWidget*>(obj) == ui->textName) {
             this->ui->textName->setColorForLeaveEvent();
         } else if (qobject_cast<QWidget*>(obj) == ui->textPrice) {
             this->ui->textPrice->setColorForLeaveEvent();
         }
    }
    else if (event->type() == QEvent::FocusIn)
    {
        if (qobject_cast<QWidget*>(obj) == ui->pushButtonOk) {
            this->ui->pushButtonOk->setColorForEnterEvent();
        } else if (qobject_cast<QWidget*>(obj) == ui->comboBoxDay) {
            this->ui->comboBoxDay->setColorForEnterEvent();
        } else if (qobject_cast<QWidget*>(obj) == ui->comboBoxMonth) {
            this->ui->comboBoxMonth->setColorForEnterEvent();
        } else if (qobject_cast<QWidget*>(obj) == ui->comboBoxCategory) {
            this->ui->comboBoxCategory->setColorForEnterEvent();
        } else if (qobject_cast<QWidget*>(obj) == ui->comboBoxRepeat) {
            this->ui->comboBoxRepeat->setColorForEnterEvent();
        } else if (qobject_cast<QWidget*>(obj) == ui->textName) {
            this->ui->textName->setColorForEnterEvent();
        } else if (qobject_cast<QWidget*>(obj) == ui->textPrice) {
            this->ui->textPrice->setColorForEnterEvent();
        }
    }
    else if (event->type() == QEvent::FocusOut)
    {
        if (qobject_cast<QPushButton*>(obj) == ui->pushButtonOk)  {
            this->ui->pushButtonOk->setColorForLeaveEvent();
        } else if (qobject_cast<QWidget*>(obj) == ui->comboBoxDay) {
            this->ui->comboBoxDay->setColorForLeaveEvent();
        } else if (qobject_cast<QWidget*>(obj) == ui->comboBoxMonth) {
            this->ui->comboBoxMonth->setColorForLeaveEvent();
        } else if (qobject_cast<QWidget*>(obj) == ui->comboBoxCategory) {
            this->ui->comboBoxCategory->setColorForLeaveEvent();
        } else if (qobject_cast<QWidget*>(obj) == ui->comboBoxRepeat) {
            this->ui->comboBoxRepeat->setColorForLeaveEvent();
        } else if (qobject_cast<QWidget*>(obj) == ui->textName) {
            this->ui->textName->setColorForLeaveEvent();
        } else if (qobject_cast<QWidget*>(obj) == ui->textPrice) {
            this->ui->textPrice->setColorForLeaveEvent();
        }
    }
    return false;
}

void TransactionDialog::setCategoryList(std::vector<std::string> categoryList)
{
    for (std::vector<std::string>::iterator catIt = categoryList.begin(); catIt != categoryList.end(); ++catIt)
    {
        ui->comboBoxCategory->addItem(QString::fromStdString(*catIt));
    }
}

void TransactionDialog::displayItemInfo(std::string Nam, double Pri, int Cat, int Mon, int Day, RepetitionOption Repeat, int year)
{
    this->ui->comboBoxDay->clear();
    Year = year;
    int Month = Mon;
    int NumberOfDaysInMonth = 0;

    if( Month == 1)
    {
        if((Year%400==0) || (Year%4==0 && Year%100!=0))
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

    if (iLanguage == GERMAN) {
        ui->textPrice->setText(QString::fromStdString(getAmountAsStringInGermanFormat(Pri)));
    } else {
        ui->textPrice->setText(QString::number(Pri, 0, 2));
    }

    ui->textName->setText(QString::fromStdString(Nam));
    ui->comboBoxCategory->setCurrentIndex(Cat);
    ui->comboBoxMonth->setCurrentIndex(Mon);
    ui->comboBoxDay->setCurrentIndex(Day);
    ui->comboBoxRepeat->setCurrentIndex(static_cast<int>(Repeat));
}

void TransactionDialog::on_pushButtonOk_clicked()
{
    this->checkAndSetTransaction();
    if (transactionNameOK && transactionAmountOK){
        this->close();
    } else if (!transactionNameOK) {
        //Show message: "Please give a name for current transaction"
        eraseConfirmation_dialog eraseConfirmationWindow;
        eraseConfirmationWindow.setModal(true);
        eraseConfirmationWindow.setOverallThemeStyleSheet(overallThemeStyleSheetString, usingDarkTheme);
        if (iLanguage == ENGLISH)
        {
            eraseConfirmationWindow.setWindowTitle(" Information");
            eraseConfirmationWindow.setInfoText("Every transaction needs a name.");
        }
        else if (iLanguage == GERMAN)
        {
            eraseConfirmationWindow.setWindowTitle(" Information");
            eraseConfirmationWindow.setInfoText("Ein Name wird benötigt.");
        }
        else if (iLanguage == SPANISH)
        {
            eraseConfirmationWindow.setWindowTitle(" Información");
            eraseConfirmationWindow.setInfoText("Cada transacción necesita un nombre.");
        }
        eraseConfirmationWindow.exec();
        this->focusNextChild();
    } else if (!transactionAmountOK) {
        //Show message: "Please give a valid amount"
        eraseConfirmation_dialog eraseConfirmationWindow;
        eraseConfirmationWindow.setModal(true);
        eraseConfirmationWindow.setOverallThemeStyleSheet(overallThemeStyleSheetString, usingDarkTheme);
        if (iLanguage == ENGLISH)
        {
            eraseConfirmationWindow.setWindowTitle(" Information");
            eraseConfirmationWindow.setInfoText("Please enter a valid amount.");
        }
        else if (iLanguage == GERMAN)
        {
            eraseConfirmationWindow.setWindowTitle(" Information");
            eraseConfirmationWindow.setInfoText("Bitte geben Sie einen gültigen Betrag ein.");
        }
        else if (iLanguage == SPANISH)
        {
            eraseConfirmationWindow.setWindowTitle(" Información");
            eraseConfirmationWindow.setInfoText("Por favor introduzca un monto válido.");
        }
        eraseConfirmationWindow.exec();
        this->focusNextChild();
        this->focusNextChild();
    }
}

void TransactionDialog::provideArticleInfo(std::string & Nam, double &Pri, int &Cat, int &Mon, int &Day, RepetitionOption &Repeat)
{
    Nam     = Name_.toStdString();
    Pri     = Price_.toDouble();
    Mon     = Month_;
    Day     = Day_+1;
    Cat     = Category_;
    Repeat  = Repeat_;
}

void TransactionDialog::setNumberOfDaysInSelectedMonth(int selectedMonth)
{
    int selectedDay = this->ui->comboBoxDay->currentIndex();
    this->ui->comboBoxDay->clear();

    int NumberOfDaysInMonth = 0;

    if( selectedMonth == 1)
    {
        if((Year%400==0) || (Year%4==0 && Year%100!=0))
            NumberOfDaysInMonth = 29;
        else
            NumberOfDaysInMonth = 28;
    }
    else if (selectedMonth == 0 || selectedMonth == 2 || selectedMonth == 4 || selectedMonth == 6 || selectedMonth == 7 || selectedMonth == 9 || selectedMonth==11)	{
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
        selectedDay = NumberOfDaysInMonth-1; //Because Index starts from zero and NumberOfDaysInMonth doesn't.
    }
    this->ui->comboBoxDay->setCurrentIndex(selectedDay); //Index starts from zero
}

void TransactionDialog::on_comboBoxMonth_currentIndexChanged(int index)
{
    this->setNumberOfDaysInSelectedMonth(index);
}
