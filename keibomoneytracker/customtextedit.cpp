#include "customtextedit.h"

CustomTextEdit::CustomTextEdit(QWidget *parent) :
    QTextEdit(parent)
{

}

CustomTextEdit::~CustomTextEdit()
{

}

void CustomTextEdit::updateColorTheme(const bool &useDarkTheme)
{
    usingDarkTheme = useDarkTheme;

    if (usingDarkTheme) {
        this->setStyleSheet(darkColorIdle);
    } else {
        this->setStyleSheet(lightColorIdle);
    }
}


void CustomTextEdit::setColorForEnterEvent()
{
    if (usingDarkTheme) {
        this->setStyleSheet(darkColorFocused);
    } else {
        this->setStyleSheet(lightColorFocused);
    }
}

void CustomTextEdit::setColorForLeaveEvent()
{
    if (usingDarkTheme) {
        this->setStyleSheet(darkColorIdle);
    } else {
        this->setStyleSheet(lightColorIdle);
    }
}

void CustomTextEdit::setColorForMouseButtonPressEvent()
{
    if (usingDarkTheme) {
        this->setStyleSheet(darkColorMousePressed);
    } else {
        this->setStyleSheet(lightColorMousePressed);
    }
}
