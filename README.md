# HashBosseCat Password Recovery Tool
### Built using C++, Qt Framework, openSSL and CMake.

## Introduction
Welcome to `hash-bosse-cat`, a sophisticated password recovery tool developed with the cutting-edge C++20 standards and the robust Qt framework for desktop GUI. Inspired by the agility and sharpness of a cat named Bosse, this tool aims to provide a sleek, user-friendly interface coupled with powerful wordlist-based hash cracking algorithms.

## Features
- **Modern C++20**: Utilizes the latest language features for optimal performance and code clarity.
- **Qt Framework**: Offers a responsive and intuitive user interface.
- **OpenSSL Library Integration**: Employs the OpenSSL library for secure and efficient hashing of strings.
- **Wordlist-Based Cracking**: Leverages comprehensive wordlists for efficient hash cracking.
- **Salt Wordlists**: Built in function to add common salts and create variation of each string in wordlists.
- **Support for Multiple Hash Types**: Compatible with a variety of hashing algorithms.
- **Cross-Platform**: Works seamlessly on multiple operating systems thanks to the QT framework.

## Getting Started
These instructions will get you a copy of the project up and running on your local machine for development and testing purposes.

### Prerequisites
- C++20 compatible compiler (Clang, GCC etc.)
- Qt Framework v6.6.1
- CMake & Ninja [optional] (included in Qt Framework)

### Installing
1. **Clone the repository**
    ```bash
    git clone https://github.com/simonthorell/hash-bosse-cat.git
    ```
2. **Navigate to the project directory**
    ```bash
    cd hash-bosse-cat
    ```
3. **Build the project using VS Code**
    - Open the project folder in Visual Studio Code.
    - Ensure you have the CMake Tools and C++ extensions installed.
    - Configure the project by selecting the appropriate kit (compiler, platform, etc.) from the CMake Tools extension.
    - Build the project by invoking the build command from the CMake Tools extension.
    - If necessary, refer to the VS Code documentation for detailed instructions on setting up and using CMake Tools.

4. **Modify the GUI**
    - Use the Qt Creator IDE to get a graphic tool for modifying the .ui files.

## Usage
- Launch the application after successful installation.
- Follow the on-screen instructions to input the hash values.
- Load your wordlist file through the GUI.
- Select the appropriate hash type and start the recovery process. Monitor the progress through the interactive UI.

## Contributing
Contributions are what make the open-source community such an amazing place to learn, inspire, and create. Any contributions you make are **greatly appreciated**.

1. Fork the Project
2. Create your Feature Branch (`git checkout -b feature/AmazingFeature`)
3. Commit your Changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the Branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

## License
Distributed under the MIT License. See `LICENSE` for more information.

## Acknowledgements
- Hats off to Bosse, the cat! Her knack for naps and cozy vibes turn coding marathons into a purr-fest. She's the silent, fluffy cheerleader behind our sleek, efficient code. Cheers to Bosse, our whiskered muse and relaxation guru!

Happy Cracking!