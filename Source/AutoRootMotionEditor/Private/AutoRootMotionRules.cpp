#include "AutoRootMotionRules.h"

#include "AutoRootMotionSettings.h"

bool FAutoRootMotionRules::HasRootMotion(const UAnimSequence* AnimSequence)
{
	if (!AnimSequence) return false;

	static const FName PelvisBoneName(TEXT("pelvis"));
	const int32 PelvisIndex = AnimSequence->GetSkeleton()
		->GetReferenceSkeleton().FindBoneIndex(PelvisBoneName);

	if (PelvisIndex == INDEX_NONE) return false;

	float TotalTime = AnimSequence->GetPlayLength();
	if (TotalTime <= KINDA_SMALL_NUMBER) return false;

	FTransform StartTM, EndTM;
	{
		FAnimExtractContext CtxStart(0.f, false);
		AnimSequence->GetBoneTransform(StartTM, FSkeletonPoseBoneIndex(PelvisIndex), CtxStart, false);
	}
	{
		FAnimExtractContext CtxEnd(TotalTime, false);
		AnimSequence->GetBoneTransform(EndTM, FSkeletonPoseBoneIndex(PelvisIndex), CtxEnd, false);
	}

	FVector DeltaLoc = EndTM.GetLocation() - StartTM.GetLocation();

	const UAutoRootMotionSettings* Settings = GetDefault<UAutoRootMotionSettings>();
	float MovementThreshold = Settings ? Settings->MovementThreshold : 10.0f;

	return DeltaLoc.SizeSquared() > MovementThreshold * MovementThreshold;
}

bool FAutoRootMotionRules::ShouldEnableRootMotion(const UAnimSequence* AnimSequence)
{
	if (!AnimSequence)
	{
		return false;
	}
	
	if (HasRootMotion(AnimSequence))
	{
		return true;
	}

	return false;
}

bool FAutoRootMotionRules::ShouldDisableRootMotion(const UAnimSequence* AnimSequence)
{
	if (!AnimSequence)
	{
		return false;
	}
	
	float Length = AnimSequence->GetPlayLength();
	if (Length < KINDA_SMALL_NUMBER)
	{
		return true;
	}

	if (!HasRootMotion(AnimSequence))
	{
		return true;
	}
	
	return false;
}