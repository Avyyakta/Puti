#-------------------------------------------------
#
# Project created by QtCreator 2015-02-28T17:46:27
#
#-------------------------------------------------

QT       += widgets declarative qml quick network opengl sql script scripttools xml xmlpatterns

greaterThan(QT_MAJOR_VERSION, 4): QT += printsupport

TARGET = kolyosa
TEMPLATE = lib

DEFINES += KOLYOSA_LIBRARY

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

	DESTDIR = $$exec_dir
}

unix {
	 target.path = /usr/lib
	 INSTALLS += target
}

SOURCES += kolyosa.cpp \
	 logger.cpp \
	 plugin_interface.cpp \
    epluginloader.cpp \
    mapplugins.cpp

HEADERS += kolyosa.h \
	 kolyosa_global.h \
	 logger.h \
	 plugin_interface.h \
    crtdobject.h \
    epluginloader.h \
    mapplugins.h
