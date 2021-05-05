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

#include "grouppiechartwidget.h"
#include <iostream>
#include <keibomoneytrackerinclude.h>

GroupPieChartWidget::GroupPieChartWidget(QWidget *parent) :
    QOpenGLWidget(parent)
{
    QSurfaceFormat format;
    format.setSamples(15);
    this->setFormat(format);

    connect(&timer, SIGNAL(timeout()), this, SLOT(update()));
    timer.start(35);

    this->setAttribute(Qt::WA_AlwaysStackOnTop);
}

GroupPieChartWidget::~GroupPieChartWidget()
{
}

void GroupPieChartWidget::updateSpace()
{
    float totalWidth = this->width();
    float totalHeigth = this->height();

    if (totalWidth > 0.0f && totalHeigth > 0.0f)
    {
        centerX = totalWidth*0.5f;
        centerY = totalHeigth*0.5f;

        float lowestDimension = (totalWidth < totalHeigth) ? totalWidth : totalHeigth;

        outterRadius  = lowestDimension*0.50f;
        innerRadius   = lowestDimension*0.300f;
        innerRadius2  = lowestDimension*0.345f;        

        if (totalWidth > 185){
            int textWidth  = 105;
            int textHeight = 19;

            int leftPercentage   = (totalWidth/2)-52;
            int topPercentage    = (totalHeigth/2)+3;
            rectangleTextPercentage = QRect(leftPercentage, topPercentage, textWidth, textHeight);

            int leftAmount   = (totalWidth/2)-54;
            int topAmount    = (totalHeigth/2)-14;
            rectangleTextAmount = QRect(leftAmount, topAmount, textWidth, textHeight);
        } else {
            int textWidth  = 105;
            int textHeight = 18;

            int leftPercentage   = (totalWidth/2)-52;
            int topPercentage    = (totalHeigth/2)+4;
            rectangleTextPercentage = QRect(leftPercentage, topPercentage, textWidth, textHeight);

            int leftAmount   = (totalWidth/2)-54;
            int topAmount    = (totalHeigth/2)-14;
            rectangleTextAmount = QRect(leftAmount, topAmount, textWidth, textHeight);
        }

        theta = (2.0f * 3.14159265359f)/numberSegments; //40 Segments for low poly circle
        thetaHighPolygonCount = (2.0f * 3.14159265359f)/segmentsHighPolygonCount;
    }
}
void GroupPieChartWidget::drawGroupChart()
{
     glBegin(GL_POLYGON);
     float r = outterRadius;
       for (int side = 0; side <= numberSegments; ++side)
         {
            GLfloat x =  r * cos(theta*side);
            GLfloat y = -r * sin(theta*side);
            if (showingIncome) {
                int r = 0, g = 0, b = 0;
                getColorCode(colorGroupIncomeUnselected, r, g, b);
                glColor3ub(r, g, b);
            } else if (!showingIncome) {
                int r = 0, g = 0, b = 0;
                getColorCode(colorGroupExpensesUnselected, r, g, b);
                glColor3ub(r, g, b);
            }
            glVertex3f(centerX + x, centerY + y, 0.0);
         }
      glEnd();

      /////////////////////////////////////////////////////////////////////
      //DRAW HERE THE LINES THAT DIVIDE EACH GROUP LIMIT/DIVISION
      glEnable(GL_BLEND);
      glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
      double offset = 0.0;
      for (std::vector<double>::iterator side = finalPercentageOfEachGroup.begin();
           side != finalPercentageOfEachGroup.end(); ++side)
        {
          double PercentageOfGroupScaled = (*side) * 1000.0;
           GLfloat x = -r * cos(thetaHighPolygonCount*(static_cast<int>(PercentageOfGroupScaled+offset)));
           GLfloat y =  r * sin(thetaHighPolygonCount*(static_cast<int>(PercentageOfGroupScaled+offset)));
           glBegin(GL_LINES);
           glLineWidth(1.0f);
           glColor4f(0.85f, 0.85f, 0.85f, 0.20f);
           glVertex3f(centerX, centerY, 0.0);
           glVertex3f(centerX + x, centerY + y, 0.0);
           glEnd();
           offset += PercentageOfGroupScaled;
        }

    /////////////////////////////////////////////////////////////////////
    //DRAW HERE THE ARC CORRESPONDING TO THE PERCENTAGE OF SELECTED GROUP
      //Compute here increasing/decreasing percentage values. Start and End of selected group
      if ( (currentPercentageStart < (finalPercentageStart - 0.001f))  ||
           (currentPercentageEnd   < (finalPercentageEnd   - 0.001f))  )  {
            dampedSpring(finalPercentageStart, currentPercentageStart);
            dampedSpring(finalPercentageEnd, currentPercentageEnd);
      }
      else if ( (currentPercentageStart > (finalPercentageStart + 0.001f)) ||
                (currentPercentageEnd   > (finalPercentageEnd   + 0.001f))  )  {

            dampedSpring(finalPercentageStart, currentPercentageStart);
            dampedSpring(finalPercentageEnd, currentPercentageEnd);
      }
      else {
          currentPercentageStart = finalPercentageStart;
          currentPercentageEnd   = finalPercentageEnd;
          flagMaxValueChecked = true;
      }

      float currentPercentageEndScaled = currentPercentageEnd * 1000.0f;
      float currentPercentageStartScaled = currentPercentageStart * 1000.0f;

      glBegin(GL_POLYGON);
        for (int currentSegment  = static_cast<int>(currentPercentageStartScaled);
                 currentSegment != static_cast<int>(currentPercentageEndScaled);  ++currentSegment)
        {
            GLfloat x = -outterRadius  * cosf(thetaHighPolygonCount*currentSegment);
            GLfloat y = outterRadius * sinf(thetaHighPolygonCount*currentSegment);
            if (showingIncome) {
                int r = 0, g = 0, b = 0;
                getColorCode(colorGroupIncomeSelected, r, g, b);
                glColor3ub(r, g, b);
            } else if (!showingIncome) {
                int r = 0, g = 0, b = 0;
                getColorCode(colorGroupExpensesSelected, r, g, b);
                glColor3ub(r, g, b);
            }
            glVertex3f(centerX, centerY, 0.0);
            glVertex3f(centerX + x, centerY + y, 0.0);

            x = -outterRadius * cos(thetaHighPolygonCount*(currentSegment+1));
            y = outterRadius * sin(thetaHighPolygonCount*(currentSegment+1));

            glVertex3f(centerX + x, centerY + y, 0.0);
        }
      glEnd();
      /////////////////////////////////////////////////////////////////////

      //DRAW HERE SEMI-TRANSPARENT LOW POLYGON CIRCLE (Small circumference for stetics)
      glBegin(GL_POLYGON);
      r = innerRadius2;
        for (int side = 0; side <= numberSegments; ++side)
          {
             GLfloat x =  r * cos(theta*side);
             GLfloat y = -r * sin(theta*side);
             glColor4f(0.85f, 0.85f, 0.85f, 0.12f);
             glVertex3f(centerX + x, centerY + y, 0.0);
          }
       glEnd();
       //DRAW HERE CIRCLE IN CENTER TO BETTER VISUALIZE TEXT
      glBegin(GL_POLYGON);
      r = innerRadius;
        for (int side = 0; side <= numberSegments; ++side)
          {
             GLfloat x =  r * cos(theta*side);
             GLfloat y = -r * sin(theta*side);
             if (showingIncome) {
                 int r = 0, g = 0, b = 0;
                 getColorCode(colorGroupIncomeBackground, r, g, b);
                 glColor3ub(r, g, b);
             } else if (!showingIncome) {
                 int r = 0, g = 0, b = 0;
                 getColorCode(colorGroupExpensesBackground, r, g, b);
                 glColor3ub(r, g, b);
             }
             glVertex3f(centerX + x, centerY + y, 0.0);
          }
       glEnd();


        glDisable(GL_BLEND);
        glFlush();

        //DRAW TEXT HERE
       QPainter painter(this);
       painter.setRenderHint(QPainter::Antialiasing, true);
       if (showingIncome) {
           int r = 0, g = 0, b = 0;
           getColorCode(colorGroupIncomeSelected, r, g, b);
           glColor3ub(r, g, b);
           painter.setPen(QColor(r, g, b));
       } else if (!showingIncome) {
           int r = 0, g = 0, b = 0;
           getColorCode(colorGroupExpensesSelected, r, g, b);
           glColor3ub(r, g, b);
           painter.setPen(QColor(r, g, b));
       }

       QFont iFont;
       iFont.setFamily(iFont.defaultFamily());
       iFont.setPointSizeF(10);
       painter.setFont(iFont);

        if (amountOfSelectedGroup >= 0.0){
            if (currentLanguage == GERMAN){
                std::string percentagetInGerman = getAmountAsStringInGermanFormat(static_cast<double>((finalPercentageEnd-finalPercentageStart)*100.0f));
                painter.drawText(rectangleTextPercentage, Qt::AlignCenter, QString::fromStdString(percentagetInGerman)+"%");

                QString amountInGerman = QString::fromStdString(getAmountAsStringInGermanFormat(amountOfSelectedGroup, 1));
                QString currencySymbol = QString::fromStdString(getCurrenySymbol(currentCurrency));

                if (currencySymbol == "$") {
                    QRect tmpRect = QRect(rectangleTextAmount.left()-5, rectangleTextAmount.top(), rectangleTextAmount.width(), rectangleTextAmount.height());
                    painter.drawText(tmpRect, Qt::AlignCenter,  QString(currencySymbol + amountInGerman));
                } else {
                    painter.drawText(rectangleTextAmount, Qt::AlignCenter,   QString(amountInGerman + " " + currencySymbol));
                }

            } else {
                painter.drawText(rectangleTextPercentage, Qt::AlignCenter,
                                 QString::number((finalPercentageEnd-finalPercentageStart)*100.0f, 0, 2)+"%");

                QString currencySymbol = QString::fromStdString(getCurrenySymbol(currentCurrency));
                if (currencySymbol == "$") {
                    QRect tmpRect = QRect(rectangleTextAmount.left()-5, rectangleTextAmount.top(), rectangleTextAmount.width(), rectangleTextAmount.height());
                    painter.drawText(tmpRect, Qt::AlignCenter,
                                 currencySymbol+QString::fromStdString(getAmountAsStringFormatted(amountOfSelectedGroup, 1)));
                }
                else {
                    painter.drawText(rectangleTextAmount, Qt::AlignCenter,
                                 QString::fromStdString(getAmountAsStringFormatted(amountOfSelectedGroup, 1))+" "+currencySymbol);
                }
            }
        }
        painter.end();

        if (flagMaxValueChecked) {
            timer.stop();
        }
}

