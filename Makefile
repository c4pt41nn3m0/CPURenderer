build:
	gcc -Wall -std=c99 ./src/Renderer/*.c -lSDL2 -lm -o bin/x64/renderer

run:
	bin/x64/renderer

clean:
	rm bin/x64/renderer
