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

    ./bin/client [hostname/ip [port]]

to start the client, which looks for a server at localhost on port 2000 by default.
( the []s mean the arg inside them is optional )

*WARNING:* The game will sometimes freeze and max out your computer's RAM. You will have to
make it force quit or end task, or from the terminal started it in, you can press ctrl-z and
then 'kill -9 %1' (ctrl-c doesn't seem to work when this happens). Yes, finding and fixing
memory leaks is on the todo list... :P

(this hasn't happened in a while for me, but I also haven't been testing with Rocke Everywhere recently either...)

By default, the server doesn't render anything, but if you type anything (literally anything)
after ./bin/server (with a space in between of course), it will start the server in a sort of
spectator mode, where you can see what is going on in the server.

You can't control a ship in this mode, but you can follow their movement, or you can also
move the camera around freely with the arrow keys ('q' or 'e' to rotate camera). Press 'f' to
toggle whether you are following a ship or moving the camera around; press 'p' to change which
ship you are following.

The client won't do anything unless it finds a server at the place it's looking for one. Once
it finds the server, it will begin receiving the server's game state broadcasts, and will send
its keyboard input to the server to be interpreted. If the client loses its connection to the
server after having previously established one, it will update the gamestate locally, which
should help minimize jitter from dropped packets. If the client misses too many consecutive
updates from the server, it will consider the connection lost, and start looking for the server
again. Similarly, if the server misses too many consecutive packets from a client, it will
consider the connection to that client lost, and stop sending updates to it.

The server seems to be able to support 4 different simultaneous connections, and there are four
different colors that your ship can be. When you join, you get randomly assigned a team (and
corresponding ship color). Later, there might be a way to specify what team you want to join.
