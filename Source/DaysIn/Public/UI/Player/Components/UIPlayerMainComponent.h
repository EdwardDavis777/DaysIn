#pragma once


/*

     Handles the construction, and life-time of the UIPlayerMain widget
	 instance.

	 Also handles UI main toggle events, such as player input that toggles 
	 the UI into the view-port, or out of the view-port etc.
	  
	 Note: at its core, visibility is handled by the UIGlobalManagerSubsystem
	 class. As the UI main is a main UI widget and cannot share the view-port
	 with others. 
	  
*/


//Engine imports.
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UIPlayerMainComponent.generated.h"



//Forward declares.
class UUIPlayerMain;
class UUIGlobalManagerSubsystem;
class UPlayerUISubsystem;
class UPlayerSubsystem;




UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DAYSIN_API UUIPlayerMainComponent : public UActorComponent
{
	GENERATED_BODY()

private:

	/*
	     Binds class functions to global system
		 dispatch events.
	*/
	void BindDelegates();

	/*
	                                 UUIPlayerMainComponent components.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Configurations|UI", meta = (AllowPrivateAccess = true))
	TSubclassOf<UUIPlayerMain> UIMainClass;

    /*
	                                         Cache components.
	*/  
	UPROPERTY(VisibleAnywhere, Category = "Data|Memory", meta = (AllowPrivateAccess = true))
	TObjectPtr<UUIPlayerMain> UIMain;

	UPROPERTY(VisibleAnywhere, Category = "Data|Memory", meta = (AllowPrivateAccess = true))
	TObjectPtr<UUIGlobalManagerSubsystem> UIGlobalManagerSubsystem;

	UPROPERTY(VisibleAnywhere, Category = "Data|Memory", meta = (AllowPrivateAccess = true))
	TObjectPtr<UPlayerUISubsystem> PlayerUISubsystem;

	UPROPERTY(VisibleAnywhere, Category = "Data|Memory", meta = (AllowPrivateAccess = true))
	TObjectPtr<UPlayerSubsystem> PlayerSubsystem;


	/*
	                                     Widget construction functions.
	*/

	/*
	      Constructs a UI main widget instance from the class reference 
		  stored on this component the moment this component is initialized.
	*/
	void MakeUIMain();


    /*
	                                    Toggle UI main event functions.
	*/

	/*
	    Delegated function; toggles the visibility of the UI main widget
		through the UI global manager subsystem.
	*/
	void ToggleUIMain();


	/*
	                                          Engine overrides.
	*/
	virtual void BeginPlay() override;
};