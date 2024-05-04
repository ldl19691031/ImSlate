PREFIX bool Button(const FString& Label) SUFFIX;
PREFIX void Text(const FString& Text) SUFFIX;
PREFIX void CheckBox(const FString& Label, bool& bChecked) SUFFIX;

PREFIX void InputScalar(const FString& Label, float& Value, float Step = 0.1f, float StepFast = 1.0f, const FString& Format = TEXT("%.3f")) SUFFIX;
PREFIX void InputText(const FString& Label, FString& Text, int32 MaxLength = 0) SUFFIX;
PREFIX void InputInt(const FString& Label, int32& Value, int32 Step = 1, int32 StepFast = 100) SUFFIX;
PREFIX void InputVector(const FString& Label, FVector& Value, float Step = 0.1f, float StepFast = 1.0f, const FString& Format = TEXT("%.3f")) SUFFIX;
PREFIX void InputAsset(const FString& Label, UObject*& Value, UClass* Class) SUFFIX;