# CLAUDE.md

## Project Overview

**Falling Balls** — Terminal-based falling ball game in C with ncurses. Players catch falling balls with arrow keys within 30 seconds. Features "Fever Time" (2x scoring after consecutive catches). UI text is in Japanese.

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
├── .claude/                # Claude Code configuration
│   ├── settings.json       # Hooks and permissions
│   ├── policies/           # Versioned policy files (TOML)
│   │   └── commit-message.toml
│   ├── skills/             # Custom skills
│   │   └── commit/         # /commit — Lucent Commits workflow
│   ├── hooks/              # Enforcement scripts
│   └── rules/              # Architecture and convention details
├── .devcontainer/          # Docker dev environment
├── src/                    # All source code
│   ├── main.c / .h
│   ├── falling_balls.c / .h
│   ├── game_result.c / .h
│   ├── ui.c / .h
│   ├── file_io.c / .h
│   ├── Makefile
│   └── data/               # Runtime data (scores CSV, help text)
├── LICENSE.txt
├── README.md
└── README.ja.md
```

## Build & Run

All commands from `src/`:

```bash
cd src
make game    # Compile
make start   # Compile and run
make clean   # Clean artifacts
```

**Dependencies:** `build-essential`, `libncurses5-dev`, `libncursesw5-dev`, `locales` (Japanese)

## Testing

No automated tests. Manual gameplay validation. Requires terminal with ncurses support.

## Important Notes

- `gettimeofday()` for millisecond-precision timing
- Japanese locale (`ja_JP.UTF-8`) required for proper rendering
- Minimum terminal size: 75 columns x 17 rows
- File paths are relative — always run from `src/`
- Color pairs: red text in last 5 seconds, blue during fever mode

## Reference

| Location | Content |
|----------|---------|
| `.claude/rules/architecture.md` | Program flow, modules, data structures, game constants |
| `.claude/rules/conventions.md` | Naming, style, file I/O format |
| `.claude/policies/commit-message.toml` | Lucent Commits v1.2 — commit message specification |
| `.claude/skills/commit/SKILL.md` | `/commit` skill for policy-compliant commits |
