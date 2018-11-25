#include "../include/translator.hpp"

void translator::format_line(long index) {
    input_text[index].assign(regex_replace(input_text[index], comments_format, ""));
    input_text[index].assign(regex_replace(input_text[index], tabs_format, " "));
    input_text[index].assign(regex_replace(input_text[index], line_bgn_format, ""));
    input_text[index].assign(regex_replace(input_text[index], opr_format, " $1"));
    input_text[index].assign(regex_replace(input_text[index], label_div_format, ":"));
}

bool translator::eval_index(string& idx){
    try{
        stoul(idx, nullptr, 0);
        return true;
    }
    catch(exception &exc) {
        return false;
    }
}

bool translator::eval_operator(string& optr) {
    return optr == "+" || optr == "-";
}

void translator::eval_ADD(deque<string> fields) {
    if(!fields[6].empty() || !fields[7].empty() || !fields[8].empty())
        error("Invalid number of arguments to instruction '%s'\n", fields[0].c_str());
    else{
        if(fields[4].empty()){
            text_section.emplace_back(";ADD\nadd eax, dword[" + fields[3] + "]");
        } else {
            if (eval_operator(fields[4]) && eval_index(fields[5]))
                text_section.emplace_back(";ADD\nadd eax, dword[" + fields[3] + fields[4] + "4*" + fields[5] + "]");
            else
                error("Invalid operation '%s %s' in instruction '%s'\n", fields[4].c_str(), fields[5].c_str(), fields[0].c_str());
        }
    }
}

void translator::eval_SUB(deque<string> fields) {
    if(!fields[6].empty() || !fields[7].empty() || !fields[8].empty())
        error("Invalid number of arguments to instruction '%s'\n", fields[0].c_str());
    else{
        if(fields[4].empty()) {
            text_section.emplace_back(";SUB\nsub eax, dword[" + fields[3] + "]");
        } else {
            if (eval_operator(fields[4]) && eval_index(fields[5]))
                text_section.emplace_back(";SUB\nsub eax, dword[" + fields[3] + fields[4] + "4*" + fields[5] + "]");
            else
                error("Invalid operation '%s %s' in instruction '%s'\n", fields[4].c_str(), fields[5].c_str(), fields[0].c_str());
        }
    }
}

void translator::eval_MUL(deque<string> fields) {
    if(!fields[6].empty() || !fields[7].empty() || !fields[8].empty())
        error("Invalid number of arguments to instruction '%s'\n", fields[0].c_str());
    else{
        if(fields[4].empty()) {
            text_section.emplace_back(";MUL\nimul dword["+ fields[3] + "]\njbe sys_overflow");
        } else {
            if (eval_operator(fields[4]) && eval_index(fields[5]))
                text_section.emplace_back(";MUL\nimul dword[" + fields[3] + fields[4] + "4*" + fields[5] + "]\njbe sys_overflow");
            else
                error("Invalid operation '%s %s' in instruction '%s'\n", fields[4].c_str(), fields[5].c_str(), fields[0].c_str());
        }
    }
}

void translator::eval_DIV(deque<string> fields) {
    if(!fields[6].empty() || !fields[7].empty() || !fields[8].empty())
        error("Invalid number of arguments to instruction '%s'\n", fields[0].c_str());
    else{
        if(fields[4].empty()) {
            text_section.emplace_back(";DIV\ncdq\nidiv dword[" + fields[3] + "]");
        } else {
            if (eval_operator(fields[4]) && eval_index(fields[5]))
                text_section.emplace_back(";DIV\ncdq\nidiv dword[" + fields[3] + fields[4] + "4*" + fields[5] + "]");
            else
                error("Invalid operation '%s %s' in instruction '%s'\n", fields[4].c_str(), fields[5].c_str(), fields[0].c_str());
        }
    }
}

void translator::eval_JMP(deque<string> fields) {
    text_section.emplace_back(";JMP\njmp " + fields[3]);
}

void translator::eval_JMPN(deque<string> fields) {
    text_section.emplace_back(";JMPN\ncmp eax, 0\njl "+ fields[3]); // jump if sign
}

