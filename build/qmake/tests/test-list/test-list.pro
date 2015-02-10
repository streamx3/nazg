TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

PRJ_ROOT = $$PWD/../../../../
SRC_DIR = $$PRJ_ROOT/tests/test-list/
OUT_PRFX = $$PRJ_ROOT/out/qmake/
release: OUT_DIR = $$OUT_PRFX/release/
debug:   OUT_DIR = $$OUT_PRFX/debug/

INCLUDEPATH += $$PRJ_ROOT/include/

SOURCES += $$SRC_DIR/*.c

HEADERS += $$SRC_DIR/*.h

DESTDIR = $$OUT_DIR/tests/
OBJECTS_DIR = $$DESTDIR/.obj

LIBS += -L $$OUT_DIR/lib/ -lnazg
