# C Library Management System (Portfolio Edition)

[![C CI](https://github.com/frankwyf/programming-project/actions/workflows/ci.yml/badge.svg)](https://github.com/frankwyf/programming-project/actions/workflows/ci.yml)

This repository is a refactored and open-source-ready version of an earlier C programming coursework project.
It is now maintained as a personal portfolio project focused on:

- C language fundamentals
- linked list based data modeling
- file-based persistence
- cross-platform command-line workflow

## Languages

- English (this file)
- Chinese: [docs/README.zh.md](docs/README.zh.md)
- Japanese: [docs/README.ja.md](docs/README.ja.md)
- Docs index: [docs/INDEX.md](docs/INDEX.md)

## Features

- User registration and login
- Librarian mode for adding/removing books
- Borrow and return flow for standard users
- Search books by title, author, and year
- Backend management tools (users and loans)
- Data persistence with plain text files (`books.txt`, `user.txt`, `loan.txt`)

## Project Structure

.
|- main.c
|- interface.c / interface.h
|- user_management.c / user_management.h
|- book_management.c / book_management.h
|- management.c / management.h
|- books.txt
|- user.txt
|- loan.txt
|- Makefile
|- docs/
|- LICENSE
|- CONTRIBUTING.md
|- CODE_OF_CONDUCT.md
|- SECURITY.md
|- CHANGELOG.md

## Build

This project has no third-party library dependency. You only need a C compiler.

```bash
make
```

If `make` is not available, compile directly:

```bash
gcc -O2 -Wall -Wextra -std=c11 -o library main.c interface.c management.c book_management.c user_management.c
```

Windows setup and VS Code terminal troubleshooting:
[docs/setup-windows.md](docs/setup-windows.md)

## Automated Tests

Local regression test scripts:

- Linux/macOS: [tests/run_regression.sh](tests/run_regression.sh)
- Windows PowerShell: [tests/run_regression.ps1](tests/run_regression.ps1)

Typical usage:

```bash
make
bash tests/run_regression.sh
```

PowerShell:

```powershell
mingw32-make
powershell -ExecutionPolicy Bypass -File tests\run_regression.ps1
```

## CI/CD

- CI workflow: [.github/workflows/ci.yml](.github/workflows/ci.yml)
	- build with make
	- direct gcc build
	- smoke test
	- regression test script (menu, login, librarian path, borrow/return persistence)
	- windows MinGW build + PowerShell regression

- Release workflow: [.github/workflows/release.yml](.github/workflows/release.yml)
	- triggers on tags like `v1.0.0`
	- builds linux and windows binaries
	- runs regression before publishing
	- uploads release artifacts (`.tar.gz` and `.zip` packages)

- Sanitizer workflow: [.github/workflows/sanitizers.yml](.github/workflows/sanitizers.yml)
	- AddressSanitizer + UndefinedBehaviorSanitizer build
	- smoke + regression execution under sanitizers

## Run

```bash
./library books.txt user.txt loan.txt
```

On Windows PowerShell:

```powershell
.\library.exe books.txt user.txt loan.txt
```

## Notes

- `user.txt` uses demo-only credentials and anonymized identities.
- This project intentionally preserves much of the original coursework logic while improving release hygiene for open-source sharing.
- See [docs/project-legacy-notes.md](docs/project-legacy-notes.md) for the migration summary from local legacy materials.

## Open Source Governance

- License: [LICENSE](LICENSE)
- Contributing: [CONTRIBUTING.md](CONTRIBUTING.md)
- Code of Conduct: [CODE_OF_CONDUCT.md](CODE_OF_CONDUCT.md)
- Security Policy: [SECURITY.md](SECURITY.md)
- Changelog: [CHANGELOG.md](CHANGELOG.md)

## CI and Collaboration

- Continuous Integration: [.github/workflows/ci.yml](.github/workflows/ci.yml)
- Bug Report Template: [.github/ISSUE_TEMPLATE/bug_report.yml](.github/ISSUE_TEMPLATE/bug_report.yml)
- Feature Request Template: [.github/ISSUE_TEMPLATE/feature_request.yml](.github/ISSUE_TEMPLATE/feature_request.yml)
- Pull Request Template: [.github/pull_request_template.md](.github/pull_request_template.md)

## License

This project is licensed under the MIT License. See [LICENSE](LICENSE).
