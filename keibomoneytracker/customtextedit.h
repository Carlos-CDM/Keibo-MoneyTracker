#ifndef CUSTOMTEXTEDIT_H
#define CUSTOMTEXTEDIT_H

#include <QTextEdit>

class CustomTextEdit : public QTextEdit
{
public:
    CustomTextEdit(QWidget *parent = 0);
    ~CustomTextEdit();

    void updateColorTheme(const bool &useDarkTheme);
    void setColorForEnterEvent();
    void setColorForLeaveEvent();
    void setColorForMouseButtonPressEvent();

private:
    bool usingDarkTheme = false;

    QString darkColorIdle = "QTextEdit{ border: 1px solid gray; border-color: rgba(102, 102, 102, 255); background-color:rgba(83, 83, 83, 255); border-radius: 3px; }";
    QString darkColorFocused = "QTextEdit{ border: 1px solid gray; border-color: rgba(102, 102, 102, 255); background-color:rgba(102, 102, 102, 255); border-radius: 3px; }";
    QString darkColorMousePressed = "QTextEdit{ border: 1px solid gray; border-color: rgba(102, 102, 102, 255); background-color:rgba(125, 125, 125, 255); border-radius: 3px; }";

    QString lightColorIdle = "QTextEdit{ border: 1px solid gray; border-color: rgba(171, 171, 171, 255); background-color:rgba(245, 245, 245, 255); border-radius: 3px; }";
    QString lightColorFocused = "QTextEdit{ border: 1px solid gray; border-color: rgba(171, 171, 171, 255); background-color:rgba(200, 200, 200, 255); border-radius: 3px; }";
    QString lightColorMousePressed = "QTextEdit{ border: 1px solid gray; border-color: rgba(171, 171, 171, 255); background-color:rgba(171, 171, 171, 255); border-radius: 3px; }";
};

#endif // CUSTOMTEXTEDIT_H
