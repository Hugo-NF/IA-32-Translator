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
    string nasm_call = "nasm -f elf -o ";
    string ld_call = "ld -m elf_i386 ";
    vector<int> files = eval_flags(argc, argv, nasm, start);
    if(start){
        translator_version();
        devs();
        for(auto &index: files){
            info("Current file: %s.asm\n", argv[index]);
            translator file_instance((string(argv[index]) + ".asm").c_str());
            file_instance.translate();
            if(file_instance.write_to_file((string(argv[index]) + ".s").c_str()))
                success("File '%s.asm' done.", argv[index]);
            if(nasm){
                info("Calling nasm...");
                system((nasm_call + string(argv[index]) + ".o " + string(argv[index]) + ".asm").c_str());
                system((ld_call + string(argv[index]) + " " + string(argv[index]) + ".o").c_str());
            }
        }

    }

    return 0;
}