#include "../include/Mesh.h"
#include <fstream>
#include <sstream>
#include <unordered_map>
using namespace Bwt::Resources;

bool Mesh::LoadFromOBJ(const std::filesystem::path& filepath)
{
	std::ifstream file(filepath);
	if (!file.is_open())
		return false;

	std::vector<Vector3> positions;
	std::vector<Vector3> normals;
	std::vector<Vector2> texcoords;

	std::unordered_map<std::string, uint32_t> vertexMap;

	std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string prefix;
        iss >> prefix;
        
        if (prefix == "v") {
            Vector3 pos;
            iss >> pos.x >> pos.y >> pos.z;
            positions.push_back(pos);
        }
        else if (prefix == "vt") {
            Vector2 uv;
            iss >> uv.u >> uv.v;
            texcoords.push_back(uv);
        }
        else if (prefix == "vn") {
            Vector3 normal;
            iss >> normal.x >> normal.y >> normal.z;
            normals.push_back(normal);
        }
        else if (prefix == "f") {
            std::string v[3];
            iss >> v[0] >> v[1] >> v[2];

            for (int i = 0; i < 3; ++i) {
                if (vertexMap.count(v[i]) == 0) {
                    std::istringstream vss(v[i]);
                    std::string posIndexStr, texIndexStr, normIndexStr;

                    std::getline(vss, posIndexStr, '/');
                    std::getline(vss, texIndexStr, '/');
                    std::getline(vss, normIndexStr, '/');

                    int pi = std::stoi(posIndexStr) - 1;
                    int ti = std::stoi(texIndexStr) - 1;
                    int ni = std::stoi(normIndexStr) - 1;

                    Vertex vert;
                    vert.position = positions[pi];
                    vert.textureUV = texcoords[ti];
                    vert.normal = normals[ni];

                    vertices.push_back(vert);
                    uint32_t index = static_cast<uint32_t>(vertices.size() - 1);
                    vertexMap[v[i]] = index;
                }

                indices.push_back(vertexMap[v[i]]);
            }
        }

        
    }

    file.close();
    return true;
}

void Bwt::Resources::Mesh::CreateBufferForShader()
{
    glCreateVertexArrays(1, &VAO);
    glCreateBuffers(1, &VBO);
    glCreateBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float) * 8, vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int),
        indices.data(), GL_STATIC_DRAW);
    // vertex positions
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    glEnableVertexAttribArray(0);
    // vertex normals
    
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3 * (sizeof(float))));
    glEnableVertexAttribArray(1);
    // vertex texture coords
    
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(6 * (sizeof(float))));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);
}

void Bwt::Resources::Mesh::Draw()
{
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

std::vector<float> Bwt::Resources::Mesh::GetVertexData()
{
    std::vector<float> data;
    for (int i = 0; i < vertices.size(); i+= 8)
    {
        data.push_back(vertices[i].position.x);
        data.push_back(vertices[i].position.y);
        data.push_back(vertices[i].position.z);

        data.push_back(vertices[i].normal.x);
        data.push_back(vertices[i].normal.y);
        data.push_back(vertices[i].normal.z);

        data.push_back(vertices[i].textureUV.u);
        data.push_back(vertices[i].textureUV.v);
    }
    return data;
}
