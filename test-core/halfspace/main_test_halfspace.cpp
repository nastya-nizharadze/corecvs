/**
 * \file main_test_halfspace.cpp
 * \brief This is the main file for the test halfspace 
 *
 * \date май 24, 2018
 * \author alexander
 *
 * \ingroup autotest  
 */

#include <iostream>
#include <core/geometry/halfspaceIntersector.h>
#include <core/geometry/mesh3d.h>
#include "gtest/gtest.h"

#include "core/utils/global.h"


using namespace corecvs;
using namespace std;

TEST(Halfspace, Space2d)
{
    double radius = 10.0;
    Polygon P = Polygon::RegularPolygon(50, Vector2dd::Zero(), radius, degToRad(5));
    ConvexPolygon CP = P.toConvexPolygon();
    //Polygon R = HalfspaceIntersector::FromConvexPolygon(CP);

    ProjectivePolygon PR  = HalfspaceIntersector::FromConvexPolygonP(CP);

    for(size_t i = 0; i < PR.size(); i++ )
    {
        Vector3dd proj = PR.at(i);
        Vector2dd reg = proj.normalisedProjective().xy();
        double toZero = reg.l2Metric();
        double dist = fabs(reg.l2Metric() - radius);

        CORE_ASSERT_TRUE_P(dist < 0.0001, ("Wrong poligon dist [%lf %lf] %lf %lf", reg.x(), reg.y(), toZero, dist ));
    }

    CP.faces.push_back(Line2d(Segment2d(Vector2dd(radius / 2, -100 ), Vector2dd(radius / 2, 100))));
    ProjectivePolygon PR1 = HalfspaceIntersector::FromConvexPolygonP(CP);
}

TEST(Halfspace, Space3d)
{
    Mesh3D mesh;

    mesh.addIcoSphere(Vector3dd::Zero(), 10, 4);
    ConvexPolyhedron CP;
    for (int faceId = 0; faceId < mesh.faces.size(); faceId++)
    {
        CP.faces.push_back(mesh.getFaceAsTrinagle(faceId).getPlane());
    }
    ConvexQuickHull::HullFaces  R = HalfspaceIntersector::FromConvexPolyhedron(CP);
}
