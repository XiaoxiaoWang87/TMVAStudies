LIBS = `root-config --glibs` -L/usr/X11R6/lib -lTMVA -L/usr/lib64/lib -lm -ldl -lstdc++
#LIBS = `root-config --glibs` -L/usr/X11R6/lib -lTMVA -lm -ldl -lstdc++ -lMinuit -lXMLIO -lMLP -lTreePlayer
#LIBS = -L/usr/X11R6/lib -lm -ldl -lstdc++
TOOL = -I../1LStopBoosted
PACKAGES = $(TOOL) $(TOOL)/readparameters 
#OPTCOMP =  +K0
#CXXFLAGS = -O3 -Wall --exceptions -I$(ROOTSYS)/include -I../1LStopBoosted/readparameters -I  

CXXFLAGS = -O3 -Wall --exceptions -I$(ROOTSYS)/include $(PACKAGES) 
# -pg -ggdb
#OBJECTS = Train.o CrossSections.o PlottingTools.o HtmlConfig.o HistoHandler.o readparameters.o selection.o
OBJECTS = Train.o CrossSections.o PlottingTools.o HtmlConfig.o HistoHandler.o readparameters.o selection.o selection_fatjets.o

all: $(OBJECTS)
	gcc $(OPTCOMP) $(CXXFLAGS) $(LIBS) -o train -g $(OBJECTS) 

selection.o: ../Root/selection.cxx ../1LStopBoosted/selection.h
	gcc $(OPTCOMP) $(CXXFLAGS) -c ../Root/selection.cxx

selection_fatjets.o: ../Root/selection_fatjets.cxx ../1LStopBoosted/selection_fatjets.h
	gcc $(OPTCOMP) $(CXXFLAGS) -c ../Root/selection_fatjets.cxx

readparameters.o: ../Root/readparameters.cxx ../1LStopBoosted/readparameters.h
	gcc $(OPTOMP) $(CXXFLAGS) -c ../Root/readparameters.cxx

HistoHandler.o: ../Root/HistoHandler.cxx ../1LStopBoosted/HistoHandler.h
	gcc $(OPTCOMP) $(CXXFLAGS) -c ../Root/HistoHandler.cxx

HtmlConfig.o: ../Root/HtmlConfig.cxx ../1LStopBoosted/HtmlConfig.h
	gcc $(OPTCOMP) ${CXXFLAGS} -c ../Root/HtmlConfig.cxx

PlottingTools.o: ../Root/PlottingTools.cxx ../1LStopBoosted/PlottingTools.h 
	gcc $(OTPCOMP) ${CXXFLAGS} -c ../Root/PlottingTools.cxx

CrossSections.o: ../Root/CrossSections.cxx ../1LStopBoosted/CrossSections.h
	gcc $(OPTCOMP) ${CXXFLAGS} -c ../Root/CrossSections.cxx

Train.o: Train.cxx Train.h ../1LStopBoosted/CrossSections.h ../Root/CrossSections.cxx 
	gcc $(OPTCOMP) ${CXXFLAGS} -c Train.cxx


clean:
	rm -f Train.o
	rm -f train
	rm -rf ti_files
	rm -f *~;
	rm -f *.o;
