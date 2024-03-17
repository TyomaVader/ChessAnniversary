// Copyright (c) 2024 Artsiom Chmutau

#include "QuestManager.h"

#include "Kismet/GameplayStatics.h"
#include "QuestStruct.h"
#include "Quest.h"
#include "../GameInstanceBase.h"
#include "QuestSave.h"

UQuestManager::UQuestManager()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void UQuestManager::BeginPlay()
{
    Super::BeginPlay();

    GameInstance = Cast<UGameInstanceBase>(UGameplayStatics::GetGameInstance(this));

    if (!GameInstance)
    {
        if (GEngine)
        {
            GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("[ERROR] GameInstance is NOT valid!"));
        }
        
        return;
    }


    QuestSave = GameInstance->QuestSave;

    FTimerHandle Handle;
    GetWorld()->GetTimerManager().SetTimer(Handle, [this]()
    {
        UE_LOG(LogTemp, Warning, TEXT("Timer finished"))
        FTimerHandle Handle;
        GetWorld()->GetTimerManager().SetTimer(Handle, [this]()
        {
            QuestSave->LoadQuestManager(this);

            UE_LOG(LogTemp, Display, TEXT("QuestManager loaded"));
            
        }, 0.0001F, false);
    }, 0.0001F, false);
}

void UQuestManager::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    if (QuestSave)
    {
        TArray<FQuestStruct> questStructs;

        for (UQuest* quest : Quests)
        {
            questStructs.Add(quest->GetQuestStruct());
        }

        QuestSave->SaveQuestManager(questStructs);

        UE_LOG(LogTemp, Display, TEXT("QuestManager saved"));
    }

    Super::EndPlay(EndPlayReason);
}

void UQuestManager::AddQuest(const FQuestStruct NewQuest)
{
    UQuest* quest = NewObject<UQuest>();
    quest->Init(NewQuest);

    Quests.Add(quest);
}
