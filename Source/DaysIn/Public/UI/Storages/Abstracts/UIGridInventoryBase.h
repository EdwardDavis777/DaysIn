#pragma once

/*
     Defines class defaults for spatial grid inventory
	 widgets. Can be used for backpacks, crate storages etc.

	 Anything that you wish to implement a spatial grid for dragging and dropping
	 should be derived from this class. It does not handle any item/instance related
	 data, you have to implement that your self. This class is meant only to handle
	 the construction of a visual grid, and really nothing else. Use the droppable
	 hook events etc for actual inventory logic.
*/


//Other imports.
#include "StaticData/UI/WidgetMath.h"



//Engine imports.
#include "CoreMinimal.h"
#include "UI/Interactables/Abstracts/UIDroppableBase.h"
#include "UIGridInventoryBase.generated.h"




UCLASS(Abstract)
class DAYSIN_API UUIGridInventoryBase : public UUIDroppableBase
{
	GENERATED_BODY()
	
public:

	/*
	     Initializes grid components, allowing the paint member function to draw
		 grid visuals. Also sets the size of the inherited root size box to account
		 for dynamic sizing.

		 @param X: amount of columns you wish to be drawn inside 
		 of a grid.

		 @param Y: amount of rows you wish to be drawn inside
		 of a grid.
	*/
	virtual void InitializeGrid(int32 X, int32 Y);
	

protected:
	/*
								       Tweakable members.
	*/
	UPROPERTY(EditAnywhere, Category = "GridData| Color")
	FLinearColor GridLineColor = FLinearColor{ 1.0f,1.0f,1.0f,1.0f };
	

	/*
	                                 Cached static members.
	*/
	UPROPERTY(VisibleAnywhere, Category = "GridData| Constants")
	int32 TileSize = WidgetMath::TileSize;

	UPROPERTY(VisibleAnywhere, Category = "GridData| Runtime")
	int32 Columns = 0;

	UPROPERTY(VisibleAnywhere, Category = "GridData| Runtime")
	int32 Rows = 0;


	/*
	                                  Paint event functions.
	*/
	int32 NativePaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, 
	FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, 
	bool bParentEnabled) const override;

public:

	/*
	                                      Accessors.
	*/
	FORCEINLINE const int32& GetColumns() const { return Columns; }
	FORCEINLINE const int32& GetRows() const { return Rows; }
};