TEMPLATE = subdirs

SUBDIRS += \
    tests \
    libnazg

tests.depends = libnazg
