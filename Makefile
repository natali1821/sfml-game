.PHONY: clean

mario: enemy.o player.o menu.o sound.o
	g++ enemy.o player.o menu.o sound.o -o mario

enemy.o: enemy.cpp
	g++ -c enemy.cpp

player.o: player.cpp
	g++ -c player.cpp

menu.o: menu.cpp
	g++ -c menu.cpp

sound.o: sound.cpp
	g++ -c sound.cpp

clean:
	rm *.o mario