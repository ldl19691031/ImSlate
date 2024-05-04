#pragma once
#include "CoreMinimal.h"
#include "SlateCore.h"
#include "ImSlateInternalWidgets.h"

typedef SListView<TSharedPtr< class FImSlateWindow > > SImSlateWindowsListView;

class SImSlateWindowsViewer : public SCompoundWidget
{
public:
    SLATE_BEGIN_ARGS(SImSlateWindowsViewer)
    {}
    SLATE_END_ARGS()

    void Construct(const FArguments& InArgs);
    virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;
private:
    TSharedPtr<SImSlateWindowsListView> WindowsListView;
    TSharedPtr<class SImSlateWindow> SlateWindowWidget;
    TArray< FImSlateWindowPtr > Windows;
    FImSlateWindowPtr CurrentWindow = nullptr;
private:
    TSharedRef<ITableRow> OnGenerateRow(TSharedPtr<FImSlateWindow> InItem, const TSharedRef<STableViewBase>& OwnerTable);
    void OnSelectionChanged(TSharedPtr<FImSlateWindow> InItem, ESelectInfo::Type SelectInfo);
};