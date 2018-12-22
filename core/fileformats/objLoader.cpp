#include <sstream>
#include <regex>
#include <fstream>

#include "core/fileformats/objLoader.h"
#include "core/utils/utils.h"
#include "core/buffers/bufferFactory.h"

#include "core/fileformats/bmpLoader.h"

using namespace std;

namespace corecvs {


static const char *com_vertex          = "v";
static const char *com_vertex_texture  = "vt";
static const char *com_vertex_normal   = "vn";
static const char *com_face            = "f";

static const char *com_use_material    = "usemtl";
static const char *com_material_lib    = "mtllib";

OBJLoader::OBJLoader()
{
}

OBJLoader::~OBJLoader()
{
}

#define LOCAL_PRINT(X) if (trace) { SYNC_PRINT(X); }

int OBJLoader::loadOBJ(istream &input, Mesh3DDecorated &mesh)
{
    int texName = 0;

    string line;
    while (!input.eof())
    {
        HelperUtils::getlineSafe (input, line);

        if (HelperUtils::startsWith(line, "#")) {
            cout << "Skipping comment " << line << endl;
            continue;
        }

        istringstream work(line);
        string command;
        work >> command;

        // LOCAL_PRINT(("Input line: %s\n", line.c_str()));

        if (command == com_vertex)
        {
            Vector3dd vertex;
            work >> vertex.x() >> vertex.y() >> vertex.z();

            mesh.addPoint(vertex);
        }
        if (command == com_vertex_texture)
        {
            Vector2dd tex;
            work >> tex.x() >> tex.y();
         //   LOCAL_PRINT(("Tex: %lf %lf\n", tex.x(), tex.y()));
            mesh.textureCoords.push_back(tex);         
        }
        if (command == com_vertex_normal)
        {
            Vector3dd normal;
            work >> normal.x() >> normal.y() >> normal.z();
         //   LOCAL_PRINT(("Normal line: %lf %lf %lf\n", normal.x(), normal.y(), normal.z()));
            mesh.normalCoords.push_back(normal);
        }
        if (command == com_face)
        {
            string strs[3];
            work >> strs[0] >> strs[1] >> strs[2];
            Vector3d32 face;
            Vector3d32 normId(-1);
            Vector4d32 texId(-1, -1, -1, texName);

            //LOCAL_PRINT(("Face line: %s\n", work.str().c_str()));

            for (int i = 0; i < 3; i++)
            {
                // LOCAL_PRINT(("Attribute: %s\n", strs[i].c_str()));
                std::stringstream splitter(strs[i]);
                std::string part;

                for (int j = 0; j < 3 && std::getline(splitter, part, '/'); j++)
                {
                    if (j == 0) {
                        int id = std::stoi(part);
                        face[i] = id - 1;
                    }

                    if (j == 1) {
                        int id = std::stoi(part);
                        texId[i] = id - 1;
                    }

                    if (j == 2) {
                        int id = std::stoi(part);
                        normId[i] = id - 1;
                    }
                }
            }
            mesh.addFace(face);
            mesh.texId.push_back(texId);
            mesh.normalId.push_back(normId);
        }
        if (command == com_use_material)
        {
            string name;
            work >> name;

            texName = 0;
            for (size_t t = 0; t < mesh.materials.size(); t++)
            {
                if (mesh.materials[t].name == name)
                {
                    texName = (int)t;
                }
            }

             cout << "Use material command: <" << name << "> id " << texName << " (" << mesh.materials.size() << ")" << endl;
        }
        if (command == com_material_lib)
        {
            cout << "Material library command: This is not fully supported" << endl;

        }
    }

    if (!mesh.normalCoords.empty())
        mesh.hasNormals = true;

    if (!mesh.textureCoords.empty())
        mesh.hasTexCoords = true;

    /* sanity checking */
    mesh.dumpInfo(cout);

    mesh.verify();

    return 0;
}

int OBJLoader::loadMaterials(istream &input, vector<OBJMaterial> &materials, const std::string &path)
{
    int count = 0;
    string line;

    OBJMaterial material;

    while (input.good())
    {
        count++;
        HelperUtils::getlineSafe (input, line);

        cout << "Line " << count << " <" <<  line << ">" << endl;

        if (HelperUtils::startsWith(line, "#")) {
            cout << "OBJLoader::loadMaterial: Skipping comment " << line << endl;
            continue;
        }

        istringstream work(line);
        string command;
        work >> command;

        cout << "OBJLoader::loadMaterial: command: " << command << endl;

        if (command == "newmtl") {
            if (!material.name.empty())
                materials.push_back(material);
            material = OBJMaterial();

            std::string material_name;
            work >> material_name;
            material.name = material_name;
        }



        int koef_id = OBJMaterial::KOEF_LAST;
        if (command == "Ka")
            koef_id = OBJMaterial::KOEF_AMBIENT;
        if (command == "Kd")
            koef_id = OBJMaterial::KOEF_DIFFUSE;
        if (command == "Ks")
            koef_id = OBJMaterial::KOEF_SPECULAR;

        if (koef_id != OBJMaterial::KOEF_LAST)
        {
            cout << "Will load koef" << endl;
            work >> material.koefs[koef_id].x();
            work >> material.koefs[koef_id].y();
            work >> material.koefs[koef_id].z();
        }


        int tex_id = OBJMaterial::TEX_LAST;
        std::string tex_name;
        if (command == "map_Ka")
            tex_id =  OBJMaterial::TEX_AMBIENT;
        if (command == "map_Kd")
            tex_id =  OBJMaterial::TEX_DIFFUSE;
        if (command == "map_Ks")
            tex_id =  OBJMaterial::TEX_SPECULAR;
        if (command == "map_bump")
            tex_id =  OBJMaterial::TEX_BUMP;

        if (tex_id != OBJMaterial::TEX_LAST)
        {
            work >> tex_name;
            std::string fullpath = path + PATH_SEPARATOR + tex_name;
            cout << "Will load texture <" << tex_name << "> ";
            cout << "full path <" << fullpath << ">" << endl;

            RGB24Buffer *texture = BufferFactory::getInstance()->loadRGB24Bitmap(fullpath);
            if (texture != NULL) {
                cout << "Texture <" << texture->getSize() << ">" << endl;
            } else {
                cout << "Failed to load texture" << endl;
            }

            material.tex[tex_id] = texture;
        }
    }
    if (!material.name.empty())
        materials.push_back(material);

    cout << "Loaded :" << materials.size() << endl;
    for (OBJMaterial &m : materials)
    {
        cout << "    <" << m.name << ">" << endl;
    }


   return 0;
}

int OBJLoader::loadOBJSimple(istream &input, Mesh3D &mesh)
{
    string line;
    while (!input.eof())
    {
        HelperUtils::getlineSafe (input, line);

        if (HelperUtils::startsWith(line, "#")) {
            cout << "Skipping comment " << line << endl;
            continue;
        }

        istringstream work(line);
        string command;
        work >> command;

        // LOCAL_PRINT(("Input line: %s\n", line.c_str()));

        if (command == com_vertex)
        {
            Vector3dd vertex;
            work >> vertex.x() >> vertex.y() >> vertex.z();

            mesh.addPoint(vertex);
        }
        if (command == com_vertex_texture)
        {
        }
        if (command == com_vertex_normal)
        {
        }
        if (command == com_face)
        {
            string strs[3];
            work >> strs[0] >> strs[1] >> strs[2];
            Vector3d32 face;

            for (int i = 0; i < 3; i++)
            {
                // LOCAL_PRINT(("Attribute: %s\n", strs[i].c_str()));
                std::stringstream splitter(strs[i]);
                std::string part;

                for (int j = 0; j < 1 && std::getline(splitter, part, '/'); j++)
                {
                    int id = std::stoi(part);
                    face[i] = id - 1;
                }
            }
            mesh.addFace(face);
        }


    }

    return 0;
}

int OBJLoader::saveOBJSimple(ostream &out, Mesh3D &mesh)
{
    vector<Vector3dd>  &vertexes = mesh.vertexes;
    vector<Vector3d32> &faces    = mesh.faces;
    //vector<Vector2d32> &edges    = mesh.edges;

    for (unsigned i = 0; i < vertexes.size(); i++)
    {
        out << "v "
            << vertexes[i].x() << " "
            << vertexes[i].y() << " "
            << vertexes[i].z() << " " << endl;

    }

    for (unsigned i = 0; i < faces.size(); i++)
    {
        out << "f "
            << (faces[i].x() + 1) << " "
            << (faces[i].y() + 1) << " "
            << (faces[i].z() + 1) << " ";
        out << std::endl;
    }

    return 0;
}



int OBJLoader::saveMaterials(const string &fileName, vector<OBJMaterial> &materials, const string &/*path*/)
{
    ofstream out;
    out.open(fileName, ios::out);
    if (out.fail())
    {
        SYNC_PRINT(("MeshLoader::saveMaterials(): Can't open mesh file <%s> for writing\n", fileName.c_str()));
        return false;
    }

    for (size_t t = 0; t < materials.size(); t++ )
    {
        out << "newmtl " << materials[t].name << endl;

        std::stringstream texname;
        texname << "tex" << t << ".bmp";

        out << "map_Ka " << texname.str() << endl;

        if (materials[t].tex[OBJMaterial::TEX_AMBIENT] != NULL)
        {
            BMPLoader().save(texname.str(), materials[t].tex[OBJMaterial::TEX_AMBIENT]);
        }
    }

    out.close();
    return 0;
}

int OBJLoader::saveObj(const  string &fileName, Mesh3DDecorated &mesh)
{
    vector<Vector3dd>  &vertexes = mesh.vertexes;
    vector<Vector3d32> &faces    = mesh.faces;

    vector<Vector2dd> &texuv    = mesh.textureCoords;
    vector<Vector3dd> &normals  = mesh.normalCoords;
    //vector<Vector2d32> &edges    = mesh.edges;

    int currentMaterial = -1;

    ofstream out;
    out.open(fileName + ".obj", ios::out);
    if (out.fail())
    {
        SYNC_PRINT(("MeshLoader::save(): Can't open mesh file <%s> for writing\n", fileName.c_str()));
        return false;
    }

    out << "mtllib " << fileName << ".mtl" << endl;


    for (unsigned i = 0; i < vertexes.size(); i++)
    {
        out << "v "
            << vertexes[i].x() << " "
            << vertexes[i].y() << " "
            << vertexes[i].z() << " " << endl;

    }

    if (mesh.hasTexCoords)
    {
        for (unsigned i = 0; i < texuv.size(); i++)
        {
            out << "vt "
                << texuv[i].x() << " "
                << texuv[i].y() << " " << endl;

        }
    }

    if (mesh.hasNormals)
    {
        for (unsigned i = 0; i < normals.size(); i++)
        {
            out << "vn "
                << normals[i].x() << " "
                << normals[i].y() << " "
                << normals[i].z() << " " << endl;
        }
    }

    for (unsigned i = 0; i < faces.size(); i++)
    {
        if (mesh.hasTexCoords) {
            Vector4d32 &texid = mesh.texId[i];
            int t = texid[3];
            if (t != currentMaterial && t < (int)mesh.materials.size()) {
                out << "usemtl " << mesh.materials[t].name << endl;
                currentMaterial = t;
            }
        }

        out << "f ";
        out << (faces[i].x() + 1);
        out << "/";
        if (mesh.hasTexCoords) { out << mesh.texId[i][0] + 1; }
        out << "/";
        if (mesh.hasNormals  ) { out << mesh.normalId[i][0] + 1; }
        out << " ";

        out << (faces[i].y() + 1);
        out << "/";
        if (mesh.hasTexCoords) { out << mesh.texId[i][1] + 1; }
        out << "/";
        if (mesh.hasNormals  ) { out << mesh.normalId[i][1] + 1; }
        out << " ";

        out << (faces[i].z() + 1);
        out << "/";
        if (mesh.hasTexCoords) { out << mesh.texId[i][2] + 1; }
        out << "/";
        if (mesh.hasNormals  ) { out << mesh.normalId[i][2] + 1; }
        out << " ";
        out << std::endl;
    }

    return 0;

}

}
