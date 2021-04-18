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

#include "accountdialog.h"
#include "ui_accountdialog.h"
#include <QFileDialog>
#include <iostream>
#include <QKeyEvent>

AccountImageView::AccountImageView(QWidget * parent) : QGraphicsView(parent)
{

}

void AccountImageView::wheelEvent(QWheelEvent *event)
{
    double scaleFactor = 1.10;

    QPointF oldPos =  mapToScene(event->position().toPoint());
    if (event->angleDelta().y() > 0){
        scale(scaleFactor, scaleFactor);
    } else {
        scale(1/scaleFactor, 1/scaleFactor);
    }
    QPointF newPos =  mapToScene(event->position().toPoint());

    QPointF delta = newPos-oldPos;
    this->translate(delta.x(), delta.y());
}

void AccountImageView::mousePressEvent(QMouseEvent* event)
{
    if (event->button() & Qt::LeftButton)
    {
        leftMouseButtonPressed = true;
        previousX = event->x();
        previousY = event->y();
    }
}

void AccountImageView::mouseMoveEvent(QMouseEvent* event)
{
    if (leftMouseButtonPressed)
    {
        setTransformationAnchor(QGraphicsView::NoAnchor);
        QPointF previousPoint = mapToScene(previousX, previousY);
        QPointF currentPoint = mapToScene(event->pos());
        QPointF translationPoint = currentPoint-previousPoint;
        translate(translationPoint.x(), translationPoint.y());
        previousX = event->x();
        previousY = event->y();
    }
}

void AccountImageView::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() & Qt::LeftButton)
    {
        leftMouseButtonPressed = false;
    }
}


AccountDialog::AccountDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AccountDialog)
{
    ui->setupUi(this);
    ui->buttonRotate->setIcon(QIcon(":/images/RotationIcon.png"));
    QString buttonStyle = "QPushButton{border: 1px solid white; border-color: rgba(186, 189, 182, 127); background-color:rgba(0, 0, 0, 0);}";
    ui->buttonRotate->setStyleSheet(buttonStyle);

    ui->buttonDeleteImage->setIcon(QIcon(":/images/ResetImageIcon.png"));
    QString buttonDeleteStyle = "QPushButton{border: 1px solid white; border-color: rgba(186, 189, 182, 127); background-color:rgba(0, 0, 0, 0);}";
    ui->buttonDeleteImage->setStyleSheet(buttonDeleteStyle);

    ui->changeFormatButton->setIcon(QIcon(":/images/FormatIcon.png"));
    QString buttonFormatStyle = "QPushButton{border: 1px solid white; border-color: rgba(186, 189, 182, 127); background-color:rgba(0, 0, 0, 0);}";
    ui->changeFormatButton->setStyleSheet(buttonFormatStyle);

    ui->buttonIconLeft->setIcon(QIcon(":/images/ArrowLeft.png"));
    QString buttonIconLeftStyle = "QPushButton{border: 1px solid white; border-color: rgba(186, 189, 182, 127); background-color:rgba(0, 0, 0, 0);}";
    ui->buttonIconLeft->setStyleSheet(buttonIconLeftStyle);

    ui->buttonIconRight->setIcon(QIcon(":/images/ArrowRight.png"));
    QString buttonIconRightStyle = "QPushButton{border: 1px solid white; border-color: rgba(186, 189, 182, 127); background-color:rgba(0, 0, 0, 0);}";
    ui->buttonIconRight->setStyleSheet(buttonIconRightStyle);

    listOfImagePaths.push_back(":/images/UserIcon.png");

    currentLayoutFormat = ImageLayoutFormat::DEFAULT;

    this->ui->textEditAccountName->setEnabled(true);
    this->ui->textEditAccountName->setTabChangesFocus(true);
    this->ui->accountGraphicsView->setFocusPolicy(Qt::NoFocus);

    this->ui->textEditAccountName->installEventFilter(this);
    this->ui->buttonIconLeft->installEventFilter(this);
    this->ui->buttonIconRight->installEventFilter(this);
    this->ui->buttonCreateAccount->installEventFilter(this);
    this->ui->selectImageButton->installEventFilter(this);
    this->ui->comboBoxCurrency->installEventFilter(this);
    this->ui->comboBoxLanguage->installEventFilter(this);


    this->setFixedSize(this->width(), this->height());

    this->ui->textEditAccountName->setWordWrapMode(QTextOption::NoWrap);
    this->ui->textEditAccountName->setStyleSheet("QScrollBar {height:5px;}");
    this->ui->textEditAccountName->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    this->ui->accountGraphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->ui->accountGraphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->ui->textEditAccountName->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
}

