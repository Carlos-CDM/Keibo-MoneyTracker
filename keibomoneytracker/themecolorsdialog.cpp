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

#include "themecolorsdialog.h"
#include "ui_themecolorsdialog.h"
#include "selectcolordialog.h"
#include "eraseconfirmation_dialog.h"
#include <iostream>
#include <QKeyEvent>

MonthBarChartColorWidget::MonthBarChartColorWidget(QWidget *parent) :
    QOpenGLWidget(parent)
{
    QSurfaceFormat format;
    format.setSamples(12);
    this->setFormat(format);
    this->setAttribute(Qt::WA_AlwaysStackOnTop);
    colorIncomeSelected = 2;
    colorIncomeUnselected = 0;
    colorOutcomeSelected = 10;
    colorOutcomeUnselected = 20;
    colorBackground = 0; //Transparent
    updateSpace();
    update();
}

MonthBarChartColorWidget::~MonthBarChartColorWidget()
{
}

void MonthBarChartColorWidget::drawScaleBoard()
{
    glPolygonMode(GL_FRONT, GL_LINE);
    glColor3f(0.1f, 0.1f, 0.1f);
    glRectf(boardX1, boardY1, boardX2, boardY2);

    for (int y = 0; y!=4; ++y)
    {
        glColor3f(0.50f, 0.50f, 0.50f);
        //glLineStipple(3, 0xAAAA);
        //glEnable(GL_LINE_STIPPLE);
        glLineWidth(1.0);
        glBegin(GL_LINES);
        glVertex2f(boardX1, heightHorizontalScaleBoardLines[y]);
        glVertex2f(boardX2, heightHorizontalScaleBoardLines[y]);
        glEnd();
        //glDisable(GL_LINE_STIPPLE);
    }
    glBegin(GL_LINES);
    glVertex2f(boardX1, heightHorizontalScaleBoardLines[4]);
    glVertex2f(boardX2, heightHorizontalScaleBoardLines[4]);
    glEnd();
}

void MonthBarChartColorWidget::updateSpace()
{
    float totalWidth = this->width();
    float totalHeigth = this->height();

    Ax = totalWidth*0.05f;
    Bx = totalWidth*0.82f;
    Cx = totalWidth*0.15f;
    Dx = Bx/4.0f;

    //Starting and final points in X of bars
    for (int a=0; a!=4; ++a)
    {
        monthXpStartIncome[a]=Ax+(a*Dx)+(Dx*0.05f);
        monthXpStartOutcome[a]=monthXpStartIncome[a]+(Dx*0.36f);

        monthXpFinalIncome[a] = monthXpStartOutcome[a];
        monthXpFinalOutcome[a] = monthXpStartOutcome[a]+(Dx*0.36f);
    }

    //Starting point and length of bars in Y
    Ay = totalHeigth*0.05f;
    By = totalHeigth*0.90f;    //This is also the maximum height a bar can have

    //Calculate offsets for scale board, only Scaleboard!
    offsetWidth  = totalWidth*0.025f;
    offsetHeigth = totalHeigth*0.025f;

    //Board points
    boardX1 = Ax-offsetWidth;
    boardY1 = Ay;
    boardX2 = Ax+Bx+offsetWidth;
    boardY2 = Ay+By+offsetHeigth;

    //Height for horizontal ScaleBoard lines
    heightHorizontalScaleBoardLines[0] = By*0.2f+Ay;
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

    //Set constant values for bars
    float normalizeHeight = totalHeigth - ( totalHeigth*0.10f );

    monthYpIncomeFinal[0] = (400.0f/500.0f)*normalizeHeight;
    monthYpIncomeFinal[1] = (300.0f/500.0f)*normalizeHeight;
    monthYpIncomeFinal[2] = (500.0f/500.0f)*normalizeHeight;
    monthYpIncomeFinal[3] = (350.0f/500.0f)*normalizeHeight;

    monthYpOutcomeFinal[0] = (200.0f/500.0f)*normalizeHeight;
    monthYpOutcomeFinal[1] = (150.0f/500.0f)*normalizeHeight;
    monthYpOutcomeFinal[2] = (275.0f/500.0f)*normalizeHeight;
    monthYpOutcomeFinal[3] = (150.0f/500.0f)*normalizeHeight;
}

void MonthBarChartColorWidget::setBarColors(const int &incomeSelected,  const int &incomeUnselected,
                                            const int &outcomeSelected, const int &outcomeUnselected)
{
    colorIncomeSelected   = incomeSelected;
    colorIncomeUnselected = incomeUnselected;

    colorOutcomeSelected   = outcomeSelected;
    colorOutcomeUnselected = outcomeUnselected;
}

void MonthBarChartColorWidget::setBackgroundColor(const int &background)
{
    colorBackground = background;
}

void MonthBarChartColorWidget::drawMonthChart()
{
    //DRAW INCOME
    for (int x = 0; x!=4; ++x)
    {
        if (x == 2)
        {
            int r= 0, g = 0, b = 0;
            getColorCode(colorIncomeSelected, r, g, b);
            glColor3ub(r, g, b);
        }
        else
        {
            int r= 0, g = 0, b = 0;
            getColorCode(colorIncomeUnselected, r, g, b);
            glColor3ub(r, g, b);
        }
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);     //Using only GL_FRONT draws things upside down - WEY!
        glRectf(monthXpStartIncome[x], Ay, monthXpFinalIncome[x], monthYpIncomeFinal[x]+Ay);
        glColor3ub(25, 25, 25);
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);     //Using only GL_FRONT draws things upside down - WEY!
        glRectf(monthXpStartIncome[x], Ay, monthXpFinalIncome[x], monthYpIncomeFinal[x]+Ay);
    }

    //DRAW OUTCOME
    for (int x = 0; x!=4; ++x)
    {
        if (x == 2)
        {
            int r, g, b;
            getColorCode(colorOutcomeSelected, r, g, b);
            glColor3ub(r, g, b);
        }
        else
        {
            int r, g, b;
            getColorCode(colorOutcomeUnselected, r, g, b);
            glColor3ub(r, g, b);
        }
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);       //Using only GL_FRONT draws things upside down - WEY!
        glRectf(monthXpStartOutcome[x], Ay, monthXpFinalOutcome[x], monthYpOutcomeFinal[x]+Ay);
        glColor3ub(25, 25, 25);
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);       //Using only GL_FRONT draws things upside down - WEY!
        glRectf(monthXpStartOutcome[x], Ay, monthXpFinalOutcome[x], monthYpOutcomeFinal[x]+Ay);
    }
}

void MonthBarChartColorWidget::initializeGL()
{
    update();
}

void MonthBarChartColorWidget::paintGL()
{
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();

    glMatrixMode(GL_MODELVIEW);       ///SET VIEW
    glPushMatrix();
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
    drawScaleBoard();
    drawQuantities();
    drawMonthChart();

    if (activationCounterBarBackgroundColor <= 2) //Workaround solution
    {
        update();
        ++activationCounterBarBackgroundColor;
        //std::cout<<"Workaround Solution ThemeColorDialog - counter value: "<<activationCounterBarBackgroundColor<<'\n';
    }
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
}

void MonthBarChartColorWidget::resizeGL(int w, int h)
{
    updateSpace();
    update();
}

void MonthBarChartColorWidget::drawQuantities()
{
    if (!painter.isActive()){
        painter.begin(this);
    }
    if (painter.isActive())
    {
       glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);  //Using only GL_FRONT draws things upside down - WEY!
       //QFont iFont = QFont("URW Gothic", 10, -1, false);
       QFont iFont;
       iFont.setFamily(iFont.defaultFamily());
       iFont.setPointSizeF(9);
       painter.setFont(iFont);

       for (int i = 0; i != 5; ++i){
           float top    = heightScaleBoardQuantities[i];
           float left   = leftQuantities;
           float width  = 100.0f;
           float height = 20.0f;
           QString txt = QString::number(scaleValues[4-i], 0 , 0)+" €";
           painter.drawText(QRect(left, top, width, height), Qt::AlignLeft,
                                        txt);
       }
       painter.end();
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
GroupPieChartColorWidget::GroupPieChartColorWidget(QWidget *parent) :
    QOpenGLWidget(parent)
{
    QSurfaceFormat format;
    format.setSamples(12);
    this->setFormat(format);
    this->setAttribute(Qt::WA_AlwaysStackOnTop);
    updateSpace();
    update();
}

GroupPieChartColorWidget::~GroupPieChartColorWidget()
{
}

void GroupPieChartColorWidget::updateSpace()
{
    float totalWidth  = this->width();
    float totalHeigth = this->height();
    float maxDiameter  = 0.0f;

    if (totalHeigth>totalWidth)
    {
        maxDiameter = totalWidth;
    } else if (totalHeigth<=totalWidth) {
        maxDiameter = totalHeigth;
    }

    centerX = totalWidth*0.5f;
    centerY = totalHeigth*0.5f;
    outterRadius  = maxDiameter*0.50f;

    innerRadius   = maxDiameter*0.300f;
    innerRadius2  = maxDiameter*0.345f;

    int width  = 100;
    int height = 15;

    int leftPercentage   = (totalWidth/2)-48;
    int topPercentage    = (totalHeigth/2)+5;
    rectangleTextPercentage = QRect(leftPercentage, topPercentage, width, height);

    int leftAmount   = (totalWidth/2)-49;
    int topAmount    = (totalHeigth/2)-12;
    rectangleTextAmount = QRect(leftAmount, topAmount, width, height);

    theta = (2*PI)/numberSegments; //40 Segments for complete circle,
    thetaColorPolygon =PI/segmentsColorPolygon; //20 Segments for half circles. 50% will show selected group, 50% unselected

    //std::cout<<"SPACE COLOR PIE CHART UPDATED"<<'\n';
}


void GroupPieChartColorWidget::drawGroupChart()
{
     glBegin(GL_POLYGON);
     float r = outterRadius;
       for (int side = 0; side <= segmentsColorPolygon; ++side)
         {
           GLfloat x =  r * cos((thetaColorPolygon*side));
           GLfloat y = -r * sin((thetaColorPolygon*side));
               int r, g, b; //OPTIMIZE OUTSIDE FOR LOOP
               getColorCode(colorUnselected, r, g, b); //UNSELECTED
               glColor3ub(r, g, b);
           glVertex3f(centerX + x, centerY + y, 0.0);
         }
      glEnd();

      glEnable(GL_BLEND);
      glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    /////////////////////////////////////////////////////////////////////
    //DRAW HERE THE ARC CORRESPONDING TO THE PERCENTAGE OF SELECTED GROUP

      glBegin(GL_POLYGON);
      for (int side = 0; side <= segmentsColorPolygon; ++side)
        {
           GLfloat x =  r * cos((thetaColorPolygon*side)+PI); //+ PI second half of pie will be not selected group
           GLfloat y = -r * sin((thetaColorPolygon*side)+PI);
               int r, g, b;//OPTIMIZE OUTSIDE FOR LOOP
               getColorCode(colorSelected, r, g, b); //SELECTED
               glColor3ub(r, g, b);
           glVertex3f(centerX + x, centerY + y, 0.0);
        }

      glEnd();
      /////////////////////////////////////////////////////////////////////

      //DRAW HERE SEMI-TRANSPARENT LOW POLYGON CIRCLE
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
                 int r, g, b;
                 getColorCode(colorBackground, r, g, b);
                 glColor3ub(r, g, b);
             glVertex3f(centerX + x, centerY + y, 0.0);
          }
       glEnd();

       glDisable(GL_BLEND);
       glFlush();

        //DRAW TEXT HERE
       QPainter painter(this);
       painter.setRenderHint(QPainter::Antialiasing, true);
       int rp, gp, bp;
       getColorCode(colorSelected, rp, gp, bp);
       painter.setPen(QColor(rp, gp, bp));   //AMOUNT OF SELECTED
        painter.setFont({"Helvetica", 10});
        if (amountOfSelectedGroup > 0.0f){
        painter.drawText(rectangleTextPercentage, Qt::AlignCenter,
                         QString::number((finalPercentageEnd-finalPercentageStart), 0, 2)+"%");
        }
        painter.drawText(rectangleTextAmount, Qt::AlignCenter,
                         QString::number(amountOfSelectedGroup, 0, 2));
        painter.end();
}

void GroupPieChartColorWidget::setColors(int selected, int unselected, int background)
{
    colorSelected = selected;
    colorUnselected = unselected;
    colorBackground = background;

    this->update();
}

void GroupPieChartColorWidget::paintGL()
{
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();
    glOrtho(0.0, this->width(), 0.0, this->height(), 0.0, 1.0);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    drawGroupChart();
}

void GroupPieChartColorWidget::initializeGL()
{
}

void GroupPieChartColorWidget::resizeGL(int w, int h)
{
    updateSpace();
    update();
}
///////////////////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////////////////////////


ThemeColorsDialog::ThemeColorsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ThemeColorsDialog)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_Hover);
    this->setMouseTracking(true);
    this->ui->checkBox->installEventFilter(this);
    this->ui->tableWidget->setTabKeyNavigation(false);
    this->ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    this->ui->tableWidget->setFocusPolicy(Qt::NoFocus);
    this->ui->labelTextCheckBox->setWordWrap(true);

    ui->label_ColorGroupSelected->installEventFilter(this);
    ui->label_ColorGroupUnselected->installEventFilter(this);
    ui->label_ColorGroupBackground->installEventFilter(this);
    ui->label_ColorBarSelected->installEventFilter(this);
    ui->label_ColorBarUnselected->installEventFilter(this);
    ui->label_ColorBarBackground->installEventFilter(this);
    ui->label_ColorIncomeAmountText->installEventFilter(this);
    ui->buttonSaveAndSet->installEventFilter(this);
    ui->comboBox->installEventFilter(this);
    ui->comboBoxOverallTheme->installEventFilter(this);

    ui->radioGroupIncome->setChecked(true); //Radio button for groups
    ui->radioBarIncome->setChecked(true);

    ui->tableWidget->setColumnCount(3);
    ui->tableWidget->setColumnWidth(0,100);
    ui->tableWidget->setColumnWidth(1,60);
    ui->tableWidget->setColumnWidth(2,35);

    ui->tableWidget->setRowCount(5);
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);

    ///--------------------------------------------------------------------------///--------------------------------------------------------------------------///
    //Set predefined color presets
    addColorConfiguration("Set 1",
                          13, 4, 9, 7, 36, 13, 4, 9, 16, 8, 8, 13, true, false
                          );
    addColorConfiguration("Set 2",
                          21, 3, 14, 6, 36, 21, 3, 14, 6, 8, 8, 21, true, false
                          );
    addColorConfiguration("Set 3",
                          13, 4, 19, 7, 36, 13, 4, 10, 7, 8, 8, 13, true, false
                          );
    addColorConfiguration("Set 4",
                          15, 6, 11, 7, 36, 15, 6, 11, 7, 7, 26, 6, true, true
                          );
    addColorConfiguration("Set 5",
                          13, 4, 19, 7, 36, 13, 4, 10, 7, 26, 26, 13, true, true
                          );

    //Set Light and Dark Theme Options
    this->allowUpdateColorsInOverallDarkThemeComboBox = false;
    this->ui->comboBoxOverallTheme->addItem("Light");
    this->ui->comboBoxOverallTheme->addItem("Dark");
    this->allowUpdateColorsInOverallDarkThemeComboBox = true;

    this->setFixedSize(this->width(), this->height());
}

