//Engine imports.
#include "UI/Storages/Abstracts/UICollectableStorageInventory.h"



/*
 
     TODO: Construct a new UI native component, and start overriding droppable hook events
	 from your drop class to add drag and drop functions to the inventory 
	 widget instances.

*/


void UUICollectableStorageInventory::NativeConstruct()
{
	Super::NativeConstruct();
}



/*
                                  UI event functions.
*/

void UUICollectableStorageInventory::RemoveStored(TObjectPtr<UItemInstance>& AssocaitedInstance)
{
	Super::RemoveStored(AssocaitedInstance);
}