AccountDialog::~AccountDialog()
{
    delete ui;
    delete item;
    delete scene;
}

void AccountDialog::setOverallThemeStyleSheet(QString styleSheetString, bool usingDarkTheme)
{
    this->setStyleSheet(styleSheetString);
    this->ui->buttonCreateAccount->updateColorTheme(usingDarkTheme);
    this->ui->selectImageButton->updateColorTheme(usingDarkTheme);
    this->ui->textEditAccountName->updateColorTheme(usingDarkTheme);
    this->ui->comboBoxCurrency->updateColorTheme(usingDarkTheme);
    this->ui->comboBoxLanguage->updateColorTheme(usingDarkTheme);
}

bool AccountDialog::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::KeyPress)
    {
        if (qobject_cast<QTextEdit*>(obj) == ui->textEditAccountName)
        {
            QKeyEvent* key = static_cast<QKeyEvent*>(event);
            if (key->key() == Qt::Key_Enter || (key->key()==Qt::Key_Return))
            {
                dialogAccountName = ui->textEditAccountName->toPlainText().toStdString();
                dialogAccountLanguage = ui->comboBoxLanguage->currentIndex();
                dialogAccountCurrency = ui->comboBoxCurrency->currentIndex();
                bool NameAlreadyExists = false;
                std::vector<std::string>::iterator itAccountsNames;
                for (itAccountsNames = listOfForbiddenAccountNames.begin(); itAccountsNames != listOfForbiddenAccountNames.end(); ++itAccountsNames)
                {
                    if (dialogAccountName == *itAccountsNames){
                        NameAlreadyExists = true;
                    }
                }
                if (NameAlreadyExists == false)
                {
                    if (dialogAccountName.empty())
                    {
                        const Language iLanguage = static_cast<Language>(dialogAccountLanguage);
                        if (iLanguage == ENGLISH){
                            this->ui->labelInfo->setText("Please enter a name.");
                        } else if (iLanguage == GERMAN){
                            this->ui->labelInfo->setText("Bitte geben Sie einen Name ein.");
                        } else if (iLanguage == SPANISH) {
                            this->ui->labelInfo->setText("Por favor introduzca un nombre.");
                        }
                    } else {
                        creationConfirmed = true;
                        this->close();
                    }
                } else {
                    this->ui->labelInfo->setWordWrap(true);
                    const Language iLanguage = static_cast<Language>(dialogAccountLanguage);
                    if (iLanguage == ENGLISH){
                        this->ui->labelInfo->setText("An Account with that name already exists, please choose a different name.");
                    } else if (iLanguage == GERMAN){
                        this->ui->labelInfo->setText("Das Konto existiert bereits, bitte geben Sie einen neuen Name ein.");
                    } else if (iLanguage == SPANISH) {
                        this->ui->labelInfo->setText("Una cuenta con ese nombre ya existe, por favor seleccione uno diferente.");
                    }
                }
                return true;
            }
        }
    }
    else if (event->type() == QEvent::Enter)
    {
        if (qobject_cast<QPushButton*>(obj) == ui->buttonIconLeft)
        {
            QString IconLeftStyle = "QPushButton{border: 1px solid white; border-color: rgba(186, 189, 182, 127); background-color:rgba(128, 128, 128, 60); }";
            ui->buttonIconLeft->setStyleSheet(IconLeftStyle);
            return true;
        }
        else if (qobject_cast<QPushButton*>(obj) == ui->buttonIconRight)
        {
            QString IconRightStyle = "QPushButton{border: 1px solid white; border-color: rgba(186, 189, 182, 127); background-color:rgba(128, 128, 128, 60); }";
            ui->buttonIconRight->setStyleSheet(IconRightStyle);
            return true;
        }
        else if (qobject_cast<QWidget*>(obj) == ui->buttonCreateAccount) {
            this->ui->buttonCreateAccount->setColorForEnterEvent();
        }
        else if (qobject_cast<QWidget*>(obj) == ui->selectImageButton) {
            this->ui->selectImageButton->setColorForEnterEvent();
        }
        else if (qobject_cast<QWidget*>(obj) == ui->textEditAccountName) {
            this->ui->textEditAccountName->setColorForEnterEvent();
        }
        else if (qobject_cast<QWidget*>(obj) == ui->comboBoxCurrency) {
            this->ui->comboBoxCurrency->setColorForEnterEvent();
        }
        else if (qobject_cast<QWidget*>(obj) == ui->comboBoxLanguage) {
            this->ui->comboBoxLanguage->setColorForEnterEvent();
        }
    }
    else if (event->type() == QEvent::Leave)
    {
        if (qobject_cast<QPushButton*>(obj) == ui->buttonIconLeft)
        {
            QString IconLeftStyle = "QPushButton{border: 1px solid white; border-color: rgba(186, 189, 182, 127); background-color:rgba(0, 0, 0, 0); }";
            ui->buttonIconLeft->setStyleSheet(IconLeftStyle);
            return true;
        }
        else if (qobject_cast<QPushButton*>(obj) == ui->buttonIconRight)
        {
            QString IconRightStyle = "QPushButton{border: 1px solid white; border-color: rgba(186, 189, 182, 127); background-color:rgba(0, 0, 0, 0); }";
            ui->buttonIconRight->setStyleSheet(IconRightStyle);
            return true;
        }
        else if (qobject_cast<QWidget*>(obj) == ui->buttonCreateAccount) {
            this->ui->buttonCreateAccount->setColorForLeaveEvent();
        }
        else if (qobject_cast<QWidget*>(obj) == ui->selectImageButton) {
            this->ui->selectImageButton->setColorForLeaveEvent();
        }
        else if (qobject_cast<QWidget*>(obj) == ui->textEditAccountName) {
            this->ui->textEditAccountName->setColorForLeaveEvent();
        }
        else if (qobject_cast<QWidget*>(obj) == ui->comboBoxCurrency) {
            this->ui->comboBoxCurrency->setColorForLeaveEvent();
        }
        else if (qobject_cast<QWidget*>(obj) == ui->comboBoxLanguage) {
            this->ui->comboBoxLanguage->setColorForLeaveEvent();
        }
    }
    if (event->type() == QEvent::MouseButtonPress)
    {
        if (qobject_cast<QWidget*>(obj) == ui->buttonCreateAccount) {
            this->ui->buttonCreateAccount->setColorForMouseButtonPressEvent();
        }
        else if (qobject_cast<QWidget*>(obj) == ui->selectImageButton) {
            this->ui->selectImageButton->setColorForMouseButtonPressEvent();
        }
        else if (qobject_cast<QWidget*>(obj) == ui->textEditAccountName) {
            this->ui->textEditAccountName->setColorForMouseButtonPressEvent();
        }
        else if (qobject_cast<QWidget*>(obj) == ui->comboBoxCurrency) {
            this->ui->comboBoxCurrency->setColorForMouseButtonPressEvent();
        }
        else if (qobject_cast<QWidget*>(obj) == ui->comboBoxLanguage) {
            this->ui->comboBoxLanguage->setColorForMouseButtonPressEvent();
        }
    }
    else if (event->type() == QEvent::MouseButtonRelease)
    {
        if (qobject_cast<QWidget*>(obj) == ui->buttonCreateAccount) {
            this->ui->buttonCreateAccount->setColorForEnterEvent();
        }
        else if (qobject_cast<QWidget*>(obj) == ui->selectImageButton) {
            this->ui->selectImageButton->setColorForEnterEvent();
        }
        else if (qobject_cast<QWidget*>(obj) == ui->textEditAccountName) {
            this->ui->textEditAccountName->setColorForEnterEvent();
        }
        else if (qobject_cast<QWidget*>(obj) == ui->comboBoxCurrency) {
            this->ui->comboBoxCurrency->setColorForEnterEvent();
        }
        else if (qobject_cast<QWidget*>(obj) == ui->comboBoxLanguage) {
            this->ui->comboBoxLanguage->setColorForEnterEvent();
        }
    }
    else if (event->type() == QEvent::FocusIn)
    {
        if (qobject_cast<QWidget*>(obj) == ui->buttonCreateAccount) {
            this->ui->buttonCreateAccount->setColorForEnterEvent();
        }
        else if (qobject_cast<QWidget*>(obj) == ui->selectImageButton) {
            this->ui->selectImageButton->setColorForEnterEvent();
        }
        else if (qobject_cast<QWidget*>(obj) == ui->textEditAccountName) {
            this->ui->textEditAccountName->setColorForEnterEvent();
        }
        else if (qobject_cast<QWidget*>(obj) == ui->comboBoxCurrency) {
            this->ui->comboBoxCurrency->setColorForEnterEvent();
        }
        else if (qobject_cast<QWidget*>(obj) == ui->comboBoxLanguage) {
            this->ui->comboBoxLanguage->setColorForEnterEvent();
        }
    }
    else if (event->type() == QEvent::FocusOut)
    {
        if (qobject_cast<QWidget*>(obj) == ui->buttonCreateAccount) {
            this->ui->buttonCreateAccount->setColorForLeaveEvent();
        }
        else if (qobject_cast<QWidget*>(obj) == ui->selectImageButton) {
            this->ui->selectImageButton->setColorForLeaveEvent();
        }
        else if (qobject_cast<QWidget*>(obj) == ui->textEditAccountName) {
            this->ui->textEditAccountName->setColorForLeaveEvent();
        }
        else if (qobject_cast<QWidget*>(obj) == ui->comboBoxCurrency) {
            this->ui->comboBoxCurrency->setColorForLeaveEvent();
        }
        else if (qobject_cast<QWidget*>(obj) == ui->comboBoxLanguage) {
            this->ui->comboBoxLanguage->setColorForLeaveEvent();
        }
    }
    return false;
}

