// 

#pragma once

#include "UnrealMemory.h"
#include "poissondiscsampler.h"

typedef class FDCELPoissonDiscSampler FDCELPDS;

class FDCELPoissonDiscSampler
{
    struct PDSRandomGenerator : PoissonDiscSampler::IPRNG
    {
        FRandomStream& RandomStream;

        PDSRandomGenerator(FRandomStream& Rand)
            : RandomStream(Rand)
        {
        }

        FORCEINLINE float RandomFloat()
        {
            return RandomStream.GetFraction();
        }

        FORCEINLINE int RandomInt(int Max)
        {
            return RandomStream.GetFraction()*Max;
        }

        FORCEINLINE virtual dcel::FReal randomFraction(dcel::FReal min, dcel::FReal max)
        {
            return RandomStream.FRandRange(min, max);
        }

        FORCEINLINE virtual int randomRange(int min, int max)
        {
            return RandomStream.RandRange(min, max-1);
        }
    };

public:

    struct GeneratorConfig
    {
        float PointRadius = 0.1f;
        float AspectRatio = 1.0f;
        FVector2D Size = FVector2D(1.f, 1.f);
        int32 KValue = 25;

        GeneratorConfig() = default;

        GeneratorConfig(float radius, FVector2D size = FVector2D(1.f, 1.f), int32 kv = 25)
        {
            Set(radius, size, kv);
        }

        FORCEINLINE void Set(float radius, FVector2D size = FVector2D(1.f, 1.f), int32 kv = 25)
        {
            KValue = kv;

            if (size.X > .0001f && size.Y > .0001f)
            {
                Size = size;
                AspectRatio = size.X / size.Y;
                PointRadius = radius * (size.X>size.Y ? 1.f : AspectRatio) * size.Y;
            }
            else
            {
                Size = FVector2D(1.f, 1.f);
                AspectRatio = 1.f;
                PointRadius = radius;
            }
        }
    };

    static void GeneratePoints(TArray<FVector2D>& OutPoints, GeneratorConfig config, FRandomStream& Rand)
    {
        const float aspectRatio = config.AspectRatio;
        const float pointRadius = config.PointRadius;
        const float kValue = config.KValue;
        const FVector2D& size( config.Size );

        dcel::Extents2d extents(0.f, 0.f, size.X, size.Y);
        PDSRandomGenerator prng( Rand );
        PoissonDiscSampler::Generator PDS;

        std::vector<dcel::Point> points;
        points = PDS.generateSamples(extents, pointRadius, kValue, prng);

        if (points.empty())
            return;

        // Memcpy if point/vector data size are equals
        if (sizeof(dcel::Point) == sizeof(FVector2D))
        {
            OutPoints.SetNumUninitialized(points.size());
            FMemory::Memcpy(OutPoints.GetData(), points.data(), points.size()*sizeof(dcel::Point));
        }
        // Otherwise, standard array assign
        else
        {
            OutPoints.Reserve(points.size());
            for (const dcel::Point& p : points)
                OutPoints.Emplace(p.x, p.y);
        }
    }

    static void GeneratePoints(TArray<FVector2D>& OutPoints, GeneratorConfig config, int32 RandSeed)
    {
        FRandomStream rand( RandSeed );
        GeneratePoints(OutPoints, config, rand);
    }
};

