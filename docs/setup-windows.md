# Windows Setup Guide

This guide installs the required C toolchain for this project on Windows.

## Option A (Recommended): MSYS2 + MinGW-w64

1. Install MSYS2 from https://www.msys2.org/
2. Open `MSYS2 UCRT64` terminal.
3. Update package database and core packages:
   `pacman -Syu`
4. Reopen `MSYS2 UCRT64` terminal, then install toolchain:
   `pacman -S --needed mingw-w64-ucrt-x86_64-gcc mingw-w64-ucrt-x86_64-make`
5. Add this directory to Windows `Path`:
   `C:\\msys64\\ucrt64\\bin`
6. Open a new PowerShell window and verify:
   `gcc --version`
   `make --version`

## Option B: LLVM/Clang + mingw32-make

If you already use LLVM, you can compile with `clang`, but you still need a `make` implementation (or compile manually with one gcc/clang command).

## Build and Run

In project root:

```powershell
make
.\\library.exe books.txt user.txt loan.txt
```

## VS Code Terminal Cannot Find gcc

If `gcc --version` works in system terminal but not in VS Code terminal, add workspace settings:

File: `.vscode/settings.json`

```json
{
   "terminal.integrated.env.windows": {
      "PATH": "C:\\mingw64\\bin;${env:PATH}"
   }
}
```

Then open a new terminal tab in VS Code and verify:

```powershell
gcc --version
mingw32-make --version
```

## If EXE Is Blocked by System Policy

Some Windows environments block newly generated executables in IDE terminals.
If you see an application control policy block message, try in PowerShell:

```powershell
Unblock-File .\\library.exe
```

If still blocked, your machine is enforcing enterprise policy. In that case:

1. Run from an allowed terminal profile or trusted folder.
2. Ask local policy admin to allow your workspace path for local development binaries.

Current project note:

- Build works in this workspace with MinGW (`C:\\mingw64\\bin`).
- If runtime is blocked in VS Code terminal by policy, CI regression in GitHub Actions remains the reliable verification path until local policy is relaxed.
