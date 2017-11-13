#pragma once
#include <vector>
#include <string>
namespace AnimationComponents {
	struct SkeletonJoints {
		float globalTransformArray[16];
		float globalTransform4x4[4][4];
		/*float localTransformArray[16];
		float localTransform4x4[4][4];*/
		int parentIndex;
		std::string jointName;
	};

	struct Keyframe {
		double time;
		std::vector<SkeletonJoints> joints;
	};

	struct AnimationClip {
		double duration;
		std::vector<Keyframe> frames;
	};
}

// for changing coordinate system:
// ...for any positions: pos.x = -pos.x (ALL POSITIONS)
// ...axes: yAxis.x = -yAxis.x, zAxis.x = -zAxis.x, xAxis.y = -xAxis.y, xAxis.z = -xAxis.z
// ...also change uv values: uv.v = 1 - uv.v