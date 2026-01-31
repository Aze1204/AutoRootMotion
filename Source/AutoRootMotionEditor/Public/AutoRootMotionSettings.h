#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "AutoRootMotionSettings.generated.h"

UCLASS(config=EditorPerProjectUserSettings, defaultconfig)
class AUTOROOTMOTION_API UAutoRootMotionSettings : public UObject
{
	GENERATED_BODY()
public:
	UAutoRootMotionSettings()
		: EnablePostImport(true)
		, MovementThreshold(10.0f)
	{}
public:
	UPROPERTY(EditAnywhere, Config, Category="AutoRootMotion")
	bool EnablePostImport;
	
	UPROPERTY(EditAnywhere, Config, Category="AutoRootMotion", meta=(ClampMin="0.0"))
	float MovementThreshold;
	
};
