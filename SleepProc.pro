TARGET = SleepProc
QT       += core gui widgets
CONFIG   += c++11

INCLUDEPATH += \
        ./core \
        ./ui

SOURCES += \
        ./core/main.cpp \
        ./ui/main_window.cpp \
        ./ui/process_table_model.cpp \
        ./core/process.cpp

HEADERS += \
        ./ui/main_window.h \
        ./ui/process_table_model.h \
        ./core/process.h

FORMS += ./forms/main_window.ui
