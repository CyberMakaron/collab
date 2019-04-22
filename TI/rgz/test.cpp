#include <iostream>
#include "code.hpp"
#include <time.h>
using namespace std;

int main(){
    int n,m;
    cout<<"Размер алфавита- ";
    cin>>n;
    cout<<"Размер блока- ";
    cin>>m;
    Alphabet a(n);
    a.read();
    a.build_code_arr(0);
    a.print_codes();
    size_t begin=clock();
    Alphabet b=a.build_nsized_Alphabet(m);
    b.build_code_arr(0);
    b.print();
    size_t end=clock();
    cout<<"Complited in "<<end-begin/CLOCKS_PER_SEC<<endl;
    return 0;
}
