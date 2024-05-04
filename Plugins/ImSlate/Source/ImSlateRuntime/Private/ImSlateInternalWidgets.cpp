#include "ImSlateInternalWidgets.h"
#include "SlateCore.h"
#include "Widgets/Input/SNumericEntryBox.h"
#include "Widgets/Input/SVectorInputBox.h"

void FImSlateContainer::AddChild(TSharedPtr<class FImSlateInternalWidgetBase> Child)
{
    check(Child.IsValid());
    Child->SetParent(AsShared());
    Children.Add(Child);
    if (bShouldUpdateChildren)
    {
        ChildrenToKeep.Add(Child);
    }
    MarkDirty();
}

void FImSlateInternalWidgetBase::MarkDirty()
{
    bDirty = true;
    if (Parent.IsValid())
    {
        Parent.Pin()->MarkDirty();
    }
}

void FImSlateContainer::Begin()
{
    bShouldUpdateChildren = true;
    ChildrenToKeep.Empty();
}

void FImSlateContainer::End()
{
    bShouldUpdateChildren = false;
    if (Children.Num() != ChildrenToKeep.Num())
    {
        MarkDirty();
    }
    Children = ChildrenToKeep;
    ChildrenToKeep.Empty();

    for (const TSharedPtr<FImSlateInternalWidgetBase>& Child : Children)
    {
        Child->End();
    }
}

bool FImSlateContainer::ContainsChild(const FString& ChildID) const
{
    for (const TSharedPtr<FImSlateInternalWidgetBase>& Child : Children)
    {
        if (Child->GetID() == ChildID)
        {
            return true;
        }
    }
    return false;
}

void FImSlateContainer::UpdateChild(TSharedPtr<class FImSlateInternalWidgetBase> Child)
{
    Child->Update();
}

void FImSlateWindow::Begin()
{
    FImSlateContainer::Begin();
}

void FImSlateWindow::End()
{
    FImSlateContainer::End();
}


TSharedPtr<SWidget> FImSlateWindow::BuildWidget()
{
    TSharedPtr<SVerticalBox> VerticalBox = SNew(SVerticalBox);
    for (const TSharedPtr<FImSlateInternalWidgetBase>& Child : Children)
    {
        TSharedPtr<SWidget> ChildWidget = Child->BuildWidget();
        if (ChildWidget.IsValid())
        {
            VerticalBox->AddSlot()
            .AutoHeight()
            .HAlign(EHorizontalAlignment::HAlign_Left)
            .VAlign(EVerticalAlignment::VAlign_Center)
            .Padding(5.0f)
            [   
                ChildWidget->AsShared()
            ];
        }
    }
    return VerticalBox;
}

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
    MarkDirty();
}

TSharedPtr<class SWidget> FImSlateInputScalar::BuildWidget()
{
    return SNew(SHorizontalBox)
        + SHorizontalBox::Slot()
        .AutoWidth()
        [
            SNew(STextBlock)
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

void FImSlateInputScalar::End()
{
    // Perform any necessary cleanup or finalization here
}

void FImSlateInputScalar::OnValueChanged(float NewValue)
{
    Value = NewValue;
}

TSharedPtr<class SWidget> FImSlateInputText::BuildWidget()
{
    return SNew(SHorizontalBox)
        + SHorizontalBox::Slot()
        .AutoWidth()
        [
            SNew(STextBlock)
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

void FImSlateInputText::End()
{
    // Perform any necessary cleanup or finalization here
}

void FImSlateInputText::OnTextChanged(const FText& NewText)
{
    Text = NewText.ToString();
}

TSharedPtr<class SWidget> FImSlateInputInt::BuildWidget()
{
    return SNew(SHorizontalBox)
        + SHorizontalBox::Slot()
        .AutoWidth()
        [
            SNew(STextBlock)
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

void FImSlateInputInt::End()
{
    // Perform any cleanup or finalization logic here
}

void FImSlateInputInt::OnValueChanged(int32 NewValue)
{
    Value = NewValue;
    MarkDirty();
}

TSharedPtr<class SWidget> FImSlateInputVector::BuildWidget()
{
    return SNew(SHorizontalBox)
        + SHorizontalBox::Slot()
        .AutoWidth()
        [
            SNew(STextBlock)
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

void FImSlateInputVector::End()
{
    // Perform any necessary cleanup or finalization here
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
    MarkDirty();
}