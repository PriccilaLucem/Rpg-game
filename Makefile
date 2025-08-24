SRC = src/main.c 
      src/states/states.c 
      src/main_menu/main_menu.c 
      src/options/options.c 
      src/button/button.c 
      src/config/config.c 
      src/screen/screen.c 
      src/ui/menu/menu.c

OBJ = $(SRC:.c=.o)

TARGET = game.exe

CFLAGS = -Wall -Wextra -Iinclude
LIBS = -lSDL2 -lSDL2_ttf -lmingw32

all: $(TARGET)

$(TARGET): $(OBJ)
	gcc -o $@ $(OBJ) $(LIBS)

clean:
	rm -f $(OBJ) $(TARGET)