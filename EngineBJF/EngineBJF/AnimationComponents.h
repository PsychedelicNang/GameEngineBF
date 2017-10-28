#pragma once
#include <vector>

namespace AnimationComponents {
	struct Keyframe {
		double time;
		float joints[16];
	};

	struct AnimationClip {
		double duration;
		std::vector<Keyframe> frames;
	};
}