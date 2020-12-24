OUT_DIR			= ./output
SRC 			= ./src
LINK_TARGET 	= $(OUT_DIR)/main.out
SRC_FILES 		= $(shell find $(SRC) -name '*.cpp')
OBJS 			= $(patsubst $(SRC)/%.cpp, $(OUT_DIR)/%.o, $(SRC_FILES))
REBUILDABLES	= $(OBJS) $(LINK_TARGET)
CC_FLAGS		= -std=c++17 -Wall -g
CC				= clang++

all: $(LINK_TARGET)
	@echo "compilation success ✅"

$(LINK_TARGET): $(OBJS)
	$(CC) $(CC_FLAGS) -o $@ $(shell find $(OUT_DIR) -name '*.o')

$(OUT_DIR)/%.o: $(SRC)/%.cpp
	$(CC) $(CC_FLAGS) -o $(OUT_DIR)/$(@F) -c $<

clean:
	rm -f $(OUT_DIR)/*
	@echo "clean done ✨"

run:
	./output/main.out
