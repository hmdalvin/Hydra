# Installation Guide for Hydra Video Converter

This guide provides step-by-step instructions to install and set up Hydra Video Converter.

## Prerequisites

- **Operating System**: Windows, Linux, or macOS
- **Dependencies**:
  - [FFmpeg](https://ffmpeg.org/download.html) (required for video processing)
  - CMake (if building from source)
  - MinGW (for Windows) or GCC (for Linux/macOS)
  - GTK4 (for GUI support)

## Installation Steps

### Windows

1. **Install FFmpeg**:

   - Download FFmpeg from [FFmpeg official site](https://ffmpeg.org/download.html).
   - Extract the contents and add `ffmpeg/bin` to your system `PATH`.

2. **Install Dependencies**:

   - Install [MinGW](https://www.mingw-w64.org/) and ensure `gcc` is in your `PATH`.
   - Install GTK4 using MSYS2:
     ```sh
     pacman -S mingw-w64-x86_64-gtk4
     ```

3. **Clone and Build the Project**:

   ```sh
   git clone https://github.com/yourusername/hydra-video-converter.git
   cd hydra-video-converter
   cmake -S . -B build -G "MinGW Makefiles"
   cmake --build build
   ```

4. **Run the Application**:
   ```sh
   ./build/hydra_video_converter.exe
   ```

### Linux/macOS

1. **Install FFmpeg**:

   ```sh
   sudo apt install ffmpeg  # Debian/Ubuntu
   brew install ffmpeg      # macOS (Homebrew)
   ```

2. **Install Dependencies**:

   ```sh
   sudo apt install build-essential cmake libgtk-4-dev  # Linux
   brew install cmake gtk4                              # macOS
   ```

3. **Clone and Build the Project**:

   ```sh
   git clone https://github.com/yourusername/hydra-video-converter.git
   cd hydra-video-converter
   cmake -S . -B build -G "Unix Makefiles"
   cmake --build build
   ```

4. **Run the Application**:
   ```sh
   ./build/hydra_video_converter
   ```

## Troubleshooting

- Ensure FFmpeg is installed and available in your `PATH`.
- Make sure all dependencies are installed properly.
- If compilation fails, verify that CMake and the correct compiler are installed.

For more support, check the [GitHub Issues](https://github.com/yourusername/hydra-video-converter/issues).
