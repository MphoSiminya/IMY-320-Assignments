#include <emscripten/bind.h>
#include <algorithm> // for std::max and std::min

using namespace emscripten;

// Define a struct to hold RGB values: easier use for later, for best practices.
struct Colour {
    int r; // Red 
    int g; // Green 
    int b; // Blue 
};

// Define a struct to hold the HSL values
struct HSL {
    double h; // Hue 
    double s; // Saturation
    double l; // Lightness
};

// Function to convert RGB colours to HSL colours 
HSL rgbToHsl(int r, int g, int b) {
    double rd = r / 255.0;
    double gd = g / 255.0;
    double bd = b / 255.0;

    // Find maximum and minimum of the RGB values
    double max = std::max({rd, gd, bd});
    double min = std::min({rd, gd, bd});

    // Initialize HSL values
    double h = 0.0, s = 0.0, l = (max + min) / 2.0;

    // If the max = min, the colour is gray, so hue and saturation are set to 0
    if (max == min) {
        h = s = 0.0; // this is the gray 
    } else {
        // Calculate saturation
        double d = max - min;
        s = (l > 0.5) ? d / (2.0 - max - min) : d / (max + min);

        // Calculate hue based on which colour is the max colour
        if (max == rd) {
            h = (gd - bd) / d + (gd < bd ? 6.0 : 0.0);
        } else if (max == gd) {
            h = (bd - rd) / d + 2.0;
        } else if (max == bd) {
            h = (rd - gd) / d + 4.0;
        }
        h /= 6.0; 
    }

    // Create and return HSL struct (created before)
    HSL result;
    result.h = h * 360.0; // Convert hue 
    result.s = s * 100.0; // Convert saturation 
    result.l = l * 100.0; // Convert lightness
    return result;
}

// Show the HSL struct and rgbToHsl function (created) to JavaScript using Embind
EMSCRIPTEN_BINDINGS(my_module) {
    value_object<HSL>("HSL")
        .field("h", &HSL::h) // show h field
        .field("s", &HSL::s) // show s field
        .field("l", &HSL::l); // show the l field

    function("rgbToHsl", &rgbToHsl); // show rgbToHsl function
}
