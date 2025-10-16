# Nom de l’exécutable
NAME = main

# Compilateur et options
CC = gcc
CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -lm

# Recherche automatique de tous les fichiers .c du dossier
SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)

# Règle par défaut
all: $(NAME)

# Compilation de l’exécutable
$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# Compilation des fichiers .o à partir des .c
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Nettoyage des fichiers objets
clean:
	rm -f $(OBJ)

# Nettoyage complet + recompilation
re: clean all




