#include "../include/translator.hpp"

void translator::translate() {
    smatch matches;
    int line_number = 0;
    for(auto &line: input_text){
        if(regex_search(line, matches, line_format)){
            deque<string> inst_fields;
            int r_group = 1;
            for(auto &match: matches) {
                inst_fields.push_back(
                        matches[r_group].str()); //0: Label, 1: Mnemonic, 2: OPERAND_1, 3: OPERATOR_1, 4: OFFSET_1, 5: OPERAND_2, 6: OPERATOR_2, 7: OFFSET_2
            }

            switch(instructions[matches[1]]){
                case ADD_CODE:
                    break;
                case SUB_CODE:
                    break;
                case MUL_CODE:
                    break;
                case DIV_CODE:
                    break;
                case JMP_CODE:
                    break;
                case JMPN_CODE    :
                    break;
                case JMPP_CODE    :
                    break;
                case JMPZ_CODE    :
                    break;
                case COPY_CODE    :
                    break;
                case LOAD_CODE    :
                    break;
                case STORE_CODE   :
                    break;
                case INPUT_CODE   :
                    break;
                case OUTPUT_CODE  :
                    break;
                case STOP_CODE    :
                    break;
                case C_INPUT_CODE :
                    break;
                case C_OUTPUT_CODE:
                    break;
                case S_INPUT_CODE :
                    break;
                case S_OUTPUT_CODE:
                    break;
                case CONST_CODE   :
                    break;
                case SPACE_CODE   :
                    break;
                case SECTION_CODE :
                    break;
                case EQU_CODE     :
                    break;
                case IF_CODE      :
                    break;
                default:
                    error("Unknown operation mnemonic at line %d\n", line_number);
            }

        }
        else {
            error("Unknown error detected at line %d\n", line_number);
        }

        line_number++;
    }
}

void translator::write_to_file(const char *filename) {

}