ThemeColorsDialog::~ThemeColorsDialog()
{
    delete ui;
}

void ThemeColorsDialog::setLanguage(const Language &currentLanguage)
{
    iLanguage = currentLanguage;
    if (iLanguage == ENGLISH) {
        this->setWindowTitle(" Appearance");
        this->allowUpdateColorsInOverallDarkThemeComboBox = false;
        this->ui->comboBoxOverallTheme->setItemText(0, "Light");
        this->ui->comboBoxOverallTheme->setItemText(1, "Dark");
        this->allowUpdateColorsInOverallDarkThemeComboBox = true;

        this->ui->labelTextPreset->setText("Preset:");
        this->ui->labelTextPreview->setText("Preview");

        this->ui->radioBarIncome->setText("Income");
        this->ui->radioBarExpenses->setText("Expenses");
        this->ui->labelTextBarSelected->setText("Selected");
        this->ui->labelTextBarUnselected->setText("Unselected");
        this->ui->labelTextBarBackground->setText("Background");

        this->ui->radioGroupIncome->setText("Income");
        this->ui->radioGroupOutcome->setText("Expenses");
        this->ui->labelTextGroupSelected->setText("Selected");
        this->ui->labelTextGroupUnselected->setText("Unselected");
        this->ui->labelTextGroupBackground->setText("Background");

        this->ui->labelTextOverallTheme->setText("Theme");
        this->ui->labelTextIncomeAmount->setText("Income amount");
        this->ui->labelTextCheckBox->setText("Monthly amount in color?                ");

        this->ui->labelTextIncomeInMonth->setText("Income in month");
        this->ui->labelTextExpensesInMonth->setText("Expenses in month");
        this->ui->groupBoxBar->setTitle("Monthly charts  ");
        this->ui->groupBoxPie->setTitle("Groups chart  ");
        this->ui->groupBoxTableButtons->setTitle("Others  ");
        this->ui->buttonSaveAndSet->setText("Save and set");
    }
    else if (iLanguage == GERMAN) {
        this->setWindowTitle(" Ansicht");
        this->allowUpdateColorsInOverallDarkThemeComboBox = false;
        this->ui->comboBoxOverallTheme->setItemText(0, "Hell");
        this->ui->comboBoxOverallTheme->setItemText(1, "Dunkel");
        this->allowUpdateColorsInOverallDarkThemeComboBox = true;
        this->ui->labelTextPreset->setText("Voreinstellung:");
        this->ui->labelTextPreview->setText("Vorschau");

        this->ui->radioBarIncome->setText("Einkommen");
        this->ui->radioBarExpenses->setText("Ausgaben");
        this->ui->labelTextBarSelected->setText("Ausgewählt");
        this->ui->labelTextBarUnselected->setText("Nicht ausgewählt");
        this->ui->labelTextBarBackground->setText("Hintergrund");

        this->ui->radioGroupIncome->setText("Einkommen");
        this->ui->radioGroupOutcome->setText("Ausgaben");
        this->ui->labelTextGroupSelected->setText("Ausgewählt");
        this->ui->labelTextGroupUnselected->setText("Nicht ausgewählt");
        this->ui->labelTextGroupBackground->setText("Hintergrund");

        this->ui->labelTextOverallTheme->setText("Thema");
        this->ui->labelTextIncomeAmount->setText("Einkommen Betrag");
        this->ui->labelTextCheckBox->setText("Monatliche Beiträge in Farbe?");

        this->ui->labelTextIncomeInMonth->setText("Monatliches Einkommen");
        this->ui->labelTextExpensesInMonth->setText("Monatliche Ausgabe");
        this->ui->groupBoxBar->setTitle("Monatliche Grafik  ");
        this->ui->groupBoxPie->setTitle("Gruppen Grafik  ");
        this->ui->groupBoxTableButtons->setTitle("Andere  ");
        this->ui->buttonSaveAndSet->setText("Speichen und schlißen");
    }
    else if (iLanguage == SPANISH) {
        this->setWindowTitle(" Apariencia");
        this->allowUpdateColorsInOverallDarkThemeComboBox = false;
        this->ui->comboBoxOverallTheme->setItemText(0, "Claro");
        this->ui->comboBoxOverallTheme->setItemText(1, "Oscuro");
        this->allowUpdateColorsInOverallDarkThemeComboBox = true;
        this->ui->labelTextPreset->setText("Preselección:");
        this->ui->labelTextPreview->setText("Vista previa");

        this->ui->radioBarIncome->setText("Ingreso");
        this->ui->radioBarExpenses->setText("Egreso");
        this->ui->labelTextBarSelected->setText("Seleccionado");
        this->ui->labelTextBarUnselected->setText("No seleccionado");
        this->ui->labelTextBarBackground->setText("Fondo");

        this->ui->radioGroupIncome->setText("Ingreso");
        this->ui->radioGroupOutcome->setText("Egreso");
        this->ui->labelTextGroupSelected->setText("Seleccionado");
        this->ui->labelTextGroupUnselected->setText("No seleccionado");
        this->ui->labelTextGroupBackground->setText("Fondo");

        this->ui->labelTextOverallTheme->setText("Tema");
        this->ui->labelTextIncomeAmount->setText("Monto de ingreso");
        this->ui->labelTextCheckBox->setText("¿Montos mensuales en color?        ");

        this->ui->labelTextIncomeInMonth->setText("Ingresos en mes:");
        this->ui->labelTextExpensesInMonth->setText("Egresos en mes:");
        this->ui->groupBoxBar->setTitle("Gráficos mensuales  ");
        this->ui->groupBoxPie->setTitle("Gráficos de grupos  ");
        this->ui->groupBoxTableButtons->setTitle("Otros  ");
        this->ui->buttonSaveAndSet->setText("Guardar y salir");
    }

    int item_Id = 0;
    for (int x = 1; x!= 6; ++x)
    {
        /////////////////////////////////FIRST COLUMN///////////////////////////////////
        ///--------------------------------------------------------------------------///
        if (x == 3){
            if (iLanguage == ENGLISH){
                ui->tableWidget->setItem(item_Id,0, new QTableWidgetItem (QString("Income"))); //Transaction name
            } else if (iLanguage == GERMAN) {
                ui->tableWidget->setItem(item_Id,0, new QTableWidgetItem (QString("Einkommen")));
            } else if (iLanguage == SPANISH) {
                ui->tableWidget->setItem(item_Id,0, new QTableWidgetItem (QString("Ingreso")));
            }
            ui->tableWidget->item(item_Id, 0)->setTextAlignment(Qt::AlignLeft);
            ui->tableWidget->item(item_Id, 0)->setTextAlignment(Qt::AlignBottom);
            ui->tableWidget->setWordWrap(false);
        } else {
            if (iLanguage == ENGLISH){
                ui->tableWidget->setItem(item_Id,0, new QTableWidgetItem (QString("Expense"))); //Transaction name
            } else if (iLanguage == GERMAN) {
                ui->tableWidget->setItem(item_Id,0, new QTableWidgetItem (QString("Ausgabe")));
            } else if (iLanguage == SPANISH) {
                ui->tableWidget->setItem(item_Id,0, new QTableWidgetItem (QString("Egreso")));
            }
            ui->tableWidget->item(item_Id, 0)->setTextAlignment(Qt::AlignLeft);
            ui->tableWidget->item(item_Id, 0)->setTextAlignment(Qt::AlignBottom);
            ui->tableWidget->setWordWrap(false);
        }

        /////////////////////////////////SECOND COLUMN//////////////////////////////////
        ///--------------------------------------------------------------------------///
        if (x == 3) {
            ui->tableWidget->setItem(item_Id,1, new QTableWidgetItem (QString("+1000")));
        } else {
            ui->tableWidget->setItem(item_Id,1, new QTableWidgetItem (QString("-")+QString::number(50*x))); //Amount
        }
        ui->tableWidget->item(item_Id,1)->setTextAlignment(Qt::AlignRight);
        ui->tableWidget->item(item_Id,1)->setTextAlignment(Qt::AlignBottom);
        /////////////////////////////////THIRD COLUMN///////////////////////////////////
        ///--------------------------------------------------------------------------///
        if (x == 3){
            ui->tableWidget->setItem(item_Id,2, new QTableWidgetItem (QString::number(7))); //Day
        } else {
            ui->tableWidget->setItem(item_Id,2, new QTableWidgetItem (QString::number(x*2))); //Day
        }
        ui->tableWidget->item(item_Id,2)->setTextAlignment(Qt::AlignRight);
        ui->tableWidget->item(item_Id,2)->setTextAlignment(Qt::AlignBottom);

        ui->tableWidget->setRowHeight(item_Id, 13);
        ++item_Id;
    }
}

QString ThemeColorsDialog::getStyleSheetString(QString objectType, int colorCode, bool useForBackground, bool useBorder)
{
    int r = 0, g = 0, b = 0;
    getColorCode(colorCode, r, g, b);
    QString StyleSheetString ;
    if (useForBackground)
    {
        if (useBorder)
        {
            bool useGrayBorder = false;
            if (colorCode == 4 ||
                colorCode == 7 ||
                colorCode == 8) {
                useGrayBorder = true;
            }
            if (useGrayBorder)
              {
                StyleSheetString = objectType+"{border: 1px solid gray;  background-color: rgb("+
                         QString::number(r)+
                         ","+
                         QString::number(g)+
                         ","+
                         QString::number(b)+
                         ");}";
              }
            else
              {
                if (colorCode != 36){
                StyleSheetString = objectType+"{border: 1px solid white; background-color: rgb("+
                         QString::number(r)+
                         ","+
                         QString::number(g)+
                         ","+
                         QString::number(b)+
                         ");}";
                } else {
                StyleSheetString = objectType+"{border: 1px solid white; background-color: rgba(255, 255, 255, 0);}"; //If transparent selected
                }
              }
        }
        else
        {
            if (colorCode != 36){
                if (objectType.isEmpty()){
                    StyleSheetString = "background-color: rgb("+
                             QString::number(r)+
                             ","+
                             QString::number(g)+
                             ","+
                             QString::number(b)+
                             ");";
                } else {
                    StyleSheetString = objectType+"{background-color: rgb("+
                             QString::number(r)+
                             ","+
                             QString::number(g)+
                             ","+
                             QString::number(b)+
                             ");}";
                }
            } else {
            StyleSheetString = objectType+"{border: 1px solid gray; background-color: rgba(255, 255, 255, 0);}"; //If transparent selected
            }
        }
    }
    else if (!useForBackground)
    {
        if (objectType.isEmpty()){
            StyleSheetString = "color: rgb("+
                     QString::number(r)+
                     ","+
                     QString::number(g)+
                     ","+
                     QString::number(b)+
                     ");";
        } else {
            StyleSheetString = objectType+"{color: rgb("+
                     QString::number(r)+
                     ","+
                     QString::number(g)+
                     ","+
                     QString::number(b)+
                     ");}";
        }

    }

    return StyleSheetString;
}

void ThemeColorsDialog::labelGroupSelectedClicked()
{
    if (showingIncomeGroups)
    {
        SelectColorDialog iColorDialog;
        iColorDialog.setLanguage(iLanguage);
        iColorDialog.setModal(true);
        iColorDialog.newColorWasSelected = false;
        iColorDialog.setOverallThemeStyleSheet(overallThemeStyleSheet);
        iColorDialog.exec();
        if (iColorDialog.newColorWasSelected)
        {
            bool switchToCustomTheme = false;
            std::cout<<"COLOR WAS PICKED - GROUP INCOME SELECTED: "<<iColorDialog.colorId<<'\n';
            if (currentColorTheme != colorConfigurationList.size()-1){
                switchToCustomTheme = true;
            }

            //If color was changed from Preset, then create an iterator pointing to last colorConfiguration (Custom config)
            std::vector<ColorConfiguration>::iterator currentColorThemeIter = colorConfigurationList.end()-1;
            if (!customColorsExist){
                //Copy current ColorConfiguration to customColorConfiguration
                std::vector<ColorConfiguration>::iterator previousColorThemeIter = colorConfigurationList.begin()+currentColorTheme;
                currentColorThemeIter->colorBarIncomeSelected = previousColorThemeIter->colorGroupIncomeSelected;
                currentColorThemeIter->colorBarIncomeUnselected = previousColorThemeIter->colorBarIncomeUnselected;
                currentColorThemeIter->colorBarExpensesSelected = previousColorThemeIter->colorBarExpensesSelected;
                currentColorThemeIter->colorBarExpensesUnselected = previousColorThemeIter->colorBarExpensesUnselected;
                //currentColorThemeIter->colorGroupIncomeSelected = previousColorThemeIter->colorGroupIncomeSelected;
                currentColorThemeIter->colorGroupIncomeUnselected = previousColorThemeIter->colorGroupIncomeUnselected;
                currentColorThemeIter->colorGroupExpensesSelected = previousColorThemeIter->colorGroupExpensesSelected;
                currentColorThemeIter->colorGroupExpensesUnselected = previousColorThemeIter->colorGroupExpensesUnselected;
                currentColorThemeIter->colorGroupIncomeBackground = previousColorThemeIter->colorGroupIncomeBackground;
                currentColorThemeIter->colorGroupExpensesBackground = previousColorThemeIter->colorGroupExpensesBackground;
                currentColorThemeIter->colorBarBackground = previousColorThemeIter->colorBarBackground;
                currentColorThemeIter->colorTableIncomeAmount = previousColorThemeIter->colorTableIncomeAmount;
                currentColorThemeIter->showMonthlyAmountsInColor = previousColorThemeIter->showMonthlyAmountsInColor;
                currentColorThemeIter->useDarkOverallTheme = previousColorThemeIter->useDarkOverallTheme;
                currentColorThemeIter->colorOverallBackground = previousColorThemeIter->colorOverallBackground;
                currentColorThemeIter->colorOverallText = previousColorThemeIter->colorOverallText;
                customColorsExist = true;
            }

            //Set here the color selected by user to corresponding element
            currentColorTheme = colorConfigurationList.size()-1;  //Current color theme will be last one (Custom config)
            currentColorThemeIter->colorGroupIncomeSelected = iColorDialog.colorId;

            ui->widget->setColors(currentColorThemeIter->colorGroupIncomeSelected,
                                  currentColorThemeIter->colorGroupIncomeUnselected,
                                  currentColorThemeIter->colorGroupIncomeBackground);

            if (switchToCustomTheme){
                ui->comboBox->setCurrentIndex(currentColorTheme);     //Select custom in ComboBox, this calls automatically updateColorsOnScreen()
                if (iLanguage == ENGLISH) {
                    ui->label_Info->setText("Switched to custom color theme.");
                } else if (iLanguage == GERMAN) {
                    ui->label_Info->setText("Zu Benutzerdefiniertem Thema geschaltet.");
                } else if (iLanguage == SPANISH) {
                    ui->label_Info->setText("Cambio a tema personalizado.");
                }
            } else if (!switchToCustomTheme) {
                ui->label_ColorGroupSelected->setStyleSheet(getStyleSheetString("QLabel", currentColorThemeIter->colorGroupIncomeSelected,
                                                                                true, false));
            }
        }
    }

    else if (!showingIncomeGroups)
    {
        SelectColorDialog iColorDialog;
        iColorDialog.setLanguage(iLanguage);
        iColorDialog.setModal(true);
        iColorDialog.newColorWasSelected = false;
        iColorDialog.setOverallThemeStyleSheet(overallThemeStyleSheet);
        iColorDialog.exec();
        if (iColorDialog.newColorWasSelected)
        {
            bool switchToCustomTheme = false;
            std::cout<<"COLOR WAS PICKED - GROUP EXPENSES SELECTED: "<<iColorDialog.colorId<<'\n';
            if (currentColorTheme != colorConfigurationList.size()-1){
                switchToCustomTheme = true;
            }

            //If color was changed from Preset, then create an iterator pointing to last colorConfiguration (Custom config)
            std::vector<ColorConfiguration>::iterator currentColorThemeIter = colorConfigurationList.end()-1;
            if (!customColorsExist){
                //Copy current ColorConfiguration to customColorConfiguration
                std::vector<ColorConfiguration>::iterator previousColorThemeIter = colorConfigurationList.begin()+currentColorTheme;
                currentColorThemeIter->colorBarIncomeSelected = previousColorThemeIter->colorGroupIncomeSelected;
                currentColorThemeIter->colorBarIncomeUnselected = previousColorThemeIter->colorBarIncomeUnselected;
                currentColorThemeIter->colorBarExpensesSelected = previousColorThemeIter->colorBarExpensesSelected;
                currentColorThemeIter->colorBarExpensesUnselected = previousColorThemeIter->colorBarExpensesUnselected;
                currentColorThemeIter->colorGroupIncomeSelected = previousColorThemeIter->colorGroupIncomeSelected;
                currentColorThemeIter->colorGroupIncomeUnselected = previousColorThemeIter->colorGroupIncomeUnselected;
                //currentColorThemeIter->colorGroupExpensesSelected = previousColorThemeIter->colorGroupExpensesSelected;
                currentColorThemeIter->colorGroupExpensesUnselected = previousColorThemeIter->colorGroupExpensesUnselected;
                currentColorThemeIter->colorGroupIncomeBackground = previousColorThemeIter->colorGroupIncomeBackground;
                currentColorThemeIter->colorGroupExpensesBackground = previousColorThemeIter->colorGroupExpensesBackground;
                currentColorThemeIter->colorBarBackground = previousColorThemeIter->colorBarBackground;
                currentColorThemeIter->colorTableIncomeAmount = previousColorThemeIter->colorTableIncomeAmount;
                currentColorThemeIter->showMonthlyAmountsInColor = previousColorThemeIter->showMonthlyAmountsInColor;
                currentColorThemeIter->useDarkOverallTheme = previousColorThemeIter->useDarkOverallTheme;
                currentColorThemeIter->colorOverallBackground = previousColorThemeIter->colorOverallBackground;
                currentColorThemeIter->colorOverallText = previousColorThemeIter->colorOverallText;
                customColorsExist = true;
            }

            //Set here the color selected by user to corresponding element
            currentColorTheme = colorConfigurationList.size()-1;  //Current color theme will be last one (Custom config)
            currentColorThemeIter->colorGroupExpensesSelected = iColorDialog.colorId;

            ui->widget->setColors(currentColorThemeIter->colorGroupExpensesSelected,
                                  currentColorThemeIter->colorGroupExpensesUnselected,
                                  currentColorThemeIter->colorGroupExpensesBackground);

            if (switchToCustomTheme){
                ui->comboBox->setCurrentIndex(currentColorTheme);     //Select custom in ComboBox, this calls automatically updateColorsOnScreen()
                if (iLanguage == ENGLISH) {
                    ui->label_Info->setText("Switched to custom color theme.");
                } else if (iLanguage == GERMAN) {
                    ui->label_Info->setText("Zu Benutzerdefiniertem Thema geschaltet.");
                } else if (iLanguage == SPANISH) {
                    ui->label_Info->setText("Cambio a tema personalizado.");
                }
            } else if (!switchToCustomTheme) {
                ui->label_ColorGroupSelected->setStyleSheet(getStyleSheetString("QLabel", currentColorThemeIter->colorGroupExpensesSelected,
                                                                                true, false));
            }
        }
    }
}

