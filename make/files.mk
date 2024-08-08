ifeq ($(UNAME), Windows)
  ECHO := echo -e
  RESOURCE_LOADER := binary/windows/ResourceLoader.exe
  OUTPUT_FILE := binary/windows/SimpleGameEngine.exe
else ifeq ($(UNAME), Linux)
  ECHO := echo
  RESOURCE_LOADER := binary/linux/ResourceLoader.out
  OUTPUT_FILE := binary/linux/SimpleGameEngine.out
#else ifeq ($(UNAME), Darwin)
endif

PROGRAM_SOURCE_DIRECTORY := program/source
PROGRAM_INCLUDE_DIRECTORY := program/include
EXTERNAL_SOURCE_DIRECTORY := external/source
OBJECT_DIRECTORY := binary/object
CPP_SOURCE_FILES := $(wildcard $(PROGRAM_SOURCE_DIRECTORY)/*.cpp)
CC_SOURCE_FILES := $(wildcard $(EXTERNAL_SOURCE_DIRECTORY)/*.c)
OBJECT_FILES := $(patsubst $(PROGRAM_SOURCE_DIRECTORY)/%.cpp,$(OBJECT_DIRECTORY)/%.o,$(CPP_SOURCE_FILES)) $(patsubst $(EXTERNAL_SOURCE_DIRECTORY)/%.c,$(OBJECT_DIRECTORY)/%.o,$(CC_SOURCE_FILES))
DEPENDENCY_FILES := $(patsubst $(OBJECT_DIRECTORY)/%.o,$(OBJECT_DIRECTORY)/%.d,$(OBJECT_FILES))

PROGRAM_SHADER_DIRECTORY := program/shader
RESOURCE_POSTFIX := _resource
RESOURCE_SOURCE_FILE := $(PROGRAM_SOURCE_DIRECTORY)/resource.cpp
RESOURCE_INCLUDE_FILE := $(PROGRAM_INCLUDE_DIRECTORY)/resource.hpp
RESOURCE_OBJECT_FILE := $(OBJECT_DIRECTORY)/resource.o
RESOURCE_FILES := $(RESOURCE_SOURCE_FILE) $(RESOURCE_INCLUDE_FILE)
SHADER_FILES := $(wildcard $(PROGRAM_SHADER_DIRECTORY)/*.glsl)

-include $(DEPENDENCY_FILES)
