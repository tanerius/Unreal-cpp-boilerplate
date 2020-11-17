// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "CustomHelpers.generated.h"

/**
 * 
 */
UCLASS()
class CUSTOMTEMPLATE_API UCustomHelpers : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	template <typename ObjClass>
	static FORCEINLINE ObjClass* LoadObjFromPath(const FName& Path)
	{
		if (Path == NAME_None) return nullptr;

		return Cast<ObjClass>(StaticLoadObject(ObjClass::StaticClass(), nullptr, *Path.ToString()));
	}

	UFUNCTION(BlueprintCallable, meta = (ToolTip = "Loads and returns a material given its path", DisplayName = "Load Material From Path", Keywords = "Tanerius"), Category = "Tanerius")
	static FORCEINLINE UMaterial* LoadMaterialFromPath(const FName& Path)
	{
		if (Path == NAME_None) return nullptr;

		return LoadObjFromPath<UMaterial>(Path);
	}

	UFUNCTION(BlueprintCallable, meta = (ToolTip = "Loads and returns a mesh given its path", DisplayName = "Load Mesh From Path", Keywords = "Tanerius"), Category = "Tanerius")
	static FORCEINLINE UStaticMesh* LoadMeshFromPath(const FName& Path)
	{
		if (Path == NAME_None) return nullptr;

		return LoadObjFromPath<UStaticMesh>(Path);
	}
};
