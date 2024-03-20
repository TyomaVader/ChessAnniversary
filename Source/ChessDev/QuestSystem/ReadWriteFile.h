#include "Kismet/BlueprintFunctionLibrary.h"
#include "ReadWriteFile.generated.h"

UCLASS()
class UReadWriteFile : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "File IO")
    static FString ReadStringFromFile(FString FileName, bool& bOutSuccess, FString& OutInfoMsg);

    UFUNCTION(BlueprintCallable, Category = "File IO")
    static void WriteStringToFile(FString FileName, FString StringToWrite, bool& bOutSuccess, FString& OutInfoMsg);
};

