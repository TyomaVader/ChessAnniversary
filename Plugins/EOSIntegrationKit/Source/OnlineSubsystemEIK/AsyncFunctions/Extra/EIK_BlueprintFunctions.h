﻿// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "OnlineSubsystemUtils.h"
#include "OnlineSubsystem.h"
#include "Engine/LocalPlayer.h"
#include "GameFramework/PlayerState.h"
#include "Interfaces/OnlineIdentityInterface.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "Kismet/GameplayStatics.h"
#include "OnlineSubsystemEIK/Subsystem/EIK_Subsystem.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "EIK_BlueprintFunctions.generated.h"

DECLARE_DYNAMIC_DELEGATE_OneParam(FOnResponseFromSanctions, bool, bWasSuccess);

DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnResponseFromEpicForAccessToken, bool, bWasSuccess, const FString&, AccessToken);

UENUM(BlueprintType)
enum class EEOSSanctionType : uint8
{
	IncorrectSanction,
	CompromisedAccount,
	UnfairPunishment,
	AppealForForgiveness,
};

UENUM(BlueprintType)
enum class EEIK_LoginStatus : uint8
{
	/** Player has not logged in or chosen a local profile */
	NotLoggedIn,
	/** Player is using a local profile but is not logged in */
	UsingLocalProfile,
	/** Player has been validated by the platform specific authentication service */
	LoggedIn,
};

UENUM(BlueprintType)
enum ESessionCurrentState
{
	/** An online session has not been created yet */
	NoSession,
	/** An online session is in the process of being created */
	Creating,
	/** Session has been created but the session hasn't started (pre match lobby) */
	Pending,
	/** Session has been asked to start (may take time due to communication with backend) */
	Starting,
	/** The current session has started. Sessions with join in progress disabled are no longer joinable */
	InProgress,
	/** The session is still valid, but the session is no longer being played (post match lobby) */
	Ending,
	/** The session is closed and any stats committed */
	Ended,
	/** The session is being destroyed */
	Destroying
};

USTRUCT(BlueprintType)
struct FEIK_CurrentSessionInfo
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, Category="EOS Integration Kit || Sessions")
	bool bHostingSession;

	UPROPERTY(BlueprintReadWrite, Category="EOS Integration Kit || Sessions")
	bool bPublicJoinable;

	UPROPERTY(BlueprintReadWrite, Category="EOS Integration Kit || Sessions")
	bool bFriendJoinable;

	UPROPERTY(BlueprintReadWrite, Category="EOS Integration Kit || Sessions")
	bool bInviteOnly;

	UPROPERTY(BlueprintReadWrite, Category="EOS Integration Kit || Sessions")
	bool bAllowInvites;

	UPROPERTY(BlueprintReadWrite, Category="EOS Integration Kit || Sessions")
	TArray<FEIKUniqueNetId> RegisteredPlayers;

	UPROPERTY(BlueprintReadWrite, Category="EOS Integration Kit || Sessions")
	FEIKUniqueNetId SessionOwner;

	UPROPERTY(BlueprintReadWrite, Category="EOS Integration Kit || Sessions")
	TEnumAsByte<ESessionCurrentState> SessionState;

	UPROPERTY(BlueprintReadWrite, Category="EOS Integration Kit || Sessions")
	TMap<FString, FEIKAttribute> SessionSettings;

	UPROPERTY(BlueprintReadWrite, Category="EOS Integration Kit || Sessions")
	int32 NumOpenPublicConnections;

	UPROPERTY(BlueprintReadWrite, Category="EOS Integration Kit || Sessions")
	int32 NumOpenPrivateConnections;
	
	UPROPERTY(BlueprintReadWrite, Category="EOS Integration Kit || Sessions")
	FString SessionIdString;

	UPROPERTY(BlueprintReadWrite, Category="EOS Integration Kit || Sessions")
	FString CompleteDebugString;
	
	FEIK_CurrentSessionInfo(): bAllowInvites(false), SessionState(), NumOpenPublicConnections(0),
	                           NumOpenPrivateConnections(0)
	{
		bHostingSession = false;
		bPublicJoinable = false;
		bFriendJoinable = false;
		bInviteOnly = false;
	}

	FEIK_CurrentSessionInfo(FNamedOnlineSession Session)
	{
		CompleteDebugString = Session.SessionInfo->ToDebugString();
		NumOpenPublicConnections = Session.NumOpenPublicConnections;
		NumOpenPrivateConnections = Session.NumOpenPrivateConnections;
		SessionIdString = Session.GetSessionIdStr();
		
		FOnlineSessionSettings LocalSessionSettings = Session.SessionSettings;
		TMap<FName, FOnlineSessionSetting>::TIterator It(LocalSessionSettings.Settings);
		
		TMap<FString, FEIKAttribute> LocalArraySettings;
		while (It)
		{
			const FName& SettingName = It.Key();
			const FOnlineSessionSetting& Setting = It.Value();
			LocalArraySettings.Add(*SettingName.ToString(), Setting.Data);
			++It;
		}
		SessionSettings = LocalArraySettings;
		bHostingSession = Session.bHosting;
		Session.GetJoinability(bPublicJoinable, bFriendJoinable, bInviteOnly, bAllowInvites);
		FEIKUniqueNetId Temp;
		Temp.SetUniqueNetId(Session.OwningUserId);
		SessionOwner = Temp;
		for (auto& Player : Session.RegisteredPlayers)
		{
			FEIKUniqueNetId Temp1;
			Temp1.SetUniqueNetId(Player);
			RegisteredPlayers.Add(Temp1);
		}
		
		switch (Session.SessionState)
		{
		case EOnlineSessionState::NoSession:
			SessionState = ESessionCurrentState::NoSession;
			break;
		case EOnlineSessionState::Creating:
			SessionState = ESessionCurrentState::Creating;
			break;
		case EOnlineSessionState::Pending:
			SessionState = ESessionCurrentState::Pending;
			break;
		case EOnlineSessionState::Starting:
			SessionState = ESessionCurrentState::Starting;
			break;
		case EOnlineSessionState::InProgress:
			SessionState = ESessionCurrentState::InProgress;
			break;
		case EOnlineSessionState::Ending:
			SessionState = ESessionCurrentState::Ending;
			break;
		case EOnlineSessionState::Ended:
			SessionState = ESessionCurrentState::Ended;
			break;
		case EOnlineSessionState::Destroying:
			SessionState = ESessionCurrentState::Destroying;
			break;
		}
	}
};

