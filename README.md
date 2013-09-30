softDev
=======

__Important:__ As of this commit, you also need to install SDL2\_image from
libsdl.org/projects, or from your package manager if it has it. The instructions are the
same as those below for the base SDL2 libraries.

For linux installations, make sure the SDL2 libraries are installed in /usr/local/lib and
/usr/local/include (the standard './configure; make; sudo make install' procedure should do this for you),
and then type 'make' while in the root directory of this project.

For macs, make sure the SDL2 framework is installed as per the directions in the SDL2-2.0.0.dmg file from
libsdl.org, then type 'make -f Makefile-mac' while in the root directory of this project.

If the make is successful, then typing './our\_game' should show up a window with a hello world
picture for two seconds and then quit.

Email me at dhakimian@westmont.edu if you have any problems, including the error message and what system
you're using.
