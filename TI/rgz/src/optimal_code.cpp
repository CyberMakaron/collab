#include "optimal_code.hpp"

using namespace std;

Symbol::Symbol(string symb,double prob):symb(symb),prob(prob){};
Symbol::Symbol(string symb,double prob,unsigned long pos):symb(symb),prob(prob),pos(pos){};

double Symbol::get_prob(){
    return this->prob;
};
string Symbol::get_symb(){
    return this->symb;
};
string Symbol::get_code(){
return this->code;
};
unsigned long Symbol::get_pos(){
    return this->pos;
};
void Symbol::set_prob(double a){
    this->prob=a;
};
void Symbol::set_symb(string origin){
    this->symb=origin;
};
void Symbol::set_code(string code){
    this->code=code;
};
void Symbol::set_pos(unsigned long pos){
	this->pos=pos;
};

void Symbol::clear_code(){
	this->code.clear();
};

void Symbol::print(){
    cout<<"\""<<this -> symb<<"\" - "<<this->prob;
};

void Symbol::print_code(){
    cout<<"\""<<this -> symb<<"\" - "<<this->prob <<" - "<< this->code;
};

Alphabet::Alphabet(unsigned long size):size(size){};

void Alphabet::read(){
    cout<<"Введите алфавит размера "<<this->size<<" :\n"; 
    string t_symb;
    double t_prob;
    for(int i=0;i<this->size;i++){
        cin>>t_symb>>t_prob;
        this->arr.push_back(Symbol(t_symb,t_prob,i+1));    
    };
};

unsigned long Alphabet::get_size(){
	return this->size;
};



void Alphabet::print(){
	cout<<endl;
    for(int i=0;i<this->size;i++){
        cout<<this->arr[i].get_pos()<<". ";
        this->arr[i].print();
        cout<<"\n";
    };
};

void Alphabet::print_codes(){
	cout<<endl;
    for(int i=0;i<this->size;i++){
        this->arr[i].print_code();
		cout<<endl;
    };
};

Symbol Alphabet::operator[](int i){
	return this->arr[i];
};


//Возвращает сумму вероятностей алфавита с элемента begin по end.
double Alphabet::sum_probs(int begin,int end){
	double t_sum=0;
	for(int i=begin;i<end;i++){
		t_sum+=this->arr[i].get_prob();
	}
	return t_sum;
};

//Шаг алгоритма Шеннона-Фано.
void Alphabet::shennoncode_build_step(int begin,int end){
	//номер элемента делящий алфавит на 2 части суммы вероятностей которых равны.
	int mid=begin;
	//Флаг остановки
	bool flag=true;
	double min_diff,diff=1;
	//Пока разность вероятностей между левой и правой частью уменьшается сдвигает mid вправо.
	do{
		mid++;
		min_diff=diff;
		diff=fabs(this->sum_probs(begin,mid)-this->sum_probs(mid,end));
	}while(diff<min_diff);
	//Возвращаемся к середенному элементу
	mid--;
	//Условия остановки рекурсии: 1.Начальный элемент последовательности равен конечному 2.Между начальным и конечным элеметом нет других элементов.
	if((begin!=end)&&(abs(begin-end)!=1)){
		//Заполняем коды символов
		for(int i=begin;i<mid;i++){
			this->arr[i].set_code(this->arr[i].get_code()+"0");
		}
		for(int i=mid;i<end;i++){
			this->arr[i].set_code(this->arr[i].get_code()+"1");
		}
		//Применяем шаг алгоритма к правому и левому подмасиву относительно mid.
		this->shennoncode_build_step(begin,mid);
		this->shennoncode_build_step(mid,end);
	}
};

void Alphabet::build_code_arr(int mode){
	//Сортировка алфавита по убыванию вероятностей.
	sort(this->arr.begin(),this->arr.end(), [](Symbol& a, Symbol& b){
			if(a.get_prob()==b.get_prob()){
				return a.get_pos()<b.get_pos();
			}
			return a.get_prob()>b.get_prob();
		});
	for(int i=0;i<this->size;i++){
		this->arr[i].clear_code();
	}
	//Заполнение кодов символов.
	switch (mode){
		case 0:
			this->shennoncode_build_step(0,this->size);
		break;
		case 1:
			cout<<"НУ ТУТ КАРОЧЕ ХАФФМАН"<<endl;	
		default:
			cout<<"НЕКОРЕКТНЫЙ ВЫБОР АЛГОРИТМА ПОСТРОЕНИЯ ОПТИМАЛЬНОГО КОДА"<<endl<<"ИСПРАВЬТЕ ИСХОДНЫЙ КОД"<<endl;
			exit(1);
		break;
	};
	//Сортировка в лексикографическом порядке.
	/*sort(this->arr.begin(),this->arr.end(), [](Symbol& a, Symbol& b){
		return a.get_pos()<b.get_pos();
	});*/
};

