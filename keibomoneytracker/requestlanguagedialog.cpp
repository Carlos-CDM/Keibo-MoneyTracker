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

#include "requestlanguagedialog.h"
#include "ui_requestlanguagedialog.h"
#include "eraseconfirmation_dialog.h"

requestLanguageDialog::requestLanguageDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::requestLanguageDialog)
{
    ui->setupUi(this);
    ui->comboBoxLanguage->addItem("English");
    ui->comboBoxLanguage->addItem("Deutsch");
    ui->comboBoxLanguage->addItem("Español");

    this->setWindowTitle(" Language");
    this->ui->pushButtonYes->setEnabled(false);
    this->ui->pushButtonYes->setVisible(false);
    allowTitleUpdate = true;
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
}

requestLanguageDialog::~requestLanguageDialog()
{
    delete ui;
}

void requestLanguageDialog::on_pushButtonOk_clicked()
{
    if (!buttonOkPressed )
    {
        if (ui->comboBoxLanguage->currentIndex() == 1){
            selectedLanguage = GERMAN;
        } else if (ui->comboBoxLanguage->currentIndex() == 2) {
            selectedLanguage = SPANISH;
        }

        if (askUserAboutGuide)
        {
            if (selectedLanguage == ENGLISH){
                this->setFixedWidth(this->width()+20);
                this->ui->pushButtonOk->setText("No");
                this->ui->pushButtonYes->setText("Yes");
                this->setWindowTitle(" Would you like to see the user guide?");
            } else if (selectedLanguage == GERMAN) {
                this->setFixedWidth(this->width()+100);
                this->ui->pushButtonOk->setGeometry(ui->pushButtonOk->x()+60, ui->pushButtonOk->y(), ui->pushButtonOk->width(), ui->pushButtonOk->height());
                this->ui->pushButtonOk->setText("Nein");
                this->ui->pushButtonYes->setText("Ja");
                this->setWindowTitle(" Möchten Sie die Benutzungserklärung ansehen?");
            } else if (selectedLanguage == SPANISH) {
                this->ui->pushButtonOk->setText("No");
                this->ui->pushButtonYes->setText("Si");
                this->setWindowTitle(" Desea ver la guia de uso?");
            }

            this->ui->comboBoxLanguage->setEnabled(false);
            this->ui->comboBoxLanguage->setVisible(false);
            this->ui->pushButtonYes->setEnabled(true);
            this->ui->pushButtonYes->setVisible(true);
        }
    }
    else {
        this->close();
    }

    buttonOkPressed = true;
}

void requestLanguageDialog::on_comboBoxLanguage_currentIndexChanged(int index)
{
    if (allowTitleUpdate)
    {
        if      (index == 0) {
            this->setWindowTitle(" Language");
            this->ui->pushButtonOk->setText("Continue");
        }
        else if (index == 1) {
            this->setWindowTitle(" Sprache");
            this->ui->pushButtonOk->setText("Weiter");
        }
        else if (index == 2) {
            this->setWindowTitle(" Idioma");
            this->ui->pushButtonOk->setText("Continuar");
        }
    }
}

void requestLanguageDialog::on_pushButtonYes_clicked()
{
    showHowToUseGuide = true;
    this->close();
}
