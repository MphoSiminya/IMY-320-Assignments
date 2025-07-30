# IMY-320-Assignments
---

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

