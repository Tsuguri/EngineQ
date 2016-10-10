#include "SerializationRules.hpp"

#include <sstream>

#include "Serializer.hpp"
#include "Deserializer.hpp"

#include "../Math/Vector2.hpp"
#include "../Math/Vector3.hpp"
#include "../Math/Matrix4.hpp"
#include "../Math/Quaternion.hpp"

namespace EngineQ
{
	namespace Serialization
	{
		void SerializeValue(const std::string& value, Serializer& serializer, std::string& type, std::string& serializedValue)
		{
			serializedValue = value;
		}

		std::string DeserializeValue(Deserializer& deserializer, const std::string*)
		{
			return deserializer.GetValue();
		}


		void SerializeValue(int value, Serializer& serializer, std::string& type, std::string& serializedValue)
		{
			serializedValue = std::to_string(value);
		}

		int DeserializeValue(Deserializer& deserializer, const int*)
		{
			return std::stoi(deserializer.GetValue());
		}


		void SerializeValue(std::size_t value, Serializer& serializer, std::string& type, std::string& serializedValue)
		{
			serializedValue = std::to_string(value);
		}

		std::size_t DeserializeValue(Deserializer& deserializer, const std::size_t*)
		{
			std::size_t ret;
			std::stringstream stream;
			stream << deserializer.GetValue();
			stream >> ret;
			return ret;
		}


		void SerializeValue(bool value, Serializer& serializer, std::string& type, std::string& serializedValue)
		{
			std::stringstream stream;
			stream << value;
			serializedValue = stream.str();
		}

		bool DeserializeValue(Deserializer& deserializer, const bool*)
		{
			bool ret;
			std::stringstream stream;
			stream << deserializer.GetValue();
			stream >> ret;
			return ret;
		}


		void SerializeValue(float value, Serializer& serializer, std::string& type, std::string& serializedValue)
		{
			serializedValue = std::to_string(value);
		}

		float DeserializeValue(Deserializer& deserializer, const float*)
		{
			return std::stof(deserializer.GetValue());
		}


		void SerializeValue(Math::Vector3 value, Serializer& serializer, std::string& type, std::string& serializedValue)
		{
			serializer.StoreValue("X", &value.X);
			serializer.StoreValue("Y", &value.Y);
			serializer.StoreValue("Z", &value.Z);
		}

		Math::Vector3 DeserializeValue(Deserializer& deserializer, const Math::Vector3*)
		{
			Math::Vector3 ret;
			ret.X = deserializer.GetValue<Math::Real>("X");
			ret.Y = deserializer.GetValue<Math::Real>("Y");
			ret.Z = deserializer.GetValue<Math::Real>("Z");
			return ret;
		}


		void SerializeValue(Math::Quaternion value, Serializer& serializer, std::string& type, std::string& serializedValue)
		{
			serializer.StoreValue("W", &value.W);
			serializer.StoreValue("X", &value.X);
			serializer.StoreValue("Y", &value.Y);
			serializer.StoreValue("Z", &value.Z);
		}

		Math::Quaternion DeserializeValue(Deserializer& deserializer, const Math::Quaternion*)
		{
			Math::Quaternion ret;
			ret.W = deserializer.GetValue<Math::Real>("W");
			ret.X = deserializer.GetValue<Math::Real>("X");
			ret.Y = deserializer.GetValue<Math::Real>("Y");
			ret.Z = deserializer.GetValue<Math::Real>("Z");
			return ret;
		}


		void SerializeValue(Math::Matrix4 value, Serializer& serializer, std::string& type, std::string& serializedValue)
		{
			serializer.StoreValue("M00", &value.M00);
			serializer.StoreValue("M01", &value.M01);
			serializer.StoreValue("M02", &value.M02);
			serializer.StoreValue("M03", &value.M03);
			serializer.StoreValue("M10", &value.M10);
			serializer.StoreValue("M11", &value.M11);
			serializer.StoreValue("M12", &value.M12);
			serializer.StoreValue("M13", &value.M13);
			serializer.StoreValue("M20", &value.M20);
			serializer.StoreValue("M21", &value.M21);
			serializer.StoreValue("M22", &value.M22);
			serializer.StoreValue("M23", &value.M23);
			serializer.StoreValue("M30", &value.M30);
			serializer.StoreValue("M31", &value.M31);
			serializer.StoreValue("M32", &value.M32);
			serializer.StoreValue("M33", &value.M33);
		}

		Math::Matrix4 DeserializeValue(Deserializer& deserializer, const Math::Matrix4*)
		{
			Math::Matrix4 ret;
			ret.M00 = deserializer.GetValue<Math::Real>("M00");
			ret.M01 = deserializer.GetValue<Math::Real>("M01");
			ret.M02 = deserializer.GetValue<Math::Real>("M02");
			ret.M03 = deserializer.GetValue<Math::Real>("M03");
			ret.M10 = deserializer.GetValue<Math::Real>("M10");
			ret.M11 = deserializer.GetValue<Math::Real>("M11");
			ret.M12 = deserializer.GetValue<Math::Real>("M12");
			ret.M13 = deserializer.GetValue<Math::Real>("M13");
			ret.M20 = deserializer.GetValue<Math::Real>("M20");
			ret.M21 = deserializer.GetValue<Math::Real>("M21");
			ret.M22 = deserializer.GetValue<Math::Real>("M22");
			ret.M23 = deserializer.GetValue<Math::Real>("M23");
			ret.M30 = deserializer.GetValue<Math::Real>("M30");
			ret.M31 = deserializer.GetValue<Math::Real>("M31");
			ret.M32 = deserializer.GetValue<Math::Real>("M32");
			ret.M33 = deserializer.GetValue<Math::Real>("M33");
			return ret;
		}
	}
}