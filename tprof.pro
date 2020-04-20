#-------------------------------------------------
#
# Project created by QtCreator 2019-11-09T22:24:47
#
#-------------------------------------------------

QT       += core gui charts serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = horno-induccion
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

INCLUDEPATH += libs

SOURCES += \
        libs/logger/message/logger_debug.cpp \
        libs/logger/message/logger_info.cpp \
        libs/logger/message/logger_message.cpp \
        libs/logger/message/logger_quit.cpp \
        libs/logger/message/logger_warning.cpp \
        libs/logger/logger.cpp \
        libs/logger/logger_worker.cpp \
        libs/chrono.cpp \
        libs/exception.cpp \
        src/connection/protocol/automatic_control_acknowledge.cpp \
        src/connection/protocol/cold_junction_reading.cpp \
        src/connection/protocol/incoming_message.cpp \
        src/connection/protocol/manual_control_acknowledge.cpp \
        src/connection/protocol/micro_message.cpp \
        src/connection/protocol/outgoing_message.cpp \
        src/connection/protocol/power_set_acknowledge.cpp \
        src/connection/protocol/protocol.cpp \
        src/connection/protocol/set_automatic_control.cpp \
        src/connection/protocol/set_manual_control.cpp \
        src/connection/protocol/set_power.cpp \
        src/connection/protocol/shutdown_ack.cpp \
        src/connection/protocol/shutdown_message.cpp \
        src/connection/protocol/temperature_reading.cpp \
        src/connection/protocol/thermocouple_configuration.cpp \
        src/connection/protocol/thermocouple_configuration_acknowledge.cpp \
        src/connection/protocol/thermocouple_fault.cpp \
        src/connection/serialport.cpp \
        src/view/application.cpp \
        src/view/auto_tunning_tab_view.cpp \
        src/view/automatic_control_tab_view.cpp \
        src/view/chart_tab_view.cpp \
        src/view/equipment_status_view.cpp \
        src/view/general_view.cpp \
        src/view/manual_power_control_view.cpp \
        src/main.cpp \
    src/view/control_configuration/classic_control_view.cpp \
    src/view/control_configuration/fuzzy_control_view.cpp \
    src/view/control_configuration/from_file_control_view.cpp \
    src/view/control_configuration/control_configuration.cpp \
    src/control/control_algorithm.cpp \
    src/control/classic_pid.cpp \
    libs/logger/message/logger_critical.cpp \
    src/control/file_control.cpp \
    src/control/zieglers_nichols.cpp \
    src/view/chart/chart_widget.cpp \
    src/view/chart/chart.cpp \
    src/view/chart/chart_conf.cpp \
    src/view/chart/chart_view.cpp



HEADERS += \
        libs/logger/message/logger_debug.h \
        libs/logger/message/logger_info.h \
        libs/logger/message/logger_message.h \
        libs/logger/message/logger_quit.h \
        libs/logger/message/logger_warning.h \
        libs/logger/logger.h \
        libs/logger/logger_worker.h \
        libs/chrono.h \
        libs/exception.h \
        libs/stream.h \
        src/connection/protocol/automatic_control_acknowledge.h \
        src/connection/protocol/cold_junction_reading.h \
        src/connection/protocol/incoming_message.h \
        src/connection/protocol/manual_control_acknowledge.h \
        src/connection/protocol/micro_message.h \
        src/connection/protocol/outgoing_message.h \
        src/connection/protocol/power_set_acknowledge.h \
        src/connection/protocol/protocol.h \
        src/connection/protocol/set_automatic_control.h \
        src/connection/protocol/set_manual_control.h \
        src/connection/protocol/set_power.h \
        src/connection/protocol/shutdown_ack.h \
        src/connection/protocol/shutdown_message.h \
        src/connection/protocol/temperature_reading.h \
        src/connection/protocol/thermocouple_configuration.h \
        src/connection/protocol/thermocouple_configuration_acknowledge.h \
        src/connection/protocol/thermocouple_fault.h \
        src/connection/serialport.h \
        src/view/application.h \
        src/view/auto_tunning_tab_view.h \
        src/view/automatic_control_tab_view.h \
        src/view/equipment_status_view.h \
        src/view/general_view.h \
        src/view/manual_power_control_view.h \
        libs/stream.h \
    src/view/control_configuration/classic_control_view.h \
    src/view/control_configuration/fuzzy_control_view.h \
    src/view/control_configuration/control_configuration.h \
    src/view/control_configuration/from_file_control_view.h \
    src/control/control_algorithm.h \
    src/control/classic_pid.h \
    libs/logger/message/logger_critical.h \
    src/control/file_control.h \
    src/control/zieglers_nichols.h \
    src/view/chart_tab_view.h \
    src/view/chart/chart_widget.h \
    src/view/chart/chart.h \
    src/view/chart/chart_conf.h \
    src/view/chart/chart_view.h

FORMS += \
		src/view/auto_tunning_tab_view.ui \
		src/view/automatic_control_tab_view.ui \
		src/view/chart_tab_view.ui \
		src/view/equipment_status_view.ui \
		src/view/general_view.ui \
                src/view/manual_power_control_view.ui \
    src/view/control_configuration/classic_control_view.ui \
    src/view/control_configuration/fuzzy_control_view.ui \
    src/view/control_configuration/from_file_control_view.ui \ 
    src/view/chart/chart_widget.ui

RESOURCES = assets/resources.qrc
