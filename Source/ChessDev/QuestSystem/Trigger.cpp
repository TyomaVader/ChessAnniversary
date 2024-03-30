#include "Trigger.h"

void UTrigger::ActivateTrigger()
{
    OnTriggerActivated.Broadcast();
}