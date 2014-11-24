all: main.exe main.o Vector3.o Vector2.o Color.o Debug.o Printable.o

main.exe: main.o Vector3.o Vector2.o Color.o Debug.o Printable.o
	g++ main.o Vector3.o Vector2.o Color.o Debug.o Printable.o -o main.exe

main.o: main.cpp
	g++ -c main.cpp -o main.o

Vector3.o: Vector3.cpp
	g++ -c Vector3.cpp -o Vector3.o 

Vector2.o: Vector2.cpp
	g++ -c Vector2.cpp -o Vector2.o 

Color.o: Color.cpp
	g++ -c Color.cpp -o Color.o

Debug.o: Debug.cpp
	g++ -c Debug.cpp -o Debug.o

Printable.o: Printable.cpp
	g++ -c Printable.cpp -o Printable.o

clean:
	rm -f *.o *.exe
