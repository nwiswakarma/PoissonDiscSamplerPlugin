#ifndef POISSONDISCSAMPLER_H
#define POISSONDISCSAMPLER_H

#include <vector>
#include <cmath>
#include <stdlib.h>
#include <time.h>

#include "dcel.h"

namespace PoissonDiscSampler {
    using namespace dcel;

    struct GridIndex {
        int i = 0;
        int j = 0;

        GridIndex() {}
        GridIndex(int ii, int jj) : i(ii), j(jj) {}
    };

    struct SampleGrid {
        Extents2d bounds;
        int width = 0;
        int height = 0;
        FReal dx = 0.0;
        std::vector<int> grid;

        SampleGrid(Extents2d extents, FReal cellsize) {
            bounds = extents;
            dx = cellsize;
            FReal bw = bounds.maxx - bounds.minx;
            FReal bh = bounds.maxy - bounds.miny;
            width = (int)ceil(bw / cellsize);
            height = (int)ceil(bh / cellsize);
            grid = std::vector<int>(width*height, -1);
        }

        int getFlatIndex(int i, int j) {
            return i + j*width;
        }

        int getSample(GridIndex g) {
            return getSample(g.i, g.j);
        }

        int getSample(int i, int j) {
            if (i < 0 || i > width || j < 0 || j > height) {
                throw std::range_error("getSample");
            }
            return grid[getFlatIndex(i, j)];
        }

        void setSample(GridIndex g, int s) {
            setSample(g.i, g.j, s);
        }

        void setSample(int i, int j, int s) {
            if (i < 0 || i > width || j < 0 || j > height) {
                throw std::range_error("setSample");
            }
            grid[getFlatIndex(i, j)] = s;
        }

        GridIndex getCell(Point p) {
            return getCell(p.x, p.y);
        }

        GridIndex getCell(FReal x, FReal y) {
            x -= bounds.minx;
            y -= bounds.miny;
            return GridIndex((int)floor(x / dx), (int)floor(y / dx));
        }
    };

    class IPRNG
    {
    public:
        virtual FReal randomFraction(FReal min, FReal max) = 0;
        virtual int randomRange(int min, int max) = 0;
    };

    class BasePRNG : public IPRNG
    {
    public:

        virtual FReal randomFraction(FReal min, FReal max)
        {
            return min + (FReal)rand() / ((FReal)RAND_MAX / (max - min));
        }

        virtual int randomRange(int min, int max)
        {
            return min + (rand() % (int)(max - min));
        }
    };

    class Generator
    {
    public:

        std::vector<Point> generateSamples(Extents2d bounds, FReal r, int k,
                            IPRNG& prng);

    private:

        IPRNG* _prng;
        FReal _randomFraction(FReal min, FReal max);
        int _randomRange(int min, int max);
        Point _randomPoint(Extents2d &extents);
        Point _randomDiscPoint(Point &center, FReal r);
        bool _findDiscPoint(Point &center, FReal r, int k, 
                            std::vector<Point> &points, SampleGrid &grid,
                            Point *p);
        bool _isSampleValid(Point &p, FReal r, 
                            std::vector<Point> &points, SampleGrid &grid);
    };

}

#endif
