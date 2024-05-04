#include "ImSlateWidgetBuilder.h"
#include "ImSlateInternalWidgets.h"

bool FImSlateWidgetBuilder::Button(const FString& Label)
{
    check(CurrentContainer.IsValid());
    return CurrentContainer->FindOrAddChild<FImSlateButton>(
        FImSlateButton::LabelToID(Label),
        Label
    )->IsPressed();
}

void FImSlateWidgetBuilder::Text(const FString& Text)
{
    check(CurrentContainer.IsValid());
    CurrentContainer->FindOrAddChild<FImSlateText>(
        FImSlateText::TextToID(Text),
        Text
    );
}

void FImSlateWidgetBuilder::CheckBox(const FString& Label, bool& bChecked)
{
    check(CurrentContainer.IsValid());
    TSharedPtr<FImSlateCheckBox> CheckBox = CurrentContainer->FindOrAddChild<FImSlateCheckBox>(
        FImSlateCheckBox::LabelToID(Label),
        Label
    );
    bChecked = CheckBox->IsChecked() == ECheckBoxState::Checked;
}

void FImSlateWidgetBuilder::InputScalar(const FString& Label, float& Value, float Step, float StepFast, const FString& Format)
{
    check(CurrentContainer.IsValid());
    TSharedPtr<FImSlateInputScalar> InputScalar = CurrentContainer->FindOrAddChild<FImSlateInputScalar>(
        FImSlateInputScalar::LabelToID(Label),
        Label,
        Value
    );
    Value = InputScalar->GetValue();
}

void FImSlateWidgetBuilder::InputText(const FString& Label, FString& Text, int32 MaxLength)
{
    check(CurrentContainer.IsValid());
    TSharedPtr<FImSlateInputText> InputText = CurrentContainer->FindOrAddChild<FImSlateInputText>(
        FImSlateInputText::LabelToID(Label),
        Label,
        Text
    );
    Text = InputText->GetText();
}

void FImSlateWidgetBuilder::InputInt(const FString& Label, int32& Value, int32 Step, int32 StepFast)
{
    check(CurrentContainer.IsValid());
    TSharedPtr<FImSlateInputInt> InputInt = CurrentContainer->FindOrAddChild<FImSlateInputInt>(
        FImSlateInputInt::LabelToID(Label),
        Label,
        Value
    );
    Value = InputInt->GetValue();
}

void FImSlateWidgetBuilder::InputVector(const FString& Label, FVector& Value, float Step, float StepFast, const FString& Format)
{
    check(CurrentContainer.IsValid());
    TSharedPtr<FImSlateInputVector> InputVector = CurrentContainer->FindOrAddChild<FImSlateInputVector>(
        FImSlateInputVector::LabelToID(Label),
        Label,
        Value
    );
    Value = InputVector->GetValue();
}

void FImSlateWidgetBuilder::InputAsset(const FString& Label, UObject*& Value, UClass* Class)
{
    check(CurrentContainer.IsValid());
    TSharedPtr<FImSlateInputAsset> InputAsset = CurrentContainer->FindOrAddChild<FImSlateInputAsset>(
        FImSlateInputAsset::LabelToID(Label),
        Label,
        Value,
        Class
    );
    Value = InputAsset->GetValue();
}