objects = rayTracing.o scene.o main.o lightSources.o image.o tinyxml2.o mesh.o
CC = g++
CFLAGS = -std=c++11 -O3 -pthread

%.o: %.cpp %.h
	$(CC) $(CFLAGS) -o $@ -c $<

run: $(objects)
	$(CC) $(CFLAGS) -o rayTracing $(objects)

clean :
	rm rayTracing $(objects)