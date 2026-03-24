#include "Args.h"
#include <iostream>
#include <stdexcept>

using namespace std;

// helper: check if something is an option
bool is_option(string s) {
    return s.size() > 0 && s[0] == '-';
}

// helper: safe int conversion
int to_int(string s, string name) {
    try {
        return stoi(s);
    } catch (...) {
        throw runtime_error("invalid integer for " + name + ": " + s);
    }
}

Args Args::parse(int argc, char* argv[]) {

    // check required args
    if (argc < 3) {
        throw runtime_error("missing output file");
    }

    Args args;
    args.input = argv[1];
    args.output = argv[2];

    for (int i = 3; i < argc; i++) {

        string token = argv[i];

        // -------- FLAGS --------
        if (token == "--grayscale" || token == "-g") {
            args.grayscale = true;
        }
        else if (token == "--blur" || token == "-l") {
            args.blur = true;
        }
        else if (token == "--flipH" || token == "-h") {
            args.flipH = true;
        }
        else if (token == "--flipV" || token == "-v") {
            args.flipV = true;
        }

        // -------- BRIGHTEN --------
        else if (token == "--brighten" || token == "-b") {

            if (i + 1 >= argc) {
                throw runtime_error("--brighten requires an integer value");
            }

            string value = argv[++i];

            if (is_option(value)) {
                throw runtime_error("--brighten expected a value but got option " + value);
            }

            int num = to_int(value, "--brighten");

            if (num < -255 || num > 255) {
                throw runtime_error("brighten must be in [-255, 255]");
            }

            args.use_brighten = true;
            args.brighten = num;
        }

        // -------- ROTATE --------
        else if (token == "--rotate" || token == "-r") {

            if (i + 1 >= argc) {
                throw runtime_error("--rotate requires an integer value");
            }

            string value = argv[++i];

            if (is_option(value)) {
                throw runtime_error("--rotate expected a value but got option " + value);
            }

            int num = to_int(value, "--rotate");

            if (num != 0 && num != 90 && num != 180 && num != 270) {
                throw runtime_error("rotate must be one of {0, 90, 180, 270}");
            }

            args.use_rotate = true;
            args.rotate = num;
        }

        // -------- UNKNOWN --------
        else {
            throw runtime_error("unknown option " + token);
        }
    }

    return args;
}

// print results
void Args::print() const {

    cout << "INPUT  : " << input << endl;
    cout << "OUTPUT : " << output << endl;

    cout << "FLAGS  : ";
    if (grayscale) cout << "grayscale ";
    if (blur) cout << "blur ";
    if (flipH) cout << "flipH ";
    if (flipV) cout << "flipV ";
    cout << endl;

    cout << "PARAMS : ";
    if (use_brighten) cout << "brighten=" << brighten << " ";
    if (use_rotate) cout << "rotate=" << rotate << " ";
    cout << endl;
}