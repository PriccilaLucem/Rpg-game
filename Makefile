# =========================
# COMPILADOR
# =========================
CC = gcc

# =========================
# DETECTAR SISTEMA
# =========================
UNAME_S := $(shell uname -s)

# =========================
# DIRETÓRIOS
# =========================
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
LIB_DIR = lib

# =========================
# FLAGS DE COMPILAÇÃO
# =========================
CFLAGS = -Wall -Wextra -std=c99 \
	-Iinclude \
	-Iinclude/SDL2 \
	-Iinclude/constants \
	-Isrc \
	-Isrc/game \
	-Isrc/structs

# Para cJSON
CFLAGS += -I$(LIB_DIR)/cJSON

# =========================
# TARGET E LDFLAGS
# =========================
ifeq ($(UNAME_S),Linux)
    TARGET = $(BIN_DIR)/game
    LDFLAGS = -lSDL2 -lSDL2_ttf -lSDL2_mixer
else ifeq ($(UNAME_S),Darwin)
    TARGET = $(BIN_DIR)/game
    HOMEBREW := $(shell which brew)
    CFLAGS += -I/usr/local/include/SDL2 -I/opt/homebrew/include/SDL2
    LDFLAGS = -L/usr/local/lib -L/opt/homebrew/lib -lSDL2 -lSDL2_ttf -lSDL2_mixer
else
    TARGET = $(BIN_DIR)/game.exe
    LDFLAGS = -Llib -lSDL2 -lSDL2_ttf -lSDL2_mixer
endif

# =========================
# FONTES DO JOGO
# =========================
SRCS = $(SRC_DIR)/main.c \
       $(SRC_DIR)/states/states.c \
       $(SRC_DIR)/ui/main_menu/main_menu.c \
       $(SRC_DIR)/ui/button/button.c \
       $(SRC_DIR)/ui/button/input_field.c \
       $(SRC_DIR)/config/config.c \
       $(SRC_DIR)/screen/screen.c \
       $(SRC_DIR)/load_obj/load_obj.c \
       $(SRC_DIR)/ui/options/options.c \
       $(SRC_DIR)/ui/options/options_render.c \
       $(SRC_DIR)/ui/options/options_handlers.c \
       $(SRC_DIR)/ui/options/options_geometry.c \
       $(SRC_DIR)/structs/charater/basic_charater.c \
       $(SRC_DIR)/structs/charater/main_charater.c \
       $(SRC_DIR)/game/init_game/init_game.c \
       $(SRC_DIR)/game/ui/charater_build.c \
       $(SRC_DIR)/game/floor/floor.c \
       $(SRC_DIR)/game/iso_camera/iso_camera.c \
       $(SRC_DIR)/game/game.c \
       $(SRC_DIR)/game/physics/physics.c \
       $(LIB_DIR)/cJSON/cJSON.c \
	   $(SRC_DIR)/lang/language.c \
	   $(SRC_DIR)/json_loader/json_loader.c

OBJS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(filter $(SRC_DIR)/%,$(SRCS))) \
        $(patsubst $(LIB_DIR)/%.c,$(OBJ_DIR)/%.o,$(filter $(LIB_DIR)/%,$(SRCS)))

$(OBJ_DIR)/%.o: $(LIB_DIR)/%.c | $(OBJ_DIR)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

# =========================
# REGRAS PRINCIPAIS
# =========================
all: download_cjson download_dlls $(TARGET)

$(TARGET): $(OBJS) | $(BIN_DIR)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(BIN_DIR):
	@mkdir -p $(BIN_DIR)

# =========================
# DOWNLOAD AUTOMÁTICO DO cJSON (Windows)
# =========================
download_cjson: | $(LIB_DIR)
	@echo "🔽 Baixando cJSON..."
	@if [ ! -d "$(LIB_DIR)/cJSON" ]; then \
		curl -L -o cJSON.zip https://github.com/DaveGamble/cJSON/archive/refs/heads/master.zip; \
		unzip -q cJSON.zip -d $(LIB_DIR); \
		mv $(LIB_DIR)/cJSON-master $(LIB_DIR)/cJSON; \
		rm cJSON.zip; \
		echo "✅ cJSON baixado e extraído"; \
	else \
		echo "✅ cJSON já existe"; \
	fi

# =========================
# DOWNLOAD DE DLLs (Windows 64-bit automático)
# =========================
# =========================
# DOWNLOAD DE DLLs E LIBS SDL2 (Windows)
# =========================
download_dlls:
	@echo "🔽 Baixando SDL2 64-bit DLLs e libs para MinGW..."

	# SDL2 runtime
	@curl -L https://github.com/libsdl-org/SDL/releases/download/release-2.28.5/SDL2-2.28.5-win32-x64.zip -o sdl2.zip
	# SDL2_ttf runtime
	@curl -L https://github.com/libsdl-org/SDL_ttf/releases/download/release-2.20.2/SDL2_ttf-2.20.2-win32-x64.zip -o sdl2_ttf.zip
	# SDL2_mixer development (contém DLLs e libs .a para MinGW)
	@curl -L https://github.com/libsdl-org/SDL_mixer/releases/download/release-2.8.1/SDL2_mixer-devel-2.8.1-mingw.tar.gz -o sdl2_mixer.tar.gz

	# Extrair DLLs
	@unzip -j sdl2.zip "*.dll" -d lib/
	@unzip -j sdl2_ttf.zip "*.dll" -d lib/

	# Extrair SDL2_mixer (usa tar, pois é .tar.gz)
	@tar -xzf sdl2_mixer.tar.gz
	@cp -f SDL2_mixer-2.8.1/x86_64-w64-mingw32/bin/*.dll lib/ 2>/dev/null || true
	@cp -f SDL2_mixer-2.8.1/x86_64-w64-mingw32/lib/*.a lib/ 2>/dev/null || true
	@cp -rf SDL2_mixer-2.8.1/x86_64-w64-mingw32/include/SDL2/* include/SDL2/ 2>/dev/null || true

	# DLLs adicionais 64-bit
	@curl -L https://www.dll-files.com/zlib1.dll?download -o lib/zlib1.dll
	@curl -L https://www.dll-files.com/libfreetype-6.dll?download -o lib/libfreetype-6.dll

	# Limpeza
	@rm -rf sdl2.zip sdl2_ttf.zip sdl2_mixer.tar.gz SDL2_mixer-2.8.1
	@echo "✅ Todas as DLLs e bibliotecas SDL2 (x64) foram baixadas para lib/ e include/SDL2/"


copy_dlls: | $(BIN_DIR)
	@echo "Copiando DLLs para $(BIN_DIR)..."
	@for dll in lib/*.dll; do \
		cp -f $$dll $(BIN_DIR)/; \
		echo "`basename $$dll` copiada"; \
	done
	@echo "✅ DLLs copiadas."
# =========================
# Limpeza
# =========================
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR) $(LIB_DIR)/cJSON
	@echo "🧹 Limpeza concluída!"

# =========================
# Rodar
# =========================
run: 
	@./$(TARGET)

rebuild: clean all run

# =========================
# PHONY
# =========================
.PHONY: all clean run rebuild copy_dlls download_dlls download_cjson
