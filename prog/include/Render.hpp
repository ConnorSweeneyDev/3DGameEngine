#pragma once

#include "Player.hpp"

class Render
{
    public:
        void DefineVertices();
        
        void predrawinit();

        void vertexcleanup();
        void drawcleanup();

    private:

};
extern Render render;
