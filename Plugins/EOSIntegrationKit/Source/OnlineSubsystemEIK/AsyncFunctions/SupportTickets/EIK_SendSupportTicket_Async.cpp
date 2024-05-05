// Fill out your copyright notice in the Description page of Project Settings.

#include "EIK_SendSupportTicket_Async.h"


#include "EIKSettings.h"
#include "Dom/JsonObject.h"
#include "Runtime/Online/HTTP/Public/Http.h"
#include "Serialization/JsonSerializer.h"
#include "Serialization/JsonWriter.h"


void UEIK_SendSupportTicket_Async::Activate()
{
	SendTicketRequest();
	Super::Activate();
}

UEIK_SendSupportTicket_Async* UEIK_SendSupportTicket_Async::SendEIKTicketRequestAsyncFunction(FSupportTicketData TicketData)
{
	UEIK_SendSupportTicket_Async* UEIK_SendEIKTicketRequest = NewObject < UEIK_SendSupportTicket_Async>();

	UEIK_SendEIKTicketRequest->Var_TicketData = TicketData;

	return UEIK_SendEIKTicketRequest;
}

void UEIK_SendSupportTicket_Async::SendTicketRequest()
{
    TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = FHttpModule::Get().CreateRequest();
    Request->SetURL("https://dev.epicgames.com/portal/api/v1/services/tickets/submit/");
    Request->SetVerb("POST");
    Request->SetHeader("Content-Type", "application/json");

    if (UEIKSettings* EIKSettings = GetMutableDefault<UEIKSettings>())
    {
        if (EIKSettings->ApiKey.IsEmpty())
        {
            // Log an error message
            UE_LOG(LogTemp, Error, TEXT("API key is empty. Cancelling function call."));

            Failure.Broadcast(TEXT("API key is empty."), FSupportTicketResponseData(), 0);
            SetReadyToDestroy();
            MarkAsGarbage();

            // Return to cancel the rest of the function
            return;
        }
        else
        {
            FString APIKey = EIKSettings->ApiKey;
            Request->SetHeader("Authorization", "Token " + FString(APIKey));
        }
    }
    else
    {
        Failure.Broadcast(TEXT("Couldn't retrive your api key from eik settings."), FSupportTicketResponseData(), 1);
        SetReadyToDestroy();
        MarkAsGarbage();
        return;
    }

    // Construct the request body
    TSharedPtr<FJsonObject> RequestObj = MakeShareable(new FJsonObject);

    FString subjectString;
    switch (Var_TicketData.Subject)
    {
    case ESupportTicketSubject::ST_open_question:
        subjectString = "open-question";
        break;
    case ESupportTicketSubject::ST_technical_support:
        subjectString = "technical-support";
        break;
    case ESupportTicketSubject::ST_ban_appeal:
        subjectString = "ban-appeal";
        break;
    default:
        UE_LOG(LogTemp, Warning, TEXT("Invalid subject enum value."));
        subjectString = "open-question";
        break;
    }

    RequestObj->SetStringField("subject", subjectString);
    RequestObj->SetStringField("message", Var_TicketData.Message);
    RequestObj->SetStringField("sender_email", Var_TicketData.SenderEmail);
    RequestObj->SetStringField("sender_name", Var_TicketData.SenderName);
    RequestObj->SetStringField("guid", Var_TicketData.Guid);
    RequestObj->SetStringField("error_code", Var_TicketData.ErrorCode);
    RequestObj->SetStringField("system_os", Var_TicketData.SystemOS);
    RequestObj->SetStringField("system_antimalware", Var_TicketData.SystemAntiMalware);
    RequestObj->SetStringField("system_other", Var_TicketData.SystemOther);

    FString RequestBody;
    TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&RequestBody);
    FJsonSerializer::Serialize(RequestObj.ToSharedRef(), Writer);
    Request->SetContentAsString(RequestBody);

    Request->OnProcessRequestComplete().BindUObject(this, &UEIK_SendSupportTicket_Async::OnResponseReceived);
    Request->ProcessRequest();
}

void UEIK_SendSupportTicket_Async::OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
    if (bWasSuccessful && Response.IsValid())
    {
        // Parse the JSON response
        TSharedPtr<FJsonObject> JsonObject;
        TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());

        if (FJsonSerializer::Deserialize(Reader, JsonObject))
        {
            // Get the 'data' object
            TSharedPtr<FJsonObject> DataObject = JsonObject->GetObjectField("data");

            // Populate the struct
            FSupportTicketResponseData ResponseData;
            ResponseData.prod_name = DataObject->GetStringField("prod_name");
            ResponseData.prod_slug = DataObject->GetStringField("prod_slug");
            ResponseData.guid = DataObject->GetStringField("guid");
            ResponseData.sender_name = DataObject->GetStringField("sender_name");
            ResponseData.sender_email = DataObject->GetStringField("sender_email");
            ResponseData.subject = DataObject->GetStringField("subject");
            ResponseData.message = DataObject->GetStringField("message");
            ResponseData.error_code = DataObject->GetStringField("error_code");
            ResponseData.system_os = DataObject->GetStringField("system_os");
            ResponseData.system_antimalware = DataObject->GetStringField("system_antimalware");
            ResponseData.system_other = DataObject->GetStringField("system_other");
            ResponseData.timestamp = DataObject->GetStringField("timestamp");

            // Broadcast the success delegate
            Success.Broadcast(Response->GetContentAsString(), ResponseData, Response->GetResponseCode());
            SetReadyToDestroy();
            MarkAsGarbage();
        }
    }
    else
    {
        Failure.Broadcast(Response->GetContentAsString(), FSupportTicketResponseData(), Response->GetResponseCode());
        SetReadyToDestroy();
        MarkAsGarbage();
    }
}

