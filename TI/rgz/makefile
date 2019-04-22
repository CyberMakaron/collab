all: test_build test_run

test_build:
	g++ test.cpp code.cpp -o test.out 

test_run: test_build
	./test.out

build:
	g++ main.cpp code.cpp -o data_model.out

run: build
	./data_model.out