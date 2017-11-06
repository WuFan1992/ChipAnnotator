QT += core gui widgets

TARGET = ChamberAnnotater
TEMPLATE = app

CONFIG += c++14

OPENCV_PATH = C:/Users/admin/Documents/dev/VS2015-update3-Qt5.9.1/opencv-3.3.0/install
INCLUDEPATH += C:/Users/admin/Documents/dev/VS2015-update3-Qt5.9.1/boost_1_65_1 $$OPENCV_PATH/include

LIBS += -L$$OPENCV_PATH/x64/vc14/lib -lopencv_core330 -lopencv_imgproc330

SOURCES += main.cpp\
        mainwindow.cpp \
    imagetagger.cpp \
    classselector.cpp \
    classes.cpp \
    utils.cpp \
    contrastadjustmentbuttons.cpp \
    contrasteditor.cpp \
    annotatorscene.cpp \
    annotatorview.cpp

HEADERS  += mainwindow.hpp \
    imagetagger.hpp \
    classselector.hpp \
    classes.hpp \
    utils.hpp \
    contrastadjustmentbuttons.hpp \
    contrasteditor.hpp \
    annotatorscene.h \
    annotatorview.h

RESOURCES += \
    images.qrc
