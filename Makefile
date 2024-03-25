all:
	g++ -I sdl2_64\include -I rapidjson-master\include -L sdl2_64\lib -o main main.cpp renderWindow.cpp vector2.cpp level.cpp player.cpp sprite.cpp sound.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer
	.\main.exe
#-mwindows