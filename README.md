softDev
=======

For linux installations, make sure the SDL2 libraries are installed in /usr/local/lib and
/usr/local/include (the standard ./configure; make; sudo make install procedure should do this), and then
type make while in the root directory of this project. Having local copies of the libraries just doesn't
work, since they have to be built differently for any machine that isn't using the exact same OS/distro.

The makefile still does everything necessary to make your program see the libs, so you don't have to, but
you do have to make sure the makefile knows where to find the libs.

If the make is successful, then typing ./our\_game './our\_game' should show up a window with a hello world
picture for two seconds and then quit.

Email me at dhakimian@westmont.edu if you have any problems, including the error message and what system
you're using.

I can create a version of the makefile that will work for standard OSX installs, but I'm not sure about
windows.
