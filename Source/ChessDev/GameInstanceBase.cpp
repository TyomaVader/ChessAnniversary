// Copyright (c) 2024 Artsiom Chmutau

#include "GameInstanceBase.h"

#include "QuestSystem/QuestSave.h"

void UGameInstanceBase::Init()
{
    Super::Init();

    if (UGameplayStatics::DoesSaveGameExist(UQuestSave::SlotName, 0))
    {
        QuestSave = Cast<UQuestSave>(UGameplayStatics::LoadGameFromSlot(UQuestSave::SlotName, 0));
    }
    else
    {
        QuestSave = Cast<UQuestSave>(UGameplayStatics::CreateSaveGameObject(UQuestSave::StaticClass()));
    }
}
