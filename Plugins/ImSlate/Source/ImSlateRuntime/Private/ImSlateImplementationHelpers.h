#pragma once
#define IMPL_API_RET_PARAM1(FunctionName, ReturnType, ParamType1, ParamName1) \
    ReturnType ImSlate::FunctionName(ParamType1 ParamName1)\
    {\
        if (UImSlateManager::WidgetBuilder != nullptr)\
        {\
            return UImSlateManager::WidgetBuilder->FunctionName(ParamName1);\
        }\
        return ReturnType{};\
    }

#define IMPL_API_PARAM1(FuncionName, ParamType1, ParamName1) \
    void ImSlate::FuncionName(ParamType1 ParamName1)\
    {\
        if (UImSlateManager::WidgetBuilder != nullptr)\
        {\
            UImSlateManager::WidgetBuilder->FuncionName(ParamName1);\
        }\
    }

#define IMPL_API_PARAM2(FuncionName, ParamType1, ParamName1, ParamType2, ParamName2) \
    void ImSlate::FuncionName(ParamType1 ParamName1, ParamType2 ParamName2)\
    {\
        if (UImSlateManager::WidgetBuilder != nullptr)\
        {\
            UImSlateManager::WidgetBuilder->FuncionName(ParamName1, ParamName2);\
        }\
    }

#define IMPL_API_PARAM3(FuncionName, ParamType1, ParamName1, ParamType2, ParamName2, ParamType3, ParamName3) \
    void ImSlate::FuncionName(ParamType1 ParamName1, ParamType2 ParamName2, ParamType3 ParamName3)\
    {\
        if (UImSlateManager::WidgetBuilder != nullptr)\
        {\
            UImSlateManager::WidgetBuilder->FuncionName(ParamName1, ParamName2, ParamName3);\
        }\
    }

#define IMPL_API_PARAM4(FuncionName, ParamType1, ParamName1, ParamType2, ParamName2, ParamType3, ParamName3, ParamType4, ParamName4) \
    void ImSlate::FuncionName(ParamType1 ParamName1, ParamType2 ParamName2, ParamType3 ParamName3, ParamType4 ParamName4)\
    {\
        if (UImSlateManager::WidgetBuilder != nullptr)\
        {\
            UImSlateManager::WidgetBuilder->FuncionName(ParamName1, ParamName2, ParamName3, ParamName4);\
        }\
    }

#define IMPL_API_PARAM5(FuncionName, ParamType1, ParamName1, ParamType2, ParamName2, ParamType3, ParamName3, ParamType4, ParamName4, ParamType5, ParamName5) \
    void ImSlate::FuncionName(ParamType1 ParamName1, ParamType2 ParamName2, ParamType3 ParamName3, ParamType4 ParamName4, ParamType5 ParamName5)\
    {\
        if (UImSlateManager::WidgetBuilder != nullptr)\
        {\
            UImSlateManager::WidgetBuilder->FuncionName(ParamName1, ParamName2, ParamName3, ParamName4, ParamName5);\
        }\
    }
