# pro file for building the makefile for qwtplot3d
#


TARGET            = qwtplot3d
TEMPLATE          = lib
CONFIG           += qt warn_on opengl thread zlib
MOC_DIR           = tmp
OBJECTS_DIR       = tmp
INCLUDEPATH       = include
DEPENDPATH        = include src
DESTDIR      			= lib
#DESTDIR = ../../lib

win32:TEMPLATE    = vclib
win32:CONFIG     += dll 
win32:DEFINES    += QT_DLL QWT3D_DLL QWT3D_MAKEDLL
win32:QMAKE_CXXFLAGS     += $$QMAKE_CFLAGS_STL 

# Comment this out, if you have zlib on your windows system
# win32:CONFIG -= zlib

linux-g++:TMAKE_CXXFLAGS += -fno-exceptions

# Input
SOURCES += src/qwt3d_axis.cpp \
           src/qwt3d_color.cpp \
           src/qwt3d_coordsys.cpp \
           src/qwt3d_dataviews.cpp \
           src/qwt3d_dataviews_cell.cpp \
           src/qwt3d_dataviews_grid.cpp \
           src/qwt3d_drawable.cpp \
           src/qwt3d_function.cpp \
           src/qwt3d_label.cpp \
           src/qwt3d_mapping.cpp \
           src/qwt3d_mousekeyboard.cpp \
           src/qwt3d_movements.cpp \
           src/qwt3d_colorlegend.cpp \
           src/qwt3d_plot.cpp \
           src/qwt3d_reader.cpp \
           src/qwt3d_surfaceplot.cpp \
           src/qwt3d_types.cpp \
           src/qwt3d_enrichment.cpp \
           src/qwt3d_enrichment_std.cpp \
           src/qwt3d_autoscaler.cpp 

HEADERS += include/qwt3d_color.h \
           include/qwt3d_function.h \
           include/qwt3d_global.h \
           include/qwt3d_io.h \
           include/qwt3d_surfaceplot.h \
           include/qwt3d_types.h \
	         include/qwt3d_axis.h \
           include/qwt3d_coordsys.h \
           include/qwt3d_drawable.h \
           include/qwt3d_femreader.h \
           include/qwt3d_helper.h \
           include/qwt3d_label.h \
           include/qwt3d_openglhelper.h \
           include/qwt3d_colorlegend.h \
           include/qwt3d_plot.h \
           include/qwt3d_reader.h \
           include/qwt3d_enrichment.h \
           include/qwt3d_enrichment_std.h \
           include/qwt3d_autoscaler.h


# gl2ps support
HEADERS+=include/qwt3d_gl2ps.h \
         3rdparty/gl2ps/gl2ps.h
         
SOURCES+=src/qwt3d_gl2ps.cpp \
         3rdparty/gl2ps/gl2ps.c

# zlib support for gl2ps
zlib {
  DEFINES += GL2PS_HAVE_ZLIB
  win32:LIBS += zlib.lib
	unix:LIBS  += -lz
}