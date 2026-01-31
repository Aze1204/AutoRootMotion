#include "AutoRootMotionEditorUI.h"

#include "AutoRootMotionModule.h"
#include "AutoRootMotionRules.h"
#include "ContentBrowserMenuContexts.h"
#include "Animation/AnimSequence.h"
#include "ToolMenuSection.h"

#include "Framework/Notifications/NotificationManager.h"
#include "Widgets/Notifications/SNotificationList.h"
#include "Misc/MessageDialog.h"
#include "Logging/LogMacros.h"

DEFINE_LOG_CATEGORY_STATIC(LogAutoRootMotion, Log, All);

#define LOCTEXT_NAMESPACE "AutoRootMotion"
bool FAutoRootMotionEditorUI::HasOnlyAnimSequencesSelected(FToolMenuSection& InSection)
{
	const UContentBrowserAssetContextMenuContext* Context =
		InSection.FindContext<UContentBrowserAssetContextMenuContext>();

	if (!Context || Context->SelectedAssets.Num() == 0)
	{
		return false;
	}

	for (const FAssetData& AssetData : Context->SelectedAssets)
	{
		if (AssetData.GetClass() != UAnimSequence::StaticClass())
		{
			return false;
		}
	}
	return true;
}

void FAutoRootMotionEditorUI::Notify(const FString& Msg, bool bPopupDialog)
{
	UE_LOG(LogAutoRootMotion, Log, TEXT("%s"), *Msg);

	FNotificationInfo Info(FText::FromString(Msg));
	Info.ExpireDuration = 2.0f;
	FSlateNotificationManager::Get().AddNotification(Info);

	if (bPopupDialog)
	{
		FMessageDialog::Open(EAppMsgType::Ok, FText::FromString(Msg));
	}
}

int32 FAutoRootMotionEditorUI::CountSelectedAnimSequences(const FToolMenuContext& InContext)
{
	const UContentBrowserAssetContextMenuContext* Context =
		InContext.FindContext<UContentBrowserAssetContextMenuContext>();

	if (!Context)
	{
		return 0;
	}

	int32 Count = 0;
	for (const FAssetData& AssetData : Context->SelectedAssets)
	{
		if (AssetData.GetClass() == UAnimSequence::StaticClass())
		{
			++Count;
		}
	}
	return Count;
}

void FAutoRootMotionEditorUI::Execute_Auto(const FToolMenuContext& InContext)
{
	const int32 Count = CountSelectedAnimSequences(InContext);
	if (Count == 0)
	{
		Notify(TEXT("No AnimSequences selected for Auto."), true);
		return;
	}

	Notify(FString::Printf(TEXT("[AutoRootMotion] Auto clicked. Selected AnimSequences: %d"), Count));
	
	const UContentBrowserAssetContextMenuContext* Context =
		InContext.FindContext<UContentBrowserAssetContextMenuContext>();

	if (!Context)
	{
		return;
	}

	for (const FAssetData& AssetData : Context->SelectedAssets)
	{
		if (AssetData.GetClass() == UAnimSequence::StaticClass())
		{
			UAnimSequence* AnimSequence = Cast<UAnimSequence>(AssetData.GetAsset());
			if (!AnimSequence)
			{
				continue;
			}
			
			if (FAutoRootMotionRules::ShouldEnableRootMotion(AnimSequence))
			{
				if (!AnimSequence->bEnableRootMotion)
				{
					AnimSequence->bEnableRootMotion = true;
					AnimSequence->MarkPackageDirty();
					Notify(FString::Printf(TEXT("Enabled Root Motion (Auto) for: %s"), *AnimSequence->GetName()));
				}
			}
			else if (FAutoRootMotionRules::ShouldDisableRootMotion(AnimSequence))
			{
				if (AnimSequence->bEnableRootMotion)
				{
					AnimSequence->bEnableRootMotion = false;
					AnimSequence->MarkPackageDirty();
					Notify(FString::Printf(TEXT("Disabled Root Motion (Auto) for: %s"), *AnimSequence->GetName()));
				}
			}
			else
			{
				Notify(FString::Printf(TEXT("No change for: %s"), *AnimSequence->GetName()));
			}
		}
	}
	
}

void FAutoRootMotionEditorUI::Execute_Enable(const FToolMenuContext& InContext)
{
	const int32 Count = CountSelectedAnimSequences(InContext);
	if (Count == 0)
	{
		Notify(TEXT("No AnimSequences selected for Enable."), true);
		return;
	}

	Notify(FString::Printf(TEXT("[AutoRootMotion] Enable clicked. Selected AnimSequences: %d"), Count));

	const UContentBrowserAssetContextMenuContext* Context =
		InContext.FindContext<UContentBrowserAssetContextMenuContext>();

	if (!Context)
	{
		return;
	}

	for (const FAssetData& AssetData : Context->SelectedAssets)
	{
		if (AssetData.GetClass() == UAnimSequence::StaticClass())
		{
			UAnimSequence* AnimSequence = Cast<UAnimSequence>(AssetData.GetAsset());
			if (AnimSequence && !AnimSequence->bEnableRootMotion)
			{
				AnimSequence->bEnableRootMotion = true;
				AnimSequence->MarkPackageDirty();
				Notify(FString::Printf(TEXT("Enabled Root Motion for: %s"), *AnimSequence->GetName()));
			}
		}
	}
}

