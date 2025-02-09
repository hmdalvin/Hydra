CC = gcc
CFLAGS = `pkg-config --cflags gtk4` -I./include
LIBS = `pkg-config --libs gtk4`
SRC = src/main.c src/converter.c src/ui.c
OBJ = $(SRC:src/%.c=src/%.o) 
EXEC = program

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC) $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(EXEC)

run: $(EXEC)
	./$(EXEC)
