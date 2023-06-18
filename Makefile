CC := g++
SFML_PATH := C:\Users\phili\OneDrive\Dokumente\Programming\libraries\SFML-2.5.1
SFML_INCLUDE := -I"$(SFML_PATH)\include" -DSFML_STATIC
SFML_LIB := -L"$(SFML_PATH)\lib" -lsfml-graphics-s -lsfml-window-s -lsfml-audio-s -lsfml-system-s -lopengl32 -lfreetype -lwinmm -lgdi32 -lopenal32 -lflac -lvorbisenc -lvorbisfile -lvorbis -logg

TARGET := main
SRCS := $(wildcard src/**/*.cpp) $(wildcard src/*.cpp)
OBJS := $(patsubst src/%.cpp,build/%.o,$(SRCS))

all: compile link run

compile: $(OBJS)

build/%.o: src/%.cpp
	@if not exist "$(dir $@)" mkdir "$(dir $@)"
	$(CC) -c $< -o $@ $(SFML_INCLUDE)


link:
	$(CC) $(OBJS) -o $(TARGET) $(SFML_LIB)

run:
	.\main

clean: $(SRCS)
	del /q $(TARGET).exe
	del /q /s build\*
	for /d %%i in (build\*) do @rd /q /s "%%i"