void translator::eval_JMPP(deque<string> fields) {
    text_section.emplace_back(";JMPP\ncmp eax, 0\njg "+ fields[3]); // jump if not sign
}

void translator::eval_JMPZ(deque<string> fields) {
    text_section.emplace_back(";JMPZ\ncmp eax, 0\nje "+ fields[3]); // jump if zero
}

void translator::eval_COPY(deque<string> fields) {
    string code, src, dst;
    bool pass = true;

    if(fields[4].empty())
        src = fields[3];
    else{
        if(eval_operator(fields[4]) && eval_index(fields[5]))
            src = fields[3] + fields[4] + "4*" + fields[5];
        else
            pass = false;
    }
    if(fields[7].empty())
        dst = fields[6];
    else{
        if(eval_operator(fields[7]) && eval_index(fields[8]))
            dst = fields[6] + fields[7] + "4*" + fields[8];
        else
            pass = false;
    }

    if(pass){
        code = ";COPY\npush eax\nmov eax, dword[" + src + "]\nmov dword[" + dst + "], eax\npop eax";
        text_section.push_back(code);
    } else
        error("Bad formed instruction: %s\n", fields[0].c_str());

}

void translator::eval_LOAD(deque<string> fields) {
    if(!fields[6].empty() || !fields[7].empty() || !fields[8].empty())
        error("Invalid number of arguments to instruction '%s'\n", fields[0].c_str());
    else{
        if(fields[4].empty()) {
            text_section.emplace_back(";LOAD\nmov eax, dword[" + fields[3] + "]");
        } else {
            if (eval_operator(fields[4]) && eval_index(fields[5]))
                text_section.emplace_back(";LOAD\nmov eax, dword[" + fields[3] + fields[4] + "4*" + fields[5] + "]");
            else
                error("Invalid operation '%s %s' in instruction '%s'\n", fields[4].c_str(), fields[5].c_str(), fields[0].c_str());
        }
    }
}

void translator::eval_STORE(deque<string> fields) {
    if(!fields[6].empty() || !fields[7].empty() || !fields[8].empty())
        error("Invalid number of arguments to instruction '%s'\n", fields[0].c_str());
    else{
        if(fields[4].empty()) {
            text_section.emplace_back(";STORE\nmov dword[" + fields[3] + "], eax");
        } else {
            if (eval_operator(fields[4]) && eval_index(fields[5]))
                text_section.emplace_back(";STORE\nmov dword[" + fields[3] + fields[4] + "4*" + fields[5] + "], eax");
            else
                error("Invalid operation '%s %s' in instruction '%s'\n", fields[4].c_str(), fields[5].c_str(), fields[0].c_str());
        }
    }
}

void translator::eval_INPUT(deque<string> fields) {
    text_section.emplace_back(";INPUT\npush eax\npush " + fields[3] + "\ncall ReadInteger\nadd esp, 4\npop eax");
    copyRoutines = true;
}

void translator::eval_OUTPUT(deque<string> fields) {
    text_section.emplace_back(";OUTPUT\npush eax\npush dword[" + fields[3] + "]\ncall PrintInteger\nadd esp, 4\npop eax");
    copyRoutines = true;
}

void translator::eval_STOP() {
    text_section.emplace_back(";STOP\nsys_exit:\nmov eax, 1\nmov ebx, 0\nint 80h\n");
}

void translator::eval_C_INPUT(deque<string> fields) {
    text_section.emplace_back(";C_INPUT\npush eax\npush " + fields[3] + "\ncall ReadChar\nadd esp, 4\npush sys_terminal_getch\ncall ReadChar\nadd esp, 4\npop eax");
    copyRoutines = true;
}

void translator::eval_C_OUTPUT(deque<string> fields) {
    text_section.emplace_back(";C_OUTPUT\npush eax\npush " + fields[3] + "\ncall PrintChar\nadd esp, 4\npop eax");
    copyRoutines = true;
}

