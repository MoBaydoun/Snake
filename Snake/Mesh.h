#pragma once

#include "Includes.h"

struct VertexData
{
    std::vector<GLfloat> positions;
    std::vector<GLfloat> normals;
    std::vector<GLfloat> texCoords;
    std::vector<GLfloat> colors;
};

struct Vertex
{
    GLKVector3 position;
    GLKVector3 normal;
    GLKVector2 texCoord;
    
    Vertex(GLKVector3 pos, GLKVector3 norm, GLKVector2 tex) : position(pos), normal(norm), texCoord(tex) {}
};

class Mesh
{
public:
    Mesh(const char *objName)
    {
        LoadObjModelV2(objName);
    }
    
    void LoadObjModel(const char *objName);
    void LoadObjModelV2(const char *objName);
    
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
}

void Mesh::LoadObjModelV2(const char *objName)
{
    const char *filePath = Utilities::FindPath(objName);
    std::ifstream fin{filePath};

    std::vector<Vertex> verts{};

    std::vector<GLKVector3> positions{};
    std::vector<GLKVector2> texCoords{};
    std::vector<GLKVector3> normals{};

    std::vector<int> indices{};

    std::string currentLine;
    while (std::getline(fin, currentLine, '\n'))
    {
        std::istringstream iss(currentLine);
        std::string marker;
        iss >> marker;
        if (marker == "v")
        {
            float x;
            float y;
            float z;
            iss >> x;
            iss >> y;
            iss >> z;
            positions.emplace_back(GLKVector3{x, y, z});
        }
        else if (marker == "vt")
        {
            float x;
            float y;
            iss >> x;
            iss >> y;
            texCoords.emplace_back(GLKVector2{x, y});
        }
        else if (marker == "vn") {
            float x;
            float y;
            float z;
            iss >> x;
            iss >> y;
            iss >> z;
            normals.emplace_back(GLKVector3{x, y, z});
        }
        else if (marker == "f") {
            std::string tri1;
            iss >> tri1;
            std::stringstream elem1(tri1);

            std::string tri2;
            iss >> tri2;
            std::stringstream elem2(tri2);

            std::string tri3;
            iss >> tri3;
            std::stringstream elem3(tri3);

            //Waveform format is 1-indexed
            std::string v1s;
            std::getline(elem1, v1s, '/');
            int v1 = std::stoi(v1s) - 1;
            verts.emplace_back(Vertex(positions.at(v1), GLKVector3{0,0,0}, GLKVector2{0, 0}));
            std::getline(elem1, v1s, '/');
            verts.at(verts.size() - 1).texCoord = texCoords.at(std::stoi(v1s) - 1);
            std::getline(elem1, v1s, '/');
            verts.at(verts.size() - 1).normal = normals.at(std::stoi(v1s) - 1);
            indices.push_back(static_cast<int>(verts.size() - 1));

            std::string v2s;
            std::getline(elem2, v2s, '/');
            int v2 = std::stoi(v2s) - 1;
            verts.emplace_back(Vertex(positions.at(v2), GLKVector3{0,0,0}, GLKVector2{0, 0}));
            std::getline(elem2, v2s, '/');
            verts.at(verts.size() - 1).texCoord = texCoords.at(std::stoi(v2s) - 1);
            std::getline(elem2, v2s, '/');
            verts.at(verts.size() - 1).normal = normals.at(std::stoi(v2s) - 1);
            indices.push_back(static_cast<int>(verts.size() - 1));

            std::string v3s;
            std::getline(elem3, v3s, '/');
            int v3 = std::stoi(v3s) - 1;
            verts.emplace_back(Vertex(positions.at(v3), GLKVector3{0,0,0}, GLKVector2{0, 0}));
            std::getline(elem3, v3s, '/');
            verts.at(verts.size() - 1).texCoord = texCoords.at(std::stoi(v3s) - 1);
            std::getline(elem3, v3s, '/');
            verts.at(verts.size() - 1).normal = normals.at(std::stoi(v3s) - 1);
            indices.push_back(static_cast<int>(verts.size() - 1));
        }
    }
    for (int i = 0; i < verts.size(); ++i)
    {
        this->vertices.positions.push_back(verts[i].position.x);
        this->vertices.positions.push_back(verts[i].position.y);
        this->vertices.positions.push_back(verts[i].position.z);
        this->vertices.normals.push_back(verts[i].normal.x);
        this->vertices.normals.push_back(verts[i].normal.y);
        this->vertices.normals.push_back(verts[i].normal.z);
        this->vertices.texCoords.push_back(verts[i].texCoord.x);
        this->vertices.texCoords.push_back(verts[i].texCoord.y);
    }
    for (auto &i : indices)
    {
        this->indices.push_back(i);
    }
    //std::cout << "SMD" << std::endl;
}
