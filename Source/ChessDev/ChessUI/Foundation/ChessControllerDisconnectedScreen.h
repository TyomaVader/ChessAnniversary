// Copyright (c) 2024 Artsiom Chmutau

#pragma once

#include "CommonActivatableWidget.h"

#include "ChessControllerDisconnectedScreen.generated.h"

class UHorizontalBox;
class UObject;

UCLASS(Abstract, BlueprintType, Blueprintable)
class UChessControllerDisconnectedScreen : public UCommonActivatableWidget
{
	GENERATED_BODY()

protected:
	void NativeOnActivated() override;

private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UHorizontalBox> HBox_SwitchUser;
};