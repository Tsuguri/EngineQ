namespace EngineQ
{
	namespace Utilities
	{
		template<typename Type>
		std::string ToString(const Type& value)
		{
			std::stringstream stream;
			stream.exceptions(std::stringstream::badbit | std::stringstream::failbit);
			stream << value;
			
			return stream.str();
		}

		template<typename Type>
		std::istream& operator >>= (std::istream& stream, Type& value)
		{
			return stream.read(reinterpret_cast<char*>(&value), sizeof(Type));
		}

		template<typename Type>
		std::ostream& operator <<= (std::ostream& stream, const Type& value)
		{
			return stream.write(reinterpret_cast<const char*>(&value), sizeof(Type));
		}
	}
}