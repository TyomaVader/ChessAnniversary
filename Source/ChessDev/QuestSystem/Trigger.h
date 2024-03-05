#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Trigger.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTriggerActivatedDelegate);

UCLASS(Blueprintable)
class CHESSDEV_API UTrigger : public UObject
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintAssignable, Category = "Trigger")
    FOnTriggerActivatedDelegate OnTriggerActivated;

    UFUNCTION(BlueprintCallable, Category = "Trigger")
    void ActivateTrigger();
};