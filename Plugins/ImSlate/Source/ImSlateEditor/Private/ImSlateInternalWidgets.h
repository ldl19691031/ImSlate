#pragma once
#include "ImSlateCoreWidgets.h"

class FImSlateButton : public FImSlateLeaf {

public:
    FORCEINLINE static FString LabelToID(const FString& InLabel) {
        return TEXT("Button_") + InLabel;
    }

    FImSlateButton(const FString& id, const FString& _label) 
        : FImSlateLeaf(id) 
        , Label(_label)
        {}

    FORCEINLINE const FString& GetLabel() const { return Label; }
    FORCEINLINE bool IsPressed() const { return bPressed; }
    
    virtual TSharedPtr<class SWidget> BuildWidget() override;
    virtual void End() override;
private:
    FString Label;
    bool bPressed = false;
private:
    FReply OnClicked();
};

class FImSlateText : public FImSlateLeaf {
public:
    FORCEINLINE static FString TextToID(const FString& InText) {
        return TEXT("Text_") + InText;
    }

    FImSlateText(const FString& id, const FString& _text) 
        : FImSlateLeaf(id) 
        , Text(_text) 
        {}

    FORCEINLINE const FString& GetText() const { return Text; }

    virtual TSharedPtr<class SWidget> BuildWidget() override;
private:
    FString Text;
};

class FImSlateCheckBox : public FImSlateLeaf {
public:
    FORCEINLINE static FString LabelToID(const FString& InLabel) {
        return TEXT("CheckBox_") + InLabel;
    }

    FImSlateCheckBox(const FString& id, const FString& _label) 
        : FImSlateLeaf(id) 
        , Label(_label) 
        {}

    FORCEINLINE const FString& GetLabel() const { return Label; }
    ECheckBoxState IsChecked() const;

    virtual TSharedPtr<class SWidget> BuildWidget() override;
private:
    FString Label;
    bool bChecked = false;
private:
    void OnCheckStateChanged(ECheckBoxState NewState);
};

class FImSlateInputScalar : public FImSlateLeaf {
public:
    FORCEINLINE static FString LabelToID(const FString& InLabel) {
        return TEXT("InputScalar_") + InLabel;
    }

    FImSlateInputScalar(const FString& id, const FString& _label, float _value)
        : FImSlateLeaf(id)
        , Label(_label)
        , Value(_value)
    {}

    FORCEINLINE const FString& GetLabel() const { return Label; }
    FORCEINLINE float GetValue() const { return Value; }
    FORCEINLINE TOptional<float> GetOptionalValue() const { return Value; }

    virtual TSharedPtr<class SWidget> BuildWidget() override;
private:
    FString Label;
    float Value;
private:
    void OnValueChanged(float NewValue);
};

class FImSlateInputText : public FImSlateLeaf {
public:
    FORCEINLINE static FString LabelToID(const FString& InLabel) {
        return TEXT("InputText_") + InLabel;
    }
    FImSlateInputText(const FString& id, const FString& _label, const FString& _text)
        : FImSlateLeaf(id)
        , Label(_label)
        , Text(_text)
    {}

    FORCEINLINE const FString& GetLabel() const { return Label; }
    FORCEINLINE const FString& GetText() const { return Text; }

    virtual TSharedPtr<class SWidget> BuildWidget() override;
private:
    FString Label;
    FString Text;
private:
    void OnTextChanged(const FText& NewText);
};

class FImSlateInputInt : public FImSlateLeaf {
public:
    FORCEINLINE static FString LabelToID(const FString& InLabel) {
        return TEXT("InputInt_") + InLabel;
    }
    FImSlateInputInt(const FString& id, const FString& _label, int32 _value)
        : FImSlateLeaf(id)
        , Label(_label)
        , Value(_value)
    {}

    FORCEINLINE const FString& GetLabel() const { return Label; }
    FORCEINLINE int32 GetValue() const { return Value; }

    virtual TSharedPtr<class SWidget> BuildWidget() override;
private:
    FString Label;
    int32 Value;
private:
    void OnValueChanged(int32 NewValue);
};

class FImSlateInputVector : public FImSlateLeaf {
public:
    FORCEINLINE static FString LabelToID (const FString& InLabel) {
        return TEXT("InputVector_") + InLabel;
    }
    FImSlateInputVector(const FString& id, const FString& _label, FVector _value)
        : FImSlateLeaf(id)
        , Label(_label)
        , Value(_value)
    {}

    FORCEINLINE const FString& GetLabel() const { return Label; }
    FORCEINLINE FVector GetValue() const { return Value; }
    TOptional<float> GetX() const { return Value.X; }
    TOptional<float> GetY() const { return Value.Y; }
    TOptional<float> GetZ() const { return Value.Z; }

    virtual TSharedPtr<class SWidget> BuildWidget() override;
private:
    FString Label;
    FVector Value;
private:
    void OnSetPosition(float NewValue,ETextCommit::Type CommitInfo, int32 Index);
};


class FImSlateInputAsset : public FImSlateLeaf {
public:
    FORCEINLINE static FString LabelToID(const FString& InLabel) {
        return TEXT("InputAsset_") + InLabel;
    }
    FImSlateInputAsset(const FString& id, const FString& _label, UObject* _value, UClass* _class)
        : FImSlateLeaf(id)
        , Label(_label)
        , Value(_value)
        , Class(_class)
    {}

    FORCEINLINE const FString& GetLabel() const { return Label; }
    FORCEINLINE UObject* GetValue() const { return Value.Get(); }

    virtual TSharedPtr<class SWidget> BuildWidget() override;
private:
    FString Label;
    TWeakObjectPtr<UObject> Value;
    TWeakObjectPtr<UClass> Class;
private:
    FString GetObjectPath() const;
    void OnAssetSelected(const FAssetData& AssetData);
};