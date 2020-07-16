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

#include "donatedialog.h"
#include "ui_donatedialog.h"
#include <QDesktopServices>
#include <QUrl>

DonateDialog::DonateDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DonateDialog)
{
    ui->setupUi(this);

    this->setFixedSize(this->width(), this->height());
    this->setImageOnLabel(":/images/AppIcon.png");
}

DonateDialog::~DonateDialog()
{
    delete ui;
    delete item;
    delete scene;
}

void DonateDialog::setLanguageAndStyleSheet(const Language &iLanguage, const QString &iStyleSheet)
{
    this->setStyleSheet(iStyleSheet);
    if (iLanguage == GERMAN)
    {
        this->ui->labelThanks->setText("Hey Du! Vielen Dank, dass Du meine App Keibo-MoneyTracker benutzt. Ich hoffe, dass sie dir hilft mehr Ordnung in deine Finanzen zu bringen. "
                                       "Wenn Du möchtest, kannst Du mir etwas spenden.");
        this->setWindowTitle("Spenden");
        this->ui->pushButtonDonate->setText("Spenden");
    }
    else if (iLanguage == SPANISH)
    {
        this->ui->labelThanks->setText("Hola! Muchas gracias por usar Keibo-MoneyTracker. Espero que te sea de ayuda con las finanzas. "
                                       "Si piensas que ésta App es útil, por favor considera una donación. ");
        this->setWindowTitle("Donar");
        this->ui->pushButtonDonate->setText("Donar");
    }
    else
    {
        this->ui->labelThanks->setText("Hey there! Thank you for using Keibo-MoneyTracker. I hope it helps you to have a clearer view about your finances. "
                                       "If you find this app useful please consider donating.");
        this->setWindowTitle("Donate");
        this->ui->pushButtonDonate->setText("Donate");
    }
}

void DonateDialog::on_pushButtonDonate_clicked()
{
    QDesktopServices::openUrl(QUrl(DonateLink));
}


void DonateDialog::setImageOnLabel(const QString &imagePath)
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
