softDev
=======

This Project requires the SDL2 libraries, as well as the extensions SDL2\_image and SDL2\_mixer.

__Instructions:__
First of all, replace the file 'Makefile' in the root directory with the appropriate file in 'makefiles/'.   

If you are using a mac and are following the below instructions for mac frameworks, then use the Makefile-macFrameworks makefile.
The macports makefile is for if you used macports to install the sdl libs. If you don't know if you are using macports then you very likely aren't using it.

For linux installations, make sure the SDL2 libraries are installed in /usr/local/lib and
/usr/local/include (the standard './configure; make; sudo make install' procedure should do this for you)

For macs, make sure the SDL2 framework is installed as per the directions in the SDL2-2.0.0.dmg file from libsdl.org  

To install the extension libraries, get them from libsdl.org/projects, and use the same installation method as you did for the main library.

If you have everything installed, then typing 'make' while in the root directory of the project should compile the
existing code successfully, and if the make is successful, then typing './our\_game' should show up a window with a 
ship that flies around with the arrow keys or wasd (plus q and e for strafing). Pressing 'f' toggles fullscreen, 'c' switches camera modes, 'p' cycles
through present Player ships, pressing 'k' decreases the health of the current Player ship, pressing 'space' shoots, and pressing 'q' quits.
