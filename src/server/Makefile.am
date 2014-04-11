bin_PROGRAMS = $(top_builddir)/bin/server
__top_builddir__bin_server_SOURCES = Alien.cpp Asteroid.cpp Collision.cpp Explosion.cpp LTexture.cpp LTimer.cpp Laser.cpp MovingObject.cpp Object.cpp Planet.cpp Player.cpp Powerup.cpp Ship.cpp Util.cpp Vec2D.cpp main.cpp
##__top_builddir__bin_server_CPPFLAGS = -std=c++11 `sdl2-config --cflags`
__top_builddir__bin_server_CPPFLAGS = -std=c++0x `sdl2-config --cflags` -D_SERVER_
__top_builddir__bin_server_LDFLAGS = `sdl2-config --libs`
__top_builddir__bin_server_LDADD = -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_net -lSDL2_ttf
