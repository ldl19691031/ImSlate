#pragma once
#include "CoreMinimal.h"
#include <utility>

const float PROPERTY_LABEL_MIN_WIDTH = 200.0f;

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
