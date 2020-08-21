game:
	g++ -std=c++11 *.cpp -o play -I include/SDL2 -L lib -l SDL2-2.0.0 -l SDL2_image-2.0.0 -l SDL2_ttf-2.0.0 -l SDL2_mixer-2.0.0
debug:
	g++ -g -std=c++11 *.cpp -o play -I include/SDL2 -L lib -l SDL2-2.0.0 -l SDL2_image-2.0.0 -l SDL2_ttf-2.0.0 -l SDL2_mixer-2.0.0
