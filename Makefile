CXX = cl.exe
CFLAGS = /EHsc /O2
LFLAGS =

driver.exe: main.obj graphs.obj
	$(CXX) /Fe$@ main.obj graphs.obj $(LFLAGS)

graphs.obj: graphs.cpp graphs.hpp
	$(CXX) /c graphs.cpp $(CFLAGS)

main.obj: main.cpp graphs.hpp
	$(CXX) /c main.cpp $(CFLAGS)

.PHONY : clean
clean:
	del *.exe *.obj
