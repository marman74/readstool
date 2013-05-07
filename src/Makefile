#Makefile clsReadsQC
#Version 0.1

CC       = gcc

readsqc: clsReadsQC.o clsErrMsg.o readsQC.o
	g++ -o ../bin/readsqc clsReadsQC.o clsErrMsg.o readsQC.o
clsReadsQC.o:	clsReadsQC.cpp clsReadsQC.h
	g++ -c -g clsReadsQC.cpp
clsErrMsg.o: clsErrMsg.cpp clsErrMsg.h
	g++ -c -g clsErrMsg.cpp
test_clsReadsQC.o: readsQC.cpp
	g++ -c -g readsQC.cpp

