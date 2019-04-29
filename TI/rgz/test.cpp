#include <iostream>
#include "optimal_code.hpp"
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
    a.print_codes();
    Alphabet b=a.build_nsized_Alphabet(m);
    unsigned m_check = b.get_symbol_size();
    cout<< m<<" = "<<m_check<<endl;
    return 0;
}
