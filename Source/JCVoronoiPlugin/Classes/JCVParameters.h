////////////////////////////////////////////////////////////////////////////////
//
// MIT License
// 
// Copyright (c) 2018-2019 Nuraga Wiswakarma
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//
////////////////////////////////////////////////////////////////////////////////
// 

#pragma once

#include "CoreUObject.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "JCVParameters.generated.h"

class UJCVDiagramObject;
struct FJCVCell;

// Feature & Trait Parameters

USTRUCT(BlueprintType)
struct JCVORONOIPLUGIN_API FJCVFeatureId
{
	GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    uint8 Type;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Index;

    FJCVFeatureId() = default;

    FJCVFeatureId(uint8 InType)
        : Type(InType)
        , Index(-1)
    {
    }

    FJCVFeatureId(uint8 InType, int32 InIndex)
        : Type(InType)
        , Index(InIndex)
    {
    }
};

USTRUCT(BlueprintType, Blueprintable)
struct JCVORONOIPLUGIN_API FJCVRadialFill
{
	GENERATED_BODY()

	UPROPERTY(Category = "JCV|Radial Fill", BlueprintReadWrite, EditAnywhere)
    float Value = .5f;

	UPROPERTY(Category = "JCV|Radial Fill", BlueprintReadWrite, EditAnywhere)
    float Radius = .85f;

	UPROPERTY(Category = "JCV|Radial Fill", BlueprintReadWrite, EditAnywhere)
    float Sharpness = 0.f;

	UPROPERTY(Category = "JCV|Radial Fill", BlueprintReadWrite, EditAnywhere)
    UCurveFloat* ValueCurve = nullptr;

	UPROPERTY(Category = "JCV|Radial Fill", BlueprintReadWrite, EditAnywhere)
    bool bRadialDegrade = true;

	UPROPERTY(Category = "JCV|Radial Fill", BlueprintReadWrite, EditAnywhere)
    bool bFilterBorder = true;
};

USTRUCT(BlueprintType)
struct JCVORONOIPLUGIN_API FJCVCellTraits
{
	GENERATED_USTRUCT_BODY()

    typedef TFunction<bool(const FJCVCell&)> FFilterCallback;

    FFilterCallback FilterCallback;

    FJCVCellTraits() = default;
    FJCVCellTraits(const FFilterCallback& InFilterCallback);

    FORCEINLINE bool HasValidCallback() const
    {
        return !!FilterCallback;
    }

    FORCEINLINE bool HasMatchingTraits(const FJCVCell* Cell) const
    {
        return Cell ? HasMatchingTraits(*Cell) : false;
    }

    FORCEINLINE bool HasMatchingTraits(const FJCVCell& Cell) const
    {
        return HasValidCallback() ? FilterCallback(Cell) : true;
    }

    FORCEINLINE const FFilterCallback* GetCallbackRef() const
    {
        return HasValidCallback() ? &FilterCallback : nullptr;
    }
};

//USTRUCT(BlueprintType, Blueprintable)
//struct JCVORONOIPLUGIN_API FJCVCellTraits_Deprecated
//{
//	GENERATED_BODY()
//
//	UPROPERTY(Category = "JCV|Cell Traits", BlueprintReadWrite, EditAnywhere)
//    uint8 TestType = 255;
//
//	UPROPERTY(Category = "JCV|Cell Traits", BlueprintReadWrite, EditAnywhere)
//    uint8 FeatureType;
//
//    FJCVCellTraits_Deprecated() = default;
//
//    FJCVCellTraits_Deprecated(uint8 f)
//        : FeatureType(f)
//    {
//    }
//
//    FJCVCellTraits_Deprecated(uint8 t, uint8 f)
//        : TestType(t)
//        , FeatureType(f)
//    {
//    }
//
//    virtual bool HasValidFeature(const FJCVCell& c) const;
//    virtual bool HasUndefinedType(const FJCVCell& c) const;
//};

//USTRUCT(BlueprintType, Blueprintable)
//struct JCVORONOIPLUGIN_API FJCVValueTraits_Deprecated : public FJCVCellTraits_Deprecated
//{
//	GENERATED_BODY()
//
//	UPROPERTY(Category = "JCV|Cell Traits", BlueprintReadWrite, EditAnywhere)
//    float ValueLo;
//
//	UPROPERTY(Category = "JCV|Cell Traits", BlueprintReadWrite, EditAnywhere)
//    float ValueHi;
//
//    FJCVValueTraits_Deprecated() = default;
//
//    FJCVValueTraits_Deprecated(float l, float v, uint8 f)
//        : FJCVCellTraits_Deprecated(f)
//        , ValueLo(l)
//        , ValueHi(v)
//    {
//    }
//
//    virtual bool HasValidFeature(const FJCVCell& c) const override;
//};

USTRUCT(BlueprintType, Blueprintable)
struct JCVORONOIPLUGIN_API FJCVOrogenParams
{
	GENERATED_BODY()

	UPROPERTY(Category = "JCV|Orogen Settings", BlueprintReadWrite, EditAnywhere)
    float OriginThreshold = .1f;

