ifneq ($(OS), Windows_NT)
  UNAME := $(shell uname -s)
endif

CXX = g++
CC = gcc
#CXXFLAGS = -s -O3 -std=c++20 -DNDEBUG -D_FORTIFY_SOURCE=2 -fstack-protector-strong
#CFLAGS = -s -O3 -DNDEBUG -D_FORTIFY_SOURCE=2 -fstack-protector-strong
CXXFLAGS = -g -O2 -std=c++20 -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC -D_FORTIFY_SOURCE=2 -fstack-protector-strong
CFLAGS = -g -O2 -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC -D_FORTIFY_SOURCE=2 -fstack-protector-strong

WARNINGS = -Wall -Wextra -Wpedantic -Wconversion -Wshadow -Wcast-qual -Wcast-align -Wfloat-equal -Wlogical-op -Wduplicated-cond -Wshift-overflow=2 -Wformat=2
INCLUDES = -Iprogram/include
ifeq ($(OS), Windows_NT)
  ECHO = echo -e
  SYSTEM_INCLUDES = -isystemexternal/include -isystemexternal/include/glad -isystemexternal/include/glm -isystemexternal/include/khr -isystemexternal/include/sdl2/windows -isystemexternal/include/stb
  LIBRARIES = -Lexternal/library/sdl2/windows -static -Wl,-Bstatic -lgcc -lstdc++ -lssp -lwinpthread -Wl,-Bdynamic -lSDL2
  OUTPUT = binary/windows/SimpleGameEngine.exe
else
  ifeq ($(UNAME), Linux)
    ECHO = echo
    SYSTEM_INCLUDES = -isystemexternal/include -isystemexternal/include/glad -isystemexternal/include/glm -isystemexternal/include/khr -isystemexternal/include/sdl2/linux -isystemexternal/include/stb
    LIBRARIES = -Lexternal/library/sdl2/linux -static-libgcc -static-libstdc++ -ldl -lpthread -lSDL2 -Wl,-rpath,'$$ORIGIN'
    OUTPUT = binary/linux/SimpleGameEngine.out
  endif
  #ifeq ($(UNAME), Darwin)
  #endif
endif

