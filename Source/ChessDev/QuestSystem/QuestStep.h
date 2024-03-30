#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "QuestStepStruct.h"
#include "Trigger.h"
#include "QuestStep.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStepProgressUpdated, UQuestStep*, Step);

UCLASS(BlueprintType)
class UQuestStep : public UObject
{
    GENERATED_BODY()

public:
    UQuestStep();

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString StepDescription;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int StepProgress;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int StepProgressTotal;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int StepTriggerId;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UTrigger* StepTrigger;

    UFUNCTION(BlueprintCallable)
    void Init(const FQuestStepStruct& StepStruct, const TArray<UTrigger*>& Triggers);

    UFUNCTION(BlueprintCallable)
    FQuestStepStruct GetQuestStepStruct() const;

    UFUNCTION(BlueprintCallable)
    void BindToTrigger(UTrigger* Trigger);

    UFUNCTION(BlueprintCallable)
    void UpdateProgress();

    UPROPERTY(BlueprintAssignable, Category = "QuestStep")
    FOnStepProgressUpdated OnStepProgressUpdated;
};
