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

#include "myopenglwidget.h"
#include <QToolTip>


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////OPENGL WIDGET CLASS DEFINITION/////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
MyOpenGLWidget::MyOpenGLWidget(QWidget *parent) :
    QOpenGLWidget(parent)
{
    QSurfaceFormat format;
    format.setSamples(12);
    this->setFormat(format);

    connect(&timer, SIGNAL(timeout()), this, SLOT(update()));
    timer.start(FRAMETIME_MS);

    this->setAttribute(Qt::WA_Hover);
    this->setMouseTracking(true);
}

MyOpenGLWidget::~MyOpenGLWidget()
{
}

void MyOpenGLWidget::calculateMouseXNormilizedPosition(const int &xInPixels) ///rename "calculateSelectedMonthByMouse" this function is being called everytime mouse moves over the widget
{
    int intervalInSelection = -1;

    for (int s = 0; s!=12; ++s){
        if ((xInPixels>monthXpStartIncome[s]) && (xInPixels<monthXpFinalOutcome[s]))
        {
            intervalInSelection = s;
            break;
        }
    }

    if ((intervalInSelection != selectedMonthByMouse) && (intervalInSelection >= 0)) {
        selectedMonthByMouse = intervalInSelection;
    }
}

void MyOpenGLWidget::drawShadowOnPointedMonth()
{
    if (selectedMonthByMouse>=0 && selectedMonthByMouse<12)
    {
      int selectedMonthId = selectedMonthByMouse;

      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
      glColor4f(0.75f,0.75f,0.75f,0.25f);
      glRectf(monthXpStartIncome[selectedMonthId], boardY1,
              monthXpFinalOutcome[selectedMonthId], boardY2);
    }
}

int MyOpenGLWidget::getSelectedMonthByClick() //If click was done on any Area belonging to a month returns the month number, otherwise it returns -1
{
    if (mouseWasClicked)
    {
        mouseWasClicked = false;
        return (selectedMonthByMouse);
    }
    else return -1;
}

void MyOpenGLWidget::processMouseClick()
{
    QPoint currentCoodinates = mapFromGlobal(QCursor::pos());
    calculateMouseXNormilizedPosition(currentCoodinates.x());
    mouseWasClicked = true;
}

bool MyOpenGLWidget::event(QEvent * e)
{
   switch(e->type())
    {
     case QEvent::MouseButtonPress:
          {
            //
          }
     return true;
     case QEvent::MouseMove:
          {
              selectedMonthByMouse = -1;
              QPoint currentCoodinates = mapFromGlobal(QCursor::pos());
              calculateMouseXNormilizedPosition(currentCoodinates.x());
              if(selectedMonthByMouse >= 0){
                QString text = QString::fromStdString(getMonthInLanguage(selectedMonthByMouse, currentLanguage));
                QToolTip::showText(QCursor::pos(), text);
              }
              else {
                QToolTip::hideText();
              }
              if (!timer.isActive()){ timer.start(FRAMETIME_MS);}
          }
        return true;
    case QEvent::Leave:
          {
              selectedMonthByMouse = -1;
              if (!timer.isActive()){ timer.start(FRAMETIME_MS);}
              selectedMonthByMouse = -1;
          }
        return true;
    case QEvent::Enter:
          {
               //
          }
        return true;
     default:
        break;
    }
  return QWidget::event(e);
}

void MyOpenGLWidget::drawScaleBoard()
{
    drawShadowOnPointedMonth();

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glColor3f(0.40f, 0.40f, 0.40f);
    glRectf(boardX1, boardY1, boardX2, boardY2);

    for (int y = 0; y!=4; ++y)
    {
        glLineWidth(1.0);
        glBegin(GL_LINES);
        glVertex2f(boardX1, heightHorizontalScaleBoardLines[y]);
        glVertex2f(boardX2, heightHorizontalScaleBoardLines[y]);
        glEnd();
        glFlush();
    }

    glBegin(GL_LINES);
    glVertex2f(boardX1, heightHorizontalScaleBoardLines[4]);
    glVertex2f(boardX2, heightHorizontalScaleBoardLines[4]);
    glEnd();
}

