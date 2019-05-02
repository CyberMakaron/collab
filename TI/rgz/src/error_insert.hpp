#ifndef _ERROR_INSERT
#define _ERROR_INSERT
    #include <string>
    #include <iostream>
    #include <time.h>
    using namespace std;

    class DataChannal{
        string data;
        long error_bit;
    public:
        DataChannal(string in_str);
        void add_error();
        string get_data();
        int get_error_bit();
    };

#endif