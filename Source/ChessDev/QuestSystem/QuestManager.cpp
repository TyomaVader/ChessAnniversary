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
}

TArray<uint8> UQuestManager::Save()
{
    // Parse the Quests into Json Objects
    TSharedPtr<FJsonObject> JsonObject = MakeShared<FJsonObject>();
    TArray<TSharedPtr<FJsonValue>> JsonQuestsArray;

    if (!JsonObject.IsValid())
    {
        UE_LOG(LogTemp, Error, TEXT("[ERROR] JsonObject is invalid."));
        return TArray<uint8>();
    }

    for (UQuest* Quest : Quests)
    {
        TSharedPtr<FJsonObject> QuestJsonObject = MakeShared<FJsonObject>();

        QuestJsonObject->SetStringField("name", Quest->QuestName);
        QuestJsonObject->SetStringField("description", Quest->QuestDescription);
        QuestJsonObject->SetNumberField("progress", Quest->Progress);

        TArray<TSharedPtr<FJsonValue>> JsonQuestStepsArray;

        for (UQuestStep* QuestStep : Quest->QuestSteps)
        {
            TSharedPtr<FJsonObject> QuestStepJsonObject = MakeShared<FJsonObject>();

            QuestStepJsonObject->SetStringField("description", QuestStep->StepDescription);
            QuestStepJsonObject->SetNumberField("progressTotal", QuestStep->StepProgressTotal);
            QuestStepJsonObject->SetNumberField("progress", QuestStep->StepProgress);
            QuestStepJsonObject->SetNumberField("triggerId", QuestStep->StepTriggerId);

            JsonQuestStepsArray.Add(MakeShared<FJsonValueObject>(QuestStepJsonObject));
        }

        QuestJsonObject->SetArrayField("questSteps", JsonQuestStepsArray);

        JsonQuestsArray.Add(MakeShared<FJsonValueObject>(QuestJsonObject));
    }

    JsonObject->SetArrayField("quests", JsonQuestsArray);

    // Save the Json to the local Quests.json
    bool bSuccess;

    FString path = *FPaths::ProjectContentDir().Append("/Quests.json");
    FString jsonString = UReadWriteJson::WriteJson(path, JsonObject, bSuccess);

    if (!bSuccess)
    {
        UE_LOG(LogTemp, Error, TEXT("[ERROR] Couldn't save the Quests.json file."));

        if (GEngine)
        {
            GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("[ERROR] Couldn't save the Quests.json file."));
            GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT("Path: %s"), *path));
        }

        return TArray<uint8>();
    }

    UE_LOG(LogTemp, Display, TEXT("[SUCCESS] Quests.json saved."));
    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, TEXT("[SUCCESS] Quests.json saved."));
    }

    // Upload the Data to the PlayerStorage
    TArray<uint8> Data;
    Data.Append((uint8*)TCHAR_TO_UTF8(*jsonString), jsonString.Len());

    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, TEXT("[SUCCESS] Quests.json loaded to ByteArray."));
    }

    return Data;
}

void UQuestManager::Load(const TArray<uint8>& Data, const TArray<UTrigger*>& Triggers, bool bIsPlayerStorage)
{
    // Byte array is a file with quests. If PlayerStorage is empty, this the file with all the existing quests from the TitleStorage. Files are in JSON format.

    // Load the Data to the local Quests.json
    FString path = *FPaths::ProjectContentDir().Append("/Quests.json");
    std::ofstream stream(std::string(TCHAR_TO_UTF8(*path)));

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

    UE_LOG(LogTemp, Display, TEXT("[SUCCESS] Quests.json loaded."));

    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, TEXT("[SUCCESS] Quests.json loaded."));
    }

    stream.close();


    // Parse the Json to Quest objects
    bool bSuccess;

    TSharedPtr<FJsonObject> JsonObject = UReadWriteJson::ReadJson(path, bSuccess);
    const TArray<TSharedPtr<FJsonValue>> JsonQuestsArray = JsonObject->GetArrayField("quests");

    TArray<FQuestStruct> PlayerQuests;

    for (auto& QuestJsonValue : JsonQuestsArray)
    {
        FQuestStruct QuestStruct;

        TSharedPtr<FJsonObject> QuestJsonObject = QuestJsonValue->AsObject();

        QuestStruct.QuestName = QuestJsonObject->GetStringField("name");
        QuestStruct.QuestDescription = QuestJsonObject->GetStringField("description");

        if (bIsPlayerStorage)
        {
            QuestStruct.Progress = QuestJsonObject->GetIntegerField("progress");
        }

        const TArray<TSharedPtr<FJsonValue>> JsonQuestStepsArray = QuestJsonObject->GetArrayField("questSteps");

        if (GEngine)
        {
            GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, FString::Printf(TEXT("JsonQuestStepsArray size: %d"), JsonQuestStepsArray.Num()));
        }

        for (TSharedPtr<FJsonValue> QuestStepJsonValue : JsonQuestStepsArray)
        {
            FQuestStepStruct QuestStepStruct;

            TSharedPtr<FJsonObject> QuestStepJsonObject = QuestStepJsonValue->AsObject();

            QuestStepStruct.StepDescription = QuestStepJsonObject->GetStringField("description");
            QuestStepStruct.StepProgressTotal = QuestStepJsonObject->GetIntegerField("progressTotal");
            QuestStepStruct.StepTriggerId = QuestStepJsonObject->GetIntegerField("triggerId");

            if (bIsPlayerStorage)
            {
                QuestStepStruct.StepProgress = QuestStepJsonObject->GetIntegerField("progress");
            }

            QuestStruct.QuestSteps.Add(QuestStepStruct);
        }

        PlayerQuests.Add(QuestStruct);
    }

    for (FQuestStruct PlayerQuest : PlayerQuests)
        this->AddQuest(PlayerQuest, Triggers);
}

void UQuestManager::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    Super::EndPlay(EndPlayReason);
}

void UQuestManager::AddQuest(const FQuestStruct NewQuest, const TArray<UTrigger*>& Triggers)
{
    UQuest* quest = NewObject<UQuest>();
    quest->Init(NewQuest, Triggers);
    
    if (quest->Progress < quest->ProgressTotal)
    {
        quest->OnQuestProgressUpdated.AddDynamic(this, &UQuestManager::QuestProgressUpdateNotify);
        quest->OnQuestStepProgressUpdated.AddDynamic(this, &UQuestManager::QuestStepProgressUpdateNotify);
    }

    Quests.Add(quest);
}

void UQuestManager::QuestProgressUpdateNotify(UQuest* Quest)
{
    OnQuestNotification.Broadcast(Quest->QuestName, Quest->Progress, Quest->ProgressTotal);

    if (Quest->Progress >= Quest->ProgressTotal)
    {
        if (GEngine)
        {
            GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, FString::Printf(TEXT("Quest %s completed!"), *Quest->QuestName));
        }

        UE_LOG(LogTemp, Display, TEXT("Quest %s completed!"), *Quest->QuestName);

        Quest->OnQuestProgressUpdated.RemoveDynamic(this, &UQuestManager::QuestProgressUpdateNotify);
    }
}

void UQuestManager::QuestStepProgressUpdateNotify(UQuestStep* Step)
{
    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, FString::Printf(TEXT("QuestStep %s progress updated. Progress: %d"), *Step->StepDescription, Step->StepProgress));
    }

    UE_LOG(LogTemp, Display, TEXT("QuestStep %s progress updated. Progress: %d"), *Step->StepDescription, Step->StepProgress);

    OnQuestNotification.Broadcast(Step->StepDescription, Step->StepProgress, Step->StepProgressTotal);
}