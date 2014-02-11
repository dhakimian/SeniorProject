Space Game
==========

This Project requires SDL2, as well as the extension libraries SDL2\_image, SDL2\_mixer, and SDL2\_net. This project also requires automake for compilation, so if you don't have that installed already, you'll need to get it.

__Instructions:__

In the top directory of the project type:

./autogen.sh

./configure

make

./server   # (client NYI)



You can't control a ship from the server, but you can follow their movement, or move the camera around with the arrow keys (press 'q' or 'e' to rotate camera). Press 'f' to toggle whether you are following a ship or moving the camera freely; press 'p' while following a ship to change which ship you are following.
