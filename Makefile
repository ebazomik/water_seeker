CC = gcc

CFLAGS = -Isrc -Isrc/utils -Isrc/player -Isrc/levels -Ilib

LIBS = -lraylib -lopengl32 -lgdi32 -lwinmm

SRCS = \
    src/main.c \
    src/player/player.c \
    src/levels/levels.c \
    src/utils/utils.c \

TARGET = game.exe

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET) $(LIBS)

clean:
	rm -rf $(TARGET)

.PHONY: all clean
