![](.github/banner.png)

<center>

![Language](https://img.shields.io/badge/Language-C++-purple?style=for-the-badge)
![Stars](https://img.shields.io/github/stars/mallory-scotton/NetworkAbyss?style=for-the-badge&color=orange)
![Language](https://img.shields.io/github/contributors/mallory-scotton/NetworkAbyss?style=for-the-badge)
![Code Size](https://img.shields.io/github/languages/code-size/mallory-scotton/NetworkAbyss?style=for-the-badge)
[![SFML](https://img.shields.io/badge/SFML-3.0.0-8AC83A?style=for-the-badge)](https://github.com/SFML/SFML)
[![Dear ImGui](https://img.shields.io/badge/Dear%20ImGui->=1.91.1-blue?style=for-the-badge)](https://github.com/ocornut/imgui)
![Last Commit](https://img.shields.io/github/last-commit/mallory-scotton/NetworkAbyss?style=for-the-badge)
![License](https://img.shields.io/github/license/mallory-scotton/NetworkAbyss?style=for-the-badge)
![Forks](https://img.shields.io/github/forks/mallory-scotton/NetworkAbyss?style=for-the-badge)

</center>

# 🎮 Network Abyss

**Network Abyss** is a **multiplayer remake** of [_Neon Abyss_](https://store.steampowered.com/app/788100/Neon_Abyss),
developed as part of a school project at **Epitech**.
This project aims to faithfully replicate the base game while introducing exciting new **multiplayer features**, including:

- **Co-op Mode** - Team up with friends and tackle the chaos together.
- **Versus Mode** - Compete against each other in intense battles.

Built with **C++**, **SFML**, and **Zlib**, this project brings fast-paced roguelike action to a networked experience! 🚀🎮

Would you like to add more details about gameplay or technical aspects? 😊

## 📌 Table Of Content

- [⚙️ Installation](#️-installation)
    - [Prequesites](#prequesites)
    - [Installation Steps](#installation-steps)
- [✨ Features](#-features)
    - [🕹️ Game](#️-game)
    - [🛰️ Game Server](#️-game-server)
    - [📦 Assets Packer](#-assets-packer)
- [🖼️ Gallery](#-gallery)
- [📄 Documentation](#-documentation)
- [🔗 Dependencies](#-dependencies)
- [📂 Sources](#-sources)
- [🤝 Contribute](#-contribute)
- [👥 Authors](#-authors)
- [📜 License](#-license)

## ⚙️ Installation

### Prequesites

Make sure you have the following installed on your system:

- **C++ Compiler** (g++, clang, or MSVC)
- **Make** (build automation tool)
- **SFML** (Simple and Fast Multimedia Library)
- **ZLib** (Compression library)

### Installation Steps

#### 1️⃣ Install Dependencies

Ubuntu/Debian:
```sh
sudo apt update
sudo apt install g++ make libsfml-dev zlib1g-dev
```

Arc Linux:
```sh
sudo pacman -S base-devel sfml zlib
```

MacOS (Homebrew):
```sh
brew install sfml zlib
```

Windows (MSYS2 - MinGW64):
```sh
pacman -S mingw-w64-x86_64-gcc mingw-w64-x86_64-make mingw-w64-x86_64-sfml mingw-w64-x86_64-zlib
```

#### 2️⃣ Clone the Repository

```sh
git clone https://github.com/mallory-scotton/NetworkAbyss
cd NetworkAbyss
```

#### 3️⃣ Build the Project

```sh
make            # Build all the components (game, server, packer)

# Or individually build the components

make build      # Build the game
make server     # Build the game server
make packer     # Build the assets packer
```

#### 4️⃣ Run the Game

```sh
./network-abyss
```

#### 5️⃣ Clean Up (Optional)

```sh
make clean      # Simple clean up
make fclean     # Full clean up
```

## ✨ Features

### 🕹️ Game

- [x] Game state manager
    - [ ] Menu
    - [ ] Server browser
    - [ ] Play
    - [ ] Map
    - [ ] Connection
    - [ ] Settings
- [x] Resources manager
    - [x] Unpack resources
    - [ ] Access cached resources
- [ ] Physics engine
    - [ ] Gravity
    - [ ] Friction
    - [ ] Air control
    - [ ] Forces
- [x] Network client
    - [x] Packet handling
    - [ ] Position interpolation
- [x] Debug mode
- [ ] Player
    - [ ] Movement
        - [ ] Right / Left
        - [ ] Jump
        - [ ] Fly
    - [ ] Replication
    - [ ] Abilities
    - [ ] Weapons
        - [ ] Shooting
        - [ ] Active capacity
        - [ ] Passive capacity
- [ ] Enemies
    - [ ] Basic enemies
    - [ ] Bosses
- [ ] Levels
    - [ ] Generator
    - [ ] Seed based
    - [ ] Rendering
    - [ ] Props
        - [ ] Doors
        - [ ] Chests
        - [ ] Breakables
- [ ] Collection system
- [ ] Achievements system
- [ ] Animation controller
- [ ] Audio system
    - [ ] Multi channel
- [ ] Chat system
- [ ] Inventory
    - [ ] Currencies
    - [ ] Statistics

### 🛰️ Game Server

- [x] TCP Protocol
    - [x] Packet broadcasting
    - [x] Socket connection
    - [x] Client identification
    - [ ] Server authority
    - [ ] Anti-Cheat system
- [x] UDP Server Discovery
    - [x] Broadcast Ip Address and Port
- [x] Custom port
- [ ] Integrated server in client

### 📦 Assets Packer

- [x] Compression using `zlib`
- [x] Pack `.pak` file
- [x] Unpack `.pak` file
- [x] Adding Assets
    - [x] Adding Image
    - [x] Adding Sound
    - [x] Adding Font
    - [x] Adding Raw Data
    - [ ] Custom key
- [x] Clearing the packer
- [x] Extract
    - [x] Extract Image
    - [ ] Extract Sound
    - [ ] Extract Font
    - [ ] Extract RawData
- [ ] Resources group
- [ ] Resources caching
- [x] Displaying information

## 🖼️ Gallery

_Coming soon..._

## 📄 Documentation

_Coming soon..._

## 🔗 Dependencies

_Coming soon..._

## 📂 Sources

_Coming soon..._

## 🤝 Contribute

_Coming soon..._

## 👥 Authors

- [🐵 Mallory SCOTTON](https://github.com/mallory-scotton) _(Project Leader)_
- [🙈 Nathan FIEVET](https://github.com/natan-fievet)
- [🙉 Hugo CATHELAIN](https://github.com/Hugo-Cathelain)
- [🙊 Ossan MSOILI]()

## 📜 License

MIT License

Copyright (c) 2025 TekyoDrift

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
