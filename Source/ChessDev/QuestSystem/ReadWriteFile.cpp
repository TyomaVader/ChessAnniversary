#include "ReadWriteFile.h"

FString UReadWriteFile::ReadStringFromFile(FString FileName, bool& bOutSuccess, FString& OutInfoMsg)
{
    //Check if file exists
    if (!FPlatformFileManager::Get().GetPlatformFile().FileExists(*FileName))
    {
        bOutSuccess = false;
        OutInfoMsg = FString::Printf(TEXT("File does not exist"));
        return "";
    }

    FString RetString = "";

    //Try to read the file. Output goes to RetString
    if(!FFileHelper::LoadFileToString(RetString, *FileName))
    {
        bOutSuccess = false;
        OutInfoMsg = FString::Printf(TEXT("Failed to read file. Maybe not file"));
        return "";
    }

    bOutSuccess = true;
    OutInfoMsg = FString::Printf(TEXT("File read successfully"));
    return RetString;

}

void UReadWriteFile::WriteStringToFile(FString FileName, FString StringToWrite, bool& bOutSuccess, FString& OutInfoMsg)
{
    //Try to write string to file
    if(!FFileHelper::SaveStringToFile(StringToWrite, *FileName))
    {
        bOutSuccess = false;
        OutInfoMsg = FString::Printf(TEXT("Failed to write to file"));
        return;
    }

    bOutSuccess = true;
    OutInfoMsg = FString::Printf(TEXT("File written successfully"));
}