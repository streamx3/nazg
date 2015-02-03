TARGET = nazg
TEMPLATE = lib
CONFIG -= qt

PRJ_ROOT = $$PWD/../../../
SRC_DIR = $$PRJ_ROOT/src/
HDR_DIR = $$PRJ_ROOT/include/
OUT_PRFX = $$PRJ_ROOT/out/qt/
release: OUT_DIR = $$OUT_PRFX/release/
debug:   OUT_DIR = $$OUT_PRFX/debug/

INCLUDEPATH += $$HDR_DIR

SOURCES += \
    $$SRC_DIR/nz_error.c \
    $$SRC_DIR/nz_list.c

HEADERS += \
    $$HDR_DIR/nazg.h \
    $$HDR_DIR/nz_assert.h \
    $$HDR_DIR/nz_common.h \
    $$HDR_DIR/nz_error.h \
    $$HDR_DIR/nz_int.h \
    $$HDR_DIR/nz_levels.h \
    $$HDR_DIR/nz_list.h \
    $$HDR_DIR/nz_memory.h \
    $$HDR_DIR/nz_space.h

DESTDIR = $$OUT_DIR/libnazg/
OBJECTS_DIR = $$DESTDIR/.obj
