// Fill out your copyright notice in the Description page of Project Settings.


#include "Examples/ImSlateGameModeExample.h"
#include "ImSlateRuntime.h"
#include "ImSlateSimpleEditorWindow.h"
#include "Materials/Material.h"

AImSlateGameModeExample::AImSlateGameModeExample()
{
    PrimaryActorTick.bStartWithTickEnabled = true;
    PrimaryActorTick.bCanEverTick = true;
}

void AImSlateGameModeExample::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    
    static int32 counter = 0;

    ImSlate::Begin("ImSlate Example");
    {
        static bool showButton = false;
        ImSlate::CheckBox("Show Button", showButton);
        if (showButton)
        {
            if (ImSlate::Button("Click Me"))
            {
                counter ++;        
            }
        }
        ImSlate::Text(FString::Printf(TEXT("Counter: %d"), counter));

        static float scalarValue = 1024.0f;
        ImSlate::InputScalar("Scalar Value", scalarValue);

        static FString textValue = "Hello World!";
        ImSlate::InputText("Text Value", textValue);

        static int32 intValue = 256;
        ImSlate::InputInt("Int Value", intValue);

        static FVector vectorValue = FVector::ZeroVector;
        ImSlate::InputVector("Vector Value", vectorValue);

        static UObject* materialValue = nullptr;
        ImSlate::InputAsset("Material Value", materialValue, UMaterial::StaticClass());
    }
    ImSlate::End();
}

static FImSlateSimpleEditorWindow ExampleWindow(
    []()
    {
        static int32 counter = 0;
        ImSlate::Begin("Simple Editor Window Example");
        {
            ImSlate::Text(FString::Printf(TEXT("Counter: %d"), counter));
            if (ImSlate::Button("Click Me"))
            {
                counter ++;
            }
        }
        ImSlate::End();
    }
);
