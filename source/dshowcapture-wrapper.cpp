#include "../dshowcapture-wrapper.h"
#include <string>
#include <vector>
#include <codecvt>
#include <comdef.h>
#include <comutil.h>

DShow::Device device;

char* wchar_t_to_char(const wchar_t* str) {
	auto size = WideCharToMultiByte(CP_UTF8, 0, str, -1, NULL, 0, NULL, NULL); //size =wcslen(deviceName)+1=6
	char *result = (char*)malloc(size * sizeof(char)); //不需要 result = (char*)malloc(size*sizeof(char)+1);
	WideCharToMultiByte(CP_UTF8, 0, str, -1, result, size, NULL, NULL);
	return result;
}

std::string wstringToUtf8(const std::wstring& str)
{
	std::wstring_convert<std::codecvt_utf8<wchar_t> > strCnv;
	return strCnv.to_bytes(str);
}

std::wstring utf8ToWstring(const std::string& str)
{
	std::wstring_convert< std::codecvt_utf8<wchar_t> > strCnv;
	return strCnv.from_bytes(str);
}

bool Init()
{
	if (!isInit) {
		HRESULT hr;
		// 初始化COM  
		hr = CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED);
		if (FAILED(hr)) {
			printf("Init error!\n");
			return false;
		}
		isInit = 1;
	}
	return true;
}

TVideoDevice* GetVideoInputDevices(int32_t* count)
{
	if (!Init()) {
		return nullptr;
	}

	videoDeviceCount = 0;

	std::vector<DShow::VideoDevice> list;
	if (!device.EnumVideoDevices(list)) {
		return nullptr;
	}

	for (const auto &it : list)
	{
		TVideoDevice* tVideoDevice = &videoDevices[videoDeviceCount];
		strcpy_s(tVideoDevice->name, MAX_NAME_LENGTH, wstringToUtf8(it.name).c_str());
		strcpy_s(tVideoDevice->path, MAX_NAME_LENGTH, wstringToUtf8(it.path).c_str());
		tVideoDevice->audioAttached = it.audioAttached;
		tVideoDevice->separateAudioFilter = it.separateAudioFilter;

		tVideoDevice->capsCount = 0;
		for (const auto &cap : it.caps)
		{
			TVideoInfo* tCap = &(tVideoDevice->caps[tVideoDevice->capsCount]);
			tCap->minCX = cap.minCX;
			tCap->minCY = cap.minCY;
			tCap->maxCX = cap.maxCX;
			tCap->maxCY = cap.maxCY;
			tCap->granularityCX = cap.granularityCX;
			tCap->granularityCY = cap.granularityCY;
			tCap->minInterval = cap.minInterval;
			tCap->maxInterval = cap.maxInterval;
			tCap->format = (TVideoFormat)cap.format;
			tVideoDevice->capsCount++;
		}
		videoDeviceCount++;
	}

	if (count) {
		*count = videoDeviceCount;
	}
	return videoDevices;
}

TAudioDevice* GetAudioInputDevices(int32_t* count)
{
	if (!Init()) {
		return nullptr;
	}

	audioDeviceCount = 0;

	std::vector<DShow::AudioDevice> list;
	if (!device.EnumAudioDevices(list)) {
		return nullptr;
	}

	for (const auto &it : list)
	{
		TAudioDevice* tAudioDevice = &audioDevices[audioDeviceCount];
		strcpy_s(tAudioDevice->name, MAX_NAME_LENGTH, wstringToUtf8(it.name).c_str());
		strcpy_s(tAudioDevice->path, MAX_NAME_LENGTH, wstringToUtf8(it.path).c_str());

		tAudioDevice->capsCount = 0;
		for (const auto &cap : it.caps)
		{
			bool isExists = false;
			for (uint32_t i = 0; i < tAudioDevice->capsCount; i++) {
				TAudioInfo* tmp = &(tAudioDevice->caps[i]);
				if (tmp->format == (TAudioFormat)cap.format && tmp->minChannels == cap.minChannels && tmp->minSampleRate == cap.minSampleRate) {
					isExists = true;
					break;
				}
			}
			if (isExists) {
				break;
			}
			TAudioInfo* tCap = &(tAudioDevice->caps[tAudioDevice->capsCount]);
			tCap->minChannels = cap.minChannels;
			tCap->maxChannels = cap.maxChannels;
			tCap->channelsGranularity = cap.channelsGranularity;
			tCap->minSampleRate = cap.minSampleRate;
			tCap->maxSampleRate = cap.maxSampleRate;
			tCap->sampleRateGranularity = cap.sampleRateGranularity;
			tCap->format = (TAudioFormat)cap.format;
			tAudioDevice->capsCount++;
		}
		audioDeviceCount++;
	}

	if (count) {
		*count = audioDeviceCount;
	}
	return audioDevices;
}