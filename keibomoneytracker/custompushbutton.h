#ifndef CUSTOMPUSHBUTTON_H
#define CUSTOMPUSHBUTTON_H

#include <QPushButton>

class CustomPushButton : public QPushButton
{
public:
    CustomPushButton(QWidget *parent = 0);
    ~CustomPushButton();

    void updateColorTheme(const bool &useDarkTheme);
    void setColorForEnterEvent();
    void setColorForLeaveEvent();
    void setColorForMouseButtonPressEvent();


private:
    bool usingDarkTheme = false;

    QString darkColorIdle = "QPushButton{ border: 1px solid gray; border-color: rgba(102, 102, 102, 255); background-color:rgba(83, 83, 83, 255); border-radius: 3px; }";
    QString darkColorFocused = "QPushButton{ border: 1px solid gray; border-color: rgba(102, 102, 102, 255); background-color:rgba(102, 102, 102, 255); border-radius: 3px; }";
    QString darkColorMousePressed = "QPushButton{ border: 1px solid gray; border-color: rgba(102, 102, 102, 255); background-color:rgba(125, 125, 125, 255); border-radius: 3px; }";

    QString lightColorIdle = "QPushButton{ border: 1px solid gray; border-color: rgba(171, 171, 171, 255); background-color:rgba(245, 245, 245, 255); border-radius: 3px; }";
    QString lightColorFocused = "QPushButton{ border: 1px solid gray; border-color: rgba(171, 171, 171, 255); background-color:rgba(200, 200, 200, 255); border-radius: 3px; }";
    QString lightColorMousePressed = "QPushButton{ border: 1px solid gray; border-color: rgba(171, 171, 171, 255); background-color:rgba(171, 171, 171, 255); border-radius: 3px; }";

};

#endif // CUSTOMPUSHBUTTON_H