void ThemeColorsDialog::labelGroupUnselectedClicked()
{
    if (showingIncomeGroups)
    {
        SelectColorDialog iColorDialog;
        iColorDialog.setLanguage(iLanguage);
        iColorDialog.setModal(true);
        iColorDialog.newColorWasSelected = false;
        iColorDialog.setOverallThemeStyleSheet(overallThemeStyleSheet);
        iColorDialog.exec();

        if (iColorDialog.newColorWasSelected)
        {
            bool switchToCustomTheme = false;
            std::cout<<"COLOR WAS PICKED - GROUP INCOME UN-SELECTED: "<<iColorDialog.colorId<<'\n';
            if (currentColorTheme != colorConfigurationList.size()-1){
                switchToCustomTheme = true;
            }

            //If color was changed from Preset, then create an iterator pointing to last colorConfiguration (Custom config)
            std::vector<ColorConfiguration>::iterator currentColorThemeIter = colorConfigurationList.end()-1;
            if (!customColorsExist){
                //Copy current ColorConfiguration to customColorConfiguration
                std::vector<ColorConfiguration>::iterator previousColorThemeIter = colorConfigurationList.begin()+currentColorTheme;
                currentColorThemeIter->colorBarIncomeSelected = previousColorThemeIter->colorGroupIncomeSelected;
                currentColorThemeIter->colorBarIncomeUnselected = previousColorThemeIter->colorBarIncomeUnselected;
                currentColorThemeIter->colorBarExpensesSelected = previousColorThemeIter->colorBarExpensesSelected;
                currentColorThemeIter->colorBarExpensesUnselected = previousColorThemeIter->colorBarExpensesUnselected;
                currentColorThemeIter->colorGroupIncomeSelected = previousColorThemeIter->colorGroupIncomeSelected;
                //currentColorThemeIter->colorGroupIncomeUnselected = previousColorThemeIter->colorGroupIncomeUnselected;
                currentColorThemeIter->colorGroupExpensesSelected = previousColorThemeIter->colorGroupExpensesSelected;
                currentColorThemeIter->colorGroupExpensesUnselected = previousColorThemeIter->colorGroupExpensesUnselected;
                currentColorThemeIter->colorGroupIncomeBackground = previousColorThemeIter->colorGroupIncomeBackground;
                currentColorThemeIter->colorGroupExpensesBackground = previousColorThemeIter->colorGroupExpensesBackground;
                currentColorThemeIter->colorBarBackground = previousColorThemeIter->colorBarBackground;
                currentColorThemeIter->colorTableIncomeAmount = previousColorThemeIter->colorTableIncomeAmount;
                currentColorThemeIter->showMonthlyAmountsInColor = previousColorThemeIter->showMonthlyAmountsInColor;
                currentColorThemeIter->useDarkOverallTheme = previousColorThemeIter->useDarkOverallTheme;
                currentColorThemeIter->colorOverallBackground = previousColorThemeIter->colorOverallBackground;
                currentColorThemeIter->colorOverallText = previousColorThemeIter->colorOverallText;
                customColorsExist = true;
            }

            //Set here the color selected by user to corresponding element
            currentColorTheme = colorConfigurationList.size()-1;  //Current color theme will be last one (Custom config)
            currentColorThemeIter->colorGroupIncomeUnselected = iColorDialog.colorId;

            ui->widget->setColors(currentColorThemeIter->colorGroupIncomeSelected,
                                  currentColorThemeIter->colorGroupIncomeUnselected,
                                  currentColorThemeIter->colorGroupIncomeBackground);

            if (switchToCustomTheme){
                ui->comboBox->setCurrentIndex(currentColorTheme);     //Select custom in ComboBox, this calls automatically updateColorsOnScreen()
                if (iLanguage == ENGLISH) {
                    ui->label_Info->setText("Switched to custom color theme.");
                } else if (iLanguage == GERMAN) {
                    ui->label_Info->setText("Zu Benutzerdefiniertem Thema geschaltet.");
                } else if (iLanguage == SPANISH) {
                    ui->label_Info->setText("Cambio a tema personalizado.");
                }
            } else if (!switchToCustomTheme) {
                ui->label_ColorGroupUnselected->setStyleSheet(getStyleSheetString("QLabel", currentColorThemeIter->colorGroupIncomeUnselected,
                                                                                  true, false));
            }
        }
    }
    else if (!showingIncomeGroups)
    {
        SelectColorDialog iColorDialog;
        iColorDialog.setLanguage(iLanguage);
        iColorDialog.setModal(true);
        iColorDialog.newColorWasSelected = false;
        iColorDialog.setOverallThemeStyleSheet(overallThemeStyleSheet);
        iColorDialog.exec();

        if (iColorDialog.newColorWasSelected)
        {
            bool  switchToCustomTheme = false;
            std::cout<<"COLOR WAS PICKED - GROUP EXPENSES UN-SELECTED: "<<iColorDialog.colorId<<'\n';
            if (currentColorTheme != colorConfigurationList.size()-1){
                switchToCustomTheme = true;
            }

            //If color was changed from Preset, then create an iterator pointing to last colorConfiguration (Custom config)
            std::vector<ColorConfiguration>::iterator currentColorThemeIter = colorConfigurationList.end()-1;
            if (!customColorsExist){
                //Copy current ColorConfiguration to customColorConfiguration
                std::vector<ColorConfiguration>::iterator previousColorThemeIter = colorConfigurationList.begin()+currentColorTheme;
                currentColorThemeIter->colorBarIncomeSelected = previousColorThemeIter->colorGroupIncomeSelected;
                currentColorThemeIter->colorBarIncomeUnselected = previousColorThemeIter->colorBarIncomeUnselected;
                currentColorThemeIter->colorBarExpensesSelected = previousColorThemeIter->colorBarExpensesSelected;
                currentColorThemeIter->colorBarExpensesUnselected = previousColorThemeIter->colorBarExpensesUnselected;
                currentColorThemeIter->colorGroupIncomeSelected = previousColorThemeIter->colorGroupIncomeSelected;
                currentColorThemeIter->colorGroupIncomeUnselected = previousColorThemeIter->colorGroupIncomeUnselected;
                currentColorThemeIter->colorGroupExpensesSelected = previousColorThemeIter->colorGroupExpensesSelected;
                //currentColorThemeIter->colorGroupExpensesUnselected = previousColorThemeIter->colorGroupExpensesUnselected;
                currentColorThemeIter->colorGroupIncomeBackground = previousColorThemeIter->colorGroupIncomeBackground;
                currentColorThemeIter->colorGroupExpensesBackground = previousColorThemeIter->colorGroupExpensesBackground;
                currentColorThemeIter->colorBarBackground = previousColorThemeIter->colorBarBackground;
                currentColorThemeIter->colorTableIncomeAmount = previousColorThemeIter->colorTableIncomeAmount;
                currentColorThemeIter->showMonthlyAmountsInColor = previousColorThemeIter->showMonthlyAmountsInColor;
                currentColorThemeIter->useDarkOverallTheme = previousColorThemeIter->useDarkOverallTheme;
                currentColorThemeIter->colorOverallBackground = previousColorThemeIter->colorOverallBackground;
                currentColorThemeIter->colorOverallText = previousColorThemeIter->colorOverallText;
                customColorsExist = true;
            }

            //Set here the color selected by user to corresponding element
            currentColorTheme = colorConfigurationList.size()-1;  //Current color theme will be last one (Custom config)
            currentColorThemeIter->colorGroupExpensesUnselected = iColorDialog.colorId;

            ui->widget->setColors(currentColorThemeIter->colorGroupExpensesSelected,
                                  currentColorThemeIter->colorGroupExpensesUnselected,
                                  currentColorThemeIter->colorGroupExpensesBackground);

            if (switchToCustomTheme){
                ui->comboBox->setCurrentIndex(currentColorTheme);     //Select custom in ComboBox, this calls automatically updateColorsOnScreen()
                if (iLanguage == ENGLISH) {
                    ui->label_Info->setText("Switched to custom color theme.");
                } else if (iLanguage == GERMAN) {
                    ui->label_Info->setText("Zu Benutzerdefiniertem Thema geschaltet.");
                } else if (iLanguage == SPANISH) {
                    ui->label_Info->setText("Cambio a tema personalizado.");
                }
            } else if (!switchToCustomTheme) {
                ui->label_ColorGroupUnselected->setStyleSheet(getStyleSheetString("QLabel", currentColorThemeIter->colorGroupExpensesUnselected,
                                                                                true, false));
            }
        }
    }
}

