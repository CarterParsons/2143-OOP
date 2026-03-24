#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include <iostream>
#include <string>

#include "stb_image.h"
#include "stb_image_write.h"
#include "termcolor.hpp"
#include <cstdlib>

using namespace std;
using namespace termcolor;

// ------------------------------------------------------------
// Program 1 (Starter):
// - Uses argv[1] argv[2] for input/output
// - Loads an image, converts it to grayscale, saves as PNG
//
// YOU will add:
//   (A) termcolor for colored messages
//   (B) a function to open the output image automatically
// ------------------------------------------------------------

bool open_file_default_app(const string& path) {
#if defined(_WIN32)
    string cmd = "start \"\" \"" + path + "\"";
#elif defined(__APPLE__)
    string cmd = "open \"" + path + "\"";
#else
    string cmd = "xdg-open \"" + path + "\"";
#endif
    return system(cmd.c_str()) == 0;
}

int main(int argc, char* argv[]) {

    if (argc < 3) {
        cout << red << "Usage: " << blue
     << "./imgtool <input_image> <output_image>\n"
     << reset;
        return 1;
    }

    string inputPath  = argv[1];
    string outputPath = argv[2];

    int width = 0, height = 0, channels_in_file = 0;

    // Force RGB (3 channels)
    unsigned char* data = stbi_load(inputPath.c_str(),
                                    &width,
                                    &height,
                                    &channels_in_file,
                                    3);

    if (!data) {
        cerr << red << "Failed to load image: " << reset
     << inputPath << "\n";
        return 1;
    }

    const int channels = 3;
    const int totalPixels = width * height;

    cout << "Loaded image: " << width << "x" << height
              << " channels: " << channels << "\n";

    // Hardcoded grayscale (luminance)
    for (int i = 0; i < totalPixels; ++i) {
        int idx = i * channels;

        int r = data[idx + 0];
        int g = data[idx + 1];
        int b = data[idx + 2];

        int gray = static_cast<int>(0.299 * r + 0.587 * g + 0.114 * b);

        // gray will already be in [0,255] for this formula
        unsigned char gr = static_cast<unsigned char>(gray);

        data[idx + 0] = gr;
        data[idx + 1] = gr;
        data[idx + 2] = gr;
    }

    // Save PNG
    if (!stbi_write_png(outputPath.c_str(),
                        width,
                        height,
                        channels,
                        data,
                        width * channels)) {

        cerr << "Failed to write output image: " << outputPath << "\n";
        stbi_image_free(data);
        return 1;
    }

    stbi_image_free(data);

    cout << green << "Saved output to: " << yellow
     << outputPath << reset << "\n";

    cout << cyan << "Opening output in default viewer...\n" << reset;
    if (!open_file_default_app(outputPath)) {
    cout << red << "Warning: could not launch viewer automatically.\n"
     << reset;
}

    return 0;
}