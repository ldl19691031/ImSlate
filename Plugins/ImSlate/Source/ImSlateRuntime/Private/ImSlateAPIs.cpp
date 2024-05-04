#include "ImSlateAPIs.h"
#include "ImSlateManager.h"

void ImSlate::Begin(const FString& Title)
{
    UImSlateManager::GetChecked()->Begin(Title);
}

void ImSlate::End()
{
    UImSlateManager::GetChecked()->End();
}