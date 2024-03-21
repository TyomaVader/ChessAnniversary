#include "Kismet/BlueprintFunctionLibrary.h"
#include "QuestStruct.h"
#include "ReadWriteJson.generated.h"

class FJsonObject;

UCLASS()
class UReadWriteJson : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:

    UFUNCTION(BlueprintCallable, Category = "File IO")
    static FQuestStruct ReadStructFromJson(FString JsonFilePath, FQuestStruct& Struct, bool& bOutSuccess);

    UFUNCTION(BlueprintCallable, Category = "File IO")
    static void WriteStructToJson(FString JsonFilePath, const FQuestStruct& Struct, bool& bOutSuccess);

    static TSharedPtr<FJsonObject> ReadJson(FString JsonFilePath, bool& bOutSuccess);

    static void WriteJson(FString JsonFilePath, TSharedPtr<FJsonObject>& JsonObject, bool& bOutSuccess);
};
