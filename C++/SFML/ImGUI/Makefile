CXX 		= g++
CXXEXT 		= cpp
CXXFLAGS	= 

SOURCE_PATH = Source
BUILD_PATH 	= Build

LIBRARIES	= -lsfml-graphics -lsfml-window -lsfml-system -lGL
INCLUDE		= -I Include/ -I Include/ImGUI

TARGET 		= run
SOURCES 	= $(shell find $(SOURCE_PATH) -type f -name *.$(CXXEXT))
OBJECTS 	= $(SOURCES:$(SOURCE_PATH)/%.$(CXXEXT)=$(BUILD_PATH)/%.o)


all: directory $(TARGET)
	./$(TARGET)

.PHONY: directory
directory:
	@mkdir -p $(BUILD_PATH)
	@mkdir -p $(BUILD_PATH)/ImGUI

$(TARGET): $(OBJECTS)
	$(CXX) $^ -o $(TARGET) $(LIBRARIES)

$(BUILD_PATH)/%.o: $(SOURCE_PATH)/%.$(CXXEXT)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -o $@

.PHONY: clean
clean:
	rm -r $(BUILD_PATH) $(TARGET) 
