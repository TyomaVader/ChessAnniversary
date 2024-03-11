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

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString QuestName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString QuestDescription;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FQuestStepStruct> QuestSteps;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int Progress;
};
