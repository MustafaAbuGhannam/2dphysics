build:
	g++ -std=c++20 -Wall ./src/*.cpp ./src/Physics/*.cpp -lm -lSDL2 -lSDL2_image -lSDL2_gfx -o app

run:
	./app

clean:
	rm app
