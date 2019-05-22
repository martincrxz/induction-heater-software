#-------------------------------------------------
#
# Project created by QtCreator 2019-05-22T16:36:19
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = hornoV3
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        src/main.cpp \
        src/view/equipment_status_view.cpp \
        src/view/general_view.cpp \
        src/view/automatic_control_tab_view.cpp \
        src/view/manual_power_control_view.cpp \
    src/view/auto_tunning_tab_view.cpp

HEADERS += \
    src/view/equipment_status_view.h \
    src/view/general_view.h \
    src/view/automatic_control_tab_view.h \
    src/view/manual_power_control_view.h \
    src/view/auto_tunning_tab_view.h

FORMS += \
    src/view/equipment_status_view.ui \
    src/view/general_view.ui \
    src/view/automatic_control_tab_view.ui \
    src/view/manual_power_control_view.ui \
    src/view/auto_tunning_tab_view.ui