void AccountDialog::getExistingAccounts(std::vector<std::string> &existingAccounts)
{
    if (ACCOUNT_BEING_EDITED){
        //std::cout<<"SET TO EDIT ACCOUNT"<<'\n';
        std::vector<std::string>::iterator itAccountsNames;
        for (itAccountsNames = existingAccounts.begin(); itAccountsNames != existingAccounts.end(); ++itAccountsNames)
        {
            if (*itAccountsNames == dialogAccountName) {continue;}
            //std::cout<<"NAME IS FORBIDDEN: "<<*itAccountsNames<<'\n';
            listOfForbiddenAccountNames.push_back(*itAccountsNames);
        }
    }

    else if (ACCOUNT_BEING_CREATED){
        listOfForbiddenAccountNames=existingAccounts;
    }

}

void AccountDialog::setLanguageList(std::vector<std::string> languageList)
{
    allowLanguageSetting = false;
    std::vector<std::string>::iterator it;

    for (it = languageList.begin(); it != languageList.end(); ++it)
    {
        ui->comboBoxLanguage->addItem(QString::fromStdString(*it));
    }
    allowLanguageSetting = true;

    if (ACCOUNT_BEING_CREATED){
        updateUiToCurrentLanguage();
    }
}

void AccountDialog::updateUiToCurrentLanguage()
{
    const Language iLanguage = static_cast<Language>(dialogAccountLanguage);
    if (iLanguage == ENGLISH){
        this->ui->labelName->setText("Name:");
        this->ui->labelCurrency->setText("Currency:");
        this->ui->labelLanguage->setText("Language:");
        this->ui->labelImage->setText("Profile image:");
        this->ui->selectImageButton->setText("Select file");
        this->ui->labelInfo->setText("");
        if (ACCOUNT_BEING_EDITED){
            this->setWindowTitle(" Edit Account");
            this->ui->buttonCreateAccount->setText("Apply");
        } else if (ACCOUNT_BEING_CREATED){
            this->setWindowTitle(" New Account");
            this->ui->buttonCreateAccount->setText("Create Account");
        } else if (ACCOUNT_BEING_VERIFIED){
            this->setWindowTitle(" Verify Account");
            this->ui->buttonCreateAccount->setText("Apply");
        }
    }
    else if (iLanguage == GERMAN)
    {
        this->ui->labelName->setText("Name:");
        this->ui->labelCurrency->setText("Währung:");
        this->ui->labelLanguage->setText("Sprache:");
        this->ui->labelImage->setText("Profilbild:");
        this->ui->selectImageButton->setText("Bild laden");
        this->ui->labelInfo->setText("");
        if (ACCOUNT_BEING_EDITED){
            this->setWindowTitle(" Konto Ändern");
            this->ui->buttonCreateAccount->setText("Übernehmen");
        } else if (ACCOUNT_BEING_CREATED){
            this->setWindowTitle(" Neues Konto");
            this->ui->buttonCreateAccount->setText("Konto erstellen");
        } else if (ACCOUNT_BEING_VERIFIED){
            this->setWindowTitle(" Konto Prüfen");
            this->ui->buttonCreateAccount->setText("Übernehmen");
        }
    }
    else if (iLanguage == SPANISH)
    {
        this->ui->labelName->setText("Nombre:");
        this->ui->labelCurrency->setText("Divisa:");
        this->ui->labelLanguage->setText("Idioma:");
        this->ui->labelImage->setText("Imagen de perfil:");
        this->ui->selectImageButton->setText("Seleccionar");
        this->ui->labelInfo->setText("");
        if (ACCOUNT_BEING_EDITED){
            this->setWindowTitle(" Editar cuenta");
            this->ui->buttonCreateAccount->setText("Aplicar");
        } else if (ACCOUNT_BEING_CREATED){
            this->setWindowTitle(" Cuenta nueva");
            this->ui->buttonCreateAccount->setText("Crear Cuenta");
        } else if (ACCOUNT_BEING_VERIFIED){
            this->setWindowTitle(" Verificar cuenta");
            this->ui->buttonCreateAccount->setText("Aplicar");
        }
    }
}

