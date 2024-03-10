// Copyright (c) 2024 Artsiom Chmutau

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "Kismet/GameplayStatics.h"
#include "QuestManager.h"
#include "QuestSave.generated.h"

/**
 * 
 */
UCLASS()
class CHESSDEV_API UQuestSave : public USaveGame
{
    GENERATED_BODY()

public:
    static const FString SlotName;

    UFUNCTION(BlueprintCallable)
    void SaveQuestManager(TArray<FQuestStruct> QuestsToSave);

    UFUNCTION(BlueprintCallable)
    void LoadQuestManager(UQuestManager* QuestManagerRef);

private:
    UPROPERTY()
    TArray<FQuestStruct> PlayerQuests;

    void Save();
};
