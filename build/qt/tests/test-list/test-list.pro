TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

PRJ_ROOT = $$PWD/../../../../
TST_DIR = $$PRJ_ROOT/tests/test-list/

INCLUDEPATH += $$PRJ_ROOT/include/

SOURCES += $$TST_DIR/*.c

HEADERS += $$TST_DIR/*.h

CONFIG(release, debug|release) {
        LIBS += -L../../../build-nazg-Desktop-Release/libnazg/ -lnazg
} else {
        LIBS += -L../../../build-nazg-Desktop-Debug/libnazg/ -lnazg
}
