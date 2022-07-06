/*********************************************************
*
* @copyright 2021-2022,ʱ�����꣨C����All right reserved
*
* @author ����
*
* @date 2022��06��30��17:25:00
*
* @brief ���ݽṹ
*
* @See
*
**********************************************************/


#pragma once
#include "CoreMinimal.h"

struct FRenderNodeData
{
	FRenderNodeData() {};

	FRenderNodeData(FString NodeName_, FString IPAddress_, FString CommandLine_, FString Params_)
		:NodeName(NodeName_),
		IPAddress(IPAddress_),
		CommandLine(CommandLine_),
		Params(Params_)
	{

	}

	FRenderNodeData(FString NodeName_, FString IPAddress_, FVector4 WindowsSize_)
		:NodeName(NodeName_),
		IPAddress(IPAddress_),
		WindowsSize(WindowsSize_)
	{

	}

	void SetParams(FString URL)
	{
		int x = WindowsSize.X;
		int y = WindowsSize.Y;
		int z = WindowsSize.Z;
		int w = WindowsSize.W;

		FString Param_ = FString::Printf(TEXT("-game -messaging -dc_cluster -nosplash -fixedseed -NoVerifyGC -noxrstereo -xrtrackingonly -RemoteControlIsHeadless -StageFriendlyName=%s -dc_cfg=\"%s\" -dx12 -dc_dev_mono -windowed -forceres WinX=%d WinY=%d ResX=%d ResY=%d -dc_node=%s Log=%s.log"), *NodeName, *URL, x, y, z, w, *NodeName, *NodeName);
		Params = Param_;
	}

	FString NodeName;

	FString IPAddress;

	FString CommandLine;

	FString Params;

	FVector4 WindowsSize;

	//��Map��ʹ���Զ���Ľṹ����ΪKey����Ҫ�Խṹ�����������==�����ز�ʵ��һ��GetTypeHash����
	friend inline bool operator==(const FRenderNodeData& A, const FRenderNodeData& B)
	{
		return A.NodeName == B.NodeName && A.IPAddress == B.IPAddress && A.CommandLine == B.CommandLine && A.Params == B.Params && A.WindowsSize == B.WindowsSize;
	}

	friend inline uint32 GetTypeHash(const FRenderNodeData& Node)
	{
		uint32 Hash = 0;

		Hash = HashCombine(Hash, GetTypeHash(Node.NodeName));
		Hash = HashCombine(Hash, GetTypeHash(Node.IPAddress));
		Hash = HashCombine(Hash, GetTypeHash(Node.CommandLine));
		Hash = HashCombine(Hash, GetTypeHash(Node.Params));
		Hash = HashCombine(Hash, GetTypeHash(Node.WindowsSize));

		return Hash;
	}

};