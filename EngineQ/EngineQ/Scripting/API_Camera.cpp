#include "API_Camera.hpp"

// This project
#include "ScriptEngine.hpp"
#include "EngineQ/Objects/Camera.hpp"


namespace EngineQ
{
	namespace Scripting
	{
		void API_Camera::API_GetUseCustomProjectionMatrix(const Object& cameraBase, bool& value)
		{
			auto& camera = static_cast<const Camera&>(cameraBase);

			value = camera.IsUsingCustomProjectionMatrix();
		}

		void API_Camera::API_SetUseCustomProjectionMatrix(Object& cameraBase, bool value)
		{
			auto& camera = static_cast<Camera&>(cameraBase);

			camera.SetUsingCustomProjectionMatrix(value);
		}
	
		void API_Camera::API_GetProjectionMatrix(Object& cameraBase, Math::Matrix4& value)
		{
			auto& camera = static_cast<Camera&>(cameraBase);

			value = camera.GetProjectionMatrix();
		}
		
		void API_Camera::API_GetCustomProjectionMatrix(const Object& cameraBase, Math::Matrix4& value)
		{
			auto& camera = static_cast<const Camera&>(cameraBase);

			value = camera.GetCustomProjectionMatrix();
		}

		void API_Camera::API_SetCustomProjectionMatrix(Object& cameraBase, const Math::Matrix4& value)
		{
			auto& camera = static_cast<Camera&>(cameraBase);

			camera.SetCustomProjectionMatrix(value);
		}
		
		void API_Camera::API_GetFieldOfView(const Object& cameraBase, float& value)
		{
			auto& camera = static_cast<const Camera&>(cameraBase);

			value = camera.GetFieldOfView();
		}

		void API_Camera::API_SetFieldOfView(Object& cameraBase, float value)
		{
			auto& camera = static_cast<Camera&>(cameraBase);

			camera.SetFieldOfView(value);
		}
			
		void API_Camera::API_GetNearDistance(const Object& cameraBase, float& value)
		{
			auto& camera = static_cast<const Camera&>(cameraBase);

			value = camera.GetNearDistance();
		}

		void API_Camera::API_SetNearDistance(Object& cameraBase, float value)
		{
			auto& camera = static_cast<Camera&>(cameraBase);

			camera.SetNewarDistance(value);
		}
			
		void API_Camera::API_GetFarDistance(const Object& cameraBase, float& value)
		{
			auto& camera = static_cast<const Camera&>(cameraBase);

			value = camera.GetFarDistance();
		}

		void API_Camera::API_SetFarDistance(Object& cameraBase, float value)
		{
			auto& camera = static_cast<Camera&>(cameraBase);

			camera.SetFarDistance(value);
		}

		void API_Camera::API_Register(ScriptEngine& scriptEngine)
		{
			scriptEngine.API_Register("EngineQ.Camera::API_GetUseCustomProjectionMatrix", API_GetUseCustomProjectionMatrix);
			scriptEngine.API_Register("EngineQ.Camera::API_SetUseCustomProjectionMatrix", API_SetUseCustomProjectionMatrix);
			scriptEngine.API_Register("EngineQ.Camera::API_GetProjectionMatrix", API_GetProjectionMatrix);
			scriptEngine.API_Register("EngineQ.Camera::API_GetCustomProjectionMatrix", API_GetCustomProjectionMatrix);
			scriptEngine.API_Register("EngineQ.Camera::API_SetCustomProjectionMatrix", API_SetCustomProjectionMatrix);
			scriptEngine.API_Register("EngineQ.Camera::API_GetFieldOfView", API_GetFieldOfView);
			scriptEngine.API_Register("EngineQ.Camera::API_SetFieldOfView", API_SetFieldOfView);
			scriptEngine.API_Register("EngineQ.Camera::API_GetNearDistance", API_GetNearDistance);
			scriptEngine.API_Register("EngineQ.Camera::API_SetNearDistance", API_SetNearDistance);
			scriptEngine.API_Register("EngineQ.Camera::API_GetFarDistance", API_GetFarDistance);
			scriptEngine.API_Register("EngineQ.Camera::API_SetFarDistance", API_SetFarDistance);
		}
	}
}