main.exe	: main.o functions.o helperFunctions.o
	g++ -O2 -std=c++11 -o main.exe main.o functions.o helperFunctions.o -l gdi32 -static-libgcc -static-libstdc++
			
main.o	: main.cpp functions.h helperFunctions.h
	g++ -O2 -std=c++11 -c -Wno-write-strings main.cpp

dataClass.o	: dataClass.cpp dataClass.h
	g++ -O2 -std=c++11 -c -Wno-write-strings dataClass.cpp functions.o helperFunctions.o

dataFeatures.o	: dataFeatures.cpp dataFeatures.h
	g++ -O2 -std=c++11 -c -Wno-write-strings dataFeatures.cpp functions.o helperFunctions.o
	
functions.o	: functions.cpp functions.h
	g++ -O2 -std=c++11 -c -Wno-write-strings functions.cpp

helperFunctions.o  : helperFunctions.cpp helperFunctions.h
	g++ -O2 -std=c++11 -c -Wno-write-strings helperFunctions.cpp
	
clean:
	del *.o
	del *.exe
	
