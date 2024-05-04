#include "SImSlateWindow.h"

void SImSlateWindow::Construct(const FArguments& InArgs)
{
}

void SImSlateWindow::RebuildWindow()
{
    ChildSlot.DetachWidget();
    if (Window.IsValid() == false)
    {
        return;
    }
    ChildSlot[
        Window->BuildWidget().ToSharedRef()
    ];
}

void SImSlateWindow::SetWindow(FImSlateWindowPtr InWindow)
{
    if (Window != InWindow)
    {
        Window = InWindow;
        RebuildWindow();
    }  
}