#pragma once

/*

    Defines interfaces for save classes. All functions are 
    to be kept pure virtual.

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

    
    /*
         Handles a generic save event that can be triggered
         at run-time.
    */
    virtual void Save() = 0;

    
    /*
         Handles a generic load event that can be triggered at
         runtime.

         @param WorldContext: pointer to the current 
         world context.
    */
    virtual void Load(UWorld* WorldContext) = 0;


    /*
        Handles a generic load event for load events that require a 
        dependency item; note this function is best used when binded to a 
        dispatch event, as opposed to just raw calls.

        @param WorldContext: pointer to the current world
        context.

        @param DependencyObject: pointer to the object that 
        the load event is dependent on.
    */
    virtual void Load(UWorld* WorldContext, UObject* DependencyObject) = 0;
};