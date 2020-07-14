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

#ifndef MYOPENGLWIDGET_H
#define MYOPENGLWIDGET_H

#include "keibomoneytracker.h"

#include <QTimer>
#include <QGLWidget>
#include <QOpenGLWidget>
#include <QOpenGLPaintDevice>
#include <QWheelEvent>
#include <math.h>
#include <cmath>

#include <QPainter>
#include "keibomoneytrackerinclude.h"

#include <thread>
#include <future>

namespace Ui {
class MyOpenGLWidget;
}

class MyOpenGLWidget : public QOpenGLWidget
{
public:
    MyOpenGLWidget(QWidget *parent = 0);
    ~MyOpenGLWidget();

    bool useBiggerFont = false;

    bool yearlyData     = false;
    bool monthlyData    = false;

    int activationCounterBarBackgroundColor = 0;  //Workaround solution

    bool flagMaxValueOfBarChecked[24] {false};
    void resetFLags();

    Language currentLanguage;
    Currency currentCurrency;

    float percentageGroupStart   = 0.0;
    float percentageGroupEnd     = 0.0;
    float currentPercentageStart = 0.0;
    float currentPercentageEnd   = 0.0;

    int Highlighted= 0;
    double scaleValues[5]  {0.0};

    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

    float currentYDimension[12]       {0.0};
    float currentYDimensionIncome[12] {0.0};
    inline float dampedSpring(GLfloat targetPosition, GLfloat &currentPosition);

    int selectedMonthByMouse = -1;
    bool mouseWasClicked = false;
    int getSelectedMonthByClick();
    void processMouseClick();

    const int FRAMETIME_MS = 35;
    QTimer timer;

    float monthYpFinalIncome[12]  {0.0f}; //Store here final Y value for Income bars
    float monthYpFinalOutcome[12] {0.0f}; //Store here final Y value for Expenses bars
    bool validYpFinalIncome[12] {false};
    bool validYpFinalOutcome[12] {false};

    inline void setBarWidgetColors (const int &barIncomeSelected,
                             const int &barIncomeUnselected,
                             const int &barExpensesSelected,
                             const int &barExpensesUnselected,
                             const int &background){
        colorBarIncomeSelected     = barIncomeSelected;
        colorBarIncomeUnselected   = barIncomeUnselected;
        colorBarExpensesSelected   = barExpensesSelected;
        colorBarExpensesUnselected = barExpensesUnselected;
        colorBackground            = background;
    }

private:

    //Colors
    int colorBarIncomeSelected     = 13;
    int colorBarIncomeUnselected   = 0;
    int colorBarExpensesSelected   = 18;
    int colorBarExpensesUnselected = 0;
    int colorBackground            = 36;

    //Space variables
    float  Ax = 0.0f; //Offset of Table on the left - 5% of total length.
    float  Bx = 0.0f; //Length of rectangle/Scale board - 80% of total length.
    float  Cx = 0.0f; //Free space for quantities of scale board - 15% of total length.
    float  Dx = 0.0f; //Length of space available for each month B/12 - 6.6667% of total length.
    //float  E = 0.0f; //Small offset to create separation between months - 10% of D.

    float monthXpStartIncome[12]  = {0.0f};  //Store here starting X position for Income bars.
    float monthXpFinalIncome[12]  = {0.0f};  //Store here final X position for Income bars.
    float monthXpStartOutcome[12] = {0.0f};  //Store here starting X positions for Outcome bars.
    float monthXpFinalOutcome[12] = {0.0f};  //Store here final X positions for Outcome bars.

    float Ay = 0.0f; //Offset from the bottom to the starting points in Y for all months.
    float By = 0.0f; //Length of height of rectanle/Scale board - 90% of total height. Also the maximum height a bar can have.
    float monthYpCurrentIncome[12]  = {0.0f};  //Store here increasing Y position for Income bars.
    float monthYpCurrentOutcome[12] = {0.0f};  //Store here increasing Y position for Outcome bars.

    float offsetWidth  = 0.0f;
    float offsetHeigth = 0.0f;

    float boardX1 = 0.0f;
    float boardY1 = 0.0f;
    float boardX2 = 0.0f;
    float boardY2 = 0.0f;

    float heightHorizontalScaleBoardLines[5] = {0.0f};
    float heightScaleBoardQuantities[5] = {0.0f};

    float leftQuantities = 0.0f;   //Starting position in X for Quantities

    //
    void updateSpace();

    QPainter painter;

    void drawChart();
    void drawScaleBoard();
    void drawQuantities();

    void drawShadowOnPointedMonth();
    void calculateMouseXNormilizedPosition(const int &xInPixels);

protected:
    bool event(QEvent * e);

};

#endif // MYOPENGLWIDGET_H
