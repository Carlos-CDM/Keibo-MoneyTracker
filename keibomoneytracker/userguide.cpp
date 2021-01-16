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

#include "userguide.h"
#include "ui_userguide.h"
#include <iostream>

UserGuide::UserGuide(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UserGuide)
{
    ui->setupUi(this);

    this->setFixedSize(this->width(), this->height());

    this->ui->textEditExplanation->setReadOnly(true);
    this->ui->textEditExplanation->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->ui->textEditExplanation->installEventFilter(this);
    this->ui->graphicsViewImage->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->ui->graphicsViewImage->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    //----------------------------------------------------------//
    int groupIconWidth  = this->ui->pushButtonPrevious->width();
    int groupIconHeight = this->ui->pushButtonPrevious->height();

    this->ui->pushButtonNext->installEventFilter(this);
    this->ui->pushButtonNext->setIcon(QIcon(":/images/ArrowRight.png"));
    this->ui->pushButtonNext->setIconSize(QSize(groupIconWidth, groupIconHeight));
    QString buttonNextStyle = "QPushButton{border: 1px solid white; border-color: rgba(0,0,0,0); border-radius: 5px;}";
    this->ui->pushButtonNext->setStyleSheet(buttonNextStyle);

    this->ui->pushButtonPrevious->installEventFilter(this);
    this->ui->pushButtonPrevious->setIcon(QIcon(":/images/ArrowLeft.png"));
    this->ui->pushButtonPrevious->setIconSize(QSize(groupIconWidth, groupIconHeight));
    QString buttonPreviousStyle = "QPushButton{border: 1px solid white; border-color: rgba(0,0,0,0); border-radius: 5px;}";
    this->ui->pushButtonPrevious->setStyleSheet(buttonPreviousStyle);

    this->ui->pushButtonAccounts->installEventFilter(this);
    this->ui->pushButtonMainWindow->installEventFilter(this);
    this->ui->pushButtonTransactions->installEventFilter(this);
    this->ui->pushButtonGroups->installEventFilter(this);
    this->ui->pushButtonAppearance->installEventFilter(this);
    this->ui->pushButtonStoredFiles->installEventFilter(this);
}

UserGuide::~UserGuide()
{
    delete ui;
    delete item;
    delete scene;
    delete pushButtonCurrentlySelectedTutorial;
}

bool UserGuide::eventFilter(QObject *obj, QEvent *event)
{
    QString buttonUnselectedStyle = "QPushButton{ border: 1px solid gray; border-color: rgba(186, 189, 182, 127); background-color:rgba(0, 0, 0, 0); border-radius: 5px; }"; //border: 1px solid gray; border-color: rgba(186, 189, 182, 127);
    QString buttonSelectedStyle = "QPushButton{ border: 1px solid gray; border-color: rgba(186, 189, 182, 127); background-color:rgba(128, 128, 128, 60); border-radius: 5px; }";
    QString buttonUnselectedStyleArrow = "QPushButton{  background-color:rgba(0, 0, 0, 0); border-radius: 5px; }";
    QString buttonSelectedStyleArrow = "QPushButton{  background-color:rgba(128, 128, 128, 60); border-radius: 5px; }";

    if (event->type() == QEvent::Enter)
    {
        if (qobject_cast<QPushButton*>(obj) == pushButtonCurrentlySelectedTutorial)
        {
            return false;
        }
        else if (qobject_cast<QPushButton*>(obj) == ui->pushButtonPrevious)
        {
            ui->pushButtonPrevious->setStyleSheet(buttonSelectedStyleArrow);
            return true;
        }
        else if (qobject_cast<QPushButton*>(obj) == ui->pushButtonNext)
        {
            ui->pushButtonNext->setStyleSheet(buttonSelectedStyleArrow);
            return true;
        }
        else if (qobject_cast<QPushButton*>(obj) == ui->pushButtonAccounts)
        {
            ui->pushButtonAccounts->setStyleSheet(buttonSelectedStyle);
            return true;
        }
        else if (qobject_cast<QPushButton*>(obj) == ui->pushButtonMainWindow)
        {
            ui->pushButtonMainWindow->setStyleSheet(buttonSelectedStyle);
            return true;
        }
        else if (qobject_cast<QPushButton*>(obj) == ui->pushButtonTransactions)
        {
            ui->pushButtonTransactions->setStyleSheet(buttonSelectedStyle);
            return true;
        }
        else if (qobject_cast<QPushButton*>(obj) == ui->pushButtonGroups)
        {
            ui->pushButtonGroups->setStyleSheet(buttonSelectedStyle);
            return true;
        }
        else if (qobject_cast<QPushButton*>(obj) == ui->pushButtonAppearance)
        {
            ui->pushButtonAppearance->setStyleSheet(buttonSelectedStyle);
            return true;
        }
        else if (qobject_cast<QPushButton*>(obj) == ui->pushButtonStoredFiles)
        {
            ui->pushButtonStoredFiles->setStyleSheet(buttonSelectedStyle);
            return true;
        }
    }
    else if (event->type() == QEvent::Leave)
    {
        if (qobject_cast<QPushButton*>(obj) == pushButtonCurrentlySelectedTutorial)
        {
            return false;
        }
        else if (qobject_cast<QPushButton*>(obj) == ui->pushButtonPrevious)
        {
            ui->pushButtonPrevious->setStyleSheet(buttonUnselectedStyleArrow);
            return true;
        }
        else if (qobject_cast<QPushButton*>(obj) == ui->pushButtonNext)
        {
            ui->pushButtonNext->setStyleSheet(buttonUnselectedStyleArrow);
            return true;
        }
        else if (qobject_cast<QPushButton*>(obj) == ui->pushButtonAccounts)
        {
            ui->pushButtonAccounts->setStyleSheet(buttonUnselectedStyle);
            return true;
        }
        else if (qobject_cast<QPushButton*>(obj) == ui->pushButtonMainWindow)
        {
            ui->pushButtonMainWindow->setStyleSheet(buttonUnselectedStyle);
            return true;
        }
        else if (qobject_cast<QPushButton*>(obj) == ui->pushButtonTransactions)
        {
            ui->pushButtonTransactions->setStyleSheet(buttonUnselectedStyle);
            return true;
        }
        else if (qobject_cast<QPushButton*>(obj) == ui->pushButtonGroups)
        {
            ui->pushButtonGroups->setStyleSheet(buttonUnselectedStyle);
            return true;
        }
        else if (qobject_cast<QPushButton*>(obj) == ui->pushButtonAppearance)
        {
            ui->pushButtonAppearance->setStyleSheet(buttonUnselectedStyle);
            return true;
        }
        else if (qobject_cast<QPushButton*>(obj) == ui->pushButtonStoredFiles)
        {
            ui->pushButtonStoredFiles->setStyleSheet(buttonUnselectedStyle);
            return true;
        }
    }
    return false;
}

