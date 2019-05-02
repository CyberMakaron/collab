#include "error_insert.hpp"

DataChannal::DataChannal(string in_str):data(in_str){
    srand(time(NULL));
};

void DataChannal::add_error(){
    size_t data_length=this->data.length();
    int mode;
    bool input_loop=true;
    cout<<"Моделирование канала связи."; cout<<"Произошли ли ошибки при передаче? (0 - нет, 1 - ошибка в определенном бите, 2 - случайная ошибка) - ";    
    while(input_loop){
        cout<<"Произошли ли ошибки при передаче? (0 - нет, 1 - ошибка в определенном бите, 2 - случайная ошибка) - ";
        cin>>mode;
        switch (mode){
            case 0:
                this->error_bit=-1;
                input_loop=false;
            break;
            case 1:
                bool error_loop=true;
                int error_index;
                while(error_loop){
                    cout<<"Введите номер бита в котором произошла ошибка (от 0 до "
                        <<data_length<<") - ";
                    cin>>error_index;
                    if(error_index>data_length){
                        cout<<"Некорректный выбор. Повторите ввод."<<endl;                
                    }
                    else {
                        error_loop=false;
                        this->error_bit=error_index;
                    };
                }
                input_loop=false;
            break;
            case 2:
                this->error_bit=random()%data_length;
                input_loop=false;
            break;        
            default:
                cout<<"Некорректный выбор. Повторите ввод."<<endl;
            break;
        }
    }
};

string DataChannal::get_data(){
    return this->data;
};  

int DataChannal::get_error_bit(){
    return this->error_bit;
};
