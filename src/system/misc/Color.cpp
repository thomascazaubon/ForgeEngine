#include "Color.h"

#include "system/math/MathUtils.h"

namespace ForgeEngine
{
	Color::Color(unsigned int r, unsigned int g, unsigned int b, float a /*= 1.f*/) :
		m_R(r),
		m_G(g),
		m_B(b),
		m_A(a)
	{
	}

	Color Color::GetGrayScale() const
	{
		unsigned int sumValues = m_R + m_G + m_B;
		return Color{ sumValues / 3, sumValues / 3, sumValues / 3, m_A };
	}

	/*static*/ Color Color::GetGrayScale(Color c)
	{
		return c.GetGrayScale();
	}

	Color Color::operator*(float multiplier)
	{
		float clampedMultiplier = ForgeMaths::Clamp(multiplier, 0.f, 1.f);
		return Color(m_R * clampedMultiplier, m_G * clampedMultiplier, m_B * clampedMultiplier);
	}

	std::ostream& operator<<(std::ostream& os, const Color& c)
	{
		os << "{R" << c.GetR() << ", G" << c.GetG() << ", B" << c.GetB() << ", A" << c.GetA() << "}";
		return os;
	}
}