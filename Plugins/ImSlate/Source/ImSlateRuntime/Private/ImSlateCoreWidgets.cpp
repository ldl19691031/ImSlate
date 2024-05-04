#include "ImSlateCoreWidgets.h"
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
