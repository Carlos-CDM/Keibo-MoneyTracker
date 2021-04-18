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

#include "selectcolordialog.h"
#include "ui_selectcolordialog.h"
#include <iostream>
#include <keibomoneytrackerinclude.h>

SelectColorDialog::SelectColorDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SelectColorDialog)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_Hover);
    this->setMouseTracking(true);

    this->installEventFilter(this);

    ui->Color_0->installEventFilter(this);
    ui->Color_1->installEventFilter(this);
    ui->Color_2->installEventFilter(this);
    ui->Color_3->installEventFilter(this);
    ui->Color_4->installEventFilter(this);
    ui->Color_5->installEventFilter(this);
    ui->Color_6->installEventFilter(this);
    ui->Color_7->installEventFilter(this);
    ui->Color_8->installEventFilter(this);
    ui->Color_9->installEventFilter(this);
    ui->Color_10->installEventFilter(this);
    ui->Color_11->installEventFilter(this);
    ui->Color_12->installEventFilter(this);
    ui->Color_13->installEventFilter(this);
    ui->Color_14->installEventFilter(this);
    ui->Color_15->installEventFilter(this);
    ui->Color_16->installEventFilter(this);
    ui->Color_17->installEventFilter(this);
    ui->Color_18->installEventFilter(this);
    ui->Color_19->installEventFilter(this);
    ui->Color_20->installEventFilter(this);
    ui->Color_21->installEventFilter(this);
    ui->Color_22->installEventFilter(this);
    ui->Color_23->installEventFilter(this);
    ui->Color_24->installEventFilter(this);
    ui->Color_25->installEventFilter(this);
    ui->Color_26->installEventFilter(this);
    ui->Color_27->installEventFilter(this);
    ui->Color_28->installEventFilter(this);
    ui->Color_29->installEventFilter(this);
    ui->Color_30->installEventFilter(this);
    ui->Color_31->installEventFilter(this);
    ui->Color_32->installEventFilter(this);
    ui->Color_33->installEventFilter(this);
    ui->Color_34->installEventFilter(this);
    ui->Color_35->installEventFilter(this);
    ui->Transparent->setVisible(false);
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
}

SelectColorDialog::~SelectColorDialog()
{
    delete ui;
}

void SelectColorDialog::setLanguage(const Language &currentLanguage)
{
   if (currentLanguage == ENGLISH)
   {
       this->ui->Transparent->setText("No color");
       this->setWindowTitle(" Pick a color");
   }
   else if (currentLanguage == GERMAN)
   {
       this->ui->Transparent->setText("Keine Farbe");
       this->setWindowTitle(" Wählen Sie eine Farbe");
   }
   else if (currentLanguage == SPANISH)
   {
       this->ui->Transparent->setText("Sin color");
       this->setWindowTitle(" Seleccione un color");
   }
}

void SelectColorDialog::setOverallThemeStyleSheet(QString styleSheetString)
{
    this->setStyleSheet(styleSheetString);
}

void SelectColorDialog::enableTransparency()
{
    ui->Transparent->setVisible(true);
    ui->Transparent->setEnabled(true);
    this->setFixedHeight((this->height()+25));
}