	UPROPERTY(Category = "JCV|Orogen Settings", BlueprintReadWrite, EditAnywhere)
    float AreaThreshold = .01f;

	UPROPERTY(Category = "JCV|Orogen Settings", BlueprintReadWrite, EditAnywhere)
    uint8 FeatureType = 1;

	UPROPERTY(Category = "JCV|Orogen Settings", BlueprintReadWrite, EditAnywhere)
    bool bDivergentAsConvergent = false;
};

// Cell Types

USTRUCT(BlueprintType)
struct JCVORONOIPLUGIN_API FJCVCellTypeGroupRef
{
	GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<uint8> Data;
};

USTRUCT(BlueprintType)
struct JCVORONOIPLUGIN_API FJCVCellRef
{
	GENERATED_BODY()

    const FJCVCell* Data;

    FJCVCellRef() : Data(nullptr)
    {
    }

    explicit FJCVCellRef(const FJCVCell* Cell) : Data(Cell)
    {
    }

    explicit FJCVCellRef(const FJCVCell& Cell) : Data(&Cell)
    {
    }

    FORCEINLINE void Set(const FJCVCell* Cell)
    {
        Data = Cell;
    }

    bool HasValidCell() const
    {
        return Data != nullptr;
    }
};

USTRUCT(BlueprintType)
struct JCVORONOIPLUGIN_API FJCVCellDetailsRef
{
	GENERATED_USTRUCT_BODY()

    const FJCVCell* Cell;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bIsValid;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Index;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FVector2D Point;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Value;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bIsBorder;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    uint8 FeatureType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 FeatureIndex;

    FJCVCellDetailsRef();

    explicit FJCVCellDetailsRef(const FJCVCellRef& InCellRef)
    {
        Set(InCellRef);
    }

    explicit FJCVCellDetailsRef(const FJCVCell* InCell)
    {
        Set(InCell);
    }

    void Set(const FJCVCell* InCell);

    FORCEINLINE void Set(const FJCVCellRef& InCellRef)
    {
        Set(InCellRef.Data);
    }
};

USTRUCT(BlueprintType)
struct JCVORONOIPLUGIN_API FJCVCellRefGroup
{
	GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite)
    TArray<FJCVCellRef> Data;
};

USTRUCT(BlueprintType)
struct JCVORONOIPLUGIN_API FJCVCellJunctionRef
{
	GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite)
    FVector2D Point;

    UPROPERTY(BlueprintReadWrite)
    TArray<FJCVCellRef> Cells;

    FJCVCellJunctionRef() = default;

    FJCVCellJunctionRef(
        const FVector2D& InPoint,
        const TArray<FJCVCell*>& InCells
        )
        : Point(InPoint)
        , Cells(InCells)
    {
    }
};

USTRUCT(BlueprintType)
struct JCVORONOIPLUGIN_API FJCVPointGroup
{
	GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FVector2D> Points;
};

USTRUCT(BlueprintType)
struct JCVORONOIPLUGIN_API FJCVDualGeometry
{
	GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FVector> Points;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<int32> PolyIndices;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<int32> CellIndices;

    FORCEINLINE bool HasGeometry() const
    {
        return Points.Num() >= 3 && PolyIndices.Num() >= 3;
    }
};

USTRUCT(BlueprintType)
struct JCVORONOIPLUGIN_API FJCVPolyGeometry
{
	GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FVector> Points;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<int32> PolyIndices;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<int32> CellIndices;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<int32> CellPolyCounts;

    FORCEINLINE bool HasGeometry() const
    {
        return Points.Num() >= 3 && PolyIndices.Num() >= 3;
    }
};

UCLASS()
class UJCVTraitsLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

    UFUNCTION(BlueprintCallable, BlueprintPure, Category="JCV", meta=(DisplayName="Create Feature Traits", AutoCreateRefTerm="SubTraits,FeatureId"))
    static void K2_CreateFeatureTraits(
        FJCVCellTraits& Traits,
        const FJCVCellTraits& SubTraits,
        const FJCVFeatureId& FeatureId,
        bool bInvertResult = false
        );

    UFUNCTION(BlueprintCallable, BlueprintPure, Category="JCV", meta=(DisplayName="Create Value Traits", AutoCreateRefTerm="SubTraits"))
    static void K2_CreateValueTraits(
        FJCVCellTraits& Traits,
        const FJCVCellTraits& SubTraits,
        float ValueLo = 0.f,
        float ValueHi = 1.f,
        bool bInvertResult = false
        );

    static void CreateFeatureTraits(
        FJCVCellTraits& Traits,
        FJCVFeatureId FeatureId,
        bool bInvertResult = false,
        const FJCVCellTraits::FFilterCallback* SubCallbackRef = nullptr
        );

    static void CreateValueTraits(
        FJCVCellTraits& Traits,
        float ValueLo = 0.f,
        float ValueHi = 1.f,
        bool bInvertResult = false,
        const FJCVCellTraits::FFilterCallback* SubCallbackRef = nullptr
        );
};
