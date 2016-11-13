#include "ShaderPreprocessor.hpp"

#include <fstream>
#include <sstream>
#include <iterator>

namespace EngineQ
{
	namespace Graphics
	{
		enum class Preprocessor::State
		{
			None,
			CommentStart,
			CommentOneline,
			CommentMultiline,

			CommentMultilineEnd,

			Prep_,

			Prep_i,
			Prep_in,
			Prep_inc,
			Prep_incl,
			Prep_inclu,
			Prep_includ,
			Prep_include,

			SkipToNewLine,

			Prep_include_beforeFilename,
			Prep_include_relativeFilename,
		};

		bool Preprocessor::IsValidNameStart(char c)
		{
			return ((c == '_') || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
		}

		bool Preprocessor::IsValidNameChar(char c)
		{
			return IsValidNameStart(c) || (c >= '0' && c <= '9');
		}

		std::string Preprocessor::GetFilePath(const std::string& filePath)
		{
			std::size_t length = filePath.size();
			for (auto it = filePath.rbegin(); it != filePath.rend(); ++it)
			{
				if (*it == '/')
					break;

				length -= 1;
			}

			if (length > filePath.size())
				return std::string{};

			return filePath.substr(0, length);
		}

		std::ostream& Preprocessor::PreprocessFile(const std::string& fileName, std::ostream& output)
		{
			State state = State::None;

			bool write = true;
			bool writeLater = false;
			int line = 1;

			std::stringstream stringstream;

			std::fstream input;
			input.exceptions(std::ifstream::badbit | std::ifstream::failbit);

			input.open(fileName);
			std::noskipws(input);

			for (std::istreambuf_iterator<char> it = input, end; it != end; ++it)
			{
				switch (state)
				{
					case State::None:
					{
						switch (*it)
						{
							case '/': state = State::CommentStart; break;
							case '#': state = State::Prep_; write = false; break;

							default: break;
						}
					}
					break;

					case State::CommentStart:
					{
						switch (*it)
						{
							case '/': state = State::CommentOneline;  break;
							case '*': state = State::CommentMultiline; break;

							default: break;
						}
					}
					break;

					case State::CommentOneline:
					{
						switch (*it)
						{
							case '\n': state = State::None; line += 1; break;

							default: break;
						}
					}
					break;

					case State::CommentMultiline:
					{
						switch (*it)
						{
							case '*': state = State::CommentMultilineEnd; break;

							default: break;
						}
					}
					break;

					case State::CommentMultilineEnd:
					{
						switch (*it)
						{
							case '/': state = State::None; break;

							default: state = State::CommentMultiline; break;
						}
					}
					break;

					case State::SkipToNewLine:
					{
						switch (*it)
						{
							case '\n': state = State::None; break;

							default: break;
						}
					}
					break;

					case State::Prep_:
					{
						switch (*it)
						{
							case 'i': state = State::Prep_i; break;

							default: state = State::SkipToNewLine; output << "#"; write = true; break;
								//	default: throw ParsingException{ "Invalid preprocessor directive" };
						}
					}
					break;

					case State::Prep_i:
					{
						switch (*it)
						{
							case 'n': state = State::Prep_in; break;

							default: state = State::SkipToNewLine; output << "#i"; write = true; break;
								//	default: throw ParsingException{ "Invalid preprocessor directive" };
						}
					}
					break;

					case State::Prep_in:
					{
						switch (*it)
						{
							case 'c': state = State::Prep_inc; break;

							default: state = State::SkipToNewLine; output << "#in"; write = true; break;
						//	default: throw ParsingException{ "Invalid preprocessor directive" };
						}
					}
					break;

					case State::Prep_inc:
					{
						switch (*it)
						{
							case 'l': state = State::Prep_incl; break;

							default: state = State::SkipToNewLine; output << "#inc"; write = true; break;
						//	default: throw ParsingException{ "Invalid preprocessor directive" };
						}
					}
					break;

					case State::Prep_incl:
					{
						switch (*it)
						{
							case 'u': state = State::Prep_inclu; break;

							default: state = State::SkipToNewLine; output << "#incl"; write = true; break;
						//	default: throw ParsingException{ "Invalid preprocessor directive" };
						}
					}
					break;

					case State::Prep_inclu:
					{
						switch (*it)
						{
							case 'd': state = State::Prep_includ; break;

							default: state = State::SkipToNewLine; output << "#inclu"; write = true; break;
						//	default: throw ParsingException{ "Invalid preprocessor directive" };
						}
					}
					break;

					case State::Prep_includ:
					{
						switch (*it)
						{
							case 'e': state = State::Prep_include; break;

							default: state = State::SkipToNewLine; output << "#includ"; write = true; break;
						//	default: throw ParsingException{ "Invalid preprocessor directive" };
						}
					}
					break;

					case State::Prep_include:
					{
						switch (*it)
						{
							case ' ': state = State::Prep_include_beforeFilename; break;

							default: state = State::SkipToNewLine; output << "#include"; write = true; break;
						//	default: throw ParsingException{ "Invalid preprocessor directive" };
						}
					}
					break;

					case State::Prep_include_beforeFilename:
					{
						switch (*it)
						{
							case ' ': break;
							case '"': state = State::Prep_include_relativeFilename; break;

							default: throw ParsingException{ "Invalid include" };
						}
					}
					break;

					case State::Prep_include_relativeFilename:
					{
						switch (*it)
						{
							case '"':
							{
								std::string newFileName = GetFilePath(fileName) + stringstream.str();

								this->PreprocessFile(newFileName, output);

								stringstream.clear();
								writeLater = true;

								state = State::None;
							}
							break;

							default: stringstream << *it; break;
						}
					}
					break;
				}

				if (write)
				{
					output << *it;
				}
				else
				{
					if (writeLater)
					{
						write = true;
						writeLater = false;
					}
				}
			}

			input.close();

			return output;
		}
	}
}