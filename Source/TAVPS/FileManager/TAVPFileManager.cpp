#include "TAVPFileManager.h"
#include "Runtime/Core/Public/HAL/PlatformFilemanager.h"
#include "Runtime/Core/Public/Misc/FileHelper.h"
#include "Runtime/Core/Public/Misc/Paths.h"
#include "Runtime/Json/Public/Serialization/JsonReader.h"


FTAVPFileManager* FTAVPFileManager::TAVPFileManager = nullptr;

FTAVPFileManager::FTAVPFileManager()
{

}
FTAVPFileManager::~FTAVPFileManager()
{

}


FTAVPFileManager* FTAVPFileManager::Get()
{
	if (!TAVPFileManager)
	{
		return TAVPFileManager = new FTAVPFileManager();
	}

	return TAVPFileManager;
}

FString FTAVPFileManager::LoadFile(FString FileName)
{
	FString Result;

	/*FString ProjectConfig = FPaths::ProjectConfigDir();

	FString FullFilepath = ProjectConfig + "Render_2node.ndisplay";

	if (FPaths::FileExists(FullFilepath))
	{
		const TCHAR* FileName_ = *FullFilepath;

		FFileHelper::LoadFileToString(Result, FileName_);
	}

	for (int i = 0; i < T_NodeDatas.Num(); i++)
	{
		T_NodeDatas[i].SetParams(FullFilepath);
	}*/

	return Result;
}

bool FTAVPFileManager::DeSerializeNdisConfig()
{
	FString Messages;

	FString ProjectConfigPath = FPaths::ProjectConfigDir();

	//FString EnginePaht = FPaths::EngineConfigDir();

	FString FullFilePath = ProjectConfigPath + "TAVPNdisConfig.ndisplay";

	if (!FPaths::FileExists(FullFilePath))
	{
		UE_LOG(LogTemp, Warning, TEXT("Ndisplay config path: %s , not Exist"), *FullFilePath);

		return false;
	}
	const TCHAR* FileName_ = *FullFilePath;

	FFileHelper::LoadFileToString(Messages, FileName_);

	/*-------------------*/

	T_NodeDatas.Empty();

	TSharedRef<TJsonReader<TCHAR>> Reader = FJsonStringReader::Create(Messages);

	TSharedPtr<FJsonObject> JsonData;

	if (!FJsonSerializer::Deserialize(Reader, JsonData))
	{
		return false;
	}

	TSharedPtr<FJsonValue> MainValue;// = JsonData->TryGetField(TEXT("nDisplay"));

	JsonData = JsonData->GetObjectField(TEXT("nDisplay"));

	FString EngineVersion = JsonData->GetStringField("version");

	JsonData = JsonData->GetObjectField(TEXT("cluster"))->GetObjectField(TEXT("nodes"));

	uint8 NodeNum = 15;


	for (int i = 0; i < NodeNum; i++)
	{
		TSharedPtr<FJsonValue> NodeValue;

		TSharedPtr<FJsonObject> NodeObject;

		FString NodeName = FString::Printf(TEXT("Node_%d"), i);

		NodeValue = JsonData->TryGetField(NodeName);

		if (!NodeValue.IsValid())
		{
			break;
		}
		NodeObject = NodeValue->AsObject();

		FString host_IP = NodeObject->GetStringField(TEXT("host"));

		NodeValue = NodeObject->TryGetField(TEXT("window"));

		NodeObject = NodeValue->AsObject();

		FVector4 win;

		win.X = NodeObject->GetIntegerField(TEXT("x"));
		win.Y = NodeObject->GetIntegerField(TEXT("y"));
		win.Z = NodeObject->GetIntegerField(TEXT("w"));
		win.W = NodeObject->GetIntegerField(TEXT("h"));

		FRenderNodeData NodeData = FRenderNodeData(NodeName, host_IP, win);

		T_NodeDatas.Add(NodeData);
	}

	for (int i = 0; i < T_NodeDatas.Num(); i++)
	{
		T_NodeDatas[i].SetParams(FullFilePath);
	}

	return true;
}

TArray<FRenderNodeData> FTAVPFileManager::GetNodeDatas()
{

	return T_NodeDatas;
}