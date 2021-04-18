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

#include "accountstatsdialog.h"
#include "ui_accountstatsdialog.h"
#include <iostream>
#include <QScrollBar>

AccountStatsDialog::AccountStatsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AccountStatsDialog)
{
    ui->setupUi(this);
    this->setFixedSize(this->geometry().width(),this->geometry().height());
    ui->tableStats->setFrameStyle(QFrame::NoFrame);
    ui->tableStats->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
}

AccountStatsDialog::~AccountStatsDialog()
{
    delete ui;
}

void AccountStatsDialog::setThemeStyleSheet(QString styleSheetString)
{
    this->setStyleSheet(styleSheetString);

    this->ui->tableStats->verticalScrollBar()->setStyleSheet(
                "QScrollBar:vertical { width: 15px; margin: 0px 0px 0px 0px; }"
                "QScrollBar::add-line:vertical { border: none; background: none;}"
                "QScrollBar::sub-line:vertical { border: none; background: none;}");
    this->ui->tableStats->horizontalScrollBar()->setStyleSheet(
                "QScrollBar:horizontal { width: 15px; margin: 0px 0px 0px 0px; }"
                "QScrollBar::add-line:horizontal { border: none; background: none;}"
                "QScrollBar::sub-line:horizontal { border: none; background: none;}" );


    this->ui->groupBox->setStyleSheet("QGroupBox#groupBox{border: 1px solid gray; border-color:rgba(186, 189, 182, 130); border-radius:5px;}");
    this->ui->labelAccountImage->setStyleSheet("QLabel#labelAccountImage{border: 1px solid gray; border-color:rgba(186, 189, 182, 130); border-radius:5px;}");
    this->ui->labelAdditionalInformation->setStyleSheet("QLabel#labelAdditionalInformation{border: 1px solid gray; border-color:rgba(186, 189, 182, 130); border-left-style: rgba(255, 255, 255, 0); border-right-style: rgba(255, 255, 255, 0); border-bottom-style: rgba(255, 255, 255, 0);}");
}

void AccountStatsDialog::getAccountStats(std::vector<QString> statNames, std::vector<QString> statValues)
{
   ui->tableStats->setWordWrap(false);
   ui->tableStats->setRowCount(27);
   ui->tableStats->setColumnCount(2);
   ui->tableStats->setColumnWidth(0,(ui->tableStats->width()/2)-10);
   ui->tableStats->setColumnWidth(1,(ui->tableStats->width()/2)-5);
   ui->tableStats->setTabKeyNavigation(false);
   ui->tableStats->setEditTriggers(QAbstractItemView::NoEditTriggers);
   ui->tableStats->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);

   ui->tableStats->verticalHeader()->setVisible(false);
   ui->tableStats->setShowGrid(false);

   std::vector<QString>::iterator QStrNamesIterator = statNames.begin()+5;
   std::vector<QString>::iterator QStrValueIterator = statValues.begin()+5;

   for (int rowId = 0; rowId != 27; ++rowId)
   {
       if (rowId == 3 || rowId == 6 || rowId == 9 || rowId == 14 || rowId == 19 || rowId == 24){
           ui->tableStats->setRowHeight(rowId,5);
       }  else {
           //FIRST COLUMN
           ui->tableStats->setItem(rowId,0, new QTableWidgetItem (*QStrNamesIterator));
           ui->tableStats->item(rowId, 0)->setTextAlignment(Qt::AlignBottom);
           //SECOND COLUMN
           ui->tableStats->setItem(rowId,1, new QTableWidgetItem (*QStrValueIterator));
           ui->tableStats->item(rowId, 1)->setTextAlignment(Qt::AlignBottom);
           ui->tableStats->setRowHeight(rowId,20);

           ++QStrNamesIterator;
           ++QStrValueIterator;
       }
   }


  QStrValueIterator = statValues.begin()+3;
  if (!(*QStrValueIterator).isEmpty()){
      QImage srcImg(*QStrValueIterator);
      QPixmap imagePixmap = QPixmap::fromImage(srcImg);
      int w = ui->labelAccountImage->width();
      int h = ui->labelAccountImage->height();
      ui->labelAccountImage->setPixmap(imagePixmap.scaled(w, h, Qt::KeepAspectRatio, Qt::SmoothTransformation));
      ui->labelAccountImage->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
  }

  ui->labelAccountName->setText(statValues[0]);
  ui->labelTimeInterval->setText(statValues[4]);
  ui->labelAccountLanguage->setText(statValues[2]);
  ui->labelAccountCurrency->setText(statValues[1]);

  ui->labelName->setText(statNames[0]);
  ui->labelCurrency->setText(statNames[1]);
  ui->labelLanguage->setText(statNames[2]);

  QStrValueIterator = statValues.end()-1;
  ui->labelAdditionalInformation->setText(*QStrValueIterator);
}
