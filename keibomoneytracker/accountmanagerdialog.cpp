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

#include "accountmanagerdialog.h"
#include "ui_accountmanagerdialog.h"

AccountManagerDialog::AccountManagerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AccountManagerDialog)
{
    ui->setupUi(this);
    this->ui->tableWidget->setTabKeyNavigation(false);
    this->ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    int iconWidth  = ui->btnOpenAccount->width();
    int iconHeight = ui->btnOpenAccount->height();

    ui->btnOpenAccount->installEventFilter(this);
    ui->btnOpenAccount->setIcon(QIcon(":/images/Open.png"));
    ui->btnOpenAccount->setIconSize(QSize(iconWidth, iconHeight));
    QString buttonOpenStyle = "QPushButton{border: 1px solid white; border-color: rgba(186, 189, 182, 127); border-radius: 5px;}"; //background-color:rgba(0, 0, 0, 15);
    ui->btnOpenAccount->setStyleSheet(buttonOpenStyle);

    ui->btnEditAccount->installEventFilter(this);
    ui->btnEditAccount->setIcon(QIcon(":/images/Edit.png"));
    ui->btnEditAccount->setIconSize(QSize(iconWidth, iconHeight));
    QString buttonEditStyle = "QPushButton{border: 1px solid white; border-color: rgba(186, 189, 182, 127); border-radius: 5px;}";
    ui->btnEditAccount->setStyleSheet(buttonEditStyle);

    ui->btnDeleteAccount->installEventFilter(this);
    ui->btnDeleteAccount->setIcon(QIcon(":/images/Delete.png"));
    ui->btnDeleteAccount->setIconSize(QSize(iconWidth, iconHeight));
    QString buttonDeleteStyle = "QPushButton{border: 1px solid white; border-color: rgba(186, 189, 182, 127); border-radius: 5px;}";
    ui->btnDeleteAccount->setStyleSheet(buttonDeleteStyle);

    ui->btnCreateNewAccount->installEventFilter(this);
    ui->btnCreateNewAccount->setIcon(QIcon(":/images/CreateNew.png"));
    ui->btnCreateNewAccount->setIconSize(QSize(iconWidth, iconHeight));
    QString buttonCreateNewStyle = "QPushButton{border: 1px solid white; border-color: rgba(186, 189, 182, 127); border-radius: 5px;}";
    ui->btnCreateNewAccount->setStyleSheet(buttonCreateNewStyle);

    this->setAttribute(Qt::WA_Hover);
    this->setMouseTracking(true);
}

AccountManagerDialog::~AccountManagerDialog()
{
    delete ui;
}

bool AccountManagerDialog::eventFilter(QObject *obj, QEvent *event)
{
   if (event->type() == QEvent::Enter)
    {
        if (qobject_cast<QPushButton*>(obj) == ui->btnOpenAccount)
        {
            QString buttonOpenStyle = "QPushButton{border: 1px solid white; border-color: rgba(186, 189, 182, 127); background-color:rgba(128, 128, 128, 60); border-radius: 5px;}";
            ui->btnOpenAccount->setStyleSheet(buttonOpenStyle);
            return true;
        }
        else if (qobject_cast<QPushButton*>(obj) == ui->btnEditAccount)
        {
            QString buttonEditStyle = "QPushButton{border: 1px solid white; border-color: rgba(186, 189, 182, 127); background-color:rgba(128, 128, 128, 60); border-radius: 5px;}";
            ui->btnEditAccount->setStyleSheet(buttonEditStyle);
            return true;
        }
        else if (qobject_cast<QPushButton*>(obj) == ui->btnDeleteAccount)
        {
            QString buttonDeleteStyle = "QPushButton{border: 1px solid white; border-color: rgba(186, 189, 182, 127); background-color:rgba(128, 128, 128, 60); border-radius: 5px;}";
            ui->btnDeleteAccount->setStyleSheet(buttonDeleteStyle);
            return true;
        }
        else if (qobject_cast<QPushButton*>(obj) == ui->btnCreateNewAccount)
        {
            QString buttonCreateNewStyle = "QPushButton{border: 1px solid white; border-color: rgba(186, 189, 182, 127); background-color:rgba(128, 128, 128, 60); border-radius: 5px;}";
            ui->btnCreateNewAccount->setStyleSheet(buttonCreateNewStyle);
            return true;
        }
    }

    else if (event->type() == QEvent::Leave)
    {
        if (qobject_cast<QPushButton*>(obj) == ui->btnOpenAccount)
        {
            QString buttonOpenStyle = "QPushButton{border: 1px solid white; border-color: rgba(186, 189, 182, 127); background-color:rgba(0, 0, 0, 0); border-radius: 5px;}";
            ui->btnOpenAccount->setStyleSheet(buttonOpenStyle);
            return true;
        }
        else if (qobject_cast<QPushButton*>(obj) == ui->btnEditAccount)
        {
            QString buttonEditStyle = "QPushButton{border: 1px solid white; border-color: rgba(186, 189, 182, 127); background-color:rgba(0, 0, 0, 0); border-radius: 5px;}";
            ui->btnEditAccount->setStyleSheet(buttonEditStyle);
            return true;
        }
        else if (qobject_cast<QPushButton*>(obj) == ui->btnDeleteAccount)
        {
            QString buttonDeleteStyle = "QPushButton{border: 1px solid white; border-color: rgba(186, 189, 182, 127); background-color:rgba(0, 0, 0, 0); border-radius: 5px;}";
            ui->btnDeleteAccount->setStyleSheet(buttonDeleteStyle);
            return true;
        }
        else if (qobject_cast<QPushButton*>(obj) == ui->btnCreateNewAccount)
        {
            QString buttonCreateNewStyle = "QPushButton{border: 1px solid white; border-color: rgba(186, 189, 182, 127); background-color:rgba(0, 0, 0, 0); border-radius: 5px;}";
            ui->btnCreateNewAccount->setStyleSheet(buttonCreateNewStyle);
            return true;
        }
    }
    return false;
}

