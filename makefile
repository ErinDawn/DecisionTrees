main.exe	: main.o dataClasses.o functions.o helperFunctions.o
	g++ -O2 -std=c++11 -o main.exe main.o dataClasses.o functions.o helperFunctions.o -l gdi32 -static-libgcc -static-libstdc++
			
main.o	: main.cpp dataClasses.h functions.h helperFunctions.h
	g++ -O2 -std=c++11 -c -Wno-write-strings main.cpp

dataClasses.o	: dataClasses.cpp dataClasses.h functions.h helperFunctions.h
	g++ -O2 -std=c++11 -c -Wno-write-strings dataClasses.cpp functions.o helperFunctions.o

functions.o	: functions.cpp functions.h helperFunctions.h
	g++ -O2 -std=c++11 -c -Wno-write-strings functions.cpp helperFunctions.o

helperFunctions.o  : helperFunctions.cpp helperFunctions.h
	g++ -O2 -std=c++11 -c -Wno-write-strings helperFunctions.cpp
	
clean:
	del *.o
	del *.exe
	

