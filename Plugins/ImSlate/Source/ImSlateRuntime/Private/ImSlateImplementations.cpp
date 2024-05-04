#include "ImSlateAPIs.h"
#include "ImSlateManager.h"
#include "ImSlateImplementationHelpers.h"

IMPL_API_RET_PARAM1     (Button, bool, const FString&, Label)
IMPL_API_PARAM1         (Text, const FString&, Text)
IMPL_API_PARAM2         (CheckBox, const FString&, Label, bool&, bChecked)
IMPL_API_PARAM5         (InputScalar, const FString&, Label, float&, Value, float, Step, float, StepFast, const FString&, Format)
IMPL_API_PARAM3         (InputText, const FString&, Label, FString&, Text, int32, MaxLength)
IMPL_API_PARAM4         (InputInt, const FString&, Label, int32&, Value, int32, Step, int32, StepFast)
IMPL_API_PARAM5         (InputVector, const FString&, Label, FVector&, Value, float, Step, float, StepFast, const FString&, Format)
IMPL_API_PARAM3         (InputAsset, const FString&, Label, UObject*&, Value, UClass*, Class)