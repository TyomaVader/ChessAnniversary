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


DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnQuestNotification, FString, Name, int, Progress, int, ProgressTotal);

/**
 * QuestManager is a component that manages the quests in the game.
*/
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CHESSDEV_API UQuestManager : public UActorComponent
{
    GENERATED_BODY()

public:
    UQuestManager();

    /**
     * Add a new quest to the Quests array.
     * 
     * @param NewQuest The quest to add.
     * @param Triggers The triggers array for identifying the binded triggers.
     * 
     * @return void
    */
    UFUNCTION(BlueprintCallable)
    void AddQuest(const FQuestStruct NewQuest, const TArray<UTrigger*>& Triggers);

    UFUNCTION(BlueprintCallable)
    TArray<uint8> Save();

    /**
     * Load the quests from the file.
     * 
     * @param Data ByteArray file from the TitleStorage or PlayerStorage.
     * @param Triggers The triggers array for identifying the binded triggers.
     * @param bIsPlayerStorage The flag to determine if the data is from the player storage.
     * 
     * @return void
    */
    UFUNCTION(BlueprintCallable)
    void Load(const TArray<uint8>& Data, const TArray<UTrigger*>& Triggers, bool bIsPlayerStorage);


    UFUNCTION(BlueprintCallable)
    void QuestProgressUpdateNotify(UQuest* Quest);

    UFUNCTION(BlueprintCallable)
    void QuestStepProgressUpdateNotify(UQuestStep* Step);

protected:
    // Called when the game starts
    virtual void BeginPlay() override;

    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:
    UPROPERTY(BlueprintReadOnly, Category = "QuestSystem")
    TArray<UQuest*> Quests;

    UPROPERTY(BlueprintAssignable, Category = "QuestSystem")
    FOnQuestNotification OnQuestNotification;

private:
    UPROPERTY()
    UGameInstanceBase* GameInstance;
};
