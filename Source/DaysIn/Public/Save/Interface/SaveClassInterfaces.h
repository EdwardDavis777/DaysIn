#pragma once

/*

    Defines interfaces for save classes. All functions are 
    pure virtual.

*/


//Engine imports.
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SaveClassInterfaces.generated.h"





/*
                                      Reflection system classes.
*/

UCLASS()
class DAYSIN_API USaveClassInterfaces : public UObject
{ GENERATED_BODY() };

UINTERFACE()
class USaveInterface : public UInterface
{ GENERATED_BODY() };


/*
                                             Interfaces.
*/

class ISaveInterface
{
	GENERATED_BODY()
public:
    virtual void Save() = 0;
    virtual void Load(UWorld* WorldContext) = 0;
};