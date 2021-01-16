greaterThan(QT_MAJOR_VERSION, 4):
QT += core opengl
QT -= gui
QT += widgets

TARGET = keibomoneytracker
#CONFIG += console
CONFIG -= app_bundle
CONFIG += c++11

TEMPLATE = app

SOURCES += main.cpp \
    aboutdialog.cpp \
    accountstatsdialog.cpp \
    checkfaultytransactionsdialog.cpp \
    customcombobox.cpp \
    custompushbutton.cpp \
    customtextedit.cpp \
    donatedialog.cpp \
    gui_keibomoneytracker.cpp \
    keibomoneytracker.cpp \
    myopenglwidget.cpp \
    eraseconfirmation_dialog.cpp \
    managegroupsdialog.cpp \
    addgroupdialog.cpp \
    grouppiechartwidget.cpp \
    accountdialog.cpp \
    accountmanagerdialog.cpp \
    newelementsaddedautomaticallydialog.cpp \
    requestlanguagedialog.cpp \
    themecolorsdialog.cpp \
    selectcolordialog.cpp \
    transactiondialog.cpp \
    userguide.cpp \
    weeklyphrases.cpp

HEADERS += \
    aboutdialog.h \
    accountstatsdialog.h \
    checkfaultytransactionsdialog.h \
    customcombobox.h \
    custompushbutton.h \
    customtextedit.h \
    donatedialog.h \
    gui_keibomoneytracker.h \
    keibomoneytracker.h \
    myopenglwidget.h \
    eraseconfirmation_dialog.h \
    managegroupsdialog.h \
    addgroupdialog.h \
    grouppiechartwidget.h \
    accountdialog.h \
    accountmanagerdialog.h \
    newelementsaddedautomaticallydialog.h \
    requestlanguagedialog.h \
    themecolorsdialog.h \
    selectcolordialog.h \
    keibomoneytrackerinclude.h \
    transactiondialog.h \
    userguide.h \
    weeklyphrases.h

FORMS += \
    aboutdialog.ui \
    accountstatsdialog.ui \
    checkfaultytransactionsdialog.ui \
    donatedialog.ui \
    eraseconfirmation_dialog.ui \
    gui_keibomoneytracker.ui \
    managegroupsdialog.ui \
    addgroupdialog.ui \
    accountdialog.ui \
    accountmanagerdialog.ui \
    newelementsaddedautomaticallydialog.ui \
    requestlanguagedialog.ui \
    themecolorsdialog.ui \
    selectcolordialog.ui \
    transactiondialog.ui \
    userguide.ui


QMAKE_LFLAGS += -no-pie

unix {
    LIBS += -lGL
}

win32 {
    LIBS += -lopengl32
    DEFINES += USING_WINDOWS
}

RESOURCES += \
    resourceimages.qrc
