CC = g++
CFLAGS = -Wall -ansi
LDFLAGS	= -lSDL -lSDL_image -lGLU -lGL -lm

projetjeu: projetjeu.o unites.o interface.o grille.o
		$(CC) -o $@ $^ $(LDFLAGS)
		./$@ 

projetjeu.o: projetjeu.cpp unites.h interface/interface.h
	$(CC) -o $@ -c $< $(CFLAGS) $(LDFLAGS)

unites.o: unites.cpp unites.h
	$(CC) -o $@ -c $< $(CFLAGS) $(LDFLAGS)

interface.o: interface/interface.cpp interface/interface.h
	$(CC) -o $@ -c $< $(CFLAGS) $(LDFLAGS)

grille.o: interface/grille.cpp interface/interface.h
	$(CC) -o $@ -c $< $(CFLAGS) $(LDFLAGS)

clean:
	rm -rf *.o
