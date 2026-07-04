#pragma once

/*
     Defines item object related interfaces, such as interaction
	 interfaces etc.
*/


//Engine imports.
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ItemInterfaceClass.generated.h"


//Forward declares.
class UItemInstance;




/*
                                  Reflection system classes.
*/

UCLASS()
class DAYSIN_API UItemInterfaceClass : public UObject
{ GENERATED_BODY() };




UINTERFACE()
class UItemInterface : public UInterface
{ GENERATED_BODY() };




/*
                                      Interface classes.
*/

class IItemInterface
{
    GENERATED_BODY()
public:

    virtual void Pickup() = 0;
    virtual void Drop(UItemInstance* Instance) = 0;
};