#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Quest.h"
#include "QuestManager.generated.h"

UCLASS(Blueprintable)
class CHESSDEV_API UQuestManager : public UObject
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintReadOnly)
    TArray<UQuest*> ActiveQuests;

    UPROPERTY(BlueprintReadOnly)
    TArray<UQuest*> CompletedQuests;

    UFUNCTION(BlueprintCallable)
    void AddQuest(UQuest* NewQuest);

    UFUNCTION(BlueprintCallable)
    void RemoveQuest(UQuest* QuestToRemove);
};
