#pragma once

#include "Player.hpp"
#include "Item.hpp"
#include "Shader.hpp"

class Render
{
    public:
        void SpecifyObjects();
        template<typename Type> void SpecifyObject(std::string name, std::shared_ptr<Type>& object, std::vector<std::shared_ptr<Type>>& objectList);

        template<typename Type> void SpecifyVertices(std::shared_ptr<Type>& object);
        template<typename Type> void PreDraw(std::shared_ptr<Type>& object); 
        template<typename Type> void Draw(std::shared_ptr<Type>& object);

        void PreDrawObjects();
        void DrawObjects();
        void CleanupObjects();
        
        void predrawinit();

        template<typename Type> void objectcleanup(std::shared_ptr<Type>& object);
        void vertexcleanup();
        void drawcleanup();
    
    private:
        std::vector<GLfloat> defaultQuadVertices =
        {
            // Vertex 0
            -0.5f, -0.5f, 0.0f, // Bottom left vertex position
            1.0f, 0.0f, 0.0f,   // Bottom left vertex color
            // Vertex 1
            0.5f, -0.5f, 0.0f,  // Bottom right vertex position
            0.0f, 1.0f, 0.0f,   // Bottom right vertex color
            // Vertex 2
            -0.5f, 0.5f, 0.0f,  // Top left vertex position
            0.0f, 0.0f, 1.0f,   // Top left vertex color
            // Vertex 3
            0.5f, 0.5f, 0.0f,   // Top right vertex position
            1.0f, 0.0f, 0.0f    // Top right vertex color
        };
        std::vector<GLuint> defaultQuadIndices =
        {
            0, 1, 2, // Triangle 1
            3, 2, 1  // Triangle 2
        };
};
extern Render render;