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

#include "aboutdialog.h"
#include "ui_aboutdialog.h"

AboutDialog::AboutDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutDialog)
{
    ui->setupUi(this);

    this->setWindowTitle(" About");
    this->setFixedSize(this->width(), this->height());

     ui->textAbout->setReadOnly(true);
     ui->textLibraries->setReadOnly(true);
     ui->textLicense->setReadOnly(true);
     ui->textAuthor->setReadOnly(true);
     ui->textAppName->setReadOnly(true);
     ui->textAppVersion->setReadOnly(true);

     this->setImageOnLabel(":/images/AppIcon.png");

     ui->graphicsViewIcon->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
     ui->graphicsViewIcon->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
     ui->textAppVersion->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
     setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

}

AboutDialog::~AboutDialog()
{
    delete ui;
    delete item;
    delete scene;
}

void AboutDialog::setImageOnLabel(const QString &imagePath)
{
    ui->graphicsViewIcon->resetTransform();

    QImage srcImg(imagePath);
    QPixmap imagePixmap = QPixmap::fromImage(srcImg);

    if (!imagePixmap.isNull())
    {
        int w = ui->graphicsViewIcon->width()-2;
        int h = ui->graphicsViewIcon->height()-2;

        item = new QGraphicsPixmapItem(imagePixmap);
        item->setTransformationMode(Qt::SmoothTransformation);
        scene = new QGraphicsScene(this);

        scene->addItem(item);

        double factorX = w/(static_cast<double>(imagePixmap.width()));
        double factorY = h/(static_cast<double>(imagePixmap.height()));
        ui->graphicsViewIcon->scale(factorX, factorY);

        ui->graphicsViewIcon->setScene(scene);
    }
}
