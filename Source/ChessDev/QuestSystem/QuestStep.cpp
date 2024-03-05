#include "QuestStep.h"

void UQuestStep::BindToTrigger(UTrigger* Trigger)
{
    if (Trigger)
    {
        StepTrigger = Trigger;
        StepTrigger->OnTriggerActivated.AddDynamic(this, &UQuestStep::UpdateProgress);
    }
}

void UQuestStep::UpdateProgress()
{
    // TODO: Implement this function
    StepProgress += 1;
}