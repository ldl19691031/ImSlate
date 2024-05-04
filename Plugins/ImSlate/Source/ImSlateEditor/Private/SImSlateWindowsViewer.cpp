#include "SImSlateWindowsViewer.h"
#include "ImSlateAPIs.h"
#include "ImSlateManager.h"
#include "SImSlateWindow.h"

void SImSlateWindowsViewer::Construct(const FArguments& InArgs)
{
    WindowsListView = 
    SNew(SImSlateWindowsListView)
    .ListItemsSource(&Windows)
    .OnGenerateRow(this, &SImSlateWindowsViewer::OnGenerateRow)
    .OnSelectionChanged(this, &SImSlateWindowsViewer::OnSelectionChanged)
    ;
    SlateWindowWidget = SNew(SImSlateWindow);
    this->ChildSlot
    [
        SNew(SVerticalBox)
        + SVerticalBox::Slot()
        .FillHeight(1.0f)
        .Padding(10)
        [
            SNew(SHorizontalBox)
            + SHorizontalBox::Slot()
            .FillWidth(0.2f)
            [
                WindowsListView.ToSharedRef()
            ]
            + SHorizontalBox::Slot()
            .FillWidth(0.8f)
            [
                SNew(SBorder)
                .Padding(10)
                .Content()
                [
                    SlateWindowWidget.ToSharedRef()
                ]
            ]
        ]
    ];
}



TSharedRef<ITableRow> SImSlateWindowsViewer::OnGenerateRow(TSharedPtr<FImSlateWindow> InItem, const TSharedRef<STableViewBase>& OwnerTable)
{
    return SNew(STableRow<TSharedPtr<FImSlateWindow>>, OwnerTable)
    [
        SNew(SBox)
        .HeightOverride(24)
        .Padding(5)
        [
            SNew(STextBlock)
            .Text(FText::FromString(InItem->GetTitle()))
        ]
        
    ];
}

void SImSlateWindowsViewer::OnSelectionChanged(TSharedPtr<FImSlateWindow> InItem, ESelectInfo::Type SelectInfo)
{
    if (InItem.IsValid())
    {
        CurrentWindow = InItem;
        SlateWindowWidget->SetWindow(InItem);
    }
}

void SImSlateWindowsViewer::Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime)
{
    SCompoundWidget::Tick(AllottedGeometry, InCurrentTime, InDeltaTime);
    const TArray<FImSlateWindowPtr> nextWindows = UImSlateManager::GetChecked()->GetWindows();
    if (nextWindows != Windows)
    {
        Windows = nextWindows;
        WindowsListView->RequestListRefresh();
        if (Windows.Num() > 0 && CurrentWindow == nullptr)
        {
            WindowsListView->SetSelection(Windows[0]);
        }
    }
    if (CurrentWindow && CurrentWindow->IsDirty())
    {
        SlateWindowWidget->SetWindow(CurrentWindow);
        SlateWindowWidget->RebuildWindow();
        CurrentWindow->ClearDirty();
    }
}