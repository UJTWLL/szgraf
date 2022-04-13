all:
	gcc -Iinclude src/*   -lSOIL -lglu32 -lopengl32 -lglut32 -lm -o ujtwll.exe 
linux:
	gcc -Iinclude src/*  -lSOIL -lGL -lGLU -lglut -lm -o ujtwll.exe 