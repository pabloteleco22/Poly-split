QT += core gui widgets

TARGET = poly-split
TEMPLATE = app

SOURCES += \
    main.cpp \
    ../lib/poly/point.cpp \
    ../lib/poly/vector.cpp \
    ../lib/poly/line.cpp \
    ../lib/poly/segment.cpp \
    ../lib/poly/polygon.cpp \
    renderarea.cpp \
    mainwindow.cpp

HEADERS += \
        ../lib/poly/point.hpp \
        ../lib/poly/vector.hpp \
        ../lib/poly/line.hpp \
        ../lib/poly/polygon.hpp \
        renderarea.h \
        mainwindow.h

FORMS += mainwindow.ui
