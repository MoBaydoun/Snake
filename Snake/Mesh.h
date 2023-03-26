#pragma once

#include "Includes.h"

struct VertexData
{
    std::vector<GLfloat> positions;
    std::vector<GLfloat> normals;
    std::vector<GLfloat> texCoords;
    std::vector<GLfloat> colors;
};

class Mesh
{
public:
    Mesh(const char *objName)
    {
        LoadObjModel(objName);
    }
    
    void LoadObjModel(const char *objName);
    
    const VertexData& GetVertices() const { return vertices; }
    const std::vector<GLuint>& GetIndices() const { return indices; }
private:
    VertexData vertices;
    std::vector<GLuint> indices;
};

void Mesh::LoadObjModel(const char *objName)
{
    const char *filePath = Utilities::FindPath(objName);
    std::ifstream file{filePath};
    std::string line;
    while (std::getline(file, line)) {
        if (line.substr(0, 2) == "v ") {
            std::istringstream s{line.substr(2)};
            GLfloat x, y, z;
            s >> x >> y >> z;
            this->vertices.positions.push_back(x);
            this->vertices.positions.push_back(y);
            this->vertices.positions.push_back(z);
        } else if (line.substr(0, 3) == "vn ") {
            std::istringstream s{line.substr(3)};
            GLfloat x, y, z;
            s >> x >> y >> z;
            this->vertices.normals.push_back(x);
            this->vertices.normals.push_back(y);
            this->vertices.normals.push_back(z);
        } else if (line.substr(0, 3) == "vt ") {
            std::istringstream s{line.substr(3)};
            GLfloat x, y;
            s >> x >> y;
            this->vertices.texCoords.push_back(x);
            this->vertices.texCoords.push_back(y);
        } else if (line.substr(0, 2) == "f ") {
            std::istringstream s{line.substr(2)};
            std::string tri1, tri2, tri3;
            s >> tri1;
            s >> tri2;
            s >> tri3;
            std::stringstream elem1{tri1};
            std::stringstream elem2{tri2};
            std::stringstream elem3{tri3};
            std::string v1, v2, v3;
            std::getline(elem1, v1, '/');
            this->indices.push_back(std::stoi(v1) - 1);
            std::getline(elem1, v1, '/');
            //vt
            std::getline(elem1, v1, '/');
            //vn
            std::getline(elem2, v2, '/');
            this->indices.push_back(std::stoi(v2) - 1);
            std::getline(elem2, v2, '/');
            //vt
            std::getline(elem2, v2, '/');
            //vn
            std::getline(elem3, v3, '/');
            this->indices.push_back(std::stoi(v3) - 1);
            std::getline(elem3, v3, '/');
            //vt
            std::getline(elem3, v3, '/');
            //vn
        }
    }
    for (int i = 0; i < this->vertices.positions.size(); i += 3)
    {
        this->vertices.colors.push_back(1.0f);
        this->vertices.colors.push_back(0.0f);
        this->vertices.colors.push_back(1.0f);
        this->vertices.colors.push_back(1.0f);
    }
}
