#include "../include/translator.hpp"

void translator::format_line(long index) {
    smatch m;
    input_text[index].assign(regex_replace(input_text[index], comments_format, ""));
    input_text[index].assign(regex_replace(input_text[index], tabs_format, " "));
    input_text[index].assign(regex_replace(input_text[index], line_bgn_format, ""));
    input_text[index].assign(regex_replace(input_text[index], opr_format, ":"));
    input_text[index].assign(regex_replace(input_text[index], label_div_format, " $1"));
    if(regex_search(input_text[index], m, hex_format)){
        int num = (int) stoul(m[0].str(), nullptr, 16);
        input_text[index].assign(regex_replace(input_text[index], hex_format, to_string(num)));
    }
}

int translator::eval_index(string& idx){
    return stoi(idx);
}

bool translator::eval_operator(string& optr){
    if(optr == "+")
        return true;
    else if(optr == "-")
        return false;
    else
        throw invalid_argument("unknown operator");
}

void translator::eval_ADD(deque<string> fields) {
    text_section.push_back(translations[fields[2]]);
}

void translator::eval_SUB(deque<string> fields) {
    text_section.push_back(translations[fields[2]]);
}

void translator::eval_MUL(deque<string> fields) {
    text_section.push_back(translations[fields[2]]);
}

void translator::eval_DIV(deque<string> fields) {
    text_section.push_back(translations[fields[2]]);
}

void translator::eval_JMP(deque<string> fields) {
    text_section.push_back(translations[fields[2]]);
}

void translator::eval_JMPN(deque<string> fields) {
    text_section.push_back(translations[fields[2]]);
}

void translator::eval_JMPP(deque<string> fields) {
    text_section.push_back(translations[fields[2]]);
}

void translator::eval_JMPZ(deque<string> fields) {
    text_section.push_back(translations[fields[2]]);
}

void translator::eval_COPY(deque<string> fields) {
    text_section.push_back(translations[fields[2]]);
}

void translator::eval_LOAD(deque<string> fields) {
    text_section.push_back(translations[fields[2]]);
}

void translator::eval_STORE(deque<string> fields) {
    text_section.push_back(translations[fields[2]]);
}

void translator::eval_INPUT(deque<string> fields) {
    text_section.push_back(translations[fields[2]]);
}

void translator::eval_OUTPUT(deque<string> fields) {
    text_section.push_back(translations[fields[2]]);
}

void translator::eval_STOP(deque<string> fields) {
    text_section.push_back(translations[fields[2]]);
}

void translator::eval_C_INPUT(deque<string> fields) {
    text_section.push_back(translations[fields[2]]);
}

void translator::eval_C_OUTPUT(deque<string> fields) {
    text_section.push_back(translations[fields[2]]);
}

void translator::eval_S_INPUT(deque<string> fields) {
    text_section.push_back(translations[fields[2]]);
}

void translator::eval_S_OUTPUT(deque<string> fields) {
    text_section.push_back(translations[fields[2]]);
}

void translator::eval_CONST(deque<string> fields) {
    text_section.push_back(translations[fields[2]]);
}

void translator::eval_SPACE(deque<string> fields) {
    text_section.push_back(translations[fields[2]]);
}

void translator::eval_SECTION(deque<string> fields) {
    text_section.push_back(translations[fields[2]]);
}

void translator::eval_EQU(deque<string> fields) {
    text_section.push_back(translations[fields[2]]);
}

void translator::eval_IF(deque<string> fields) {
    text_section.push_back(translations[fields[2]]);
}

void translator::translate() {
    smatch matches;
    long stop = input_text.size();

    for(long index = 0; index < stop; index++){
        if(input_text[index].empty()){
            input_text.erase(input_text.begin() + index);
            index--;
            stop = input_text.size();
        }
        else{
            format_line(index);
            if(regex_search(input_text[index], matches, line_format)){
                deque<string> inst_fields;
                for(auto &match: matches) {
                    inst_fields.push_back(match.str());
                    //0: All, 1: Label, 2: Mnemonic, 3: OPERAND_1, 4: OPERATOR_1, 5: OFFSET_1, 6: OPERAND_2, 7: OPERATOR_2, 8: OFFSET_2
                }

                try{
                    switch(instructions[inst_fields[2]]){
                        case ADD_CODE:
                            eval_ADD(inst_fields);
                            break;
                        case SUB_CODE:
                            eval_SUB(inst_fields);
                            break;
                        case MUL_CODE:
                            eval_MUL(inst_fields);
                            break;
                        case DIV_CODE:
                            eval_DIV(inst_fields);
                            break;
                        case JMP_CODE:
                            eval_JMP(inst_fields);
                            break;
                        case JMPN_CODE:
                            eval_JMPN(inst_fields);
                            break;
                        case JMPP_CODE:
                            eval_JMPP(inst_fields);
                            break;
                        case JMPZ_CODE:
                            eval_JMPZ(inst_fields);
                            break;
                        case COPY_CODE:
                            eval_COPY(inst_fields);
                            break;
                        case LOAD_CODE:
                            eval_LOAD(inst_fields);
                            break;
                        case STORE_CODE:
                            eval_STORE(inst_fields);
                            break;
                        case INPUT_CODE:
                            eval_INPUT(inst_fields);
                            break;
                        case OUTPUT_CODE:
                            eval_OUTPUT(inst_fields);
                            break;
                        case STOP_CODE:
                            eval_STOP(inst_fields);
                            break;
                        case C_INPUT_CODE:
                            eval_C_INPUT(inst_fields);
                            break;
                        case C_OUTPUT_CODE:
                            eval_C_OUTPUT(inst_fields);
                            break;
                        case S_INPUT_CODE:
                            eval_S_INPUT(inst_fields);
                            break;
                        case S_OUTPUT_CODE:
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
            else if(regex_search(input_text[index], matches, label_std)){
                text_section.push_back(matches[0].str());
            }
            else {
                error("Unknown error detected at line %d\n", index+1);
                proceed = false;
            }
        }
    }
    translated = true;
}

void translator::write_to_file(const char *filename) {
    io_file output_file(filename, fstream::out);

    output_file.writelines(data_section);
    output_file.writelines(bss_section);
    output_file.writelines(text_section);

    output_file.close();
}

