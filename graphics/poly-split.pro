QT += core gui widgets

TARGET = poly-split
TEMPLATE = app

SOURCES += \
    main.cpp \
    ../src/poly/point.cpp \
    ../src/poly/vector.cpp \
    ../src/poly/line.cpp \
    ../src/poly/segment.cpp \
    ../src/poly/polygon.cpp \
    renderarea.cpp \
    mainwindow.cpp

HEADERS += \
        ../src/poly/point.hpp \
        ../src/poly/vector.hpp \
        ../src/poly/line.hpp \
        ../src/poly/polygon.hpp \
        renderarea.h \
        mainwindow.h

FORMS += mainwindow.ui
