#include "DebugDrawer.h"

namespace ForgeEngine
{
	DebugDrawer::DebugDrawer(const std::shared_ptr<Shader>& drawShader)
		: m_DrawShader(drawShader)
	{
	}

	void DebugDrawer::CreateLine(const Vector3& lineStart, const Vector3& lineEnd, const Color& color, unsigned int durationMS)
	{
		m_ActiveElements.push_back(new DebugLine(color, lineStart, lineEnd, durationMS));
	}

	void DebugDrawer::Update()
	{
		for (const DebugElement* element : m_ActiveElements)
		{
			element->Draw(*(m_DrawShader.get()));
		}

		for (int i = m_ActiveElements.size() - 1; i >= 0; i--)
		{
			const DebugElement* element = m_ActiveElements[i];
			if (element->HasExpired())
			{
				m_ActiveElements.erase(m_ActiveElements.begin() + i);
				delete(element);
			}
		}
	}
}
