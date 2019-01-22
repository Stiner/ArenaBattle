// Fill out your copyright notice in the Description page of Project Settings.

#include "WebService.h"
#include "WebConnection.h"

DEFINE_LOG_CATEGORY(WebConnection);

UWebConnection::UWebConnection()
{
    UE_LOG(LogClass, Warning, TEXT("%s"), TEXT("WebConnection Contructor Called."));
    Host = TEXT("localhost:8000");
    URI = TEXT("/");
}

void UWebConnection::RequestToken(const FString& UserID)
{
    UE_LOG(WebConnection, Warning, TEXT("Reqeust Token call."));
    
    //TokenCompleteDelegate.ExecuteIfBound(TEXT("0LCJydGkiOiI2a3NjVE9pTUNESVZWM05qVTIyUnlTIn0.VJyMOicM"));
    TokenCompleteDelegate.Broadcast(TEXT("0LCJydGkiOiI2a3NjVE9pTUNESVZWM05qVTIyUnlTIn0.VJyMOicM"));
}
