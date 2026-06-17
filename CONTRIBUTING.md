# Contributing

Thank you for your interest in contributing.

## Development Setup

1. Install a C compiler (`gcc`/`clang`) and `make`.
2. Build with `make`.
3. Run with `./library books.txt user.txt loan.txt` (Windows: `.\\library.exe ...`).

## Pull Request Checklist

1. Keep changes focused and small.
2. Preserve current CLI behavior unless explicitly improving it.
3. Update documentation when behavior changes.
4. Avoid introducing personal data into sample files.
5. Ensure code compiles with `-Wall -Wextra`.

## Code Style

1. Keep C code in existing style (simple procedural C, clear function boundaries).
2. Prefer readable variable names over short abbreviations.
3. Add comments only for non-obvious logic.