void MyOpenGLWidget::drawQuantities()
{
    if (!painter.isActive()){
        //this->makeCurrent();
        painter.begin(this);
    }
    if (painter.isActive())
    {
       painter.setRenderHint(QPainter::Antialiasing, true);
       glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

       for (int i = 0; i != 5; ++i){
           float top    = heightScaleBoardQuantities[i];
           float left   = leftQuantities;
           float width  = 100.0f;
           float height = 20.0f;
           QString txt = QString::number(scaleValues[4-i], 0 , 0)+" "+QString::fromStdString(getCurrenySymbol(currentCurrency));

           if (useBiggerFont){
               //QFont iFont = QFont("URW Gothic", 11, -1, false);
               QFont iFont;
               iFont.setFamily(iFont.defaultFamily());
               iFont.setPointSizeF(11);
               painter.setFont(iFont);
           } else{
              if (scaleValues[4-i] >= 1000000.0){
                  //QFont iFont = QFont("URW Gothic", 8, -1, false);
                  QFont iFont;
                  iFont.setFamily(iFont.defaultFamily());
                  iFont.setPointSizeF(8);
                  painter.setFont(iFont);
              } else {
                  //QFont iFont = QFont("URW Gothic", 9, -1, false);
                  QFont iFont;
                  iFont.setFamily(iFont.defaultFamily());
                  iFont.setPointSizeF(9);
                  painter.setFont(iFont);
              }
           }
           painter.drawText(QRect(left, top, width, height), Qt::AlignLeft,
                                        txt);
       }
       painter.end();
    }
}

void MyOpenGLWidget::updateSpace()
{
        float totalWidth = this->width();
        float totalHeigth = this->height();

        if (totalWidth > 0.0f && totalHeigth > 0.0f)
        {
            Ax = totalWidth*0.05f;
            Bx = totalWidth*0.82f;
            Cx = totalWidth*0.15f;
            Dx = Bx/12.0f;

            //Starting and final points in X of bars
            for (int a=0; a!=12; ++a)
            {
                monthXpStartIncome[a]=Ax+(a*Dx)+(Dx*0.05f);
                monthXpStartOutcome[a]=monthXpStartIncome[a]+(Dx*0.36f);

                monthXpFinalIncome[a] = monthXpStartOutcome[a];
                monthXpFinalOutcome[a] = monthXpStartOutcome[a]+(Dx*0.36f);
            }

            //Starting point and length in Y of bars
            Ay = totalHeigth*0.025f;
            By = totalHeigth*0.925f;    //This is also the maximum height a bar can have

            //Calculate offsets for scale board, free space between bars and limits of rectangle (board)
            offsetWidth  = totalWidth*0.025f;
            offsetHeigth = totalHeigth*0.025f;

            //Board points
            boardX1 = Ax-offsetWidth;
            boardY1 = Ay;
            boardX2 = Ax+Bx+offsetWidth;
            boardY2 = Ay+By+offsetHeigth;

            //Height for horizontal ScaleBoard lines
            heightHorizontalScaleBoardLines[0] = (By*0.2f)+Ay;
            heightHorizontalScaleBoardLines[1] = By*0.4f+Ay;
            heightHorizontalScaleBoardLines[2] = By*0.6f+Ay;
            heightHorizontalScaleBoardLines[3] = By*0.8f+Ay;
            heightHorizontalScaleBoardLines[4] = By+Ay;

            //Height for for Quantities of ScaleBoard. These are inverted to the OpenGL space.
            heightScaleBoardQuantities[0] = totalHeigth - heightHorizontalScaleBoardLines[4]-3.0f;
            heightScaleBoardQuantities[1] = totalHeigth - heightHorizontalScaleBoardLines[3]-3.0f;
            heightScaleBoardQuantities[2] = totalHeigth - heightHorizontalScaleBoardLines[2]-3.0f;
            heightScaleBoardQuantities[3] = totalHeigth - heightHorizontalScaleBoardLines[1]-3.0f;
            heightScaleBoardQuantities[4] = totalHeigth - heightHorizontalScaleBoardLines[0]-3.0f;

            //Starting position in X for Quantities
            leftQuantities = Ax+Bx+offsetWidth+3.0f;

            //std::cout<<"SPACE UPDATED IN BAR CHART WIDGET\n";
            if (totalWidth > 750){
                useBiggerFont = true;
            } else {
                useBiggerFont = false;
            }
        }
}

