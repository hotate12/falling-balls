# Code Conventions

## Naming and Style

- **Naming:** `snake_case` for functions and variables; `UPPER_CASE` for constants
- **Brace style:** K&R
- **Function prefixes:** `init_*` (initialization), `*_scr` (screen/UI), `load_*` (file loading)
- **State management:** Global variables in `falling_balls.c` for game state (`x`, `y`, `score`, `game_time`, `catch_count`, `fever_active`)
- **Compiler warnings:** Suppressed with `-w` flag
- **Comments:** Minimal; Japanese text in UI strings and help files

## File I/O

- **Paths are relative** — the game expects to be run from `src/` so `./rw_file/` resolves correctly
- CSV format: `date,score,name` with 6 rows (3 ranking + 3 history)
- Score display limited to 3 digits (max 999)
- Username input limited to 28 characters
