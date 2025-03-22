/*
* Copyright © 2020-2025 Carlos Constancio Dominguez Martinez
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

#include "exportdialog.h"
#include "ui_exportdialog.h"
#include "QFileDialog"
#include "eraseconfirmation_dialog.h"

ExportDialog::ExportDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ExportDialog)
{
    ui->setupUi(this);
    this->setFixedSize(this->width(), this->height());
    ui->listWidget->setSelectionMode(QAbstractItemView::NoSelection);
    ui->cancelButton->installEventFilter(this);
    ui->exportButton->installEventFilter(this);
}

ExportDialog::~ExportDialog()
{
    delete ui;
    mainAccount = nullptr;
}

void ExportDialog::setAccount(Account *tAccount)
{
    mainAccount = tAccount;
    switch (mainAccount->getAccountLanguage()) {
       case ENGLISH:
        ui->cancelButton->setText("Cancel");
        ui->exportButton->setText("Export");
        ui->labelNote->setText("One file per selected year will be created.");
        this->setWindowTitle("Select data");
        break;
       case GERMAN:
        ui->cancelButton->setText("Abbrechen");
        ui->exportButton->setText("Exportieren");
        ui->labelNote->setText("Es wird eine Datei für jedes ausgewählte Jahr erstellt.");
        this->setWindowTitle("Daten Auswählen");
        break;
       case SPANISH:
        ui->cancelButton->setText("Cancelar");
        ui->exportButton->setText("Exportar");
        ui->labelNote->setText("Se creará un archivo por cada año.");
        this->setWindowTitle("Seleccionar datos");
        break;
       default:
        break;
    }
}

void ExportDialog::setOverallThemeStyleSheet(QString styleSheetString, bool useDarkTheme)
{
    this->setStyleSheet(styleSheetString);
    ui->cancelButton->updateColorTheme(useDarkTheme);
    ui->exportButton->updateColorTheme(useDarkTheme);
    styleSheetStr = styleSheetString;
    usingDarkTheme = useDarkTheme;
}

void ExportDialog::setListOfYearsWithData(std::vector<int>& listOfYearsWithData)
{
    for (std::vector<int>::iterator it = listOfYearsWithData.begin();
         it != listOfYearsWithData.end(); ++it)
    {
        QListWidgetItem *listItem = new QListWidgetItem(QString::number(*it),ui->listWidget);
        listItem->setCheckState(Qt::Unchecked);
        ui->listWidget->addItem(listItem);
    }

}

void ExportDialog::on_exportButton_clicked()
{
    std::string infoText = "";
    switch (mainAccount->getAccountLanguage()) {
       case ENGLISH:
        infoText = "Select Directory";
        break;
       case GERMAN:
        infoText = "Ordner Auswählen";
        break;
       case SPANISH:
        infoText = "Seleccionar carpeta";
        break;
       default:
        break;
    }

#ifdef USING_WINDOWS
    homeFolder = QDir::homePath();
#endif

    QString savingPath = QFileDialog::getExistingDirectory(this, tr(infoText.c_str()),
                                                homeFolder,
                                                QFileDialog::ShowDirsOnly
                                                | QFileDialog::DontResolveSymlinks);

    std::vector<int> listOfSelectedYearsToExport;
    for (int i = 0; i != ui->listWidget->count(); ++i)
    {
        QListWidgetItem* item = ui->listWidget->item(i);
        if (item->checkState() == Qt::CheckState::Checked)
        {
            listOfSelectedYearsToExport.push_back(item->text().toInt());
        }

    }

    mainAccount->exportDataToCsvFile(savingPath.toStdString(), listOfSelectedYearsToExport);

    eraseConfirmation_dialog infoDialog;
    QString infoTitle;
    switch (mainAccount->getAccountLanguage()) {
       case ENGLISH:
        infoText = "Data has been exported.";
        infoTitle = "Information";
        break;
       case GERMAN:
        infoText = "Die Daten wurden exportiert.";
        infoTitle = "Information";
        break;
       case SPANISH:
        infoText = "Los datos se han exportado.";
        infoTitle = "Información";
        break;
       default:
        break;
    }
    infoDialog.setInfoText(infoText);
    infoDialog.setWindowTitle(infoTitle);
    infoDialog.setOverallThemeStyleSheet(styleSheetStr, usingDarkTheme);
    infoDialog.exec();

    mainAccount = nullptr;

    this->close();
}


void ExportDialog::on_cancelButton_clicked()
{
    mainAccount = nullptr;
    this->close();
}

bool ExportDialog::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::MouseButtonPress)
    {
        if (qobject_cast<QWidget*>(obj) == ui->cancelButton) {
            this->ui->cancelButton->setColorForMouseButtonPressEvent();
        }
        else if (qobject_cast<QWidget*>(obj) == ui->exportButton) {
            this->ui->exportButton->setColorForMouseButtonPressEvent();
        }
    }
    else if (event->type() == QEvent::MouseButtonRelease)
    {
        if (qobject_cast<QWidget*>(obj) == ui->cancelButton) {
            this->ui->cancelButton->setColorForEnterEvent();
        }
        else if (qobject_cast<QWidget*>(obj) == ui->exportButton) {
            this->ui->exportButton->setColorForEnterEvent();
        }
    }
    else if (event->type() == QEvent::Enter)
     {
         if (qobject_cast<QPushButton*>(obj) == ui->cancelButton)
         {
             this->ui->cancelButton->setColorForEnterEvent();
         }
         else if (qobject_cast<QWidget*>(obj) == ui->exportButton) {
             this->ui->exportButton->setColorForEnterEvent();
         }
    }
    else if (event->type() == QEvent::Leave)
     {
         if (qobject_cast<QPushButton*>(obj) == ui->cancelButton)
         {
             this->ui->cancelButton->setColorForLeaveEvent();
         }
         else if (qobject_cast<QWidget*>(obj) == ui->exportButton) {
             this->ui->exportButton->setColorForLeaveEvent();
         }
    }
    return false;
}
