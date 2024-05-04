#include "ImSlateManager.h"
#include "ImSlateAPIs.h"

UImSlateManager* UImSlateManager::Get()
{
    return GEngine->GetEngineSubsystem<UImSlateManager>();
}

UImSlateManager* UImSlateManager::GetChecked()
{
    UImSlateManager* Manager = Get();
    check(Manager);
    return Manager;
}

void UImSlateManager::Begin(const FString& Title)
{
    if (Windows.Contains(Title) == false)
    {
        TSharedPtr<FImSlateWindow> Window = MakeShared<FImSlateWindow>(Title);
        Windows.Add(Title, Window);
    }
    CurrentWindow = Windows[Title];
    CurrentContainer = CurrentWindow;
    CurrentContainer->Begin();
}

void UImSlateManager::End()
{
    CurrentContainer->End();
    CurrentWindow.Reset();
    CurrentContainer.Reset();
}

bool UImSlateManager::Button(const FString& Label)
{
    check(CurrentContainer.IsValid());
    TSharedPtr<FImSlateButton> Button = CurrentContainer->FindOrAddChild<FImSlateButton>(
        FImSlateButton::LabelToID(Label), 
        Label
    );
    return Button->IsPressed();
}

void UImSlateManager::Text(const FString& Text)
{
    check(CurrentContainer.IsValid());
    CurrentContainer->FindOrAddChild<FImSlateText>(
        FImSlateText::TextToID(Text),
        Text
    );
}

void UImSlateManager::CheckBox(const FString& Label, bool& bChecked)
{
    check(CurrentContainer.IsValid());
    TSharedPtr<FImSlateCheckBox> CheckBox = CurrentContainer->FindOrAddChild<FImSlateCheckBox>(
        FImSlateCheckBox::LabelToID(Label),
        Label
    );
    bChecked = CheckBox->IsChecked() == ECheckBoxState::Checked;
}

void UImSlateManager::InputScalar(const FString& Label, float& Value, float Step, float StepFast, const FString& Format)
{
    check(CurrentContainer.IsValid());
    TSharedPtr<FImSlateInputScalar> InputScalar = CurrentContainer->FindOrAddChild<FImSlateInputScalar>(
        FImSlateInputScalar::LabelToID(Label),
        Label,
        Value
    );
    Value = InputScalar->GetValue();
}

void UImSlateManager::InputText(const FString& Label, FString& Text, int32 MaxLength)
{
    check(CurrentContainer.IsValid());
    TSharedPtr<FImSlateInputText> InputText = CurrentContainer->FindOrAddChild<FImSlateInputText>(
        FImSlateInputText::LabelToID(Label),
        Label,
        Text
    );
    Text = InputText->GetText();
}

void UImSlateManager::InputInt(const FString& Label, int32& Value, int32 Step, int32 StepFast)
{
    check(CurrentContainer.IsValid());
    TSharedPtr<FImSlateInputInt> InputInt = CurrentContainer->FindOrAddChild<FImSlateInputInt>(
        FImSlateInputInt::LabelToID(Label),
        Label,
        Value
    );
    Value = InputInt->GetValue();
}

void UImSlateManager::InputVector(const FString& Label, FVector& Value, float Step, float StepFast, const FString& Format)
{
    check(CurrentContainer.IsValid());
    TSharedPtr<FImSlateInputVector> InputVector = CurrentContainer->FindOrAddChild<FImSlateInputVector>(
        FImSlateInputVector::LabelToID(Label),
        Label,
        Value
    );
    Value = InputVector->GetValue();
}
