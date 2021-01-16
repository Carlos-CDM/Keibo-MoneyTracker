#include "customcombobox.h"

CustomComboBox::CustomComboBox(QWidget *parent) :
    QComboBox(parent)
{
}

CustomComboBox::~CustomComboBox()
{

}

void CustomComboBox::updateColorTheme(const bool &useDarkTheme)
{
    usingDarkTheme = useDarkTheme;

    if (usingDarkTheme) {
        this->setStyleSheet("QScrollBar:vertical {width: 15px;}"+darkColorIdle);
    } else {
        this->setStyleSheet("QScrollBar:vertical {width: 15px;}"+lightColorIdle);
    }
}


void CustomComboBox::setColorForEnterEvent()
{
    if (usingDarkTheme) {
        this->setStyleSheet("QScrollBar:vertical {width: 15px;}"+darkColorFocused);
    } else {
        this->setStyleSheet("QScrollBar:vertical {width: 15px;}"+lightColorFocused);
    }
}

void CustomComboBox::setColorForLeaveEvent()
{
    if (usingDarkTheme) {
        this->setStyleSheet("QScrollBar:vertical {width: 15px;}"+darkColorIdle);
    } else {
        this->setStyleSheet("QScrollBar:vertical {width: 15px;}"+lightColorIdle);
    }
}

void CustomComboBox::setColorForMouseButtonPressEvent()
{
    if (usingDarkTheme) {
        this->setStyleSheet("QScrollBar:vertical {width: 15px;}"+darkColorMousePressed);
    } else {
        this->setStyleSheet("QScrollBar:vertical {width: 15px;}"+lightColorMousePressed);
    }
}
