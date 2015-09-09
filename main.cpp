/**
 * clip - A simple copy and paste utility for the terminal
 *
 * @author  Matthew Cross <blacklightgfx@gmail.com>
 * @package clip
 */
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

using namespace std;

const char* TEMP_FILE = "tmp_buffer";

const int REQUIRED_ARGUMENT_COUNT = 2;

void print_help() {
    cout << "Basic usage" << endl
         << "clip [copy|paste] [source]" << endl
         << "--------------------------" << endl
         << "copy     - Copies stdin or a file to the buffer" << endl
         << "paste    - Pastes the current buffer to stdout or a file" << endl
         << "source   - A file path or blank (Optional)" << endl;
}

void copy_file(const char* filename, const char* destination) {
    ifstream input(filename, fstream::binary);
    ofstream output(destination, fstream::trunc|fstream::binary);
    output << input.rdbuf();
    output.flush();
    output.close();
    input.close();
}

void write_to_buffer(int data_length, char** data) {
    ofstream file(TEMP_FILE);
    if (!file.is_open()) {
        cerr << "Error: Failed to open buffer file" << endl;
        return;
    }

    cout << "Entering interactive mode press CTRL+D to exit" << endl;

    for (string line; getline(cin, line);) {
        file << line << endl;
    }

    file.flush();
    file.close();
}

void read_from_buffer() {
    ifstream file(TEMP_FILE);
    if (!file.is_open()) {
        cerr << "Error: Failed to open buffer file" << endl;
        return;
    }

    for (string line; getline(file, line);) {
        cout << line << endl;
    }

    file.close();
}

bool string_equals(const char* command, const char* sample) {
    return 0 == strcmp(command, sample);
}

void copy_action(int argc, char** argv, bool using_file) {
    if (using_file) {
        copy_file(argv[2], TEMP_FILE);
    } else {
        write_to_buffer(argc, argv);
    }
}

void paste_action(int argc, char** argv, bool using_file) {
    if (using_file) {
        copy_file(TEMP_FILE, argv[2]);
    } else {
        read_from_buffer();
    }
}

void run_app(int argc, char** argv) {
    bool using_file = (argc == REQUIRED_ARGUMENT_COUNT + 1);

    if (string_equals("copy", argv[1])) {
        copy_action(argc, argv, using_file);
    } else if (string_equals("paste", argv[1])){
        paste_action(argc, argv, using_file);
    } else {
        print_help();
    }
}

int main(int argc, char** argv) {
    if (argc < REQUIRED_ARGUMENT_COUNT) {
        print_help();
        return 1;
    }

    try {
        run_app(argc, argv);
    } catch (exception e) {
        cerr << "Exception: " << e.what() << endl;
        return 1;
    }

    return 0;
}

