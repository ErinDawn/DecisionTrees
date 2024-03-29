main.exe	: main.o buildTree.o translate.o dataClasses.o functions.o helperFunctions.o
	g++ -O2 -std=c++11 -o main.exe main.o buildTree.o translate.o dataClasses.o functions.o helperFunctions.o -l gdi32 -static-libgcc -static-libstdc++
			
main.o	: main.cpp buildTree.h dataClasses.h functions.h helperFunctions.h
	g++ -O2 -std=c++11 -c -Wno-write-strings main.cpp

buildTree.o	: buildTree.cpp dataClasses.h functions.h helperFunctions.h
	g++ -O2 -std=c++11 -c -Wno-write-strings buildTree.cpp

translate.o	: translate.cpp dataClasses.h functions.h helperFunctions.h
	g++ -O2 -std=c++11 -c -Wno-write-strings translate.cpp

dataClasses.o	: dataClasses.cpp dataClasses.h functions.h helperFunctions.h
	g++ -O2 -std=c++11 -c -Wno-write-strings dataClasses.cpp functions.cpp helperFunctions.cpp

functions.o	: functions.cpp functions.h helperFunctions.h
	g++ -O2 -std=c++11 -c -Wno-write-strings functions.cpp helperFunctions.cpp

helperFunctions.o  : helperFunctions.cpp helperFunctions.h
	g++ -O2 -std=c++11 -c -Wno-write-strings helperFunctions.cpp
	
clean:
	del *.o
	del *.exe
	

