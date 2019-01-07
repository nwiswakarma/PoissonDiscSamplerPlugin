//
// Updated from original source. 2018 Nuraga Wiswakarma

#ifndef DCEL_H
#define DCEL_H

#include <stdio.h>
#include <iostream>
#include <math.h>
#include <vector>
#include <stdexcept>
#include <exception>

#ifndef DCEL_REAL_TYPE
	#define DCEL_REAL_TYPE float
#endif

namespace dcel {

typedef DCEL_REAL_TYPE FReal;

class Point {
public:
	Point() {}
	Point(FReal px, FReal py) : x(px), y(py) {}

	FReal x = 0.0;
	FReal y = 0.0;
};

class Ref {
public:
	Ref() {}
	Ref(int id) : ref(id) {};

	bool operator == (const Ref &r) {
		return ref == r.ref;
	}

	bool operator != (const Ref &r) {
		return ref != r.ref;
	}

	int ref = -1;
};

class Face;
class HalfEdge {
public:
	HalfEdge() {}

	Ref origin;
	Ref twin;
	Ref incidentFace;
	Ref next;
	Ref prev;
	Ref id;
};

class Face {
public:
	Face() {}

	Ref outerComponent;
	std::vector<Ref> innerComponents;
	Ref id;
};

class Vertex {
public: 
	Vertex() {}
	Vertex(FReal x, FReal y) : position(x, y) {}

	Point position;
	Ref incidentEdge;
	Ref id;
};

struct Extents2d {
    FReal minx = 0.0;
    FReal miny = 0.0;
    FReal maxx = 0.0;
    FReal maxy = 0.0;

    Extents2d() {}
    Extents2d(FReal mina, FReal minb, FReal maxa, FReal maxb) : 
                    minx(mina), miny(minb), maxx(maxa), maxy(maxb) {}

    bool containsPoint(dcel::Point p) {
        return containsPoint(p.x, p.y);
    }
    
    bool containsPoint(FReal x, FReal y) {
        return x >= minx && x < maxx && y >= miny && y < maxy;
    }
};

}

#endif