void AccountDialog::on_comboBoxLanguage_currentIndexChanged(int index)
{
    if (allowLanguageSetting){
        dialogAccountLanguage = index;
        this->updateUiToCurrentLanguage();
    }
}

void AccountDialog::setCurrencyList(std::vector<std::string> currencyList)
{
    std::vector<std::string>::iterator it;

     for (it = currencyList.begin(); it != currencyList.end(); ++it)
     {
         ui->comboBoxCurrency->addItem(QString::fromStdString(*it));
     }
}

void AccountDialog::on_buttonCreateAccount_clicked()
{
    dialogAccountName = ui->textEditAccountName->toPlainText().toStdString();
    dialogAccountLanguage = ui->comboBoxLanguage->currentIndex();
    dialogAccountCurrency = ui->comboBoxCurrency->currentIndex();

    bool NameAlreadyExists = false;
    std::vector<std::string>::iterator itAccountsNames;
    for (itAccountsNames = listOfForbiddenAccountNames.begin(); itAccountsNames != listOfForbiddenAccountNames.end(); ++itAccountsNames)
    {
        if (dialogAccountName == *itAccountsNames){
            NameAlreadyExists = true;
        }
    }

    if (NameAlreadyExists == false)
    {
        if (dialogAccountName.empty())
        {
            const Language iLanguage = static_cast<Language>(dialogAccountLanguage);
            if (iLanguage == ENGLISH){
                this->ui->labelInfo->setText("Please enter a name.");
            } else if (iLanguage == GERMAN){
                this->ui->labelInfo->setText("Bitte geben Sie einen Name ein.");
            } else if (iLanguage == SPANISH) {
                this->ui->labelInfo->setText("Por favor introduzca un nombre.");
            }
        } else {
            creationConfirmed = true;
            this->close();
        }
    } else {
        this->ui->labelInfo->setWordWrap(true);
        const Language iLanguage = static_cast<Language>(dialogAccountLanguage);
        if (iLanguage == ENGLISH){
            this->ui->labelInfo->setText("An Account with that name already exists, please choose a different name.");
        } else if (iLanguage == GERMAN){
            this->ui->labelInfo->setText("Das Konto existiert bereits, bitte geben Sie einen neuen Name ein.");
        } else if (iLanguage == SPANISH) {
            this->ui->labelInfo->setText("Una cuenta con ese nombre ya existe, por favor seleccione uno diferente.");
        }
    }
}

