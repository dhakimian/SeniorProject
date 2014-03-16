Space Game
==========

__Requirements__

* SDL2
* SDL2\_image
* SDL2\_mixer
* SDL2\_net
* GNU autotools (autoconf, automake)

__Instructions:__

In the top directory of the project type:

    ./autogen.sh

    ./configure

    make

Then you can type either

    ./bin/server

to start the server, or

    ./bin/client [host [port]]

to start the client, which looks for a server at localhost on port 2000 by default.

*WARNING:* The game will sometimes freeze and max out your computer's RAM. You will have to
make it force quit or end task, or from the terminal started it in, you can press ctrl-z and
then 'kill -9 %1' (ctrl-c doesn't seem to work when this happens). Yes, finding and fixing
memory leaks is on the todo list... :P

By default, the server doesn't render anything, but if you type anything (literally anything)
after ./bin/server, it will turn on a sort of spectator mode, where you can see what is going
on in the server.

Right now the game isn't really playable unless the server and client are going at the same
speed, and the best way to get them to go at the same speed is to start the server in graphical
mode. However, the sleep time between cycles on the server when not in graphical mode is close
enough to the default client speed that it is playable.

You can't control a ship in this mode, but you can follow their movement, or you can also
move the camera around freely with the arrow keys ('q' or 'e' to rotate camera). Press 'f' to
toggle whether you are following a ship or moving the camera around; press 'p' to change which
ship you are following.

The client won't do anything unless it finds a server at the place it's looking for one. Once
it finds the server, it will begin receiving the server's game state broadcasts, and will send
its keyboard input to the server to be interpreted. If the client loses its connection to the
server after having previously established one, it will update the gamestate locally, which
helps minimize jitter from dropped packets.
This also means that you can play a client-side-only single player game by starting a server,
connecting to it, and then killing the server. (But as soon as a server comes online again at
the place the client is expecting, it will connect to it and have its state reset to that of
the server's)

The server seems to be able to support 4 different connections, and there are four different
colors that your ship can be. Right now, every client centers on the first Player object they
find in g\_objects, so this means that if you are the first client to connect, everything works
as expected, but if you join after that, even though you are controlling a second ship, you are
focused on the first one, which makes things rather difficult :)

This should hopefully be remedied soon, but until then, for all practical purposes the game
still only supports one player :P
