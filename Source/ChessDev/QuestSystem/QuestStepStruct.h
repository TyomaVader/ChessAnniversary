#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Trigger.h"
#include "QuestStepStruct.generated.h"

USTRUCT(BlueprintType)
struct FQuestStepStruct : public FTableRowBase
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString StepDescription;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int StepProgress = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int StepProgressTotal;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int StepTriggerId;
};