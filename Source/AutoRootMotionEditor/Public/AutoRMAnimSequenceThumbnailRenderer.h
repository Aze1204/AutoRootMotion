#pragma once

#include "ThumbnailRendering/AnimSequenceThumbnailRenderer.h"
#include "AutoRMAnimSequenceThumbnailRenderer.generated.h"

UCLASS(Config=Editor)
class UAutoRMAnimSequenceThumbnailRenderer : public UAnimSequenceThumbnailRenderer
{
	GENERATED_BODY()

public:
	virtual void Draw(
		UObject* Object,
		int32 X,
		int32 Y,
		uint32 Width,
		uint32 Height,
		FRenderTarget* Viewport,
		FCanvas* Canvas,
		bool bAdditionalViewFamily
	) override;
};
