#include "Args.h"
#include <iostream>

using namespace std;

int main(int argc, char* argv[]) {
    try {
        Args args = Args::parse(argc, argv);
        args.print();
    }
    catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
        cout << "Usage: ./imgtool <input_image> <output_image> [options]" << endl;
        return 1;
    }

    return 0;
}