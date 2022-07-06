/*********************************************************
*
* @copyright 2021-2022,时光坐标（C），All right reserved
*
* @author 曹落
*
* @date 2022年07月01日15:14:04
*
* @brief 文件管理器 单例
*
* @See
*
**********************************************************/


#pragma once
#include "../TAVPDataType.h"
#include "CoreMinimal.h"

/**
 *
 */

class TAVPS_API FTAVPFileManager
{
public:
	FTAVPFileManager();
	~FTAVPFileManager();

	static FTAVPFileManager* Get();
public:

	FString LoadFile(FString FileName);

	bool DeSerializeNdisConfig();

	TArray<FRenderNodeData> GetNodeDatas();

private:

	static FTAVPFileManager* TAVPFileManager;

	TArray<FRenderNodeData> T_NodeDatas;

};