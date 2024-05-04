#include "ImSlateManager.h"
#include "ImSlateAPIs.h"
#include "ImSlateCoreWidgets.h"
#include "ImSlateSimpleEditorWindow.h"

FImSlateWidgetBuilderInterface* UImSlateManager::WidgetBuilder = nullptr;

UImSlateManager* UImSlateManager::Get()
{
    return GEngine->GetEngineSubsystem<UImSlateManager>();
}

void UImSlateManager::Initialize(FSubsystemCollectionBase& Collection)
{
    EditorTickHandle = FTSTicker::GetCoreTicker().AddTicker(
        FTickerDelegate::CreateLambda([this](float DeltaTime)
    {
        for (FImSlateSimpleEditorWindow* Window : FImSlateSimpleEditorWindow::Windows)
        {
            Window->Tick(DeltaTime);
        }
        return true;
    }));

    //Collect all editor simple windows
    for (FImSlateSimpleEditorWindow* Window : FImSlateSimpleEditorWindow::Windows)
    {
        Window->Tick(0.0f);
    }
    EditorTickWindows = GetWindows();
}

void UImSlateManager::Deinitialize()
{
   FTSTicker::GetCoreTicker().RemoveTicker(EditorTickHandle);
}

UImSlateManager* UImSlateManager::GetChecked()
{
    UImSlateManager* Manager = Get();
    check(Manager);
    return Manager;
}

void FImSlateWidgetBuilderInterface::Begin()
{
    if (CurrentContainer.IsValid())
    {
        CurrentContainer->Begin();
    }
}

void FImSlateWidgetBuilderInterface::End()
{
    if (CurrentContainer.IsValid())
    {
        CurrentContainer->End();
        CurrentContainer.Reset();
    }
}

void UImSlateManager::Begin(const FString& Title)
{
    if (Windows.Contains(Title) == false)
    {
        TSharedPtr<FImSlateWindow> Window = MakeShared<FImSlateWindow>(Title);
        Windows.Add(Title, Window);
    }
    CurrentWindow = Windows[Title];
    if (WidgetBuilder)
    {
        WidgetBuilder->CurrentContainer = StaticCastSharedPtr<FImSlateContainer>(CurrentWindow);
        WidgetBuilder->Begin();
    }
    
}

void UImSlateManager::End()
{
    if (WidgetBuilder)
    {
        WidgetBuilder->End();
    }
    CurrentWindow.Reset();
}
