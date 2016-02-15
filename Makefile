# the compiler to use.
CC=g++
# Compiler Flages
CFLAGS=-c -Wall -std=c++11

ANNtrain: trainMain.o csvparse.o neuralnet.o perceptron.o weights.o
	$(CC) $(CFLAGS) trainmain.o csvparse.o neuralnet.o perceptron.o weights.o -o ANNtrain

ANNtest: testMain.o csvparse.o neuralnet.o perceptron.o weights.o
	$(CC) $(CFLAGS) trainmain.o csvparse.o neuralnet.o perceptron.o weights.o -o ANNtest

CrossValidate: crossMain.o csvparse.o neuralnet.o perceptron.o weights.o
	$(CC) $(CFLAGS) trainmain.o csvparse.o neuralnet.o perceptron.o weights.o -o CrossValidate

csvparse.o: csvparse.cpp csvparse.h
	$(CC) $(CFLAGS) csvparse.cpp csvparse.h

neuralnet.o: neuralnet.cpp neuralnet.h
	$(CC) $(CFLAGS) neuralnet.cpp neuralnet.h

perceptron.o: perceptron.cpp perceptron.h
	$(CC) $(CFLAGS) perceptron.cpp perceptron.h

Weights.o: weights.cpp weights.h
	$(CC) $(CFLAGS) weights.cpp weights.h


clean:
	rm *o *~ ANNtrain ANNtest CrossValidate
