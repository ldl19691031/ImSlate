#pragma once
#include "CoreMinimal.h"
#include <utility>

class IMSLATERUNTIME_API FImSlateInternalWidgetBase :public TSharedFromThis<FImSlateInternalWidgetBase>{
public:
    FImSlateInternalWidgetBase() = delete;
    FImSlateInternalWidgetBase(const FString& InID) : ID(InID) {}

    virtual ~FImSlateInternalWidgetBase() = default;

    virtual void Update() {}
    virtual void End() {}
    virtual void MarkDirty();
    virtual TSharedPtr<class SWidget> BuildWidget() { return nullptr; }

    void SetParent(TSharedPtr<class FImSlateInternalWidgetBase> InParent) { Parent = InParent; }

    const FString& GetID() const { return ID; }
    FORCEINLINE bool IsDirty() const { return bDirty; }
    FORCEINLINE void ClearDirty() { bDirty = false; }
private:
    FString ID;
    TWeakPtr<class FImSlateInternalWidgetBase> Parent;
    bool bDirty = false;
};

typedef TSharedPtr<class FImSlateInternalWidgetBase> FImSlateInternalWidgetPtr;

class IMSLATERUNTIME_API FImSlateContainer : public FImSlateInternalWidgetBase{
public:
    FImSlateContainer();
    FImSlateContainer(const FString& InID) : FImSlateInternalWidgetBase(InID) {}
    FImSlateContainer(const FImSlateContainer& Other) = delete;
    FImSlateContainer& operator=(const FImSlateContainer& Other) = delete;

    void AddChild(TSharedPtr<class FImSlateInternalWidgetBase> Child);
    virtual void Begin();
    virtual void End();

    bool HasChildren() const { return Children.Num() > 0; }
    bool ContainsChild(const FString& ChildID) const;

    template<typename TWidgetType>
    TSharedPtr<TWidgetType> GetChild(const FString& ChildID) {
        for (TSharedPtr<FImSlateInternalWidgetBase> Child : Children) {
            if (Child->GetID() == ChildID) {
                if (bShouldUpdateChildren)
                {
                    ChildrenToKeep.Add(Child);
                }
                return StaticCastSharedPtr<TWidgetType>(Child);
            }
        }
        return nullptr;
    }

    
    template<typename TWidgetType, typename... Params>
    TSharedPtr<TWidgetType> FindOrAddChild(const FString& ChildID, Params... Args) {
        TSharedPtr<TWidgetType> Child = GetChild<TWidgetType>(ChildID);
        if (!Child.IsValid()) {
            Child = MakeShared<TWidgetType>(ChildID, std::forward<Params>(Args)...);
            AddChild(Child);
        }
        return Child;
    }

protected:
    TArray<TSharedPtr<class FImSlateInternalWidgetBase> > Children;

    TArray<TSharedPtr<class FImSlateInternalWidgetBase> > ChildrenToKeep;

    bool bShouldUpdateChildren = false;

private:
    virtual void UpdateChild(TSharedPtr<class FImSlateInternalWidgetBase> Child);
};

typedef TSharedPtr<class FImSlateContainer> FImSlateContainerPtr;

class IMSLATERUNTIME_API FImSlateWindow : public FImSlateContainer {
public:
    FImSlateWindow(const FString& InTitle) 
        : FImSlateContainer(TEXT("Window_") + InTitle)
        , Title(InTitle) 
        {}

    virtual void Begin() override;
    virtual void End() override;
    virtual TSharedPtr<class SWidget> BuildWidget() override;

    FORCEINLINE const FString& GetTitle() const { return Title; }
protected:
    FString Title;
};

typedef TSharedPtr<class FImSlateWindow> FImSlateWindowPtr;


class IMSLATERUNTIME_API FImSlateLeaf : public FImSlateInternalWidgetBase {
public:
    FImSlateLeaf(const FString& InID) : FImSlateInternalWidgetBase(InID) {}
};

class IMSLATERUNTIME_API FImSlateButton : public FImSlateLeaf {

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

class IMSLATERUNTIME_API FImSlateText : public FImSlateLeaf {
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

class IMSLATERUNTIME_API FImSlateCheckBox : public FImSlateLeaf {
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

class IMSLATERUNTIME_API FImSlateInputScalar : public FImSlateLeaf {
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
    virtual void End() override;
private:
    FString Label;
    float Value;
private:
    void OnValueChanged(float NewValue);
};

class IMSLATERUNTIME_API FImSlateInputText : public FImSlateLeaf {
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
    virtual void End() override;
private:
    FString Label;
    FString Text;
private:
    void OnTextChanged(const FText& NewText);
};

class IMSLATERUNTIME_API FImSlateInputInt : public FImSlateLeaf {
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
    virtual void End() override;
private:
    FString Label;
    int32 Value;
private:
    void OnValueChanged(int32 NewValue);
};

class IMSLATERUNTIME_API FImSlateInputVector : public FImSlateLeaf {
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
    virtual void End() override;
private:
    FString Label;
    FVector Value;
private:
    void OnSetPosition(float NewValue,ETextCommit::Type CommitInfo, int32 Index);
};

