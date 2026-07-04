//Engine imports.
#include "Save/SaveArchive/SaveMethods.h"




namespace SaveMethod
{
	void MakeSaveSlot(USaveGame* SaveClass, const FString& SlotName, uint32_t SlotIndex)
	{
		UGameplayStatics::AsyncSaveGameToSlot(SaveClass, SlotName, SlotIndex);
	}

	USaveGame* LoadSave(const FString& SlotName, uint32_t SlotIndex)
	{
		if (SlotName.IsEmpty()) return nullptr;		
		auto* Loaded = UGameplayStatics::LoadGameFromSlot(SlotName, SlotIndex);
		return Loaded;
	}
}