void FAutoRootMotionEditorUI::Execute_Disable(const FToolMenuContext& InContext)
{
	const int32 Count = CountSelectedAnimSequences(InContext);
	if (Count == 0)
	{
		Notify(TEXT("No AnimSequences selected for Disable."), true);
		return;
	}

	Notify(FString::Printf(TEXT("[AutoRootMotion] Disable clicked. Selected AnimSequences: %d"), Count));

	const UContentBrowserAssetContextMenuContext* Context =
		InContext.FindContext<UContentBrowserAssetContextMenuContext>();

	if (!Context)
	{
		return;
	}

	for (const FAssetData& AssetData : Context->SelectedAssets)
	{
		if (AssetData.GetClass() == UAnimSequence::StaticClass())
		{
			UAnimSequence* AnimSequence = Cast<UAnimSequence>(AssetData.GetAsset());
			if (AnimSequence && AnimSequence->bEnableRootMotion)
			{
				AnimSequence->bEnableRootMotion = false;
				AnimSequence->MarkPackageDirty();
				Notify(FString::Printf(TEXT("Disabled Root Motion for: %s"), *AnimSequence->GetName()));
			}
		}
	}
}

void FAutoRootMotionEditorUI::Execute_AuditSelection(const FToolMenuContext& InContext)
{
	const int32 Count = CountSelectedAnimSequences(InContext);
	Notify(FString::Printf(TEXT("[AutoRootMotion] Audit Selection clicked. Selected AnimSequences: %d"), Count));
}

void FAutoRootMotionEditorUI::Execute_AuditFolder()
{
	Notify(TEXT("[AutoRootMotion] Audit Folder clicked. (TODO: pick folder + scan)"));
}

void FAutoRootMotionEditorUI::RegisterMenus()
{
    UToolMenus* ToolMenus = UToolMenus::Get();
    if (!ToolMenus) return;

    UToolMenu* Menu = ToolMenus->ExtendMenu("ContentBrowser.AssetContextMenu");
    if (!Menu) return;

    FToolMenuSection& Section = Menu->FindOrAddSection(
        "AutoRootMotion",
        FText::FromString("AutoRootMotion")
    );

    Section.AddDynamicEntry(
        "AutoRootMotion_Dynamic",
        FNewToolMenuSectionDelegate::CreateStatic([](FToolMenuSection& InSection)
        {
            if (!HasOnlyAnimSequencesSelected(InSection))
            {
                return;
            }

        	InSection.AddMenuEntry(
				"AutoRootMotion_Auto",
				LOCTEXT("AutoRootMotion_Auto", "Detect Root Motion Automatically"),
				LOCTEXT("AutoRootMotion_AutoTooltip", "Detects root motion based on pelvis movement and applies appropriate settings"),
				FSlateIcon(),
				FToolMenuExecuteAction::CreateStatic([](const FToolMenuContext& MenuContext)
				{
					Execute_Auto(MenuContext);
				})
			);

        	InSection.AddMenuEntry(
				"AutoRootMotion_Enable",
				LOCTEXT("AutoRootMotion_Enable", "Enable Root Motion"),
				LOCTEXT("AutoRootMotion_EnableTooltip", "Force enable root motion for selected animations"),
				FSlateIcon(),
				FToolMenuExecuteAction::CreateStatic([](const FToolMenuContext& MenuContext)
				{
					Execute_Enable(MenuContext);
				})
			);

        	InSection.AddMenuEntry(
				"AutoRootMotion_Disable",
				LOCTEXT("AutoRootMotion_Disable", "Disable Root Motion"),
				LOCTEXT("AutoRootMotion_DisableTooltip", "	Force disable root motion for selected animations"),
				FSlateIcon(),
				FToolMenuExecuteAction::CreateStatic([](const FToolMenuContext& MenuContext)
				{
					Execute_Disable(MenuContext);
				})
			);
        })
    );
}

void FAutoRootMotionEditorUI::Register()
{
	UToolMenus::RegisterStartupCallback(
		FSimpleMulticastDelegate::FDelegate::CreateStatic(&FAutoRootMotionEditorUI::RegisterMenus)
	);
}

void FAutoRootMotionEditorUI::Unregister()
{
	//TODO
}
#undef LOCTEXT_NAMESPACE