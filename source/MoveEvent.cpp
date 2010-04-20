#include "MoveEvent.h"


using namespace Balyoz;

MoveEvent::MoveEvent(GameUnit *gu, NxOgre::Vec3 pos){
	m_unit = gu;
	m_position = pos;
	m_type = MOVE_EVENT;
}
MoveEvent::~MoveEvent (){}

