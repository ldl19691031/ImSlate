#pragma once

#include "CoreMinimal.h"

class UObject;
class UClass;
class IMSLATERUNTIME_API FImSlateWidgetBuilderInterface {
public:
    virtual void Begin();
    virtual void End();

    #define PREFIX virtual
    #define SUFFIX = 0
    #include "ImSlateFunctions.h"
    #undef PREFIX
    #undef SUFFIX
    
    TSharedPtr<class FImSlateContainer> CurrentContainer;

    virtual ~FImSlateWidgetBuilderInterface() {}
};