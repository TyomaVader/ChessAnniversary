#include "ReadWriteFile.h"

FString UReadWriteFile::ReadStringFromFile(FString FileName, bool& bOutSuccess)
{
    //Check if file exists
    if (!FPlatformFileManager::Get().GetPlatformFile().FileExists(*FileName))
    {
        bOutSuccess = false;
        UE_LOG(LogTemp, Error, TEXT("File does not exist"));
        return "";
    }

    FString RetString = "";

    //Try to read the file. Output goes to RetString
    if(!FFileHelper::LoadFileToString(RetString, *FileName))
    {
        bOutSuccess = false;
        UE_LOG(LogTemp, Error, TEXT("Failed to read file. Maybe not file"));
        return "";
    }

    bOutSuccess = true;
    UE_LOG(LogTemp, Display, TEXT("File read successfully"));
    return RetString;

}

void UReadWriteFile::WriteStringToFile(FString FileName, FString StringToWrite, bool& bOutSuccess)
{
    //Try to write string to file
    if(!FFileHelper::SaveStringToFile(StringToWrite, *FileName))
    {
        bOutSuccess = false;
        UE_LOG(LogTemp, Error, TEXT("Failed to write to file"));
        return;
    }

    bOutSuccess = true;
    UE_LOG(LogTemp, Display, TEXT("File written successfully"));
}