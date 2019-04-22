#include <iostream>
#include "code.hpp"
using namespace std;

int main(){
    int n,m;
    cout<<"Размер алфавита- ";
    cin>>n;
    cout<<"Размер блока- ";
    cin>>m;
    Alphabet a(n);
    a.read();
    a.build_code_arr();
    a.print_codes();
    
    Alphabet b=a.build_nsized_Alphabet(m);
    b.build_code_arr();
    b.print_codes();
    string s("AAABBABB");
    vector<int> test=word_to_index_arr(b,s);
    cout<<endl;
    for(auto i=test.begin();i!=test.end();i++) cout<<*i<<" ";
    return 0;
}
