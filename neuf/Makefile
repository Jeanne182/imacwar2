CC = g++
CFLAGS = -Wall -ansi -Isrc
LDFLAGS	= -lSDL -lSDL_image -lGLU -lGL -lm 

BINDIR	= bin/
SRCDIR	= src/
OBJDIR	= obj/

projetjeu: $(OBJDIR)projetjeu.o $(OBJDIR)unites.o $(OBJDIR)interface.o $(OBJDIR)sprites.o $(OBJDIR)selection.o $(OBJDIR)boutons.o $(OBJDIR)initialisation.o $(OBJDIR)clics.o
		$(CC) -o $(BINDIR)$@ $^ $(LDFLAGS)
		./$(BINDIR)$@ 

$(OBJDIR)projetjeu.o: src/game/projetjeu.cpp src/unites/unites.h src/interface/interface.h src/game/game.h
	$(CC) -o $@ -c $< $(CFLAGS) $(LDFLAGS)

$(OBJDIR)unites.o: src/unites/unites.cpp src/unites/unites.h 
	$(CC) -o $@ -c $< $(CFLAGS) $(LDFLAGS)

$(OBJDIR)interface.o: src/interface/interface.cpp src/interface/interface.h
	$(CC) -o $@ -c $< $(CFLAGS) $(LDFLAGS)

$(OBJDIR)sprites.o: src/interface/sprites.cpp src/interface/interface.h
	$(CC) -o $@ -c $< $(CFLAGS) $(LDFLAGS)

$(OBJDIR)selection.o: src/interface/selection.cpp src/interface/interface.h
	$(CC) -o $@ -c $< $(CFLAGS) $(LDFLAGS)

$(OBJDIR)boutons.o: src/interface/boutons.cpp src/interface/interface.h
	$(CC) -o $@ -c $< $(CFLAGS) $(LDFLAGS)

$(OBJDIR)initialisation.o: src/game/initialisation.cpp src/unites/unites.h src/interface/interface.h src/game/game.h
	$(CC) -o $@ -c $< $(CFLAGS) $(LDFLAGS)

$(OBJDIR)clics.o: src/game/clics.cpp src/unites/unites.h src/interface/interface.h src/game/game.h
	$(CC) -o $@ -c $< $(CFLAGS) $(LDFLAGS)

clean:
	rm -rf $(OBJDIR)*
	rm -rf $(BINDIR)*
