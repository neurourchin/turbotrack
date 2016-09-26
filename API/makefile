
CXX=x86_64-w64-mingw32-g++.exe
CXXFLAGS= -c -v -Wall -mwindows

MC_API_targetdir=bin
MC_API_sampledir=samples

#interprocess directories
IP_dir=InterProcess
IP_targetdir=$(IP_dir)/bin


all: $(MC_API_targetdir)/mc_api.dll samples interprocess
interprocess: $(IP_targetdir)/interprocess.o
samples: $(MC_API_targetdir)/mc_client.exe $(MC_API_targetdir)/mc_host.exe

#Make the wrapper API
mc_api_dll.o:  mc_api_dll.c mc_api_dll.h 
	$(CXX) $(CXXFLAGS) -DBUILDING_MC_API_DLL mc_api_dll.c 
	
	
#Make the actual DLL
$(MC_API_targetdir)/mc_api.dll: mc_api_dll.o $(IP_targetdir)/interprocess.o 
	$(CXX) -shared -o $(MC_API_targetdir)/mc_api.dll mc_api_dll.o $(IP_targetdir)/interprocess.o -Wl,--out-implib,mc_api.a  $(LinkerWinAPILibObj)
	
#Make the underlying interprocess routine
$(IP_targetdir)/interprocess.o: 
	cd $(IP_dir) && make clean && make all && cd ..



#Make the samples: host
$(MC_API_targetdir)/mc_host.exe: $(MC_API_targetdir)/mc_api.dll mc_host.o
	$(CXX) -o $(MC_API_targetdir)/mc_host.exe mc_host.o -L$(MC_API_targetdir) -lmc_api $(LinkerWinAPILibObj)
		

mc_host.o: $(MC_API_sampledir)/mc_host.c
	$(CXX) $(CXXFLAGS) $(MC_API_sampledir)/mc_host.c

#Make the samples: client	
$(MC_API_targetdir)/mc_client.exe: mc_client.o
	$(CXX) -o $(MC_API_targetdir)/mc_client.exe mc_client.o -L$(MC_API_targetdir) -lmc_api	$(LinkerWinAPILibObj)

mc_client.o: $(MC_API_sampledir)/mc_client.c
	$(CXX) $(CXXFLAGS) $(MC_API_sampledir)/mc_client.c
	



	
.PHONY: run
run:
	start $(MC_API_targetdir)/mc_host.exe
	$(MC_API_targetdir)/mc_client.exe
	
#	start $(IP_targetdir)/host.exe 
#	$(IP_targetdir)/client.exe
	
	
.PHONY: clean
clean:	
	rm -rfv *.o *.dll *.a 
	rm -rfv bin/*.dll bin/*.exe
	rm -fv $(IP_targetdir)/interprocess.o
