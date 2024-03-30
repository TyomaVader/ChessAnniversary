#include "ReadWriteJson.h"
#include "ReadWriteFile.h"
#include "Json.h"
#include "JsonUtilities.h"
#include "Serialization/JsonSerializer.h"

TSharedPtr<FJsonObject> UReadWriteJson::ReadJson(FString JsonFilePath, bool& bOutSuccess)
{
    //Try to read file
    FString JsonString = UReadWriteFile::ReadStringFromFile(JsonFilePath, bOutSuccess);
    if (!bOutSuccess)
    {
        return nullptr;
    }

    TSharedPtr<FJsonObject> RetJsonObject;

    //Try to convert string to json object
    if (!FJsonSerializer::Deserialize(TJsonReaderFactory<>::Create(JsonString), RetJsonObject))
    {
        bOutSuccess = false;
        UE_LOG(LogTemp, Error, TEXT("[ERROR] Failed to convert string to json object."));
        return nullptr;
    }

    bOutSuccess = true;
    UE_LOG(LogTemp, Display, TEXT("[SUCCESS] Json object created successfully."));
    return RetJsonObject;
}

FString UReadWriteJson::WriteJson(FString JsonFilePath, TSharedPtr<FJsonObject>& JsonObject, bool& bOutSuccess)
{
    FString JsonString;

    //Try to convert json object to string
    if(!FJsonSerializer::Serialize(JsonObject.ToSharedRef(), TJsonWriterFactory<TCHAR>::Create(&JsonString, 0)))
    {
        bOutSuccess = false;
        UE_LOG(LogTemp, Error, TEXT("[ERROR] Failed to convert json object to string."));
        return "";
    }

    //Try to write string to file
    UReadWriteFile::WriteStringToFile(JsonFilePath, JsonString, bOutSuccess);
    if(!bOutSuccess)
    {
        return "";
    }
    
    bOutSuccess = true;
    UE_LOG(LogTemp, Display, TEXT("[SUCCESS] Json object written successfully."));

    return JsonString;
}

FQuestStruct UReadWriteJson::ReadStructFromJson(FString JsonFilePath, FQuestStruct& Struct, bool& bOutSuccess)
{
    //Try to read generic json object from file
    TSharedPtr<FJsonObject> JsonObject = ReadJson(JsonFilePath, bOutSuccess);
    if(!bOutSuccess)
    {
        return FQuestStruct();
    }

    FQuestStruct RetStruct;

    //Try to convert generic json object to the desired struct
    if(!FJsonObjectConverter::JsonObjectToUStruct<FQuestStruct>(JsonObject.ToSharedRef(), &RetStruct))
    {
        bOutSuccess = false;
        UE_LOG(LogTemp, Error, TEXT("[ERROR] Failed to convert json object to struct."));
        return FQuestStruct();
    }

    bOutSuccess = true;
    UE_LOG(LogTemp, Display, TEXT("[SUCCESS] Struct created successfully."));
    return RetStruct;
}


void UReadWriteJson::WriteStructToJson(FString JsonFilePath, const FQuestStruct& Struct, bool& bOutSuccess)
{
    //Try to convert struct to generic json object
    TSharedPtr<FJsonObject> JsonObject = FJsonObjectConverter::UStructToJsonObject(Struct);

    if(!JsonObject.IsValid())
    {
        bOutSuccess = false;
        UE_LOG(LogTemp, Error, TEXT("[ERROR] Failed to convert struct to json object."));
        return;
    }
    
    //Try to write generic json object to file
    WriteJson(JsonFilePath, JsonObject, bOutSuccess);
}

