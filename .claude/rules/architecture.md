# Architecture

## Program Flow

```
main() → initscr() → start_scr() [menu loop]
  ├─ Play    → play_game() → init_game() → game loop → result() → save_score()
  ├─ Scores  → load_scores()
  ├─ Help    → load_game_help()
  └─ Exit    → exit_scr()
→ endwin()
```

## Module Responsibilities

| Module | Role |
|--------|------|
| `main.c` | ncurses initialization, locale setup, menu entry |
| `falling_balls.c` | Game loop, input handling, ball spawning/movement, collision detection, fever mode |
| `game_sup_func.c` | Result screen, score saving, CSV update logic, username input |
| `scr_sup_func.c` | Menu rendering, help screen, scores display, exit confirmation, terminal size check |
| `file_io.c` | Low-level CSV/text file reading and writing |

## Key Data Structures

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

## Game Constants

- Play area: 20x12 characters
- Basket: 3 chars wide (`|_|`)
- Ball drop interval: 400ms
- Game duration: 30 seconds
- Fever trigger: 8 consecutive catches (lasts 8 seconds, 2x scoring)
- Max balls array: 10,000
- Minimum terminal size: 75 columns x 17 rows
