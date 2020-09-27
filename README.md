# Unreal Engine 4.2x C++ Boilerplate

One of the most frustrating things about Unreal Engine is starting up an empty project where you need to st up and connect all the scafolding. Especially if you are trying to work it out in C++. There are web sites out there that help to quickly set up, but I created this repo so that i can keep it handy each time.  
  
All of the bolerplate code is Blueprint free. It is done entirely in C++.  
  
This repo is a boilerplate of essential components already conencted with samples of how to do some pretty commonly asked stuff on the net.
  
If it helped you, thumbs up! I am happy it did.  

 Below is some info on Unreal Engine lingo and Framework descriptions.  

## The Unreal Engine 4 Gameplay Framework

The Gameplay Framework of Unreal Engine 4 provides a powerful set of classes to build your game. Your game can be a shooter, farm simulator, a deep RPG, it does not matter, the framework is very flexible and does some heavy lifting and sets some standards. It has a pretty deep integration with the engine so my immediate advice is to stick to these classes instead of trying to ‘roll your own’ game framework as you might with engine’s like Unity3D. Understanding this framework is critical in being successful and efficient is building your projects.

## Contents

[Who is this for?](#who-is-this-for)  
[Gameplay Framework Classes](#gameplay-framework-classes)  
[Actor](#actor)  
[ActorComponent](#actorcomponent)  
[PlayerController](#playercontroller)  
[AIController](#AIController)  
[Pawn](#pawn)  
[GameModeBase](#GameModeBase)  
[HUD](#hud)  
[World](#world)  
[GameInstance](#GameInstance)  
[PlayerState](#PlayerState)  
[GameStateBase](#GameStateBase)  
[UObject](#UObject)  
[GameplayStatics](#GameplayStatics)  
  
## Who is this for

Anyone who is interesting in building games with UE4, specifically those in C++, and would like to learn more about Unreal’s Gameplay Framework. This post walks through the core classes you will use from the Gameplay Framework and explains their use, how they get instantiated by the engine and how to access each of those classes from other parts of your game code. Most of the information presented applies to Blueprint as well.  
  
If you are looking to get started with Unreal Engine 4, check out my earlier guide. I have another guide specific to Virtual Reality for beginners for those looking to educate themselves on the specifics of VR in Unreal Engine 4.  
  
## Gameplay Framework Classes

When building games in Unreal Engine 4 you will find a lot of boilerplate is already done for you. There are a handful of classes you will be using a lot in making games in C++ or Blueprint for that matter. I will walk through each of the classes, some neat features they hold and how to reference them from other places in your code. Most information in this guide applies to Blueprint all the same, although I use C++ snippets and some functions may not be exposed to Blueprint and therefor only relevant to C++ users.  

## Actor

Perhaps the most used class in your game. Actor is the base for any object in your level including players, AI enemies, doors, walls, and gameplay objects. Actors are built-up using ActorComponents (see next section) like StaticMeshComponent, CharacterMovementComponent, ParticleComponent and tons more. Even classes like GameMode (see below) are Actors (even though a GameMode does not have a ‘real’ position in the world). Let’s talk about a few things you need to know about Actors.
  
Actor is the class you can network replicate (for multiplayer) and is easily done by calling SetReplicates(true) in your constructor. There is a lot that comes into play when dealing with effective networking in Actors, so I will not be able cover that in this blog.  
  
Actors support the concept receiving of damage out of the box. Damage can be applied directly to the Actor using MyActor->TakeDamage(…) or via UGameplayStatics::ApplyDamage(…) note there are variations available for PointDamage (eg. hitscan weapons) and RadialDamage for things like explosions. There is a great intro to [Damage in UE4!](https://www.unrealengine.com/en-US/blog/damage-in-ue4) on the official Unreal Engine site.  
  
You can easily spawn a new Actor instance in code by using `GetWorld()->SpawnActor<T>(…);` where T is the class to return, eg. AActor of one of your own types like AGadgetActor, AGameplayProp, etc.  
  
## Here is a snippet where an Actor is spawned at runtime
  
```c++
FTransform SpawnTM;
FActorSpawnParameters SpawnParams;
SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
SpawnParams.Owner = GetOwner();
/* Attempt to assign an instigator (used for damage application) */
SpawnParams.Instigator = Cast<APawn>(GetOwner());

ASEquippableActor* NewItem = GetWorld()->SpawnActor<ASEquippableActor>(NewItemClass, SpawnTM, SpawnParams);
```

There are many ways to get access to Actors, usually you would have a pointer/reference to the specific Actor you are interested in. In the sample above, we can keep the pointer to the equippable actor via the NewItem variable and start manipulating the Actor instance through that.

One especially useful function you may use when prototyping or getting to grips with the engine is UGameplayStatics::GetAllActorsOfClass(…) this lets you grab an array of all actors of the class you pass in (including the derived classes, if you were to pass in Actor as the class you basically get ALL things in the level… probably not what you are looking for) The function is often feared and avoided as it’s not a very efficient way of interacting with your environment, but sometimes it’s the only tool you got.

Actors don’t actually own a translation,rotation or scale. This is all set and retrieved via the RootComponent, eg. the top-level component in the hierarchy of SceneComponents (see below for more on SceneComponents) the very commonly used functions like MyActor->GetActorLocation() actually go into the RootComponent and returns its world location.

Here are some additional useful functions you will use within the context of an Actor:

* **BeginPlay** // The ‘first’ function to be called once the Actor has spawned and is completely initialized. This is a good place to setup basic logic, a timer, or change some properties now that its fully initialized and can query its surroundings.  
* **Tick** // Called every frame, for most Actors this will eventually be turned off for performance reason, but its enabled by default. Great for setting up dynamic logic quickly and checking stuff in a per-frame basis. Eventually you will find yourself moving more code to event-based logic or running timers to performance logic on lower frequencies.  
* **EndPlay** // Called when the Actor is being removed from the world including a ‘EEndPlayReason’ which specifies why it was called.  
* **GetComponentByClass** // Find a single component instance of specific class, very useful when you don’t have the exact type of the Actor but know it must contain a certain component type. There is also GetComponentsByClass to return all instances of the class, not just the first one found.  
* **GetActorLocation** // And all its variations, `*Rotation`, `*Scale` including SetActorLocation etc.  
* **NotifyActorBeginOverlap** // Neat for checking overlaps caused by any of its components. Quickly set up gameplay triggers this way.  
* **GetOverlappingActors** // Easily find out what other Actors are currently overlapping ours, also a component variation is available: GetOverlappingComponents  
  
Actor contains a LOT of functionality and variables, its the cornerstone of the gameplay framework in Unreal Engine so its not surprising. A good way to further explore this class is by opening up the header file of Actor.h in Visual Studio and see what functionality is available.  There is more to cover here so let’s move onto the next class on our list.

## Recommended Reading

[Actor Lifecycle!](https://docs.unrealengine.com/en-US/Programming/UnrealArchitecture/Actors/ActorLifecycle/index.html)  
  
## ActorComponent

Components live inside of Actors, common components include StaticMeshComponent, CharacterMovementComponent, CameraComponent, and SphereComponent. These components each handle one particular task like movement, physics interaction (eg. a collision volume to purely check for overlapping Actors) or to visually display something in the world like a player mesh.  
  
A sub-class of this component is **SceneComponent**, and is the base class for anything with a Transform (Position, Rotation, Scale) and supports attachment. For example, you can attach your CameraComponent to a SpringArmComponent to setup a third-person camera, both have a transform and attachment is required to properly manage relative positions.  
  
Components are most commonly created in the constructor of the Actor, you can also create and destroy components at runtime. First, let’s look at one of my Actor’s constructors.  
  
```c++
ASEquippableActor::ASEquippableActor()
{
 PrimaryActorTick.bCanEverTick = true;

 MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
 MeshComp->SetCollisionObjectType(ECC_WorldDynamic); // Just setting a property on our component
 // Set our root component for other SceneComponents to attach to
 RootComponent = MeshComp;

// not attached to anything (not a SceneComponent with a transform)
ItemComp = CreateDefaultSubobject<UItemComponent>(TEXT("ItemComp"));

}
```  

The USkeletalMeshComponent is created using the *CreateDefaultSubobject\<T>* (a function of Actor) and requires a name to be specified (you will see this name in the Blueprint’s component list) you will use this function a LOT if you create your game code in C++, but ONLY within the context of the constructor.

You may also notice we setup the MeshComp to be the new RootComponent. Now any SceneComponent must be attached to this mesh, which is easily done using the following line:  
  
```c++
 WidgetComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("InteractWidgetComp"));
 WidgetComp->SetupAttachment(MeshComp);
```  

The SetupAttachment will handle the initial attaching for us and it expected to be called for ALL scene components except the RootComponent itself to be done in the constructor. You may wonder why my ItemComponent does not call this SetupAttachment function. This is simply because that component is an ActorComponent but NOT a SceneComponent and has no Transform (location, rotation, scale) and does therefore not need to be added to the hierarchy. The component will still be registered with the Actor regardless, as that is separate from the hierarchy meaning functions like MyActor->GetComponentByClass will return any ActorComponents and SceneComponents.  
  
Together with Actor these Components are critical in building your game in both C++ and Blueprint. They truly are the building blocks for your game. You can easily create your own custom components and have them handle something specific in your game such as a HealthComponent that holds hitpoints and reacts to the damage the owning Actor receives.  
  
During gameplay you can spawn your own components using the code below. This is different from the CreateDefaultSubobject which is for constructors only.  
  
```c++
UActorComponent* SpawnedComponent = NewObject<UActorComponent>(this, UStaticMeshComponent::StaticClass(), TEXT("DynamicSpawnedMeshCompoent"));
 if (SpawnedComponent)
 {
    SpawnedComponent->RegisterComponent();
 }
```  
  
Some built-in useful functionality for ActorComponents include:
  
* **TickComponent()** // Just like the Actor’s Tick() runs every frame to do high frequency logic.
* bool bIsActive and the functions associated like Activate, Deactivate, .. to enable/disable the component entirely (including the TickComponent) without destroying the component or removing it from the Actor.  
  
To enable replication on the ActorComponent you must call SetIsReplicated(true) which is slightly different in name from the Actor’s function. This is only necessary if you are trying to replicate a specific piece of logic for this component like a variable on function calls, and so not all components on a replicated Actor need to be replicated.  
  
## PlayerController

The primary class for a player, receiving the input of the user. A PlayerController itself is not visually shown in the environment instead, it will ‘Possess’ a Pawn instance which defines the visual and physical representation of that player in the world. During gameplay a player may possess a number of different pawns (eg. a vehicle, or a fresh copy of the Pawn when respawning) while the PlayerController instance remains the same throughout the duration of the level. This is important as there may also be moments where the PlayerController does not possess any pawn at all. This means things like the opening of menus should be added to the PlayerController and not the Pawn class.  
  
In multiplayer games the PlayerController only exists on the owning client and the server. This means in a game of 4 players, the server has 4 player controllers, and each client only has 1. This is very important in understanding where to put certain variables as when all players require a player’s variable to be replicated it should never exist in the PlayerController but in the Pawn or even PlayerState (covered later) instead.  
  
### Accessing PlayerControllers  

* GetWorld()->GetPlayerControllerIterator() // GetWorld is available in any Actor instance
* PlayerState->GetOwner() // owner of playerstate is of type PlayerController, you will need to cast it to PlayerController yourself.
* Pawn->GetController() // Only set when the pawn is currently ‘possessed’ (ie. controlled) by a PlayerController.  
  
This class contains a *PlayerCameraManager* which handles view targets and camera transforms including camera shakes. Another important class the PlayerController handles is HUD (covered below) which is used for Canvas rendering (not used as much now that UMG is available) and can be great for managing some data you want to pass on to your UMG interface.  
  
Whenever a new players joins the GameMode, a new PlayerController is created for this player via Login() in the GameModeBase class.  
  
## AIController

Similar in concept to the PlayerController class, but purely for AI agents instead of players. Will possess a Pawn (see below) much like the PlayerController and is the ‘brain’ of the agent. Where the Pawn is the visual representation of the agent, the AIController is the decision maker.  
  
Behavior Trees run via this controller and so should any handling of perception data (what the AI can see and hear) and push the decisions into the Pawn to act.  
  
### Accessing AIController

AIControllers can be accessed in the same way as PlayerControllers from inside a Pawn (via “Get Controller”) and in Blueprint there is a “GetAIController” function available anywhere, the input is expected to be the Pawn that is controlled by AI.  
  
### Spawning

AIControllers can be spawned automatically if desired by setting the variable “Auto Possess AI” in the Pawn class. Make sure you set “AI Controller Class” variable in the Pawn to your desired class when using this.  
  
## Pawn

The physical and visual representation of what the player (or AI) is controlling. This can be a vehicle, a warrior, a turret, or anything that presents your game’s character. A common sub-class for Pawn is Character which implements a SkeletalMesh and more importantly a CharacterMovementComponent with MANY options for fine-tuning how your player can traverse the environment using common shooter type movement.  
  
In multiplayer games each Pawn instance is replicated to other clients. This means in 4 player game, both the server and each of the clients all have 4 pawn instances. It is not uncommon to “kill” a Pawn instance when the player dies, and to spawn a fresh instance on player respawn. Keep this in mind for storing your data you want to keep beyond the single life of a player (or refrain from using this pattern altogether and keeping the pawn instance alive instead)  
  
### Accessing Pawns

* **PlayerController->GetPawn()** // Only when the PC currently has a pawn possessed
* **GetWorld()->GetPawnIterator()** // GetWorld is available in any Actor instance, returns ALL pawns including AI you may have.  
  
### Spawned by

GameModeBase spawns the Pawn via SpawnDefaultPawnAtTransform, the GameModeBase class also specifies which Pawn class to spawn.  
  
## GameModeBase

The primary class that specifies which classes to use (PlayerController, Pawn, HUD, GameState, PlayerState) and commonly used to specify game rules for modes such as ‘Capture the Flag’ where it could handle the flags, or to handle ‘wave spawns’ in a wave based shooter. Handles other key features like spawning the player as well.  
  
GameMode is a sub-class of GameModeBase and contains a few more features originally used by Unreal Tournament such as MatchState and other shooter type features.  

In multiplayer the GameMode class only exists on the server! This means no client ever has an instance. For singleplayer games this has no effect. To replicate functions and store data you need for your GameMode you should consider using GameState which does exist on all clients and is made for specifically this purpose.  
  
## Accessing GameMode
  
* `GetWorld()->GetAuthGameMode()` // GetWorld is available from any Actor instance.
* `GetGameState()` // return gamestate for replicating functions and/or variables
* `InitGame(…)` // initialize some of the game rules including those provided on the URL (eg. “MyMap?MaxPlayersPerTeam=2”) which can be passed in with loading levels in the game.  
  
## HUD

The user interface class. Has a lot of ‘Canvas’ code which is the user interface drawing code that came before UMG – which took over most of today’s interface drawing.  
  
Class only exists on the client. Not suitable for replication. Is owned by the PlayerController.  

### Accessing HUD

PlayerController->GetHUD() // Available in your local PlayerController  
  
### Spawned by

Spawned inside of PlayerController that owns the HUD via SpawnDefaultHUD (spawns generic AHUD), then overriden by the GameModeBase via InitializeHUDForPlayer with the HUD class specified in GameModeBase.  
  
### Remarks

I use this class less and less compared to pre-UE4 days, UMG can be handled via the PlayerController. Just keep in mind that for multiplayer games you do want to make sure the player controller IsLocalController() before spawning any widgets.  
  
## World

UWorld is the top level object representing a map in which Actors and Components will exist and be rendered. Contains the persistent level and many other objects like gamestate, gamemode and lists like Pawns and Controllers currently on the map.  
  
Line tracing and all its variations is done via the world with functions like World->LineTraceSingleByChannel and many other variations like it.  
  
### Accessing World

Easy to access by calling GetWorld() inside your Actors.  
  
When trying to get the world instance in static functions you need to pass in a ‘WorldContextObject’ which is basically just an input parameter that we can use to call ->GetWorld() on. Here is an example from one of my header files:  
  
```c++
static APlayerController* GetFirstLocalPlayerController(UObject* WorldContextObject);
```  
  
## GameInstance

GameInstance has one instance that persists throughout the lifetime of the game. Traveling between maps and menus will maintain the same instance of this class. This class can be used to provide event hooks of handling network errors, loading of user data like game settings and generally features that are not relevant to only a specific level of your game.  
  
### Accessing GameInstance

* `GetWorld()->GetGameInstance<T>();` // where T is the class type eg. `GetGameInstance<UGameInstance>()` or your own derived type.
* `Actor->GetGameInstance()`  
  
### Remarks

Generally not used a whole lot early in your game project. does not do anything critical unless you’re diving deeper into the development (things like game sessions, demo playback or persisting some data between levels)  
  
## PlayerState

Container for variables to replicate between client/server for a specific player. For multiplayer games, it’s not supposed to run logic, and is just data container since PlayerController is not available on all clients and Pawn are often destroyed when a player dies so unsuitable for data that needs to be stored even after death.  
  
### Accessing PlayerState

Pawn has it as variable Pawn->PlayerState, also available in Controller->PlayerState. The PlayerState in Pawn is only assigned for as long as a Controller has possessed that Pawn, otherwise it’s a nullptr.  
  
A list of all current PlayerState instances (eg. all players currently in the match) is available via GameState->PlayerArray.  
  
### Spawned by

Class to spawn is assigned in GameMode (PlayerStateClass) and spawned by AController::InitPlayerState()  
  
### Remarks

Only useful when working on multiplayer games.  
  
## GameStateBase

Similar to PlayerState, but for clients about GameMode information. Since GameMode instance does not exist on clients, but only on server this is a useful container to replicate information like match time elapsed or team scores etc.  
  
Comes in two variations, GameState and GameStateBase where GameState handles the extra variables required by GameMode (as opposed to GameModeBase)  
  
### Accessing GameStateBase

* `World->GetGameState<T>()` // where T is the class to cast to eg. GetGameState<AGameState>()
* `MyGameMode->GetGameState()` // stored and available in your gamemode instance (only relevant on server which owns the only instance of GameMode), clients should use the above call instead.  
  
### Remarks

Use GameStateBase over GameState unless your gamemode derives from GameMode instead of GameModeBase.  
  
## UObject

The base object for almost anything in the engine, Actors derive from UObject and so do the other core classes like GameInstance. This will never be used to render something, but can be very useful to store some data and functions when structs may not be suitable for your specific requirements.  
  
### Spawning UObjects

UObjects are not spawned like Actors, but created using `NewObject<T>()` for example:  
  
```c++
TSubclassOf<UObject> ClassToCreate;
UObject* NewDesc = NewObject<UObject>(this, ClassToCreate);
```  
  
### Remarks

It’s unlikely you will derive classes directly from UObject unless you are comfortable with the engine and are diving into more custom systems. For example I am using it to store lists of information from a database.  
  
Can be used with networking, but requires some extra setup in the object class, and the objects need to be stored inside an Actor.  
  
## GameplayStatics

Static class to handle many common game related functionality like playing sounds and spawning particle effects, spawning Actors, applying damage to Actors, getting playerpawn, playercontroller, etc. Bottomline, this class is very useful for all sorts of gameplay access. All functions are static which means you don’t need to own a pointer to any instance of this class and can call functions directly from anywhere as seen below.  
  
### Accessing GameplayStatics

Since GameplayStatics is a UBlueprintFunctionLibrary you can access it from anywhere in your code (or Blueprint for that matter)  
  
```c++
UGameplayStatics::WhateverFunction(); // static functions are easily accessed anywhere, just include #include "Kismet/GameplayStatics.h"
```

## References

Some further recommended reading for the gameplay framework and programming within Unreal Engine 4.  
  
* [Gameplay Framework Documentation!](https://docs.unrealengine.com/en-US/Programming/UnrealArchitecture/Reference/Classes/index.html)
* [Gameplay Programming Documentation!](https://docs.unrealengine.com/en-US/Programming/UnrealArchitecture/index.html)
* [Actor Lifecycle Documentation!](https://docs.unrealengine.com/en-US/Programming/UnrealArchitecture/Actors/ActorLifecycle/index.html)
