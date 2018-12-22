/**
 * \file main_test_fileformats.cpp
 * \brief This is the main file for the test fileformats
 *
 * \date Aug 22, 2010
 * \author alexander
 * \ingroup autotest
 */
#include <sstream>
#include <fstream>
#include <iostream>

#include <core/fileformats/pltLoader.h>
#include <core/fileformats/xyzListLoader.h>

#include "gtest/gtest.h"

#include "core/utils/global.h"

#include "core/fileformats/rawLoader.h"
#include "core/buffers/g12Buffer.h"
#include "core/fileformats/bmpLoader.h"
#include "core/fileformats/ppmLoader.h"
#include "core/fileformats/plyLoader.h"
#include "core/fileformats/objLoader.h"
#include "core/fileformats/gcodeLoader.h"

using namespace corecvs;

TEST(FileFormats, testFileFormats)
{
    /** Test case 1 */
    RAWLoaderBase *rawLoader = new RAWLoaderBase();
    G12Buffer *raw = rawLoader->loadG12("data/testdata/32x32_12h_test_raw.raw");
    if (raw == nullptr)
    {
        cout << "Could not open test image" << endl;
        return;
    }
    CORE_ASSERT_TRUE(raw != NULL, "RAW Image load failed");
    CORE_ASSERT_TRUE(raw->h == raw->w, "RAW Image sizes corrupted");
    CORE_ASSERT_TRUE(raw->verify(), "RAW Image verification failed");
    delete_safe(raw);
    delete_safe(rawLoader);

    /** Test case 2 */
    G12Buffer *bmp = BMPLoader().loadG12("data/testdata/test_bmp.bmp");
    CORE_ASSERT_TRUE(bmp->h == bmp->w, "BMP Image sizes corrupted");
    CORE_ASSERT_TRUE(bmp != NULL, "BMP Image load failed");
    CORE_ASSERT_TRUE(bmp->verify(), "BMP Image verification failed");
    delete_safe(bmp);

    /** Test case 3 */
    G12Buffer *ppm = PPMLoader().loadG12("data/testdata/test_ppm.ppm");
    CORE_ASSERT_TRUE(ppm == NULL, "test PPM with type:6 image has been loaded but shouldn't!");
    //CORE_ASSERT_TRUE(ppm->h == ppm->w, "PPM Image sizes corrupted");
    //CORE_ASSERT_TRUE(ppm->verify(), "PPM Image verification failed");
    delete_safe(ppm);

    /** Test case 4 */
    MetaData *metadata = new MetaData;
    G12Buffer *metappm = PPMLoader().loadG12("data/testdata/test_pgm_metadata.pgm", metadata);
    CORE_ASSERT_TRUE(metappm != NULL, "PGM with Metadata Image load failed");
    CORE_ASSERT_TRUE(metappm->h == metappm->w, "PGM with Metadata Image sizes corrupted");
    CORE_ASSERT_TRUE(metappm->verify(), "PGM with Metadata Image verification failed");
    CORE_ASSERT_TRUE(metadata->at("hello_world")[0] == 42, "PGM Metadata read failed");
    delete_safe(metappm);
    delete_safe(metadata);

    /** Test case 5 */
    G12Buffer *bmp1 = BMPLoader().loadG12("data/calib-object.bmp");
    CORE_ASSERT_TRUE(bmp1 != NULL, "BMP Image load failed");
    CORE_ASSERT_TRUE(bmp1->verify(), "BMP Image verification failed");
    delete_safe(bmp1);
}

TEST(FileFormats, DISABLED_testBMP24)
{
    BMPLoader *bmpLoader = new BMPLoader();
    bmpLoader->trace = true;
    G12Buffer   *bmp1 = bmpLoader->loadG12("first.bmp");
    RGB24Buffer *bmp2 = bmpLoader->loadRGB("first.bmp");

    cout << bmp1->h << " " << bmp1->w << endl;
    cout << bmp2->h << " " << bmp2->w << endl;

    bmpLoader->save("saved.bmp"   , bmp1);
    bmpLoader->save("savedrgb.bmp", bmp2);


    CORE_ASSERT_TRUE(bmp1 != NULL, "BMP Image load failed");
    CORE_ASSERT_TRUE(bmp1->verify(), "BMP Image verification failed");
    delete_safe(bmp1);
    delete_safe(bmpLoader);
}

TEST(FileFormats, testPlyLoader)
{
    const char *tests[4];
    tests[0] = "sdvfas";
    tests[1] =
        "ply\n"
        "format binary 2.0\n";

    tests[2] =
        "ply\n"
        "comment Blah Blah...\n"
        "format ascii 1.0\n";

    tests[3] =
        "ply\n"
        "format ascii 1.0\n"
        "comment made by Greg Turk\n"
        "comment this file is a cube\n"
        "element vertex 8\n"
        "property float x\n"
        "property float y\n"
        "property float z\n"
        "element face 6\n"
        "property list uchar int vertex_index\n"
        "end_header\n"
        "0 0 0\n"
        "0 0 1\n"
        "0 1 1\n"
        "0 1 0\n"
        "1 0 0\n"
        "1 0 1\n"
        "1 1 1\n"
        "1 1 0\n"
        "3 0 1 2 3\n"
        "3 7 6 5 4\n"
        "3 0 4 5 1\n"
        "3 1 5 6 2\n"
        "3 2 6 7 3\n"
        "3 3 7 4 0\n";

    /*    "4 0 1 2 3\n"
        "4 7 6 5 4\n"
        "4 0 4 5 1\n"
        "4 1 5 6 2\n"
        "4 2 6 7 3\n"
        "4 3 7 4 0\n";*/

    for (unsigned i = 0; i < CORE_COUNT_OF(tests); i++)
    {
        Mesh3D mesh;
        PLYLoader loader;
        std::string str(tests[i]);
        std::istringstream stream(str);
        int result = loader.loadPLY(stream, mesh);
        printf("Test case %d result: %d\n", i, result);
    }
}

