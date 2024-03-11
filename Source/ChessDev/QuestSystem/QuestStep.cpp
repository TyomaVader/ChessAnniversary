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

    if (IsValid(StepStruct.StepTrigger))
    {
        this->BindToTrigger(StepStruct.StepTrigger);

        if (GEngine)
        {
            GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, TEXT("QuestStep bound to trigger"));
        }
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
    StepStruct.StepTrigger = StepTrigger;

    return StepStruct;
}

void UQuestStep::BindToTrigger(UTrigger* Trigger)
{
    if (Trigger)
    {
        StepTrigger = Trigger;
        StepTrigger->OnTriggerActivated.AddDynamic(this, &UQuestStep::UpdateProgress);
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