inline float MyOpenGLWidget::dampedSpring(GLfloat targetPosition, GLfloat &currentPosition)
{
    double SPRING_CONST             = 150.0;
    float timeStep                  = 0.031f;
    float currentVelocity           = 2.5f;
    float currentDistanceToTarget   = targetPosition-currentPosition;
    float springForce               = currentDistanceToTarget * (static_cast<float>(SPRING_CONST));
    float dampingForce              = (-currentVelocity) * 2 * (static_cast<float>(sqrt(SPRING_CONST)));
    float resultingForce            = springForce + dampingForce;

    currentVelocity                 += (resultingForce * timeStep);

    float displacement              = currentVelocity * timeStep;

    currentPosition                 += displacement;

    return currentPosition;
}

void MyOpenGLWidget::drawChart()
{
    //DRAW INCOME
    for (int x = 0; x!=12; ++x)
    {
        if (x == Highlighted)
        {
            int r = 0, g = 0, b = 0;
            getColorCode(colorBarIncomeSelected, r, g, b);
            glColor3ub(r, g, b);
        }
        else
        {
            int r = 0, g = 0, b = 0;
            getColorCode(colorBarIncomeUnselected, r, g, b);
            glColor3ub(r, g, b);
        }

        float finalYpDimension = 0.0f;
        if (validYpFinalIncome[x]){
            finalYpDimension = (monthYpFinalIncome[x])*(By);
        } else {
            finalYpDimension = 1.0f;
        }

        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        if (monthYpCurrentIncome[x] < (finalYpDimension-2.0f)) {
            GLfloat tempCurrentY= monthYpCurrentIncome[x];
            std::future<float> futVal= std::async(std::launch::async, &MyOpenGLWidget::dampedSpring, this, finalYpDimension+4.0f, std::ref(tempCurrentY));
            futVal.get();
            monthYpCurrentIncome[x] = tempCurrentY;
            glRectf(monthXpStartIncome[x], Ay, monthXpFinalIncome[x], monthYpCurrentIncome[x]+Ay);
            glColor3d(0.1, 0.1, 0.1);
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            glRectf(monthXpStartIncome[x], Ay, monthXpFinalIncome[x], monthYpCurrentIncome[x]+Ay);
        }
        else if (monthYpCurrentIncome[x] > (finalYpDimension+2.0f)) {
            GLfloat tempCurrentY= monthYpCurrentIncome[x];
            std::future<float> futVal= std::async(std::launch::async, &MyOpenGLWidget::dampedSpring, this, finalYpDimension-4.0f, std::ref(tempCurrentY));
            futVal.get();
            monthYpCurrentIncome[x] = tempCurrentY;
            glRectf(monthXpStartIncome[x], Ay, monthXpFinalIncome[x], monthYpCurrentIncome[x]+Ay);
            glColor3d(0.1, 0.1, 0.1);
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            glRectf(monthXpStartIncome[x], Ay, monthXpFinalIncome[x], monthYpCurrentIncome[x]+Ay);
        }
        else {
            monthYpCurrentIncome[x] = finalYpDimension;
            glRectf(monthXpStartIncome[x], Ay, monthXpFinalIncome[x], monthYpCurrentIncome[x]+Ay);
            glColor3d(0.1, 0.1, 0.1);
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            glRectf(monthXpStartIncome[x], Ay, monthXpFinalIncome[x], monthYpCurrentIncome[x]+Ay);

            if (flagMaxValueOfBarChecked[x] == false){
                flagMaxValueOfBarChecked[x] = true;
            }
        }
    }

    //DRAW OUTCOME
    for (int x = 0; x!=12; ++x)
    {
        if (x == Highlighted)
        {
            int r = 0, g = 0, b = 0;
            getColorCode(colorBarExpensesSelected, r, g, b);
            glColor3ub(r, g, b);
        }
        else
        {
            int r = 0, g = 0, b = 0;
            getColorCode(colorBarExpensesUnselected, r, g, b);
            glColor3ub(r, g, b);
        }

        float finalYpDimension = 0.0f;
        if (validYpFinalOutcome[x]){
            finalYpDimension = (monthYpFinalOutcome[x])*(By);
        } else {
            finalYpDimension = 1.0f;
        }
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        if (monthYpCurrentOutcome[x] < (finalYpDimension-2.0f)) {
            GLfloat tempCurrentY= monthYpCurrentOutcome[x];
            std::future<float> futVal= std::async(std::launch::async, &MyOpenGLWidget::dampedSpring, this, finalYpDimension+4.0f, std::ref(tempCurrentY));
            futVal.get();
            monthYpCurrentOutcome[x] = tempCurrentY;
            glRectf(monthXpStartOutcome[x], Ay, monthXpFinalOutcome[x], monthYpCurrentOutcome[x]+Ay);
            glColor3d(0.1, 0.1, 0.1);
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            glRectf(monthXpStartOutcome[x], Ay, monthXpFinalOutcome[x], monthYpCurrentOutcome[x]+Ay);
        }
        else if (monthYpCurrentOutcome[x] > (finalYpDimension+2.0f)) {
            GLfloat tempCurrentY= monthYpCurrentOutcome[x];
            std::future<float> futVal= std::async(std::launch::async, &MyOpenGLWidget::dampedSpring, this, finalYpDimension-4.0f, std::ref(tempCurrentY));
            futVal.get();
            monthYpCurrentOutcome[x] = tempCurrentY;
            glRectf(monthXpStartOutcome[x], Ay, monthXpFinalOutcome[x], monthYpCurrentOutcome[x]+Ay);
            glColor3d(0.1, 0.1, 0.1);
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            glRectf(monthXpStartOutcome[x], Ay, monthXpFinalOutcome[x], monthYpCurrentOutcome[x]+Ay);
        }
        else {
            monthYpCurrentOutcome[x] = finalYpDimension;
            glRectf(monthXpStartOutcome[x], Ay, monthXpFinalOutcome[x], monthYpCurrentOutcome[x]+Ay);
            glColor3d(0.1, 0.1, 0.1);
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            glRectf(monthXpStartOutcome[x], Ay, monthXpFinalOutcome[x], monthYpCurrentOutcome[x]+Ay);

            if (flagMaxValueOfBarChecked[x+12] == false){
                flagMaxValueOfBarChecked[x+12] = true;
            }
        }
    }
    bool allFlagsChecked = true;
    for (int i = 0; i != 24; ++i){
        if (flagMaxValueOfBarChecked[i] == false){
            allFlagsChecked = false;
        }
    }
    if (allFlagsChecked){
        timer.stop();
    }
}

