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
