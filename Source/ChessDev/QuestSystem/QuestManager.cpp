#include "QuestManager.h"

void UQuestManager::AddQuest(UQuest* NewQuest)
{
    ActiveQuests.Add(NewQuest);
}

void UQuestManager::RemoveQuest(UQuest* QuestToRemove)
{
    ActiveQuests.Remove(QuestToRemove);
    CompletedQuests.Add(QuestToRemove);
}
