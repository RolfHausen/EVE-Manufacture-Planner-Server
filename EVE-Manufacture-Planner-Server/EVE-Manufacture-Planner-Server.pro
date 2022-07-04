QT += core gui
QT += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    abyssalmaterial.cpp \
    blueprint.cpp \
    commodity.cpp \
    dataloadworker.cpp \
    datamodel.cpp \
    dbmanager.cpp \
    factionmaterial.cpp \
    fuelblock.cpp \
    gas.cpp \
    globals.cpp \
    iceproduct.cpp \
    item.cpp \
    main.cpp \
    mainwindow.cpp \
    mineral.cpp \
    moongoo.cpp \
    namedcomponent.cpp \
    pidata.cpp \
    piproduct.cpp \
    planet.cpp \
    planetaryview.cpp \
    productionview.cpp \
    reactionmaterial.cpp \
    salvage.cpp \
    t1product.cpp \
    t2product.cpp \
    t3product.cpp

HEADERS += \
    abyssalmaterial.h \
    blueprint.h \
    commodity.h \
    dataloadworker.h \
    datamodel.h \
    dbmanager.h \
    factionmaterial.h \
    fuelblock.h \
    gas.h \
    globals.h \
    iceproduct.h \
    item.h \
    mainwindow.h \
    mineral.h \
    moongoo.h \
    namedcomponent.h \
    pidata.h \
    piproduct.h \
    planet.h \
    planetaryview.h \
    productionview.h \
    reactionmaterial.h \
    salvage.h \
    t1product.h \
    t2product.h \
    t3product.h

FORMS += \
    mainwindow.ui \
    productionview.ui

TRANSLATIONS += \
    EVE-Manufacture-Planner-Server_de_DE.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    pwd.txt

copydata.commands = $(COPY_FILE) \"$$shell_path($$PWD\\pwd.txt)\" \"$$shell_path($$OUT_PWD)\"
first.depends = $(first) copydata
export(first.depends)
export(copydata.commands)
QMAKE_EXTRA_TARGETS += first copydata
