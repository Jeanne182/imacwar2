CC = g++
CFLAGS = -Wall -ansi
LDFLAGS	= -lSDL -lSDL_image -lGLU -lGL -lm

BINDIR	= bin/
SRCDIR	= src/
OBJDIR	= obj/

projetjeu: $(OBJDIR)projetjeu.o $(OBJDIR)unites.o $(OBJDIR)interface.o $(OBJDIR)sprites.o $(OBJDIR)selection.o
		$(CC) -o $(BINDIR)$@ $^ $(LDFLAGS)
		./$(BINDIR)$@ 

$(OBJDIR)projetjeu.o: src/imacwar2/projetjeu.cpp src/unites/unites.h src/interface/interface.h
	$(CC) -o $@ -c $< $(CFLAGS) $(LDFLAGS)

$(OBJDIR)unites.o: src/unites/unites.cpp src/unites/unites.h
	$(CC) -o $@ -c $< $(CFLAGS) $(LDFLAGS)

$(OBJDIR)interface.o: src/interface/interface.cpp src/interface/interface.h
	$(CC) -o $@ -c $< $(CFLAGS) $(LDFLAGS)

$(OBJDIR)sprites.o: src/interface/sprites.cpp src/interface/interface.h
	$(CC) -o $@ -c $< $(CFLAGS) $(LDFLAGS)

$(OBJDIR)selection.o: src/interface/selection.cpp src/interface/interface.h
	$(CC) -o $@ -c $< $(CFLAGS) $(LDFLAGS)

clean:
	rm -rf $(OBJDIR)*
	rm -rf $(BINDIR)*
