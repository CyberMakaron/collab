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
    b.build_code_arr(0);
    b.print_codes();
    return 0;
}
