#pragma once

#include "CoreMinimal.h"
#include "ToolMenus.h"

class FAutoRootMotionEditorUI
{
public:
	static void Register();
	static void Unregister();
	
	static bool HasOnlyAnimSequencesSelected(FToolMenuSection& InSection);
	static void Notify(const FString& Msg, bool bPopupDialog = false);
	static int32 CountSelectedAnimSequences(const FToolMenuContext& InContext);
	static void Execute_Auto(const FToolMenuContext& InContext);
	static void Execute_Enable(const FToolMenuContext& InContext);
	static void Execute_Disable(const FToolMenuContext& InContext);
	static void Execute_AuditSelection(const FToolMenuContext& InContext);
	static void Execute_AuditFolder();
	static void RegisterMenus();
};
