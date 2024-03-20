// Copyright (c) 2024 Artsiom Chmutau

#include "QuestManager.h"

#include "Kismet/GameplayStatics.h"
#include "QuestStruct.h"
#include "Quest.h"
#include "../GameInstanceBase.h"

UQuestManager::UQuestManager()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void UQuestManager::BeginPlay()
{
    Super::BeginPlay();

    // GameInstance = Cast<UGameInstanceBase>(UGameplayStatics::GetGameInstance(this));

    // if (!GameInstance)
    // {
    //     if (GEngine)
    //     {
    //         GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("[ERROR] GameInstance is NOT valid!"));
    //         UE_LOG(LogTemp, Error, TEXT("[ERROR] GameInstance is NOT valid!"));
    //     }
        
    //     return;
    // }
}

TArray<uint8> UQuestManager::Save()
{
    // TODO: Implement
    TArray<uint8> Data;




    return Data;
}

void UQuestManager::Load(const TArray<uint8>& Data, const TArray<UTrigger*>& Triggers)
{
    // Byte array is a file with quests. If PlayerStorage is empty, this the file with all the existing quests from the TitleStorage. Files are in JSON format.

    // TArray<uint8>& -> JSON

    FString path = *FPaths::ProjectContentDir().Append("/Quests.json");
    std::fstream stream(std::string(TCHAR_TO_UTF8(*path)));

    if (!stream.is_open())
    {
        UE_LOG(LogTemp, Error, TEXT("[ERROR] Couldn't open the Quests.json file."));

        if (GEngine)
        {
            GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("[ERROR] Couldn't open the Quests.json file."));
            GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT("Path: %s"), *path));
        }

        return;
    }

    stream.write(reinterpret_cast<const char*>(Data.GetData()), Data.Num());

    UE_LOG(LogTemp, Display, TEXT("Quests.json loaded."));

    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, TEXT("Quests.json loaded."));
    }
    
    // JSON -> TArray<FQuestStruct>
    // JSON File -> FString -> FJsonObject -> TArray<FQuestStruct>
    // https://www.youtube.com/watch?v=4wJ45mrzrkM&t=9s
    // TArray<TSharedPtr<FJsonValue>> JsonQuestsArray = JsonObject->GetArrayField("quests");

    stream.close();


    return;


    TArray<FQuestStruct> PlayerQuests; // Place quests from the JSON file to this array

    for (FQuestStruct PlayerQuest : PlayerQuests)
        this->AddQuest(PlayerQuest, Triggers);

}

void UQuestManager::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    // if (QuestSave)
    // {
    //     TArray<FQuestStruct> questStructs;

    //     for (UQuest* quest : Quests)
    //     {
    //         questStructs.Add(quest->GetQuestStruct());
    //     }

    //     QuestSave->SaveQuestManager(questStructs);

    //     UE_LOG(LogTemp, Display, TEXT("QuestManager saved"));
    // }

    Super::EndPlay(EndPlayReason);
}

void UQuestManager::AddQuest(const FQuestStruct NewQuest, const TArray<UTrigger*>& Triggers)
{
    UQuest* quest = NewObject<UQuest>();
    quest->Init(NewQuest, Triggers);

    Quests.Add(quest);
}