void AccountDialog::on_textEditAccountName_textChanged()
{
    std::string textEntered = ui->textEditAccountName->toPlainText().toStdString();
    bool wrongCharacterEntered = false;
    std::string::iterator stringIt;
    std::string allowedText;
    for (stringIt = textEntered.begin(); stringIt != textEntered.end(); ++stringIt)
    {
        if ( (*stringIt == '/') || (*stringIt == '*') || (*stringIt == '|') || (*stringIt == ':') || (*stringIt == '<')
          || (*stringIt == '>') || (*stringIt == '"') || (*stringIt == '\\'))
        {
            wrongCharacterEntered = true;
        } else {
            allowedText += *stringIt;
        }
    }

    if (wrongCharacterEntered)
    {
        ui->textEditAccountName->setText(QString::fromStdString(allowedText));
        QTextCursor cursor = ui->textEditAccountName->textCursor();
        cursor.movePosition( QTextCursor::End );
        ui->textEditAccountName->setTextCursor(cursor);

        if (dialogAccountLanguage == ENGLISH){
            this->ui->labelInfo->setText("An account name cannot have the symbols:  / \\ * | : < > '' ");
        } else if (dialogAccountLanguage == GERMAN){
            this->ui->labelInfo->setText("Ein Konto kann nicht folgende Symbole haben: / \\ * | : < > '' ");
        } else if (dialogAccountLanguage == SPANISH) {
            this->ui->labelInfo->setText("Un nombre de cuenta no puede usar los símbolos: / \\ * | : < > '' ");
        }
    } else {
         this->ui->labelInfo->setText(" ");
    }
}