void UserGuide::setImageOnLabel(const QString &imagePath)
{
    ui->graphicsViewImage->resetTransform();

    QImage srcImg(imagePath);
    QPixmap imagePixmap = QPixmap::fromImage(srcImg);

    if (!imagePixmap.isNull())
    {
        int w = ui->graphicsViewImage->width()-5;
        int h = ui->graphicsViewImage->height()-5;

        item = new QGraphicsPixmapItem(imagePixmap);
        item->setTransformationMode(Qt::SmoothTransformation);
        scene = new QGraphicsScene(this);

        scene->addItem(item);

        double factorX = w/(static_cast<double>(imagePixmap.width()));
        double factorY = h/(static_cast<double>(imagePixmap.height()));
        ui->graphicsViewImage->scale(factorX, factorY);

        ui->graphicsViewImage->setScene(scene);
    }
}

void UserGuide::highlightButton(QPushButton *button)
{
    pushButtonCurrentlySelectedTutorial = button;

    QString buttonUnselectedStyle = "QPushButton{border: 1px solid gray; border-color: rgba(186, 189, 182, 127); background-color:rgba(0, 0, 0, 0); border-radius: 5px; }";
    QString buttonSelectedStyle = "QPushButton{border: 1px solid gray; border-color: rgba(186, 189, 182, 127); background-color:rgba(135, 190, 193, 128); border-radius: 5px; }";

    ui->pushButtonAccounts->setStyleSheet(buttonUnselectedStyle);
    ui->pushButtonMainWindow->setStyleSheet(buttonUnselectedStyle);
    ui->pushButtonTransactions->setStyleSheet(buttonUnselectedStyle);
    ui->pushButtonGroups->setStyleSheet(buttonUnselectedStyle);
    ui->pushButtonAppearance->setStyleSheet(buttonUnselectedStyle);
    ui->pushButtonStoredFiles->setStyleSheet(buttonUnselectedStyle);

    button->setStyleSheet(buttonSelectedStyle);
}

void UserGuide::updateInfoOnScreen()
{
    if (languageSet)
    {
        std::vector<QString>::iterator textPartIt;
        std::vector<QString>::iterator textExplanationIt;
        std::vector<QString>::iterator textImagePath;
        switch (currentTutorial) {
        case ACCOUNTS:
            {
                 textPartIt = AccountTutorialParts.begin()+AccountPartIndex;
                 ui->labelTutorialPart->setText(*textPartIt);
                 textExplanationIt = AccountPartsExplanation.begin()+AccountPartIndex;
                 ui->textEditExplanation->setText(*textExplanationIt);
                 textImagePath = AccountPartsImagePath.begin()+AccountPartIndex;
                 setImageOnLabel(*textImagePath);
                 highlightButton(ui->pushButtonAccounts);
            }
            break;
        case MAINWINDOW:
            {
                 textPartIt = MainwindowTutorialParts.begin()+MainwindowPartIndex;
                 ui->labelTutorialPart->setText(*textPartIt);
                 textExplanationIt = MainwindowPartsExplanation.begin()+MainwindowPartIndex;
                 ui->textEditExplanation->setText(*textExplanationIt);
                 textImagePath = MainwindowPartsImagePath.begin()+MainwindowPartIndex;
                 setImageOnLabel(*textImagePath);
                 highlightButton(ui->pushButtonMainWindow);
            }
            break;
        case TRANSACTIONS:
            {
                 textPartIt = TransactionsTutorialParts.begin()+TransactionsPartIndex;
                 ui->labelTutorialPart->setText(*textPartIt);
                 textExplanationIt = TransactionsPartsExplanation.begin()+TransactionsPartIndex;
                 ui->textEditExplanation->setText(*textExplanationIt);
                 textImagePath = TransactionsPartsImagePath.begin()+TransactionsPartIndex;
                 setImageOnLabel(*textImagePath);
                 highlightButton(ui->pushButtonTransactions);
            }
            break;
        case GROUPS:
            {
                 textPartIt = GroupsTutorialParts.begin()+GroupsPartIndex;
                 ui->labelTutorialPart->setText(*textPartIt);
                 textExplanationIt = GroupsPartsExplanation.begin()+GroupsPartIndex;
                 ui->textEditExplanation->setText(*textExplanationIt);
                 textImagePath = GroupsPartsImagePath.begin()+GroupsPartIndex;
                 setImageOnLabel(*textImagePath);
                 highlightButton(ui->pushButtonGroups);
            }
            break;
        case APPEARANCE:
            {
                 textPartIt = AppearanceTutorialParts.begin()+AppearancePartIndex;
                 ui->labelTutorialPart->setText(*textPartIt);
                 textExplanationIt = AppearancePartsExplanation.begin()+AppearancePartIndex;
                 ui->textEditExplanation->setText(*textExplanationIt);
                 textImagePath = AppearancePartsImagePath.begin()+AppearancePartIndex;
                 setImageOnLabel(*textImagePath);
                 highlightButton(ui->pushButtonAppearance);
            }
            break;
        case STOREDFILES:
            {
                 textPartIt = StoredfilesTutorialParts.begin()+StoredfilesPartIndex;
                 ui->labelTutorialPart->setText(*textPartIt);
                 textExplanationIt = StoredfilesPartsExplanation.begin()+StoredfilesPartIndex;
                 ui->textEditExplanation->setText(*textExplanationIt);
                 textImagePath = StoredfilesPartsImagePath.begin()+StoredfilesPartIndex;
                 setImageOnLabel(*textImagePath);
                 highlightButton(ui->pushButtonStoredFiles);
            }
            break;
        default:
            break;
        }
    }
}

