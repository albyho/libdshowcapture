#pragma once

#include "_exports.h"
#include "dshowcapture.hpp"

#define MAX_NAME_LENGTH		256
#define MAX_PATH_LENGTH		512
#define MAX_DEVICE			10
#define MAX_CAPS			20

#pragma pack(push,1)

enum class TVideoFormat : int32_t {
	AnyVideo,
	UnknownVideo,

	/* raw formats */
	ARGB = 100,
	XRGB,

	/* planar YUV formats */
	I420 = 200,
	NV12,
	YV12,
	Y800,

	/* packed YUV formats */
	YVYU = 300,
	YUY2,
	UYVY,
	HDYC,

	/* encoded formats */
	MJPEG = 400,
	H264,
};

enum class TAudioFormat : int32_t {
	AnyAudio,
	UnknownAudio,

	/* raw formats */
	Wave16bit = 100,
	WaveFloat,

	/* encoded formats */
	AAC = 200,
	AC3,
	MPGA, /* MPEG 1 */
};

struct TVideoInfo {
	int32_t minCX, minCY;					// ��С�ֱ��ʣ�����
	int32_t maxCX, maxCY;					// ���ֱ��ʣ�����
	int32_t granularityCX, granularityCY;	// ���ȣ�
	int64_t minInterval, maxInterval;		// ֡ʱ������λ 100ns
	TVideoFormat format;					// ��Ƶ��ʽ
};

struct TAudioInfo {
	int32_t minChannels, maxChannels;		// ��С�����ͨ����
	int32_t channelsGranularity;			// ͨ�����ȣ�
	int32_t minSampleRate, maxSampleRate;	// ��С����������
	int32_t sampleRateGranularity;			// ���������ȣ�		
	TAudioFormat format;					// ��Ƶ��ʽ
};

struct TDeviceId {
	char name[MAX_NAME_LENGTH];
	char path[MAX_PATH_LENGTH];
};

struct TVideoDevice : TDeviceId {
	uint8_t audioAttached = 0;
	uint8_t separateAudioFilter = 0;
	uint32_t capsCount = 0;
	TVideoInfo caps[MAX_CAPS];
};

struct TAudioDevice : TDeviceId {
	uint32_t capsCount = 0;
	TAudioInfo caps[MAX_CAPS];
};

#pragma pack(pop)

uint8_t isInit = 0;
uint32_t videoDeviceCount = 0;
uint32_t audioDeviceCount = 0;
TVideoDevice videoDevices[MAX_DEVICE];
TAudioDevice audioDevices[MAX_DEVICE];

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

	DSHOWWRAPPER_API TVideoDevice* GetVideoInputDevices(int32_t* count);

	DSHOWWRAPPER_API TAudioDevice* GetAudioInputDevices(int32_t* count);

#ifdef __cplusplus
}
#endif // __cplusplus