void AccountDialog::on_buttonDeleteImage_clicked()
{
    indexSelectedImage = 0;

    QImage srcImg(listOfImagePaths[indexSelectedImage]);
    imagePixmap = QPixmap::fromImage(srcImg);
    if (!imagePixmap.isNull()) {
        imageSelected = true;
        currentLayoutFormat = DEFAULT;
        ui->labelInfo->setText("");
        projectPixMapOntoView(true);
    }
}

void AccountDialog::provideAccountProperties(std::string &accountName,
                                             short &accountLanguage,
                                             short &accountCurrency)
{
    accountName = dialogAccountName;
    accountLanguage = dialogAccountLanguage;
    accountCurrency = dialogAccountCurrency;
}

void AccountDialog::receiveAccountProperties(std::string &accountName,  //This is only used when an account is being verified.
                                             short &accountLanguage,
                                             short &accountCurrency,
                                             std::string &accountImagePath)
{
    dialogAccountName = accountName;
    dialogAccountLanguage = accountLanguage;
    dialogAccountCurrency = accountCurrency;
    dialogAccountImagePath = accountImagePath;

    ui->textEditAccountName->setText(QString::fromStdString(dialogAccountName));
    ui->comboBoxLanguage->setCurrentIndex(dialogAccountLanguage);
    ui->comboBoxCurrency->setCurrentIndex(dialogAccountCurrency);
    this->updateUiToCurrentLanguage();

    QImage srcImg(QString::fromStdString(dialogAccountImagePath));
    imagePixmap = QPixmap::fromImage(srcImg);

    if (!imagePixmap.isNull()) {
        listOfImagePaths.push_back(QString::fromStdString(dialogAccountImagePath));
        indexSelectedImage = listOfImagePaths.size()-1; //Substract one because the index is used to access element in vector, which starts from zero
        projectPixMapOntoView(true);
        imageSelected = true;
    }    
}

void AccountDialog::on_selectImageButton_clicked()
{
    QString originalImagePath;
    #ifdef USING_WINDOWS
        homeFolder = QDir::homePath();
    #endif

    const Language iLanguage = static_cast<Language>(dialogAccountLanguage);
    if (iLanguage == ENGLISH){
        originalImagePath = QFileDialog::getOpenFileName(this, tr("Open file"),
                                                         homeFolder,
                                                         tr("Images (*.png *.jpeg *.jpg)"));
    } else if (iLanguage == GERMAN){
        originalImagePath = QFileDialog::getOpenFileName(this, tr("Datei öffnen"),
                                                         homeFolder,
                                                         tr("Images (*.png *.jpeg *.jpg)"));
    } else if (iLanguage == SPANISH) {
        originalImagePath = QFileDialog::getOpenFileName(this, tr("Seleccionar archivo"),
                                                         homeFolder,
                                                         tr("Images (*.png *.jpeg *.jpg)"));
    }
    QImage srcImg(originalImagePath);
    imagePixmap = QPixmap::fromImage(srcImg);

    if (!imagePixmap.isNull()) {
        listOfImagePaths.push_back(originalImagePath);
        indexSelectedImage = listOfImagePaths.size()-1; //Substract one because the index is used to access element in vector, which starts from zero
        projectPixMapOntoView(true);
        imageSelected = true;
        //std::cout<<"IMAGE WAS SELECTED "<<'\n';
    }
}