void ThemeColorsDialog::labelGroupBackgroundClicked()
{
    if (showingIncomeGroups)
    {
        SelectColorDialog iColorDialog;
        iColorDialog.setLanguage(iLanguage);
        iColorDialog.setModal(true);
        iColorDialog.newColorWasSelected = false;
        iColorDialog.setOverallThemeStyleSheet(overallThemeStyleSheet);
        iColorDialog.exec();
        if (iColorDialog.newColorWasSelected)
        {
            bool switchToCustomTheme = false;
            std::cout<<"COLOR WAS PICKED - GROUP INCOME BACKGROUND: "<<iColorDialog.colorId<<'\n';
            if (currentColorTheme != colorConfigurationList.size()-1){
                switchToCustomTheme = true;
            }

            //If color was changed from Preset, then create an iterator pointing to last colorConfiguration (Custom config)
            std::vector<ColorConfiguration>::iterator currentColorThemeIter = colorConfigurationList.end()-1;
            if (!customColorsExist){
                //Copy current ColorConfiguration to customColorConfiguration
                std::vector<ColorConfiguration>::iterator previousColorThemeIter = colorConfigurationList.begin()+currentColorTheme;
                currentColorThemeIter->colorBarIncomeSelected = previousColorThemeIter->colorGroupIncomeSelected;
                currentColorThemeIter->colorBarIncomeUnselected = previousColorThemeIter->colorBarIncomeUnselected;
                currentColorThemeIter->colorBarExpensesSelected = previousColorThemeIter->colorBarExpensesSelected;
                currentColorThemeIter->colorBarExpensesUnselected = previousColorThemeIter->colorBarExpensesUnselected;
                currentColorThemeIter->colorGroupIncomeSelected = previousColorThemeIter->colorGroupIncomeSelected;
                currentColorThemeIter->colorGroupIncomeUnselected = previousColorThemeIter->colorGroupIncomeUnselected;
                currentColorThemeIter->colorGroupExpensesSelected = previousColorThemeIter->colorGroupExpensesSelected;
                currentColorThemeIter->colorGroupExpensesUnselected = previousColorThemeIter->colorGroupExpensesUnselected;
                //currentColorThemeIter->colorGroupIncomeBackground = previousColorThemeIter->colorGroupIncomeBackground;
                currentColorThemeIter->colorGroupExpensesBackground = previousColorThemeIter->colorGroupExpensesBackground;
                currentColorThemeIter->colorBarBackground = previousColorThemeIter->colorBarBackground;
                currentColorThemeIter->colorTableIncomeAmount = previousColorThemeIter->colorTableIncomeAmount;
                currentColorThemeIter->showMonthlyAmountsInColor = previousColorThemeIter->showMonthlyAmountsInColor;
                currentColorThemeIter->useDarkOverallTheme = previousColorThemeIter->useDarkOverallTheme;
                currentColorThemeIter->colorOverallBackground = previousColorThemeIter->colorOverallBackground;
                currentColorThemeIter->colorOverallText = previousColorThemeIter->colorOverallText;
                customColorsExist = true;
            }

            //Set here the color selected by user to corresponding element
            currentColorTheme = colorConfigurationList.size()-1;  //Current color theme will be last one (Custom config)
            currentColorThemeIter->colorGroupIncomeBackground = iColorDialog.colorId;

            ui->widget->setColors(currentColorThemeIter->colorGroupIncomeSelected,
                                  currentColorThemeIter->colorGroupIncomeUnselected,
                                  currentColorThemeIter->colorGroupIncomeBackground);

            if (switchToCustomTheme){
                ui->comboBox->setCurrentIndex(currentColorTheme);     //Select custom in ComboBox, this calls automatically updateColorsOnScreen()
                if (iLanguage == ENGLISH) {
                    ui->label_Info->setText("Switched to custom color theme.");
                } else if (iLanguage == GERMAN) {
                    ui->label_Info->setText("Zu Benutzerdefiniertem Thema geschaltet.");
                } else if (iLanguage == SPANISH) {
                    ui->label_Info->setText("Cambio a tema personalizado.");
                }
            } else if (!switchToCustomTheme) {
                ui->label_ColorGroupBackground->setStyleSheet(getStyleSheetString("QLabel", currentColorThemeIter->colorGroupIncomeBackground,
                                                                                  true, false));
            }
        }
    }

    else if (!showingIncomeGroups)
    {
        SelectColorDialog iColorDialog;
        iColorDialog.setLanguage(iLanguage);
        iColorDialog.setModal(true);
        iColorDialog.newColorWasSelected = false;
        iColorDialog.setOverallThemeStyleSheet(overallThemeStyleSheet);
        iColorDialog.exec();
        if (iColorDialog.newColorWasSelected)
        {
            bool switchToCustomTheme = false;
            std::cout<<"COLOR WAS PICKED - GROUP EXPENSES BACKGROUND: "<<iColorDialog.colorId<<'\n';
            if (currentColorTheme != colorConfigurationList.size()-1){
                switchToCustomTheme = true;
            }

            //If color was changed from Preset, then create an iterator pointing to last colorConfiguration (Custom config)
            std::vector<ColorConfiguration>::iterator currentColorThemeIter = colorConfigurationList.end()-1;
            if (!customColorsExist){
                //Copy current ColorConfiguration to customColorConfiguration
                std::vector<ColorConfiguration>::iterator previousColorThemeIter = colorConfigurationList.begin()+currentColorTheme;
                currentColorThemeIter->colorBarIncomeSelected = previousColorThemeIter->colorGroupIncomeSelected;
                currentColorThemeIter->colorBarIncomeUnselected = previousColorThemeIter->colorBarIncomeUnselected;
                currentColorThemeIter->colorBarExpensesSelected = previousColorThemeIter->colorBarExpensesSelected;
                currentColorThemeIter->colorBarExpensesUnselected = previousColorThemeIter->colorBarExpensesUnselected;
                currentColorThemeIter->colorGroupIncomeSelected = previousColorThemeIter->colorGroupIncomeSelected;
                currentColorThemeIter->colorGroupIncomeUnselected = previousColorThemeIter->colorGroupIncomeUnselected;
                currentColorThemeIter->colorGroupExpensesSelected = previousColorThemeIter->colorGroupExpensesSelected;
                currentColorThemeIter->colorGroupExpensesUnselected = previousColorThemeIter->colorGroupExpensesUnselected;
                currentColorThemeIter->colorGroupIncomeBackground = previousColorThemeIter->colorGroupIncomeBackground;
                //currentColorThemeIter->colorGroupExpensesBackground = previousColorThemeIter->colorGroupExpensesBackground;
                currentColorThemeIter->colorBarBackground = previousColorThemeIter->colorBarBackground;
                currentColorThemeIter->colorTableIncomeAmount = previousColorThemeIter->colorTableIncomeAmount;
                currentColorThemeIter->showMonthlyAmountsInColor = previousColorThemeIter->showMonthlyAmountsInColor;
                currentColorThemeIter->useDarkOverallTheme = previousColorThemeIter->useDarkOverallTheme;
                currentColorThemeIter->colorOverallBackground = previousColorThemeIter->colorOverallBackground;
                currentColorThemeIter->colorOverallText = previousColorThemeIter->colorOverallText;
                customColorsExist = true;
            }

            //Set here the color selected by user to corresponding element
            currentColorTheme = colorConfigurationList.size()-1;  //Current color theme will be last one (Custom config)
            currentColorThemeIter->colorGroupExpensesBackground = iColorDialog.colorId;

            ui->widget->setColors(currentColorThemeIter->colorGroupExpensesSelected,
                                  currentColorThemeIter->colorGroupExpensesUnselected,
                                  currentColorThemeIter->colorGroupExpensesBackground);

            if (switchToCustomTheme){
                ui->comboBox->setCurrentIndex(currentColorTheme);     //Select custom in ComboBox, this calls automatically updateColorsOnScreen()
                if (iLanguage == ENGLISH) {
                    ui->label_Info->setText("Switched to custom color theme.");
                } else if (iLanguage == GERMAN) {
                    ui->label_Info->setText("Zu Benutzerdefiniertem Thema geschaltet.");
                } else if (iLanguage == SPANISH) {
                    ui->label_Info->setText("Cambio a tema personalizado.");
                }
            } else if (!switchToCustomTheme) {
                ui->label_ColorGroupBackground->setStyleSheet(getStyleSheetString("QLabel", currentColorThemeIter->colorGroupExpensesBackground,
                                                                                  true, false));
            }
        }
    }
}

void ThemeColorsDialog::labelBarSelectedClicked()
{
    SelectColorDialog iColorDialog;
    iColorDialog.setLanguage(iLanguage);
    iColorDialog.setModal(true);
    iColorDialog.newColorWasSelected = false;
    iColorDialog.setOverallThemeStyleSheet(overallThemeStyleSheet);
    iColorDialog.exec();
    if (iColorDialog.newColorWasSelected)
    {
        bool switchToCustomTheme = false;
        if (ui->radioBarIncome->isChecked()){
                std::cout<<"COLOR WAS PICKED - BAR INCOME SELECTED: "<<iColorDialog.colorId<<'\n';
                if (currentColorTheme != colorConfigurationList.size()-1){
                    switchToCustomTheme = true;
                }

                //If color was changed from Preset, then create an iterator pointing to last colorConfiguration (Custom config)
                std::vector<ColorConfiguration>::iterator currentColorThemeIter = colorConfigurationList.end()-1;
                if (!customColorsExist){
                    //Copy current ColorConfiguration to customColorConfiguration
                    std::vector<ColorConfiguration>::iterator previousColorThemeIter = colorConfigurationList.begin()+currentColorTheme;
                    //currentColorThemeIter->colorBarIncomeSelected = previousColorThemeIter->colorGroupIncomeSelected;
                    currentColorThemeIter->colorBarIncomeUnselected = previousColorThemeIter->colorBarIncomeUnselected;
                    currentColorThemeIter->colorBarExpensesSelected = previousColorThemeIter->colorBarExpensesSelected;
                    currentColorThemeIter->colorBarExpensesUnselected = previousColorThemeIter->colorBarExpensesUnselected;
                    currentColorThemeIter->colorGroupIncomeSelected = previousColorThemeIter->colorGroupIncomeSelected;
                    currentColorThemeIter->colorGroupIncomeUnselected = previousColorThemeIter->colorGroupIncomeUnselected;
                    currentColorThemeIter->colorGroupExpensesSelected = previousColorThemeIter->colorGroupExpensesSelected;
                    currentColorThemeIter->colorGroupExpensesUnselected = previousColorThemeIter->colorGroupExpensesUnselected;
                    currentColorThemeIter->colorGroupIncomeBackground = previousColorThemeIter->colorGroupIncomeBackground;
                    currentColorThemeIter->colorGroupExpensesBackground = previousColorThemeIter->colorGroupExpensesBackground;
                    currentColorThemeIter->colorBarBackground = previousColorThemeIter->colorBarBackground;
                    currentColorThemeIter->colorTableIncomeAmount = previousColorThemeIter->colorTableIncomeAmount;
                    currentColorThemeIter->showMonthlyAmountsInColor = previousColorThemeIter->showMonthlyAmountsInColor;
                    currentColorThemeIter->useDarkOverallTheme = previousColorThemeIter->useDarkOverallTheme;
                    currentColorThemeIter->colorOverallBackground = previousColorThemeIter->colorOverallBackground;
                    currentColorThemeIter->colorOverallText = previousColorThemeIter->colorOverallText;
                    customColorsExist = true;
                }

                //Set here the color selected by user to corresponding element
                currentColorTheme = colorConfigurationList.size()-1;  //Current color theme will be last one (Custom config)
                currentColorThemeIter->colorBarIncomeSelected = iColorDialog.colorId;                

                /*ui->widget_2->setBarColors(currentColorThemeIter->colorBarIncomeSelected,
                                           currentColorThemeIter->colorBarIncomeUnselected,
                                           currentColorThemeIter->colorBarExpensesSelected,
                                           currentColorThemeIter->colorBarExpensesUnselected);*/

                if (switchToCustomTheme){
                    ui->comboBox->setCurrentIndex(currentColorTheme);     //Select custom in ComboBox, this calls automatically updateColorsOnScreen()
                    if (iLanguage == ENGLISH) {
                        ui->label_Info->setText("Switched to custom color theme.");
                    } else if (iLanguage == GERMAN) {
                        ui->label_Info->setText("Zu Benutzerdefiniertem Thema geschaltet.");
                    } else if (iLanguage == SPANISH) {
                        ui->label_Info->setText("Cambio a tema personalizado.");
                    }
                } else if (!switchToCustomTheme) {
                    this->updateColorsOnScreen();
                }

        } else {
            std::cout<<"COLOR WAS PICKED - BAR EXPENSES SELECTED: "<<iColorDialog.colorId<<'\n';
            if (currentColorTheme != colorConfigurationList.size()-1){
                switchToCustomTheme = true;
            }

            //If color was changed from Preset, then create an iterator pointing to last colorConfiguration (Custom config)
            std::vector<ColorConfiguration>::iterator currentColorThemeIter = colorConfigurationList.end()-1;
            if (!customColorsExist){
                //Copy current ColorConfiguration to customColorConfiguration
                std::vector<ColorConfiguration>::iterator previousColorThemeIter = colorConfigurationList.begin()+currentColorTheme;
                currentColorThemeIter->colorBarIncomeSelected = previousColorThemeIter->colorGroupIncomeSelected;
                currentColorThemeIter->colorBarIncomeUnselected = previousColorThemeIter->colorBarIncomeUnselected;
                //currentColorThemeIter->colorBarExpensesSelected = previousColorThemeIter->colorBarExpensesSelected;
                currentColorThemeIter->colorBarExpensesUnselected = previousColorThemeIter->colorBarExpensesUnselected;
                currentColorThemeIter->colorGroupIncomeSelected = previousColorThemeIter->colorGroupIncomeSelected;
                currentColorThemeIter->colorGroupIncomeUnselected = previousColorThemeIter->colorGroupIncomeUnselected;
                currentColorThemeIter->colorGroupExpensesSelected = previousColorThemeIter->colorGroupExpensesSelected;
                currentColorThemeIter->colorGroupExpensesUnselected = previousColorThemeIter->colorGroupExpensesUnselected;
                currentColorThemeIter->colorGroupIncomeBackground = previousColorThemeIter->colorGroupIncomeBackground;
                currentColorThemeIter->colorGroupExpensesBackground = previousColorThemeIter->colorGroupExpensesBackground;
                currentColorThemeIter->colorBarBackground = previousColorThemeIter->colorBarBackground;
                currentColorThemeIter->colorTableIncomeAmount = previousColorThemeIter->colorTableIncomeAmount;
                currentColorThemeIter->showMonthlyAmountsInColor = previousColorThemeIter->showMonthlyAmountsInColor;
                currentColorThemeIter->useDarkOverallTheme = previousColorThemeIter->useDarkOverallTheme;
                currentColorThemeIter->colorOverallBackground = previousColorThemeIter->colorOverallBackground;
                currentColorThemeIter->colorOverallText = previousColorThemeIter->colorOverallText;
                customColorsExist = true;
            }

            //Set here the color selected by user to corresponding element
            currentColorTheme = colorConfigurationList.size()-1;  //Current color theme will be last one (Custom config)
            currentColorThemeIter->colorBarExpensesSelected = iColorDialog.colorId;

            /*ui->widget_2->setBarColors(currentColorThemeIter->colorBarIncomeSelected,
                                       currentColorThemeIter->colorBarIncomeUnselected,
                                       currentColorThemeIter->colorBarExpensesSelected,
                                       currentColorThemeIter->colorBarExpensesUnselected);*/

            if (switchToCustomTheme){
                ui->comboBox->setCurrentIndex(currentColorTheme);     //Select custom in ComboBox, this calls automatically updateColorsOnScreen()
                if (iLanguage == ENGLISH) {
                    ui->label_Info->setText("Switched to custom color theme.");
                } else if (iLanguage == GERMAN) {
                    ui->label_Info->setText("Zu Benutzerdefiniertem Thema geschaltet.");
                } else if (iLanguage == SPANISH) {
                    ui->label_Info->setText("Cambio a tema personalizado.");
                }
            } else if (!switchToCustomTheme) {
                this->updateColorsOnScreen();
            }
        }
    }
}