void AccountManagerDialog::setOverallThemeStyleSheet(QString styleSheetString)
{
    this->setStyleSheet(styleSheetString);
    this->ui->labelImage->setStyleSheet("QLabel#labelImage{border: 1px solid gray; border-color:rgba(186, 189, 182, 130); border-radius:5px;}");
}

void AccountManagerDialog::fillListWithExistingAccounts(std::vector<std::string> listOfAccounts,
                                                        std::vector<std::string> listOfAccountPaths)
{
   allowLoadAccountImages = false;
    ui->tableWidget->setRowCount(listOfAccounts.size());
    ui->tableWidget->setColumnCount(1);
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);

    ui->tableWidget->verticalHeader()->setVisible(false);
    ui->tableWidget->horizontalHeader()->setVisible(false);
    ui->tableWidget->setShowGrid(false);
    /*QFont font = QFont("URW Gothic", 10, -1, false);
    ui->tableWidget->setFont (font);*/

    int itemId = 0;
    for (std::vector<std::string>::iterator accountIterator =  listOfAccounts.begin();
                                            accountIterator != listOfAccounts.end();
                                            ++accountIterator)
    {
        ui->tableWidget->setItem(itemId,0, new QTableWidgetItem (QString::fromStdString(*accountIterator)));
        ui->tableWidget->setRowHeight(itemId, 22);
        ++itemId;
    }
    allowLoadAccountImages = true;

    iListOfAccountPaths = listOfAccountPaths;

    this->ui->tableWidget->setSelectionBehavior( QAbstractItemView::SelectItems );
    this->ui->tableWidget->setSelectionMode( QAbstractItemView::SingleSelection );
    this->ui->tableWidget->setCurrentIndex(this->ui->tableWidget->model()->index(0, 0));//Select first account automatically
}

int AccountManagerDialog::provideSelectedAccountIdIndex(int &selectedAccountIdIndex)
{
    selectedAccountIdIndex = SELECTED_ACCOUNT_INDEX;
    return SELECTED_ACCOUNT_INDEX;
}

void AccountManagerDialog::on_btnOpenAccount_clicked()
{
    QItemSelectionModel *selection = this->ui->tableWidget->selectionModel();
    QModelIndexList highlightedRows = selection->selectedRows();
    if (highlightedRows.count()>0 && highlightedRows.count()<2)
    {
        OpenAccount = true;
        this->close();
    }
}

void AccountManagerDialog::on_btnEditAccount_clicked()
{
    QItemSelectionModel *selection = this->ui->tableWidget->selectionModel();
    QModelIndexList highlightedRows = selection->selectedRows();
    if (highlightedRows.count()>0 && highlightedRows.count()<2)
    {
        EditAccount = true;
        this->close();
    }
}

void AccountManagerDialog::on_btnDeleteAccount_clicked()
{
    QItemSelectionModel *selection = this->ui->tableWidget->selectionModel();
    QModelIndexList highlightedRows = selection->selectedRows();
    if (highlightedRows.count()>0 && highlightedRows.count()<2)
    {
        DeleteAccount = true;
        this->close();
    }
}

void AccountManagerDialog::on_btnCreateNewAccount_clicked()
{
    CreateNewAccount = true;
    this->close();

}

void AccountManagerDialog::on_tableWidget_itemSelectionChanged()
{    
    if (allowLoadAccountImages)
    {
        SELECTED_ACCOUNT_INDEX = ui->tableWidget->currentRow();
        std::vector<std::string>::iterator accountPathIterator =  iListOfAccountPaths.begin()+SELECTED_ACCOUNT_INDEX;
        //Search for existing images for accounts.
        if (SELECTED_ACCOUNT_INDEX >= 0) {
            QString imagePath = QString::fromStdString(*accountPathIterator+"/AccountIcon.png");
            std::cout<<"IMAGE ACCOUNT PATH: "<<imagePath.toStdString()<<'\n';
            QImage srcImg(imagePath);
            QPixmap imagePixmap = QPixmap::fromImage(srcImg);
            if (!imagePixmap.isNull()) {
                int w = ui->labelImage->width();
                int h = ui->labelImage->height();
                ui->labelImage->setPixmap(imagePixmap.scaled(w, h, Qt::KeepAspectRatio, Qt::SmoothTransformation));
                ui->labelImage->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
            } else {
                ui->labelImage->setText("No image");
            }
        }
    }
}
