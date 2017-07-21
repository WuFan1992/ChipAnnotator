QT += core gui widgets

TARGET = ChamberAnnotater
TEMPLATE = app

CONFIG += c++14

INCLUDEPATH += C:/prog/toolchain-VS2015-update3-Qt5.7/boost_1_62_0

SOURCES += main.cpp\
        mainwindow.cpp \
    imagetagger.cpp \
    classselector.cpp \
    classes.cpp \
    utils.cpp

HEADERS  += mainwindow.hpp \
    imagetagger.hpp \
    classselector.hpp \
    classes.hpp \
    utils.hpp

RESOURCES += \
    images.qrc
