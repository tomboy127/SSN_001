QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    axon.cpp \
    cell.cpp \
    input.cpp \
    main.cpp \
    mainwindow.cpp \
    neuron.cpp \
    output.cpp \
    random.cpp

HEADERS += \
    axon.h \
    cell.h \
    config.h \
    input.h \
    mainwindow.h \
    neuron.h \
    output.h \
    random.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
