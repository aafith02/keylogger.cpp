# 🛡️ C++ Keylogger (Educational Purpose Only)

This is a simple low-level keylogger written in C++ using the Windows API.  
It captures keyboard events and logs them to a file named `keylog.txt`.

> ⚠️ Warning:This project is for educational and ethical learning purposes only.  
> Do not use this code for unauthorized access, spying, or malicious activities.

---

 🧰 Requirements

- Windows OS(tested on Windows 10/11)
- Administrator privileges (required to install global keyboard hook)
- [MSYS2](https://www.msys2.org/) with `g++` installed

---

 🛠️ Installation & Setup

1. Install MSYS2 and g++

Follow official MSYS2 setup guide:  
➡️ https://www.msys2.org/

Then open MSYS2 UCRT64 terminal and run:

```bash
pacman -Syu            # Update all packages
pacman -S mingw-w64-ucrt-x86_64-gcc   # Install g++