void UserGuide::setOverallThemeStyleSheet(QString styleSheetString) //Also updates ui to current Language
{
    this->setStyleSheet(styleSheetString);
}

void UserGuide::on_pushButtonPrevious_clicked()
{
    switch (currentTutorial) {
    case ACCOUNTS:
        {
         if (AccountPartIndex > 0)
            AccountPartIndex--;
        }
        break;
    case MAINWINDOW:
        {
         if (MainwindowPartIndex > 0)
            MainwindowPartIndex--;
        }
        break;
    case TRANSACTIONS:
        {
         if (TransactionsPartIndex > 0)
            TransactionsPartIndex--;
        }
        break;
    case GROUPS:
        {
         if (GroupsPartIndex > 0)
            GroupsPartIndex--;
        }
        break;
    case APPEARANCE:
        {
         if (AppearancePartIndex > 0)
            AppearancePartIndex--;
        }
        break;
    case STOREDFILES:
        {
         if (StoredfilesPartIndex > 0)
            StoredfilesPartIndex--;
        }
        break;
    default:
        break;
    }
    this->updateInfoOnScreen();
}

void UserGuide::on_pushButtonNext_clicked()
{
    switch (currentTutorial) {
    case ACCOUNTS:
        {
         if(AccountPartIndex < (AccountTutorialParts.size()-1))
            AccountPartIndex++;
        }
        break;
    case MAINWINDOW:
        {
         if(MainwindowPartIndex < (MainwindowTutorialParts.size()-1))
            MainwindowPartIndex++;
        }
        break;
    case TRANSACTIONS:
        {
         if(TransactionsPartIndex < (TransactionsTutorialParts.size()-1))
            TransactionsPartIndex++;
        }
        break;
    case GROUPS:
        {
         if(GroupsPartIndex < (GroupsTutorialParts.size()-1))
            GroupsPartIndex++;
        }
        break;
    case APPEARANCE:
        {
         if(AppearancePartIndex < (AppearanceTutorialParts.size()-1))
            AppearancePartIndex++;
        }
        break;
    case STOREDFILES:
        {
         if(StoredfilesPartIndex < (StoredfilesTutorialParts.size()-1))
            StoredfilesPartIndex++;
        }
        break;
    default:
        break;
    }
    this->updateInfoOnScreen();
}

void UserGuide::on_pushButtonAccounts_clicked()
{
    currentTutorial = ACCOUNTS;
    this->updateInfoOnScreen();
}

void UserGuide::on_pushButtonMainWindow_clicked()
{
    currentTutorial = MAINWINDOW;
    this->updateInfoOnScreen();
}

void UserGuide::on_pushButtonTransactions_clicked()
{
    currentTutorial = TRANSACTIONS;
    this->updateInfoOnScreen();
}

void UserGuide::on_pushButtonGroups_clicked()
{
    currentTutorial = GROUPS;
    this->updateInfoOnScreen();
}

void UserGuide::on_pushButtonAppearance_clicked()
{
    currentTutorial = APPEARANCE;
    this->updateInfoOnScreen();
}

void UserGuide::on_pushButtonStoredFiles_clicked()
{
    currentTutorial = STOREDFILES;
    this->updateInfoOnScreen();
}


