#include "ReadWriteJson.h"
#include "ReadWriteFile.h"
#include "Json.h"
#include "JsonUtilities.h"
#include "Serialization/JsonSerializer.h"

TSharedPtr<FJsonObject> UReadWriteJson::ReadJson(FString JsonFilePath, bool& bOutSuccess, FString& OutInfoMsg)
{
    //Try to read file
    FString JsonString = UReadWriteFile::ReadStringFromFile(JsonFilePath, bOutSuccess, OutInfoMsg);
    if (!bOutSuccess)
    {
        return nullptr;
    }

    TSharedPtr<FJsonObject> RetJsonObject;

    //Try to convert string to json object
    if(!FJsonSerializer::Deserialize(TJsonReaderFactory<>::Create(JsonString), RetJsonObject))
    {
        bOutSuccess = false;
        OutInfoMsg = FString::Printf(TEXT("Failed to convert string to json object"));
        return nullptr;
    }

    bOutSuccess = true;
    OutInfoMsg = FString::Printf(TEXT("Json object created successfully"));
    return RetJsonObject;
}

void UReadWriteJson::WriteJson(FString JsonFilePath, TSharedPtr<FJsonObject>& JsonObject, bool& bOutSuccess, FString& OutInfoMsg)
{
    FString JsonString;

    //Try to convert json object to string
    if(!FJsonSerializer::Serialize(JsonObject.ToSharedRef(), TJsonWriterFactory<TCHAR>::Create(&JsonString, 0)))
    {
        bOutSuccess = false;
        OutInfoMsg = FString::Printf(TEXT("Failed to convert json object to string"));
        return;
    }

    //Try to write string to file
    UReadWriteFile::WriteStringToFile(JsonFilePath, JsonString, bOutSuccess, OutInfoMsg);
    if(!bOutSuccess)
    {
        return;
    }
    
    bOutSuccess = true;
    OutInfoMsg = FString::Printf(TEXT("Json object written successfully"));
}

FQuestStruct UReadWriteJson::ReadStructFromJson(FString JsonFilePath, FQuestStruct& Struct, bool& bOutSuccess, FString& OutInfoMsg)
{
    //Try to read generic json object from file
    TSharedPtr<FJsonObject> JsonObject = ReadJson(JsonFilePath, bOutSuccess, OutInfoMsg);
    if(!bOutSuccess)
    {
        return FQuestStruct();
    }

    FQuestStruct RetStruct;

    //Try to convert generic json object to the desired struct
    if(!FJsonObjectConverter::JsonObjectToUStruct<FQuestStruct>(JsonObject.ToSharedRef(), &RetStruct))
    {
        bOutSuccess = false;
        OutInfoMsg = FString::Printf(TEXT("Failed to convert json object to struct"));
        return FQuestStruct();
    }

    bOutSuccess = true;
    OutInfoMsg = FString::Printf(TEXT("Struct created successfully"));
    return RetStruct;
}


void UReadWriteJson::WriteStructToJson(FString JsonFilePath, const FQuestStruct& Struct, bool& bOutSuccess, FString& OutInfoMsg)
{
    //Try to convert struct to generic json object
    TSharedPtr<FJsonObject> JsonObject = FJsonObjectConverter::UStructToJsonObject(Struct);

    if(!JsonObject.IsValid())
    {
        bOutSuccess = false;
        OutInfoMsg = FString::Printf(TEXT("Failed to convert struct to json object"));
        return;
    }
    
    //Try to write generic json object to file
    WriteJson(JsonFilePath, JsonObject, bOutSuccess, OutInfoMsg);
}

