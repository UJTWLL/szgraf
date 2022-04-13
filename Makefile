all:
	gcc -Iinclude src/*   -lSOIL -lglu32 -lopengl32 -lglut32 -lm -o szgrafbead.exe 
linux:
	gcc -Iinclude src/*  -lSOIL -lGL -lGLU -lglut -lm -o szgrafbead.exe 
