#include "Camera.h"

Camera* Camera::s_instance = nullptr;

void Camera::Update(float dt)
{
	if (m_Target != nullptr)
	{
		m_Viewbox.x = m_Target->X - SCREEN_WIDTH / 2;
		m_Viewbox.y = m_Target->Y - SCREEN_HEIGHT / 2;
		if (m_Viewbox.x < 0)
		{
			m_Viewbox.x = 0;
		}
		if (m_Viewbox.y < 0)
		{
			m_Viewbox.y = 0;
		}
		if (m_Viewbox.x > (2 * SCREEN_WIDTH - m_Viewbox.w))
		{
			m_Viewbox.x = (2 * SCREEN_WIDTH - m_Viewbox.w);
		}
		if (m_Viewbox.y > (2 * SCREEN_HEIGHT - m_Viewbox.h))
		{
			m_Viewbox.y = (2 * SCREEN_HEIGHT - m_Viewbox.h);
		}
		m_Position = Vec2(m_Viewbox.x, m_Viewbox.y);
	}
}