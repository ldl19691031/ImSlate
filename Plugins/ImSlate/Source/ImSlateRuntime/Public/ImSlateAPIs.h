#pragma once

#include "CoreMinimal.h"

namespace ImSlate {
    IMSLATERUNTIME_API void Begin(const FString& Title);
    IMSLATERUNTIME_API void End();   
    
    IMSLATERUNTIME_API bool Button(const FString& Label);
    IMSLATERUNTIME_API void Text(const FString& Text);
    IMSLATERUNTIME_API void CheckBox(const FString& Label, bool& bChecked);
    
    IMSLATERUNTIME_API void InputScalar(const FString& Label, float& Value, float Step = 0.1f, float StepFast = 1.0f, const FString& Format = TEXT("%.3f"));
    IMSLATERUNTIME_API void InputText(const FString& Label, FString& Text, int32 MaxLength = 0);
    IMSLATERUNTIME_API void InputInt(const FString& Label, int32& Value, int32 Step = 1, int32 StepFast = 100);
    IMSLATERUNTIME_API void InputVector(const FString& Label, FVector& Value, float Step = 0.1f, float StepFast = 1.0f, const FString& Format = TEXT("%.3f"));
}