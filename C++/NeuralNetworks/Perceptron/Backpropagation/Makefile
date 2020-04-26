CXX 			= g++
CXXEXT 			= cpp
CXXFLAGS		= -Wall -MMD -MP

SRC_DIR 		= src
INC_DIR			= include 
LIB_DIR 		= libs
BUILD_DIR 		= build

LIBS			= -lsfml-graphics -lsfml-window -lsfml-system -lGL -lthor 

COMPILE_FLAGS 	= $(INC_DIR:%=-I %) $(CXXFLAGS)
LINKING_FLAGS 	= $(LIB_DIR:%=-L %) $(LIB_DIR:%=-Wl,-rpath %) $(LIBS)

TARGET 			= run
SOURCES 		= $(shell find $(SRC_DIR) -type f -name *.$(CXXEXT))
OBJECTS 		= $(SOURCES:$(SRC_DIR)/%.$(CXXEXT)=$(BUILD_DIR)/%.o)
DEPENDENCIES 	= $(OBJECTS:.o=.d)


all: $(TARGET)
	./$(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $^ -o $(TARGET) $(LINKING_FLAGS)

.PRECIOUS: $(BUILD_DIR)/. $(BUILD_DIR)%/.

$(BUILD_DIR)/.:
	mkdir -p $@

$(BUILD_DIR)%/.:
	mkdir -p $@

.SECONDEXPANSION:

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.$(CXXEXT) | $$(@D)/.
	$(CXX) $(COMPILE_FLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -r $(BUILD_DIR) $(TARGET) 

-include $(DEPENDENCIES)
