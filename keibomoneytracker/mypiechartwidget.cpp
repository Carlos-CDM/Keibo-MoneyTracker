#include "mypiechartwidget.h"


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////OPENGL PIECHARTWIDGET CLASS DEFINITION//////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
MyPieChartWidget::MyPieChartWidget(QWidget *parent) :
    QGLWidget(parent)
{
       connect(&timerPie, SIGNAL(timeout()), this, SLOT(updateGL()));
       timerPie.start(250);
}

MyPieChartWidget::~MyPieChartWidget()
{
}

void MyPieChartWidget::initializeGL()
{
}

void MyPieChartWidget::paintGL()
{
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);       ///SET VIEW
    glLoadIdentity();
    gluOrtho2D(-1.0, 16.0, -1.0, 9.0);
    glViewport(-16, -9, 482, 290);
    drawCircle(0.7f);
}

void MyPieChartWidget::resizeGL(int w, int h)
{
  updateGL();
}


void MyPieChartWidget::drawCircle (float radius)
{
   const float DEG2RAD = 3.14159/180;
   glBegin(GL_LINE_LOOP);

   for (int i=0; i != 360; i++)
   {
      float degInRad = i*DEG2RAD;
      glVertex2f(cos(degInRad)*radius,sin(degInRad)*radius);
   }

   glEnd();
}
