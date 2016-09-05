//
//  Author: Shervin Aflatooni
//

#ifndef WINDOW_H
#define WINDOW_H

#include <list>
#include <stdint.h>
#include <string>
#include "Util.h"
#include "Event.h"

class Window
{
public:
	Window(void);
	virtual ~Window(void);

	//
	virtual bool initialize(const std::string& name, int width, int height) = 0;
	virtual void destroy() = 0;

	int get_x() const;
	int get_y() const;
	int get_width() const;
	int get_height() const;

	virtual bool take_screen_shot(unsigned char* pixeldata) { return false; }

	virtual EGLNativeWindowType  get_native_window() const = 0;
	virtual EGLNativeDisplayType get_native_display() const = 0;

	virtual void message_loop() = 0;

	virtual void  push_event(Event event);
	bool          pop_event(Event *event);

	virtual void set_mouse_pos(int x, int y) = 0;
	virtual bool set_position(int x, int y) = 0;
	virtual bool resize(int width, int height) = 0;
	virtual void set_visible(bool isVisible) = 0;

	virtual void signal_test_event() = 0;
	bool did_test_event_fire();
protected:
	int mX;
	int mY;
	int mWidth;
	int mHeight;

	std::list<Event> mEvents;
};

#endif