void ThemeColorsDialog::labelBarUnselectedClicked()
{
    SelectColorDialog iColorDialog;
    iColorDialog.setLanguage(iLanguage);
    iColorDialog.setModal(true);
    iColorDialog.newColorWasSelected = false;
    iColorDialog.setOverallThemeStyleSheet(overallThemeStyleSheet);
    iColorDialog.exec();
    if (iColorDialog.newColorWasSelected)
    {
        bool switchToCustomTheme = false;
        if (ui->radioBarIncome->isChecked()){
            std::cout<<"COLOR WAS PICKED - BAR INCOME UN-SELECTED: "<<iColorDialog.colorId<<'\n';
            if (currentColorTheme != colorConfigurationList.size()-1){
                switchToCustomTheme = true;
            }

            //If color was changed from Preset, then create an iterator pointing to last colorConfiguration (Custom config)
            std::vector<ColorConfiguration>::iterator currentColorThemeIter = colorConfigurationList.end()-1;
            if (!customColorsExist){
                //Copy current ColorConfiguration to customColorConfiguration
                std::vector<ColorConfiguration>::iterator previousColorThemeIter = colorConfigurationList.begin()+currentColorTheme;
                currentColorThemeIter->colorBarIncomeSelected = previousColorThemeIter->colorGroupIncomeSelected;
                //currentColorThemeIter->colorBarIncomeUnselected = previousColorThemeIter->colorBarIncomeUnselected;
                currentColorThemeIter->colorBarExpensesSelected = previousColorThemeIter->colorBarExpensesSelected;
                currentColorThemeIter->colorBarExpensesUnselected = previousColorThemeIter->colorBarExpensesUnselected;
                currentColorThemeIter->colorGroupIncomeSelected = previousColorThemeIter->colorGroupIncomeSelected;
                currentColorThemeIter->colorGroupIncomeUnselected = previousColorThemeIter->colorGroupIncomeUnselected;
                currentColorThemeIter->colorGroupExpensesSelected = previousColorThemeIter->colorGroupExpensesSelected;
                currentColorThemeIter->colorGroupExpensesUnselected = previousColorThemeIter->colorGroupExpensesUnselected;
                currentColorThemeIter->colorGroupIncomeBackground = previousColorThemeIter->colorGroupIncomeBackground;
                currentColorThemeIter->colorGroupExpensesBackground = previousColorThemeIter->colorGroupExpensesBackground;
                currentColorThemeIter->colorBarBackground = previousColorThemeIter->colorBarBackground;
                currentColorThemeIter->colorTableIncomeAmount = previousColorThemeIter->colorTableIncomeAmount;
                currentColorThemeIter->showMonthlyAmountsInColor = previousColorThemeIter->showMonthlyAmountsInColor;
                currentColorThemeIter->useDarkOverallTheme = previousColorThemeIter->useDarkOverallTheme;
                currentColorThemeIter->colorOverallBackground = previousColorThemeIter->colorOverallBackground;
                currentColorThemeIter->colorOverallText = previousColorThemeIter->colorOverallText;
                customColorsExist = true;
            }

            //Set here the color selected by user to corresponding element
            currentColorTheme = colorConfigurationList.size()-1;  //Current color theme will be last one (Custom config)
            currentColorThemeIter->colorBarIncomeUnselected = iColorDialog.colorId;            

            /*ui->widget_2->setBarColors(currentColorThemeIter->colorBarIncomeSelected,
                                       currentColorThemeIter->colorBarIncomeUnselected,
                                       currentColorThemeIter->colorBarExpensesSelected,
                                       currentColorThemeIter->colorBarExpensesUnselected);*/

            if (switchToCustomTheme){
                ui->comboBox->setCurrentIndex(currentColorTheme);     //Select custom in ComboBox, this calls automatically updateColorsOnScreen()
                if (iLanguage == ENGLISH) {
                    ui->label_Info->setText("Switched to custom color theme.");
                } else if (iLanguage == GERMAN) {
                    ui->label_Info->setText("Zu Benutzerdefiniertem Thema geschaltet.");
                } else if (iLanguage == SPANISH) {
                    ui->label_Info->setText("Cambio a tema personalizado.");
                }
            } else if (!switchToCustomTheme) {
                //ui->label_ColorBarUnselected->setStyleSheet(getStyleSheetString("QLabel", currentColorThemeIter->colorBarIncomeUnselected, false));
                this->updateColorsOnScreen();
            }

        } else {
            std::cout<<"COLOR WAS PICKED - BAR EXPENSES UN-SELECTED: "<<iColorDialog.colorId<<'\n';
            if (currentColorTheme != colorConfigurationList.size()-1){
                switchToCustomTheme = true;
            }

            //If color was changed from Preset, then create an iterator pointing to last colorConfiguration (Custom config)
            std::vector<ColorConfiguration>::iterator currentColorThemeIter = colorConfigurationList.end()-1;
            if (!customColorsExist){
                //Copy current ColorConfiguration to customColorConfiguration
                std::vector<ColorConfiguration>::iterator previousColorThemeIter = colorConfigurationList.begin()+currentColorTheme;
                currentColorThemeIter->colorBarIncomeSelected = previousColorThemeIter->colorGroupIncomeSelected;
                currentColorThemeIter->colorBarIncomeUnselected = previousColorThemeIter->colorBarIncomeUnselected;
                currentColorThemeIter->colorBarExpensesSelected = previousColorThemeIter->colorBarExpensesSelected;
                //currentColorThemeIter->colorBarExpensesUnselected = previousColorThemeIter->colorBarExpensesUnselected;
                currentColorThemeIter->colorGroupIncomeSelected = previousColorThemeIter->colorGroupIncomeSelected;
                currentColorThemeIter->colorGroupIncomeUnselected = previousColorThemeIter->colorGroupIncomeUnselected;
                currentColorThemeIter->colorGroupExpensesSelected = previousColorThemeIter->colorGroupExpensesSelected;
                currentColorThemeIter->colorGroupExpensesUnselected = previousColorThemeIter->colorGroupExpensesUnselected;
                currentColorThemeIter->colorGroupIncomeBackground = previousColorThemeIter->colorGroupIncomeBackground;
                currentColorThemeIter->colorGroupExpensesBackground = previousColorThemeIter->colorGroupExpensesBackground;
                currentColorThemeIter->colorBarBackground = previousColorThemeIter->colorBarBackground;
                currentColorThemeIter->colorTableIncomeAmount = previousColorThemeIter->colorTableIncomeAmount;
                currentColorThemeIter->showMonthlyAmountsInColor = previousColorThemeIter->showMonthlyAmountsInColor;
                currentColorThemeIter->useDarkOverallTheme = previousColorThemeIter->useDarkOverallTheme;
                currentColorThemeIter->colorOverallBackground = previousColorThemeIter->colorOverallBackground;
                currentColorThemeIter->colorOverallText = previousColorThemeIter->colorOverallText;
                customColorsExist = true;
            }

            //Set here the color selected by user to corresponding element
            currentColorTheme = colorConfigurationList.size()-1;  //Current color theme will be last one (Custom config)
            currentColorThemeIter->colorBarExpensesUnselected = iColorDialog.colorId;

            /*ui->widget_2->setBarColors(currentColorThemeIter->colorBarIncomeSelected,
                                       currentColorThemeIter->colorBarIncomeUnselected,
                                       currentColorThemeIter->colorBarExpensesSelected,
                                       currentColorThemeIter->colorBarExpensesUnselected);*/

            if (switchToCustomTheme){
                ui->comboBox->setCurrentIndex(currentColorTheme);     //Select custom in ComboBox, this calls automatically updateColorsOnScreen()
                if (iLanguage == ENGLISH) {
                    ui->label_Info->setText("Switched to custom color theme.");
                } else if (iLanguage == GERMAN) {
                    ui->label_Info->setText("Zu Benutzerdefiniertem Thema geschaltet.");
                } else if (iLanguage == SPANISH) {
                    ui->label_Info->setText("Cambio a tema personalizado.");
                }
            } else if (!switchToCustomTheme) {
                //ui->label_ColorBarUnselected->setStyleSheet(getStyleSheetString("QLabel", currentColorThemeIter->colorBarExpensesUnselected, false));
                this->updateColorsOnScreen();
            }
        }
    }
}

void ThemeColorsDialog::labelBarBackgroundClicked()
{
    SelectColorDialog iColorDialog;
    iColorDialog.setLanguage(iLanguage);
    iColorDialog.setModal(true);
    iColorDialog.newColorWasSelected = false;
    iColorDialog.enableTransparency();//"No Color" can be selected for Bar-Background
    iColorDialog.setOverallThemeStyleSheet(overallThemeStyleSheet);
    iColorDialog.exec();
    if (iColorDialog.newColorWasSelected)
    {
        std::cout<<"COLOR WAS PICKED - BAR BACKGROUND: "<<iColorDialog.colorId<<'\n';
        bool switchToCustomTheme = false;
        if (currentColorTheme != colorConfigurationList.size()-1){
            if (iLanguage == ENGLISH) {
                ui->label_Info->setText("Switched to custom color theme.");
            } else if (iLanguage == GERMAN) {
                ui->label_Info->setText("Zu Benutzerdefiniertem Thema geschaltet.");
            } else if (iLanguage == SPANISH) {
                ui->label_Info->setText("Cambio a tema personalizado.");
            }
            switchToCustomTheme = true;
        }

        //If color was changed from Preset, then create an iterator pointing to last colorConfiguration (Custom config)
        std::vector<ColorConfiguration>::iterator currentColorThemeIter = colorConfigurationList.end()-1;
        if (!customColorsExist){
            //Copy current ColorConfiguration to customColorConfiguration
            std::vector<ColorConfiguration>::iterator previousColorThemeIter = colorConfigurationList.begin()+currentColorTheme;
            currentColorThemeIter->colorBarIncomeSelected = previousColorThemeIter->colorGroupIncomeSelected;
            currentColorThemeIter->colorBarIncomeUnselected = previousColorThemeIter->colorBarIncomeUnselected;
            currentColorThemeIter->colorBarExpensesSelected = previousColorThemeIter->colorBarExpensesSelected;
            currentColorThemeIter->colorBarExpensesUnselected = previousColorThemeIter->colorBarExpensesUnselected;
            currentColorThemeIter->colorGroupIncomeSelected = previousColorThemeIter->colorGroupIncomeSelected;
            currentColorThemeIter->colorGroupIncomeUnselected = previousColorThemeIter->colorGroupIncomeUnselected;
            currentColorThemeIter->colorGroupExpensesSelected = previousColorThemeIter->colorGroupExpensesSelected;
            currentColorThemeIter->colorGroupExpensesUnselected = previousColorThemeIter->colorGroupExpensesUnselected;
            currentColorThemeIter->colorGroupIncomeBackground = previousColorThemeIter->colorGroupIncomeBackground;
            currentColorThemeIter->colorGroupExpensesBackground = previousColorThemeIter->colorGroupExpensesBackground;
            //currentColorThemeIter->colorBarBackground = previousColorThemeIter->colorBarBackground;
            currentColorThemeIter->colorTableIncomeAmount = previousColorThemeIter->colorTableIncomeAmount;
            currentColorThemeIter->showMonthlyAmountsInColor = previousColorThemeIter->showMonthlyAmountsInColor;
            currentColorThemeIter->useDarkOverallTheme = previousColorThemeIter->useDarkOverallTheme;
            currentColorThemeIter->colorOverallBackground = previousColorThemeIter->colorOverallBackground;
            currentColorThemeIter->colorOverallText = previousColorThemeIter->colorOverallText;
            customColorsExist = true;
        }

        //Set here the color selected by user to corresponding element
        currentColorTheme = colorConfigurationList.size()-1;  //Current color theme will be last one (Custom config)
        currentColorThemeIter->colorBarBackground = iColorDialog.colorId;

        if (switchToCustomTheme){
            ui->comboBox->setCurrentIndex(currentColorTheme);     //Select custom in ComboBox, this calls automatically updateColorsOnScreen()
            if (iLanguage == ENGLISH) {
                ui->label_Info->setText("Switched to custom color theme.");
            } else if (iLanguage == GERMAN) {
                ui->label_Info->setText("Zu Benutzerdefiniertem Thema geschaltet.");
            } else if (iLanguage == SPANISH) {
                ui->label_Info->setText("Cambio a tema personalizado.");
            }
        } else if (!switchToCustomTheme) {
            //ui->label_ColorBarBackground->setStyleSheet(getStyleSheetString("QLabel", currentColorThemeIter->colorBarBackground, false));
            this->updateColorsOnScreen();
        }
    }
}

void ThemeColorsDialog::on_radioBarIncome_clicked()
{
    std::vector<ColorConfiguration>::iterator currentColorThemeIter = colorConfigurationList.begin()+currentColorTheme;
    ui->label_ColorBarSelected->setStyleSheet(getStyleSheetString("QLabel", currentColorThemeIter->colorBarIncomeSelected, true, false));
    ui->label_ColorBarUnselected->setStyleSheet(getStyleSheetString("QLabel", currentColorThemeIter->colorBarIncomeUnselected, true, false));

    showingIncomeBars = true;
}

void ThemeColorsDialog::on_radioBarExpenses_clicked()
{
    std::vector<ColorConfiguration>::iterator currentColorThemeIter = colorConfigurationList.begin()+currentColorTheme;
    ui->label_ColorBarSelected->setStyleSheet(getStyleSheetString("QLabel", currentColorThemeIter->colorBarExpensesSelected, true, false));
    ui->label_ColorBarUnselected->setStyleSheet(getStyleSheetString("QLabel", currentColorThemeIter->colorBarExpensesUnselected, true, false));

    showingIncomeBars= false;
}

void ThemeColorsDialog::on_radioGroupIncome_clicked()
{
    std::vector<ColorConfiguration>::iterator currentColorThemeIter = colorConfigurationList.begin()+currentColorTheme;
    ui->widget->setColors(currentColorThemeIter->colorGroupIncomeSelected,
                          currentColorThemeIter->colorGroupIncomeUnselected,
                          currentColorThemeIter->colorGroupIncomeBackground);

    ui->label_ColorGroupSelected->setStyleSheet(getStyleSheetString("QLabel", currentColorThemeIter->colorGroupIncomeSelected, true, false));
    ui->label_ColorGroupUnselected->setStyleSheet(getStyleSheetString("QLabel", currentColorThemeIter->colorGroupIncomeUnselected, true, false));
    ui->label_ColorGroupBackground->setStyleSheet(getStyleSheetString("QLabel", currentColorThemeIter->colorGroupIncomeBackground, true, false));

    showingIncomeGroups = true;
}

void ThemeColorsDialog::on_radioGroupOutcome_clicked()
{
    std::vector<ColorConfiguration>::iterator currentColorThemeIter = colorConfigurationList.begin()+currentColorTheme;
    ui->widget->setColors(currentColorThemeIter->colorGroupExpensesSelected,
                          currentColorThemeIter->colorGroupExpensesUnselected,
                          currentColorThemeIter->colorGroupExpensesBackground);

    ui->label_ColorGroupSelected->setStyleSheet(getStyleSheetString("QLabel", currentColorThemeIter->colorGroupExpensesSelected, true, false));
    ui->label_ColorGroupUnselected->setStyleSheet(getStyleSheetString("QLabel", currentColorThemeIter->colorGroupExpensesUnselected, true, false));
    ui->label_ColorGroupBackground->setStyleSheet(getStyleSheetString("QLabel", currentColorThemeIter->colorGroupExpensesBackground, true, false));;

    showingIncomeGroups = false;
}