using std::ifstream;

TEST(FileFormats, DISABLED_testObjLoader)
{
    OBJLoader loader;
    ifstream file("body-v2.obj", ifstream::in);

    Mesh3D mesh;
    loader.loadOBJSimple(file, mesh);
}


TEST(FileFormats, DISABLED_testObjMaterialLoader)
{
    cout << "Test Obj Format Material Loader" << endl;
    OBJLoader loader;
    ifstream file("/home/alexander/work/data/3d/source/Mesh.obj1.mtl", ifstream::in);

    vector<OBJMaterial> materials;
    loader.loadMaterials(file, materials, "/home/alexander/work/data/3d/source");

    cout << materials.size() << endl;
}



TEST(FileFormats, testGcodeLoader)
{
    const char input[] =
            "; Slic3r style comments\n"
            "G01 Z-0.125000 F100.0 (Penetrate)\n"
            "G02 X73.327786 Y20.305024 Z-0.125000 I-38.815360 J0.000000 F400.000000\n"
            "G02 X59.120378 Y6.097616 Z-0.125000 I-33.615088 J19.407680\n"
            "G02 X39.712698 Y0.897344 Z-0.125000 I-19.407680 J33.615088\n"
            "G02 X20.305018 Y6.097616 Z-0.125000 I-0.000000 J38.815360\n"
            "G02 X6.097610 Y20.305024 Z-0.125000 I19.407680 J33.615088\n"
            "G02 X0.897338 Y39.712704 Z-0.125000 I33.615087 J19.407679\n"
            "G02 X6.097611 Y59.120384 Z-0.125000 I38.815360 J-0.000000\n"
            "G02 X20.305019 Y73.327792 Z-0.125000 I33.615088 J-19.407680\n"
            "G02 X39.712699 Y78.528064 Z-0.125000 I19.407680 J-33.615088\n"
            "G02 X59.120379 Y73.327792 Z-0.125000 I0.000000 J-38.815360\n"
            "G02 X73.327787 Y59.120384 Z-0.125000 I-19.407680 J-33.615088\n"
            "G02 X78.528059 Y39.712704 Z-0.125000 I-33.615088 J-19.407680\n"
            "G01 X78.528059 Y39.712704 Z-0.125000\n"
            "G00 Z5.000000\n";

    GcodeLoader loader;
    Mesh3D mesh;    
    std::string str(input);
    {
        std::istringstream stream(str);
        /*int result =*/ loader.loadGcode(stream, mesh);
        mesh.dumpPLY("gcode-test.ply");
    }

    {
        std::istringstream stream(str);
        std::ostringstream ostream;

        GCodeProgram program;

        loader.loadGcode(stream, program);
        loader.saveGcode(ostream, program);
        cout << "Saving:" << endl;
        cout << ostream.str() << endl;
    }

}

TEST(FileFormats, testGcodeLoader1)
{
    const char input[] = "G1 X0  F3000\n";
    GcodeLoader loader;
    Mesh3D mesh;
    std::string str(input);
    std::istringstream stream(str);
    loader.loadGcode(stream, mesh);
}

TEST(FileFormats, testhpglLoader)
{
    const char input[] =
            "IN;\n"
            "PT0;\n"
            "PU;\n"
            "SP3;\n"
            "PA88,3478;\n"
            "PD;\n"
            "PA103,3481;\n"
            "PA116,3490;\n"
            "PA125,3502;\n"
            "PA128,3518;\n"
            "PA125,3533;\n"
            "PA116,3546;\n"
            "PA109,3551;\n";


    HPGLLoader loader;
    HPGLProgram program;
    std::string str(input);
    std::istringstream stream(str);
    loader.loadHPGLcode(stream, program);

    cout << program << std::endl;
}


TEST(FileFormats, testXYZListLoader)
{
    const char input[] =
    "0 1 2\n"
    "3 4 5\n"
    "6 7 8\n"
    "9 10 11\n"
    "12 13 14\n";

    Mesh3D mesh;

    XYZListLoader loader;
    std::string str(input);
    std::istringstream stream(str);
    loader.loadXYZ(stream, mesh);

    loader.saveXYZ(cout, mesh);
}

TEST(FileFormats, testXYZListLoader1)
{
    const char input[] =
    "0 1 2 0\n"
    "3 4 5 1\n"
    "6 7 8 2\n"
    "9 10 11 3\n"
    "12 13 14 4\n";

    Mesh3D mesh;
    mesh.switchAttributes();

    XYZListLoader loader;
    std::string str(input);
    std::istringstream stream(str);
    loader.loadXYZ(stream, mesh);

    loader.saveXYZ(cout, mesh);
}

TEST(FileFormats, testLabelList)
{
    const char input[] =
    "-0.751001 -3.26496 0.213015 0.001927 id:4\n"
    "-0.751065 -3.26494 0.213870 0.002132 id:4\n"
    "-0.878894 -3.49883 0.184953 0.002388 id:4\n"
    "-0.690898 -3.65771 0.235221 0.003894 id:4\n";

    LabelList list;
    XYZListLoader loader;
    std::string str(input);
    std::istringstream stream(str);

    loader.loadLabelList(stream, list);

    CORE_ASSERT_TRUE(list.size() == 4, "Reading problem" );
    loader.saveLabelList(cout  , list);
}
