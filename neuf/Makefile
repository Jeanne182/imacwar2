CC = g++
CFLAGS = -Wall -ansi -Isrc -g
LDFLAGS	= -lSDL -lSDL_image -lGLU -lGL -lm -lSDL_ttf -std=c++11

BINDIR	= bin/
SRCDIR	= src/
OBJDIR	= obj/

main: $(OBJDIR)main.o $(OBJDIR)unites.o $(OBJDIR)interface.o $(OBJDIR)sprites.o $(OBJDIR)selection.o $(OBJDIR)boutons.o $(OBJDIR)initialisation.o $(OBJDIR)clics.o $(OBJDIR)textures.o $(OBJDIR)text.o $(OBJDIR)affichage.o $(OBJDIR)a_star.o
		$(CC) -o $(BINDIR)$@ $^ $(LDFLAGS)
		./$(BINDIR)$@

$(OBJDIR)main.o: src/game/main.cpp src/unites/unites.h src/interface/interface.h src/game/game.h
	$(CC) -o $@ -c $< $(CFLAGS) $(LDFLAGS)

$(OBJDIR)unites.o: src/unites/unites.cpp src/unites/unites.h
	$(CC) -o $@ -c $< $(CFLAGS) $(LDFLAGS)

$(OBJDIR)interface.o: src/interface/interface.cpp src/interface/interface.h
	$(CC) -o $@ -c $< $(CFLAGS) $(LDFLAGS)

$(OBJDIR)sprites.o: src/interface/sprites.cpp src/interface/interface.h
	$(CC) -o $@ -c $< $(CFLAGS) $(LDFLAGS)

$(OBJDIR)selection.o: src/unites/selection.cpp src/unites/unites.h
	$(CC) -o $@ -c $< $(CFLAGS) $(LDFLAGS)

$(OBJDIR)boutons.o: src/interface/boutons.cpp src/interface/interface.h
	$(CC) -o $@ -c $< $(CFLAGS) $(LDFLAGS)

$(OBJDIR)initialisation.o: src/game/initialisation.cpp src/unites/unites.h src/interface/interface.h src/game/game.h
	$(CC) -o $@ -c $< $(CFLAGS) $(LDFLAGS)

$(OBJDIR)clics.o: src/game/clics.cpp src/unites/unites.h src/interface/interface.h src/game/game.h
	$(CC) -o $@ -c $< $(CFLAGS) $(LDFLAGS)

$(OBJDIR)textures.o: src/game/textures.cpp src/interface/interface.h
	$(CC) -o $@ -c $< $(CFLAGS) $(LDFLAGS)

$(OBJDIR)text.o: src/interface/text.cpp src/interface/text.h
	$(CC) -o $@ -c $< $(CFLAGS) $(LDFLAGS)

$(OBJDIR)affichage.o: src/interface/affichage.cpp src/interface/interface.h
	$(CC) -o $@ -c $< $(CFLAGS) $(LDFLAGS)

$(OBJDIR)a_star.o: src/game/a_star.cpp src/game/a_star.h
	$(CC) -o $@ -c $< $(CFLAGS) $(LDFLAGS)

clean:
	rm -rf $(OBJDIR)*
	rm -rf $(BINDIR)*
