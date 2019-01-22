// Fill out your copyright notice in the Description page of Project Settings.

#include "ArenaBattle.h"
#include "ABGameInstance.h"

UABGameInstance::UABGameInstance()
{
    AB_LOG(Warning, TEXT("Arena Battle Game Instance Contructor START."));
    WebConnection = CreateDefaultSubobject<UWebConnection>(TEXT("MyWebConnection"));
    AB_LOG(Warning, TEXT("Arena Battle Game Instance Contructor END."));
}

void UABGameInstance::Init()
{
    Super::Init();
    
    AB_LOG_CALLONLY(Warning);

    // [1-6]
    UClass* classInfo1 = WebConnection->GetClass();
    UClass* classInfo2 = UWebConnection::StaticClass();
    
    if (classInfo1 == classInfo2)
    {
        AB_LOG(Warning, TEXT("classInfo1 is same with classInfo2."));
    }
    
    for (TFieldIterator<UProperty> it(classInfo1); it; ++it)
    {
        AB_LOG(Warning, TEXT("Field : %s, Type : %s"), *it->GetName(), *it->GetClass()->GetName());
        UStrProperty* strProp = FindField<UStrProperty>(classInfo1, *it->GetName());
        
        if (strProp)
        {
            AB_LOG(Warning, TEXT("Value = %s"), *strProp->GetPropertyValue_InContainer(WebConnection));
        }
    }
    
    for (const auto& Entry : classInfo1->NativeFunctionLookupTable)
    {
        AB_LOG(Warning, TEXT("Function = %s"), *Entry.Name.ToString());
        UFunction* func1 = classInfo1->FindFunctionByName(Entry.Name);
        if (func1->ParmsSize == 0)
        {
            WebConnection->ProcessEvent(func1, NULL);
        }
    }
    
    // [1-7]
    TArray<UObject*> DefaultSubobjects;
    GetDefaultSubobjects(DefaultSubobjects);
    for (const auto& Entry : DefaultSubobjects)
    {
        AB_LOG(Warning, TEXT("DefaultSubobject : %s"), *Entry->GetClass()->GetName());
        AB_LOG(Warning, TEXT("Outer of DefaultSubobject : %s"), *Entry->GetOuter()->GetClass()->GetName());
    }
    
    WebConnectionNew = NewObject<UWebConnection>(this);
    AB_LOG(Warning, TEXT("Outer of NewObject : %s"), *WebConnectionNew->GetOuter()->GetClass()->GetName());
    
    
    UWorld* currentWorld = GetWorld();
    for (const auto& Entry : FActorRange(currentWorld))
    {
        AB_LOG(Warning, TEXT("Actor : %s"), *Entry->GetName());
        TArray<UObject*> components;
        Entry->GetDefaultSubobjects(components);
        for (const auto& CEntry : components)
        {
            AB_LOG(Warning, TEXT(" -- Component : %s"), *CEntry->GetName());
        }
    }
    
    for (TActorIterator<AStaticMeshActor> It(currentWorld); It; ++It)
    {
        AB_LOG(Warning, TEXT("StaticMesh Actor : %s"), *It->GetName());
    }
    
    WebConnection->Host = TEXT("localhost");
    WebConnectionNew->Host = TEXT("127.0.0.1");
    
    for (TObjectIterator<UWebConnection> It; It; ++It)
    {
        UWebConnection* conn = *It;
        AB_LOG(Warning, TEXT("WebConnection Object Host : %s"), *conn->Host);
    }
    
    // [1-11]
    //WebConnection->TokenCompleteDelegate.BindUObject(this, &UABGameInstance::RequestTokenComplete);
    WebConnection->TokenCompleteDelegate.AddDynamic(this, &UABGameInstance::RequestTokenComplete);
    WebConnection->RequestToken(TEXT("destiny"));
    
    // [1-12]
//    WebConnectionNew2 = NewObject<UWebConnection>(this);
//    WebConnectionNew2->Host = TEXT("127.0.0.1");
//    WebConnectionNew2->URI = TEXT("/");
//    
//    FString FullPath = FString::Printf(TEXT("%s%s"), *FPaths::GameSavedDir(), TEXT("WebConnection.txt"));
//    FArchive* ArWriter = IFileManager::Get().CreateFileWriter(*FullPath);
//    if (ArWriter)
//    {
//        //*ArWriter << WebConnectionNew2->Host;
//        //*ArWriter << WebConnectionNew2->URI;
//        *ArWriter << *WebConnectionNew2;
//        
//        ArWriter->Close();
//        delete ArWriter;
//        ArWriter = NULL;
//    }
//    
//    TSharedPtr<FArchive> FileReader = MakeShareable(IFileManager::Get().CreateFileReader(*FullPath));
//    if (FileReader.IsValid())
//    {
//        //FString Host;
//        //FString URI;
//        //*FileReader.Get() << Host;
//        //*FileReader.Get() << URI;
//        //FileReader->Close();
//        //AB_LOG(Warning, TEXT("WebConnection : Host %s, URI %s"), *Host, *URI);
//        
//        UWebConnection* WebConnectionFromFile = NewObject<UWebConnection>(this);
//        *FileReader.Get() << *WebConnectionFromFile;
//        FileReader->Close();
//        AB_LOG(Warning, TEXT("Webconnection From File : Host %s, URI %s"), *WebConnectionFromFile->Host, *WebConnectionFromFile->URI);
//    }
    
    // [1-12]
    FString PackageName = TEXT("/Temp/SavedWebConnection");
    UPackage* NewPackage = CreatePackage(nullptr, *PackageName);
    WebConnectionNew2 = NewObject<UWebConnection>(NewPackage);
    FString PackageFileName = FPackageName::LongPackageNameToFilename(PackageName, FPackageName::GetAssetPackageExtension());
    
    WebConnectionNew2->Host = TEXT("127.0.0.1");
    WebConnectionNew2->URI = TEXT("/");
    if (UPackage::SavePackage(NewPackage, WebConnectionNew2, RF_Standalone, *PackageFileName))
    {
        UPackage* SavedPackage = ::LoadPackage(NULL, *PackageFileName, LOAD_None);
        TArray<UObject*> ObjectsInPackage;
        GetObjectsWithOuter(SavedPackage, ObjectsInPackage, false);
        for (const auto& EachObject : ObjectsInPackage)
        {
            UWebConnection* WebConnectionFromFile = Cast<UWebConnection>(EachObject);
            if (WebConnectionFromFile)
            {
                AB_LOG(Warning, TEXT("WebConnection From File : Host %s, URI %s"), *WebConnectionFromFile->Host, *WebConnectionFromFile->URI);
            }
        }
    }
}

void UABGameInstance::RequestTokenComplete(const FString& Token)
{
    AB_LOG(Warning, TEXT("Token : %s"), *Token);
}
