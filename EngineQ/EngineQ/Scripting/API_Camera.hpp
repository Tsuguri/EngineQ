#ifndef ENGINEQ_SCRIPTING_API_CAMERA_HPP
#define ENGINEQ_SCRIPTING_API_CAMERA_HPP

#include "Types.hpp"
#include <Math/Types.hpp>
#include "../Objects/Types.hpp"

namespace EngineQ
{
	namespace Scripting
	{
		class API_Camera
		{
		public:
			static void API_GetUseCustomProjectionMatrix(const Object& cameraBase, bool& value);
			static void API_SetUseCustomProjectionMatrix(Object& cameraBase, bool value);
				   
			static void API_GetProjectionMatrix(Object& cameraBase, Math::Matrix4& value);
				   
			static void API_GetCustomProjectionMatrix(const Object& cameraBase, Math::Matrix4& value);
			static void API_SetCustomProjectionMatrix(Object& cameraBase, const Math::Matrix4& value);
				   
			static void API_GetFieldOfView(const Object& cameraBase, float& value);
			static void API_SetFieldOfView(Object& cameraBase, float value);
				   
			static void API_GetNearDistance(const Object& cameraBase, float& value);
			static void API_SetNearDistance(Object& cameraBase, float value);
				   
			static void API_GetFarDistance(const Object& cameraBase, float& value);
			static void API_SetFarDistance(Object& cameraBase, float value);

			static void API_Register(ScriptEngine& scriptEngine);
		};
	}
}

#endif // !ENGINEQ_SCRIPTING_API_CAMERA_HPP
