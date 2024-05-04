#pragma once
#include "CoreMinimal.h"
#include "ImSlateManager.h"

class FImSlateWidgetBuilder : public FImSlateWidgetBuilderInterface {
public:
    #define PREFIX virtual
    #define SUFFIX override
    #include "ImSlateFunctions.h"
    #undef PREFIX
    #undef SUFFIX
};