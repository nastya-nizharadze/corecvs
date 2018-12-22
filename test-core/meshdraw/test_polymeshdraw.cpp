
#include <iostream>
#include "gtest/gtest.h"

#include "core/utils/global.h"
#include "core/geometry/mesh3d.h"
#include "core/fileformats/meshLoader.h"
#include "core/geometry/polylinemesh.h"

using namespace std;
using namespace corecvs;


TEST(meshbuild, testPolylineMesh1)
{
    cout << "Starting test <testpolylinemesh>. This is a manual test" << endl;

    vector<Vector3dd> v;
    PolylineMesh plm;
    PolyLine pl;
    srand(time(NULL));

    for (int i = 0; i < 7; i++)
    {
        for (double j = i*0.5; j < 7 - i*0.5; j+=1)
        {
            if ((i != 3) || (j != 2.5))
                v.push_back(Vector3dd(j, i, 0));
        }
        pl = PolyLine(v);
        plm.addPolyline(pl);
        v.clear();

    }/*
    for(int i = 0; i < 10; i++)
        v.push_back(Vector3dd(i, 0.0, 0.0));
*/
    plm.mesh.dumpPLY("surface.ply");

}


TEST(meshbuild, testPolylineMesh2)
{
    cout << "Starting test <testpolylinemesh>. This is a manual test" << endl;

    vector<Vector3dd> v;
    PolylineMesh plm;
    PolyLine pl;
    srand(time(NULL));

    for(int i = 0; i < 100; i++)
    {
        for(int k = 0; k < 100; k++)
        {
                if(rand() % 10 < 8)
                v.push_back(Vector3dd((k - 50), (i - 50), (i - 50)*(i - 50) / 100.0 - (k - 50)*(k - 50) / 100.0));
        }
        pl = PolyLine(v);
        plm.addPolyline(pl);
        v.clear();
    }

   plm.mesh.dumpPLY("surface.ply");
}
