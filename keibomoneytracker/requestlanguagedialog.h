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

#ifndef REQUESTLANGUAGEDIALOG_H
#define REQUESTLANGUAGEDIALOG_H

#include <QDialog>
#include "keibomoneytrackerinclude.h"

namespace Ui {
class requestLanguageDialog;
}

class requestLanguageDialog : public QDialog
{
    Q_OBJECT

public:
    explicit requestLanguageDialog(QWidget *parent = nullptr);
    ~requestLanguageDialog();

    Language selectedLanguage = ENGLISH;
    bool showHowToUseGuide = false;
    bool askUserAboutGuide = true;

private slots:
    void on_pushButtonOk_clicked();
    void on_comboBoxLanguage_currentIndexChanged(int index);
    void on_pushButtonYes_clicked();

private:
    Ui::requestLanguageDialog *ui;
    bool allowTitleUpdate = false;
    bool buttonOkPressed = false;
};

#endif // REQUESTLANGUAGEDIALOG_H
