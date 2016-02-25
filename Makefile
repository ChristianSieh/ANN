# the compiler to use.
CC=g++
# Compiler Flags
CFLAGS=-c -Wall -std=c++11
# Linker Flags
LFLAGS=
all: ANNtrain ANNtest CrossValidate

ANNtrain: trainMain.o csvparse.o neuralnet.o perceptron.o weights.o prmFile.o
	$(CC) $(LFLAGS) trainMain.o csvparse.o neuralnet.o perceptron.o weights.o prmFile.o -o ANNtrain

ANNtest: testMain.o csvparse.o neuralnet.o perceptron.o weights.o prmFile.o
	$(CC) $(LFLAGS) testMain.o csvparse.o neuralnet.o perceptron.o weights.o prmFile.o -o ANNtest

CrossValidate: crossMain.o csvparse.o neuralnet.o perceptron.o weights.o prmFile.o
	$(CC) $(LFLAGS) crossMain.o csvparse.o neuralnet.o perceptron.o weights.o prmFile.o -o CrossValidate

trainMain.o: trainMain.cpp
	$(CC) $(CFLAGS) trainMain.cpp

testMain.o: testMain.cpp
	$(CC) $(CFLAGS) testMain.cpp

crossMain.o: crossMain.cpp
	$(CC) $(CFLAGS) crossMain.cpp

csvparse.o: csvparse.cpp csvparse.h
	$(CC) $(CFLAGS) csvparse.cpp csvparse.h

neuralnet.o: neuralnet.cpp neuralnet.h
	$(CC) $(CFLAGS) neuralnet.cpp neuralnet.h

perceptron.o: perceptron.cpp perceptron.h
	$(CC) $(CFLAGS) perceptron.cpp perceptron.h

weights.o: weights.cpp weights.h
	$(CC) $(CFLAGS) weights.cpp weights.h

prmFile.o: prmFile.cpp prmFile.h
	$(CC) $(CFLAGS) prmFile.cpp prmFile.h

clean:
	rm *.gch *o *~ *.wts ANNtrain ANNtest CrossValidate