void translator::eval_S_INPUT(deque<string> fields) {
    text_section.emplace_back(";S_INPUT\npush eax\npush " + fields[3] + "\ncall ReadString\nadd esp, 4\npop eax");
    copyRoutines = true;
}

void translator::eval_S_OUTPUT(deque<string> fields) {
    text_section.emplace_back(";S_OUTPUT\npush eax\npush " + fields[3] + "\ncall PrintString\nadd esp, 4\npop eax");
    copyRoutines = true;
}

void translator::eval_CONST(deque<string> fields) {
    string code = fields[1] + " dd " + fields[5];
    data_section.push_back(code);
}

void translator::eval_SPACE(deque<string> fields) {
    string code = fields[1] + " resd " + (fields[5].empty()? "1":fields[5]);
    bss_section.push_back(code);
}

void translator::eval_SECTION(deque<string> fields) {
    transform(fields[3].begin(), fields[3].end(), fields[3].begin(), ::tolower);
    string code = "section ." + fields[3];
    if(fields[3] == "text"){
        text_section.emplace_back("\n" + code);
        text_section.emplace_back("global _start");
        text_section.emplace_back("_start:");
    }
    else if(fields[3] == "data"){
        data_section.emplace_front("nwln dd 0xd, 0xa");
        data_section.emplace_front("ovfl_msg dd 'O','v','e','r','f','l','o','w',' ',"
                                   " 'd', 'e','t','e','c','t','e','d','.',' ','E','x',"
                                   "'i','t','i','n','g','.','.','.',0");
        data_section.push_front(code);
    }
    else if(fields[3] == "bss") {
        bss_section.emplace_front("sys_terminal_getch resb 1");
        bss_section.emplace_front("\n" + code);
    }
    else
        error("Unknown section .%s directive\n", fields[3].c_str());
}

void translator::eval_EQU(deque<string> fields) {
    string code = fields[1] + " EQU " + fields[5];
    data_section.push_back(code);
}

void translator::eval_IF(deque<string> fields) {
    string code = "%if " + fields[3];
    text_section.push_back(code);
}

