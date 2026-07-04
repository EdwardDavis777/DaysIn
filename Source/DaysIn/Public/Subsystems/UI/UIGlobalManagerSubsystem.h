#pragma once

/*
     Manages visibility states of main widgets that essentially ask to be
	 handled by this manager. Will allow only a 1:1 relationship with its managed
	 widget and the view-port. Disallows any other managed widget to share the view-port
	 with anything else.

	 Therefore; only widgets that must implement the above should be managed by this
	 subsystem. This subsystem is not a cache, it will track only the widget it is 
	 currently rendering, and thats it. Once its cleared its pointer is freed until
	 the next widget is rendered. And even then, it holds just a general UUserWidget
	 pointer to the current view-port widget.

*/


//Engine imports.
#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "UIGlobalManagerSubsystem.generated.h"



UCLASS()
class DAYSIN_API UUIGlobalManagerSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

private:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;


    /*
	                    UUIGlobalManagerSubsystem cache components.
	*/
	UPROPERTY()
	TObjectPtr<UUserWidget> ManagedWidget;
     
	/*
	                         UUIGlobalManagerSubsystem states.
	*/
	UPROPERTY()
	bool bViewportCleared = true;

public:


	/*
	                                     Mutators.
	*/

	/*
	     Sets the current widget to the view-port and manages its render state
		 dis-allowing others to be added to the view-port.

		 @param Widget: pointer to the widget you wish to add to the view-port
		 and manage.
	*/
	void SetManagedWidget(UUserWidget* Widget);


	/*
	     Clears the current view-port and allows the subsystem to manage other
		 widgets.

		 @param Widget: pointer to the current widget, needed to ensure that the 
		 caller actually owns the widget that is trying to be cleared.
	*/
	void ClearManagedWidget(UUserWidget* Widget);


	/*
	                                    Accessors.
	*/
	const UUserWidget* GetManagedWidget() const;
	const bool& bIsViewportCleared() const;
};