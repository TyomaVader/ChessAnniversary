// Copyright (c) 2024 Artsiom Chmutau

#include "QuestSave.h"

const FString UQuestSave::SlotName = FString("QuestSave");

void UQuestSave::SaveQuestManager(TArray<FQuestStruct> QuestsToSave)
{
    PlayerQuests = QuestsToSave;

    Save();
}

void UQuestSave::LoadQuestManager(UQuestManager* QuestManagerRef)
{
    for (FQuestStruct PlayerQuest : PlayerQuests)
        QuestManagerRef->AddQuest(PlayerQuest);

}

void UQuestSave::Save()
{
    UGameplayStatics::SaveGameToSlot(this, SlotName, 0);
}
