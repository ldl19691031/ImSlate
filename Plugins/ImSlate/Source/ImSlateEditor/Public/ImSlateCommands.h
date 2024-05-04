// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "ImSlateStyle.h"

class FImSlateCommands : public TCommands<FImSlateCommands>
{
public:

	FImSlateCommands()
		: TCommands<FImSlateCommands>(TEXT("ImSlate"), NSLOCTEXT("Contexts", "ImSlate", "ImSlate Plugin"), NAME_None, FImSlateStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > OpenPluginWindow;
};