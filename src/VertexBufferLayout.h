#pragma once

#include <vector>
#include <GL/glew.h>

struct VertexBufferElement
{
	unsigned int type;
	unsigned int count;
	unsigned char normalized;

	VertexBufferElement(const unsigned int i_type, const unsigned int i_count, const bool i_normalized)
		: type(i_type), count(i_count),	normalized(i_normalized)
	{

	}
};

class VertexBufferLayout
{
private:
	std::vector<VertexBufferElement> m_Elements;
	unsigned int m_Stride;
public:
	VertexBufferLayout()
		: m_Stride(0) {}

	template<typename T>
	void Push(int count)
	{
		static_assert(false);
	}

	template<>
	void Push<float>(const int count)
	{
		m_Elements.push_back( { GL_FLOAT, count, GL_FALSE } );
		m_Stride += GetGLTypeSize<GLfloat>();
	}

	template<>
	void Push<unsigned int>(const int count)
	{
		m_Elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
		m_Stride += GetGLTypeSize<GLuint>();
	}

	template<>
	void Push<unsigned char>(const int count)
	{
		m_Elements.push_back({ GL_UNSIGNED_BYTE , count, GL_TRUE });
		m_Stride += GetGLTypeSize<GLubyte>();
	}

	inline const std::vector<VertexBufferElement> GetElements() const& { return m_Elements; }
	inline unsigned int GetStride() const { return m_Stride; }

	template<typename T>
	unsigned int GetGLTypeSize()
	{
		return sizeof(T);
	}
};