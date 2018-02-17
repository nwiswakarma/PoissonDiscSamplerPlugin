// 

#pragma once

#include "CoreMinimal.h"
#include "CoreUObject.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "DCELPoissonDiscSampler.h"
#include "PDSFunctionLibrary.generated.h"

UCLASS()
class UPDSFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

    UFUNCTION(BlueprintCallable)
    static TArray<FVector2D> GeneratePoints(int32 RandomSeed = 1337, float PointRadius = .1f, FVector2D SampleDimension = FVector2D(1.f, 1.f), int32 KValue = 25)
    {
        FDCELPoissonDiscSampler::GeneratorConfig pdsConf(PointRadius, SampleDimension, KValue);

        TArray<FVector2D> points;
        FDCELPoissonDiscSampler::GeneratePoints(points, pdsConf, RandomSeed);

        return MoveTemp(points);
    }
};

