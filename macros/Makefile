LIBS = `root-config --glibs` -L/usr/X11R6/lib -lm -ldl -lstdc++
#LIBS = -L/usr/X11R6/lib -lm -ldl -lstdc++
TOOL = -I../BoostedStop
PACKAGES = $(TOOL) $(TOOL)/readparameters 
#OPTCOMP =  +K0
#CXXFLAGS = -O3 -Wall --exceptions -I$(ROOTSYS)/include -I../BoostedStop/readparameters -I  

CXXFLAGS = -O3 -Wall --exceptions -I$(ROOTSYS)/include $(PACKAGES) 
# -pg -ggdb
OBJECTS = Plot.o PlottingTools.o HtmlConfig.o readparameters.o HistoHandler.o

all: $(OBJECTS)
	gcc $(OPTCOMP) $(CXXFLAGS) $(LIBS) -o makePlot -g $(OBJECTS) 

	
readparameters.o: ../../Root/readparameters.cxx ../../BoostedStop/readparameters.h
	gcc $(OPTOMP) $(CXXFLAGS) -c ../../Root/readparameters.cxx

HistoHandler.o: ../../Root/HistoHandler.cxx ../../BoostedStop/HistoHandler.h 
	gcc $(OTPCOMP) ${CXXFLAGS} -c ../../Root/HistoHandler.cxx


HtmlConfig.o: ../../Root/HtmlConfig.cxx ../../BoostedStop/HtmlConfig.h
	gcc $(OPTCOMP) ${CXXFLAGS} -c ../../Root/HtmlConfig.cxx

PlottingTools.o: ../../Root/PlottingTools.cxx ../../BoostedStop/PlottingTools.h 
	gcc $(OTPCOMP) ${CXXFLAGS} -c ../../Root/PlottingTools.cxx



Plot.o: Plot.cxx Plot.h
	gcc $(OPTCOMP) ${CXXFLAGS} -c Plot.cxx


clean:
	rm -f Plot.o
	rm -f makePlot
	rm -rf ti_files
	rm -f *~;
	rm -f *.o;
