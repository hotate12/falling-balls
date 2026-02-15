# CLAUDE.md

## Project Overview

**CATCH THE FALLING BALLS** is a terminal-based falling ball game written in C using the ncurses library. Players move a basket with arrow keys to catch falling balls within a 30-second time limit. Features a "Fever Time" mechanic that doubles scoring after consecutive catches. UI text is in Japanese.

## Technology Stack

- **Language:** C (C99)
- **UI Library:** ncurses / ncursesw
- **Build System:** GNU Make
- **Compiler:** GCC
- **Target OS:** Ubuntu 20.04 LTS (via devcontainer)
- **Locale:** ja_JP.UTF-8

## Project Structure

```
.
├── .devcontainer/          # Docker dev environment
│   ├── Dockerfile          # Ubuntu 20.04 + ncurses + Japanese locale
│   └── devcontainer.json
├── src/                    # All source code
│   ├── main.c / main.h                    # Entry point, ncurses init, menu loop
│   ├── catch_the_falling_balls.c / .h     # Core game logic, game loop, ball physics
│   ├── game_sup_func.c / .h               # Scoring, results, save/update scores
│   ├── scr_sup_func.c / .h                # Screen helpers: help, scores, exit dialogs
│   ├── file_io.c / .h                     # CSV read/write for score persistence
│   ├── makefile                           # Build configuration
│   └── rw_file/                           # Runtime data files
│       ├── hist_scores.csv                # Ranking + history (6 rows: 3 ranking, 3 history)
│       └── help.txt                       # In-game help text (Japanese)
├── LICENSE.txt             # MIT License
└── README.md
```

## Build & Run

All commands must be run from the `src/` directory:

```bash
cd src

# Compile only
make game

# Compile and run
make start

# Clean build artifacts
make clean
```

The makefile compiles each `.c` file to `.o`, then links with `-lncursesw`.

**Build dependencies:** `build-essential`, `libncurses5-dev`, `libncursesw5-dev`, `locales` (Japanese)

## Architecture

### Program Flow

```
main() → initscr() → start_scr() [menu loop]
  ├─ Play    → play_game() → init_game() → game loop → result() → save_score()
  ├─ Scores  → load_scores()
  ├─ Help    → load_game_help()
  └─ Exit    → exit_scr()
→ endwin()
```

### Module Responsibilities

| Module | Role |
|--------|------|
| `main.c` | ncurses initialization, locale setup, menu entry |
| `catch_the_falling_balls.c` | Game loop, input handling, ball spawning/movement, collision detection, fever mode |
| `game_sup_func.c` | Result screen, score saving, CSV update logic, username input |
| `scr_sup_func.c` | Menu rendering, help screen, scores display, exit confirmation, terminal size check |
| `file_io.c` | Low-level CSV/text file reading and writing |

### Key Data Structures

```c
typedef struct {
    int x, y;
    int next_drop_timing;
    bool active, flag, special_ball;
} Ball;

typedef struct {
    char date[24];
    int score;
    char name[32];
} database;
```

### Game Constants

- Play area: 20×12 characters
- Basket: 3 chars wide (`|_|`)
- Ball drop interval: 400ms
- Game duration: 30 seconds
- Fever trigger: 8 consecutive catches (lasts 8 seconds, 2× scoring)
- Max balls array: 10,000
- Minimum terminal size: 75 columns × 17 rows

## Code Conventions

- **Naming:** `snake_case` for functions and variables; `UPPER_CASE` for constants
- **Brace style:** K&R
- **Function prefixes:** `init_*` (initialization), `*_scr` (screen/UI), `load_*` (file loading)
- **State management:** Global variables in `catch_the_falling_balls.c` for game state (`x`, `y`, `score`, `game_time`, `catch_count`, `fever_active`)
- **Compiler warnings:** Suppressed with `-w` flag
- **Comments:** Minimal; Japanese text in UI strings and help files

## File I/O

- **Paths are relative** — the game expects to be run from `src/` so `./rw_file/` resolves correctly
- CSV format: `date,score,name` with 6 rows (3 ranking + 3 history)
- Score display limited to 3 digits (max 999)
- Username input limited to 28 characters

## Testing

No automated tests. Validation is done through manual gameplay. The game requires a terminal with ncurses support, so it cannot run in headless/CI environments without a virtual terminal.

## Important Notes

- The game uses `gettimeofday()` for millisecond-precision timing
- Japanese locale (`ja_JP.UTF-8`) is required for proper text rendering
- Color pairs are used for UI feedback: red text in last 5 seconds, blue during fever mode
- The devcontainer Dockerfile handles all environment setup automatically
