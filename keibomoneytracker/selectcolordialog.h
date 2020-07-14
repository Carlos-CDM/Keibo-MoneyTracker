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

#ifndef SELECTCOLORDIALOG_H
#define SELECTCOLORDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include "keibomoneytrackerinclude.h"

namespace Ui {
class SelectColorDialog;
}

/////////////////////////////////////////////////////////////////////////////
/// \brief The SelectColorDialog class
//
class SelectColorDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SelectColorDialog(QWidget *parent = 0);
    ~SelectColorDialog();

    bool newColorWasSelected = false;
    int colorId = 0;

    bool eventFilter(QObject *obj, QEvent *event);
    void enableTransparency();

    void setOverallThemeStyleSheet(QString styleSheetString);
    void setLanguage(const Language & currentLanguage);

private slots:
    void on_Transparent_clicked();

private:
    Ui::SelectColorDialog *ui;
};

#endif // SELECTCOLORDIALOG_H
