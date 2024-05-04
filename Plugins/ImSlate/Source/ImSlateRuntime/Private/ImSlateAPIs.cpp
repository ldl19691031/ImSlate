#include "ImSlateAPIs.h"
#include "ImSlateInternalWidgets.h"
#include "ImSlateManager.h"

void ImSlate::Begin(const FString& Title)
{
    UImSlateManager::GetChecked()->Begin(Title);
}

void ImSlate::End()
{
    UImSlateManager::GetChecked()->End();
}

bool ImSlate::Button(const FString& Label)
{
    return UImSlateManager::GetChecked()->Button(Label);
}

void ImSlate::Text(const FString& Text)
{
    UImSlateManager::GetChecked()->Text(Text);
}

void ImSlate::CheckBox(const FString& Label, bool& bChecked)
{
    UImSlateManager::GetChecked()->CheckBox(Label, bChecked);
}

void ImSlate::InputScalar(const FString& Label, float& Value, float Step, float StepFast, const FString& Format)
{
    UImSlateManager::GetChecked()->InputScalar(Label, Value, Step, StepFast, Format);
}

void ImSlate::InputText(const FString& Label, FString& Text, int32 MaxLength)
{
    UImSlateManager::GetChecked()->InputText(Label, Text, MaxLength);
}

void ImSlate::InputInt(const FString& Label, int32& Value, int32 Step, int32 StepFast)
{
    UImSlateManager::GetChecked()->InputInt(Label, Value, Step, StepFast);
}

void ImSlate::InputVector(const FString& Label, FVector& Value, float Step, float StepFast, const FString& Format)
{
    UImSlateManager::GetChecked()->InputVector(Label, Value, Step, StepFast, Format);
}