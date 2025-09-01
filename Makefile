# Compilador
CC = gcc

# Flags de compilação
CFLAGS = -Wall -Wextra -Iinclude/SDL2 -Iinclude/constants

# Flags de linkedição
LDFLAGS = -Llib -lSDL2 -lSDL2_ttf

# Diretórios
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
LIB_DIR = lib

# Arquivos fonte
SRCS = $(SRC_DIR)/main.c \
       $(SRC_DIR)/states/states.c \
       $(SRC_DIR)/ui/main_menu/main_menu.c \
       $(SRC_DIR)/ui/button/button.c \
       $(SRC_DIR)/config/config.c \
       $(SRC_DIR)/screen/screen.c \
       $(SRC_DIR)/load_obj/load_obj.c \
       $(SRC_DIR)/ui/options/options.c \
       $(SRC_DIR)/game/characters/character.c \
       $(SRC_DIR)/entities/main_character/main_character.c \
       $(SRC_DIR)/structs/character/basic_character.c \
       $(SRC_DIR)/game/collision/collision.c \
       $(SRC_DIR)/game/floor/floor.c \
       $(SRC_DIR)/game/init_game/init_game.c
# Arquivos objeto
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Nome do executável
TARGET = $(BIN_DIR)/game.exe

# Regra padrão
all: $(TARGET)

# Regra para criar o executável
$(TARGET): $(OBJS) | $(BIN_DIR)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

# Regra para compilar arquivos .c em .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

# Criar diretórios se não existirem
$(BIN_DIR):
	@mkdir -p $(BIN_DIR)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

# Verificar arquitetura
check_architecture:
	@echo "Verificando arquitetura..."
	@file lib/SDL2.dll 2>/dev/null || echo "Use: 'make download_dlls' para baixar DLLs corretas"

# Baixar DLLs corretas (64-bit)
download_dlls:
	@echo "Baixando DLLs SDL2 64-bit..."
	@curl -L https://github.com/libsdl-org/SDL/releases/download/release-2.28.5/SDL2-2.28.5-win32-x64.zip -o sdl2.zip
	@curl -L https://github.com/libsdl-org/SDL_ttf/releases/download/release-2.20.2/SDL2_ttf-2.20.2-win32-x64.zip -o sdl2_ttf.zip
	@unzip -j sdl2.zip "*.dll" -d lib/
	@unzip -j sdl2_ttf.zip "*.dll" -d lib/
	@rm sdl2.zip sdl2_ttf.zip
	@echo "DLLs baixadas para lib/"

# Copiar DLLs (apenas se existirem)
copy_dlls: | $(BIN_DIR)
	@if [ -f lib/SDL2.dll ]; then \
		cp -f lib/SDL2.dll $(BIN_DIR)/; \
		echo "SDL2.dll copiada"; \
	else \
		echo "SDL2.dll não encontrada. Use: make download_dlls"; \
	fi
	@if [ -f lib/SDL2_ttf.dll ]; then \
		cp -f lib/SDL2_ttf.dll $(BIN_DIR)/; \
		echo "SDL2_ttf.dll copiada"; \
	else \
		echo "SDL2_ttf.dll não encontrada. Use: make download_dlls"; \
	fi

# Limpar arquivos compilados
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

# Executar o programa (com verificação)
run: $(TARGET) copy_dlls
	@if [ -f bin/SDL2.dll ] && [ -f bin/SDL2_ttf.dll ]; then \
		./$(TARGET); \
	else \
		echo "DLLs não encontradas. Use: make download_dlls"; \
		exit 1; \
	fi

# Recompilar e executar
rebuild: clean all run

.PHONY: all clean run rebuild copy_dlls download_dlls check_architecture