TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    Color.cpp \
    Debug.cpp \
    Printable.cpp \
    Vector2.cpp \
    Vector3.cpp

include(deployment.pri)
qtcAddDeployment()

OTHER_FILES +=

HEADERS += \
    Color.h \
    Debug.h \
    Printable.h \
    Vector2.h \
    Vector3.h

