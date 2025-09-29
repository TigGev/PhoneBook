CC = gcc
CFLAGS = -Wall -Iinclude
SRC = src/main.c src/phonebook.c
OBJ = $(SRC:.c=.o)
TARGET = build/PhoneBook

all: $(TARGET)

$(TARGET): $(OBJ)
	@mkdir -p build
	$(CC) $(CFLAGS) -o $@ $(OBJ)

clean:
	rm -rf src/*.o build/
