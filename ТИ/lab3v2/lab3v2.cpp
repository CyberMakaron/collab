/*					TODO
Реализовать алгоритм Хаффмана для генерации кодов 
Реализовать алгоритм декодирования decode(...)
Сверить и отладить блочное кодирование
Сменить название переменных в encode(...) на названия из decode(...)
Сменить названия переменных в symb
В averageLen(...) добавить возможность выбора, для какого кода будет вычисляться средняя длина
*/

#include "pch.h"
#include <iostream>
#include <cmath>
#include <string>
#include <list>

using namespace std;

struct symb {
	string s;		//символ
	double prob;	//вероятность
	int code[256];	//код
	int top;		//длина кода, сменить на len
	//int codeH[256]; Имеет смысл добавить еще одно поле codeHa(u)f, которое будет содержать код по Хаффману
	//int lenH;		//длина кода, полученная алгоритмом Хаффмана для генерации кодов
};

//Возвращает 1, если сумма вероятностей в массиве а равна 1
int checkProb(symb *a, int n) {
	double sum = 0;
	for (int i = 0; i < n; i++) {
		sum += a[i].prob;
	}
	if (sum == 1) {
		return 1;
	}
	else {
		return 0;
	}
}
//сортирует массив символов а по неубыванию вероятностей
void sortProb(symb* a, int n) {
	double min = a[0].prob;
	int minPos = 0, pos = 0;
	while (pos != n) {
		min = a[pos].prob;
		minPos = pos;
		for (int i = pos; i < n; i++) {
			if (a[i].prob < min) {
				min = a[i].prob;
				minPos = i;
			}
		}
		swap(a[pos], a[minPos]);
		pos++;
	}
}
//считывает символы и вероятности их появления в масссив а
symb* readAlphabet(int n) {
	symb * a = new symb[n];
	cout << "Введите символы и их вероятности" << endl;
	for (int i = 0; i < n; i++) {
		cin >> a[i].s >> a[i].prob;
		a[i].top = -1;
	}
	sortProb(a, n);
	return a;
	/*if (checkProb(a, n)) {
		sortProb(a, n);
		return a;
	}
	else {
		exit(1);
	}*/
}
//выводит массив а на экран. ДОБАВИТЬ ВОЗМОЖНОСТЬ ВЫВОДА КОДА ХАФФМАНА
void printAlphabet(symb *a, int n) {
	for (int i = n - 1; i >= 0; i--) {
		cout << a[i].s << " " << a[i].prob << " ";
		for (int k = 0; k <= a[i].top; k++) {
			cout << a[i].code[k];
		}
		cout << endl;
	}
}
//записывает в поле code код символа
void getCodes(int l, int h, symb s[]) {
	float pack1 = 0, pack2 = 0, diff1 = 0, diff2 = 0;
	int i, d, k, j;
	if ((l + 1) == h || l == h || l > h) {
		if (l == h || l > h)
			return;
		s[h].code[++(s[h].top)] = 0;
		s[l].code[++(s[l].top)] = 1;
		return;
	}
	else {
		for (i = l; i <= h - 1; i++)
			pack1 = pack1 + s[i].prob;
		pack2 = pack2 + s[h].prob;
		diff1 = pack1 - pack2;
		if (diff1 < 0)
			diff1 = diff1 * -1;
		j = 2;
		while (j != h - l + 1) {
			k = h - j;
			pack1 = pack2 = 0;
			for (i = l; i <= k; i++)
				pack1 = pack1 + s[i].prob;
			for (i = h; i > k; i--)
				pack2 = pack2 + s[i].prob;
			diff2 = pack1 - pack2;
			if (diff2 < 0)
				diff2 = diff2 * -1;
			if (diff2 >= diff1)
				break;
			diff1 = diff2;
			j++;
		}
		k++;
		for (i = l; i <= k; i++)
			s[i].code[++(s[i].top)] = 1;
		for (i = k + 1; i <= h; i++)
			s[i].code[++(s[i].top)] = 0;
		getCodes(l, k, s);
		getCodes(k + 1, h, s);
	}
}
//Реализовать! 
void getCodesH() {
	//list <>;
	return NULL;
}
//Записывает в массив res н-граммы, построенные на алфавите frs. src - массив, хранящий символы и вероятности н-1-грамма
void getNgramms(symb *src, int m, symb *frs, int l, symb *res, int n) {
	int k = 0, d = 0;
	for (int i = 0; i < n; i++) {
		if (k == l) {
			k = 0;
			d++;
		}
		res[i].s = src[d].s;
		res[i].prob = src[d].prob;
		k++;
	}
	k = 0;
	for (int i = 0; i < n; i++) {
		if (k == l) {
			k = 0;
		}
		res[i].s += frs[k].s;
		res[i].prob *= frs[k].prob;
		k++;
	}
}
//возвращает среднюю длину кодов, хранящихся в массиве а. Добавить возможность вычислять либо дл. кода Шеннона, либо Хаффмана
double averageLen(symb *a, int n) {
	double maxlen = 0;
	for (int i = 0; i < n; i++) {
		maxlen += a[i].prob * a[i].top;
	}
	return (maxlen + 1);
}
//Возвращает этропию алфавита источника а размером n.
double entropy(symb *a, int n) {
	double res = 0;
	for (int i = 0; i < n; i++) {
		res += a[i].prob * log2(a[i].prob);
	}
	return -res;
}
//возвращает строку, которая содержит закодированное сообщение str с помощью алфавита a, n - размер блока
string encode(string str, symb *a, int m, int n) {
	string result = " ", tmp = " ";						//содержит кодируемый блок
	int count, j = 0,  i = 0;							//содержит количество символов в последнем блоке, если блок не полный
	while (j != str.length()) {
		for (i = 0; i < n; i++) {
			if (i != str.length()) {					//во времменную строку записывается блок, который нужно закодировать
				tmp[i] = str[j + i];
			}
			else {
				exit(1);
				count = i;
			}
		}
		j += i;
		//поиск кода для блока tmp 
		for (int i = 0; i < m; i++) {
			string code;
			if (a[i].s == tmp) {
				for (int j = 0; j <= a[i].top; j++) {
					code += '0' + a[i].code[j];
				}
				result += code;
				i = m;
			}
		}
	}
	//cout << "result = " << result << endl;
	return result;
}
//Возвращает строку, которая содержит расшифрованное сообщение str с помощью алфавита a размером n
string decode(string str, symb *a, int n, int blockSize) {
	return NULL;
}

