CC      = gcc
CFLAGS = -Wall -Wextra -std=c99 -D_POSIX_C_SOURCE=200809L
TARGET  = wildwater

# Tous les fichiers source
SRC = \
    main.c \
    src/src.c \
    Max/max.c \
    parsing/parser.c \
    avl/avl.c \
    leaks/leaks.c \
    real/real.c

OBJ = $(SRC:.c=.o)

# ---------- règle principale ----------
all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

# ---------- compilation .c -> .o ----------
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# ---------- nettoyage ----------
clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: all clean
