
CXX=x86_64-w64-mingw32-g++.exe
CXXFLAGS= -c -v -Wall -mwindows

#This WIN API linker objects must go at the END of the linker command
LinkerWinAPILibObj= -lcomctl32 -lgdi32 -lole32 -lavifil32 -lavicap32 -lwinmm -lmsvfw32 -lkernel32 -luser32 -lgdi32 -lwinspool -lshell32 -lole32 -loleaut32 -luuid -lcomdlg32 -ladvapi32 -lsetupapi -lmingw32 -lsetupapi -static-libgcc -static-libstdc++

targetdir=bin
srcdir=src
smpldir=samples

all: $(targetdir)/interprocess.o $(targetdir)/client.exe $(targetdir)/host.exe
interprocess: $(targetdir)/interprocess.o



$(targetdir)/client.exe: $(targetdir)/interprocess.o client.o
	$(CXX) client.o $(targetdir)/interprocess.o -o $(targetdir)/client.exe $(LinkerWinAPILibObj)
	

client.o:$(smpldir)/client.c $(srcdir)/interprocess.h
	$(CXX) $(CXXFLAGS) $(smpldir)/client.c
	


$(targetdir)/host.exe: $(targetdir)/interprocess.o host.o
	$(CXX) host.o $(targetdir)/interprocess.o -o $(targetdir)/host.exe $(LinkerWinAPILibObj)
	

host.o:$(smpldir)/host.c $(srcdir)/interprocess.h
	$(CXX) $(CXXFLAGS) $(smpldir)/host.c 
	
$(targetdir)/interprocess.o: $(srcdir)/interprocess.h $(srcdir)/interprocess.c
	$(CXX) $(CXXFLAGS) $(srcdir)/interprocess.c -o $(targetdir)/interprocess.o




.PHONY: run
run:
	start $(targetdir)/host.exe 
	$(targetdir)/client.exe
	
	
.PHONY: clean
clean:	
	rm -rfv *.o 
	rm -rfv bin/*.exe bin/*.o