void ThemeColorsDialog::labelColorIncomeAmountTextClicked()
{
    SelectColorDialog iColorDialog;
    iColorDialog.setLanguage(iLanguage);
    iColorDialog.setModal(true);
    iColorDialog.newColorWasSelected = false;
    iColorDialog.setOverallThemeStyleSheet(overallThemeStyleSheet);
    iColorDialog.exec();
    if (iColorDialog.newColorWasSelected)
    {
        std::cout<<"COLOR WAS PICKED - INCOME AMOUNT: "<<iColorDialog.colorId<<'\n';
        bool switchToCustomTheme = false;
        if (currentColorTheme != colorConfigurationList.size()-1){
            switchToCustomTheme = true;
        }

        //If color was changed from Preset, then create an iterator pointing to last colorConfiguration (Custom config)
        std::vector<ColorConfiguration>::iterator currentColorThemeIter = colorConfigurationList.end()-1;
        if (!customColorsExist){
            //Copy current ColorConfiguration to customColorConfiguration
            std::vector<ColorConfiguration>::iterator previousColorThemeIter = colorConfigurationList.begin()+currentColorTheme;
            currentColorThemeIter->colorBarIncomeSelected = previousColorThemeIter->colorGroupIncomeSelected;
            currentColorThemeIter->colorBarIncomeUnselected = previousColorThemeIter->colorBarIncomeUnselected;
            currentColorThemeIter->colorBarExpensesSelected = previousColorThemeIter->colorBarExpensesSelected;
            currentColorThemeIter->colorBarExpensesUnselected = previousColorThemeIter->colorBarExpensesUnselected;
            currentColorThemeIter->colorGroupIncomeSelected = previousColorThemeIter->colorGroupIncomeSelected;
            currentColorThemeIter->colorGroupIncomeUnselected = previousColorThemeIter->colorGroupIncomeUnselected;
            currentColorThemeIter->colorGroupExpensesSelected = previousColorThemeIter->colorGroupExpensesSelected;
            currentColorThemeIter->colorGroupExpensesUnselected = previousColorThemeIter->colorGroupExpensesUnselected;
            currentColorThemeIter->colorGroupIncomeBackground = previousColorThemeIter->colorGroupIncomeBackground;
            currentColorThemeIter->colorGroupExpensesBackground = previousColorThemeIter->colorGroupExpensesBackground;
            currentColorThemeIter->colorBarBackground = previousColorThemeIter->colorBarBackground;
            //currentColorThemeIter->colorTableIncomeAmount = previousColorThemeIter->colorTableIncomeAmount;
            currentColorThemeIter->showMonthlyAmountsInColor = previousColorThemeIter->showMonthlyAmountsInColor;
            currentColorThemeIter->useDarkOverallTheme = previousColorThemeIter->useDarkOverallTheme;
            currentColorThemeIter->colorOverallBackground = previousColorThemeIter->colorOverallBackground;
            currentColorThemeIter->colorOverallText = previousColorThemeIter->colorOverallText;
            customColorsExist = true;
        }

        //Set here the color selected by user to corresponding element
        currentColorTheme = colorConfigurationList.size()-1;  //Current color theme will be last one (Custom config)
        currentColorThemeIter->colorTableIncomeAmount = iColorDialog.colorId;

            int r = 0, g = 0, b = 0;
            getColorCode(currentColorThemeIter->colorTableIncomeAmount, r, g, b);
            ui->tableWidget->item(2, 1)->setForeground(QColor(r, g, b));


        if (switchToCustomTheme){
            ui->comboBox->setCurrentIndex(currentColorTheme);     //Select custom in ComboBox, this calls automatically updateColorsOnScreen()
            if (iLanguage == ENGLISH) {
                ui->label_Info->setText("Switched to custom color theme.");
            } else if (iLanguage == GERMAN) {
                ui->label_Info->setText("Zu Benutzerdefiniertem Thema geschaltet.");
            } else if (iLanguage == SPANISH) {
                ui->label_Info->setText("Cambio a tema personalizado.");
            }
        } else if (!switchToCustomTheme) {
            ui->label_ColorIncomeAmountText->setStyleSheet(getStyleSheetString("QLabel", currentColorThemeIter->colorTableIncomeAmount, true, false));
        }
    }
}

bool ThemeColorsDialog::eventFilter(QObject *obj, QEvent *event)
{
    std::vector<ColorConfiguration>::iterator currentColorThemeIter = colorConfigurationList.begin()+currentColorTheme;
    if (event->type() == QEvent::MouseButtonPress)
    {
        if (qobject_cast<QLabel*>(obj) == ui->label_ColorGroupSelected)
          {
            this->labelGroupSelectedClicked();
          }
        else if(qobject_cast<QLabel*>(obj) == ui->label_ColorGroupUnselected)
          {
            this->labelGroupUnselectedClicked();
          }
        else if (qobject_cast<QLabel*>(obj) == ui->label_ColorGroupBackground)
          {
            this->labelGroupBackgroundClicked();
          }
        else if (qobject_cast<QPushButton*>(obj) == ui->buttonSaveAndSet)
          {
            this->ui->buttonSaveAndSet->setColorForMouseButtonPressEvent();
          }
        else if (qobject_cast<QComboBox*>(obj) == ui->comboBox)
          {
            this->ui->comboBox->setColorForMouseButtonPressEvent();
          }
        else if (qobject_cast<QComboBox*>(obj) == ui->comboBoxOverallTheme)
          {
            this->ui->comboBoxOverallTheme->setColorForMouseButtonPressEvent();
          }
        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        else if (qobject_cast<QLabel*>(obj) == ui->label_ColorBarSelected)
        {
            this->labelBarSelectedClicked();
        }
        else if (qobject_cast<QLabel*>(obj) == ui->label_ColorBarUnselected)
        {
            this->labelBarUnselectedClicked();
        }
        else if (qobject_cast<QLabel*>(obj) == ui->label_ColorBarBackground)
        {
            this->labelBarBackgroundClicked();
        }
        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        else if (qobject_cast<QLabel*>(obj) == ui->label_ColorIncomeAmountText)
        {
            this->labelColorIncomeAmountTextClicked();
        }
    }

    else if (event->type() == QEvent::Enter)
    {
        if (qobject_cast<QLabel*>(obj) == ui->label_ColorGroupSelected)
          {
            if (showingIncomeGroups) {
                ui->label_ColorGroupSelected->setStyleSheet(getStyleSheetString("QLabel", currentColorThemeIter->colorGroupIncomeSelected, true, true));
            } else {
                ui->label_ColorGroupSelected->setStyleSheet(getStyleSheetString("QLabel", currentColorThemeIter->colorGroupExpensesSelected, true, true));
            }
          }
        else if(qobject_cast<QLabel*>(obj) == ui->label_ColorGroupUnselected)
          {
            if (showingIncomeGroups) {
                ui->label_ColorGroupUnselected->setStyleSheet(getStyleSheetString("QLabel", currentColorThemeIter->colorGroupIncomeUnselected, true, true));
            } else {
                ui->label_ColorGroupUnselected->setStyleSheet(getStyleSheetString("QLabel", currentColorThemeIter->colorGroupExpensesUnselected, true, true));
            }
          }
        else if (qobject_cast<QLabel*>(obj) == ui->label_ColorGroupBackground)
          {
            if (showingIncomeGroups) {
                ui->label_ColorGroupBackground->setStyleSheet(getStyleSheetString("QLabel", currentColorThemeIter->colorGroupIncomeBackground, true, true));
            } else {
                ui->label_ColorGroupBackground->setStyleSheet(getStyleSheetString("QLabel", currentColorThemeIter->colorGroupExpensesBackground, true, true));
            }
          }
        else if (qobject_cast<QPushButton*>(obj) == ui->buttonSaveAndSet)
          {
            this->ui->buttonSaveAndSet->setColorForEnterEvent();
          }
        else if (qobject_cast<QComboBox*>(obj) == ui->comboBox)
          {
            this->ui->comboBox->setColorForEnterEvent();
          }
        else if (qobject_cast<QComboBox*>(obj) == ui->comboBoxOverallTheme)
          {
            this->ui->comboBoxOverallTheme->setColorForEnterEvent();
          }
        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        else if (qobject_cast<QLabel*>(obj) == ui->label_ColorBarSelected)
        {
            if (showingIncomeBars){
                ui->label_ColorBarSelected->setStyleSheet(getStyleSheetString("QLabel", currentColorThemeIter->colorBarIncomeSelected, true, true));
            } else {
                ui->label_ColorBarSelected->setStyleSheet(getStyleSheetString("QLabel", currentColorThemeIter->colorBarExpensesSelected, true, true));
            }
        }
        else if (qobject_cast<QLabel*>(obj) == ui->label_ColorBarUnselected)
        {
            if (showingIncomeBars){
                ui->label_ColorBarUnselected->setStyleSheet(getStyleSheetString("QLabel", currentColorThemeIter->colorBarIncomeUnselected, true, true));
            } else {
                ui->label_ColorBarUnselected->setStyleSheet(getStyleSheetString("QLabel", currentColorThemeIter->colorBarExpensesUnselected, true, true));
            }
        }
        else if (qobject_cast<QLabel*>(obj) == ui->label_ColorBarBackground)
        {
            ui->label_ColorBarBackground->setStyleSheet(getStyleSheetString("QLabel", currentColorThemeIter->colorBarBackground, true, true));
        }
        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        else if (qobject_cast<QLabel*>(obj) == ui->label_ColorIncomeAmountText)
        {
            ui->label_ColorIncomeAmountText->setStyleSheet(getStyleSheetString("QLabel", currentColorThemeIter->colorTableIncomeAmount, true, true));
        }
    }

    else if (event->type() == QEvent::Leave)
    {
        if (qobject_cast<QLabel*>(obj) == ui->label_ColorGroupSelected)
          {
            if (showingIncomeGroups) {
                ui->label_ColorGroupSelected->setStyleSheet(getStyleSheetString("QLabel", currentColorThemeIter->colorGroupIncomeSelected, true, false));
            } else {
                ui->label_ColorGroupSelected->setStyleSheet(getStyleSheetString("QLabel", currentColorThemeIter->colorGroupExpensesSelected, true, false));
            }
          }
        else if(qobject_cast<QLabel*>(obj) == ui->label_ColorGroupUnselected)
          {
            if (showingIncomeGroups) {
                ui->label_ColorGroupUnselected->setStyleSheet(getStyleSheetString("QLabel", currentColorThemeIter->colorGroupIncomeUnselected, true, false));
            } else {
                ui->label_ColorGroupUnselected->setStyleSheet(getStyleSheetString("QLabel", currentColorThemeIter->colorGroupExpensesUnselected, true, false));
            }
          }
        else if (qobject_cast<QLabel*>(obj) == ui->label_ColorGroupBackground)
          {
            if (showingIncomeGroups) {
                ui->label_ColorGroupBackground->setStyleSheet(getStyleSheetString("QLabel", currentColorThemeIter->colorGroupIncomeBackground, true, false));
            } else {
                ui->label_ColorGroupBackground->setStyleSheet(getStyleSheetString("QLabel", currentColorThemeIter->colorGroupExpensesBackground, true, false));
            }
          }
        else if (qobject_cast<QPushButton*>(obj) == ui->buttonSaveAndSet)
          {
            this->ui->buttonSaveAndSet->setColorForLeaveEvent();
          }
        else if (qobject_cast<QComboBox*>(obj) == ui->comboBox)
          {
            this->ui->comboBox->setColorForLeaveEvent();
          }
        else if (qobject_cast<QComboBox*>(obj) == ui->comboBoxOverallTheme)
          {
            this->ui->comboBoxOverallTheme->setColorForLeaveEvent();
          }
        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        else if (qobject_cast<QLabel*>(obj) == ui->label_ColorBarSelected)
        {
            if (showingIncomeBars){
                ui->label_ColorBarSelected->setStyleSheet(getStyleSheetString("QLabel", currentColorThemeIter->colorBarIncomeSelected, true, false));
            } else {
                ui->label_ColorBarSelected->setStyleSheet(getStyleSheetString("QLabel", currentColorThemeIter->colorBarExpensesSelected, true, false));
            }
        }
        else if (qobject_cast<QLabel*>(obj) == ui->label_ColorBarUnselected)
        {
            if (showingIncomeBars){
                ui->label_ColorBarUnselected->setStyleSheet(getStyleSheetString("QLabel", currentColorThemeIter->colorBarIncomeUnselected, true, false));
            } else {
                ui->label_ColorBarUnselected->setStyleSheet(getStyleSheetString("QLabel", currentColorThemeIter->colorBarExpensesUnselected, true, false));
            }
        }
        else if (qobject_cast<QLabel*>(obj) == ui->label_ColorBarBackground)
        {
            ui->label_ColorBarBackground->setStyleSheet(getStyleSheetString("QLabel", currentColorThemeIter->colorBarBackground, true, false));
        }
        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        else if (qobject_cast<QLabel*>(obj) == ui->label_ColorIncomeAmountText)
        {
            ui->label_ColorIncomeAmountText->setStyleSheet(getStyleSheetString("QLabel", currentColorThemeIter->colorTableIncomeAmount, true, false));
        }
    }    

    else if (event->type() == QEvent::MouseButtonRelease)
    {
        if (qobject_cast<QWidget*>(obj) == ui->buttonSaveAndSet) {
            this->ui->buttonSaveAndSet->setColorForEnterEvent();
        }
        else if (qobject_cast<QComboBox*>(obj) == ui->comboBox)
          {
            this->ui->comboBox->setColorForEnterEvent();
          }
        else if (qobject_cast<QComboBox*>(obj) == ui->comboBoxOverallTheme)
          {
            this->ui->comboBoxOverallTheme->setColorForEnterEvent();
          }
    }

    else if (event->type() == QEvent::KeyPress)
    {
        if (qobject_cast<QCheckBox*>(obj) == ui->checkBox)
                {
                    QKeyEvent* key = static_cast<QKeyEvent*>(event);
                    if ( (key->key()==Qt::Key_Enter) || (key->key()==Qt::Key_Return) ) {
                            if (ui->checkBox->isChecked()) {
                                this->ui->checkBox->setChecked(false);
                            } else {
                                this->ui->checkBox->setChecked(true);
                            }
                        return true;
                    }
                }
    }
    return false;
}