void AccountDialog::saveImageToAccountPath(std::string accountPath)
{
    //imagePixmap=imagePixmap.scaled(1600, 1200, Qt::KeepAspectRatio); //TO LIMIT IMAGE SIZE

    QPointF OriginRect = ui->accountGraphicsView->mapToScene(0, 0);
    QPointF EndRect    = ui->accountGraphicsView->mapToScene(ui->accountGraphicsView->width(), ui->accountGraphicsView->height());

    QRect croppedScene (OriginRect.x(), OriginRect.y(), (EndRect.x()-OriginRect.x()), (EndRect.y()-OriginRect.y()));
    QPixmap croppedImage = imagePixmap.copy(croppedScene);
    QString copyImagePath = QString::fromStdString(accountPath)+"/AccountIcon.png";
    QFile file(copyImagePath);
    croppedImage.save(&file, "PNG");

    dialogAccountImagePath = copyImagePath.toStdString();
}

void AccountDialog::on_buttonRotate_clicked()
{
    if (imageSelected){
        if (!imagePixmap.isNull()) {
        rotatePixMap(90);
        projectPixMapOntoView(false);
        }
    }
}

void AccountDialog::projectPixMapOntoView(bool scaleToWidgetSize)
{
    if (scaleToWidgetSize){
        ui->accountGraphicsView->resetTransform();
    }
    double horizontalSide = imagePixmap.width();
    double verticalSide   = imagePixmap.height();
    const int MaxWidth  = 160;
    const int MaxHeight = 151;

    if (currentLayoutFormat == DEFAULT)
    {
        double ratio = 0.0;
        if (horizontalSide > verticalSide)
        {
            ratio = verticalSide/horizontalSide;
            ui->accountGraphicsView->setFixedWidth(MaxWidth);
            int labelHeight = MaxWidth*ratio;
            ui->accountGraphicsView->setFixedHeight(labelHeight);
        } else {
            ratio = horizontalSide/verticalSide;
            ui->accountGraphicsView->setFixedHeight(MaxHeight);
            int labelHeight = MaxHeight*ratio;
            ui->accountGraphicsView->setFixedWidth(labelHeight);
        }
    } else if (currentLayoutFormat == LANDSCAPE) {
        ui->accountGraphicsView->setFixedWidth(MaxWidth);
        ui->accountGraphicsView->setFixedHeight(100);
    } else if (currentLayoutFormat == PORTRAIT) {
        ui->accountGraphicsView->setFixedWidth(100);
        ui->accountGraphicsView->setFixedHeight(MaxHeight);
    } else if (currentLayoutFormat == SQUARE) {
        ui->accountGraphicsView->setFixedWidth(MaxWidth);
        ui->accountGraphicsView->setFixedHeight(MaxHeight);
    }

    int w = ui->accountGraphicsView->width()-10;
    int h = ui->accountGraphicsView->height()-10;

    item = new QGraphicsPixmapItem(imagePixmap);
    //imagePixmap.scaled(w, h, Qt::KeepAspectRatio)
    scene = new QGraphicsScene(this);
    scene->addItem(item);

    ui->accountGraphicsView->setScene(scene);

    //Scale to fit whole image in GraphicsView
    if (scaleToWidgetSize){
        double factorX = w/horizontalSide;
        double factorY = h/verticalSide;
        ui->accountGraphicsView->scale(factorX, factorY);
    }
}

void AccountDialog::rotatePixMap(int degrees)
{
    if (imageSelected){
        QTransform rotationMatrix ;
        rotationMatrix.rotate(degrees);
        imagePixmap = imagePixmap.transformed(rotationMatrix);
    }
}

