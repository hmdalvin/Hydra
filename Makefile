CC = gcc
CFLAGS = `pkg-config --cflags gtk4` -I./include
LIBS = `pkg-config --libs gtk4`
SRC_DIR = src
OBJ_DIR = build/obj
SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))
EXEC = program

all: $(EXEC)

# Pastikan folder build/obj ada
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Link semua object menjadi program utama
$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC) $(LIBS)

# Kompilasi semua file .c menjadi .o di build/obj/
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Bersihkan hasil kompilasi
clean:
	rm -rf $(OBJ_DIR) $(EXEC)

# Jalankan program setelah kompilasi
run: $(EXEC)
	./$(EXEC)
