/*********************************************************
*
* @copyright 2021-2022,时光坐标（C），All right reserved
*
* @author 曹落
*
* @date 2022年06月30日17:25:00
*
* @brief 数据结构
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

	//在Map中使用自定义的结构体作为Key，需要对结构体做运算符“==”重载并实现一个GetTypeHash函数
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