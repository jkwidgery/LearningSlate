#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "DeveloperProfileAsset.generated.h"

UENUM(BlueprintType)
enum class EProfileTheme : uint8
{
	TurtleRock UMETA(DisplayName = "Turtle Rock"),
	Pastel     UMETA(DisplayName = "Pastel"),
};

UENUM()
enum class ESkillType
{
	Hard,
	Soft,
	Count UMETA(Hidden)
};

USTRUCT(BlueprintType)
struct FDeveloperContactInfo
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString Email;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString LinkedIn;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString Phone;
};

USTRUCT(BlueprintType)
struct FDeveloperSkill
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString SkillName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ClampMin = "0", ClampMax = "100"))
	int32 Proficiency;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ESkillType SkillType;
};

UCLASS()
class DEVELOPERPROFILE_API UDeveloperProfileAsset : public UObject
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString DisplayName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString RoleTitle;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (MultiLine = "true"))
	FString Bio;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSoftObjectPtr<UTexture2D> Portrait;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FDeveloperContactInfo ContactInfo;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FDeveloperSkill> Skills;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Appearance")
	EProfileTheme Theme = EProfileTheme::TurtleRock;
};