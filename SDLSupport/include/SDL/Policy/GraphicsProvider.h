#pragma once
#include <functional>
#include <memory>

namespace sdl
{
class Renderer;
class Display;
class TextureFactory;

namespace policy
{
class Initialization;

class GraphicsProvider
{
public:
	using RendererT = Renderer;
	using DisplayT = Display;
	using TextureFactoryT = TextureFactory;

	void InitGraphics(Initialization& i_windowProvider);

	const RendererT* GetRenderer() const;
	RendererT* GetRenderer();

	const DisplayT* GetDisplay() const;

	const TextureFactoryT* GetTextureFactory() const;
	TextureFactoryT* GetTextureFactory();

protected:
	GraphicsProvider();
	~GraphicsProvider();

	GraphicsProvider(const GraphicsProvider&) = delete;
	GraphicsProvider(GraphicsProvider&&) = delete;

	GraphicsProvider& operator=(const GraphicsProvider&) = delete;
	GraphicsProvider& operator=(GraphicsProvider&&) = delete;

private:
	std::unique_ptr<RendererT> m_renderer;
	std::unique_ptr<DisplayT> m_display;
	std::unique_ptr<TextureFactoryT> m_textureFactory;

};
}
}