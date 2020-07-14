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

#ifndef THEMECOLORSDIALOG_H
#define THEMECOLORSDIALOG_H

#include <QDialog>
#include <QOpenGLWidget>
#include <QOpenGLPaintDevice>
#include <GL/gl.h>
#include <QPainter>
#include <math.h>
#include <keibomoneytrackerinclude.h>

namespace Ui {
class ThemeColorsDialog;
class GroupPieChartColorWidget;
}

class ThemeColorsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ThemeColorsDialog(QWidget *parent = 0);
    ~ThemeColorsDialog();

    bool colorSelectionConfirmed    = false;    
    bool customColorsExist          = false;
    unsigned int  currentColorTheme = 0;

    bool allowUpdateColorsInOverallDarkThemeComboBox = false;
    bool allowUpdateColorsInPresetComboBox           = false;

    unsigned int numberOfPresetColorThemes   = 0;

    void addCustomColorConfiguration (const ColorConfiguration &customColorConfig);

    std::vector<ColorConfiguration> colorConfigurationList;
    void addColorConfiguration(const std::string &themeName,
                               const int &barIncomeSelected,
                               const int &barIncomeUnselected,
                               const int &barExpensesSelected,
                               const int &barExpensesUnselected,
                               const int &barBackground,
                               const int &groupIncomeSelected,
                               const int &groupIncomeUnselected,
                               const int &groupExpensesSelected,
                               const int &groupExpensesUnselected,
                               const int &groupIncomeBackground,
                               const int &groupExpensesBackground,
                               const int &tableIncomeAmount,
                               const bool &monthlyAmountInColor,
                               const bool &useDarkOverall);
    void setCurrentColorConfiguration();
    void updateColorsOnScreen();
    void setLanguage(const Language &currentLanguage);

private slots:
    void on_radioGroupIncome_clicked();
    void on_radioGroupOutcome_clicked();
    void on_radioBarIncome_clicked();
    void on_radioBarExpenses_clicked();
    void on_buttonSaveAndSet_clicked();
    void on_comboBox_currentIndexChanged(int index);
    void on_checkBox_clicked();
    void on_comboBoxOverallTheme_currentIndexChanged(int index);

private:
    Ui::ThemeColorsDialog *ui;

    bool showingIncomeGroups  = true;
    bool showingIncomeBars    = true;

    bool eventFilter(QObject *obj, QEvent *event);

    Language iLanguage =  ENGLISH;

    void labelGroupSelectedClicked();
    void labelGroupUnselectedClicked();
    void labelGroupBackgroundClicked();
    void labelBarSelectedClicked();
    void labelBarUnselectedClicked();
    void labelBarBackgroundClicked();
    void labelColorIncomeAmountTextClicked();

    QString getStyleSheetString(QString objectType, int colorCode, bool useForBackground, bool useBorder);
    QString overallThemeStyleSheet;
};


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class GroupPieChartColorWidget : public QOpenGLWidget
{
public:
    GroupPieChartColorWidget(QWidget *parent = 0);
    ~GroupPieChartColorWidget();
    const float PI = 3.14159265359f;

    float amountOfSelectedGroup = 12345.67f;

    float finalPercentageStart = 0.0f;
    float finalPercentageEnd   = 50.0f;

    float centerX = 0.0f;
    float centerY = 0.0f;
    float outterRadius  = 0.0f;
    float innerRadius   = 0.0f;
    float innerRadius2  = 0.0f;

    ///Colors
    void setColors (int selected, int unselected, int background);
    int colorSelected   = 0;
    int colorUnselected = 0;
    int colorBackground = 0;

private:

    int centerR = 0;
    int centerG = 0;
    int centerB = 0;

    QRect rectangleTextPercentage;
    QRect rectangleTextAmount;

    void updateSpace();
    void drawGroupChart();

    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

    float theta = 0.0f;
    float numberSegments = 40.0f;
    float thetaColorPolygon = 0.0f;
    float segmentsColorPolygon = 20.0f;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class MonthBarChartColorWidget : public QOpenGLWidget
{
public:
    MonthBarChartColorWidget(QWidget *parent = 0);
    ~MonthBarChartColorWidget();

    ///Colors
    void setBarColors (const int &incomeSelected,  const int &incomeUnselected,
                       const int &outcomeSelected, const int &outcomeUnselected);
    void setBackgroundColor (const int &background);
    int colorIncomeSelected    = 0;
    int colorOutcomeSelected   = 0;
    int colorIncomeUnselected  = 0;
    int colorOutcomeUnselected = 0;
    int colorBackground = 0;    

    int activationCounterBarBackgroundColor = 0;  //Workaround solution

private:

    float  Ax = 0.0f; //Offset of Table on the left - 5% of total length.
    float  Bx = 0.0f; //Length of rectangle/Scale board - 80% of total length.
    float  Cx = 0.0f; //Free space for quantities of scale board - 15% of total length.
    float  Dx = 0.0f; //Length of space available for each month B/12 - 6.6667% of total length.

    float monthXpStartIncome[4]  = {0.0f};  //Store here starting X position for Income bars.
    float monthXpFinalIncome[4]  = {0.0f};  //Store here final X position for Income bars.
    float monthXpStartOutcome[4] = {0.0f};  //Store here starting X positions for Outcome bars.
    float monthXpFinalOutcome[4] = {0.0f};  //Store here final X positions for Outcome bars.

    float Ay = 0.0f; //Offset from the bottom to the starting points in Y for all months.
    float By = 0.0f; //Length of height of rectanle/Scale board - 90% of total height. Also the maximum height a bar can have.
    float monthYpIncome[4]  = {0.0f};  //Store here increasing Y position for Income bars.
    float monthYpOutcome[4] = {0.0f};  //Store here increasing Y position for Outcome bars.

    float offsetWidth  = 0.0f;
    float offsetHeigth = 0.0f;

    float boardX1 = 0.0f;
    float boardY1 = 0.0f;
    float boardX2 = 0.0f;
    float boardY2 = 0.0f;

    float heightHorizontalScaleBoardLines[5] = {0.0f};
    float heightScaleBoardQuantities[5] = {0.0f};

    float leftQuantities = 0.0f; //Starting position in X for Quantities
    double scaleValues[5]  {100.0, 200, 300, 400, 500};

    float monthYpIncomeFinal[4]  {0.0f}; //Store here final Y value for Income bars
    float monthYpOutcomeFinal[4] {0.0f}; //Store here final Y value for Outcome bars

    QRect rectangleTextPercentage;
    QRect rectangleTextAmount;

    QPainter painter;

    void updateSpace();
    void drawMonthChart();
    void drawScaleBoard();
    void drawQuantities();

    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
};

#endif // THEMECOLORSDIALOG_H
