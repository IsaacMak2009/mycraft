all:
	make main.exe

%.exe: %.cpp
	g++ $< -o $@ -lopengl32 -lglfw3 -lgdi32 -lglew32

clean:
	del *.exe