#include "QuestStep.h"

UQuestStep::UQuestStep()
{
    StepDescription = "New Quest Step";
    StepProgress = 0;
}

void UQuestStep::Init(const FQuestStepStruct& StepStruct, const TArray<UTrigger*>& Triggers)
{
    StepDescription = StepStruct.StepDescription;
    StepProgress = StepStruct.StepProgress;
    StepTriggerId = StepStruct.StepTriggerId;

    if (IsValid(Triggers[StepTriggerId]))
    {
        this->BindToTrigger(Triggers[StepTriggerId]);
    } else
    {
        if (GEngine)
        {
            GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("[ERROR] Cannot initialize QuestStep. Trigger is NOT valid!"));
        }
    }
}

FQuestStepStruct UQuestStep::GetQuestStepStruct() const
{
    FQuestStepStruct StepStruct;
    StepStruct.StepDescription = StepDescription;
    StepStruct.StepProgress = StepProgress;
    StepStruct.StepProgressTotal = StepProgressTotal;
    StepStruct.StepTriggerId = StepTriggerId;

    return StepStruct;
}

void UQuestStep::BindToTrigger(UTrigger* Trigger)
{
    if (Trigger)
    {
        Trigger->OnTriggerActivated.AddDynamic(this, &UQuestStep::UpdateProgress);
    } else
    {
        if (GEngine)
        {
            GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("[ERROR] QuestStep could not bind to trigger. Trigger is NOT valid!"));
        }
    }
}

void UQuestStep::UpdateProgress()
{
    // TODO: Implement this function
    StepProgress += 1;

    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, FString::Printf(TEXT("QuestStep progress updated. Progress: %d"), StepProgress));
    }
}