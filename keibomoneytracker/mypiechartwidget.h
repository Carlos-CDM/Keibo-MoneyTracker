#ifndef MYPIECHARTWIDGET_H
#define MYPIECHARTWIDGET_H

#include <QTimer>
#include <QGLWidget>
#include <GL/gl.h>
#include <GL/glu.h>

class MyPieChartWidget : public QGLWidget
{
public:
    MyPieChartWidget(QWidget *parent = 0);
    ~MyPieChartWidget();

    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

private:
    QTimer timerPie;

    void drawCircle (float radius);
};

#endif // MYPIECHARTWIDGET_H
