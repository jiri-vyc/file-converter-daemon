#pragma once
#include "Includes.h"

/**
* Utilities for time values - unit converting functions.
*/
class TimeUtils {
public:
	static const int SECONDS = 1;
	static const int MILLISECONDS = 1000;
	static const int MICROSECONDS = 1000000;
	static const int NANOSECONDS = 1000000000;

	static double MilliToSeconds(double milliseconds){
		return milliseconds / TimeUtils::MILLISECONDS;
	}
	static double SecondsToMilli(double seconds){
		return seconds * TimeUtils::MILLISECONDS;
	}
	static double NanoToSeconds(double nanoseconds){
		return nanoseconds / TimeUtils::NANOSECONDS;
	}
	static double SecondsToNano(double seconds){
		return seconds * TimeUtils::NANOSECONDS;
	}
	static double SecondsToMicro(double seconds){
		return seconds * TimeUtils::MICROSECONDS;
	}
	static double MicroToSeconds(double microseconds){
		return microseconds / TimeUtils::MICROSECONDS;
	}

	#ifdef _WIN32
	/** Gets precise processor time in specified format, Windows systems */
	static float GetMyCPUTime(int format)
	{
		HANDLE hProcess;    // specifies the process of interest
		FILETIME lpCreationTime;    // when the process was created
		FILETIME lpExitTime;    // when the process exited
		FILETIME lpKernelTime;    // time the process has spent in kernel mode
		FILETIME lpUserTime;
		LARGE_INTEGER t1, t2;
		if (!format){
			format = TimeUtils::SECONDS;
		}


		hProcess = GetCurrentProcess();
		GetProcessTimes(hProcess, &lpCreationTime, &lpExitTime, &lpKernelTime, &lpUserTime);
		memcpy(&t1, &lpUserTime, sizeof(FILETIME));
		memcpy(&t2, &lpKernelTime, sizeof(FILETIME));
		return ((float)(t1.QuadPart + t2.QuadPart) * 100 / 1000000000 * format); // time in miliseconds
	}
	#else
	/** Gets precise processor time in specified format, Unix systems */
	static float GetMyCPUTime(int format)
	{
		return ((float)clock()/CLOCKS_PER_SEC * 100 / 100 * format); // time in specified format
	}
	#endif


	/**
	flat distribution over the range low .. high inclusive
	*/
	static int rngrandom(int low, int high) {
		int q = high - low + 1;
		return rand() % q + low;
	}
};