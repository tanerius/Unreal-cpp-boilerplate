// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ActorBasic.generated.h"

UCLASS()
class CUSTOMTEMPLATE_API AActorBasic : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AActorBasic();


	/** 
	* Some UPROPERTY clarifications:
	*
	*
	* EditDefaultsOnly 
	*
	* Allows you to set Only a default value for a variable in the blueprint window which will be same for all 
	* objects of the type. You cannot change this variable in editor after you've put it in the map.
	* 
	*
	* EditInstanceOnly 
	*
	* Allows you to set separate values of the variable for every object you place in the map , 
	* but you cannot set it in blueprint before you put it in the map, The default value for this 
	* variable can be set in C++ constructor.
	*
	*
	* EditAnywhere 
	*
	* Allows both of above!
	*
	*
	* As seen Editxx will allow you to edit the variables defaults value but will not allow you to read or write 
	* its value in a Blueprint Graph. To be able to read or write a variables value in Blueprint Graph or Logic 
	* you'll need BlueprintReadOnly or BlueprintReadWrite alongside the EditXX like (EditDefaultsOnly,BlueprintReadOnly)
	* 
	* BlueprintReadOnly or BlueprintReadWrite Controls whether the variable show up in graph nodes.
	* 
	* VisibleXXX indicates where your blueprint variable should be visible , Visible as in its value and 
	* representation and not scope visiblity. but you cannot change its defaults value.
	*
	* Whether you can read write a Visible marked variable depends again on BlueprintReadOnly or BlueprintReadWrite
	*
	* Now you'd wonder why some components are marked (BlueprintReadOnly , VisibleDefaultsOnly)
	*
	* In this case you're not allowed to change the variable itself since its Marked BlueprintReadOnly . 
	* The variable here is a pointer! A pointer to your component!
	* So you have privilage to edit the properties in the component itself because they belong to the 
	* component and not the actor , But you cannot change everything your variable is pointing to in the defaults.
	*
	* Text by: Commander Sheppard (https://forums.unrealengine.com/member/28922-commander-shepard)
	*/


	/** 
	* Dummy root component 
	* Make sure actors have a SceneComponent as a root component. Makes working with them way easier
	*
	*/
	UPROPERTY(Category = AttributesCustom, EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USceneComponent* BasicActorRoot;

	/** 
	* Text component 
	* Lets add a basic text component to the actor as well. 
	* We anchor this with BasicActorRoot
	* 
	*/
	UPROPERTY(Category = AttributesCustom, EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UTextRenderComponent* SomeText;


	/**
	* Custom actor component
	* Lets add a basic actor component to this actor 
	*
	*/
	UPROPERTY(Category = AttributesCustom, EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UCustomActorComponent* CustomComponent = nullptr;


	/**
	* Custom actor component
	* Lets add a basic actor component to this actor
	*
	*/
	UFUNCTION(BlueprintNativeEvent)
	void OnTenSecondsPassed(int32 time);
	void OnTenSecondsPassed_Implementation(int32 time);


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
