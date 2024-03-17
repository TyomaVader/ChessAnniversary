// Copyright (c) 2024 Artsiom Chmutau

#pragma once

#include "CommonTabListWidgetBase.h"

#include "ChessTabListWidgetBase.generated.h"

class UCommonButtonBase;
class UCommonUserWidget;
class UObject;
class UWidget;
struct FFrame;

USTRUCT(BlueprintType)
struct FChessTabDescriptor
{
    GENERATED_BODY()

public:
    FChessTabDescriptor() : bHidden(false), CreatedTabContentWidget(nullptr) {}

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    FName TabId;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText TabText;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FSlateBrush IconBrush;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    bool bHidden;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    TSubclassOf<UCommonButtonBase> TabButtonType;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UCommonUserWidget> TabContentType;

    UPROPERTY(Transient)
	TObjectPtr<UWidget> CreatedTabContentWidget;
};

UINTERFACE(BlueprintType)
class UChessTabButtonInterface : public UInterface
{
    GENERATED_BODY()
};

class IChessTabButtonInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, Category = "Tab Button")
	void SetTabLabelInfo(const FChessTabDescriptor& TabDescriptor);
};

UCLASS(Blueprintable, BlueprintType, Abstract, meta = (DisableNativeTick))
class CHESSDEV_API UChessTabListWidgetBase : public UCommonTabListWidgetBase
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Tab List")
	bool GetPreregisteredTabInfo(const FName TabNameId, FChessTabDescriptor& OutTabInfo);

	/** Helper method to get at all the preregistered tab infos */
	const TArray<FChessTabDescriptor>& GetAllPreregisteredTabInfos() { return PreregisteredTabInfoArray; }

	// Toggles whether or not a specified tab is hidden, can only be called before the switcher is associated
	UFUNCTION(BlueprintCallable, Category = "Tab List")
	void SetTabHiddenState(FName TabNameId, bool bHidden);

	UFUNCTION(BlueprintCallable, Category = "Tab List")
	bool RegisterDynamicTab(const FChessTabDescriptor& TabDescriptor);

	UFUNCTION(BlueprintCallable, Category = "Tab List")
	bool IsFirstTabActive() const;

	UFUNCTION(BlueprintCallable, Category = "Tab List")
	bool IsLastTabActive() const;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Tab List")
	bool IsTabVisible(FName TabId);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Tab List")
	int32 GetVisibleTabCount();

	/** Delegate broadcast when a new tab is created. Allows hook ups after creation. */
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnTabContentCreated, FName, TabId, UCommonUserWidget*, TabWidget);
	DECLARE_EVENT_TwoParams(UChessTabListWidgetBase, FOnTabContentCreatedNative, FName /* TabId */, UCommonUserWidget* /* TabWidget */);

	/** Broadcasts when a new tab is created. */
	UPROPERTY(BlueprintAssignable, Category = "Tab List")
	FOnTabContentCreated OnTabContentCreated;
	FOnTabContentCreatedNative OnTabContentCreatedNative;

protected:
	// UUserWidget interface
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	// End UUserWidget

	virtual void HandlePreLinkedSwitcherChanged() override;
	virtual void HandlePostLinkedSwitcherChanged() override;

	virtual void HandleTabCreation_Implementation(FName TabId, UCommonButtonBase* TabButton) override;

private:
	void SetupTabs();

	UPROPERTY(EditAnywhere, meta=(TitleProperty="TabId"))
	TArray<FChessTabDescriptor> PreregisteredTabInfoArray;
	
	/**
	 * Stores label info for tabs that have been registered at runtime but not yet created. 
	 * Elements are removed once they are created.
	 */
	UPROPERTY()
	TMap<FName, FChessTabDescriptor> PendingTabLabelInfoMap;
};
