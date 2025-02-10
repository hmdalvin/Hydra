# Contributing to Hydra Video Converter

Thank you for your interest in contributing to Hydra Video Converter! Follow the guidelines below to ensure a smooth contribution process.

## How to Contribute

### 1. Fork and Clone the Repository

First, fork the repository on GitHub and clone it to your local machine:

```sh
git clone https://github.com/yourusername/hydra-video-converter.git
cd hydra-video-converter
```

### 2. Create a New Branch

Always create a new branch for your changes:

```sh
git checkout -b feature-name
```

### 3. Install Dependencies

Ensure all necessary dependencies are installed:

```sh
cmake -S . -B build -G "MinGW Makefiles"
cmake --build build
```

For Linux/macOS:

```sh
cmake -S . -B build -G "Unix Makefiles"
cmake --build build
```

### 4. Make Your Changes

Modify the necessary files and test your changes before committing.

### 5. Commit and Push

Commit your changes with a meaningful message:

```sh
git add .
git commit -m "Added new feature X"
git push origin feature-name
```

### 6. Create a Pull Request

Go to GitHub, navigate to your forked repository, and create a pull request against the `main` branch of the original repository.

## Code Guidelines

- Follow the project’s coding style.
- Keep commits small and well-documented.
- Ensure your changes do not break existing functionality.

## Reporting Issues

If you find a bug or have a feature request, open an issue on GitHub:

[GitHub Issues](https://github.com/yourusername/hydra-video-converter/issues)

Thank you for contributing! 🚀
