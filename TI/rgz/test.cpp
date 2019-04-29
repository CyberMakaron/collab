#include <iostream>
#include "optimal_code.hpp"
#include <time.h>
using namespace std;

int main(){
    int n,m;
    string str,code;
    cout<<"Размер алфавита - ";
    cin>>n;
    cout<<"Размер блока - ";
    cin>>m;
    Alphabet a(n);
    a.read();
    Alphabet b=a.build_nsized_Alphabet(m);
    cout<<"Введите слово для кодирования - ";
    cin>>str;
    code=b.encode_text(str);
    cout<<"result code - "<<code;
    return 0;
}
