#pragma once
#include <vector>
#include <string>
namespace AnimationComponents {
	struct SkeletonJoints {
		float globalTransformArray[16];
		//float localTransformArray[16];	// Inverse bindpose
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

	struct BindPose {
		std::vector<SkeletonJoints> joints;
		struct BindPoseJoints {
			float globalTransformArray[16];
			int parentIndex;
			std::string jointName;
		};
	};
}


// for changing coordinate system:
// ...for any positions: pos.x = -pos.x (ALL POSITIONS)
// ...axes: yAxis.x = -yAxis.x, zAxis.x = -zAxis.x, xAxis.y = -xAxis.y, xAxis.z = -xAxis.z
// ...also change uv values: uv.v = 1 - uv.v