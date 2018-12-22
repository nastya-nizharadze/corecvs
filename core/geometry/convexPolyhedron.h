#ifndef CONVEXPOLYHEDRON_H
#define CONVEXPOLYHEDRON_H

#include <vector>
#include "core/geometry/line.h"
#include "core/geometry/plane.h"
#include "core/geometry/axisAlignedBox.h"

namespace corecvs {

using std::vector;

template<typename HalfspaceType, typename VectorType>
class ConvexPolyhedronGeneric
{
public:
    vector<HalfspaceType> faces;

    ConvexPolyhedronGeneric() {}

    bool isInside(const VectorType &p)
    {
        for (HalfspaceType &type: faces )
        {
            if (type.pointWeight(p) < 0)
                return false;
        }
        return true;
    }

    unsigned size() const
    {
		return (unsigned)faces.size();
    }

    Vector3dd getPoint(int i) const
    {
        return faces[i].projectZeroTo();
    }

    Vector3dd getNormal(int i) const
    {
        return faces[i].normal();
    }

    friend ostream & operator <<(ostream &out, const ConvexPolyhedronGeneric &polyhedron)
    {
        out << "[";
        for (const HalfspaceType &halfspace : polyhedron.faces) {
            out << halfspace;
        }
        out << "]";
        return out;
    }

    void inset(double dist)
    {
        for (HalfspaceType &type: faces )
        {
            type.last() -= dist * type.normal().l2Metric();
        }
    }

};


class ConvexPolyhedron : public ConvexPolyhedronGeneric<Plane3d, Vector3dd>
{
public:
    ConvexPolyhedron();
    ConvexPolyhedron(const AxisAlignedBox3d &box);

    bool intersectWith(const Ray3d &ray, double &t1, double &t2)
    {
        return ray.clip<ConvexPolyhedron> (*this, t1, t2);
    }
};

class ConvexPolygon : public ConvexPolyhedronGeneric< Line2d, Vector2dd>
{
public:   

    void append(const ConvexPolygon &other);
    void simplify();

    void intersectWith(const ConvexPolygon &other);
    friend ConvexPolygon intersect (const ConvexPolygon &a1, const ConvexPolygon &a2);
//    friend       Polygon intersectP(const ConvexPolygon &a1, const ConvexPolygon &a2);
};


} // namespace corecvs


#endif // CONVEXPOLYHEDRON_H
