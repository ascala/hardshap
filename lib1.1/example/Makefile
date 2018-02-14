CFLAGS = -g -O2
#CFLAGS = -O2 --static
CC = gcc $(CFLAGS)

CXXFLAGS = -g -O2
#CXXFLAGS = -O2 --static
CXX = g++ $(CXXFLAGS)


#SE2D_DIR = /home/scala/hardshap/trunk/lib1.1
SE2D_DIR = ..

INC_SE2D = -I./ -I$(SE2D_DIR)/include 


SE2D_SUBS  = $(SE2D_DIR)/lib/Circle.cpp     $(SE2D_DIR)/lib/se2d_overlap.cpp  $(SE2D_DIR)/lib/SphericalCap.cpp
SE2D_SUBS += $(SE2D_DIR)/lib/Ellipse.cpp    $(SE2D_DIR)/lib/Segment.cpp       
SE2D_SUBS += $(SE2D_DIR)/lib/Rectangle.cpp  $(SE2D_DIR)/lib/SEllipse.cpp

MC_SOURCES =  $(SE2D_SUBS) SimPar.cpp SimBox2d.cpp MCstep2d.cpp Histogram.cpp

INC_PLOT = $(INC_SE2D) `pkg-config --libs --cflags plplotd-c++`
PLOT_SOURCES = $(MC_SOURCES) $(SE2D_DIR)/lib/wrap_plplot.cpp

all: StartMonteCarlo MonteCarlo

clean:
	rm -f *.x *.o *~

StartMonteCarlo: 
	$(CXX) StartMC.cpp $(MC_SOURCES) $(INC_SE2D) -D_CIRCLE -o StartMC_CIRCLE.x
	$(CXX) StartMC.cpp $(MC_SOURCES) $(INC_SE2D) -D_SELLIPSE -o StartMC_SELLIPSE.x
	$(CXX) StartMC.cpp $(MC_SOURCES) $(INC_SE2D) -D_RECTANGLE -o StartMC_RECTANGLE.x

MonteCarlo: 
	$(CXX) MC.cpp $(MC_SOURCES) $(INC_SE2D) -D_CIRCLE -o MC_CIRCLE.x
	$(CXX) MC.cpp $(MC_SOURCES) $(INC_SE2D) -D_SELLIPSE -o MC_SELLIPSE.x
	$(CXX) MC.cpp $(MC_SOURCES) $(INC_SE2D) -D_RECTANGLE -o MC_RECTANGLE.x

plview:
	$(CXX) plview.cpp $(PLOT_SOURCES) $(INC_PLOT) -D_CIRCLE -o plCIRCLE.x
	$(CXX) plview.cpp $(PLOT_SOURCES) $(INC_PLOT) -D_SELLIPSE -o plSELLIPSE.x
	$(CXX) plview.cpp $(PLOT_SOURCES) $(INC_PLOT) -D_RECTANGLE -o plRECTANGLE.x
