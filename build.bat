@ECHO OFF

g++ -std=c++17 prog/*.cpp src/glad.c -Iprog/include -Isrc/include -Isrc/include/glad -Isrc/include/glm -Isrc/include/KHR -Isrc/include/SDL2 -Lsrc/lib -Wall -lmingw32 -lSDL2main -lSDL2 -o SDLGLTest
