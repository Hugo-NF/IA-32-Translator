#include "../include/io_file.hpp"

bool io_file::is_open() {
    return this->file_stream.is_open();
}

void io_file::close() {
    this->file_stream.close();
}

deque<string> io_file::readfile() {
    deque<string> text;
    string buffer;
    while(!this->file_stream.eof()){
        getline(this->file_stream, buffer);
        text.emplace_back(buffer);
    }
    this->file_stream.seekg(0, fstream::beg);
    return text;
}

string io_file::get_filename() {
    return this->filename;
}

string io_file::read_in_string(){
    string buffer;
    while(!this->file_stream.eof())
        buffer += (char) this->file_stream.get();
    this->file_stream.seekg(0, fstream::beg);
    return buffer;
}

void io_file::writeline(const string &line) {
    this->file_stream.write(line.c_str(), line.size());
}

void io_file::writelines(deque<string>& content) {
    for(auto &line: content){
        this->file_stream.write(line.c_str(), line.size());
        this->file_stream.put('\n');
    }
}

