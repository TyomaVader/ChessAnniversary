// Copyright (c) 2024 Artsiom Chmutau

#include "Quest.h"

void UQuest::AddQuestStep(UQuestStep* NewStep)
{
    QuestSteps.Add(NewStep);
}