void ThemeColorsDialog::on_buttonSaveAndSet_clicked()
{
    std::vector<ColorConfiguration>::iterator currentColorConfigIt = colorConfigurationList.begin()+currentColorTheme;

    if (currentColorConfigIt->colorBarIncomeSelected == currentColorConfigIt->colorBarExpensesSelected){
        //Color of income and outcome selected bars are the same
        eraseConfirmation_dialog iEraseConfirmationDialog;
        iEraseConfirmationDialog.setModal(true);
        iEraseConfirmationDialog.setOverallThemeStyleSheet(overallThemeStyleSheet, currentColorConfigIt->useDarkOverallTheme);
        if (iLanguage == GERMAN) {
            iEraseConfirmationDialog.setWindowTitle(" Achtung");
            iEraseConfirmationDialog.setInfoText("Die Farben für die ausgewählten Balken des Einkommens und der Ausgaben sind gleich. Um sie besser zu unterscheiden, wählen Sie unterschiedliche Farben. Wollen Sie fortfahren?");
        } else if (iLanguage == SPANISH) {
            iEraseConfirmationDialog.setWindowTitle(" Aviso");
            iEraseConfirmationDialog.setInfoText("Los colores para las barras de ingreso y egreso seleccionados son los mismos, para diferenciar mejor se recomienda usar colores diferentes. Desea continuar de todas maneras?");
        } else {
            iEraseConfirmationDialog.setWindowTitle(" Warning");
            iEraseConfirmationDialog.setInfoText("Colors for Selected Income and Expenses Bars are the same, to differentiate them better it is recommended to choose different colors. Are you sure you want to proceed?");
        }
        iEraseConfirmationDialog.exec();
        bool confirmColors = iEraseConfirmationDialog.comfirmed();

        if (!confirmColors){
            return;
        }
    }
    else if (currentColorConfigIt->colorBarIncomeSelected == currentColorConfigIt->colorBarIncomeUnselected){
        //Color of Income Selected and Income Un-Selected bars are the same
        eraseConfirmation_dialog iEraseConfirmationDialog;
        iEraseConfirmationDialog.setModal(true);
        iEraseConfirmationDialog.setOverallThemeStyleSheet(overallThemeStyleSheet, currentColorConfigIt->useDarkOverallTheme);
        if (iLanguage == GERMAN) {
            iEraseConfirmationDialog.setWindowTitle(" Achtung");
            iEraseConfirmationDialog.setInfoText("Die Farben der ausgewählten und nicht ausgewählten Balken des Einkommens sind gleich. Um sie besser zu unterscheiden, wählen Sie unterschiedliche Farben. Wollen Sie fortfahren?");
        } else if (iLanguage == SPANISH) {
            iEraseConfirmationDialog.setWindowTitle(" Aviso");
            iEraseConfirmationDialog.setInfoText("Los colores para las barras de ingreso seleccionados y no seleccionados son los mismos, para diferenciar mejor se recomienda usar colores diferentes. Desea continuar de todas maneras?");
        } else {
            iEraseConfirmationDialog.setWindowTitle(" Warning");
            iEraseConfirmationDialog.setInfoText("Colors for Income Selected and Un-Selected Bars are the same, to differentiate them better it is recommended to choose different colors. Are you sure you want to proceed?");
        }
        iEraseConfirmationDialog.exec();
        bool confirmColors = iEraseConfirmationDialog.comfirmed();

        if (!confirmColors){
            return;
        }
    }
    else if (currentColorConfigIt->colorBarExpensesSelected == currentColorConfigIt->colorBarExpensesUnselected){
        //Color of Expenses Selected and Expenses Un-Selected bars are the same
        eraseConfirmation_dialog iEraseConfirmationDialog;
        iEraseConfirmationDialog.setModal(true);
        iEraseConfirmationDialog.setOverallThemeStyleSheet(overallThemeStyleSheet, currentColorConfigIt->useDarkOverallTheme);
        if (iLanguage == GERMAN) {
            iEraseConfirmationDialog.setWindowTitle(" Achtung");
            iEraseConfirmationDialog.setInfoText("Die Farben der ausgewählten und nicht ausgewählten Balken der Ausgaben sind gleich. Um sie besser zu unterscheiden, wählen Sie unterschiedliche Farben. Wollen Sie fortfahren?");
        } else if (iLanguage == SPANISH) {
            iEraseConfirmationDialog.setWindowTitle(" Aviso");
            iEraseConfirmationDialog.setInfoText("Los colores para las barras de egreso seleccionados y no seleccionados son los mismos, para diferenciar mejor se recomienda usar colores diferentes. Desea continuar de todas maneras?");
        } else {
            iEraseConfirmationDialog.setWindowTitle(" Warning");
            iEraseConfirmationDialog.setInfoText("Colors for Expenses Selected and Un-Selected Bars are the same, to differentiate them better it is recommended to choose different colors. Are you sure you want to proceed?");
        }
        iEraseConfirmationDialog.exec();
        bool confirmColors = iEraseConfirmationDialog.comfirmed();

        if (!confirmColors){
            return;
        }
    }

    else if ( (currentColorConfigIt->colorGroupIncomeSelected == currentColorConfigIt->colorGroupIncomeUnselected) ||
              (currentColorConfigIt->colorGroupIncomeSelected == currentColorConfigIt->colorGroupIncomeBackground)   ) {
        //Color of Income Groups: Selected and Un-Selected are the same OR Selected and Background are the same
        eraseConfirmation_dialog iEraseConfirmationDialog;
        iEraseConfirmationDialog.setModal(true);
        iEraseConfirmationDialog.setOverallThemeStyleSheet(overallThemeStyleSheet, currentColorConfigIt->useDarkOverallTheme);
        if (iLanguage == GERMAN) {
            iEraseConfirmationDialog.setWindowTitle(" Achtung");
            iEraseConfirmationDialog.setInfoText("Prüfen Sie bitte die Farben der Einkommensgruppe. Um sie besser zu unterscheiden, wählen Sie unterschiedliche Farben. Wollen Sie fortfahren?");
        } else if (iLanguage == SPANISH) {
            iEraseConfirmationDialog.setWindowTitle(" Aviso");
            iEraseConfirmationDialog.setInfoText("Verifique los colores de grupos de ingreso, para diferenciarlos mejor se recomienda usar colores diferentes. Desea continuar de todas maneras?");
        } else {
            iEraseConfirmationDialog.setWindowTitle(" Warning");
            iEraseConfirmationDialog.setInfoText("Please verify Income Groups colors. To differentiate them better it is recommended to choose different colors. Are you sure you want to proceed?");
        }
            iEraseConfirmationDialog.exec();
        bool confirmColors = iEraseConfirmationDialog.comfirmed();

        if (!confirmColors){
            this->ui->radioGroupIncome->setChecked(true);
            ui->widget->setColors(currentColorConfigIt->colorGroupIncomeSelected,
                                  currentColorConfigIt->colorGroupIncomeUnselected,
                                  currentColorConfigIt->colorGroupIncomeBackground);
            ui->label_ColorGroupSelected->setStyleSheet(getStyleSheetString("QLabel", currentColorConfigIt->colorGroupIncomeSelected, true, false));
            ui->label_ColorGroupUnselected->setStyleSheet(getStyleSheetString("QLabel", currentColorConfigIt->colorGroupIncomeUnselected, true, false));
            ui->label_ColorGroupBackground->setStyleSheet(getStyleSheetString("QLabel", currentColorConfigIt->colorGroupIncomeBackground, true, false));;
            showingIncomeGroups = true;

            return;
        }
    }
    else if ( (currentColorConfigIt->colorGroupExpensesSelected == currentColorConfigIt->colorGroupExpensesUnselected) ||
              (currentColorConfigIt->colorGroupExpensesSelected == currentColorConfigIt->colorGroupExpensesBackground)   ) {
        //Color of Expenses Groups: Selected and Un-Selected are the same OR Selected and Background are the same
        eraseConfirmation_dialog iEraseConfirmationDialog;
        iEraseConfirmationDialog.setModal(true);
        iEraseConfirmationDialog.setOverallThemeStyleSheet(overallThemeStyleSheet, currentColorConfigIt->useDarkOverallTheme);
        if (iLanguage == GERMAN) {
            iEraseConfirmationDialog.setWindowTitle(" Achtung");
            iEraseConfirmationDialog.setInfoText("Prüfen Sie bitte die Farben der Ausgabensgruppe. Um sie besser zu unterscheiden, wählt man unterschiedliche Farben. Wollen Sie fortfahren?");
        } else if (iLanguage == SPANISH) {
            iEraseConfirmationDialog.setWindowTitle(" Aviso");
            iEraseConfirmationDialog.setInfoText("Verifique los colores de grupos de egreso, para diferenciarlos mejor se recomienda usar colores diferentes. Desea continuar de todas maneras?");
        } else {
            iEraseConfirmationDialog.setWindowTitle(" Warning");
            iEraseConfirmationDialog.setInfoText("Please verify Expenses Groups colors. To differentiate them better it is recommended to choose different colors. Are you sure you want to proceed?");
        }
        iEraseConfirmationDialog.exec();
        bool confirmColors = iEraseConfirmationDialog.comfirmed();

        if (!confirmColors){
            this->ui->radioGroupOutcome->setChecked(true);
            ui->widget->setColors(currentColorConfigIt->colorGroupExpensesSelected,
                                  currentColorConfigIt->colorGroupExpensesUnselected,
                                  currentColorConfigIt->colorGroupExpensesBackground);
            ui->label_ColorGroupSelected->setStyleSheet(getStyleSheetString("QLabel", currentColorConfigIt->colorGroupExpensesSelected, true, false));
            ui->label_ColorGroupUnselected->setStyleSheet(getStyleSheetString("QLabel", currentColorConfigIt->colorGroupExpensesUnselected, true, false));
            ui->label_ColorGroupBackground->setStyleSheet(getStyleSheetString("QLabel", currentColorConfigIt->colorGroupExpensesBackground, true, false));;
            showingIncomeGroups = false;

            return;
        }
    }

    colorSelectionConfirmed = true;
    this->close();
}

void ThemeColorsDialog::addColorConfiguration(const  std::string &themeName,
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
                                               const bool &useDarkOverall)
{
    ColorConfiguration tempColorConfiguration(themeName);
    tempColorConfiguration.colorBarIncomeSelected     = barIncomeSelected;
    tempColorConfiguration.colorBarIncomeUnselected   = barIncomeUnselected;
    tempColorConfiguration.colorBarExpensesSelected   = barExpensesSelected;
    tempColorConfiguration.colorBarExpensesUnselected = barExpensesUnselected;
    tempColorConfiguration.colorBarBackground         = barBackground;

    tempColorConfiguration.colorGroupIncomeSelected   = groupIncomeSelected;
    tempColorConfiguration.colorGroupIncomeUnselected = groupIncomeUnselected;
    tempColorConfiguration.colorGroupIncomeBackground = groupIncomeBackground;

    tempColorConfiguration.colorGroupExpensesSelected   = groupExpensesSelected;
    tempColorConfiguration.colorGroupExpensesUnselected = groupExpensesUnselected;
    tempColorConfiguration.colorGroupExpensesBackground = groupExpensesBackground;

    tempColorConfiguration.colorTableIncomeAmount       = tableIncomeAmount;
    tempColorConfiguration.showMonthlyAmountsInColor    = monthlyAmountInColor;

    tempColorConfiguration.useDarkOverallTheme        = useDarkOverall;
    tempColorConfiguration.setOverallThemeColors();

    colorConfigurationList.push_back(tempColorConfiguration);    
    ++numberOfPresetColorThemes;

    this->allowUpdateColorsInPresetComboBox=false;
    ui->comboBox->addItem(QString::fromStdString(themeName));
    this->allowUpdateColorsInPresetComboBox=true;
}

void ThemeColorsDialog::updateColorsOnScreen()
{
    std::vector<ColorConfiguration>::iterator currentColorConfigIt = colorConfigurationList.begin()+currentColorTheme;

    ///--------------------------------------------------------------------------///--------------------------------------------------------------------------///
    //Set colors for pie chart
    if (ui->radioGroupIncome->isChecked()) {
        ui->widget->setColors(currentColorConfigIt->colorGroupIncomeSelected,
                              currentColorConfigIt->colorGroupIncomeUnselected,
                              currentColorConfigIt->colorGroupIncomeBackground);

        ui->widget->update();

        ui->label_ColorGroupSelected->setStyleSheet(getStyleSheetString("QLabel", currentColorConfigIt->colorGroupIncomeSelected, true, false));
        ui->label_ColorGroupUnselected->setStyleSheet(getStyleSheetString("QLabel", currentColorConfigIt->colorGroupIncomeUnselected, true, false));
        ui->label_ColorGroupBackground->setStyleSheet(getStyleSheetString("QLabel", currentColorConfigIt->colorGroupIncomeBackground, true, false));
    }   else  if (ui->radioGroupOutcome->isChecked()) {
        ui->widget->setColors(currentColorConfigIt->colorGroupExpensesSelected,
                              currentColorConfigIt->colorGroupExpensesUnselected,
                              currentColorConfigIt->colorGroupExpensesBackground);

        ui->widget->update();

        ui->label_ColorGroupSelected->setStyleSheet(getStyleSheetString("QLabel", currentColorConfigIt->colorGroupExpensesSelected, true, false));
        ui->label_ColorGroupUnselected->setStyleSheet(getStyleSheetString("QLabel", currentColorConfigIt->colorGroupExpensesUnselected, true, false));
        ui->label_ColorGroupBackground->setStyleSheet(getStyleSheetString("QLabel", currentColorConfigIt->colorGroupExpensesBackground, true, false));
    }


    ///--------------------------------------------------------------------------///--------------------------------------------------------------------------///
    //Set colors for bar chart
    ui->widget_2->activationCounterBarBackgroundColor = 0; ///THIS FIXES THE ISSUE WHEN BG-COLOR NOT BEING SET. IF VALUE IS ZERO THE GL-UPDATE LOOP WILL BE ITERATED
    ui->widget_2->setBarColors(currentColorConfigIt->colorBarIncomeSelected,
                               currentColorConfigIt->colorBarIncomeUnselected,
                               currentColorConfigIt->colorBarExpensesSelected,
                               currentColorConfigIt->colorBarExpensesUnselected);
    ui->widget_2->setBackgroundColor(currentColorConfigIt->colorBarBackground);
    ui->widget_2->update();

    if (ui->radioBarIncome->isChecked())
    {
        ui->label_ColorBarSelected->setStyleSheet(getStyleSheetString("QLabel", currentColorConfigIt->colorBarIncomeSelected, true, false));
        ui->label_ColorBarUnselected->setStyleSheet(getStyleSheetString("QLabel", currentColorConfigIt->colorBarIncomeUnselected, true, false));
        ui->label_ColorBarBackground->setStyleSheet(getStyleSheetString("QLabel", currentColorConfigIt->colorBarBackground, true, false));

    } else if (ui->radioBarExpenses->isChecked()){
        ui->label_ColorBarSelected->setStyleSheet(getStyleSheetString("QLabel", currentColorConfigIt->colorBarExpensesSelected, true, false));
        ui->label_ColorBarUnselected->setStyleSheet(getStyleSheetString("QLabel", currentColorConfigIt->colorBarExpensesUnselected, true, false));
        ui->label_ColorBarBackground->setStyleSheet(getStyleSheetString("QLabel", currentColorConfigIt->colorBarBackground, true, false));
    }


    ///--------------------------------------------------------------------------///--------------------------------------------------------------------------///
    //Set color for label of Text tablewidget amount.
     ui->label_ColorIncomeAmountText->setStyleSheet(getStyleSheetString("QLabel", currentColorConfigIt->colorTableIncomeAmount, true, false));
     int r = 0, g = 0, b = 0;
     getColorCode(currentColorConfigIt->colorTableIncomeAmount, r, g, b);
     ui->tableWidget->item(2, 1)->setForeground(QColor(r, g, b));
     QFont iFont;
     iFont.setPointSize(8);
     ui->tableWidget->horizontalHeader()->setFont(iFont);
     ui->tableWidget->verticalHeader()->setFont(iFont);
     QStringList tableHeader;
     if (iLanguage == ENGLISH) {
         tableHeader<<"Name"<<"Amount"<<"Day";
     } else if (iLanguage == GERMAN) {
         tableHeader<<"Name"<<"Betrag"<<"Tag";
     } else if (iLanguage == SPANISH) {
         tableHeader<<"Nombre"<<"Monto"<<"Día";
     }
     ui->tableWidget->setHorizontalHeaderLabels(tableHeader);
     int r_OB, g_OB, b_OB;
     getColorCode(currentColorConfigIt->colorOverallBackground, r_OB, g_OB, b_OB);
     QString overallBackgroundColor = "background-color: rgb("+   //Overall background
                                      QString::number(r_OB)+
                                      ","+
                                      QString::number(g_OB)+
                                      ","+
                                      QString::number(b_OB)+
                                      ");";
     ui->tableWidget->setStyleSheet("QTableCornerButton::section {" + overallBackgroundColor + "}"
                                          "QHeaderView::section {" + overallBackgroundColor + "}");


     ///--------------------------------------------------------------------------///--------------------------------------------------------------------------///
     //Set color for label of Text monthly amounts.
     if (currentColorConfigIt->showMonthlyAmountsInColor)
     {
         ui->checkBox->setChecked(true);
         ///INCOME
         ui->monthlyIncomeLabel->setStyleSheet(getStyleSheetString("QLabel",currentColorConfigIt->colorBarIncomeSelected, false, false));
         ///EXPENSES
         ui->monthlyExpensesLabel->setStyleSheet(getStyleSheetString("QLabel",currentColorConfigIt->colorBarExpensesSelected, false, false));
     }
     else if (!(currentColorConfigIt->showMonthlyAmountsInColor)){
         currentColorConfigIt->setOverallThemeColors();
         ui->checkBox->setChecked(false);
         ///INCOME
         ui->monthlyIncomeLabel->setStyleSheet(getStyleSheetString("QLabel",currentColorConfigIt->colorOverallText, false, false));
         ///EXPENSES
         ui->monthlyExpensesLabel->setStyleSheet(getStyleSheetString("QLabel",currentColorConfigIt->colorOverallText, false, false));
     }

     ///--------------------------------------------------------------------------///--------------------------------------------------------------------------///
     //Set color for Overall background, text and borders depending on value Light/Dark.
     this->ui->tableWidget->verticalHeader()->setStyleSheet("background-color: rgba(0, 0, 0, 0); border-bottom-style: rgba(255, 255, 255, 0);");
     overallThemeStyleSheet = getStyleSheetString("", currentColorConfigIt->colorOverallBackground,  true,  false) +
                              getStyleSheetString("", currentColorConfigIt->colorOverallText, false, false);
     this->setStyleSheet(overallThemeStyleSheet);
     this->ui->buttonSaveAndSet->updateColorTheme(currentColorConfigIt->useDarkOverallTheme);
     this->ui->comboBox->updateColorTheme(currentColorConfigIt->useDarkOverallTheme);
     this->ui->comboBoxOverallTheme->updateColorTheme(currentColorConfigIt->useDarkOverallTheme);	 
     this->ui->comboBox->updateColorTheme(currentColorConfigIt->useDarkOverallTheme);
}

