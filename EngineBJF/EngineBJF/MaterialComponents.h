#pragma once
#include <array>
#include <vector>
#include <string>
#include <map>

struct alignas(16) float4 : std::array<float, 4> { using std::array<float, 4>::array;  };

namespace MaterialComponents {
	struct Material {
		enum properties { EMISSIVE = 0, AMBIENT, DIFFUSE, NORMAL, BUMP, TRANSPARENCY, DISPLACEMENT, VECTOR_DISPLACEMENT, SPECULAR, SHININESS, REFLECTION, COUNT };

		enum materialType { PHONG = 0, LAMBERT } m_materialType;

		struct properties_t {
			std::string filePath;	// "WasNotGiven" if there is not file path
			float4 value;			// any value which is -1 represents no valid value or N/A (meaing -1,-1,-1,.5f would represent the data type is a single floating point value)
		};
		std::map<properties, properties_t> m_mapPropValues;
		std::map<properties, properties_t>::iterator m_mapPropValuesIter;
	};
}