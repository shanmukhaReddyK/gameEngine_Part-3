CXX    := g++
OUTPUT := sfmlgame

LIB_PATH := -L ./external/SFML/lib
RPATH    := -Wl,-rpath,'$$ORIGIN/../external/SFML/lib'
INCLUDES  := -I./src -I ./src/imgui -I ./external/

ifeq ($(DEBUG),1)
	CXX_FLAGS := -g -O0 -std=c++20 -Wall -Wextra -Wno-unused-result -Wno-deprecated-declarations -no-pie -Wno-reoder
	LDFLAGS   := $(LIB_PATH) $(RPATH) -g -no-pie -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lGL
else
	CXX_FLAGS := -O3 -std=c++20 -Wno-unused-result -Wno-deprecated-declarations -Wno-reoder
	LDFLAGS   := $(LIB_PATH) $(RPATH) -O3 -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lGL
endif

SRC_FILES := $(wildcard src/*.cpp src/imgui/*.cpp)
OBJ_FILES := $(SRC_FILES:.cpp=.o)
DEP_FILES := $(SRC_FILES:.cpp=.d)

-include $(DEP_FILES)

all: $(OUTPUT)

$(OUTPUT): $(OBJ_FILES) Makefile
	$(CXX) $(OBJ_FILES) $(LDFLAGS) -o ./bin/$(OUTPUT)

.cpp.o:
	$(CXX) -MMD -MP -c $(CXX_FLAGS) $(INCLUDES) $< -o $@

clean:
	rm -f $(OBJ_FILES) $(DEP_FILES) ./bin/$(OUTPUT)

run: $(OUTPUT)
	cd bin && ./$(OUTPUT)

#for nvim clangd lsp
compiledb: clean
	@echo "[" > compile_commands.json
	@first=1; for file in $(SRC_FILES); do \
		if [ $$first -eq 0 ]; then echo "," >> compile_commands.json; fi; \
		first=0; \
		echo "  {" >> compile_commands.json; \
		echo "    \"directory\": \"$(shell pwd)\"," >> compile_commands.json; \
		echo "    \"command\": \"$(CXX) -c $(CXX_FLAGS) $(INCLUDES) $$file\"," >> compile_commands.json; \
		echo "    \"file\": \"$$file\"" >> compile_commands.json; \
		echo "  }" >> compile_commands.json; \
	done
	@echo "]" >> compile_commands.json
	@echo "Generated compile_commands.json successfully!"
