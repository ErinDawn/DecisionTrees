main.exe	: main.o dataInfo.o functions.o helperFunctions.o
	g++ -O2 -std=c++11 -o main.exe main.o dataInfo.o functions.o helperFunctions.o -l gdi32 -static-libgcc -static-libstdc++
			
main.o	: main.cpp dataInfo.h functions.h helperFunctions.h
	g++ -O2 -std=c++11 -c -Wno-write-strings main.cpp

dataInfo.o	: dataInfo.cpp dataInfo.h functions.h helperFunctions.h
	g++ -O2 -std=c++11 -c -Wno-write-strings dataInfo.cpp functions.o helperFunctions.o

functions.o	: functions.cpp functions.h helperFunctions.h
	g++ -O2 -std=c++11 -c -Wno-write-strings functions.cpp helperFunctions.o

helperFunctions.o  : helperFunctions.cpp helperFunctions.h
	g++ -O2 -std=c++11 -c -Wno-write-strings helperFunctions.cpp
	
clean:
	del *.o
	del *.exe
	
