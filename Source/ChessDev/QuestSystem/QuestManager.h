// Copyright (c) 2024 Artsiom Chmutau

#pragma once

#include <fstream>

#include "ReadWriteJson.h"

#include "CoreMinimal.h"
#include "Misc/Paths.h"
#include "Dom/JsonObject.h"
#include "Components/ActorComponent.h"
#include "Quest.h"
#include "../GameInstanceBase.h"
#include "QuestManager.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CHESSDEV_API UQuestManager : public UActorComponent
{
    GENERATED_BODY()

public:
    UQuestManager();

    UFUNCTION(BlueprintCallable)
    void AddQuest(const FQuestStruct NewQuest, const TArray<UTrigger*>& Triggers);

    UFUNCTION(BlueprintCallable)
    TArray<uint8> Save();

    UFUNCTION(BlueprintCallable)
    void Load(const TArray<uint8>& Data, const TArray<UTrigger*>& Triggers);

protected:
    // Called when the game starts
    virtual void BeginPlay() override;

    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:
    UPROPERTY(BlueprintReadOnly, Category = "QuestSystem")
    TArray<UQuest*> Quests;

private:
    UPROPERTY()
    UGameInstanceBase* GameInstance;
};
