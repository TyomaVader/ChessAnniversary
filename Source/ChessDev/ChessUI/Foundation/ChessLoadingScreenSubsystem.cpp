// Copyright (c) 2024 Artsiom Chmutau

#include "ChessLoadingScreenSubsystem.h"

#include "Blueprint/UserWidget.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(ChessLoadingScreenSubsystem)

class UUserWidget;

//////////////////////////////////////////////////////////////////////
// UChessLoadingScreenSubsystem

UChessLoadingScreenSubsystem::UChessLoadingScreenSubsystem() {}

void UChessLoadingScreenSubsystem::SetLoadingScreenContentWidget(TSubclassOf<UUserWidget> NewWidgetClass)
{
	if (LoadingScreenWidgetClass != NewWidgetClass)
	{
		LoadingScreenWidgetClass = NewWidgetClass;

		OnLoadingScreenWidgetChanged.Broadcast(LoadingScreenWidgetClass);
	}
}

TSubclassOf<UUserWidget> UChessLoadingScreenSubsystem::GetLoadingScreenContentWidget() const
{
	return LoadingScreenWidgetClass;
}