#ifndef TRANSLATOR_HPP
#define TRANSLATOR_HPP

#include "console.hpp"
#include "io_file.hpp"
#include "defs.hpp"

#include <deque>
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

    regex line_format = regex(LINE_REGEX, regex::ECMAScript);
    map<string, string> equ_definitions;
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

    map<string, string> translations = {
            {"ADD"      , "PLACEHOLDER ADD"     },
            {"SUB"      , "PLACEHOLDER SUB"     },
            {"MUL"      , "PLACEHOLDER MUL"     },
            {"DIV"      , "PLACEHOLDER DIV"     },
            {"JMP"      , "PLACEHOLDER JMP"     },
            {"JMPN"     , "PLACEHOLDER JMPN"    },
            {"JMPP"     , "PLACEHOLDER JMPP"    },
            {"JMPZ"     , "PLACEHOLDER JMPZ"    },
            {"COPY"     , "PLACEHOLDER COPY"    },
            {"LOAD"     , "PLACEHOLDER LOAD"    },
            {"STORE"    , "PLACEHOLDER STORE"   },
            {"INPUT"    , "PLACEHOLDER INPUT"   },
            {"OUTPUT"   , "PLACEHOLDER OUTPUT"  },
            {"C_INPUT"  , "PLACEHOLDER C_INPUT" },
            {"C_OUTPUT" , "PLACEHOLDER C_OUTPUT"},
            {"S_INPUT"  , "PLACEHOLDER S_INPUT" },
            {"S_OUTPUT" , "PLACEHOLDER S_OUTPUT"},
            {"STOP"     , "PLACEHOLDER STOP"    },
            {"CONST"    , "PLACEHOLDER CONST"   },
            {"SPACE"    , "PLACEHOLDER SPACE"   },
            {"SECTION"  , "PLACEHOLDER SECTION" },
            {"EQU"      , "PLACEHOLDER EQU"     },
            {"IF"       , "PLACEHOLDER IF"      }
    };


public:
    explicit translator(const char* filename): input_file((string(filename) + ".asm").c_str(), fstream::in){
        input_text = input_file.readfile();
    }

    virtual ~translator() = default;

    void translate();
    void write_to_file(const char *filename);

};


#endif //TRANSLATOR_HPP
