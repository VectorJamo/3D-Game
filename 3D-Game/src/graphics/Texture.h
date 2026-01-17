#pragma once
class Texture
{
private:
	int m_Width, m_Height, m_ColorChannels;
	unsigned int m_TextureID;

public:
	Texture(const char* texturePath);
	~Texture();

	void Bind(int textureSlot = 0);
};