void MyOpenGLWidget::resetFLags()
{
    for (int i = 0; i != 24; ++i){
        flagMaxValueOfBarChecked[i] = false;
    }

    if (timer.isActive() == false) {
        timer.start(35);
    }
}


void MyOpenGLWidget::initializeGL()
{

}

void MyOpenGLWidget::paintGL()
{
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);       ///SET VIEW
    glLoadIdentity();

    this->setAttribute(Qt::WA_AlwaysStackOnTop);
    glOrtho(0.0, this->width(), 0.0, this->height(), 0.0, 1.0);

    float fr = 0.0f;
    float fg = 0.0f;
    float fb = 0.0f;
    float fa = 0.0f;
    if (colorBackground < 36)
    {
        int r, g, b;
        getColorCode(colorBackground, r, g, b);
        fr = (static_cast<float>(r))/255.0f;
        fg = (static_cast<float>(g))/255.0f;
        fb = (static_cast<float>(b))/255.0f;
        fa = 1.0f;
    }
    glClearColor(fr, fg, fb, fa);

    if (activationCounterBarBackgroundColor <= 2) //Workaround solution
    {
        update();
        ++activationCounterBarBackgroundColor;
    }

    drawScaleBoard();
    drawChart();
    drawQuantities();
}

void MyOpenGLWidget::resizeGL(int w, int h)
{
    update();
    updateSpace();
    resetFLags();
}
