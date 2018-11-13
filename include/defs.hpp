#ifndef TRADUTOR_DEFS_HPP
#define TRADUTOR_DEFS_HPP

#define TRANSLATOR_VERSION  "0.0.1"

#define FLAG_HELP       "-h"
#define FLAG_VERSION    "-v"
#define FLAG_DEV        "-d"
#define FLAG_EXE        "-o"
#define FLAG_TRANSLATE  "-c"

#define COMMENTS    "(\t|\\s)*;(.*)"
#define TABS_SPACES "(\t|\\s)+"
#define LINE_BEGIN  "^ "
#define OPR_REGEX   "(?:|\t|\\s)*([,+\\-])(?:|\t|\\s)*"
#define LABEL_DIV   "(\t|\\s)+:"
#define LABEL_STD   "(?:([A-Za-z_]\\w*):)"
#define LINE_REGEX  "^(?:([A-Za-z_]\\w*): )?([A-Za-z]+)(?: ([A-Za-z_]\\w*))?(?: ([+-]) )?(?: ?([-\\d]+))?(?: ,)?(?: ([A-Za-z_]\\w*))?(?: ([+-]) )?(?: ?([-\\d]+))?$"

#define ADD_CODE         1
#define SUB_CODE         2
#define MUL_CODE         3
#define DIV_CODE         4
#define JMP_CODE         5
#define JMPN_CODE        6
#define JMPP_CODE        7
#define JMPZ_CODE        8
#define COPY_CODE        9
#define LOAD_CODE        10
#define STORE_CODE       11
#define INPUT_CODE       12
#define OUTPUT_CODE      13
#define STOP_CODE        14
#define C_INPUT_CODE     15
#define C_OUTPUT_CODE    16
#define S_INPUT_CODE     19
#define S_OUTPUT_CODE    20
#define CONST_CODE       21
#define SPACE_CODE       22
#define SECTION_CODE     23
#define EQU_CODE         24
#define IF_CODE          25

#endif //TRADUTOR_DEFS_HPP
