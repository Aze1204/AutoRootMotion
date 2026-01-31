#include "AutoRootMotionModule.h"
#include "AutoRootMotionEditorUI.h"
#include "AutoRootMotionRules.h"
#include "AutoRootMotionSettings.h"
#include "ISettingsModule.h"

#include "Logging/LogMacros.h"
#include "Modules/ModuleManager.h"
IMPLEMENT_MODULE(FAutoRootMotionModule, AutoRootMotion)
#define LOCTEXT_NAMESPACE "AutoRootMotion"
void FAutoRootMotionModule::StartupModule()
{
	FAutoRootMotionEditorUI::Register();
	IModuleInterface::StartupModule();
	
	if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
	{
		SettingsModule->RegisterSettings("Project", "Plugins", "AutoRootMotion",
			LOCTEXT("AutoRootMotionSettingsName", "AutoRootMotion Settings"),
			LOCTEXT("AutoRootMotionSettingsDesc", "Configure AutoRootMotion plugin options."),
			GetMutableDefault<UAutoRootMotionSettings>()
		);
	}
	FEditorDelegates::OnAssetPostImport.AddRaw(this, &FAutoRootMotionModule::OnAssetPostImport);
	
}

void FAutoRootMotionModule::ShutdownModule()
{
	FAutoRootMotionEditorUI::Unregister();
	if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
	{
		SettingsModule->UnregisterSettings("Project", "Plugins", "AutoRootMotion");
	}

	IModuleInterface::ShutdownModule();
	FEditorDelegates::OnAssetPostImport.RemoveAll(this);
}


void FAutoRootMotionModule::OnAssetPostImport(UFactory* InFactory, UObject* InCreatedObject)
{
	if (!GetDefault<UAutoRootMotionSettings>()->EnablePostImport) return;

	if (UAnimSequence* Anim = Cast<UAnimSequence>(InCreatedObject))
	{
		if (FAutoRootMotionRules::HasRootMotion(Anim))
		{
			Anim->bEnableRootMotion = true;
			Anim->MarkPackageDirty();
		}
	}
}
#undef LOCTEXT_NAMESPACE