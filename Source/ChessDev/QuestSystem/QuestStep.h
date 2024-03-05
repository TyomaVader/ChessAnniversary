#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Trigger.h"
#include "QuestStep.generated.h"

UCLASS(Blueprintable)
class CHESSDEV_API UQuestStep : public UObject
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    FString StepDescription;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    float StepProgress;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    UTrigger* StepTrigger;

    UFUNCTION(BlueprintCallable)
    void BindToTrigger(UTrigger* Trigger);

    UFUNCTION(BlueprintCallable)
    void UpdateProgress();
};
