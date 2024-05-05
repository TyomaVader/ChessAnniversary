﻿// Copyright Epic Games, Inc. All Rights Reserved.


#include "EIK_DestroySession_AsyncFunction.h"
#include "OnlineSubsystemUtils.h"
#include "Kismet/GameplayStatics.h"

UEIK_DestroySession_AsyncFunction* UEIK_DestroySession_AsyncFunction::DestroyEIKSessions(
	FName SessionName,
	FEIKUniqueNetId PlayerId)
{
	UEIK_DestroySession_AsyncFunction* Ueik_DestroySessionObject = NewObject<UEIK_DestroySession_AsyncFunction>();
	Ueik_DestroySessionObject->Var_PlayerId = PlayerId;
	Ueik_DestroySessionObject->Var_SessionName = SessionName;
	return Ueik_DestroySessionObject;
}

void UEIK_DestroySession_AsyncFunction::Activate()
{
	DestroySession();
	Super::Activate();
}

void UEIK_DestroySession_AsyncFunction::DestroySession()
{
	if(const IOnlineSubsystem *SubsystemRef = IOnlineSubsystem::Get())
	{
		if(const IOnlineSessionPtr SessionPtrRef = SubsystemRef->GetSessionInterface())
		{
			SessionPtrRef->OnDestroySessionCompleteDelegates.AddUObject(this,&UEIK_DestroySession_AsyncFunction::OnDestroySessionCompleted);
			if(Var_PlayerId.IsValid())
			{
				SessionPtrRef->RemovePlayerFromSession(0,Var_SessionName,Var_PlayerId.UniqueNetId.ToSharedRef().Get());
				SessionPtrRef->UnregisterPlayer(Var_SessionName,Var_PlayerId.UniqueNetId.ToSharedRef().Get());
			}
			SessionPtrRef->DestroySession(Var_SessionName);
		}
		else
		{
			if(bDelegateCalled)
			{
				return;
			}
			OnFail.Broadcast();
			SetReadyToDestroy();
			MarkAsGarbage();
			bDelegateCalled = true;
		}
	}
	else
	{
		if(bDelegateCalled)
		{
			return;
		}
		OnFail.Broadcast();
		SetReadyToDestroy();
MarkAsGarbage();
		bDelegateCalled = true;
	}
}

void UEIK_DestroySession_AsyncFunction::OnDestroySessionCompleted(FName SessionName, bool bWasSuccess)
{
	if(bDelegateCalled)
	{
		return;
	}
	bDelegateCalled = true;
	if(bWasSuccess)
	{
		OnSuccess.Broadcast();
	}
	else
	{
		OnFail.Broadcast();
	}
	SetReadyToDestroy();
MarkAsGarbage();
}
