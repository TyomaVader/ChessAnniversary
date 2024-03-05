// Copyright (c) 2024 Artsiom Chmutau

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "QuestStep.h"
#include "Quest.generated.h"

/**
 * 
 */
UCLASS()
class CHESSDEV_API UQuest : public UObject
{
	GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    FString QuestName;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    TArray<UQuestStep*> QuestSteps;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    FString Description;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    FString Status;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    float Progress;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    FString Reward;

    UFUNCTION(BlueprintCallable)
    void AddQuestStep(UQuestStep* NewStep);
};
