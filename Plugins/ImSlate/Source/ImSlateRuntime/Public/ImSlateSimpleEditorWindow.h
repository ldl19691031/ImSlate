#pragma once
#include "CoreMinimal.h"

class IMSLATERUNTIME_API FImSlateSimpleEditorWindow {
public:
    static TArray<FImSlateSimpleEditorWindow*> Windows;
    FImSlateSimpleEditorWindow(TFunction<void()> WindowTickFunction)
        : WindowTickFunction(WindowTickFunction) 
        {
            Windows.Add(this);
        }
    FORCEINLINE void Tick(float DeltaTime) {
        WindowTickFunction();
    }
private:
    TFunction<void()> WindowTickFunction;
};