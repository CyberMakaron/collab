all: test_build test_run

test_build:
	g++ src/test.cpp src/optimal_code.cpp -o build/test.out -O3 -g

test_run: test_build
	build/test.out

build:
	g++ src/main.cpp src/optimal_code.cpp -o build/data_model.out

run: build
	build/data_model.out