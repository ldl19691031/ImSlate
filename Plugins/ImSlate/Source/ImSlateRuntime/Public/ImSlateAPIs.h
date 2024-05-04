#pragma once

#include "CoreMinimal.h"

class UObject;
class UClass;

namespace ImSlate {
    IMSLATERUNTIME_API void Begin(const FString& Title);
    IMSLATERUNTIME_API void End();   
    
    #define PREFIX IMSLATERUNTIME_API
    #define SUFFIX 
    #include "ImSlateFunctions.h"
    #undef PREFIX
    #undef SUFFIX
}