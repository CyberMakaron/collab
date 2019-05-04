#ifndef _REPORT_GEN
#define _REPORT_GEN

#include <string>
#include <iostream>
#include "optimal_code.hpp"
#include "error_insert.hpp"




class Report{
    virtual void gen_report(string filename) = 0;
};

class MarkdownReport: public Report{
public:
    void gen_report();
};

class TXTReport: public Report{
public:
    void gen_report();
};

#endif