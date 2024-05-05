﻿// Copyright (c) 2023 Betide Studio. All Rights Reserved.


#include "EIK_AcceptFriendInvite_AsyncFunction.h"
#include "OnlineSubsystemUtils.h"

UEIK_AcceptFriendInvite_AsyncFunction* UEIK_AcceptFriendInvite_AsyncFunction::AcceptFriendInvite(
	FEIKUniqueNetId FriendId)
{
	UEIK_AcceptFriendInvite_AsyncFunction* UEIK_AcceptFriendInviteObject= NewObject<UEIK_AcceptFriendInvite_AsyncFunction>();
	UEIK_AcceptFriendInviteObject->Var_FriendId = FriendId;
	return UEIK_AcceptFriendInviteObject;
}

void UEIK_AcceptFriendInvite_AsyncFunction::OnAcceptComplete(int32 LocalUserNum, bool bWasSuccessful,
	const FUniqueNetId& FriendId, const FString& ListName, const FString& ErrorStr)
{
	if(bWasSuccessful)
	{
		OnSuccess.Broadcast("");
		SetReadyToDestroy();
		MarkAsGarbage();
	}
	else
	{
		OnFailure.Broadcast(ErrorStr);
		SetReadyToDestroy();
		MarkAsGarbage();
	}
}

void UEIK_AcceptFriendInvite_AsyncFunction::Activate()
{
	Super::Activate();
	if(const IOnlineSubsystem *SubsystemRef = Online::GetSubsystem(GetWorld()))
	{
		if(const IOnlineFriendsPtr FriendsInterface = SubsystemRef->GetFriendsInterface())
		{
			FriendsInterface->AcceptInvite(0,*Var_FriendId.GetUniqueNetId(),"",FOnAcceptInviteComplete::CreateUObject(this, &UEIK_AcceptFriendInvite_AsyncFunction::OnAcceptComplete));
			SetReadyToDestroy();
			MarkAsGarbage();
		}
		else
		{
			// Failed to get Friends Interface
			SetReadyToDestroy();
			MarkAsGarbage();
			OnFailure.Broadcast("Failed to get Friends Interface");
		}
	}
	else
	{
		// Failed to get Subsystem
		SetReadyToDestroy();
		MarkAsGarbage();
		OnFailure.Broadcast("Failed to get Subsystem");
	}
}
