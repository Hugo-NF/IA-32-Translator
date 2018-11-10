#ifndef IO_FILE_HPP
#define IO_FILE_HPP

#include <iostream>
#include <fstream>
#include <deque>

#include "console.hpp"

using namespace std;
using namespace console;

class io_file{
private:
    fstream file_stream;
    string filename;

public:
    explicit io_file(const char* filename, fstream::openmode flag){
        this->filename = filename;
        file_stream.open(filename, flag);
        if (!file_stream.is_open())
            error("IOModule: Could not open file %s\n", filename);

    }

    virtual ~io_file() = default;
    bool is_open();
    void close();
    string get_filename();
    string read_in_string();
    deque<string> readfile();
    void writeline(const string& line);
    void writelines(deque<string>& content);

};

#endif //IO_FILE_HPP
