#ifndef ENGINEQ_UTILITIES_RESOURCES_IDS_HPP
#define ENGINEQ_UTILITIES_RESOURCES_IDS_HPP

namespace EngineQ
{
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
		
			static int DeferredGeometry;
			static int DeferredLightning;

			static int CustomDeferred;
		};


	}
}

#endif