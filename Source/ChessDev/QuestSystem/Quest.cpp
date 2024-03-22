// Copyright (c) 2024 Artsiom Chmutau

#include "Quest.h"

UQuest::UQuest()
{
    QuestName = "New Quest";
    QuestDescription = "New Quest Description";
    Progress = 0;
}

void UQuest::Init(const FQuestStruct& QuestStruct, const TArray<UTrigger*>& Triggers)
{
    QuestName = QuestStruct.QuestName;
    QuestDescription = QuestStruct.QuestDescription;
    Progress = QuestStruct.Progress;
    ProgressTotal = QuestStruct.QuestSteps.Num();

    for (const FQuestStepStruct& Step : QuestStruct.QuestSteps)
    {
        UQuestStep* questStep = NewObject<UQuestStep>();
        questStep->Init(Step, Triggers);

        QuestSteps.Add(questStep);

        questStep->OnStepProgressUpdated.AddDynamic(this, &UQuest::UpdateProgress);
    }
}

FQuestStruct UQuest::GetQuestStruct() const
{
    FQuestStruct QuestStruct;
    QuestStruct.QuestName = QuestName;
    QuestStruct.QuestDescription = QuestDescription;
    QuestStruct.Progress = Progress;

    for (UQuestStep* Step : QuestSteps)
    {
        QuestStruct.QuestSteps.Add(Step->GetQuestStepStruct());
    }

    return QuestStruct;
}

void UQuest::UpdateProgress(UQuestStep* Step)
{
    if (!IsValid(Step))
    {
        if (GEngine)
        {
            GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("[ERROR] QuestStep not found!"));
        }

        UE_LOG(LogTemp, Error, TEXT("[ERROR] QuestStep not found!"));

        return;
    }

    if (Step->StepProgress >= Step->StepProgressTotal)
    {
        this->Progress += 1;
        Step->OnStepProgressUpdated.RemoveDynamic(this, &UQuest::UpdateProgress);
        OnQuestProgressUpdated.Broadcast(this);
    }

    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, FString::Printf(TEXT("Quest progress updated. Progress: %d"), Progress));
    }

    UE_LOG(LogTemp, Display, TEXT("Quest progress updated. Progress: %d"), Progress);

    OnQuestStepProgressUpdated.Broadcast(Step);
}