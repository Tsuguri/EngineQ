#ifndef UTILITIES_RESOURCES_IDS_HPP
#define UTILITIES_RESOURCES_IDS_HPP

namespace Utilities
{
	class ResourcesIDs
	{
	private:
		ResourcesIDs();
	public:
		static int QuadShader;
		static int BasicShader;
		static int CustomShader;

		static int BlurShader;
		static int BlurVShader;
		static int BrightExtract;
		static int CombineShader;
	};
}

#endif // !UTILITIES_RESOURCES_IDS_HPP