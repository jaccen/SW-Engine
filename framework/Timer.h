#ifndef ES3D_GAMETIME_H_
#define ES3D_GAMETIME_H_
#include "Util.h"
/**
* This class delivers the elapsed game time.
*/
class GameTime {
private:
	static u32 lastTime;
	static u32 currentTime;
	static u32 beginTime;
	static f64 useTime;

	static u32 times[8];
	static u32 pos;
	static u32 dt;
	static f32 dtfloat;
	static u32 dtTrue;
	static f32 dtfloatTrue;
	static u8 _timeArg;
	static s64 dayTime;
public:
	static u32 getTimeDelta();
	static u32 getTime();
	static s64 getDayTime();
	static u32 getTimeDeltaConst();
	static f32 getTimeDeltaConstf();
	static u32 getTimeTrueDeltaConst();
	static f32 getTimeTrueDeltaConstf();

	static u32 getUseTime();
private:
	static void timeArg(u8 v){ _timeArg = v; }
	static u8 timeArg(){ return _timeArg; }
public:
	inline static f32 utilToFloatTime(u32 t_time)
	{
		return 0.001f * t_time;
	}

	static s64 getTimeOfDay(){
		return dayTime;
	}


	static b2 illegalChanged();
#ifdef USE_FOR_TOOL_EDITOR
	static b2 mflagTimePause;
#endif
	//加速
public:
	static u32 getUseTimeStable();
	static u32 getTimeDeltaConstStable();
	static f32 getTimeDeltaConstfStable();
	static void setTimeRate(f32 rate);
	static f32 getTimeRate() {
		return timeRate;
	}
	static s32 getTimeModify() {
		return useTime - useTimeStable;
	}

private:
	static u32 getTimeNative();
	static f32 timeRate;
	//-----不受加速暂停等影响的时间------
	static u32 useTimeStable;
	static u32 dtStable;
	static f32 dtFloatStable;
};

inline
void sleep(s32 stime) {
#ifdef _WIN32
	Sleep(stime);
#else
	usleep(stime * 1000);
#endif
}


#endif /*ES3D_GAMETIME_H_*/
