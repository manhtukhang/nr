#-------------------------------------------------
#
# Project created by QtCreator 2014-12-21T09:36:13
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = number_recognition
TEMPLATE = app

# INCLUDEPATH += D:\Programs\opencv\binary\install\include
# LIBS += -L"D:\Programs\opencv\binary\install\x64\mingw\bin"

LIBS +=  -lopencv_core \
         -lopencv_objdetect \
         -lopencv_highgui \
         -lopencv_imgproc \
         -lopencv_features2d \
         -lopencv_calib3d \
         -lopencv_flann \
         -lopencv_contrib \
         -lopencv_legacy \
         -lopencv_nonfree


SOURCES += main.cpp\
        mainwindow.cpp \
    platefinder.cpp \
    recognise.cpp \
    detect.cpp

HEADERS  += mainwindow.h \
    platefinder.h \
    recognise.h \
    detect.h

FORMS    += mainwindow.ui