void AccountDialog::on_buttonIconRight_clicked()
{
    if (indexSelectedImage == (listOfImagePaths.size()-1)){
        indexSelectedImage = 0;
    } else {
        ++indexSelectedImage;
    }

    QImage srcImg(listOfImagePaths[indexSelectedImage]);
    imagePixmap = QPixmap::fromImage(srcImg);
    if (!imagePixmap.isNull()) {
        imageSelected = true;
        currentLayoutFormat = DEFAULT;
        ui->labelInfo->setText("");
        projectPixMapOntoView(true);
    }
}

void AccountDialog::on_buttonIconLeft_clicked()
{
    if (indexSelectedImage == 0){
        indexSelectedImage = (listOfImagePaths.size()-1);
    } else {
        --indexSelectedImage;
    }

    QImage srcImg(listOfImagePaths[indexSelectedImage]);
    imagePixmap = QPixmap::fromImage(srcImg);
    if (!imagePixmap.isNull()) {
        imageSelected = true;
        currentLayoutFormat = DEFAULT;
        ui->labelInfo->setText("");
        projectPixMapOntoView(true);
    }
}

void AccountDialog::on_changeFormatButton_clicked() //IT CHANGES IMAGE FORMAT
{
    if (imageSelected){
        if (!imagePixmap.isNull()){

            switch (currentLayoutFormat) {
            case DEFAULT:
            {currentLayoutFormat = LANDSCAPE;
                {
                    const Language iLanguage = static_cast<Language>(dialogAccountLanguage);
                    if (iLanguage == ENGLISH){
                        ui->labelInfo->setText("Landscape");
                    }
                    else if (iLanguage == GERMAN){
                        ui->labelInfo->setText("Landscape");
                    }
                    else if (iLanguage == SPANISH){
                        ui->labelInfo->setText("Panorámico");
                    }
                }
                break;}
            case LANDSCAPE:
            {currentLayoutFormat = PORTRAIT;
                {
                    const Language iLanguage = static_cast<Language>(dialogAccountLanguage);
                    if (iLanguage == ENGLISH){
                        ui->labelInfo->setText("Portrait");
                    }
                    else if (iLanguage == GERMAN){
                        ui->labelInfo->setText("Porträt");
                    }
                    else if (iLanguage == SPANISH){
                        ui->labelInfo->setText("Retrato");
                    }
                }
                break;}
            case PORTRAIT:
            {currentLayoutFormat = SQUARE;
                {
                    const Language iLanguage = static_cast<Language>(dialogAccountLanguage);
                    if (iLanguage == ENGLISH){
                        ui->labelInfo->setText("Square");
                    }
                    else if (iLanguage == GERMAN){
                        ui->labelInfo->setText("Quadrat");
                    }
                    else if (iLanguage == SPANISH){
                        ui->labelInfo->setText("Cuadrado");
                    }
                }
                break;}
            case SQUARE:
            {currentLayoutFormat = DEFAULT;
                {
                    const Language iLanguage = static_cast<Language>(dialogAccountLanguage);
                    if (iLanguage == ENGLISH){
                        ui->labelInfo->setText("Original format");
                    }
                    else if (iLanguage == GERMAN){
                        ui->labelInfo->setText("Originales Format");
                    }
                    else if (iLanguage == SPANISH){
                        ui->labelInfo->setText("Formato original");
                    }
                }
                break;}
            default:
            {currentLayoutFormat = DEFAULT;
                break;}
            }

            this->projectPixMapOntoView(false);
        }
    }
}

void AccountDialog::setInitialLanguage(Language iLanguage)
{
    short int tempLanguage = static_cast<short int>(iLanguage);
    this->ui->comboBoxLanguage->setCurrentIndex(tempLanguage);
    if (ACCOUNT_BEING_CREATED)
    {
        QImage srcImg(listOfImagePaths[indexSelectedImage]);
        imagePixmap = QPixmap::fromImage(srcImg);
        if (!imagePixmap.isNull()) {
            imageSelected = true;
            currentLayoutFormat = DEFAULT;
            ui->labelInfo->setText("");
            projectPixMapOntoView(true);
        }
    }
}
