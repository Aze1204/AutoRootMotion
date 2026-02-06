#include "AutoRMAnimSequenceThumbnailRenderer.h"

#include "Animation/AnimSequence.h"
#include "CanvasTypes.h"
#include "CanvasItem.h"
#include "Engine/Engine.h"

static bool IsRootMotionEnabled(const UAnimSequence* Seq)
{
	return Seq && Seq->bEnableRootMotion;
}

void UAutoRMAnimSequenceThumbnailRenderer::Draw(
	UObject* Object,
	int32 X,
	int32 Y,
	uint32 Width,
	uint32 Height,
	FRenderTarget* Viewport,
	FCanvas* Canvas,
	bool bAdditionalViewFamily
)
{
	Super::Draw(Object, X, Y, Width, Height, Viewport, Canvas, bAdditionalViewFamily);

	const UAnimSequence* Seq = Cast<UAnimSequence>(Object);
	if (!Canvas || !IsRootMotionEnabled(Seq))
	{
		return;
	}
	
	const float Padding   = FMath::Clamp<float>((float)Width * 0.03f, 3.f, 8.f);
	const float BadgeSize = FMath::Clamp<float>((float)Width * 0.40f, 24.f, 56.f);

	const FVector2D Pos(X + (float)Width - BadgeSize - Padding, Y + Padding);
	const FVector2D Size(BadgeSize, BadgeSize);
	
	FCanvasTileItem Bg(Pos, Size, FLinearColor(0.f, 0.f, 0.f, 0.62f));
	Bg.BlendMode = SE_BLEND_Translucent;
	Canvas->DrawItem(Bg);
	
	FCanvasTextItem Txt(
		Pos + FVector2D(BadgeSize * 0.18f, BadgeSize * 0.10f),
		FText::FromString(TEXT("RM")),
		GEngine ? GEngine->GetSmallFont() : nullptr,
		FLinearColor::White
	);
	Txt.EnableShadow(FLinearColor(0.f, 0.f, 0.f, 0.85f));

	const float TextScale = FMath::Clamp<float>(BadgeSize / 28.f, 0.95f, 1.75f);
	Txt.Scale = FVector2D(TextScale, TextScale);

	Canvas->DrawItem(Txt);
}

