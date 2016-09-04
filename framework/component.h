#ifndef ENGINE_COMPONENT_H
#define ENGINE_COMPONENT_H
#include "Util.h"
enum ComponentType
{
	EMPTY,
	TRANSFORM = 1 << 0,
	CAMERA = 1 << 1,
	CONTROLLER = 1 << 2,
	MODEL = 1 << 3,
	TEXTURE = 1 << 4,
	LIGHT = 1 << 5,
	RIGIDBODY = 1 << 6
};
class Component
{
public:
	Component(ComponentType type);
	const ComponentType getType() const;

private:
	ComponentType mType;
};

#endif // !ENGINE_COMPONENT_H