bool SelectColorDialog::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::MouseButtonPress)
    {
      if (qobject_cast<QLabel*>(obj) == ui->Color_0)
        {
            colorId = 0;
            newColorWasSelected = true;
        }
      else if (qobject_cast<QLabel*>(obj) == ui->Color_1)
        {
            colorId = 1;
            newColorWasSelected = true;
        }
      else if (qobject_cast<QLabel*>(obj) == ui->Color_2)
        {
            colorId = 2;
            newColorWasSelected = true;
        }
      else if (qobject_cast<QLabel*>(obj) == ui->Color_3)
        {
            colorId = 3;
            newColorWasSelected = true;
        }
      else if (qobject_cast<QLabel*>(obj) == ui->Color_4)
        {
            colorId = 4;
            newColorWasSelected = true;
        }
      else if (qobject_cast<QLabel*>(obj) == ui->Color_5)
        {
            colorId = 5;
            newColorWasSelected = true;
        }
      else if (qobject_cast<QLabel*>(obj) == ui->Color_6)
        {
            colorId = 6;
            newColorWasSelected = true;
        }
      else if (qobject_cast<QLabel*>(obj) == ui->Color_7)
        {
            colorId = 7;
            newColorWasSelected = true;
        }
      else if (qobject_cast<QLabel*>(obj) == ui->Color_8)
        {
            colorId = 8;
            newColorWasSelected = true;
        }
      else if (qobject_cast<QLabel*>(obj) == ui->Color_9)
        {
            colorId = 9;
            newColorWasSelected = true;
        }
      else if (qobject_cast<QLabel*>(obj) == ui->Color_10)
        {
            colorId = 10;
            newColorWasSelected = true;
        }
      else if (qobject_cast<QLabel*>(obj) == ui->Color_11)
        {
            colorId = 11;
            newColorWasSelected = true;
        }
      else if (qobject_cast<QLabel*>(obj) == ui->Color_12)
        {
            colorId = 12;
            newColorWasSelected = true;
        }
      else if (qobject_cast<QLabel*>(obj) == ui->Color_13)
        {
            colorId = 13;
            newColorWasSelected = true;
        }
      else if (qobject_cast<QLabel*>(obj) == ui->Color_14)
        {
            colorId = 14;
            newColorWasSelected = true;
        }
      else if (qobject_cast<QLabel*>(obj) == ui->Color_15)
        {
            colorId = 15;
            newColorWasSelected = true;
        }
      else if (qobject_cast<QLabel*>(obj) == ui->Color_16)
        {
            colorId = 16;
            newColorWasSelected = true;
        }
      else if (qobject_cast<QLabel*>(obj) == ui->Color_17)
        {
            colorId = 17;
            newColorWasSelected = true;
        }
      else if (qobject_cast<QLabel*>(obj) == ui->Color_18)
        {
            colorId = 18;
            newColorWasSelected = true;
        }
      else if (qobject_cast<QLabel*>(obj) == ui->Color_19)
        {
            colorId = 19;
            newColorWasSelected = true;
        }
      else if (qobject_cast<QLabel*>(obj) == ui->Color_20)
        {
            colorId = 20;
            newColorWasSelected = true;
        }
      else if (qobject_cast<QLabel*>(obj) == ui->Color_21)
        {
            colorId = 21;
            newColorWasSelected = true;
        }
      else if (qobject_cast<QLabel*>(obj) == ui->Color_22)
        {
            colorId = 22;
            newColorWasSelected = true;
        }
      else if (qobject_cast<QLabel*>(obj) == ui->Color_23)
        {
            colorId = 23;
            newColorWasSelected = true;
        }
      else if (qobject_cast<QLabel*>(obj) == ui->Color_24)
        {
            colorId = 24;
            newColorWasSelected = true;
        }
      else if (qobject_cast<QLabel*>(obj) == ui->Color_25)
        {
            colorId = 25;
            newColorWasSelected = true;
        }
      else if (qobject_cast<QLabel*>(obj) == ui->Color_26)
        {
            colorId = 26;
            newColorWasSelected = true;
        }
      else if (qobject_cast<QLabel*>(obj) == ui->Color_27)
        {
            colorId = 27;
            newColorWasSelected = true;
        }
      else if (qobject_cast<QLabel*>(obj) == ui->Color_28)
        {
            colorId = 28;
            newColorWasSelected = true;
        }
      else if (qobject_cast<QLabel*>(obj) == ui->Color_29)
        {
            colorId = 29;
            newColorWasSelected = true;
        }
      else if (qobject_cast<QLabel*>(obj) == ui->Color_30)
        {
            colorId = 30;
            newColorWasSelected = true;
        }
      else if (qobject_cast<QLabel*>(obj) == ui->Color_31)
        {
            colorId = 31;
            newColorWasSelected = true;
        }
      else if (qobject_cast<QLabel*>(obj) == ui->Color_32)
        {
            colorId = 32;
            newColorWasSelected = true;
        }
      else if (qobject_cast<QLabel*>(obj) == ui->Color_33)
        {
            colorId = 33;
            newColorWasSelected = true;
        }
      else if (qobject_cast<QLabel*>(obj) == ui->Color_34)
        {
            colorId = 34;
            newColorWasSelected = true;
        }
      else if (qobject_cast<QLabel*>(obj) == ui->Color_35)
        {
            colorId = 35;
            newColorWasSelected = true;
        }
      std::cout<<"COLOR ID IS "<<colorId<<'\n';

      if (colorId >= 0){
          this->close();
          return true;
      }
    }

    else if (event->type() == QEvent::Enter)
    {
        int r = 0, g = 0, b = 0;
        if (qobject_cast<QLabel*>(obj) == ui->Color_0)
          {
            getColorCode(0, r, g, b);
            QString labelFormatStyle = "QLabel{border: 1px solid white; background-color: rgb("+
                    QString::number(r)+
                    ","+
                    QString::number(g)+
                    ","+
                    QString::number(b)+
                    ");}";
              ui->Color_0->setStyleSheet(labelFormatStyle);
          }
        else if (qobject_cast<QLabel*>(obj) == ui->Color_1)
        {
            getColorCode(1, r, g, b);
            QString labelFormatStyle = "QLabel{border: 1px solid white; background-color: rgb("+
                    QString::number(r)+
                    ","+
                    QString::number(g)+
                    ","+
                    QString::number(b)+
                    ");}";
            ui->Color_1->setStyleSheet(labelFormatStyle);
        }
        else if (qobject_cast<QLabel*>(obj) == ui->Color_2)
        {
            getColorCode(2, r, g, b);
            QString labelFormatStyle = "QLabel{border: 1px solid white; background-color: rgb("+
                    QString::number(r)+
                    ","+
                    QString::number(g)+
                    ","+
                    QString::number(b)+
                    ");}";
            ui->Color_2->setStyleSheet(labelFormatStyle);
        }
        else if (qobject_cast<QLabel*>(obj) == ui->Color_3)
        {
            getColorCode(3, r, g, b);
            QString labelFormatStyle = "QLabel{border: 1px solid white; background-color: rgb("+
                    QString::number(r)+
                    ","+
                    QString::number(g)+
                    ","+
                    QString::number(b)+
                    ");}";
            ui->Color_3->setStyleSheet(labelFormatStyle);
        }
        else if (qobject_cast<QLabel*>(obj) == ui->Color_4)
        {
            getColorCode(4, r, g, b);
            QString labelFormatStyle = "QLabel{border: 1px solid white; background-color: rgb("+
                    QString::number(r)+
                    ","+
                    QString::number(g)+
                    ","+
                    QString::number(b)+
                    ");}";
            ui->Color_4->setStyleSheet(labelFormatStyle);
        }
        else if (qobject_cast<QLabel*>(obj) == ui->Color_5)
        {
            getColorCode(5, r, g, b);
            QString labelFormatStyle = "QLabel{border: 1px solid white; background-color: rgb("+
                    QString::number(r)+
                    ","+
                    QString::number(g)+
                    ","+
                    QString::number(b)+
                    ");}";
            ui->Color_5->setStyleSheet(labelFormatStyle);
        }
        else if (qobject_cast<QLabel*>(obj) == ui->Color_6)
        {
            getColorCode(6, r, g, b);
            QString labelFormatStyle = "QLabel{border: 1px solid white; background-color: rgb("+
                    QString::number(r)+
                    ","+
                    QString::number(g)+
                    ","+
                    QString::number(b)+
                    ");}";
            ui->Color_6->setStyleSheet(labelFormatStyle);
        }
        else if (qobject_cast<QLabel*>(obj) == ui->Color_7)
        {
            getColorCode(7, r, g, b);
            QString labelFormatStyle = "QLabel{border: 1px solid white; background-color: rgb("+
                    QString::number(r)+
                    ","+
                    QString::number(g)+
                    ","+
                    QString::number(b)+
                    ");}";
            ui->Color_7->setStyleSheet(labelFormatStyle);
        }
        else if (qobject_cast<QLabel*>(obj) == ui->Color_8)
        {
            getColorCode(8, r, g, b);
            QString labelFormatStyle = "QLabel{border: 1px solid white; background-color: rgb("+
                    QString::number(r)+
                    ","+
                    QString::number(g)+
                    ","+
                    QString::number(b)+
                    ");}";
            ui->Color_8->setStyleSheet(labelFormatStyle);
        }
        else if (qobject_cast<QLabel*>(obj) == ui->Color_9)
        {
            getColorCode(9, r, g, b);
            QString labelFormatStyle = "QLabel{border: 1px solid white; background-color: rgb("+
                    QString::number(r)+
                    ","+
                    QString::number(g)+
                    ","+
                    QString::number(b)+
                    ");}";
            ui->Color_9->setStyleSheet(labelFormatStyle);
        }
        else if (qobject_cast<QLabel*>(obj) == ui->Color_10)
        {
            getColorCode(10, r, g, b);
            QString labelFormatStyle = "QLabel{border: 1px solid white; background-color: rgb("+
                    QString::number(r)+
                    ","+
                    QString::number(g)+
                    ","+
                    QString::number(b)+
                    ");}";
            ui->Color_10->setStyleSheet(labelFormatStyle);
        }
        else if (qobject_cast<QLabel*>(obj) == ui->Color_11)
        {
            getColorCode(11, r, g, b);
            QString labelFormatStyle = "QLabel{border: 1px solid white; background-color: rgb("+
                    QString::number(r)+
                    ","+
                    QString::number(g)+
                    ","+
                    QString::number(b)+
                    ");}";
            ui->Color_11->setStyleSheet(labelFormatStyle);
        }
        else if (qobject_cast<QLabel*>(obj) == ui->Color_12)
        {
            getColorCode(12, r, g, b);
            QString labelFormatStyle = "QLabel{border: 1px solid white; background-color: rgb("+
                    QString::number(r)+
                    ","+
                    QString::number(g)+
                    ","+
                    QString::number(b)+
                    ");}";
            ui->Color_12->setStyleSheet(labelFormatStyle);
        }
        else if (qobject_cast<QLabel*>(obj) == ui->Color_13)
        {
            getColorCode(13, r, g, b);
            QString labelFormatStyle = "QLabel{border: 1px solid white; background-color: rgb("+
                    QString::number(r)+
                    ","+
                    QString::number(g)+
                    ","+
                    QString::number(b)+
                    ");}";
            ui->Color_13->setStyleSheet(labelFormatStyle);
        }
        else if (qobject_cast<QLabel*>(obj) == ui->Color_14)
        {
            getColorCode(14, r, g, b);
            QString labelFormatStyle = "QLabel{border: 1px solid white; background-color: rgb("+
                    QString::number(r)+
                    ","+
                    QString::number(g)+
                    ","+
                    QString::number(b)+
                    ");}";
            ui->Color_14->setStyleSheet(labelFormatStyle);
        }
        else if (qobject_cast<QLabel*>(obj) == ui->Color_15)
        {
            getColorCode(15, r, g, b);
            QString labelFormatStyle = "QLabel{border: 1px solid white; background-color: rgb("+
                    QString::number(r)+
                    ","+
                    QString::number(g)+
                    ","+
                    QString::number(b)+
                    ");}";
            ui->Color_15->setStyleSheet(labelFormatStyle);
        }
        else if (qobject_cast<QLabel*>(obj) == ui->Color_16)
        {
            getColorCode(16, r, g, b);
            QString labelFormatStyle = "QLabel{border: 1px solid white; background-color: rgb("+
                    QString::number(r)+
                    ","+
                    QString::number(g)+
                    ","+
                    QString::number(b)+
                    ");}";
            ui->Color_16->setStyleSheet(labelFormatStyle);
        }
        else if (qobject_cast<QLabel*>(obj) == ui->Color_17)
        {
            getColorCode(17, r, g, b);
            QString labelFormatStyle = "QLabel{border: 1px solid white; background-color: rgb("+
                    QString::number(r)+
                    ","+
                    QString::number(g)+
                    ","+
                    QString::number(b)+
                    ");}";
            ui->Color_17->setStyleSheet(labelFormatStyle);
        }
        else if (qobject_cast<QLabel*>(obj) == ui->Color_18)
        {
            getColorCode(18, r, g, b);
            QString labelFormatStyle = "QLabel{border: 1px solid white; background-color: rgb("+
                    QString::number(r)+
                    ","+
                    QString::number(g)+
                    ","+
                    QString::number(b)+
                    ");}";
            ui->Color_18->setStyleSheet(labelFormatStyle);
        }
        else if (qobject_cast<QLabel*>(obj) == ui->Color_19)
        {
            getColorCode(19, r, g, b);
            QString labelFormatStyle = "QLabel{border: 1px solid white; background-color: rgb("+
                    QString::number(r)+
                    ","+
                    QString::number(g)+
                    ","+
                    QString::number(b)+
                    ");}";
            ui->Color_19->setStyleSheet(labelFormatStyle);
        }
        else if (qobject_cast<QLabel*>(obj) == ui->Color_20)
        {
            getColorCode(20, r, g, b);
            QString labelFormatStyle = "QLabel{border: 1px solid white; background-color: rgb("+
                    QString::number(r)+
                    ","+
                    QString::number(g)+
                    ","+
                    QString::number(b)+
                    ");}";
            ui->Color_20->setStyleSheet(labelFormatStyle);
        }
        else if (qobject_cast<QLabel*>(obj) == ui->Color_21)
        {
            getColorCode(21, r, g, b);
            QString labelFormatStyle = "QLabel{border: 1px solid white; background-color: rgb("+
                    QString::number(r)+
                    ","+
                    QString::number(g)+
                    ","+
                    QString::number(b)+
                    ");}";
            ui->Color_21->setStyleSheet(labelFormatStyle);
        }
        else if (qobject_cast<QLabel*>(obj) == ui->Color_22)
        {
            getColorCode(22, r, g, b);
            QString labelFormatStyle = "QLabel{border: 1px solid white; background-color: rgb("+
                    QString::number(r)+
                    ","+
                    QString::number(g)+
                    ","+
                    QString::number(b)+
                    ");}";
            ui->Color_22->setStyleSheet(labelFormatStyle);
        }
        else if (qobject_cast<QLabel*>(obj) == ui->Color_23)
        {
            getColorCode(23, r, g, b);
            QString labelFormatStyle = "QLabel{border: 1px solid white; background-color: rgb("+
                    QString::number(r)+
                    ","+
                    QString::number(g)+
                    ","+
                    QString::number(b)+
                    ");}";
            ui->Color_23->setStyleSheet(labelFormatStyle);
        }
        else if (qobject_cast<QLabel*>(obj) == ui->Color_24)
        {
            getColorCode(24, r, g, b);
            QString labelFormatStyle = "QLabel{border: 1px solid white; background-color: rgb("+
                    QString::number(r)+
                    ","+
                    QString::number(g)+
                    ","+
                    QString::number(b)+
                    ");}";
            ui->Color_24->setStyleSheet(labelFormatStyle);
        }
        else if (qobject_cast<QLabel*>(obj) == ui->Color_25)
        {
            getColorCode(25, r, g, b);
            QString labelFormatStyle = "QLabel{border: 1px solid white; background-color: rgb("+
                    QString::number(r)+
                    ","+
                    QString::number(g)+
                    ","+
                    QString::number(b)+
                    ");}";
            ui->Color_25->setStyleSheet(labelFormatStyle);
        }
        else if (qobject_cast<QLabel*>(obj) == ui->Color_26)
        {
            getColorCode(26, r, g, b);
            QString labelFormatStyle = "QLabel{border: 1px solid white; background-color: rgb("+
                    QString::number(r)+
                    ","+
                    QString::number(g)+
                    ","+
                    QString::number(b)+
                    ");}";
            ui->Color_26->setStyleSheet(labelFormatStyle);
        }
        else if (qobject_cast<QLabel*>(obj) == ui->Color_27)
        {
            getColorCode(27, r, g, b);
            QString labelFormatStyle = "QLabel{border: 1px solid white; background-color: rgb("+
                    QString::number(r)+
                    ","+
                    QString::number(g)+
                    ","+
                    QString::number(b)+
                    ");}";
            ui->Color_27->setStyleSheet(labelFormatStyle);
        }
        else if (qobject_cast<QLabel*>(obj) == ui->Color_28)
        {
            getColorCode(28, r, g, b);
            QString labelFormatStyle = "QLabel{border: 1px solid white; background-color: rgb("+
                    QString::number(r)+
                    ","+
                    QString::number(g)+
                    ","+
                    QString::number(b)+
                    ");}";
            ui->Color_28->setStyleSheet(labelFormatStyle);
        }
        else if (qobject_cast<QLabel*>(obj) == ui->Color_29)
        {
            getColorCode(29, r, g, b);
            QString labelFormatStyle = "QLabel{border: 1px solid white; background-color: rgb("+
                    QString::number(r)+
                    ","+
                    QString::number(g)+
                    ","+
                    QString::number(b)+
                    ");}";
            ui->Color_29->setStyleSheet(labelFormatStyle);
        }
        else if (qobject_cast<QLabel*>(obj) == ui->Color_30)
        {
            getColorCode(30, r, g, b);
            QString labelFormatStyle = "QLabel{border: 1px solid white; background-color: rgb("+
                    QString::number(r)+
                    ","+
                    QString::number(g)+
                    ","+
                    QString::number(b)+
                    ");}";
            ui->Color_30->setStyleSheet(labelFormatStyle);
        }
        else if (qobject_cast<QLabel*>(obj) == ui->Color_31)
        {
            getColorCode(31, r, g, b);
            QString labelFormatStyle = "QLabel{border: 1px solid white; background-color: rgb("+
                    QString::number(r)+
                    ","+
                    QString::number(g)+
                    ","+
                    QString::number(b)+
                    ");}";
            ui->Color_31->setStyleSheet(labelFormatStyle);
        }
        else if (qobject_cast<QLabel*>(obj) == ui->Color_32)
        {
            getColorCode(32, r, g, b);
            QString labelFormatStyle = "QLabel{border: 1px solid white; background-color: rgb("+
                    QString::number(r)+
                    ","+
                    QString::number(g)+
                    ","+
                    QString::number(b)+
                    ");}";
            ui->Color_32->setStyleSheet(labelFormatStyle);
        }
        else if (qobject_cast<QLabel*>(obj) == ui->Color_33)
        {
            getColorCode(33, r, g, b);
            QString labelFormatStyle = "QLabel{border: 1px solid white; background-color: rgb("+
                    QString::number(r)+
                    ","+
                    QString::number(g)+
                    ","+
                    QString::number(b)+
                    ");}";
            ui->Color_33->setStyleSheet(labelFormatStyle);
        }
        else if (qobject_cast<QLabel*>(obj) == ui->Color_34)
        {
            getColorCode(34, r, g, b);
            QString labelFormatStyle = "QLabel{border: 1px solid white; background-color: rgb("+
                    QString::number(r)+
                    ","+
                    QString::number(g)+
                    ","+
                    QString::number(b)+
                    ");}";
            ui->Color_34->setStyleSheet(labelFormatStyle);
        }
        else if (qobject_cast<QLabel*>(obj) == ui->Color_35)
        {
            getColorCode(35, r, g, b);
            QString labelFormatStyle = "QLabel{border: 1px solid white; background-color: rgb("+
                    QString::number(r)+
                    ","+
                    QString::number(g)+
                    ","+
                    QString::number(b)+
                    ");}";
            ui->Color_35->setStyleSheet(labelFormatStyle);
        }
    }
    else if (event->type() == QEvent::Leave)
    {   int r = 0, g = 0, b = 0;
        if (qobject_cast<QLabel*>(obj) == ui->Color_0)
          {
            getColorCode(0, r, g, b);
            QString labelFormatStyle = "QLabel{background-color: rgb("+
                    QString::number(r)+
                    ","+
                    QString::number(g)+
                    ","+
                    QString::number(b)+
                    ");}";
              ui->Color_0->setStyleSheet(labelFormatStyle);
          }
        else if (qobject_cast<QLabel*>(obj) == ui->Color_1)
        {
            getColorCode(1, r, g, b);
            QString labelFormatStyle = "QLabel{background-color: rgb("+
                    QString::number(r)+
                    ","+
                    QString::number(g)+
                    ","+
                    QString::number(b)+
                    ");}";
            ui->Color_1->setStyleSheet(labelFormatStyle);
        }
        else if (qobject_cast<QLabel*>(obj) == ui->Color_2)
        {
            getColorCode(2, r, g, b);
            QString labelFormatStyle = "QLabel{background-color: rgb("+
                    QString::number(r)+
                    ","+
                    QString::number(g)+
                    ","+
                    QString::number(b)+
                    ");}";
            ui->Color_2->setStyleSheet(labelFormatStyle);
        }
        else if (qobject_cast<QLabel*>(obj) == ui->Color_3)
        {
            getColorCode(3, r, g, b);
            QString labelFormatStyle = "QLabel{background-color: rgb("+
                    QString::number(r)+
                    ","+
                    QString::number(g)+
                    ","+
                    QString::number(b)+
                    ");}";
            ui->Color_3->setStyleSheet(labelFormatStyle);
        }
        else if (qobject_cast<QLabel*>(obj) == ui->Color_4)
        {
            getColorCode(4, r, g, b);
            QString labelFormatStyle = "QLabel{background-color: rgb("+
                    QString::number(r)+
                    ","+
                    QString::number(g)+
                    ","+
                    QString::number(b)+
                    ");}";
            ui->Color_4->setStyleSheet(labelFormatStyle);
        }
        else if (qobject_cast<QLabel*>(obj) == ui->Color_5)
        {
            getColorCode(5, r, g, b);
            QString labelFormatStyle = "QLabel{background-color: rgb("+
                    QString::number(r)+
                    ","+
                    QString::number(g)+
                    ","+
                    QString::number(b)+
                    ");}";
            ui->Color_5->setStyleSheet(labelFormatStyle);
        }
        else if (qobject_cast<QLabel*>(obj) == ui->Color_6)
        {
            getColorCode(6, r, g, b);
            QString labelFormatStyle = "QLabel{background-color: rgb("+
                    QString::number(r)+
                    ","+
                    QString::number(g)+
                    ","+
                    QString::number(b)+
                    ");}";
            ui->Color_6->setStyleSheet(labelFormatStyle);
        }
        else if (qobject_cast<QLabel*>(obj) == ui->Color_7)
        {
            getColorCode(7, r, g, b);
            QString labelFormatStyle = "QLabel{background-color: rgb("+
                    QString::number(r)+
                    ","+
                    QString::number(g)+
                    ","+
                    QString::number(b)+
                    ");}";
            ui->Color_7->setStyleSheet(labelFormatStyle);
        }
        else if (qobject_cast<QLabel*>(obj) == ui->Color_8)
        {
            getColorCode(8, r, g, b);
            QString labelFormatStyle = "QLabel{background-color: rgb("+
                    QString::number(r)+
                    ","+
                    QString::number(g)+
                    ","+
                    QString::number(b)+
                    ");}";
            ui->Color_8->setStyleSheet(labelFormatStyle);
        }
        else if (qobject_cast<QLabel*>(obj) == ui->Color_9)
        {
            getColorCode(9, r, g, b);
            QString labelFormatStyle = "QLabel{background-color: rgb("+
                    QString::number(r)+
                    ","+
                    QString::number(g)+
                    ","+
                    QString::number(b)+
                    ");}";
            ui->Color_9->setStyleSheet(labelFormatStyle);
        }
        else if (qobject_cast<QLabel*>(obj) == ui->Color_10)
        {
            getColorCode(10, r, g, b);
            QString labelFormatStyle = "QLabel{background-color: rgb("+
                    QString::number(r)+
                    ","+
                    QString::number(g)+
                    ","+
                    QString::number(b)+
                    ");}";
            ui->Color_10->setStyleSheet(labelFormatStyle);
        }
        else if (qobject_cast<QLabel*>(obj) == ui->Color_11)
        {
            getColorCode(11, r, g, b);
            QString labelFormatStyle = "QLabel{background-color: rgb("+
                    QString::number(r)+
                    ","+
                    QString::number(g)+
                    ","+
                    QString::number(b)+
                    ");}";
            ui->Color_11->setStyleSheet(labelFormatStyle);
        }
        else if (qobject_cast<QLabel*>(obj) == ui->Color_12)
        {
            getColorCode(12, r, g, b);
            QString labelFormatStyle = "QLabel{background-color: rgb("+
                    QString::number(r)+
                    ","+
                    QString::number(g)+
                    ","+
                    QString::number(b)+
                    ");}";
            ui->Color_12->setStyleSheet(labelFormatStyle);
        }
        else if (qobject_cast<QLabel*>(obj) == ui->Color_13)
        {
            getColorCode(13, r, g, b);
            QString labelFormatStyle = "QLabel{background-color: rgb("+
                    QString::number(r)+
                    ","+
                    QString::number(g)+
                    ","+
                    QString::number(b)+
                    ");}";
            ui->Color_13->setStyleSheet(labelFormatStyle);
        }
        else if (qobject_cast<QLabel*>(obj) == ui->Color_14)
        {
            getColorCode(14, r, g, b);
            QString labelFormatStyle = "QLabel{background-color: rgb("+
                    QString::number(r)+
                    ","+
                    QString::number(g)+
                    ","+
                    QString::number(b)+
                    ");}";
            ui->Color_14->setStyleSheet(labelFormatStyle);
        }
        else if (qobject_cast<QLabel*>(obj) == ui->Color_15)
        {
            getColorCode(15, r, g, b);
            QString labelFormatStyle = "QLabel{background-color: rgb("+
                    QString::number(r)+
                    ","+
                    QString::number(g)+
                    ","+
                    QString::number(b)+
                    ");}";
            ui->Color_15->setStyleSheet(labelFormatStyle);
        }
        else if (qobject_cast<QLabel*>(obj) == ui->Color_16)
        {
            getColorCode(16, r, g, b);
            QString labelFormatStyle = "QLabel{background-color: rgb("+
                    QString::number(r)+
                    ","+
                    QString::number(g)+
                    ","+
                    QString::number(b)+
                    ");}";
            ui->Color_16->setStyleSheet(labelFormatStyle);
        }
        else if (qobject_cast<QLabel*>(obj) == ui->Color_17)
        {
            getColorCode(17, r, g, b);
            QString labelFormatStyle = "QLabel{background-color: rgb("+
                    QString::number(r)+
                    ","+
                    QString::number(g)+
                    ","+
                    QString::number(b)+
                    ");}";
            ui->Color_17->setStyleSheet(labelFormatStyle);
        }
        else if (qobject_cast<QLabel*>(obj) == ui->Color_18)
        {
            getColorCode(18, r, g, b);
            QString labelFormatStyle = "QLabel{background-color: rgb("+
                    QString::number(r)+
                    ","+
                    QString::number(g)+
                    ","+
                    QString::number(b)+
                    ");}";
            ui->Color_18->setStyleSheet(labelFormatStyle);
        }
        else if (qobject_cast<QLabel*>(obj) == ui->Color_19)
        {
            getColorCode(19, r, g, b);
            QString labelFormatStyle = "QLabel{background-color: rgb("+
                    QString::number(r)+
                    ","+
                    QString::number(g)+
                    ","+
                    QString::number(b)+
                    ");}";
            ui->Color_19->setStyleSheet(labelFormatStyle);
        }
        else if (qobject_cast<QLabel*>(obj) == ui->Color_20)
        {
            getColorCode(20, r, g, b);
            QString labelFormatStyle = "QLabel{background-color: rgb("+
                    QString::number(r)+
                    ","+
                    QString::number(g)+
                    ","+
                    QString::number(b)+
                    ");}";
            ui->Color_20->setStyleSheet(labelFormatStyle);
        }
        else if (qobject_cast<QLabel*>(obj) == ui->Color_21)
        {
            getColorCode(21, r, g, b);
            QString labelFormatStyle = "QLabel{background-color: rgb("+
                    QString::number(r)+
                    ","+
                    QString::number(g)+
                    ","+
                    QString::number(b)+
                    ");}";
            ui->Color_21->setStyleSheet(labelFormatStyle);
        }
        else if (qobject_cast<QLabel*>(obj) == ui->Color_22)
        {
            getColorCode(22, r, g, b);
            QString labelFormatStyle = "QLabel{background-color: rgb("+
                    QString::number(r)+
                    ","+
                    QString::number(g)+
                    ","+
                    QString::number(b)+
                    ");}";
            ui->Color_22->setStyleSheet(labelFormatStyle);
        }
        else if (qobject_cast<QLabel*>(obj) == ui->Color_23)
        {
            getColorCode(23, r, g, b);
            QString labelFormatStyle = "QLabel{background-color: rgb("+
                    QString::number(r)+
                    ","+
                    QString::number(g)+
                    ","+
                    QString::number(b)+
                    ");}";
            ui->Color_23->setStyleSheet(labelFormatStyle);
        }
        else if (qobject_cast<QLabel*>(obj) == ui->Color_24)
        {
            getColorCode(24, r, g, b);
            QString labelFormatStyle = "QLabel{background-color: rgb("+
                    QString::number(r)+
                    ","+
                    QString::number(g)+
                    ","+
                    QString::number(b)+
                    ");}";
            ui->Color_24->setStyleSheet(labelFormatStyle);
        }
        else if (qobject_cast<QLabel*>(obj) == ui->Color_25)
        {
            getColorCode(25, r, g, b);
            QString labelFormatStyle = "QLabel{background-color: rgb("+
                    QString::number(r)+
                    ","+
                    QString::number(g)+
                    ","+
                    QString::number(b)+
                    ");}";
            ui->Color_25->setStyleSheet(labelFormatStyle);
        }
        else if (qobject_cast<QLabel*>(obj) == ui->Color_26)
        {
            getColorCode(26, r, g, b);
            QString labelFormatStyle = "QLabel{background-color: rgb("+
                    QString::number(r)+
                    ","+
                    QString::number(g)+
                    ","+
                    QString::number(b)+
                    ");}";
            ui->Color_26->setStyleSheet(labelFormatStyle);
        }
        else if (qobject_cast<QLabel*>(obj) == ui->Color_27)
        {
            getColorCode(27, r, g, b);
            QString labelFormatStyle = "QLabel{background-color: rgb("+
                    QString::number(r)+
                    ","+
                    QString::number(g)+
                    ","+
                    QString::number(b)+
                    ");}";
            ui->Color_27->setStyleSheet(labelFormatStyle);
        }
        else if (qobject_cast<QLabel*>(obj) == ui->Color_28)
        {
            getColorCode(28, r, g, b);
            QString labelFormatStyle = "QLabel{background-color: rgb("+
                    QString::number(r)+
                    ","+
                    QString::number(g)+
                    ","+
                    QString::number(b)+
                    ");}";
            ui->Color_28->setStyleSheet(labelFormatStyle);
        }
        else if (qobject_cast<QLabel*>(obj) == ui->Color_29)
        {
            getColorCode(29, r, g, b);
            QString labelFormatStyle = "QLabel{background-color: rgb("+
                    QString::number(r)+
                    ","+
                    QString::number(g)+
                    ","+
                    QString::number(b)+
                    ");}";
            ui->Color_29->setStyleSheet(labelFormatStyle);
        }
        else if (qobject_cast<QLabel*>(obj) == ui->Color_30)
        {
            getColorCode(30, r, g, b);
            QString labelFormatStyle = "QLabel{background-color: rgb("+
                    QString::number(r)+
                    ","+
                    QString::number(g)+
                    ","+
                    QString::number(b)+
                    ");}";
            ui->Color_30->setStyleSheet(labelFormatStyle);
        }
        else if (qobject_cast<QLabel*>(obj) == ui->Color_31)
        {
            getColorCode(31, r, g, b);
            QString labelFormatStyle = "QLabel{background-color: rgb("+
                    QString::number(r)+
                    ","+
                    QString::number(g)+
                    ","+
                    QString::number(b)+
                    ");}";
            ui->Color_31->setStyleSheet(labelFormatStyle);
        }
        else if (qobject_cast<QLabel*>(obj) == ui->Color_32)
        {
            getColorCode(32, r, g, b);
            QString labelFormatStyle = "QLabel{background-color: rgb("+
                    QString::number(r)+
                    ","+
                    QString::number(g)+
                    ","+
                    QString::number(b)+
                    ");}";
            ui->Color_32->setStyleSheet(labelFormatStyle);
        }
        else if (qobject_cast<QLabel*>(obj) == ui->Color_33)
        {
            getColorCode(33, r, g, b);
            QString labelFormatStyle = "QLabel{background-color: rgb("+
                    QString::number(r)+
                    ","+
                    QString::number(g)+
                    ","+
                    QString::number(b)+
                    ");}";
            ui->Color_33->setStyleSheet(labelFormatStyle);
        }
        else if (qobject_cast<QLabel*>(obj) == ui->Color_34)
        {
            getColorCode(34, r, g, b);
            QString labelFormatStyle = "QLabel{background-color: rgb("+
                    QString::number(r)+
                    ","+
                    QString::number(g)+
                    ","+
                    QString::number(b)+
                    ");}";
            ui->Color_34->setStyleSheet(labelFormatStyle);
        }
        else if (qobject_cast<QLabel*>(obj) == ui->Color_35)
        {
            getColorCode(35, r, g, b);
            QString labelFormatStyle = "QLabel{background-color: rgb("+
                    QString::number(r)+
                    ","+
                    QString::number(g)+
                    ","+
                    QString::number(b)+
                    ");}";
            ui->Color_35->setStyleSheet(labelFormatStyle);
        }
    }

    return false;
}

void SelectColorDialog::on_Transparent_clicked()
{
    colorId = 36;
    newColorWasSelected = true;
    this->close();
}
