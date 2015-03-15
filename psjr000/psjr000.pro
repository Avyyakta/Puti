#-------------------------------------------------
#
# Project created by QtCreator 2015-03-02T14:35:21
#
#-------------------------------------------------

QT       += core script declarative qml quick network sql script scripttools xml xmlpatterns

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = psjr000
TEMPLATE = lib
CONFIG += plugin

UTILS_LIB = kolyosa
UTILS_DIR = ../kolyosa

CONFIG(debug, debug|release) {
	TARGET = $$qtLibraryTarget($$TARGET )
	DEFINES += IS_DEBUG
} else {
	TARGET = $$qtLibraryTarget($$TARGET )
	DEFINES -= IS_DEBUG
}

windows {
	exec_dir = ../../bin
	database_dir = ../../db
	plugins_dir = ../../plugins
	translate_dir = ../../translates

	pretarget.path = $$exec_dir
	pretarget.commands = -$${QMAKE_MKDIR} $$exec_dir
	predata.path = $$database_dir
	predata.commands = -$${QMAKE_MKDIR} $$database_dir
	preplugins.path = $$database_dir
	preplugins.commands = -$${QMAKE_MKDIR} $$plugins_dir
	pretrnsl.path = $$translate_dir
	pretrnsl.commands = -$${QMAKE_MKDIR} $$translate_dir
	QMAKE_EXTRA_TARGETS += pretarget predata preplugins pretrnsl
	PRE_TARGETDEPS += pretarget predata preplugins pretrnsl

	DESTDIR = $$plugins_dir

	LIBS += -L$$exec_dir -ladvapi32
}

unix {
	 target.path = /usr/lib
	 INSTALLS += target
}

LIBS +=  -l$$qtLibraryTarget($$UTILS_LIB )

INCLUDEPATH += $$UTILS_DIR

SOURCES += scriptextensionplugin.cpp \
    frmvseuslugi.cpp \
    proba.cpp \
    dlgsetup.cpp \
    frmmainsetup.cpp

HEADERS += scriptextensionplugin.h \
    frmvseuslugi.h \
    proba.h \
    dlgsetup.h \
    frmmainsetup.h

DISTFILES += psjr000.json

FORMS += \
    frmvseuslugi.ui \
    dlgsetup.ui \
    frmmainsetup.ui

RESOURCES += \
    resources.qrc
