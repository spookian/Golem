# Golem
Golem is a program made to inject code into a vanilla copy of Kirby's Return to Dream Land.

## Compilation

Use CMake to generate a makefile or equivalent for your compiler of choice, and then compile.

## Usage

This section's currently a work in progress, and I am still developing my example code to showcase the program.
If you wish to use it however, you must place a copy of RtDL's main.dol in the same folder as the compiled binary.

Next, the argument must be set to another dol file, the one whose code (must be in the first text section) and data you want to inject into RtDL.
The program will then spit out a new dol file to be used for RtDL (you must change it to main.dol). 

Finalize the romhack by hooking into whatever function you want to reroute into your new function, either via editing the binary or via a Gecko code.

## Warning

This program is very much in development, and most updates to the repo will likely be broken. Please use with caution.
