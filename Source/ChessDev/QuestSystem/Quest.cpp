// Copyright (c) 2024 Artsiom Chmutau

#include "Quest.h"

UQuest::UQuest()
{
    QuestName = "New Quest";
    QuestDescription = "New Quest Description";
    Progress = 0;
}

void UQuest::Init(const FQuestStruct& QuestStruct)
{
    QuestName = QuestStruct.QuestName;
    QuestDescription = QuestStruct.QuestDescription;
    Progress = QuestStruct.Progress;

    for (const FQuestStepStruct& Step : QuestStruct.QuestSteps)
    {
        UQuestStep* questStep = NewObject<UQuestStep>();
        questStep->Init(Step);

        QuestSteps.Add(questStep);
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