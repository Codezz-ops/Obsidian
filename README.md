# Obsidian
Obsidian is a high-level programming language.

<p align="center">
    <img src="images/0BBATIZ.png" alt="obsidian logo">
</p>

<!-- TOC -->
- [Features](#features)
- [Installation](#installation)
    - [Build](#build)
- [Usage](#usage)
- [Examples](#examples)
    - [Hello, World](#hello-world)
    - [Error Handling](#error-handling)
- [Contribute](#contributing)
- [License](#license)
<!-- TOC -->

## Features

- **high-level**: Obsidian provides a high-level abstraction, allowing developers to write code that is closer to human-readable language.
- **Dynamic Typing**: Variables in Obsidian are dynamically typed, meaning their types are determined at runtime.
- **File Extension**: Obsidian source files have the extension `.ob`.

## Installation
To start using Obsidian, follow the installation guide below:

<details>
<summary>Windows</summary>

install chocolatey [chocolatey](https://chocolatey.org/). 

<code>.\install\install.ps1</code>

</details>

<details>
<summary>Linux</summary>

<code>./install/install.sh</code>

</details>

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

## Examples

### Hello, world!
```
fn main() {
    print("Hello, world!");
    exit(0);
}
```

### Error Handling
```
Error: [line: 2, column: 30] Unexpected character: ~
    2 |     print("Hello, world!\n");~
      |                              ^

```

## Contributing
If you find any bugs or want to contribute to Obsidian, please feel free to open an issue or submit a pull request on the GitHub repository. We welcome your feedback and suggestions to make this tool even better.

## License
Obsidian is open-source software licensed under the [GNUv2](https://github.com/Codezz-ops/Obsidian/blob/main/LICENSE) License. You are free to use, modify, and distribute this software with proper attribution and in compliance with the license terms.

