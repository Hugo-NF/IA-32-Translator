#include "../include/console.hpp"
#include "../include/translator.hpp"
#include "../include/defs.hpp"

using namespace console;

vector<int> eval_flags(int argc, const char **argv, bool& mount, bool& start){
    vector<int> res;
    for(int arg = 1; arg < argc; arg++){
        if(argv[arg][0] != '-')
            res.push_back(arg);
        else {
            if(string(argv[arg]) == FLAG_HELP){
                help();
                start = false;
            }
            else if(string(argv[arg]) == FLAG_VERSION){
                translator_version();
                start = false;
            }
            else if(string(argv[arg]) == FLAG_DEV){
                devs();
                start = false;
            }
            else if(string(argv[arg]) == FLAG_EXE)
                mount = true;
            else if(string(argv[arg]) == FLAG_TRANSLATE)
                mount = false;
            else {
                fatal("Translator: Unknown flag option %s" RESET "\n", argv[arg]);
                start = false;
            }
        }
    }
    return res;
}

int main(int argc, const char** argv) {
    bool start = true, nasm = false;
    //string nasm_call = "";
    vector<int> files = eval_flags(argc, argv, nasm, start);
    if(start){
        translator_version();
        devs();
        for(auto &index: files){
            translator file_instance((string(argv[index]) + ".asm").c_str());
            file_instance.translate();
            file_instance.write_to_file((string(argv[index]) + ".s").c_str());
        }
    }

    return 0;
}