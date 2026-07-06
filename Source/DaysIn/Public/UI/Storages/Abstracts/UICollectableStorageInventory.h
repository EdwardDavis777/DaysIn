#pragma once


/*

    Defines class defaults for visible collectable storage inventory
 	spatil grids. Such as backpacks, med bags etc.
    
    Also handles interaction hook events, such as droppable storage 
    events etc.

*/


//Other imports.
#include "SharedData/UI/UIRegionTag.h"


//Engine imports.
#include "CoreMinimal.h"
#include "UI/Storages/Abstracts/UIGridInventoryBase.h"
#include "UICollectableStorageInventory.generated.h"




UCLASS()
class DAYSIN_API UUICollectableStorageInventory : public UUIGridInventoryBase
{
	GENERATED_BODY()

protected:
    virtual void NativeConstruct() override;

    /*
                                    Data.
    */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data| Configurations")
    ERegionTag RegionTag;
public:


    /*
                              UI event functions.
    */
    virtual void RemoveStored(TObjectPtr<UItemInstance>& AssocaitedInstance) override;


    /*
                                  Accessors.
    */
    FORCEINLINE const ERegionTag& GetRegionTag() const { return RegionTag; }
};