CXX := gcc

CPPSTANDARD := c17

CXXFLAGS := -Wall -Wextra -Wsign-conversion -Wfloat-equal -Wundef -Wshadow -Wpointer-arith -Wcast-align -Wstrict-prototypes -Wwrite-strings -Wcast-qual -Wunreachable-code

SOURCE_FOLDER := ./src
SOURCE_FILES := $(wildcard */*.cpp)

HEADER_FOLDER := ./header
HEADER_FILES := $(wildcard */*.hpp)

OBJECT_FOLDERS := ./src/obj
OBJECT_FILES := $(addprefix $(OBJECT_FOLDERS)/,$(patsubst %.cpp,%.o,$(notdir $(SOURCE_FILES))))

main: $(OBJECT_FILES)
	$(CXX) $(CXXFLAGS) -std=$(CPPSTANDARD) -o $@ $^ -I$(HEADER_FOLDER)

$(OBJECT_FOLDERS)/%.o: $(SOURCE_FOLDER)/%.cpp $(HEADER_FILES)
	$(CXX) $(CXXFLAGS) -std=$(CPPSTANDARD) -c -o $@ $< -O2 -I$(HEADER_FOLDER)

.PHONY: clean

clean: 
	rm -f $(OBJECT_FOLDERS)/*.o