void GroupPieChartWidget::paintGL()
{
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();
    glOrtho(0.0, this->width(), 0.0, this->height(), 0.0, 1.0);
    glClearColor(0.0f,0.0f,0.0f,0.0f);
    drawGroupChart();
}

void GroupPieChartWidget::initializeGL()
{
}

void GroupPieChartWidget::resizeGL(int w, int h)
{
    updateSpace();
    update();
}

void GroupPieChartWidget::resetFLags()
{
    flagMaxValueChecked = false;
    if (!timer.isActive()) {
        timer.start(35);
    }
}

inline float GroupPieChartWidget::dampedSpring(float targetPosition, float &currentPosition)
{
    double SPRING_CONST             = 100.0;
    float timeStep                  = 0.035f;
    float currentVelocity           = 0.005f;
    float currentDistanceToTarget   = targetPosition-currentPosition;
    float springForce               = currentDistanceToTarget * (static_cast<float>(SPRING_CONST));
    float dampingForce              = (-currentVelocity) * 2 * (static_cast<float>(sqrt(SPRING_CONST)));
    float resultingForce            = springForce + dampingForce;

    currentVelocity                 += (resultingForce * timeStep);

    float displacement              = currentVelocity * timeStep;

    currentPosition                 += displacement;

    return currentPosition;
}
