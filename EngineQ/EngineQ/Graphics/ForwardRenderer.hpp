#ifndef ENGINEQ_GRAPHICS_FORWARDRENDERER_HPP
#define ENGINEQ_GRAPHICS_FORWARDRENDERER_HPP

#include "../Scene.hpp"
#include "Mesh.hpp"
#include "Framebuffer.hpp"

namespace EngineQ
{
	namespace Graphics
	{

		class ForwardRenderer
		{
		private:
			Framebuffer frm;
			std::shared_ptr<Shader> quadShader;
			GLuint quadVao;


			void InitScreenQuad();
		public:
			ForwardRenderer(EngineQ::Engine* engine);
			virtual ~ForwardRenderer();

			void Render(Scene* scene);


		};
	}
}

#endif