int main() {
	setlocale(LC_ALL, "Rus");
	int n;
	cout << "Введите количество символов" << endl;
	cin >> n;
	symb *a = readAlphabet(n);
	getCodes(0, n - 1, a);
	cout << "Полученный алфавит, вероятности и коды:" << endl;
	printAlphabet(a, n);
	cout << "Энтропия источника:" << entropy(a, n) << endl;
	cout << "Средняя длинна кода:" << averageLen(a, n) << endl;

	cout << "Введите строку, которую нужно закодировать" << endl;
	string src;
	cin >> src;
	string res = encode(src, a, n, 1);
	cout << "Результат кодирования строки: " << res;

	cout << "Хотите поблочное кодирование? (Я не умею спрашивать нормально) 0/1" << endl;
	///bool uzat`!!!!!!!!!!!!!!!!!!!!!!!!!!
	int mode;
	cin >> mode;
	if (mode) {
		int blockSize;
		cout << "Введите длину блоков" << endl;
		cin >> blockSize;
		if (blockSize > 4) {
			cout << "С данной длиной блока вычисление кодов будет длиться долго. Продолжить? 0/1" << endl;
			cin >> mode; 
			//if (mode == 0) exit(2);
			
			int prevn = n;
			symb *prev = new symb[prevn];
			prev = a;
			
			int curn = n;
			symb *cur;
			
			for (int i = 1; i < blockSize; i++) {
				//Получаем н-граммы. prev, prevn - массив и индекс н-1-грамма
				curn *= n;
				*curn = new symb[curn];
				getNgramms(prev, prevn, a, n, cur, curn);
				prevn *= n;
				*prev = new symb[prevn];
			}
			
			for (int i = 0; i < curn; i++) {
				cur[i].top = -1;
			}
			getCodes(0, curn - 1, cur);
			cout << "Полученные коды для " << blockSize << "-грамм: " << endl;
			printAlphabet(cur, curn);
			
			res = encode(src, cur, curn, blockSize);
			cout << "Результат кодирования строки: " << res << endl;
		}
	}
	
	
	/*cout << "Результат для биграмм, построенных на введенных данных:" << endl;
	int n2 = n * n;
	symb *a2 = new symb[n2];
	getNgramms(a, n, a, n, a2, n2);
	for (int i = 0; i <= n2; i++) {
		a2[i].top = -1;
	}
	getCodes(0, n2 - 1, a2);
	sortProb(a2, n2);
	cout << "Средняя длинна кода:" << averageLen(a2, n2)/2 << endl;
	printAlphabet(a2, n2);

	string s;
	cout << "Введите строку, которую необходимо закодировать" << endl;
	cin >> s;
	string res = makeCode(s, a, n, 1);
	string res1 = makeCode(s, a2, n2, 2);
	cout << res << endl << res1 << endl;*/
}
