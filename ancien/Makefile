CC = g++
CFLAGS = -Wall -ansi

projetjeu: projetjeu.o unites.o grille.o
		$(CC) -o $@ $^
		./$@

projetjeu.o: projetjeu.cpp unites.h grille.h
	$(CC) -o $@ -c $< $(CFLAGS)

unites.o: unites.cpp unites.h
	$(CC) -o $@ -c $< $(CFLAGS)

grille.o: grille.cpp grille.h
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -rf *.o
