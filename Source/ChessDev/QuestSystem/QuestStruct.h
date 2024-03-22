#pragma once

#include "CoreMinimal.h"

#include "QuestStep.h"
#include "Engine/DataTable.h"
#include "QuestStruct.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FQuestStruct : public FTableRowBase
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly)
    FString QuestName;

    UPROPERTY(BlueprintReadOnly)
    FString QuestDescription;

    UPROPERTY(BlueprintReadOnly)
    TArray<FQuestStepStruct> QuestSteps;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int Progress = 0;

    UPROPERTY(BlueprintReadOnly)
    int ProgressTotal;
};