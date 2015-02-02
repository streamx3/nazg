TEMPLATE = subdirs

SUBDIRS += \
    tests \
    nazg

tests.depends = nazg
