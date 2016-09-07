
#ifdef _WIN32_WCE
#include <winbase.h>
#endif

#ifdef __SYMBIAN32__
#include <e32std.h>
#elif _WIN32
#include <time.h>
#else
#include <time.h>
#include <sys/time.h>
#endif

#ifdef __IPHONE_NA
//#include "Shell.h"
#endif


#include "Timer.h"

u32 GameTime::lastTime = 0;
u32 GameTime::currentTime = 0;
u32 GameTime::beginTime = 0;
f64 GameTime::useTime = 0.f;
//------------------
u32 GameTime::useTimeStable = 0;
f32 GameTime::timeRate = 1.f;
u32 GameTime::dtStable = 0;
f32 GameTime::dtFloatStable = 0;

u32 GameTime::pos = 0;
u32 GameTime::dt = 0;
f32 GameTime::dtfloat = 0;
u32 GameTime::dtTrue = 0;
f32 GameTime::dtfloatTrue = 0;
u32 GameTime::times[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
s64 GameTime::dayTime = 0;

#ifdef USE_FOR_TOOL_EDITOR
b2 GameTime::mflagTimePause = false; //add by dcg at 2013.8.23
#endif

u32 GameTime::getTime() {
#ifdef USE_FOR_TOOL_EDITOR
	if (GameTime::mflagTimePause) {
		return 0;
	}//add by dcg at 2013.8.23
#endif
	u32 time = getTimeNative();
	//    if (math::equalZero(timeRate)) {
	//        time = currentTime;
	//    }
	return time;
}

u32 GameTime::getTimeNative() {
#ifdef __SYMBIAN32__
	static GLboolean init = GL_TRUE;
	static TTime startTime;
	TTime actualTime;

	if (init) {
		startTime.HomeTime();
		init = GL_FALSE;
	}
	actualTime.HomeTime();

	return (GLuint)(actualTime.MicroSecondsFrom(startTime).Int64() / 1000);
#elif _WIN32_WCE
	static GLboolean init = GL_TRUE;
	static FILETIME startTime;
	FILETIME actualTime;
	SYSTEMTIME time;

	if (init) {
		GetSystemTime(&time);
		SystemTimeToFileTime(&time, &startTime);

		init = GL_FALSE;
	}
	GetSystemTime(&time);
	SystemTimeToFileTime(&time, &actualTime);

	return (GLuint)((*(GLulong*)& actualTime) / 100000 - (*(GLulong*)& startTime) / 100000);
	//#elif __IPHONE_NA
	//
	//    return (GLuint) (Shell_getCurrentTime()*1000);
#elif WIN32
	time_t clock;
	struct tm tm;
	SYSTEMTIME wtm;
	GetLocalTime(&wtm);
	tm.tm_year = wtm.wYear - 1900;
	tm.tm_mon = wtm.wMonth - 1;
	tm.tm_mday = wtm.wDay;
	tm.tm_hour = wtm.wHour;
	tm.tm_min = wtm.wMinute;
	tm.tm_sec = wtm.wSecond;
	tm.tm_isdst = -1;
	clock = mktime(&tm);
	dayTime = (s64)clock * 1000 + wtm.wMilliseconds;
	static s64 bTime = dayTime;
	return (u32)(dayTime - bTime);
#else
	static struct timeval tv;
	gettimeofday(&tv, NULL);
	dayTime = (s64)tv.tv_sec * 1000 + tv.tv_usec / 1000;
	static s64 bTime = dayTime;
	return (u32)(dayTime - bTime);
	//     static struct timespec tv;
	//    clock_gettime(&tv,NULL);
	//    dayTime = (s64)tv.tv_sec * 1000 + tv.tv_usec/1000;
	//    static s64 bTime = dayTime;`
	//    return (GLuint)(dayTime - bTime);
#endif
}

u32 GameTime::getTimeDelta() {
	static bool reset = true;
	if (reset) {
		lastTime = getTime();
		currentTime = lastTime;
		beginTime = lastTime;
		reset = false;
	}
	else {
		lastTime = currentTime;
		currentTime = getTime();
		dtTrue = currentTime - lastTime;
		useTimeStable += dtTrue;
		useTime += dtTrue * timeRate;
	}
	times[pos & 7] = dtTrue;
	pos++;
	dtStable = ((times[0] + times[1] + times[2] + times[3] + times[4] +
		times[5] + times[6] + times[7]) * timeArg()) >> 10;
	if (dtStable >= 100) {
		dtStable = 100;
	}
	dt = dtStable * timeRate;
	dtfloat = utilToFloatTime(dt);
	dtTrue *= timeRate;
	dtfloatTrue = utilToFloatTime(dtTrue);
	dtFloatStable = utilToFloatTime(dtStable);
	return dt;
}

u32 GameTime::getTimeDeltaConst() {
	return dt;
}

u32 GameTime::getTimeDeltaConstStable() {
	return dtStable;
}

f32 GameTime::getTimeDeltaConstf(){
	return dtfloat;
}

f32 GameTime::getTimeDeltaConstfStable(){
	return dtFloatStable;
}

u32 GameTime::getUseTime() {
	return (u32)useTime;
}

u32 GameTime::getUseTimeStable() {
	return useTimeStable;
}

void GameTime::setTimeRate(f32 rate) {
	if (rate < 0) {
		rate = 0;
	}
	timeRate = rate;
}



s64 GameTime::getDayTime() {
	return dayTime;
}

u32 GameTime::getTimeTrueDeltaConst() {
	return dtTrue;
}

f32 GameTime::getTimeTrueDeltaConstf() {
	return dtfloatTrue;
}
