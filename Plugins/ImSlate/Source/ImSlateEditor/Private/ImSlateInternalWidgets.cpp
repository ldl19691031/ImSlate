#include "ImSlateInternalWidgets.h"
#include "SlateCore.h"
#include "Widgets/Input/SNumericEntryBox.h"
#include "Widgets/Input/SVectorInputBox.h"
#include "PropertyEditorModule.h"
#include "PropertyCustomizationHelpers.h"

TSharedPtr<SWidget> FImSlateButton::BuildWidget()
{
    return SNew(SButton)
    .Text(FText::FromString(Label))
    .OnClicked(this, &FImSlateButton::OnClicked);
}

FReply FImSlateButton::OnClicked()
{
    bPressed = true;
    MarkDirty();
    return FReply::Handled();
}

void FImSlateButton::End()
{
    bPressed = false;
}


TSharedPtr<SWidget> FImSlateText::BuildWidget()
{
    return SNew(STextBlock)
    .Text(FText::FromString(GetID()));
}

TSharedPtr<SWidget> FImSlateCheckBox::BuildWidget()
{
    return SNew(SCheckBox)
        .IsChecked(this, &FImSlateCheckBox::IsChecked)
        .OnCheckStateChanged(this, &FImSlateCheckBox::OnCheckStateChanged)
        [
            SNew(STextBlock)
            .Text(FText::FromString(Label))
        ];
}

ECheckBoxState FImSlateCheckBox::IsChecked() const
{
    return bChecked ? ECheckBoxState::Checked : ECheckBoxState::Unchecked;
}

void FImSlateCheckBox::OnCheckStateChanged(ECheckBoxState NewState)
{
    bChecked = (NewState == ECheckBoxState::Checked);
}

TSharedPtr<class SWidget> FImSlateInputScalar::BuildWidget()
{
    return SNew(SHorizontalBox)
        + SHorizontalBox::Slot()
        .VAlign(EVerticalAlignment::VAlign_Center)
        .AutoWidth()
        [
            SNew(STextBlock)
            .MinDesiredWidth(PROPERTY_LABEL_MIN_WIDTH)
            .Text(FText::FromString(Label))
        ]
        + SHorizontalBox::Slot()
        .FillWidth(1.0f)
        [
            SNew(SNumericEntryBox<float>)
            .Value(this, &FImSlateInputScalar::GetOptionalValue)
            .OnValueChanged(this, &FImSlateInputScalar::OnValueChanged)
        ];
}

void FImSlateInputScalar::OnValueChanged(float NewValue)
{
    Value = NewValue;
}

TSharedPtr<class SWidget> FImSlateInputText::BuildWidget()
{
    return SNew(SHorizontalBox)
        + SHorizontalBox::Slot()
        .VAlign(EVerticalAlignment::VAlign_Center)
        .AutoWidth()
        [
            SNew(STextBlock)
            .MinDesiredWidth(PROPERTY_LABEL_MIN_WIDTH)
            .Text(FText::FromString(Label))
        ]
        + SHorizontalBox::Slot()
        .FillWidth(1.0f)
        [
            SNew(SEditableTextBox)
            .Text(FText::FromString(Text))
            .OnTextChanged(this, &FImSlateInputText::OnTextChanged)
        ];
}

void FImSlateInputText::OnTextChanged(const FText& NewText)
{
    Text = NewText.ToString();
}

TSharedPtr<class SWidget> FImSlateInputInt::BuildWidget()
{
    return SNew(SHorizontalBox)
        + SHorizontalBox::Slot()
        .VAlign(EVerticalAlignment::VAlign_Center)
        .AutoWidth()
        [
            SNew(STextBlock)
            .MinDesiredWidth(PROPERTY_LABEL_MIN_WIDTH)
            .Text(FText::FromString(Label))
        ]
        + SHorizontalBox::Slot()
        .FillWidth(1.0f)
        [
            SNew(SNumericEntryBox<int32>)
            .Value(Value)
            .OnValueChanged(this, &FImSlateInputInt::OnValueChanged)
        ];
}

void FImSlateInputInt::OnValueChanged(int32 NewValue)
{
    Value = NewValue;
}

TSharedPtr<class SWidget> FImSlateInputVector::BuildWidget()
{
    return SNew(SHorizontalBox)
        + SHorizontalBox::Slot()
        .VAlign(EVerticalAlignment::VAlign_Center)
        .AutoWidth()
        [
            SNew(STextBlock)
            .MinDesiredWidth(PROPERTY_LABEL_MIN_WIDTH)
            .Text(FText::FromString(Label))
        ]
        + SHorizontalBox::Slot()
        .FillWidth(1.0f)
        [
            SNew(SVectorInputBox)
            .X(this, &FImSlateInputVector::GetX)
            .Y(this, &FImSlateInputVector::GetY)
            .Z(this, &FImSlateInputVector::GetZ)
            .OnXCommitted(this, &FImSlateInputVector::OnSetPosition, 0)
            .OnYCommitted(this, &FImSlateInputVector::OnSetPosition, 1)
            .OnZCommitted(this, &FImSlateInputVector::OnSetPosition, 2)
        ];
}


void FImSlateInputVector::OnSetPosition(float NewValue,ETextCommit::Type CommitInfo, int32 Index)
{
    switch (Index)
    {
    case 0:
        Value.X = NewValue;
        break;
    case 1:
        Value.Y = NewValue;
        break;
    case 2:
        Value.Z = NewValue;
        break;
    default:
        break;
    }
}

TSharedPtr<class SWidget> FImSlateInputAsset::BuildWidget()
{
    return SNew(SHorizontalBox)
        + SHorizontalBox::Slot()
        .VAlign(EVerticalAlignment::VAlign_Center)
        .AutoWidth()
        [
            SNew(STextBlock)
            .MinDesiredWidth(PROPERTY_LABEL_MIN_WIDTH)
            .Text(FText::FromString(Label))
        ]
        + SHorizontalBox::Slot()
        .FillWidth(1.0f)
        [
            SNew(SObjectPropertyEntryBox)
            .AllowClear(true)
            .OnObjectChanged(this, &FImSlateInputAsset::OnAssetSelected)
            .ObjectPath(this, &FImSlateInputAsset::GetObjectPath)
            .AllowedClass(Class.Get())
        ];
}

void FImSlateInputAsset::OnAssetSelected(const FAssetData& AssetData)
{
    Value = AssetData.GetAsset();
}

FString FImSlateInputAsset::GetObjectPath() const
{
    return Value.IsValid() ? Value->GetPathName() : TEXT("None");
}