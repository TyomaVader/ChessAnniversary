#include "ReadWriteFile.h"

FString UReadWriteFile::ReadStringFromFile(FString FileName, bool& bOutSuccess)
{
    //Check if file exists
    if (!FPlatformFileManager::Get().GetPlatformFile().FileExists(*FileName))
    {
        bOutSuccess = false;
        UE_LOG(LogTemp, Error, TEXT("[ERROR] File does not exist."));
        return "";
    }

    FString RetString = "";

    //Try to read the file. Output goes to RetString
    if(!FFileHelper::LoadFileToString(RetString, *FileName))
    {
        bOutSuccess = false;
        UE_LOG(LogTemp, Error, TEXT("[ERROR] Failed to read file."));
        return "";
    }

    bOutSuccess = true;
    UE_LOG(LogTemp, Display, TEXT("[SUCCESS] File read successfully."));
    return RetString;
}

void UReadWriteFile::WriteStringToFile(FString FileName, FString StringToWrite, bool& bOutSuccess)
{
    //Try to write string to file
    if(!FFileHelper::SaveStringToFile(StringToWrite, *FileName))
    {
        bOutSuccess = false;
        UE_LOG(LogTemp, Error, TEXT("[ERROR] Failed to write to file."));
        return;
    }

    bOutSuccess = true;
    UE_LOG(LogTemp, Display, TEXT("[SUCCESS] File written successfully."));
}