Alphabet Alphabet::build_nsized_Alphabet(int n){
	//Размер исходного алфавита.
	unsigned long m=this->size;
	//Создание результирующего алфавита размером m^n 
    unsigned long new_size=(int)round(pow(m,n));
	Alphabet newAlphabet(new_size);
	//Временные переменные для формирования нового символа алфавита.
	string t_symb; double t_prob; 
	//Массив индексов символов исходного алфавита, 0-ой элемент сигнальный для остановки алгоритма.
	int index_arr[n+1];
	for (int i=0;i<=n;i++) index_arr[i]=0;
	//Инициализация временной переменной вероятности символа.
	t_prob=1;	
	//Переменная для записи номера символа в алфавите.
	int j=1;
	do{
		//Построение нового символа алфавита.
		for(int i=1;i<=n;i++){
			int index = index_arr[i];
			t_symb+=this->arr[index].get_symb();
			t_prob*=this->arr[index].get_prob();
		};
		//Запись символа в новый алфавит
		newAlphabet.arr.push_back(Symbol(t_symb,t_prob,j));
		//Очистка временных переменных
		t_symb.clear();
		t_prob=1;

		int last=n; index_arr[last]++;
		//Перенос единицы при переполнении разрядов.
		while(index_arr[last]==m){
			index_arr[last]=0;
			index_arr[last-1]+=1;
			last--;
		};
		j++;
	} while(index_arr[0]==0);
	return newAlphabet;
};

unsigned Alphabet::get_symbol_size(){
	return arr[0].get_symb().length();
};


string Alphabet::encode_text(string str){
	//Результирующий код.
	string result_code;

	unsigned block_size = this->get_symbol_size();
	//Кол-во символов дописанных для дополнения последнего блока.
	unsigned addition_symbols = block_size - (str.length()%block_size);
	//Записываем размер блока и кол-во дописанных символов в начало кода.	
	result_code+=num_to_binstr(block_size);
	result_code+=num_to_binstr(addition_symbols);

	//Дописываем последний блок до полноценного, если он кусочный.
	for(int i=0;i<addition_symbols;i++)	str+=str[0];

	//Вычисляем размер текста в блоках.
	unsigned str_block_count=str.length()/block_size;

	for(int i=0;i<str_block_count;i++){
		//Срез строки размером равным размеру блока.
		string block_slice;
		block_slice=str.substr(i*block_size,block_size);
		//Поиск символа в алфавите.
		int symbol_index=-1,j=0;
		bool flag=true;
		while((j<this->size)&&flag){
			if(this->arr[j].get_symb()==block_slice){
				symbol_index=j;
				flag=false;
			}
			j++;
		};
		//Запись кода символа в результирующий код.
		if(flag){
			cout<<"	Неверно введено слово (мне лень делать зацикливание или эксепшоны поэтому...). Завершение программы."<<endl;
			exit(1);
		}
		else result_code+=this->arr[symbol_index].get_code();
	};
	return result_code;
};

string Alphabet::decode_text(string code){
	//Результирующий текст
	string result_text;
	//Считывание заголовка размером 16 бит с размером блока и кол-вом добавленных блоков.
	unsigned block_size = binstr_to_num(code.substr(0,8));
	unsigned addition_symbols = binstr_to_num(code.substr(8,8));
	//Удаление заголовка из кода для дальнейшего декодирования.
	code.erase(0,16);
	//Каждый шаг цикла добавляет в результирующую строку блок из исходного алфавита, и удаляет из строки с кодом код блока.
	while(code.length()!=0){
		bool flag=true;
		unsigned size_of_slice=1;
		unsigned j;
		//Поиск блока с кодом размером size_of_slice
		while((size_of_slice<=60)&&flag){
			j=0;
			string slice=code.substr(0,size_of_slice);
			//Поиск кода совпадающего с slice
			while((j<this->size)&&flag){
				if(this->arr[j].get_code()==slice){
					flag=false;
				}
				else j++;
			};
			size_of_slice++;
		};
		result_text+=arr[j].get_symb();
		//Удаление кода из начала строки 
		code.erase(0,size_of_slice-1);
	}
	//Удаление добавленных при кодировке символов.
	result_text.erase((result_text.length()-addition_symbols),addition_symbols);
	return result_text;
};


string num_to_binstr(unsigned num){
	bitset<8> result((unsigned char)num);
	return result.to_string();
};

unsigned binstr_to_num(string str){
	bitset<8> result(str);
	return (unsigned)result.to_ulong();
};
