all: test_build test_run

test_build:
	g++ test.cpp optimal_code.cpp -o test.out -O3

test_run: test_build
	./test.out

build:
	g++ main.cpp optimal_code.cpp -o data_model.out

run: build
	./data_model.out