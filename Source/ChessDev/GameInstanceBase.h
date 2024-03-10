// Copyright (c) 2024 Artsiom Chmutau

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "GameInstanceBase.generated.h"


class UQuestSave;


/**
 * 
 */
UCLASS()
class CHESSDEV_API UGameInstanceBase : public UGameInstance
{
    GENERATED_BODY()

public:
    virtual void Init() override;

    UPROPERTY(VisibleAnywhere)
    UQuestSave* QuestSave;
};
