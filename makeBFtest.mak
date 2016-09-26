# This is a stripped down makefile for the purposes of merely testing the BitFlow SDK on 
# 64 bit windows using the 32 bit mingw compiler.
# 
# I have had lots of problems linking to the BitFlow SDK on the new Win7 box
# so the goal is to make things as simple as possible.
#
# Note I am using BitFlow SDK 5.2 which is the same version I used to use successfully in 
# ARavi's lab in was on 32 bit WinXP



CXX = g++
CXXFLAGS= -c -v -Wall -mwindows 



#TailOpts =-pg # This generates output for a profiler such as gprof
TailOpts= -O2 #optimize the code	
LinkerWinAPILibObj= -lsetupapi -lmingw32

#Location of directories
MyLibs=MyLibs
3rdPartyLibs=3rdPartyLibs
bfIncDir=$(3rdPartyLibs)/BitFlowSDK
targetDir=bin



# objects that I have written, in order of dependency. 
# e.g. Objects that depend on nothing go left.
	#Objects that depend on other objects go right.

mylibraries=  Talk2FrameGrabber.o 


#3rd party statically linked objects

##BitFlow SDK
BFLibDir = C:/BitFlow\ SDK\ 5.20/Lib
BFObj = $(BFLibDir)/BFD.lib   $(BFLibDir)/BFDiskIO.lib $(BFLibDir)/BFDrv.lib $(BFLibDir)/BFEr.lib $(BFLibDir)/BFOS.lib $(BFLibDir)/BFS.lib $(BFLibDir)/Bid.lib $(BFLibDir)/BufferInterface.lib $(BFLibDir)/Cid.lib  $(BFLibDir)/R2Cam.lib $(BFLibDir)/R2D.lib $(BFLibDir)/R64D.lib $(BFLibDir)/RvD.lib $(BFLibDir)/clallserial.lib $(BFLibDir)/clserbit.lib $(BFLibDir)/DispSurf.lib

testFG :  $(targetDir)/FGtest.exe 

# Linker
$(targetDir)/FGtest.exe : FGtest.o Talk2FrameGrabber.o $(BFobj) 
	$(CXX) -o $(targetDir)/FGtest.exe FGtest.o  Talk2FrameGrabber.o  $(BFObj)
#	$(CXX) -o $(targetDir)/FGtest.exe FGtest.o Talk2FrameGrabber.o $(BFObj) $(LinkerWinAPILibObj) $(TailOpts) 

	
# Compiler

FGtest.o : $(MyLibs)/Talk2FrameGrabber.h FGtest.cpp
	$(CXX) $(CXXFLAGS) FGtest.cpp -I$(MyLibs) -I$(bfIncDir)

Talk2FrameGrabber.o: $(MyLibs)/Talk2FrameGrabber.cpp $(MyLibs)/Talk2FrameGrabber.h
	$(CXX) $(CXXFLAGS) $(MyLibs)/Talk2FrameGrabber.cpp -I$(bfIncDir)
	

.PHONY: clean run
clean:
	rm -rfv *.o


