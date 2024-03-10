#include "QuestStep.h"

UQuestStep::UQuestStep()
{
    StepDescription = "New Quest Step";
    StepProgress = 0;
}

void UQuestStep::Init(const FQuestStepStruct& StepStruct)
{
    StepDescription = StepStruct.StepDescription;
    StepProgress = StepStruct.StepProgress;

    if (StepStruct.StepTrigger)
    {
        this->BindToTrigger(StepStruct.StepTrigger);
    }
}

FQuestStepStruct UQuestStep::GetQuestStepStruct() const
{
    FQuestStepStruct StepStruct;
    StepStruct.StepDescription = StepDescription;
    StepStruct.StepProgress = StepProgress;
    StepStruct.StepTrigger = StepTrigger;

    return StepStruct;
}

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