void ThemeColorsDialog::addCustomColorConfiguration(const ColorConfiguration &customColorConfig)
{
      colorConfigurationList.push_back(customColorConfig);
      if (iLanguage == ENGLISH) {
          ui->comboBox->addItem("Custom");
      } else if (iLanguage == GERMAN) {
          ui->comboBox->addItem("Benutzerdefiniert");
      } else if (iLanguage == SPANISH) {
          ui->comboBox->addItem("Personalizado");
      }

      //std::cout<<"ADDED CUSTOM COLORCONFIG TO LIST. Size of list of configurations: "<<colorConfigurationList.size()<<'\n';

      if (  (customColorConfig.colorBarIncomeSelected != 13 ) ||  //If any custom color has been changed from STANDARD-DEFAULT, it means customColors exist
            (customColorConfig.colorBarIncomeUnselected != 4 ) ||
            (customColorConfig.colorBarExpensesSelected != 9 ) ||
            (customColorConfig.colorBarExpensesUnselected != 7 ) ||
            (customColorConfig.colorBarBackground != 36 ) ||
            (customColorConfig.colorGroupIncomeSelected != 13 ) ||
            (customColorConfig.colorGroupIncomeUnselected != 4 ) ||
            (customColorConfig.colorGroupExpensesSelected != 9 ) ||
            (customColorConfig.colorGroupExpensesUnselected != 16 ) ||
            (customColorConfig.colorGroupIncomeBackground != 8 ) ||
            (customColorConfig.colorGroupExpensesBackground != 8 ) ||
            (customColorConfig.colorTableIncomeAmount != 13 ) ||
            (customColorConfig.showMonthlyAmountsInColor != true) ||
            (customColorConfig.useDarkOverallTheme != false)   ){
          customColorsExist = true;
          std::cout<<"CUSTOM COLORCONFIG EXIST, VALUES SET "<<'\n';
      }
}

void ThemeColorsDialog::setCurrentColorConfiguration()
{
    //USE CREATED VECTOR STORING ALL COLORS HERE, THE COLORS FOR STANDARD, DARK, AND LIGHT WILL BE DECLARED IN THIS CLASS
    //(THEMECOLORSDIALOG). THE EXTERIOR CLASSES (like mainWindow) WILL CARE JUST ABOUT THE RESULT OF THE CURRENT SELECTED COLOR

    this->ui->comboBox->setCurrentIndex(currentColorTheme); // Index starts from 0
    this->updateColorsOnScreen();
}

void ThemeColorsDialog::on_comboBox_currentIndexChanged(int index)
{
    if (allowUpdateColorsInPresetComboBox)
    {
        std::cout<<"SIZE OF COLORCONFIG-LIST IS: "<<colorConfigurationList.size()<<'\n';
        unsigned int selectedIndex = index;
        if (selectedIndex == (colorConfigurationList.size()-1)){
            //If Index was changed to customIndex, then create an iterator pointing to last colorConfiguration (Custom config)
            std::vector<ColorConfiguration>::iterator currentColorThemeIter = colorConfigurationList.end()-1;
            if (!customColorsExist){
                //Copy current ColorConfiguration to customColorConfiguration
                //std::cout<<"INDEX CHANGED AND NO CUSTOMCOLORS EXIST. COPYING CURRENT COLORS TO CUSTOMTHEME. CURRENTTHEME IS:"<<currentColorTheme<<'\n';
                std::vector<ColorConfiguration>::iterator previousColorThemeIter = colorConfigurationList.begin()+currentColorTheme;
                currentColorThemeIter->colorBarIncomeSelected = previousColorThemeIter->colorBarIncomeSelected;
                currentColorThemeIter->colorBarIncomeUnselected = previousColorThemeIter->colorBarIncomeUnselected;
                currentColorThemeIter->colorBarExpensesSelected = previousColorThemeIter->colorBarExpensesSelected;
                currentColorThemeIter->colorBarExpensesUnselected = previousColorThemeIter->colorBarExpensesUnselected;
                currentColorThemeIter->colorGroupIncomeSelected = previousColorThemeIter->colorGroupIncomeSelected;
                currentColorThemeIter->colorGroupIncomeUnselected = previousColorThemeIter->colorGroupIncomeUnselected;
                currentColorThemeIter->colorGroupExpensesSelected = previousColorThemeIter->colorGroupExpensesSelected;
                currentColorThemeIter->colorGroupExpensesUnselected = previousColorThemeIter->colorGroupExpensesUnselected;
                currentColorThemeIter->colorGroupIncomeBackground = previousColorThemeIter->colorGroupIncomeBackground;
                currentColorThemeIter->colorGroupExpensesBackground = previousColorThemeIter->colorGroupExpensesBackground;
                currentColorThemeIter->colorBarBackground = previousColorThemeIter->colorBarBackground;
                currentColorThemeIter->colorTableIncomeAmount = previousColorThemeIter->colorTableIncomeAmount;
                currentColorThemeIter->showMonthlyAmountsInColor = previousColorThemeIter->showMonthlyAmountsInColor;
                currentColorThemeIter->useDarkOverallTheme = previousColorThemeIter->useDarkOverallTheme;
                currentColorThemeIter->colorOverallBackground = previousColorThemeIter->colorOverallBackground;
                currentColorThemeIter->colorOverallText = previousColorThemeIter->colorOverallText;
                //customColorsExist = true;
            }
        }

        currentColorTheme = index;
        if (currentColorTheme != colorConfigurationList.size()-1){
            ui->label_Info->clear();
        }

        //Here just set the index of DarkOverallTheme-ComboBox, do not update colors, it is done later.
        std::vector<ColorConfiguration>::iterator currentColorConfigIt = colorConfigurationList.begin()+currentColorTheme;
        this->allowUpdateColorsInOverallDarkThemeComboBox = false;
        if (currentColorConfigIt->useDarkOverallTheme){
            this->ui->comboBoxOverallTheme->setCurrentIndex(1);
            std::cout<<"THEME INDEX SET TO DARK"<<'\n';
        } else if (!currentColorConfigIt->useDarkOverallTheme) {
            this->ui->comboBoxOverallTheme->setCurrentIndex(0);
            std::cout<<"THEME INDEX SET TO LIGHT"<<'\n';
        }
        this->allowUpdateColorsInOverallDarkThemeComboBox = true;

        this->updateColorsOnScreen();
    }
}

void ThemeColorsDialog::on_comboBoxOverallTheme_currentIndexChanged(int index)
{
    if (allowUpdateColorsInOverallDarkThemeComboBox)
    {
        std::cout<<"ALLOWED CHANGE OF OVERALL THEME TO DARK/LIGHT"<<'\n';
        bool switchToCustomTheme = false;
        if (currentColorTheme != colorConfigurationList.size()-1){  //If color was changed from Preset, then create an iterator pointing to last colorConfiguration (Custom config)
            std::vector<ColorConfiguration>::iterator currentColorThemeIter = colorConfigurationList.end()-1;
            if (!customColorsExist){
                //Copy current ColorConfiguration to customColorConfiguration
                std::vector<ColorConfiguration>::iterator previousColorThemeIter = colorConfigurationList.begin()+currentColorTheme;
                currentColorThemeIter->colorBarIncomeSelected = previousColorThemeIter->colorBarIncomeSelected;
                currentColorThemeIter->colorBarIncomeUnselected = previousColorThemeIter->colorBarIncomeUnselected;
                currentColorThemeIter->colorBarExpensesSelected = previousColorThemeIter->colorBarExpensesSelected;
                currentColorThemeIter->colorBarExpensesUnselected = previousColorThemeIter->colorBarExpensesUnselected;
                currentColorThemeIter->colorGroupIncomeSelected = previousColorThemeIter->colorGroupIncomeSelected;
                currentColorThemeIter->colorGroupIncomeUnselected = previousColorThemeIter->colorGroupIncomeUnselected;
                currentColorThemeIter->colorGroupExpensesSelected = previousColorThemeIter->colorGroupExpensesSelected;
                currentColorThemeIter->colorGroupExpensesUnselected = previousColorThemeIter->colorGroupExpensesUnselected;
                currentColorThemeIter->colorGroupIncomeBackground = previousColorThemeIter->colorGroupIncomeBackground;
                currentColorThemeIter->colorGroupExpensesBackground = previousColorThemeIter->colorGroupExpensesBackground;
                currentColorThemeIter->colorBarBackground = previousColorThemeIter->colorBarBackground;
                currentColorThemeIter->colorTableIncomeAmount = previousColorThemeIter->colorTableIncomeAmount;
                //currentColorThemeIter->useDarkOverallTheme = previousColorThemeIter->useDarkOverallTheme;
                currentColorThemeIter->showMonthlyAmountsInColor = previousColorThemeIter->showMonthlyAmountsInColor;
                customColorsExist = true;
                std::cout<<"Copy of preset made IN COMBO BOX DARK THEME"<<'\n';
            }
            currentColorTheme = colorConfigurationList.size()-1;  //Current color theme will be last one (Custom config)
            if (iLanguage == ENGLISH) {
                ui->label_Info->setText("Switched to custom color theme.");
            } else if (iLanguage == GERMAN) {
                ui->label_Info->setText("Zu Benutzerdefiniertem Thema geschaltet.");
            } else if (iLanguage == SPANISH) {
                ui->label_Info->setText("Cambio a tema personalizado.");
            }
            switchToCustomTheme = true;
        }

        //Set here the color selected by user to corresponding elements
        std::vector<ColorConfiguration>::iterator currentColorConfigIt = colorConfigurationList.begin()+currentColorTheme;
        if (index == 0){
            currentColorConfigIt->useDarkOverallTheme = false;
        } else if (index == 1) {
            currentColorConfigIt->useDarkOverallTheme = true;
        }  currentColorConfigIt->setOverallThemeColors();

        if (switchToCustomTheme){
            this->allowUpdateColorsInPresetComboBox = false;
            ui->comboBox->setCurrentIndex(currentColorTheme);     //Select custom in ComboBox, In this case updateColorsOnScreen() is not called.
            this->allowUpdateColorsInPresetComboBox = true;
        }
        this->updateColorsOnScreen();
    }
}

void ThemeColorsDialog::on_checkBox_clicked()
{
    if (currentColorTheme != colorConfigurationList.size()-1){
        if (iLanguage == ENGLISH) {
            ui->label_Info->setText("Switched to custom color theme.");
        } else if (iLanguage == GERMAN) {
            ui->label_Info->setText("Zu Benutzerdefiniertem Thema geschaltet.");
        } else if (iLanguage == SPANISH) {
            ui->label_Info->setText("Cambio a tema personalizado.");
        }

        //If color was changed from Preset, then create an iterator pointing to last colorConfiguration (Custom config)
        std::vector<ColorConfiguration>::iterator currentColorThemeIter = colorConfigurationList.end()-1;
        if (!customColorsExist){
            //Copy current ColorConfiguration to customColorConfiguration
            std::vector<ColorConfiguration>::iterator previousColorThemeIter = colorConfigurationList.begin()+currentColorTheme;
            currentColorThemeIter->colorBarIncomeSelected = previousColorThemeIter->colorBarIncomeSelected;
            currentColorThemeIter->colorBarIncomeUnselected = previousColorThemeIter->colorBarIncomeUnselected;
            currentColorThemeIter->colorBarExpensesSelected = previousColorThemeIter->colorBarExpensesSelected;
            currentColorThemeIter->colorBarExpensesUnselected = previousColorThemeIter->colorBarExpensesUnselected;
            currentColorThemeIter->colorGroupIncomeSelected = previousColorThemeIter->colorGroupIncomeSelected;
            currentColorThemeIter->colorGroupIncomeUnselected = previousColorThemeIter->colorGroupIncomeUnselected;
            currentColorThemeIter->colorGroupExpensesSelected = previousColorThemeIter->colorGroupExpensesSelected;
            currentColorThemeIter->colorGroupExpensesUnselected = previousColorThemeIter->colorGroupExpensesUnselected;
            currentColorThemeIter->colorGroupIncomeBackground = previousColorThemeIter->colorGroupIncomeBackground;
            currentColorThemeIter->colorGroupExpensesBackground = previousColorThemeIter->colorGroupExpensesBackground;
            currentColorThemeIter->colorBarBackground = previousColorThemeIter->colorBarBackground;
            currentColorThemeIter->colorTableIncomeAmount = previousColorThemeIter->colorTableIncomeAmount;
            currentColorThemeIter->useDarkOverallTheme = previousColorThemeIter->useDarkOverallTheme;
            currentColorThemeIter->colorOverallBackground = previousColorThemeIter->colorOverallBackground;
            currentColorThemeIter->colorOverallText = previousColorThemeIter->colorOverallText;
            //currentColorThemeIter->showMonthlyAmountsInColor = previousColorThemeIter->showMonthlyAmountsInColor;
            customColorsExist = true;
        }

    }

    //If color was changed from Preset, then create an iterator pointing to last colorConfiguration (Custom config)
    currentColorTheme = colorConfigurationList.size()-1;  //Current color theme will be last one (Custom config)
    std::vector<ColorConfiguration>::iterator currentColorConfigIt = colorConfigurationList.begin()+currentColorTheme;

    ui->comboBox->setCurrentIndex(currentColorTheme);

    //Set here the color selected by user to corresponding element, the checkBox has already last(recently changed) state/value at this point.
    if (!(currentColorConfigIt->showMonthlyAmountsInColor) && (ui->checkBox->isChecked()) ){
        currentColorConfigIt->showMonthlyAmountsInColor = true;
        std::cout<<"FIRST OPTION - showMonthlyAmountsInColor SET AS TRUE"<<'\n';
    }
    else if (currentColorConfigIt->showMonthlyAmountsInColor && !(ui->checkBox->isChecked())) {
        currentColorConfigIt->showMonthlyAmountsInColor = false;
        std::cout<<"SECOND OPTION - showMonthlyAmountsInColor SET AS FALSE"<<'\n';
    }
    else if (currentColorConfigIt->showMonthlyAmountsInColor && ui->checkBox->isChecked()){
        currentColorConfigIt->showMonthlyAmountsInColor = false;
        std::cout<<"THIRD OPTION - showMonthlyAmountsInColor SET AS FALSE"<<'\n';
    }
    else if (!(currentColorConfigIt->showMonthlyAmountsInColor) && !(ui->checkBox->isChecked())){
        currentColorConfigIt->showMonthlyAmountsInColor = true;
        std::cout<<"FOURTH OPTION - showMonthlyAmountsInColor SET AS TRUE"<<'\n';
    }
    this->updateColorsOnScreen();
}
