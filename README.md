# Console Game SNAKE 2.0

- Demo: <https://youtu.be/T7vTSeiKzMs/>

# Description

- This Game is create by using C language.
- Using third-party library `console.h` (already attached in source code).
- Using native API to play sound.
- Keyboard to play only.
- All in a single file so as to easy to understand the code flow.
(Strongly Recommend to refactor the code after you understande the code flow.)

# Feature

- [x] Play /Pause /Reset when playing.
- [x] Store Top 5 highest score and player name.
- [x] Cool and lively sound.
- [x] Colorful and great graphics. 
- [x] Snake Bots and special objects.
- [x] Various mode as well as level of difficult for player to challenge.

# Setup

Download all file and put in same directory

- **Run**: Run file `TrainCproject.exe`.
- **Compile**: Create project in the same folder with game files, then add file  `trainCproject.c` and `console.h` to project.

1. Dev-C++: Right click on project -> Menu project -> project options > parameters and type `-lwinmm` into LINKER column section (this will allow Dev-C++ to play sound) 
-> F11 (compile & run).

2. Visual Studio: Switch debug mode to Debug x86 -> Ctr + F5 (start without debugging).

If `.exe` file has error about missing or broken file, go to <https://www.dll-files.com/> and download the file that the error told you. Then put that file (after extracted) to C:\Windows\System32 and the folder that contains `.exe` file.

# License & copyright

© Trần Trung Kiên - Hồ Linh Chi - Hoàng Phi Hải, FPT University TP.HCM
Licensed under the [MIT LICENSE](LICENSE).
