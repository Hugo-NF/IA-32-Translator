#ifndef TRANSLATOR_HPP
#define TRANSLATOR_HPP

#include "console.hpp"
#include "io_file.hpp"
#include "defs.hpp"

#include <deque>
#include <exception>
#include <map>
#include <regex>
#include <string>

using namespace std;

class translator{
private:

    io_file input_file;
    deque<string> input_text;
    deque<string> text_section;
    deque<string> data_section;
    deque<string> bss_section;

    bool proceed = true;
    bool translated = false;
    bool copyRoutines = false;

    regex line_format       = regex(LINE_REGEX, regex::ECMAScript);
    regex label_std         = regex(LABEL_STD, regex::ECMAScript);
    regex comments_format   = regex(COMMENTS, regex::ECMAScript);
    regex tabs_format       = regex(TABS_SPACES, regex::ECMAScript);
    regex line_bgn_format   = regex(LINE_BEGIN, regex::ECMAScript);
    regex opr_format        = regex(OPR_REGEX, regex::ECMAScript);
    regex label_div_format  = regex(LABEL_DIV, regex::ECMAScript);

    map<string, int> instructions = {
            {"ADD"      , 1},
            {"SUB"      , 2},
            {"MUL"      , 3},
            {"DIV"      , 4},
            {"JMP"      , 5},
            {"JMPN"     , 6},
            {"JMPP"     , 7},
            {"JMPZ"     , 8},
            {"COPY"     , 9},
            {"LOAD"     , 10},
            {"STORE"    , 11},
            {"INPUT"    , 12},
            {"OUTPUT"   , 13},
            {"STOP"     , 14},
            {"C_INPUT"  , 15},
            {"C_OUTPUT" , 16},
            {"S_INPUT"  , 19},
            {"S_OUTPUT" , 20},
            {"CONST"    , 21},
            {"SPACE"    , 22},
            {"SECTION"  , 23},
            {"EQU"      , 24},
            {"IF"       , 25}
    };

    void format_line(long index);
    bool eval_index(string& idx);
    bool eval_operator(string& optr);
    void eval_ADD(deque<string> fields);
    void eval_SUB(deque<string> fields);
    void eval_MUL(deque<string> fields);
    void eval_DIV(deque<string> fields);
    void eval_JMP(deque<string> fields);
    void eval_JMPN(deque<string> fields);
    void eval_JMPP(deque<string> fields);
    void eval_JMPZ(deque<string> fields);
    void eval_COPY(deque<string> fields);
    void eval_LOAD(deque<string> fields);
    void eval_STORE(deque<string> fields);
    void eval_INPUT(deque<string> fields);
    void eval_OUTPUT(deque<string> fields);
    void eval_STOP();
    void eval_C_INPUT(deque<string> fields);
    void eval_C_OUTPUT(deque<string> fields);
    void eval_S_INPUT(deque<string> fields);
    void eval_S_OUTPUT(deque<string> fields);
    void eval_CONST(deque<string> fields);
    void eval_SPACE(deque<string> fields);
    void eval_SECTION(deque<string> fields);
    void eval_EQU(deque<string> fields);
    void eval_IF(deque<string> fields);


public:
    explicit translator(const char* filename): input_file(filename, fstream::in){
        if(input_file.is_open())
            input_text = input_file.readfile();
    }

    virtual ~translator() = default;

    void translate();
    bool write_to_file(const char *filename);

};


#endif //TRANSLATOR_HPP
