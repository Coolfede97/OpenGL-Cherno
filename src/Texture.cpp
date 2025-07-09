#include "Texture.h"
#include "vendor/stb_image/stb_image.h"

Texture::Texture(std::string& path)
	: m_RendererID(0), m_FilePath(path), m_LocalBuffer(nullptr), m_Width(0), m_Height(0), m_BPP(0)
{
	// Turns around the texture, so that it is up-side down
	// We do this because OpenGL expects textures (0,0) position to be at the bottom-left corner,
	// not at the top-left corner.
	stbi_set_flip_vertically_on_load(1);

	// The last variable are the desired channels we want. We put 4 because of the RGBA channels
	m_LocalBuffer = stbi_load(path.c_str(), &m_Width, &m_Height, &m_BPP, 4);

	GLCall(glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLCall(glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GLCall(glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP));
	GLCall(glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP));

	GLCall(glGenTextures(1, &m_RendererID));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererID));
}

Texture::~Texture()
{

}

void Texture::Bind(unsigned int slot /*= 0*/) const
{

}

void Texture::Unbind()
{

}
