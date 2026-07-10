#pragma once


/*

    Defines class defaults for visible collectable storage inventory
 	spatil grids. Such as backpacks, med bags etc.
    
    Also handles interaction hook events, such as droppable storage 
    events etc.

*/  
 

//Engine imports.
#include "CoreMinimal.h"
#include "UI/Storages/Abstracts/UIGridInventoryBase.h"
#include "UICollectableStorageInventory.generated.h"




//Forward declares.
class UStorageUIInventoryComponent;
class UCollectableStorageInstance;
class UStorageInventorySubsystem;




UCLASS()
class DAYSIN_API UUICollectableStorageInventory : public UUIGridInventoryBase
{
	GENERATED_BODY()

public:
    virtual void NativeConstruct() override;
    virtual void InitializeGrid(int32 X, int32 Y, UObject* OwnerObject) override;
    void BindDelegates();


    /*
                                 Event functions.
    */
    void AddItemEvent(UObject* StorageObject, UObject* AddedInstance, const FIntPoint& Position);
    virtual void HookDragOverEvent(const FGeometry& InGeometry, const FDragDropEvent& InDragEvent, UDragDropOperation* InOperation) override;
    virtual void HookDragLeaveEvent(const FDragDropEvent& InDragEvent, UDragDropOperation* InOperation) override;
    virtual bool StoreDropped(UItemInstance* ItemInstance, const FIntPoint& Position = FIntPoint(0, 0)) override;
    virtual void RemoveStored(TObjectPtr<UItemInstance>& AssocaitedInstance) override;

private:

    /*
                                     Data.
    */
    UPROPERTY(VisibleAnywhere, Category = "Data| Runtime", meta = (AllowPrivateAccess = true))
    TObjectPtr<UCollectableStorageInstance> StorageInstance;


    /*
                                  components.
    */
    UPROPERTY()
    TObjectPtr<UStorageUIInventoryComponent> StorageUIComponent;

    UPROPERTY()
    TObjectPtr<UStorageInventorySubsystem> StorageInventorySubsystem;
};