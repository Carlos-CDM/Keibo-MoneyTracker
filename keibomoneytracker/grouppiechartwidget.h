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

#ifndef GROUPPIECHARTWIDGET_H
#define GROUPPIECHARTWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLPaintDevice>
#include <QTimer>
#include <cmath>
#include <QPainter>
#include "keibomoneytrackerinclude.h"

namespace Ui {
class GroupPieChartWidget;
}

class GroupPieChartWidget : public QOpenGLWidget
{
public:
    GroupPieChartWidget(QWidget *parent = 0);
    ~GroupPieChartWidget();
    bool showingIncome = false;

    bool flagMaxValueChecked = false;

    double amountOfSelectedGroup = 0.0;

    float finalPercentageStart = 0.0f;
    float finalPercentageEnd   = 0.0f;

    float centerX = 0.0f;
    float centerY = 0.0f;
    float outterRadius  = 0.0f;
    float innerRadius   = 0.0f;
    float innerRadius2  = 0.0f;

    std::vector<double> finalPercentageOfEachGroup;

    QTimer timer;
    void resetFLags();    

    inline void setGroupWidgetColors (const int &groupIncomeSelected,
                                      const int &groupIncomeUnselected,
                                      const int &groupExpensesSelected,
                                      const int &groupExpensesUnselected,
                                      const int &groupIncomeBackground,
                                      const int &groupExpensesBackground)
    {
        colorGroupIncomeSelected      = groupIncomeSelected;
        colorGroupIncomeUnselected    = groupIncomeUnselected;
        colorGroupExpensesSelected    = groupExpensesSelected;
        colorGroupExpensesUnselected  = groupExpensesUnselected;
        colorGroupIncomeBackground    = groupIncomeBackground;
        colorGroupExpensesBackground  = groupExpensesBackground;
    }

    inline void setProperties(const Language &iLanguage, const Currency &iCurrency)
    {
        currentLanguage = iLanguage;
        currentCurrency = iCurrency;
    }

private:    
    Language currentLanguage = ENGLISH;
    Currency currentCurrency = DOLLAR;

    int colorGroupIncomeSelected      = 13;
    int colorGroupIncomeUnselected    = 4;
    int colorGroupExpensesSelected    = 9;
    int colorGroupExpensesUnselected  = 4;
    int colorGroupIncomeBackground    = 26;
    int colorGroupExpensesBackground  = 26;

    QRect rectangleTextPercentage;
    QRect rectangleTextAmount;

    float currentPercentageStart = 0.0f;
    float currentPercentageEnd   = 0.0f;

    inline float dampedSpring(float targetPosition, float &currentPosition);

    void updateSpace();
    void drawGroupChart();

    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

    float numberSegments = 40.0f;
    float theta = 0.0f;
    float segmentsHighPolygonCount = 1000.0f; //In order to reach displayability of 0.10% in pie chart
    float thetaHighPolygonCount = 0.0f;
};
#endif // GROUPPIECHARTWIDGET_H
