CC=g++
LDFLAGS=-lGL -lGLEW -lglut
CFLAGS=-g -Wall -I../common

OUTPUT=balldemo

SRC=logging.cpp \
   ../common/tex.cpp \
   ../common/glutils.cpp \
   ../common/matrix.cpp \
   ../common/sprite.cpp \
   ../common/stage.cpp \
   main.cpp

OBJ=$(SRC:.cpp=.o)

all: $(SRC) $(OUTPUT)

$(OUTPUT): $(OBJ)
	$(CC) $(LDFLAGS) $(OBJ) -o $@

.cpp.o:
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm -f $(OUTPUT) $(OBJ)
