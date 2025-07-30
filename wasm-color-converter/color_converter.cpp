#include <emscripten/bind.h>
#include <algorithm> // for std::max and std::min

using namespace emscripten;

// Define a struct to hold RGB values (not strictly necessary for this example, but good practice)
struct Color {
    int r; // Red (0-255)
    int g; // Green (0-255)
    int b; // Blue (0-255)
};

// Define a struct to hold HSL values
struct HSL {
    double h; // Hue (0-360 degrees)
    double s; // Saturation (0-100%)
    double l; // Lightness (0-100%)
};

// Function to convert RGB to HSL
HSL rgbToHsl(int r, int g, int b) {
    // Normalize RGB values to [0, 1]
    double rd = r / 255.0;
    double gd = g / 255.0;
    double bd = b / 255.0;
    
    // Find the maximum and minimum of the RGB values
    double max = std::max({rd, gd, bd});
    double min = std::min({rd, gd, bd});
    
    // Initialize HSL values
    double h = 0.0, s = 0.0, l = (max + min) / 2.0;

    // If max equals min, the color is achromatic (gray), so hue and saturation are 0
    if (max == min) {
        h = s = 0.0; // Achromatic
    } else {
        // Calculate saturation
        double d = max - min;
        s = (l > 0.5) ? d / (2.0 - max - min) : d / (max + min);
        
        // Calculate hue based on which color is max
        if (max == rd) {
            h = (gd - bd) / d + (gd < bd ? 6.0 : 0.0);
        } else if (max == gd) {
            h = (bd - rd) / d + 2.0;
        } else if (max == bd) {
            h = (rd - gd) / d + 4.0;
        }
        h /= 6.0; // Normalize hue to [0, 1]
    }

    // Create and return HSL struct
    HSL result;
    result.h = h * 360.0; // Convert hue to degrees (0-360)
    result.s = s * 100.0; // Convert saturation to percentage (0-100)
    result.l = l * 100.0; // Convert lightness to percentage (0-100)
    
    return result;
}

// Expose the HSL struct and rgbToHsl function to JavaScript using Embind
EMSCRIPTEN_BINDINGS(my_module) {
    value_object<HSL>("HSL")
        .field("h", &HSL::h) // Expose h field
        .field("s", &HSL::s) // Expose s field
        .field("l", &HSL::l); // Expose l field
        
    function("rgbToHsl", &rgbToHsl); // Expose rgbToHsl function
}