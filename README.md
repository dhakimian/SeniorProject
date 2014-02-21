Space Game
==========

This Project requires SDL2, as well as the extension libraries SDL2\_image, SDL2\_mixer, and SDL2\_net. This project also requires automake for compilation, so if you don't have that installed already, you'll need to get it.

__Instructions:__

In the top directory of the project type:

./autogen.sh

./configure

make

Then you can type either

./bin/server

or 

./bin/client

to start the server or client.

You can't control a ship from the server, but you can follow their movement, or move the camera around with the arrow keys (press 'q' or 'e' to rotate camera). Press 'f' to toggle whether you are following a ship or moving the camera freely; press 'p' while following a ship to change which ship you are following.

You can send packets to the server at port 2000 that contain certain strings to make the server do things. If you send "p", it does the same thing pressing 'p' does; "l", "r", "u", "d" will move the camera position a small distance to the left, right, up, or down respectively, assuming you are not currently following a ship.

The client currently is pretty much just at the state the entire project was at before I started working on this as my senior project this semester, so you can fly around and shoot and do everything you could before, and not anything new. Well, there is some stuff that is new compared to the project's current state on masonnl's repo, but that is all stuff I worked on personally during Christmas that I never pushed up (until now, to this repo).