void UserGuide::setCurrentLanguage(Language iLanguage)
{
    currentLanguage = iLanguage;
    if (currentLanguage == ENGLISH)
    {
        this->setWindowTitle(" User Guide");
//----------------------------------------------------------//  Tutorial 1
        //Accounts Part One
        AccountTutorialParts.push_back("1 of 2 - Creating an account");
        AccountPartsImagePath.push_back(":/images/English/Tutorial_1_1.png");
        AccountPartsExplanation.push_back("You can create an account by providing the required information as shown above. "
                                          "If no account has been yet created the window above will appear when you start the app. "
                                          "If you already have an account and want to create a new one you can open the window by clicking on 'File → New'.");
        //Accounts Part Two
        AccountTutorialParts.push_back("2 of 2 - Opening and managing accounts");
        AccountPartsImagePath.push_back(":/images/English/Tutorial_1_2.png");
        AccountPartsExplanation.push_back("If only one account exists, this one will be automatically opened each time you start the app. "
                                          "If you have more than one account, you'll have the option to choose which account to open as shown above. "
                                          "In this window you have options to edit or delete the existing accounts or if you want you can also create a new account. "
                                          "To open the window above, click on 'File → Open'.");

//----------------------------------------------------------//  Tutorial 2
        //MainWindow Part One
        MainwindowTutorialParts.push_back("1 of 5 - Main window");
        MainwindowPartsImagePath.push_back(":/images/English/Tutorial_2_1.png");
        MainwindowPartsExplanation.push_back("In the main window you have access to all transactions you have entered on a yearly basis. "
                                             "These are organized in monthly lists and groups lists. "
                                             "You can navigate through the years, months and groups by using the corresponding arrow buttons.");
        //MainWindow Part Two A
        MainwindowTutorialParts.push_back("2 of 5 - Monthly list");
        MainwindowPartsImagePath.push_back(":/images/English/Tutorial_2_2A.png");
        MainwindowPartsExplanation.push_back("The list shows the transactions corresponding to the selected year and month. "
                                             "Below the list you have the options add, edit or delete transactions to the selected year. "
                                             "Below the options you can also see the monthly and yearly balances.");
        //MainWindow Part Two B
        MainwindowTutorialParts.push_back("3 of 5 - Monthly charts");
        MainwindowPartsImagePath.push_back(":/images/English/Tutorial_2_2B.png");
        MainwindowPartsExplanation.push_back("The bars in the chart represent the monthly amounts for the selected year. "
                                             "Each month consists of two bars, being the monthly income the bar on the left and the expenses on the right. "
                                             "Any month can also be selected by clicking on the corresponding area of the chart. ");
        //MainWindow Part Three A
        MainwindowTutorialParts.push_back("4 of 5 - Groups lists");
        MainwindowPartsImagePath.push_back(":/images/English/Tutorial_2_3.png");
        MainwindowPartsExplanation.push_back("This list contains all transactions belonging to a specific group or category. "
                                             "Use the button 'Income/Expenses' to switch between type of transactions and the arrows to change the selected group. ");
        //MainWindow Part Three B
        MainwindowTutorialParts.push_back("5 of 5 - Pie chart");
        MainwindowPartsImagePath.push_back(":/images/English/Tutorial_2_3.png");
        MainwindowPartsExplanation.push_back("The pie chart shows the percentage and amount of the selected group. "
                                             "Click on the chart to be able to select any specific group directly.");

//----------------------------------------------------------//  Tutorial 3
        //Transactions Part One
        TransactionsTutorialParts.push_back("1 of 3 - Adding transactions");
        TransactionsPartsImagePath.push_back(":/images/English/Tutorial_3_1.png");
        TransactionsPartsExplanation.push_back("To add a transaction click on the corresponding button below the monthly list. "
                                               "Please notice that transactions will be added to the current selected year. ");
        //Transactions Part Two
        TransactionsTutorialParts.push_back("2 of 3 - Adding transactions");
        TransactionsPartsImagePath.push_back(":/images/English/Tutorial_3_2.png");
        TransactionsPartsExplanation.push_back("Each transaction requires a name, date and amount. "
                                               "Repetition options can be set to every week, every two weeks or once in a month. "
                                               "If a repetition option with a past month or day was selected, the corresponding copies will be automatically added until present day. "
                                               "If the transaction was added to a past year, this will be repeated until the end of that year. "
                                               "A notification will appear each time transactions were added automatically.");
        //Transactions Part Three
        TransactionsTutorialParts.push_back("3 of 3 - Editing and deleting transactions");
        TransactionsPartsImagePath.push_back(":/images/English/Tutorial_3_3.png");
        TransactionsPartsExplanation.push_back("To edit or delete a transaction first select a transaction from the monthly list, "
                                               "then press either 'Edit item' button or 'Delete item' respectively. "
                                               "Only one transaction can be edited at a time.  ");

//----------------------------------------------------------//  Tutorial 4
        //Groups Part One
        GroupsTutorialParts.push_back("1 of 1 - Managing Groups");
        GroupsPartsImagePath.push_back(":/images/English/Tutorial_4_1.png");
        GroupsPartsExplanation.push_back("Groups are used to classify transactions. "
                                         "To manage groups click on 'Edit' on the main window and select the type of groups you would like to change. "
                                         "Here you can add a new group, change the name of an existing group or delete a group. "
                                         "When deleting a group, all transactions belonging to that group will change to 'Not classified'. "
                                         "A notification will then appear showing how many transactions in each year belong to the group being deleted. ");

//----------------------------------------------------------//  Tutorial 5
        //Appearance Part One
        AppearanceTutorialParts.push_back("1 of 4 - Appearance");
        AppearancePartsImagePath.push_back(":/images/English/Tutorial_5_1.png");
        AppearancePartsExplanation.push_back("Here you can change the look of the main elements. "
                                             "To open the appearance window click on 'Options → Appearance' on the main window. "
                                             "You can select any of the presets or customize your own set of colors. "
                                             "Just click on any rectangle showing the current color of an element to choose a new one. "
                                             "The first time you change a color, a copy of the current preset will be made and set as your custom preset.");
        //Appearance Part Two
        AppearanceTutorialParts.push_back("2 of 4 - Monthly charts");
        AppearancePartsImagePath.push_back(":/images/English/Tutorial_5_2.png");
        AppearancePartsExplanation.push_back("Choose here a color for the monthly income and expenses bars. "
                                             "A different set can be chosen for not selected months. "
                                             "The background can also be changed. ");
        //Appearance Part Three
        AppearanceTutorialParts.push_back("3 of 4 - Groups chart");
        AppearancePartsImagePath.push_back(":/images/English/Tutorial_5_3.png");
        AppearancePartsExplanation.push_back("Choose here the  colors for the income and expenses groups respectively. "
                                             "Notice that the percentage and amount at the center will have the same color as the selected group in the pie chart. "
                                             "Hence the option to choose a different background color "
                                             "for each type of transactions.");
        //Appearance Part Four
        AppearanceTutorialParts.push_back("4 of 4 - Others");
        AppearancePartsImagePath.push_back(":/images/English/Tutorial_5_4.png");
        AppearancePartsExplanation.push_back("In the last section a theme can be selected, this changes the window background and letters. "
                                             "A color for the income amounts in the monthly list can also be chosen. "
                                             "Finally, decide if the monthly amounts below should be shown in color, notice that the colors will be the same as in the corresponding bars.");

//----------------------------------------------------------//  Tutorial 6
        //Stored files
        StoredfilesTutorialParts.push_back("1 of 1 - Stored Files");
        StoredfilesPartsImagePath.push_back(":/images/English/Tutorial_6_1.png");
        StoredfilesPartsExplanation.push_back("Keibo-MoneyTracker will create a folder in the home directory. "
                                              "Inside, a folder for each account will be created. "
                                              "Please do not modify any of these folders and/or files. Doing so may cause information to be unrecoverable.");

//----------------------------------------------------------//
        this->languageSet=true;
    }

    else if (currentLanguage == SPANISH)
    {
        this->setWindowTitle(" Guia de usuario");
        ui->pushButtonAccounts->setText("Cuentas");
        ui->pushButtonMainWindow->setText("Ventana principal");
        ui->pushButtonTransactions->setText("Transacciones");
        ui->pushButtonGroups->setText("Grupos");
        ui->pushButtonAppearance->setText("Apariencia");
        ui->pushButtonStoredFiles->setText("Archivos");
        //----------------------------------------------------------//  Tutorial 1
                //Accounts Part One
                AccountTutorialParts.push_back("1 de 2 - Crear una cuenta");
                AccountPartsImagePath.push_back(":/images/Spanish/Tutorial_1_1_ES.png");
                AccountPartsExplanation.push_back("Usa la ventana que se muestra en la imagen para crear una cuenta e introduce la información requerida. "
                                                  "En caso de que no existan cuentas, la ventana se abrirá automáticamente cada vez que inicies la aplicación. "
                                                  "Si ya tienes una cuenta y deseas crear una nueva abre la ventana haciendo clic en 'Archivo → Nuevo'.");
                //Accounts Part Two
                AccountTutorialParts.push_back("2 de 2 - Seleccionar y administrar cuentas");
                AccountPartsImagePath.push_back(":/images/Spanish/Tutorial_1_2_ES.png");
                AccountPartsExplanation.push_back("Si solo existe una cuenta, ésta se abrirá automáticamente cuando inicies la aplicación. "
                                                  "Si dos o mas cuentas existen, tendrás la opción de elejir con que cuenta deseas continuar como se muestra en la imágen. "
                                                  "En la ventana también se tienen opciones para editar o eliminar una de las cuentas existentes. "
                                                  "Una cuenta nueva puede también ser creada. \n"
                                                  "Para abrir la ventana haz clic en 'Archivo → Abrir'.");

        //----------------------------------------------------------//  Tutorial 2
                //MainWindow Part One
                MainwindowTutorialParts.push_back("1 de 5 - Ventana principal");
                MainwindowPartsImagePath.push_back(":/images/Spanish/Tutorial_2_1_ES.png");
                MainwindowPartsExplanation.push_back("En la ventana principal se tiene acceso a todas las transacciones que se han introducido y pertenecen al año que se muestra en pantalla. "
                                                     "Éstas están organizadas en listas mensuales y listas de grupos. "
                                                     "Cambia el año, mes o grupo seleccionado usando las flechas correspondientes. ");
                //MainWindow Part Two A
                MainwindowTutorialParts.push_back("2 de 5 - Listas mensuales");
                MainwindowPartsImagePath.push_back(":/images/Spanish/Tutorial_2_2A_ES.png");
                MainwindowPartsExplanation.push_back("En la lista se encuentran las transacciones correspondientes al año y mes seleccionados. "
                                                     "Debajo de la lista tienes opciones para añadir, editar o eliminar transacciones respectivamente. "
                                                     "Debajo de las opciones se encuentran los balances del mes y año seleccionados.");
                //MainWindow Part Two B
                MainwindowTutorialParts.push_back("3 de 5 - Graficas mensuales");
                MainwindowPartsImagePath.push_back(":/images/Spanish/Tutorial_2_2B_ES.png");
                MainwindowPartsExplanation.push_back("Las barras en la gráfica representan los montos mensuales en el año seleccionado. "
                                                     "Cada mes consiste de dos barras, siendo ingresos la barra izquierda y egresos la derecha. "
                                                     "El mes también puede ser seleccionado desde la gráfica haciendo click en el área que corresponde. ");
                //MainWindow Part Three A
                MainwindowTutorialParts.push_back("4 de 5 - Listas de grupos");
                MainwindowPartsImagePath.push_back(":/images/Spanish/Tutorial_2_3_ES.png");
                MainwindowPartsExplanation.push_back("Esta lista contiene las transacciones que pertenecen a un grupo o categoría en específico. "
                                                     "Usa el botón 'Ingresos/Egresos' para cambiar el tipo de transacciones y las flechas para cambiar el grupo seleccionado. ");
                //MainWindow Part Three B
                MainwindowTutorialParts.push_back("5 de 5 - Gráfica de grupos");
                MainwindowPartsImagePath.push_back(":/images/Spanish/Tutorial_2_3_ES.png");
                MainwindowPartsExplanation.push_back("El gráfico circular muestra el porcentaje y el monto que el grupo seleccionado ocupa. "
                                                     "Haz clic sobre el gráfico para seleccionar un grupo en específico directamente. ");

        //----------------------------------------------------------//  Tutorial 3
                //Transactions Part One
                TransactionsTutorialParts.push_back("1 de 3 - Añadir transacciones");
                TransactionsPartsImagePath.push_back(":/images/Spanish/Tutorial_3_1_ES.png");
                TransactionsPartsExplanation.push_back("Para añadir ingresos o egresos presiona el botón correspondiente debajo de la lista mensual. "
                                                       "Note que las transacciones se añadirán al año seleccionado en la ventana principal. ");
                //Transactions Part Two
                TransactionsTutorialParts.push_back("2 de 3 - Añadir transacciones");
                TransactionsPartsImagePath.push_back(":/images/Spanish/Tutorial_3_2_ES.png");
                TransactionsPartsExplanation.push_back("Cada transacción requiere un nombre, fecha y monto. "
                                                       "La opción de repetición puede ser cada semana, cada dos semanas o una vez al mes. "
                                                       "Si una transaccion se añade para el año presente con un mes o día en el pasado "
                                                       "las copias correspondientes serán añadidas hasta la fecha actual. "
                                                       "En caso de que el año sea anterior al actual, la transacción se repetirá hasta el final de ese año. "
                                                       "Una notificación aparecerá cuando transacciones sean añadidas automáticamente. ");
                //Transactions Part Three
                TransactionsTutorialParts.push_back("3 de 3 - Editando y eliminando transacciones");
                TransactionsPartsImagePath.push_back(":/images/Spanish/Tutorial_3_3_ES.png");
                TransactionsPartsExplanation.push_back("Para eliminar o editar transacciones, seleccione primero una transacción de la lista y haga click sobre el botón correspondiente. "
                                                       "Solo una transacción puede ser editada a la vez. ");

        //----------------------------------------------------------//  Tutorial 4
                //Groups Part One
                GroupsTutorialParts.push_back("1 de 1 - Editando grupos");
                GroupsPartsImagePath.push_back(":/images/Spanish/Tutorial_4_1_ES.png");
                GroupsPartsExplanation.push_back("Para poder editar grupos haga clic en 'Editar' en la parte superior de la ventana principal y seleccione el tipo de grupos a cambiar. "
                                                 "Aqui se puede añadir grupos nuevos, cambiar el nombre de los existentes o borrar grupos. "
                                                 "Al eliminar un grupo, todas las transacciones que pertenecen a ese grupo cambiarán a 'Sin clasificar'. "
                                                 "Una notificación aparecerá mostrando cuantas transacciones en cada año pertenecen al grupo a eliminar. ");

        //----------------------------------------------------------//  Tutorial 5
                //Appearance Part One
                AppearanceTutorialParts.push_back("1 de 4 - Apariencia");
                AppearancePartsImagePath.push_back(":/images/Spanish/Tutorial_5_1_ES.png");
                AppearancePartsExplanation.push_back("Aqui puedes cambiar el color de los elementos principales. "
                                                     "Para abrir la ventana haz clic en 'Opciones → Apariencia'. "
                                                     "Es posible elejir una de las preselecciones o definir un conjunto de colores propio. "
                                                     "Haz clic en cualquier rectángulo con el color actual de un elemento para elejir un color nuevo. "
                                                     "Al cambiar la primera vez uno de los colores se hará una copia de la preselección elejida, "
                                                     "ésta se establecerá como la preselección personalizada.");
                //Appearance Part Two
                AppearanceTutorialParts.push_back("2 de 4 - Gráficas mensuales");
                AppearancePartsImagePath.push_back(":/images/Spanish/Tutorial_5_2_ES.png");
                AppearancePartsExplanation.push_back("Seleccione aqui un color para las barras mensuales de ingresos y egresos. "
                                                     "Colores diferentes pueden ser elegidos para meses no seleccionados. "
                                                     "El color de fondo para las graficas mensuales también puede ser cambiado");
                //Appearance Part Three
                AppearanceTutorialParts.push_back("3 de 4 - Gráficas de grupos");
                AppearancePartsImagePath.push_back(":/images/Spanish/Tutorial_5_3_ES.png");
                AppearancePartsExplanation.push_back("Selecciona aquí el color para los grupos de ingresos y egresos respectivamente. "
                                                     "Nota que el porcentage y monto en el centro serán del mismo color que el del grupo seleccionado "
                                                     "en la gráfica circular, debido a esto el color de fondo del centro de la gráfica puede ser diferente "
                                                     "para ingresos y egresos.");
                //Appearance Part Four
                AppearanceTutorialParts.push_back("4 de 4 - Otros");
                AppearancePartsImagePath.push_back(":/images/Spanish/Tutorial_5_4_ES.png");
                AppearancePartsExplanation.push_back("En la última sección se puede elegir entre temas oscuro y claro, esto cambia el fondo de las ventanas y las letras. "
                                                     "También se puede elegir un color para los montos de ingresos en la lista mensual. "
                                                     "Por último, los montos mensuales en la parte inferior pueden mostraste en color, éstos serán igual a los de las "
                                                     "barras correspondientes. ");

        //----------------------------------------------------------//  Tutorial 6
                //Stored files
                StoredfilesTutorialParts.push_back("1 de 1 - Archivos guardados en el sistema");
                StoredfilesPartsImagePath.push_back(":/images/Spanish/Tutorial_6_1_ES.png");
                StoredfilesPartsExplanation.push_back("Keibo-MoneyTracker creará una carpeta en el directorio personal. "
                                                      "Dentro de ella se creará una carpeta por cada cuenta existente. "
                                                      "Por favor no modifiques ninguna de las carpetas o archivos dentro de éstas, "
                                                      "al hacerlo podría causar que información sea inrecuperable. ");

        //----------------------------------------------------------//
                this->languageSet=true;
    }

    else if (currentLanguage == GERMAN)
    {
        this->setWindowTitle(" Benutzererklärung");
        ui->pushButtonAccounts->setText("Konten");
        ui->pushButtonMainWindow->setText("Hauptfenster");
        ui->pushButtonTransactions->setText("Transaktionen");
        ui->pushButtonGroups->setText("Gruppen");
        ui->pushButtonAppearance->setText("Ansicht");
        ui->pushButtonStoredFiles->setText("Gespeicherte Dateien");
        //----------------------------------------------------------//  Tutorial 1
                //Accounts Part One
                AccountTutorialParts.push_back("1 von 2 - Konto erstellen");
                AccountPartsImagePath.push_back(":/images/German/Tutorial_1_1_DE.png");
                AccountPartsExplanation.push_back("Erstelle ein Konto mit den vorhandenen Informationen. "
                                                  "Wenn noch kein Konto vorhanden ist, erscheint das Fenster beim Starten der App. "
                                                  "Wenn bereits ein Konto vorhanden ist und ein weiterer erstellt werden soll, ist das Fenster unter 'Datei → Neu' zu finden.");
                //Accounts Part Two
                AccountTutorialParts.push_back("2 von 2 - Konto öffnen und bearbeiten");
                AccountPartsImagePath.push_back(":/images/German/Tutorial_1_2_DE.png");
                AccountPartsExplanation.push_back("Existiert nur ein Konto, öffnet sich dieses automatisch beim Starten der App. "
                                                  "Ist mehr als ein Konto vorhanden, erscheint das Fenster und kann entschieden werden welches Konto geöffnet wird. "
                                                  "Vorhandene Konten können bearbeitet und gelöscht werden oder ein weiteres Konto erstellt werden. "
                                                  "Mit 'Datei → Öffnen' öffnet sich der hier angezeigte Kontomanager.");

        //----------------------------------------------------------//  Tutorial 2
                //MainWindow Part One
                MainwindowTutorialParts.push_back("1 von 5 - Hauptfenster");
                MainwindowPartsImagePath.push_back(":/images/German/Tutorial_2_1_DE.png");
                MainwindowPartsExplanation.push_back("Im Hauptfenster sind Transaktionen vorhanden, die jährlich eingetragen wurden. "
                                                     "Diese sind organisiert nach Monats- und Gruppenlisten. "
                                                     "Navigiere mit den dazugehörigen Pfeiltasten die Jahre, Monate und Gruppen.");
                //MainWindow Part Two A
                MainwindowTutorialParts.push_back("2 von 5 - Monatlichen Listen");
                MainwindowPartsImagePath.push_back(":/images/German/Tutorial_2_2A_DE.png");
                MainwindowPartsExplanation.push_back("Hier sind die monatlichen Transaktionen vorhanden. "
                                                     "Unter der Liste sind die Optionen Einkommen, Ausgabe, Ändern oder Löschen für die Transaktionen vorhanden. "
                                                     "Unten sind die monaltichen und jährlichen Einkommen und Ausgaben zu sehen.");
                //MainWindow Part Two B
                MainwindowTutorialParts.push_back("3 von 5 - Balkendiagramm");
                MainwindowPartsImagePath.push_back(":/images/German/Tutorial_2_2B_DE.png");
                MainwindowPartsExplanation.push_back("Das Balkendiagramm zeigt den monatlichen Betrag des Jahres. "
                                                     "Für jeden Monat repräsentiert der linke Balken das Einkommen und der rechte Balken die Ausgaben. "
                                                     "Wähle den Monat aus durch einen Klick auf dem Diagramm. ");
                //MainWindow Part Three A
                MainwindowTutorialParts.push_back("4 von 5 - Gruppen Listen");
                MainwindowPartsImagePath.push_back(":/images/German/Tutorial_2_3_DE.png");
                MainwindowPartsExplanation.push_back("Alle Transaktionen des ausgwählten Jahres und die dazugehörigen Gruppen werden angezeigt. "
                                                     "Benutze die Taste 'Einkommen/Ausgaben' um zwischen den Transaktionen zu wechseln "
                                                     "und benutze die Pfeiltaste, um zwischen den einzelnen Gruppen zu wechseln.");
                //MainWindow Part Three B
                MainwindowTutorialParts.push_back("5 von 5 - Kreisdiagramm");
                MainwindowPartsImagePath.push_back(":/images/German/Tutorial_2_3_DE.png");
                MainwindowPartsExplanation.push_back("Das Kreisdiagramm zeigt den Anteil der ausgewählten Gruppe. "
                                                     "Klicke auf das Kreisdiagramm, um das Menü zu sehen und eine spezififsche Gruppe direkt auszuwählen.");

        //----------------------------------------------------------//  Tutorial 3
                //Transactions Part One A
                TransactionsTutorialParts.push_back("1 von 3 - Transaktionen hinzufügen");
                TransactionsPartsImagePath.push_back(":/images/German/Tutorial_3_1_DE.png");
                TransactionsPartsExplanation.push_back("Klicke auf die dazugehörige Taste im Hauptfenster um Einkommen oder Ausgaben einzutragen. "
                                                       "Die Transaktion wird zu dem dazu ausgewähltem Jahr hinzugefügt.");
                //Transactions Part One B
                TransactionsTutorialParts.push_back("2 von 3 - Transaktionen hinzufügen");
                TransactionsPartsImagePath.push_back(":/images/German/Tutorial_3_2_DE.png");
                TransactionsPartsExplanation.push_back("Jede Transaktion benötigt Namen, Datum und Betrag. "
                                                       "Wiederholungen der Transaktionen können wöchentlich, jede zwei Wochen oder monatlich eingestellt werden. "
                                                       "Wurde eine Wiederholung mit einem verganenem Datum ausgwählt, wird die Transaktion automatisch bis zu dem aktuellen Tag wiederholt. "
                                                       "Wurde die Transaktion zu einem verganenem Jahr hinzugefügt, wiederholt sie sich bis zum Ende des verganenem Jahres. "
                                                       "Eine Benachrichtigung erscheint, wenn neue Transaktionen hinzugefügt werden.");
                //Transactions Part Two
                TransactionsTutorialParts.push_back("3 von 3 - Transaktionen ändern und löschen");
                TransactionsPartsImagePath.push_back(":/images/German/Tutorial_3_3_DE.png");
                TransactionsPartsExplanation.push_back("Wähle eine Transaktion in der Monatsliste aus. "
                                                       "Drücke entweder 'Ändern' oder 'Löschen'. "
                                                       "Nur eine Transaktion kann gleichzeitig bearbeitet werden.");

        //----------------------------------------------------------//  Tutorial 4
                //Groups Part One
                GroupsTutorialParts.push_back("1 von 1 - Gruppen bearbeiten");
                GroupsPartsImagePath.push_back(":/images/German/Tutorial_4_1_DE.png");
                GroupsPartsExplanation.push_back("Zum klassifizieren der Transaktionen können Gruppen ausgwählt werden. "
                                                 "Zum Bearbeiten der Gruppe drücke 'Bearbeiten' auf dem Hauptfenster und wähle die Gruppe aus, die verändert werden soll. "
                                                 "Neue Gruppen können hinzugefügt, namentlich verändert oder gelöscht werden. "
                                                 "Beim Löschen einer Gruppe werden alle Transaktionen die zu dieser Gruppe gehören zu 'Nicht klassifiziert' verändert. "
                                                 "Wird eine Gruppe gelöscht erscheint, die Informaiton mit der Anzahl der Transaktionen in jedem jahr, die zu dieser Gruppe gehören.");

        //----------------------------------------------------------//  Tutorial 5
                //Appearance Part One
                AppearanceTutorialParts.push_back("1 von 4 - Ansicht");
                AppearancePartsImagePath.push_back(":/images/German/Tutorial_5_1_DE.png");
                AppearancePartsExplanation.push_back("Das Design der Hauptelemente kann verändert werden. "
                                                     "Klicke auf 'Optionen → Ansicht', um das Erscheinungsbild zu verändern. "
                                                     "Es können bereits vorhandene Erscheinungsbilder ausgwählt oder ein eigenes erstellt werden. "
                                                     "Veränderst du das erste Mal eine Farbe wird eine Kopie des entworfenen Erscheinungsbild erstellt und als persönliches Erscheinunngsbild gespeichert.");
                //Appearance Part Two
                AppearanceTutorialParts.push_back("2 von 4 - Balkendiagramm");
                AppearancePartsImagePath.push_back(":/images/German/Tutorial_5_2_DE.png");
                AppearancePartsExplanation.push_back("Farben für den ausgewählten Monat und den nicht ausgewählten Monat für monaltiches Einkommen und Ausgaben können gewählt werden. "
                                                     "Klicke auf das Rechteck mit der bereits vorhandenen Farbe und wähle eine neue Farbe aus. "
                                                     "Der Hintergrund von dem monatlichen Diagramm kann auch verändert werden. ");
                //Appearance Part Three
                AppearanceTutorialParts.push_back("3 von 4 - Kreisdiagramm");
                AppearancePartsImagePath.push_back(":/images/German/Tutorial_5_3_DE.png");
                AppearancePartsExplanation.push_back("Farben für die ausgwählte Gruppe und die nicht ausgewählte Gruppe für Einkommen und Ausgabe können gewählt werden. "
                                                     "Eine andere Hintergrundfarbe kann für jede Transaktion ausgwählt werden. ");
                //Appearance Part Four
                AppearanceTutorialParts.push_back("4 von 4 - Anderen");
                AppearancePartsImagePath.push_back(":/images/German/Tutorial_5_4_DE.png");
                AppearancePartsExplanation.push_back("Folgende Optionen sind vorhanden:"
                                                     "Wähle zwischen einem hellen oder dunklen Thema. "
                                                     "Entscheide, ob die monatlichen Beiträge in Farbe erscheinen sollen. "
                                                     "Die selben Farben werden in den dazugehörigen Balken angezeigt.");

        //----------------------------------------------------------//  Tutorial 6
                //Stored files
                StoredfilesTutorialParts.push_back("1 von 1 - Gespeicherte Dateien");
                StoredfilesPartsImagePath.push_back(":/images/German/Tutorial_6_1_DE.png");
                StoredfilesPartsExplanation.push_back("Keibo-MoneyTracker kreiert einen eigenen Ordner in dem persönlichen Ordner. "
                                                      "Darin wird ein Ordner für jedes Konto erstellt mit allen dazugehörigen Daten. "
                                                      "Bitte verändere diese Ordner nicht, weil dies zu unkorrekten Angaben führen kann. ");

        this->languageSet=true;
    }

    this->updateInfoOnScreen();
}
