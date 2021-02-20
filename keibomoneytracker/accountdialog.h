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

#ifndef ACCOUNTDIALOG_H
#define ACCOUNTDIALOG_H

#include <QDialog>
#include <QGraphicsView>
#include <QtWidgets>
#include <QWidget>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QtGui>
#include "keibomoneytrackerinclude.h"

namespace Ui {
class AccountDialog;
class AccountImageView;
}

class AccountImageView : public QGraphicsView
{
public:
    AccountImageView(QWidget* parent = 0);

private:

    bool leftMouseButtonPressed = false;
    float previousX = 0.0f;
    float previousY = 0.0f;

    QPointF target_scene_pos, target_viewport_pos;

protected:
    virtual void wheelEvent(QWheelEvent *event);
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
};


enum ImageLayoutFormat {DEFAULT, LANDSCAPE, PORTRAIT, SQUARE};
class AccountDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AccountDialog(QWidget *parent = 0);
    ~AccountDialog();

    bool creationConfirmed = false;
    bool eventFilter(QObject *obj, QEvent *event);
    bool allowLanguageSetting = false;

    void setInitialLanguage(Language iLanguage);

    void setToCreateAccount() {ACCOUNT_BEING_CREATED  = true;}
    void setToEditAccount()   {ACCOUNT_BEING_EDITED   = true;}
    void setToVerifyAccount() {ACCOUNT_BEING_VERIFIED = true;}

    void setLanguageList(std::vector<std::string> languageList);
    void setCurrencyList(std::vector<std::string> currencyList);
    void updateUiToCurrentLanguage();

    void provideAccountProperties(std::string &accountName,
                                  short int &accountLanguage,
                                  short int &accountCurrency);

    void receiveAccountProperties(std::string &accountName,
                                  short int &accountLanguage,
                                  short int &accountCurrency,
                                  std::string &accountImagePath);

    bool imageWasSelected() {return imageSelected;}
    void saveImageToAccountPath(std::string accountPath);
    void provideAccountImagePath (std::string &accountImagePath) {accountImagePath = dialogAccountImagePath;}

    void getExistingAccounts(std::vector<std::string> &existingAccounts);

    void setOverallThemeStyleSheet(QString styleSheetString, bool usingDarkTheme);

private slots:
    void on_buttonCreateAccount_clicked();
    void on_selectImageButton_clicked();
    void on_buttonRotate_clicked();
    void on_buttonIconRight_clicked();
    void on_buttonIconLeft_clicked();
    void on_changeFormatButton_clicked();
    void on_buttonDeleteImage_clicked();
    void on_comboBoxLanguage_currentIndexChanged(int index);
    void on_textEditAccountName_textChanged();

private:
    Ui::AccountDialog *ui;

    bool imageSelected = false;

    bool ACCOUNT_BEING_EDITED   = false;
    bool ACCOUNT_BEING_CREATED  = false;
    bool ACCOUNT_BEING_VERIFIED = false;

    ImageLayoutFormat currentLayoutFormat;

    QString dialogAccountPath;
    QPixmap imagePixmap;

    unsigned int indexSelectedImage = 0;
    void rotatePixMap(int degrees);
    void projectPixMapOntoView(bool scaleToWidgetSize);
    std::vector<QString> listOfImagePaths;

    QString homeFolder                 = "/home";
    std::string dialogAccountName      = "";
    short int dialogAccountLanguage    = 0;
    short int dialogAccountCurrency    = 0;
    std::string dialogAccountImagePath = "";

    std::vector<std::string> listOfForbiddenAccountNames;

    QGraphicsItem *item;
    QGraphicsScene *scene;
};

#endif // ACCOUNTDIALOG_H
