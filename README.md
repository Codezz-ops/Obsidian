# Obsidian
Obsidian is a high-level programming language.

To propose an improvement, kindly open an issue with the prefix SUGGESTION: and detail your insight. Your contributions are greatly appreciated!

## Features

- **high-level**: Obsidian rovides a high-level abstraction, allowing developers to write code that is closer to human-readable language.
- **Dynamic Typing**: Variables in Obsidian are dynamically typed, meaning their types are determined at runtime.
- **File Extension**: Obsidian source files have the extension `.ob`.

## Installation
To start using Obsidian, follow the installation guide below:

- Windows: install chocolatey [chocolatey](https://chocolatey.org/).    
    ```
    .\install\install.ps1
    ```

- Linux: install packages
    ```
    bash install/install.sh
    ```

## Build
To start using Obsidian, follow the build guide below:
    
- Windows: 
    ```
    cmake -S . -B build -G "MinGW Makefiles"
    cmake --build build
    ```

- Linux:
    ```
    cmake -S . -B build
    cmake --build build
    ```

## Usage
```
./build/obsidian <filename>
```