PROGRAM_SOURCE_DIRECTORY = program/source
EXTERNAL_SOURCE_DIRECTORY = external/source
OBJECTS_DIRECTORY = binary/object
CPP_SOURCES = $(wildcard $(PROGRAM_SOURCE_DIRECTORY)/*.cpp)
C_SOURCES = $(wildcard $(EXTERNAL_SOURCE_DIRECTORY)/*.c)
OBJECTS = $(patsubst $(PROGRAM_SOURCE_DIRECTORY)/%.cpp,$(OBJECTS_DIRECTORY)/%.o,$(CPP_SOURCES)) $(patsubst $(EXTERNAL_SOURCE_DIRECTORY)/%.c,$(OBJECTS_DIRECTORY)/%.o,$(C_SOURCES))

COMMANDS_DIRECTORY = compile_commands.json
FORMAT_DIRECTORY = .clang-format
CLANGD_DIRECTORY = .clangd
STYLE = BasedOnStyle: LLVM
TAB_WIDTH = IndentWidth: 2
INITIALIZER_WIDTH = ConstructorInitializerIndentWidth: 2
CONTINUATION_WIDTH = ContinuationIndentWidth: 2
BRACES = BreakBeforeBraces: Allman
LANGUAGE = Language: Cpp
LIMIT = ColumnLimit: 100
BLOCKS = AllowShortBlocksOnASingleLine: true
FUNCTIONS = AllowShortFunctionsOnASingleLine: true
IFS = AllowShortIfStatementsOnASingleLine: true
LOOPS = AllowShortLoopsOnASingleLine: true
CASE_LABELS = AllowShortCaseLabelsOnASingleLine: true
PP_DIRECTIVES = IndentPPDirectives: BeforeHash
NAMESPACE_INDENTATION = NamespaceIndentation: All
NAMESPACE_COMMENTS = FixNamespaceComments: false
INDENT_CASE_LABELS = IndentCaseLabels: true
BREAK_TEMPLATE_DECLARATIONS = AlwaysBreakTemplateDeclarations: false

all: compile_commands clang-format clangd object $(OUTPUT)

compile_commands:
	@$(ECHO) "[" > $(COMMANDS_DIRECTORY)
	@for source in $(CPP_SOURCES); do $(ECHO) "\t{ \"directory\": \"$(CURDIR)\", \"command\": \"$(CXX) $(CXXFLAGS) $(WARNINGS) $(INCLUDES) $(SYSTEM_INCLUDES) -c $$source -o $(OBJECTS_DIRECTORY)/$$(basename $$source .cpp).o\", \"file\": \"$$source\" },"; done >> $(COMMANDS_DIRECTORY)
	@for source in $(C_SOURCES); do $(ECHO) "\t{ \"directory\": \"$(CURDIR)\", \"command\": \"$(CC) $(CFLAGS) $(INCLUDES) $(SYSTEM_INCLUDES) -c $$source -o $(OBJECTS_DIRECTORY)/$$(basename $$source .c).o\", \"file\": \"$$source\" },"; done >> $(COMMANDS_DIRECTORY)
	@sed -i "$$ s/,$$//" $(COMMANDS_DIRECTORY)
	@$(ECHO) "]" >> $(COMMANDS_DIRECTORY)
	@$(ECHO) "Write | $(COMMANDS_DIRECTORY)"

clang-format:
	@$(ECHO) "---\n$(STYLE)\n$(TAB_WIDTH)\n$(INITIALIZER_WIDTH)\n$(CONTINUATION_WIDTH)\n$(BRACES)\n---\n$(LANGUAGE)\n$(LIMIT)\n$(BLOCKS)\n$(FUNCTIONS)\n$(IFS)\n$(LOOPS)\n$(CASE_LABELS)\n$(PP_DIRECTIVES)\n$(NAMESPACE_INDENTATION)\n$(NAMESPACE_COMMENTS)\n$(INDENT_CASE_LABELS)\n$(BREAK_TEMPLATE_DECLARATIONS)\n..." > $(FORMAT_DIRECTORY)
	@find program -type f \( -name "*.cpp" -o -name "*.hpp" \) -print0 | xargs -0 -I{} sh -c 'clang-format -i "{}"'
	@$(ECHO) "Write | $(FORMAT_DIRECTORY)"

clangd:
	@$(ECHO) "Diagnostics:\n\tUnusedIncludes: None" > $(CLANGD_DIRECTORY)
	@$(ECHO) "Write | $(CLANGD_DIRECTORY)"

object:
	@if [ ! -d "$(OBJECTS_DIRECTORY)" ]; then mkdir -p $(OBJECTS_DIRECTORY); $(ECHO) "Write | $(OBJECTS_DIRECTORY)"; fi

$(OUTPUT): $(OBJECTS)
	@$(CXX) $(CXXFLAGS) $(WARNINGS) $(INCLUDES) $(SYSTEM_INCLUDES) $(OBJECTS) $(LIBRARIES) -o $(OUTPUT)
	@$(ECHO) "Link  | $(OBJECTS) -> $(OUTPUT)"
$(OBJECTS_DIRECTORY)/%.o: $(PROGRAM_SOURCE_DIRECTORY)/%.cpp
	@$(CXX) $(CXXFLAGS) $(WARNINGS) $(INCLUDES) $(SYSTEM_INCLUDES) -c $< -o $@
	@$(ECHO) "CXX   | $< -> $@"
$(OBJECTS_DIRECTORY)/%.o: $(EXTERNAL_SOURCE_DIRECTORY)/%.c
	@$(CC) $(CFLAGS) $(INCLUDES) $(SYSTEM_INCLUDES) -c $< -o $@
	@$(ECHO) "CC    | $< -> $@"

clean:
	@if [ -d "$(OBJECTS_DIRECTORY)" ]; then rm -r $(OBJECTS_DIRECTORY); fi
	@if [ -f $(OUTPUT) ]; then rm -r $(OUTPUT); fi
