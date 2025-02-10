# Build Project with CMake

This guide explains how to configure, build, clean, and run a project using CMake with different build systems.

## 1. Running CMake Configuration

Run the following command to configure CMake:

```sh
cmake -S . -B build
```

If using **MinGW Makefiles**, use:

```sh
cmake -S . -B build -G "MinGW Makefiles"
```

## 2. Build Project

To build the project, run:

```sh
cmake --build build
```

If using **Makefiles**:

```sh
cd build
make
```

If using **MSBuild** (Windows):

```sh
cmake --build build --config Release
```

## 3. Clean Build Folder

To clean the build directory:

```sh
cmake --build build --target clean
```

If using **Makefiles**:

```sh
make clean
```

To completely remove the `build` folder:

```sh
rm -rf build
```

If using Windows (Command Prompt or PowerShell):

```sh
rmdir /s /q build
```

## 4. Running Build Program

To run the compiled program:

```sh
./build/program
```

If using Windows:

```sh
build\program.exe
```
