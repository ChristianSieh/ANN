# the compiler to use.
CC=g++
# Compiler Flages
CFLAGS=-c -Wall -std=c++11

all: ANNtrain ANNtest CrossValidate

ANNtrain: trainMain.o csvparse.o neuralnet.o perceptron.o weights.o prmFile.o
	$(CC)  trainMain.o csvparse.o neuralnet.o perceptron.o weights.o prmFile.o -o ANNtrain

ANNtest: testMain.o csvparse.o neuralnet.o perceptron.o weights.o prmFile.o
	$(CC)  testMain.o csvparse.o neuralnet.o perceptron.o weights.o prmFile.o -o ANNtest

CrossValidate: crossMain.o csvparse.o neuralnet.o perceptron.o weights.o prmFile.o
	$(CC)  crossMain.o csvparse.o neuralnet.o perceptron.o weights.o prmFile.o -o CrossValidate

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
	rm *.gch *o *~ ANNtrain ANNtest CrossValidate
