// Copyright (c) 2024 Artsiom Chmutau

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "QuestStep.h"
#include "QuestStruct.h"
#include "Quest.generated.h"

/**
 * 
 */
UCLASS()
class CHESSDEV_API UQuest : public UObject
{
	GENERATED_BODY()

public:
    UQuest();

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    FString QuestName;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    FString QuestDescription;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    TArray<UQuestStep*> QuestSteps;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    int Progress;

    UFUNCTION(BlueprintCallable)
    void Init(const FQuestStruct& QuestStruct);

    UFUNCTION(BlueprintCallable)
    FQuestStruct GetQuestStruct() const;
};
