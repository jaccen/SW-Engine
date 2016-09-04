#include "component.h"




Component::Component(ComponentType type) : mType(type)
{

}

const ComponentType Component::getType() const
{
	return mType;
}
