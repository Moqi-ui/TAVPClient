/*********************************************************
*
* @copyright 2021-2022,ʱ�����꣨C����All right reserved
*
* @author ����
*
* @date 2022��07��01��15:14:04
*
* @brief �ļ������� ����
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