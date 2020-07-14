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

#ifndef USERGUIDE_H
#define USERGUIDE_H

#include <QDialog>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include "keibomoneytrackerinclude.h"

namespace Ui {
class UserGuide;
}

class UserGuide : public QDialog
{
    Q_OBJECT

public:
    explicit UserGuide(QWidget *parent = nullptr);
    ~UserGuide();

    void setOverallThemeStyleSheet(QString styleSheetString);
    void setCurrentLanguage(Language iLanguage);

private slots:
    void on_pushButtonPrevious_clicked();
    void on_pushButtonNext_clicked();
    void on_pushButtonAccounts_clicked();
    void on_pushButtonMainWindow_clicked();
    void on_pushButtonTransactions_clicked();
    void on_pushButtonGroups_clicked();
    void on_pushButtonAppearance_clicked();
    void on_pushButtonStoredFiles_clicked();

private:
    Ui::UserGuide *ui;

    bool languageSet = false;
    enum Tutorial {ACCOUNTS, MAINWINDOW, TRANSACTIONS, GROUPS, APPEARANCE, STOREDFILES};

    Language currentLanguage =  ENGLISH;
    Tutorial currentTutorial = ACCOUNTS;

    QGraphicsPixmapItem *item;
    QGraphicsScene *scene;

    void setImageOnLabel(const QString &imagePath);

    unsigned int AccountPartIndex = 0;
    std::vector<QString> AccountTutorialParts;
    std::vector<QString> AccountPartsExplanation;
    std::vector<QString> AccountPartsImagePath;

    unsigned int MainwindowPartIndex = 0;
    std::vector<QString> MainwindowTutorialParts;
    std::vector<QString> MainwindowPartsExplanation;
    std::vector<QString> MainwindowPartsImagePath;

    unsigned int TransactionsPartIndex = 0;
    std::vector<QString> TransactionsTutorialParts;
    std::vector<QString> TransactionsPartsExplanation;
    std::vector<QString> TransactionsPartsImagePath;

    unsigned int GroupsPartIndex = 0;
    std::vector<QString> GroupsTutorialParts;
    std::vector<QString> GroupsPartsExplanation;
    std::vector<QString> GroupsPartsImagePath;

    unsigned int AppearancePartIndex = 0;
    std::vector<QString> AppearanceTutorialParts;
    std::vector<QString> AppearancePartsExplanation;
    std::vector<QString> AppearancePartsImagePath;

    unsigned int StoredfilesPartIndex = 0;
    std::vector<QString> StoredfilesTutorialParts;
    std::vector<QString> StoredfilesPartsExplanation;
    std::vector<QString> StoredfilesPartsImagePath;

    void updateInfoOnScreen();
    void highlightButton(QPushButton *button);
    QPushButton *pushButtonCurrentlySelectedTutorial;

    bool eventFilter(QObject *obj, QEvent *event);
};

#endif // USERGUIDE_H
