#pragma once
#include "CoreMinimal.h"
#include "SlateCore.h"
#include "ImSlateInternalWidgets.h"

class SImSlateWindow : public SCompoundWidget
{
public:
    SLATE_BEGIN_ARGS(SImSlateWindow)
    {}
    SLATE_END_ARGS()

    void Construct(const FArguments& InArgs);
    void SetWindow(FImSlateWindowPtr InWindow);
    void RebuildWindow();
private:
    FImSlateWindowPtr Window;

};