void translator::translate() {
    smatch matches;
    long stop = input_text.size();

    for(long index = 0; index < stop; index++){
        format_line(index);
        if(input_text[index].empty()){
            input_text.erase(input_text.begin() + index);
            index--;
            stop = input_text.size();
        }
        else{
            if(regex_search(input_text[index], matches, line_format)){
                deque<string> inst_fields;
                for(auto &match: matches) {
                    inst_fields.push_back(match.str());
                    //0: All, 1: Label, 2: Mnemonic, 3: OPERAND_1, 4: OPERATOR_1, 5: OFFSET_1, 6: OPERAND_2, 7: OPERATOR_2, 8: OFFSET_2
                }
                try{
                    switch(instructions[inst_fields[2]]){
                        case ADD_CODE:
                            if(!inst_fields[1].empty())
                                text_section.emplace_back(inst_fields[1] + ":");
                            eval_ADD(inst_fields);
                            break;
                        case SUB_CODE:
                            if(!inst_fields[1].empty())
                                text_section.emplace_back(inst_fields[1] + ":");
                            eval_SUB(inst_fields);
                            break;
                        case MUL_CODE:
                            if(!inst_fields[1].empty())
                                text_section.emplace_back(inst_fields[1] + ":");
                            eval_MUL(inst_fields);
                            break;
                        case DIV_CODE:
                            if(!inst_fields[1].empty())
                                text_section.emplace_back(inst_fields[1] + ":");
                            eval_DIV(inst_fields);
                            break;
                        case JMP_CODE:
                            if(!inst_fields[1].empty())
                                text_section.emplace_back(inst_fields[1] + ":");
                            eval_JMP(inst_fields);
                            break;
                        case JMPN_CODE:
                            if(!inst_fields[1].empty())
                                text_section.emplace_back(inst_fields[1] + ":");
                            eval_JMPN(inst_fields);
                            break;
                        case JMPP_CODE:
                            if(!inst_fields[1].empty())
                                text_section.emplace_back(inst_fields[1] + ":");
                            eval_JMPP(inst_fields);
                            break;
                        case JMPZ_CODE:
                            if(!inst_fields[1].empty())
                                text_section.emplace_back(inst_fields[1] + ":");
                            eval_JMPZ(inst_fields);
                            break;
                        case COPY_CODE:
                            if(!inst_fields[1].empty())
                                text_section.emplace_back(inst_fields[1] + ":");
                            eval_COPY(inst_fields);
                            break;
                        case LOAD_CODE:
                            if(!inst_fields[1].empty())
                                text_section.emplace_back(inst_fields[1] + ":");
                            eval_LOAD(inst_fields);
                            break;
                        case STORE_CODE:
                            if(!inst_fields[1].empty())
                                text_section.emplace_back(inst_fields[1] + ":");
                            eval_STORE(inst_fields);
                            break;
                        case INPUT_CODE:
                            if(!inst_fields[1].empty())
                                text_section.emplace_back(inst_fields[1] + ":");
                            eval_INPUT(inst_fields);
                            break;
                        case OUTPUT_CODE:
                            if(!inst_fields[1].empty())
                                text_section.emplace_back(inst_fields[1] + ":");
                            eval_OUTPUT(inst_fields);
                            break;
                        case STOP_CODE:
                            if(!inst_fields[1].empty())
                                text_section.emplace_back(inst_fields[1] + ":");
                            eval_STOP();
                            break;
                        case C_INPUT_CODE:
                            if(!inst_fields[1].empty())
                                text_section.emplace_back(inst_fields[1] + ":");
                            eval_C_INPUT(inst_fields);
                            break;
                        case C_OUTPUT_CODE:
                            if(!inst_fields[1].empty())
                                text_section.emplace_back(inst_fields[1] + ":");
                            eval_C_OUTPUT(inst_fields);
                            break;
                        case S_INPUT_CODE:
                            if(!inst_fields[1].empty())
                                text_section.emplace_back(inst_fields[1] + ":");
                            eval_S_INPUT(inst_fields);
                            break;
                        case S_OUTPUT_CODE:
                            if(!inst_fields[1].empty())
                                text_section.emplace_back(inst_fields[1] + ":");
                            eval_S_OUTPUT(inst_fields);
                            break;
                        case CONST_CODE:
                            eval_CONST(inst_fields);
                            break;
                        case SPACE_CODE:
                            eval_SPACE(inst_fields);
                            break;
                        case SECTION_CODE:
                            eval_SECTION(inst_fields);
                            break;
                        case EQU_CODE:
                            eval_EQU(inst_fields);
                            break;
                        case IF_CODE:
                            eval_IF(inst_fields);
                            input_text.insert(input_text.begin() + index + 2, "%endif");
                            break;
                        default:
                            error("Unknown operation mnemonic '%s' at line %d\n", inst_fields[2].c_str(), index+1);
                            proceed = false;
                            break;
                    }
                }
                catch(exception &exc){
                    error("Exception '%s' reported at line %d\n", exc.what(), index+1);
                    proceed = false;
                }
            }
            else if(regex_search(input_text[index], matches, label_std))
                text_section.push_back(matches[0].str());
            else if(input_text[index] == "%endif")
                text_section.emplace_back("%endif");
            else {
                error("Unknown error detected at line %d\n", index+1);
                proceed = false;
            }
        }
    }
    translated = !input_text.empty();
}

bool translator::write_to_file(const char *filename) {
    /*
    io_file debug((string(filename) + "_debug.s").c_str(), fstream::out);
    debug.writelines(input_text);
    debug.close();
    */
    if(proceed && translated){
        io_file output_file(filename, fstream::out);
        output_file.writelines(data_section);
        output_file.writelines(bss_section);
        output_file.writelines(text_section);
        deque<string> functions;

        if(copyRoutines){
            io_file io_functions("../IA-32/io.asm", fstream::in);
            if(io_functions.is_open()){
                functions = io_functions.readfile();
                output_file.writelines(functions);
            }
            else
                error("Missing I/O functions definitions. No such file or directory: ../IA-32/io.asm");
        }

        output_file.close();


        return true;
    }
    return false;
}

