#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <algorithm>
#include <bitset>

using namespace std;


//Cимвол алфавита. symb - сам символ, prob - вероятность появления.
class Symbol{
    //Непосредственно символ.
    string symb;
    //Вероятность появления символа.
    double prob;
    //Оптимальный код для элемента алфавита.
    string code;
    //true - код построен, false - код не построен.
    //Позиция символа в алфавите
    unsigned long pos;
public:
    Symbol(string symb,double prob);
    Symbol(string symb,double prob,unsigned long pos);
    double get_prob();
    string get_symb();
    string get_code();
    unsigned long get_pos();
    void set_prob(double a);
    void set_symb(string origin);
    void set_code(string code);
    void set_pos(unsigned long pos);
    void clear_code();
    void print();
    void print_code();
};

class Alphabet{
    vector<Symbol> arr;
    unsigned long size;
    //true - код построен, false - код еще не построен.
public:
    Alphabet(unsigned long size);
    void read();
    unsigned long get_size();
    void print();
    void print_codes();
    double sum_probs(int begin,int end);
    //Шаг построения код Шеннона-Фано.
    void shennoncode_build_step(int begin,int end);
    //Строит оптимальный код (0 - Шеннона-Фано, 1 - Хаффмана) 
    void build_code_arr(int mode);
    //Строит новый алфавит из n-грамм
    Alphabet build_nsized_Alphabet(int n);
    //Возвращает размер символа алфавита
    unsigned get_symbol_size();
    Symbol operator[](int i);
    
    //Кодирует строку str состоящую из символов этого алфавита. **Первые 8 бит** - размер блока. 
    //**Вторые 8 бит** - кол-во добавленных символов при кусочном кодировании.
    //Остальной код - закодированная строка.
    string encode_text(string str);
    //Декодирует code в строку состоящую из символов этого алфавита.
    string decode_text(string code);
};  

//Возвращает строку с числом num записанным в двоичной форме.
string num_to_binstr(unsigned num);

//Возвращает число num записанным в двоичной форме в строке str.
unsigned binstr_to_num(string str);
