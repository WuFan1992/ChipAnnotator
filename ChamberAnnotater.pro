QT += core gui widgets

TARGET = ChamberAnnotater
TEMPLATE = app

CONFIG += c++14

OPENCV_PATH = C:/prog/VS2015-update3-Qt5.7/opencv-3.1.0/install
INCLUDEPATH += C:/prog/VS2015-update3-Qt5.7/boost_1_62_0 $$OPENCV_PATH/include

LIBS += -L$$OPENCV_PATH/x64/vc14/lib -lopencv_core310 -lopencv_imgproc310

SOURCES += main.cpp\
        mainwindow.cpp \
    imagetagger.cpp \
    classselector.cpp \
    classes.cpp \
    utils.cpp \
    contrastadjustmentbuttons.cpp \
    contrasteditor.cpp

HEADERS  += mainwindow.hpp \
    imagetagger.hpp \
    classselector.hpp \
    classes.hpp \
    utils.hpp \
    contrastadjustmentbuttons.hpp \
    contrasteditor.hpp

RESOURCES += \
    images.qrc
