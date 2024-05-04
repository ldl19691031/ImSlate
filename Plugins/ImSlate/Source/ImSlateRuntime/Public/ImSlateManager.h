#pragma once

#include "CoreMinimal.h"
#include "Subsystems/EngineSubsystem.h"
#include "Containers/Ticker.h"
#include "ImSlateWidgetBuilderInterface.h"
#include "ImSlateManager.generated.h"


UCLASS()
class IMSLATERUNTIME_API UImSlateManager : public UEngineSubsystem
{
    GENERATED_BODY()
public:
    static UImSlateManager* Get();
    static UImSlateManager* GetChecked();

    //Begin UEngineSubsystem interface
    virtual void Initialize(FSubsystemCollectionBase& Collection) override;
    virtual void Deinitialize() override;
    //End UEngineSubsystem interface

    void Begin(const FString& Title);
    void End();
    
    FORCEINLINE TArray< TSharedPtr<class FImSlateWindow> > GetWindows() const
    {
        TArray< TSharedPtr<class FImSlateWindow> > OutWindows;
        Windows.GenerateValueArray(OutWindows);
        return OutWindows;
    }
private:
    TMap<FString, TSharedPtr<class FImSlateWindow> > Windows;
    TSharedPtr<class FImSlateWindow> CurrentWindow;
    TArray< TSharedPtr<class FImSlateWindow> > EditorTickWindows;
    FTSTicker::FDelegateHandle EditorTickHandle;
public:
    static class FImSlateWidgetBuilderInterface* WidgetBuilder;
};

