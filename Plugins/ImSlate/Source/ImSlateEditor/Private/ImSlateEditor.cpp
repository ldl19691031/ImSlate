// Copyright Epic Games, Inc. All Rights Reserved.

#include "ImSlateEditor.h"
#include "ImSlateStyle.h"
#include "ImSlateCommands.h"
#include "LevelEditor.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "ToolMenus.h"
#include "SImSlateWindowsViewer.h"
#include "ImSlateManager.h"
#include "ImSlateWidgetBuilder.h"

static const FName ImSlateTabName("ImSlate");

#define LOCTEXT_NAMESPACE "FImSlateEditorModule"

void FImSlateEditorModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FImSlateStyle::Initialize();
	FImSlateStyle::ReloadTextures();

	FImSlateCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FImSlateCommands::Get().OpenPluginWindow,
		FExecuteAction::CreateRaw(this, &FImSlateEditorModule::PluginButtonClicked),
		FCanExecuteAction());

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FImSlateEditorModule::RegisterMenus));
	
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(ImSlateTabName, FOnSpawnTab::CreateRaw(this, &FImSlateEditorModule::OnSpawnPluginTab))
		.SetDisplayName(LOCTEXT("FImSlateTabTitle", "ImSlate"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);

	UImSlateManager::WidgetBuilder = new FImSlateWidgetBuilder();
}

void FImSlateEditorModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FImSlateStyle::Shutdown();

	FImSlateCommands::Unregister();

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(ImSlateTabName);

	UImSlateManager::WidgetBuilder = nullptr;
}

TSharedRef<SDockTab> FImSlateEditorModule::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{
	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			SNew(SImSlateWindowsViewer)
		];
}

void FImSlateEditorModule::PluginButtonClicked()
{
	FGlobalTabmanager::Get()->TryInvokeTab(ImSlateTabName);
}

void FImSlateEditorModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);

	{
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
		{
			FToolMenuSection& Section = Menu->FindOrAddSection("WindowLayout");
			Section.AddMenuEntryWithCommandList(FImSlateCommands::Get().OpenPluginWindow, PluginCommands);
		}
	}

	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar");
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("Settings");
			{
				FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FImSlateCommands::Get().OpenPluginWindow));
				Entry.SetCommandList(PluginCommands);
			}
		}
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FImSlateEditorModule, ImSlateEditor)