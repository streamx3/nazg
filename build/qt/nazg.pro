TEMPLATE = subdirs

SUBDIRS += \
    tests \
    libnazg

tests.depends = libnazg

debug {
  message(qmaking debug)
}
release {
  message(qmaking release)
}
