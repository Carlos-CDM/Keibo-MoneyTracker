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

#include "addgroupdialog.h"
#include "ui_addgroupdialog.h"
#include <QKeyEvent>

Addgroupdialog::Addgroupdialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Addgroupdialog)
{
    ui->setupUi(this);

    this->ui->textEdit->installEventFilter(this);
    this->ui->acceptButton->installEventFilter(this);
    this->ui->cancelButton->installEventFilter(this);

    this->ui->textEdit->setTabChangesFocus(true);
    this->ui->cancelButton->setAutoDefault(false);
    this->ui->acceptButton->setAutoDefault(false);
}

Addgroupdialog::~Addgroupdialog()
{
    delete ui;
}

void Addgroupdialog::setLanguage(const Language &iLanguage)
{
    if (iLanguage == SPANISH){
        this->ui->acceptButton->setText("Aceptar");
        this->ui->cancelButton->setText("Cancelar");
    }
    else if (iLanguage == GERMAN) {
        this->ui->acceptButton->setText("Akzeptieren");
        this->ui->cancelButton->setText("Abbrechen");
    }
    else {
        this->ui->acceptButton->setText("Accept");
        this->ui->cancelButton->setText("Cancel");
    }
}

void Addgroupdialog::setOverallThemeStyleSheet(QString styleSheetString, bool usingDarkTheme)
{
    this->setStyleSheet(styleSheetString);
    this->ui->acceptButton->updateColorTheme(usingDarkTheme);
    this->ui->cancelButton->updateColorTheme(usingDarkTheme);
    this->ui->textEdit->updateColorTheme(usingDarkTheme);
}

void Addgroupdialog::provideGroupName(std::string &groupName) ///Provide name to external variable by reference
{                                                             ///not by return value
   groupName = tempGroupName.toStdString();
}

void Addgroupdialog::setGroupName(std::string &groupName)
{
    ui->textEdit->setText(QString::fromStdString(groupName));
    tempGroupName =  QString::fromStdString(groupName);
}

void Addgroupdialog::on_acceptButton_clicked()
{
    if (tempGroupName != ui->textEdit->toPlainText())
    {            ////If the current text on textfield is different to already existing or intended to edit group
        tempGroupName = ui->textEdit->toPlainText();  /// then set tempGroupName as new entered name of the group
    }
    this->close();
}

void Addgroupdialog::on_cancelButton_clicked()
{
    this->close();
}

bool Addgroupdialog::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::KeyPress)
    {
        if (qobject_cast<QTextEdit*>(obj) == ui->textEdit)
        {
            QKeyEvent* key = static_cast<QKeyEvent*>(event);
            if (key->key() == Qt::Key_Enter || (key->key()==Qt::Key_Return))
            {
                if (tempGroupName != ui->textEdit->toPlainText())
                {
                    tempGroupName = ui->textEdit->toPlainText();
                }
                this->close();
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
                if (tempGroupName != ui->textEdit->toPlainText())
                {
                    tempGroupName = ui->textEdit->toPlainText();
                }
                this->close();
                return true;
            }
            else if (key->key() == Qt::Key_Tab)
            {
                this->focusNextChild();
                return true;
            }
        }
        else if (qobject_cast<QPushButton*>(obj) == ui->cancelButton)
        {
            QKeyEvent* key = static_cast<QKeyEvent*>(event);
            if (key->key() == Qt::Key_Enter || (key->key()==Qt::Key_Return))
            {
                this->close();
                return true;
            }
            else if (key->key() == Qt::Key_Tab)
            {
                this->focusNextChild();
                return true;
            }
        }
    }
    else if (event->type() == QEvent::MouseButtonPress)
    {
        if (qobject_cast<QWidget*>(obj) == ui->acceptButton) {
            this->ui->acceptButton->setColorForMouseButtonPressEvent();
        } else if (qobject_cast<QWidget*>(obj) == ui->cancelButton) {
            this->ui->cancelButton->setColorForMouseButtonPressEvent();
        } else if (qobject_cast<QWidget*>(obj) == ui->textEdit) {
            this->ui->textEdit->setColorForMouseButtonPressEvent();
        }
    }
    else if (event->type() == QEvent::MouseButtonRelease)
    {
        if (qobject_cast<QWidget*>(obj) == ui->acceptButton) {
            this->ui->acceptButton->setColorForEnterEvent();
        } else if (qobject_cast<QWidget*>(obj) == ui->cancelButton) {
            this->ui->cancelButton->setColorForEnterEvent();
        } else if (qobject_cast<QWidget*>(obj) == ui->textEdit) {
            this->ui->textEdit->setColorForEnterEvent();
        }
    }
    else if (event->type() == QEvent::Enter)
     {
         if (qobject_cast<QPushButton*>(obj) == ui->acceptButton) {
             this->ui->acceptButton->setColorForEnterEvent();
         } else if (qobject_cast<QWidget*>(obj) == ui->cancelButton) {
             this->ui->cancelButton->setColorForEnterEvent();
         } else if (qobject_cast<QWidget*>(obj) == ui->textEdit) {
             this->ui->textEdit->setColorForEnterEvent();
         }
    }
    else if (event->type() == QEvent::Leave)
     {
         if (qobject_cast<QPushButton*>(obj) == ui->acceptButton) {
             this->ui->acceptButton->setColorForLeaveEvent();
         } else if (qobject_cast<QWidget*>(obj) == ui->cancelButton) {
             this->ui->cancelButton->setColorForLeaveEvent();
         } else if (qobject_cast<QWidget*>(obj) == ui->textEdit) {
             this->ui->textEdit->setColorForLeaveEvent();
         }
    }
    return false;
}
