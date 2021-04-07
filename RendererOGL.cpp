#include "RendererOGL.h"
#include <GL/glew.h>
#include "Rectangle.h"
#include "Vector2.h"
#include "Log.h"
#include "SpriteComponent.h"

#include <SDL_image.h>

RendererOGL::RendererOGL() : window(nullptr), vertexArray(nullptr), context(nullptr)
{
}

RendererOGL::~RendererOGL()
{
}

bool RendererOGL::initialize(Window& windowP)
{
	window = &windowP;

	// Set OpenGL Attributes
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

	// Request a Color Buffer With 8-Bit per RGBA Channel
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);

	// Enable Double Buffering
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	//Force OpenGL to use Hardware Acceleration
	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

	context = SDL_GL_CreateContext(windowP.getSDLWindow());
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		Log::error(LogCategory::Video, "Failed to Initialize GLEW");
		return false;
	}

	// Clear GLEW benign error code for some platforms
	glGetError();

	if (IMG_Init(IMG_INIT_PNG) == 0)
	{
		Log::error(LogCategory::Video, "Unable to Initialize SDL_image");
		return false;
	}

	vertexArray = new VertexArray(vertices, 4, indices, 6);
	return true;
}

void RendererOGL::beginDraw()
{
	glClearColor(0.45f, 0.45f, 1.0f, 1.0f);
	// Clear The Color Buffer
	glClear(GL_COLOR_BUFFER_BIT);
	// Enable Alpha Blendering on the Color Buffer
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void RendererOGL::draw()
{
	drawSprites();
}

void RendererOGL::drawSprite(const Actor& actor, const Texture& tex, Rectangle srcRect, Vector2 origin, Flip flip) const
{
}

void RendererOGL::endDraw()
{
	SDL_GL_SwapWindow(window->getSDLWindow());
}

void RendererOGL::close()
{
	SDL_GL_DeleteContext(context);
	delete vertexArray;
}

void RendererOGL::addSprite(SpriteComponent* sprite)
{
	// Insert the Sprite at the Right Place in Function of drawOrder
	int spriteDrawOrder = sprite->getDrawOrder();
	auto iter = begin(sprites);
	for (; iter != end(sprites); ++iter)
	{
		if (spriteDrawOrder < (*iter)->getDrawOrder()) {
			break;
		}
	}
}

void RendererOGL::removeSprite(SrpiteComponent* sprite)
{
	auto iter = std::find(begin(sprites), end(sprites), sprite);
	sprites.erase(iter);
}

void RendererOGL::drawSprites()
{
	for (auto sprite : sprites)
	{
		sprite->draw(*this);
	}
}
