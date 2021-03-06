#include "pch.h"
#include "OpenGlRendererApi.h"

#include <glad/glad.h>

namespace Running
{
	void OpenGlRendererApi::SetClearColor(const glm::vec4& color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void OpenGlRendererApi::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void OpenGlRendererApi::DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray)
	{
		glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
	}
}
