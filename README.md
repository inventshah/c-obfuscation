# C Obfuscation
Convert pure functions to binary functional pointers in C files.

### How to Use
Dependencies: `regex.h`

Clone: `git clone https://github.com/inventshah/c-obfuscation.git`

Compile: `./build.sh`

Run: `./bin/main [c source filename]]`

Options:

* `-o [output file name]` Saves the obfuscated c file to that location, default is `out.c`
* `-b [binary]` uses the binary file instead of compiling a new one.

Functions will be converted to their binary counter parts and can be executed as functional pointers.

Run `bash test-all.sh` to check the test cases.

### Built With
* C
* Regex