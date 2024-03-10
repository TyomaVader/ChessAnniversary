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
    float StepProgress;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UTrigger* StepTrigger;
};
