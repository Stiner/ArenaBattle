// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/GameInstance.h"
#include "Engine/StreamableManager.h"
#include "WebConnection.h"
#include "ABGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class ARENABATTLE_API UABGameInstance : public UGameInstance
{
	GENERATED_BODY()
    
public:
    UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "WebService")
    class UWebConnection* WebConnection;
    
    UPROPERTY()
    class UWebConnection* WebConnectionNew;
    
    UPROPERTY()
    class UWebConnection* WebConnectionNew2;
    
    FStreamableManager AssetLoader;
    
public:
    UABGameInstance();
	
public:
    virtual void Init() override;
    
    UFUNCTION()
    void RequestTokenComplete(const FString& Token);
};
