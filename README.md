# 🎮 SFML Game Template

A modern C++20 game project template using [SFML 3](https://www.sfml-dev.org/), ImGui-SFML for debug UI, and CMake for cross-platform builds.  
Designed to get you started quickly with a clean architecture for 2D game development.

---

## 🚀 Features

- 📦 **CMake-based** project with Debug and Release configuration support
- 🖼️ **SFML 3.0** for graphics, audio, input, and window management
- 🛠️ **ImGui (Dear ImGui)** integrated for in-game debug tools
- 🧳 Automatic copying of SFML DLLs and asset files in build output
- 🧼 Clear and extensible folder structure

---

## 🗂️ Project Structure

📁 external/
│ ├── SFML-3.0.0/
│ ├── imgui/
│ └── imgui-sfml/
📁 assets/
│ └── images/, sounds/, fonts/ ...
📁 src/
│ ├── main.cpp
│ ├── core/
│ ├── systems/
│ ├── ui/
│ └── utils/
│ 
📄 CMakeLists.txt

---

## 🧪 Build Instructions

### Prerequisites

- CMake ≥ 3.15
- A C++20-compatible compiler (e.g. MSVC, Clang, or GCC)
- SFML 3.0.0 (provided in `external/SFML-3.0.0`)
- (Optional) Visual Studio 2022 or CLion for IDE integration

### Steps

1. Clone the repository:
   git clone https://github.com/Najimandroid/Template_SFML.git

2. Generate the build files:
	cd SFML_Template
	cmake -B build -DCMAKE_BUILD_TYPE=Debug

3. Build:
	cmake --build build
