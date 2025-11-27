# Compilador y flags
CC = gcc

# Agrego -Iinclude para que encuentre los headers en la carpeta include/
CFLAGS = -Wall -Wextra -std=c99 `pkg-config --cflags gtk4` \
         -Wno-deprecated-declarations -Wno-typedef-redefinition -Iinclude

LDFLAGS = `pkg-config --libs gtk4` -lm

# Archivos objeto 
OBJS = main.o \
       src/menu.o \
       src/app.o  \
       src/mate.o \
       src/resistor.o \
       src/poteapp.o \
       src/pot.o

# Nombre del ejecutable
TARGET = calculadora-electronica

# Regla por defecto
all: $(TARGET)

# Enlazar el ejecutable
$(TARGET): $(OBJS)
	$(CC) -o $@ $(OBJS) $(LDFLAGS)

# Compilar cada archivo objeto
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Limpiar archivos compilados
clean:
	rm -f $(OBJS) $(TARGET)

# Recompilar desde cero
rebuild: clean all


#     valgrind
valgrind: $(TARGET)
	valgrind --leak-check=full --track-origins=yes ./$(TARGET)

.PHONY: all clean rebuild valgrind
