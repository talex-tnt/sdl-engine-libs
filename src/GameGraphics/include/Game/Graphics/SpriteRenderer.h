#pragma once
#include "SpriteAtlas.h"

namespace game
{
namespace graphics
{
class Renderer2D;

class SpriteRenderer
{
public:
	using Sprite = SpriteAtlas::Sprite;
	using Rect = Sprite::Rect;
	SpriteRenderer(const Renderer2D& i_renderer);
	~SpriteRenderer();
	void Render(const Rect& i_screenRect, const Sprite& i_sprite) const;

protected:

	SpriteRenderer(const SpriteRenderer&) = delete;
	SpriteRenderer(SpriteRenderer&&) = delete;

	SpriteRenderer& operator=(const SpriteRenderer&) = delete;
	SpriteRenderer& operator=(SpriteRenderer&&) = delete;

private:
	const Renderer2D& m_renderer;
};

}
}