bin_PROGRAMS = testvec2d testSe2d testWrapPlot testLLcells testOverlap testRectangle testSCap testSegment ExampleMonteCarlo

testvec2d_SOURCES = test_vec2d.cpp  
testSe2d_SOURCES = test_se2d.cpp
testWrapPlot_SOURCES = test_wrap_plplot.cpp
testLLcells_SOURCES = test_llcells.cpp
testOverlap_SOURCES = test_overlap.cpp
testRectangle_SOURCES = test_rectangle.cpp
testSCap_SOURCES = test_scap.cpp
testSegment_SOURCES = test_segment.cpp

AM_CPPFLAGS = $(all_includes) -I../include -I../include `pkg-config --cflags plplotd-c++`
AM_LDFLAGS = $(all_libraries) ../lib/libSE2d.a ../lib/libWrapPlplot.a `pkg-config --libs plplotd-c++`

ExampleMonteCarlo_SOURCES = EllipseMCwithPlPlot.cpp SimPar.cpp SimBox2d.cpp MCstep2d.cpp SimPar.h SimBox2d.h MCstep2d.h