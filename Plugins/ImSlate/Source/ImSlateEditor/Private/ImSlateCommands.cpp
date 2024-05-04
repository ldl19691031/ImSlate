// Copyright Epic Games, Inc. All Rights Reserved.

#include "ImSlateCommands.h"

#define LOCTEXT_NAMESPACE "FImSlateModule"

void FImSlateCommands::RegisterCommands()
{
	UI_COMMAND(OpenPluginWindow, "ImSlate", "Bring up ImSlate window", EUserInterfaceActionType::Button, FInputChord());
}

#undef LOCTEXT_NAMESPACE
