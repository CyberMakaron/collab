#include <iostream>
#include "saddlePoint.h"

using namespace std;

int main(){
	setlocale(0, "RUS");
	int m, n;
	cout << "Введите размеры  платежной матрицы:" << endl;
	cin >> m >> n;
	SaddlePoint a(m, n);
	a.inputCosts();
	a.getSaddlePoint();
	a.solveMixedStrats();
}

