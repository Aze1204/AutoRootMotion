#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimSequence.h"

class FAutoRootMotionRules
{
public:
	static bool HasRootMotion(const UAnimSequence* AnimSequence);
	
	static bool ShouldEnableRootMotion(const UAnimSequence* AnimSequence);
	
	static bool ShouldDisableRootMotion(const UAnimSequence* AnimSequence);
};
