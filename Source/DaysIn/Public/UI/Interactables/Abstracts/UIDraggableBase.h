#pragma once

/*
     Defines class defaults for all draggable widgets used
	 in user interfaces.
*/


//Other imports.
#include "UI/Interactables/AbstractData/UIDraggableData.h"


//Engine imports.
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UIDraggableBase.generated.h"



//Forward declares.
class USizeBox;
class UBorder;
class UCanvasPanel;
class UImage;
class UDraggableUIComponent;
class AItemBase;
class UUIDraggableSubsystem;
class UPlayerUISubsystem;


UCLASS(Abstract)
class DAYSIN_API UUIDraggableBase : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	void BindDelegates();
	void UnBindDelegates();

	/*
	                         UUIDraggableBase components.
	*/
	UPROPERTY(meta = (BindWidget, AllowPrivateAccess = true))
	TObjectPtr<USizeBox> RootSizeBox;

	UPROPERTY(meta = (BindWidget, AllowPrivateAccess = true))
	TObjectPtr<UBorder> MainBorder;

	UPROPERTY(meta = (BindWidget, AllowPrivateAccess = true))
	TObjectPtr<UCanvasPanel> GroupPanel;

	UPROPERTY(meta = (BindWidget, AllowPrivateAccess = true))
	TObjectPtr<UImage> DragIcon;




	/*
	                                 Custom components.
	*/
	UPROPERTY(EditAnywhere, Category = "Component")
	TObjectPtr<UDraggableUIComponent> DraggableUIComponent;

	/*
	                                  Cache components.
	*/
	UPROPERTY()
	TObjectPtr<UUIDraggableSubsystem> DraggableSubsystem;

	UPROPERTY()
	TObjectPtr<UPlayerUISubsystem> PlayerUISubsystem;


	/*
	                                    Data structs.
	*/
	UPROPERTY(EditAnywhere, Category = "Data")
	FData Data;




	/*
	                          Engine UI interact event functions.
	*/
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& InOperation) override;
	virtual void NativeOnDragCancelled(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGoemetry, const FPointerEvent& InMouseEvent) override;



	/*
	                                  Template accessors.
	*/

	/*
	     Returns to a derived draggable base class an instance of their specific
		 assocaited item instance pointer.

		 @tparam UItemInstance: T must ba a UItemInstance.

		 @return UItemInstance: pointer to an assocaited item instance pointer
		 with the class type of this draggables assocaited instance.
	*/
	template<typename TInstance>
	TInstance* FindAssocaitedInstance()
	{
		if (!Data.RuntimeData.GeneralInstance) return nullptr;

		static_assert(TIsDerivedFrom<TInstance, UItemInstance>::IsDerived, "T must be a UItemInstance");
		if (TInstance* Inst = Cast<TInstance>(Data.RuntimeData.GeneralInstance))
		{
			return Inst;
		}
		return nullptr;
	}
public: 




	/*
	                             Virtual construct functions.
	*/

	/*
	     Initializes a general pointer to some item instance in memory that 
		 is associated with this draggable widget.

		 @param Instance: pointer to the item instance you wish to 
		 assoicate with this draggable widget.
	*/
	virtual void Init(UItemInstance* Instance);




	/*
	    Initializes a general pointer to some item instance in memory
		through a raw item pointer that is assocaited with this draggable widget.

		@param RawItem: raw item pointer whose instance you wish to assocaite 
		with this draggable widget.
	*/
	virtual void Init(AItemBase* RawItem);


	/*
	                                Virtual hook functions.
	*/

	/*
	     Allows derived classes the ability to hook into their assocaited drag 
		 event initialized from the base. Override this function
		 and implement logic you wish to happen during drag events.
	*/
	virtual void HookDragEvent();


	/*
	    Allows derived classes the ability to hook into their assocaited mouse
		enter events initialized from the base. Override this function
		and implment logic you wish to happen during mouse enter events.
	*/ 
	virtual void HookMouseEnterEvent();


	/*
		Allows derived classes the ability to hook into their assocaited mouse
		leave events initialized from the base. Override this function
		and implment logic you wish to happen during mouse leave events.
	*/
	virtual void HookMouseLeaveEvent();

	/*
	    Allows derived classes the ability to hook into their assocaited
		reset events. Called when the main widget (player widget) is removed
		from render.
	*/
	virtual void HookResetEvent();



	/*
	                                     Mutators.
	*/
	void AddToRender();
	void RemoveFromRender();




   

	/*
	                                     Accessors.
	*/
	USizeBox* GetSizeBox();
	const FVector2D GetSizeBoxSize() const;
	TObjectPtr<UBorder> GetBorder();
	TObjectPtr<UImage> GetImage();
	UItemInstance* GetAssocaitedInstance() const;
	const bool bVisible() const;
	const FData& GetData() const;
};