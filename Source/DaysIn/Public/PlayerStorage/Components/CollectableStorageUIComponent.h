#pragma once

/*

     Handles the construction of a collectable storage objects
	 inventory widget, etc.

*/


//Engine imports.
#include "CoreMinimal.h"
#include "CustomClasses/Components/GameplayComponent.h"
#include "CollectableStorageUIComponent.generated.h"



//Forward declares.
class UCollectableStorageInstance;
class UUICollectableStorageInventory;
class UPlayerUISubsystem;
class UUIRegionPanel;



UCLASS()
class DAYSIN_API UCollectableStorageUIComponent : public UGameplayComponent
{
	GENERATED_BODY()

public:
	virtual void Initialize(UWorld* WorldContext, UObject* OwnerObject) override;


   /*
                           Widget construction event functions.
   */
   

   /*
       Constructs a collectable storages inventory and adds it to some panel
	   inside of the players UI main.

	   @param Columns: reference to the amount of columns
	   this spatial grid implements.

	   @param Rows: reference to the amount of rows
	   this spatial grid implements.
   */
   void MakeInventory(const int32& Columnes,const int32& Rows);


   /*
       Creates a brand new inventory widget instance in memory for an initial
	   construction event.

	   @param Columns: reference to the amount of columns
	   this spatial grid implements.

	   @param Rows: reference to the amount of rows
	   this spatial grid implements.
   */
   void ConstructInitial(const int32& Columns, const int32& Rows);


   /*
	   Performs a re-build but only  for its assocaited region panel that
	   it gets added back into. Performs simple initializations for an already
	   constrcuted inventory instance.
  */
   void RebuildInRegion();





   /*
                               Widget deconstruction event functions.
   */

   /*
        Clears this inventory widget from its region panel, but keeps it in 
		memory for later.
   */
   void ClearInventory();





private:

   /*
                                        Helper functions.
   */

   /*
       Sets the size of an assocaited region panel in pixel width/height,
	   and sets the child widgets root size box size.

	   @param RegionPanel: pointer to a region panel.

	   @param Columns: reference to the amount of columns
	   this spatial grid implements.

	   @param Rows: reference to the amount of rows
	   this spatial grid implements.
   */
   void SetRegionPanelSize(UUIRegionPanel* RegionPanel,const int32& Columns,const int32& Rows);



	/*
	                                     Components.
	*/
	UPROPERTY()
	TObjectPtr<UCollectableStorageInstance> CollectableStorageInstance;

	UPROPERTY()
	TObjectPtr<UUICollectableStorageInventory> InventoryWidget;



	/*
	                                  Cache components.
	*/
	UPROPERTY()
	TObjectPtr<UPlayerUISubsystem> PlayerUISubsystem;




	/*
	                           Runtime components.
	*/

	UPROPERTY()
	TObjectPtr<UUIRegionPanel> ParentPanel;
	
	UPROPERTY()
	bool bAlreadyConstructed = false; 
};