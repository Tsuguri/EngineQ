#ifndef ENGINEQ_GRAPHICS_SHADER_PREPROCESSOR_HPP
#define ENGINEQ_GRAPHICS_SHADER_PREPROCESSOR_HPP

// Standard includes
#include <stdexcept>


namespace EngineQ
{
	namespace Graphics
	{
		class Preprocessor
		{
		private:
			enum class State;

			class ParsingException : public std::runtime_error
			{
			public:
				using std::runtime_error::runtime_error;
			};

			static bool IsValidNameStart(char c);
			static bool IsValidNameChar(char c);

			static std::string GetFilePath(const std::string& filePath);

		public:
			std::ostream& PreprocessFile(const std::string& fileName, std::ostream& output);
		};
	}
}

#endif // !ENGINEQ_GRAPHICS_SHADER_PREPROCESSOR_HPP
