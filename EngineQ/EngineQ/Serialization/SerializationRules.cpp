#include "SerializationRules.hpp"

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
			serializer.StoreValue("m00", &value.m00);
			serializer.StoreValue("m01", &value.m01);
			serializer.StoreValue("m02", &value.m02);
			serializer.StoreValue("m03", &value.m03);
			serializer.StoreValue("m10", &value.m10);
			serializer.StoreValue("m11", &value.m11);
			serializer.StoreValue("m12", &value.m12);
			serializer.StoreValue("m13", &value.m13);
			serializer.StoreValue("m20", &value.m20);
			serializer.StoreValue("m21", &value.m21);
			serializer.StoreValue("m22", &value.m22);
			serializer.StoreValue("m23", &value.m23);
			serializer.StoreValue("m30", &value.m30);
			serializer.StoreValue("m31", &value.m31);
			serializer.StoreValue("m32", &value.m32);
			serializer.StoreValue("m33", &value.m33);
		}

		Math::Matrix4 DeserializeValue(Deserializer& deserializer, const Math::Matrix4*)
		{
			Math::Matrix4 ret;
			ret.m00 = deserializer.GetValue<Math::Real>("m00");
			ret.m01 = deserializer.GetValue<Math::Real>("m01");
			ret.m02 = deserializer.GetValue<Math::Real>("m02");
			ret.m03 = deserializer.GetValue<Math::Real>("m03");
			ret.m10 = deserializer.GetValue<Math::Real>("m10");
			ret.m11 = deserializer.GetValue<Math::Real>("m11");
			ret.m12 = deserializer.GetValue<Math::Real>("m12");
			ret.m13 = deserializer.GetValue<Math::Real>("m13");
			ret.m20 = deserializer.GetValue<Math::Real>("m20");
			ret.m21 = deserializer.GetValue<Math::Real>("m21");
			ret.m22 = deserializer.GetValue<Math::Real>("m22");
			ret.m23 = deserializer.GetValue<Math::Real>("m23");
			ret.m30 = deserializer.GetValue<Math::Real>("m30");
			ret.m31 = deserializer.GetValue<Math::Real>("m31");
			ret.m32 = deserializer.GetValue<Math::Real>("m32");
			ret.m33 = deserializer.GetValue<Math::Real>("m33");
			return ret;
		}
	}
}