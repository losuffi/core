#pragma once
#include"../common_def.h"
#include"event_dispatcher.h"

namespace Aurora3D
{
	struct EngineEvt
	{
		const static EventID FrameBegin = ID(CCDKModule::Engine, 1);
		const static EventID FrameEnd = ID(CCDKModule::Engine, 2);

		struct FrameBeginData
		{
			float delta_time;
			float total_time;
			unsigned total_frame;
		};
	};

}
