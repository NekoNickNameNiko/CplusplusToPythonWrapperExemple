#pragma once
#include "Interface.h"
#include "CommonInclude.h"
#include <buffer.h>
#include <Textures.h>

namespace Bwt
{
    namespace Resources
    {
        struct Vector3 { float x, y, z; };
        struct Vector2 { float u, v; };

        struct Vertex
        {
            Vector3 position;
            Vector3 normal;
            Vector2 textureUV;

            bool operator==(const Vertex& other) const
            {
                return position.x == other.position.x &&
                    position.y == other.position.y &&
                    position.z == other.position.z &&
                    normal.x == other.normal.x &&
                    normal.y == other.normal.y &&
                    normal.z == other.normal.z &&
                    textureUV.u == other.textureUV.u &&
                    textureUV.v == other.textureUV.v;
            }
        };

        class Mesh : public IResource
        {
        public:
            Mesh() = default;
            ~Mesh() = default;

            bool LoadFromOBJ(const std::filesystem::path& filepath);
            void CreateBufferForShader();
            void Draw();

            std::vector<float> GetVertexData();

            const std::vector<Vertex>& GetVertices() const { return vertices; }
            const std::vector<uint32_t>& GetIndices() const { return indices; }

            unsigned int VBO = 0;
            unsigned int EBO = 0;
            unsigned int VAO = 0;

            unsigned int gSamplerLocation;
            Texture* pTexture = nullptr;

        private:
            std::vector<Vertex> vertices;
            std::vector<uint32_t> indices;
        };

    }
}