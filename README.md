<p align="center">
  <h1 align="center">CATCH THE FALLING BALLS</h1>
  <p align="center">A terminal-based falling ball game built with C and ncurses</p>
</p>

<p align="center">
  <a href="LICENSE.txt"><img src="https://img.shields.io/badge/license-MIT-blue.svg" alt="License: MIT"></a>
  <img src="https://img.shields.io/badge/language-C-gray.svg" alt="Language: C">
  <img src="https://img.shields.io/badge/platform-Linux-lightgrey.svg" alt="Platform: Linux">
</p>

<p align="center">
  <a href="README.ja.md">日本語</a>
</p>

---

**CATCH THE FALLING BALLS** is a fast-paced terminal game where you control a basket to catch falling balls within a 30-second time limit. Built entirely in C with the ncurses library, it runs directly in your terminal — no GUI required.

## Features

- **Simple, addictive gameplay** — Move the basket with arrow keys and catch as many balls as possible
- **Fever Time** — Chain 8 consecutive catches to activate Fever Time, doubling your score and time bonuses for 8 seconds
- **Two ball types** — Normal balls (`o`) grant +1 score / +0.8s; special balls (`*`) grant +3 score / +2s
- **Persistent leaderboard** — Top 3 scores are saved locally as a CSV file
- **Runs anywhere** — Any Linux terminal with ncurses support (minimum 75×17)

## Quick Start

### Prerequisites

- GCC
- GNU Make
- ncurses development libraries
- Japanese locale (`ja_JP.UTF-8`)

**Ubuntu / Debian:**

```bash
sudo apt install build-essential libncurses5-dev libncursesw5-dev locales
sudo locale-gen ja_JP.UTF-8
```

### Build & Run

```bash
cd src
make start
```

This compiles the project and launches the game. To compile without running:

```bash
cd src
make game
```

To clean build artifacts:

```bash
cd src
make clean
```

### Using Dev Container

A Dev Container configuration is included for a fully reproducible development environment. Open the project in VS Code with the [Dev Containers extension](https://marketplace.visualstudio.com/items?itemName=ms-vscode-remote.remote-containers), and all dependencies will be set up automatically.

## How to Play

| Action | Key |
|--------|-----|
| Move basket left | ← |
| Move basket right | → |
| Quit game | `q` |

### Scoring

| Event | Score | Time |
|-------|-------|------|
| Catch normal ball (`o`) | +1 | +0.8s |
| Catch special ball (`*`) | +3 | +2.0s |
| Miss a ball | — | −1.0s |

### Fever Time

Catch **8 balls in a row** to trigger Fever Time (8 seconds). During Fever Time:
- All score and time bonuses are **doubled**
- Missing a ball does **not** deduct time

## Project Structure

```
.
├── .devcontainer/           # Dev Container configuration
│   ├── Dockerfile
│   └── devcontainer.json
├── src/
│   ├── main.c               # Entry point, ncurses initialization
│   ├── catch_the_falling_balls.c  # Core game loop and mechanics
│   ├── game_sup_func.c      # Scoring, results, save/load
│   ├── scr_sup_func.c       # Screen rendering and UI helpers
│   ├── file_io.c            # CSV file I/O
│   ├── makefile
│   └── rw_file/
│       ├── hist_scores.csv  # Persistent score data
│       └── help.txt         # In-game help text (Japanese)
├── LICENSE.txt
├── README.md                # English
└── README.ja.md             # 日本語
```

## Technical Details

- **Language:** C (C99)
- **UI Library:** ncursesw
- **Timing:** Millisecond precision via `gettimeofday()`
- **Play area:** 20×12 characters
- **Game duration:** 30 seconds
- **Minimum terminal size:** 75 columns × 17 rows

## License

This project is licensed under the MIT License. See [LICENSE.txt](LICENSE.txt) for details.

## Author

Kosuke Baba
