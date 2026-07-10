//Engine imports.
#include "UI/GlobalActions/TransformAction.h"

//Component imports.
#include "Blueprint/UserWidget.h"




namespace Transform
{
	int32 Rot::RotNeg90(UUserWidget* WidgetToRotate)
	{
		if (!WidgetToRotate) return int32();

		FWidgetTransform Transform90;
		Transform90.Angle = -90;
		WidgetToRotate->SetRenderTransform(Transform90);

		return Transform90.Angle;
	}

	int32 Rot::RotNeg90(UWidget* WidgetToRotate)
	{
		if (!WidgetToRotate) return int32();

		FWidgetTransform Transform90;
		Transform90.Angle = -90;
		WidgetToRotate->SetRenderTransform(Transform90);
		
		return Transform90.Angle;
	}

	int32 Rot::Rot0(UUserWidget* WidgetToRotate)
	{
		if (!WidgetToRotate) return int32();
		FWidgetTransform Transform0;
		Transform0.Angle = 0;
		WidgetToRotate->SetRenderTransform(Transform0);

		return Transform0.Angle;
	}

	int32 Rot::Rot0(UWidget* WidgetToRotate)
	{
		if (!WidgetToRotate) return int32();
		FWidgetTransform Transform0;
		Transform0.Angle = 0;
		WidgetToRotate->SetRenderTransform(Transform0);

		return Transform0.Angle;
	}
}

