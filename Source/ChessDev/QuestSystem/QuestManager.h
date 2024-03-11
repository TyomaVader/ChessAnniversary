// Copyright (c) 2024 Artsiom Chmutau

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Quest.h"
#include "../GameInstanceBase.h"
#include "QuestManager.generated.h"

class UQuestSave;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CHESSDEV_API UQuestManager : public UActorComponent
{
    GENERATED_BODY()

public:
    UQuestManager();

    UFUNCTION(BlueprintCallable)
    void AddQuest(const FQuestStruct NewQuest);

protected:
    // Called when the game starts
    virtual void BeginPlay() override;

    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:
    UPROPERTY(BlueprintReadOnly, Category = "QuestSystem")
    TArray<UQuest*> Quests;

private:
    UPROPERTY()
    UQuestSave* QuestSave;

    UPROPERTY()
    UGameInstanceBase* GameInstance;
};
