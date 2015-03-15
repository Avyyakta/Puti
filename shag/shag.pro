#-------------------------------------------------
#
# Project created by QtCreator 2015-02-28T18:03:27
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = shag
TEMPLATE = app

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

	LIBS +=  -L$$exec_dir

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

	DESTDIR = $$exec_dir
}

LIBS +=  -l$$qtLibraryTarget($$UTILS_LIB ) -ladvapi32
INCLUDEPATH += $$UTILS_DIR

SOURCES += main.cpp\
		  mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

RESOURCES += \
    resources.qrc
