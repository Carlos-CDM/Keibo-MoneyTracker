#ifndef CUSTOMCOMBOBOX_H
#define CUSTOMCOMBOBOX_H

#include <QComboBox>

class CustomComboBox : public QComboBox
{
public:
    CustomComboBox(QWidget *parent = 0);
     ~CustomComboBox();

    void updateColorTheme(const bool &useDarkTheme);
    void setColorForEnterEvent();
    void setColorForLeaveEvent();
    void setColorForMouseButtonPressEvent();

private:
    bool usingDarkTheme;

    QString darkColorIdle = "QComboBox{border: 1px solid gray; border-color: rgba(102, 102, 102, 255); background-color:rgba(83, 83, 83, 255); border-radius: 3px; }";
    QString darkColorFocused = "QComboBox{ border: 1px solid gray; border-color: rgba(102, 102, 102, 255); background-color:rgba(102, 102, 102, 255); border-radius: 3px; }";
    QString darkColorMousePressed = "QComboBox{ border: 1px solid gray; border-color: rgba(102, 102, 102, 255); background-color:rgba(125, 125, 125, 255); border-radius: 3px; }";

    QString lightColorIdle = "QComboBox{ border: 1px solid gray; border-color: rgba(171, 171, 171, 255); background-color:rgba(245, 245, 245, 255); border-radius: 3px; }";
    QString lightColorFocused = "QComboBox{ border: 1px solid gray; border-color: rgba(171, 171, 171, 255); background-color:rgba(200, 200, 200, 255); border-radius: 3px; }";
    QString lightColorMousePressed = "QComboBox{ border: 1px solid gray; border-color: rgba(171, 171, 171, 255); background-color:rgba(171, 171, 171, 255); border-radius: 3px; }";
};

#endif // CUSTOMCOMBOBOX_H
