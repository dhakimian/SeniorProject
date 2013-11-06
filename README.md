softDev
=======

__Important:__ As of this commit, you also need to install SDL2\_image from
libsdl.org/projects, or from your package manager if it has it. The instructions are the
same as those below for the base SDL2 libraries.

First of all, replace the file 'Makefile' in the root directory with the appropriate file in 'makefiles/'.   

If you are using a mac and are following the below instructions for mac frameworks, then use the Makefile-macFrameworks makefile.
The macports makefile is for if you used macports to install the sdl libs. If you don't know if you are using macports then you very likely aren't using it.

For linux installations, make sure the SDL2 libraries are installed in /usr/local/lib and
/usr/local/include (the standard './configure; make; sudo make install' procedure should do this for you)

For macs, make sure the SDL2 framework is installed as per the directions in the SDL2-2.0.0.dmg file from libsdl.org  

If you have everything installed, then typing 'make' while in the root directory of the project should compile the
existing code successfully, and if the make is successful, then typing './our\_game' should show up a window with a 
ship that flies around with the arrow keys. Pressing 'f' toggles fullscreen, and pressing 'q' quits.
