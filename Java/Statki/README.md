# 🚢 Battleship Game (Java / Swing)

A desktop implementation of the classic Battleship game written in Java using Swing.  
The project supports different game modes including single-player (vs AI) and multiplayer (human vs human via network client).

---

## ▶️ How to use

1. Clone or download the repository:

git clone [<repository-url>](https://github.com/sadowski-pawel/Projects)


2. Open the project in your Java IDE (e.g. IntelliJ IDEA or Eclipse)

3. Make sure the project SDK is set to Java 8+ (or newer)

4. Run the `Server` class first  
   Then run `Start.java`
   
5. Choose game mode (AI or multiplayer) and start playing

---

### 💡 Notes

- The game uses Java Swing, so no additional dependencies are required
- For multiplayer mode, make sure the server/client connection is properly configured


## 🎯 Project goal

The goal of this project is to build a fully playable Battleship game with:

- graphical user interface (Swing)
- turn-based gameplay system
- ship placement phase
- game state management
- optional network multiplayer support

---


## ⚙️ Features

- GUI built with Java Swing
- two game modes:
  - Human vs Computer (AI)
  - Human vs Human (network mode)
- ship placement system
- turn-based battle system
- game phases:
  - placing ships
  - gameplay
  - game over
- win detection system
- board visualization for both players
- event-driven architecture (mouse + buttons)

---

## 🧠 Game architecture

The game is structured using multiple components:

- `Start` – application entry point (main class)
- `Game` – main window and game controller
- `BoardPanel` – graphical representation of the game board
- `Player` – abstract player logic
- `HumanPlayer` – user-controlled player
- `ComputerPlayer` – AI opponent
- `GameClient` – network communication (multiplayer mode)
- `HandlingEvent` – event handling (mouse + UI actions)
- `GameControlPanel` – ship selection and game controls

---

## 🔁 Game flow

1. Game starts in **SHIP PLACEMENT PHASE**
2. Player places ships on the board
3. AI or second player is initialized
4. Game switches to **GAME PHASE**
5. Players take turns attacking coordinates
6. First player to destroy all enemy ships wins

---

## 🎮 Controls

- Mouse click – place ships / attack enemy board
- Buttons:
  - select ship type
  - start game
  - import / export board

---

## 🧩 Game states

The game uses a state machine:

- `PLACING_SHIPS` – setup phase
- `GAME` – active gameplay
- `GAME_OVER` – end of match

---

## 🌐 Multiplayer mode

When running in `VS_HUMAN` mode:
- network client (`GameClient`) is started
- game listens for remote actions
- turn synchronization is handled via server/client communication

---

## 🌐 Multiplayer (Network mode)

To play in **Human vs Human** mode, you must start the server first.

### Steps:

1. Start the server application
2. Wait until the server is running and listening for connections
3. Run the game (`Start.java`)
4. Select **VS_HUMAN** mode
5. The client will automatically connect to the server

---

### ⚠️ Important

- The server must be running before starting the game
- If the server is not active, multiplayer mode will not work
- Both players must be connected to the same server instance


## 🧱 Project structure


start/
Start.java
Game.java

model/
Player.java
HumanPlayer.java
ComputerPlayer.java
Board.java
Ship.java

ui/
BoardPanel.java
GameControlPanel.java
HandlingEvent.java

client/
GameClient.java

config/
GameAssets.java

