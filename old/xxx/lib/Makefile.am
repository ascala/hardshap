lib_LIBRARIES = libSE2d.a libWrapPlplot.a

libSE2d_a_SOURCES = gaussdev.c Circle.cpp se2d_overlap.cpp SEllipse.cpp Ellipse.cpp Rectangle.cpp Segment.cpp SphericalCap.cpp 

libWrapPlplot_a_SOURCES = wrap_plplot.cpp gaussdev.c Circle.cpp se2d_overlap.cpp SEllipse.cpp Ellipse.cpp Rectangle.cpp Segment.cpp SphericalCap.cpp 

include_HEADERS = ../include/vector2d.h ../include/vector2dPETE.h ../include/vector2dOperators.h
include_HEADERS += ../include/PETE/Combiners.h   ../include/PETE/Functors.h      ../include/PETE/Scalar.h
include_HEADERS += ../include/PETE/CreateLeaf.h  ../include/PETE/OperatorTags.h  ../include/PETE/TreeNodes.h
include_HEADERS += ../include/PETE/ForEach.h     ../include/PETE/PETE.h          ../include/PETE/TypeComputations.h

include_HEADERS += ../include/Circle.h ../include/Ellipse.h ../include/gaussdev.h 
include_HEADERS += ../include/LLcells2d.h ../include/Rectangle.h ../include/se2d.h 
include_HEADERS += ../include/se2d_overlap.h ../include/Segment.h ../include/SEllipse.h 
include_HEADERS += ../include/SphericalCap.h 

include_HEADERS += ../include/wrap_plplot.h

include_HEADERS += ../include/gsl_fmin.h 

AM_CPPFLAGS = $(all_includes) -I../include `pkg-config --cflags plplotd-c++`
AM_LDFLAGS = $(all_libraries)  `pkg-config --libs plplotd-c++`

