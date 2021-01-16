#include "custompushbutton.h"
#include <QEvent>

CustomPushButton::CustomPushButton(QWidget *parent) :
    QPushButton(parent)
{
}

CustomPushButton::~CustomPushButton()
{

}

void CustomPushButton::updateColorTheme(const bool &useDarkTheme)
{
    usingDarkTheme = useDarkTheme;

    if (usingDarkTheme) {
        this->setStyleSheet(darkColorIdle);
    } else {
        this->setStyleSheet(lightColorIdle);
    }
}


void CustomPushButton::setColorForEnterEvent()
{
    if (usingDarkTheme) {
        this->setStyleSheet(darkColorFocused);
    } else {
        this->setStyleSheet(lightColorFocused);
    }
}

void CustomPushButton::setColorForLeaveEvent()
{
    if (usingDarkTheme) {
        this->setStyleSheet(darkColorIdle);
    } else {
        this->setStyleSheet(lightColorIdle);
    }
}

void CustomPushButton::setColorForMouseButtonPressEvent()
{
    if (usingDarkTheme) {
        this->setStyleSheet(darkColorMousePressed);
    } else {
        this->setStyleSheet(lightColorMousePressed);
    }
}