UCLASS()
class ONLINESUBSYSTEMEIK_API UEIK_BlueprintFunctions : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "EOS Integration Kit || Extra", meta=( WorldContext = "Context" ))
	static FString GetEpicAccountId(UObject* Context);

	UFUNCTION(BlueprintCallable, Category = "EOS Integration Kit || Extra", meta=( WorldContext = "Context" ))
	static FEIK_CurrentSessionInfo GetCurrentSessionInfo(UObject* Context, FName SessionName = "GameSession");

	UFUNCTION(BlueprintCallable, Category = "EOS Integration Kit || Extra", meta=( WorldContext = "Context" ))
	static TArray<FName> GetAllCurrentSessionNames(UObject* Context);
	UFUNCTION(BlueprintCallable, Category = "EOS Integration Kit || Extra", meta=( WorldContext = "Context" ))
	static FString GetProductUserID(UObject* Context);

	UFUNCTION(BlueprintCallable, Category="EOS Integration Kit || Friends")
	static bool ShowFriendsList();

	// This is a C++ method definition for starting lobbies and sessions
	UFUNCTION(BlueprintCallable, DisplayName="Start EIK Session", Category="EOS Integration Kit || Sessions")
	static bool StartSession(FName SessionName = "GameSession");

	// This is a C++ method definition for registering players in lobbies and sessions
	UFUNCTION(BlueprintCallable, DisplayName="Register EIK Player In Session",
		Category="EOS Integration Kit || Sessions")
	static bool RegisterPlayer(FName SessionName = "GameSession", FEIKUniqueNetId PlayerId = FEIKUniqueNetId(),
	                           bool bWasInvited = false);

	// This is a C++ method definition for unregistering players from lobbies and sessions
	UFUNCTION(BlueprintCallable, DisplayName="Unregister EIK Player In Session",
		Category="EOS Integration Kit || Sessions")
	static bool UnRegisterPlayer(FName SessionName = "GameSession", FEIKUniqueNetId PlayerId = FEIKUniqueNetId());

	// This is a C++ method definition for ending lobbies and sessions
	UFUNCTION(BlueprintCallable, DisplayName="End EIK Session", Category="EOS Integration Kit || Sessions")
	static bool EndSession(FName SessionName = "GameSession");

	// This is a C++ method definition for checking if user is in a lobby or session
	UFUNCTION(BlueprintCallable, DisplayName="Is In EIK Session", Category="EOS Integration Kit || Sessions")
	static bool IsInSession(FName SessionName = "GameSession", FEIKUniqueNetId PlayerId = FEIKUniqueNetId());

	// This is a C++ method definition for getting the nickname of a player from an online subsystem.
	// Documentation link: https://betide-studio.gitbook.io/eos-integration-kit/extra-functions/getplayernickname
	UFUNCTION(BlueprintCallable, Category="EOS Integration Kit || Extra")
	static FString GetPlayerNickname(const int32 LocalUserNum);

	// This is a C++ method definition for getting the login status of a player from an online subsystem.
	// Documentation link: https://betide-studio.gitbook.io/eos-integration-kit/extra-functions/getloginstatus
	UFUNCTION(BlueprintCallable, Category="EOS Integration Kit || Extra")
	static EEIK_LoginStatus GetLoginStatus(const int32 LocalUserNum);

	// Generate a session code of the specified length.
	// This function returns a randomly generated alphanumeric session code.
	// The 'CodeLength' parameter determines the length of the generated code (default: 9).
	UFUNCTION(BlueprintPure, Category="EOS Integration Kit || Extra")
	static FString GenerateSessionCode(int32 CodeLength = 9);

	// Check if EOS (Epic Online Services) is active or not.
	// This function returns true if EOS is active, false otherwise.
	UFUNCTION(BlueprintPure, Category="EOS Integration Kit || Extra")
	static bool IsEIKActive();

	// Get the active EOS subsystem name.
	// This function returns the name of the active EOS subsystem as a FName.
	UFUNCTION(BlueprintPure, Category="EOS Integration Kit || Extra")
	static FName GetActiveSubsystem();

	// Get the active platform's login type for EOS subsystem.
	// This function returns the active platform's login type (e.g., Epic, Steam) as an ELoginTypes enum.
	UFUNCTION(BlueprintPure, Category="EOS Integration Kit || Extra")
	static ELoginTypes GetActivePlatformSubsystem();

	// Convert a TArray<uint8> to a FString using Base64 encoding.
	// This is useful for converting binary data to a human-readable string format.
	UFUNCTION(BlueprintPure, Category="EOS Integration Kit || Extra || Conversions")
	static FString ByteArrayToString(const TArray<uint8>& DataToConvert);

	// Convert an FString to a TArray<uint8> using Base64 decoding.
	// This is useful for converting a string back to its original binary data representation.
	UFUNCTION(BlueprintPure, Category="EOS Integration Kit || Extra || Conversions")
	static TArray<uint8> StringToByteArray(const FString& DataToConvert);

	// Convert a TArray<uint8> to a SaveGame object.
	// The TArray<uint8> is deserialized to construct the SaveGame object.
	UFUNCTION(BlueprintPure, Category="EOS Integration Kit || Extra || Conversions")
	static USaveGame* ByteArrayToSaveGameObject(const TArray<uint8>& DataToConvert)
	{
		return UGameplayStatics::LoadGameFromMemory(DataToConvert);
	}

	// Convert a SaveGame object to a TArray<uint8>.
	// The SaveGame object is serialized into a binary data array (TArray<uint8>).
	UFUNCTION(BlueprintPure, Category="EOS Integration Kit || Extra || Conversions")
	static TArray<uint8> SaveGameObjectToByteArray(USaveGame* DataToConvert)
	{
		TArray<uint8> Result;
		UGameplayStatics::SaveGameToMemory(DataToConvert, Result);
		return Result;
	}

	// This is a C++ method definition for getting the User Unique NetID
	// Documentation link: https://betide-studio.gitbook.io/eos-integration-kit/extra-functions/get-useruniqueid
	UFUNCTION(BlueprintPure, DisplayName="Get User Unique NetID", Category="EOS Integration Kit || Extra")
	static FEIKUniqueNetId GetUserUniqueID(const APlayerController* PlayerController, bool& bIsValid);

	UFUNCTION(BlueprintPure, DisplayName="EOS SDK Version", Category="EOS Integration Kit || Extra")
	static FString GetEOSSDKVersion();

	//Get Plugin Version
	UFUNCTION(BlueprintPure, DisplayName="EIK Plugin Version", Category="EOS Integration Kit || Extra")
	static FString GetEIKPluginVersion();

	UFUNCTION(BlueprintCallable, Category="EOS Integration Kit || Extra")
	static bool IsValidSession(FSessionFindStruct Session);

	UFUNCTION(BlueprintCallable, Category="EOS Integration Kit || Extra")
	static bool Initialize_EIK_For_Friends(APlayerController* PlayerController);

	UFUNCTION(BlueprintPure, Category="EOS Integration Kit || Extra")
	static FString GetCurrentPort(AGameModeBase* CurrentGameMode);

	UFUNCTION(BlueprintCallable, Category="EOS Integration Kit || Extra")
	static void MakeSanctionAppeal(FString AccessToken, EEOSSanctionType Reason,
	                               const FOnResponseFromSanctions& OnResponseFromSanctions);

	UFUNCTION(BlueprintCallable, DisplayName="Request EOS Access Token", Category="EOS Integration Kit || Extra")
	static void RequestEOSAccessToken(const FOnResponseFromEpicForAccessToken& Response);
};
