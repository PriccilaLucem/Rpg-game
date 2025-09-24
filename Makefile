CC = gcc

# Detect OS
UNAME_S := $(shell uname -s)

# Flags de compilação
CFLAGS = -Wall -Wextra -std=c99 -Iinclude -Iinclude/SDL2 -Iinclude/constants -Isrc -Isrc/game -Isrc/structs

# Configuração específica por SO
ifeq ($(UNAME_S),Linux)
    LDFLAGS = -lSDL2 -lSDL2_ttf -lSDL2_mixer
    TARGET = $(BIN_DIR)/game
else ifeq ($(UNAME_S),Darwin)
    # Configuração para macOS
    HOMEBREW := $(shell which brew)
    CFLAGS += -I/usr/local/include/SDL2 -I/opt/homebrew/include/SDL2
    LDFLAGS = -L/usr/local/lib -L/opt/homebrew/lib -lSDL2 -lSDL2_ttf -lSDL2_mixer
    TARGET = $(BIN_DIR)/game
else
    LDFLAGS = -Llib -lSDL2 -lSDL2_ttf -lSDL2_mixer
    TARGET = $(BIN_DIR)/game.exe
endif

# Diretórios
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
LIB_DIR = lib

# Regra install_libs_mac (corrigida a indentação)
ifeq ($(UNAME_S),Darwin)
install_libs_mac:
	@if [ -z "$(HOMEBREW)" ]; then \
		echo "Homebrew não encontrado. Instalando Homebrew..."; \
		/bin/bash -c "$$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"; \
	fi
	@echo "Instalando SDL2, SDL2_ttf e SDL2_mixer via Homebrew..."
	@brew install sdl2 sdl2_ttf sdl2_mixer || brew upgrade sdl2 sdl2_ttf sdl2_mixer
	@echo "Bibliotecas SDL2 instaladas com sucesso!"

# Modifica a regra all para macOS
all: install_libs_mac $(TARGET)
else
all: $(TARGET)
endif

# Arquivos fonte
SRCS = $(SRC_DIR)/main.c \
       $(SRC_DIR)/states/states.c \
       $(SRC_DIR)/ui/main_menu/main_menu.c \
       $(SRC_DIR)/ui/button/button.c \
       $(SRC_DIR)/ui/button/input_field.c \
       $(SRC_DIR)/config/config.c \
       $(SRC_DIR)/screen/screen.c \
       $(SRC_DIR)/load_obj/load_obj.c \
       $(SRC_DIR)/ui/options/options.c \
       $(SRC_DIR)/structs/charater/basic_charater.c \
       $(SRC_DIR)/structs/charater/main_charater.c \
       $(SRC_DIR)/game/init_game/init_game.c \
	   $(SRC_DIR)/game/ui/charater_build.c \
	   $(SRC_DIR)/game/floor/floor.c \
	   $(SRC_DIR)/game/iso_camera/iso_camera.c \
	   $(SRC_DIR)/game/game.c \
	   $(SRC_DIR)/game/physics/physics.c

# Arquivos objeto
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

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

# Verificar arquitetura (Windows)
check_architecture:
	@echo "Verificando arquitetura..."
	@file lib/SDL2.dll 2>/dev/null || echo "Use: 'make download_dlls' para baixar DLLs corretas"

# Baixar DLLs (Windows 64-bit)
download_dlls:
	@echo "Baixando DLLs SDL2 64-bit... \n"
	@curl -L https://github.com/libsdl-org/SDL/releases/download/release-2.28.5/SDL2-2.28.5-win32-x64.zip -o sdl2.zip
	@curl -L https://github.com/libsdl-org/SDL_ttf/releases/download/release-2.20.2/SDL2_ttf-2.20.2-win32-x64.zip -o sdl2_ttf.zip
	@curl -L https://github.com/libsdl-org/SDL_mixer/releases/download/release-2.8.1/SDL2_mixer-2.8.1-win32-x64.zip -o sdl2_mixer.zip
	@unzip -j sdl2.zip "*.dll" -d lib/
	@unzip -j sdl2_ttf.zip "*.dll" -d lib/
	@unzip -j sdl2_mixer.zip "*.dll" -d lib/
	@echo  "Baixar DLLs adicionais necessárias"
	@curl -L https://www.dll-files.com/zlib1.dll?download -o lib/zlib1.dll
	@curl -L https://www.dll-files.com/libfreetype-6.dll?download -o lib/libfreetype-6.dll
	@rm sdl2.zip sdl2_ttf.zip sdl2_mixer.zip
	@echo "Todas as DLLs baixadas para lib/"

# Copiar DLLs (Windows)
copy_dlls: | $(BIN_DIR)
	@echo "Copiando todas as DLLs para $(BIN_DIR)..."
	@for dll in lib/*.dll; do \
		cp -f $$dll $(BIN_DIR)/; \
		echo "`basename $$dll` copiada"; \
	done
	@# Verificações (opcionais) de DLLs importantes
	@for required in SDL2.dll SDL2_ttf.dll SDL2_mixer.dll; do \
		if [ ! -f $(BIN_DIR)/$$required ]; then \
			echo "ERRO: $$required não foi copiada."; \
			exit 1; \
		fi; \
	done
	@echo "Todas as DLLs obrigatórias estão presentes."

# Limpar arquivos compilados
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

# Executar o programa
ifeq ($(UNAME_S),Linux)
run: $(TARGET)
	./$(TARGET)
else ifeq ($(UNAME_S),Darwin)
run: $(TARGET)
	./$(TARGET)
else
run: $(TARGET) copy_dlls
	@if [ -f bin/SDL2.dll ] && [ -f bin/SDL2_ttf.dll ]; then \
		./$(TARGET); \
	else \
		echo "DLLs não encontradas. Use: make download_dlls"; \
		exit 1; \
	fi
endif

# Recompilar e executar
rebuild: clean all run

.PHONY: all clean run rebuild copy_dlls download_dlls check_architecture
