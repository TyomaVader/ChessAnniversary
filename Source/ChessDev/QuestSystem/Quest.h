// Copyright (c) 2024 Artsiom Chmutau

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "QuestStep.h"
#include "QuestStruct.h"
#include "Quest.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnQuestProgressUpdated, UQuest*, Quest);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnQuestStepProgressUpdated, UQuestStep*, Step);

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

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    int ProgressTotal;

    UFUNCTION(BlueprintCallable)
    void Init(const FQuestStruct& QuestStruct, const TArray<UTrigger*>& Triggers);

    UFUNCTION(BlueprintCallable)
    FQuestStruct GetQuestStruct() const;

    UFUNCTION(BlueprintCallable)
    void UpdateProgress(UQuestStep* Step);

    UPROPERTY(BlueprintAssignable, Category = "Quest")
    FOnQuestProgressUpdated OnQuestProgressUpdated;

    UPROPERTY(BlueprintAssignable, Category = "Quest")
    FOnQuestStepProgressUpdated OnQuestStepProgressUpdated;
};
