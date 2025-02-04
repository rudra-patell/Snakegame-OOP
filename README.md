# Snake Game by Team Falcons

## Introduction

This is a **console-based Snake Game** developed in C++ using the Windows API for handling console operations such as cursor movement and screen clearing. The game includes dynamic grid resizing, difficulty levels, real-time high-score tracking, and an interactive menu system.

---

## Enviroment Details

- This game was devloped specifically to work with **Windows** and also includes some of the features from the Windows api library
  
---

## Features

- **Classic Snake Gameplay**: Navigate the snake to eat food and grow in size.
- **Dynamic Grid Size**: Users can set their preferred grid size (width × height).
- **Multiple Difficulty Levels**: Choose from Easy, Medium, and Hard.
- **Persistent High Score**: Stores the highest score in a file.
- **Smooth Console Graphics**: Uses ASCII characters for rendering.
- **Restart and Quit Options**: Restart the game upon game over.

---

## How the Game Works

### 1️⃣ **Game Initialization**

- The program starts by reading game settings from `userdata.txt`.
- If the file does not exist, it is created with default values (`Width: 50, Height: 25, High Score: 0`).

### 2️⃣ **Start Menu**

Users can choose from:

1. **Start Game**: Begins gameplay.
2. **Set Difficulty**: Adjusts game speed (1-Easy, 2-Medium, 3-Hard).
3. **Set Grid Size**: Allows users to modify grid dimensions (min: 15×15, max: 75×30 is suggested).
4. **Exit Game**: Closes the application.

### 3️⃣ **Gameplay Mechanics**

- The snake moves continuously in the selected direction (`WASD` keys to change direction).
- If the snake collides with the **border** or **itself**, the game ends.
- Eating food increases the snake's length and score.
- The game updates the **highest score** in `userdata.txt` in real time.

### 4️⃣ **Game Over Handling**

- The **"Game Over" screen** displays the score and high score.
- Users can **Restart** (`R`) or **Quit** (`Q`).

---

## Code Overview

### 🔹 **File Handling (`writedata()` & `readdata()`)**

- Stores **grid size** and **high score** in `userdata.txt`.
- Reads and writes game settings persistently.

### 🔹 **Game Logic (Classes)**

#### **1. Game Class**

Handles:

- Game state (game over or running)
- Score tracking
- Food consumption status

#### **2. Snake Class**

Handles:

- Movement and direction control
- Collision detection (self and walls)
- Growth mechanism when eating food

#### **3. Food Class**

Handles:

- Randomized placement of food within the grid
- Ensures food does not spawn on the snake

### 🔹 **Rendering and Input Handling**

- `display()`: Draws the **snake**, **food**, and **borders** on the console.
- `input()`: Captures player movement using **W, A, S, D** keys.

### 🔹 **Game Flow Control**

- The **main loop** continuously updates the game state.
- Uses `Sleep()` to control speed based on difficulty.
- `goto RESTART;` handles restarts without terminating the program.

---

## How to Compile and Run

### **🔧 Compilation (Windows Only)**

1. Open a terminal or **Command Prompt**.
2. Run the following command to compile:
   ```sh
   g++ main.cpp -o Snake_game.exe
   ```
3. Execute the game:
   ```sh
   Snake_game.exe
   ```

---

## Controls

| Key | Action       |
| --- | ------------ |
| W   | Move Up      |
| A   | Move Left    |
| S   | Move Down    |
| D   | Move Right   |
| R   | Restart Game |
| Q   | Quit Game    |

---

## Future Improvements

- Implementing a **pause** option.
- Adding **more obstacles** for higher difficulty.
- Improving **graphical representation** using external libraries.

---

## Credits

Developed by **Team Falcons** 🚀

This file was created by the team, with some parts of the code implemented based on solutions from Stack Overflow.

Rudra Patel        - 202404028 (G6)  
Pranav Patel       - 202404051 (G6)  
Devanshi Modi      - 202401498 (G6)  
Deep Sutariya      - 202401219 (G4)
