#pragma once

#include "CoreMinimal.h"
#include "Subsystems/EngineSubsystem.h"
#include "ImSlateManager.generated.h"

UCLASS()
class IMSLATERUNTIME_API UImSlateManager : public UEngineSubsystem
{
    GENERATED_BODY()
public:
    static UImSlateManager* Get();
    static UImSlateManager* GetChecked();

    void Begin(const FString& Title);
    void End();
    bool Button(const FString& Label);
    void Text(const FString& Text);
    void CheckBox(const FString& Label, bool& bChecked);

    void InputScalar(const FString& Label, float& Value, float Step = 0.1f, float StepFast = 1.0f, const FString& Format = TEXT("%.3f"));
    void InputText(const FString& Label, FString& Text, int32 MaxLength = 0);
    void InputInt(const FString& Label, int32& Value, int32 Step = 1, int32 StepFast = 100);
    void InputVector(const FString& Label, FVector& Value, float Step = 0.1f, float StepFast = 1.0f, const FString& Format = TEXT("%.3f"));

    FORCEINLINE TArray< TSharedPtr<class FImSlateWindow> > GetWindows() const
    {
        TArray< TSharedPtr<class FImSlateWindow> > OutWindows;
        Windows.GenerateValueArray(OutWindows);
        return OutWindows;
    }
private:
    TMap<FString, TSharedPtr<class FImSlateWindow> > Windows;

    TSharedPtr<class FImSlateWindow> CurrentWindow;
    TSharedPtr<class FImSlateContainer> CurrentContainer;

};