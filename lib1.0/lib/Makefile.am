lib_LIBRARIES = libSE2d.a libWrapPlplot.a

libSE2d_a_SOURCES = gaussdev.c Circle.cpp se2d_overlap.cpp SEllipse.cpp Ellipse.cpp Rectangle.cpp Segment.cpp SphericalCap.cpp 

libWrapPlplot_a_SOURCES = wrap_plplot.cpp gaussdev.c Circle.cpp se2d_overlap.cpp SEllipse.cpp Ellipse.cpp Rectangle.cpp Segment.cpp SphericalCap.cpp 

include_HEADERS = ../include/vector2d.h ../include/Circle.h ../include/Ellipse.h ../include/gaussdev.h ../include/gsl_fmin.h ../include/LLcells2d.h ../include/Rectangle.h ../include/se2d.h ../include/se2d_overlap.h ../include/Segment.h ../include/SEllipse.h ../include/SphericalCap.h 
include_HEADERS += ../include/wrap_plplot.h

AM_CPPFLAGS = $(all_includes) -I../include `pkg-config --cflags plplotd-c++`
AM_LDFLAGS = $(all_libraries)  `pkg-config --libs plplotd-c++`

