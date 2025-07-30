# IMY-320-Assignments
## RGB to HSL Converter with WebAssembly

This project demonstrates a WebAssembly (WASM) application that converts RGB color values to HSL using C++ compiled with Emscripten.

## Setup Instructions
1. Install Emscripten:
   ```bash
   git clone https://github.com/emscripten-core/emsdk.git
   cd emsdk
   ./emsdk install latest
   ./emsdk activate latest
   source ./emsdk_env.sh

### 🧠 Deeper Explanation of Key Concepts

1. **Why Use WASM for This?**
   - The RGB to HSL conversion involves floating-point math (divisions, comparisons, `std::max/min`). In C++, this is optimized and compiled to efficient WASM instructions. In JavaScript, the same computation would be slower, especially for large-scale tasks (e.g., processing thousands of pixels in an image). This project shows how WASM can handle math-heavy tasks efficiently.

2. **Embind’s Role**:
   - Without Embind, you’d need to manually manage memory and data passing between C++ and JavaScript, which is complex. Embind simplifies this by automatically handling the `HSL` struct and `rgbToHsl` function, making them feel like native JavaScript objects and functions.

3. **Why ES6 Modules?**
   - The `-s MODULARIZE=1 -s EXPORT_ES6=1` flags make the JavaScript output compatible with modern JavaScript modules (`import` syntax). This is cleaner and more maintainable than older approaches (like global variables).

4. **Security and the Server**:
   - Browsers block loading `.wasm` files from `file://` URLs for security reasons (to prevent malicious scripts). The Python server (`http://localhost:8000`) creates a proper HTTP environment, mimicking a real web server.

---

### Compile the C++ code:
   bashem++ --bind -O3 -o color_converter.js color_converter.cpp -s WASM=1 -s MODULARIZE=1 -s EXPORT_ES6=1

### Serve the application:
   bashpython3 -m http.server 8000

   Open http://localhost:8000 in a browser.

### Description
   This web app allows users to input RGB values (0-255) using sliders, displays the color in a box, and shows the computed HSL values (Hue: 0-360°, Saturation: 0-100%, Lightness: 0-100%). The RGB to HSL conversion is performed by C++ code compiled to WebAssembly, showcasing WASM’s performance benefits for computational tasks.

### Files
   #### index.html: The web interface with sliders and display elements.
   #### color_converter.cpp: C++ code for RGB to HSL conversion.
   #### color_converter.js and color_converter.wasm: Compiled output from Emscripten.
   #### README.md: This file.

