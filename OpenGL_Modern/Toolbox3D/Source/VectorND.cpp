#include "../Include/VectorND.h"

using namespace Bwt::Core::Maths;
VectorND::VectorND(int count, ...)
{
	tab.reserve(count);
	va_list valist;
	va_start(valist, count);
	nValue = count;
	for (int i = 0; i < count; i++)
	{
		double n = va_arg(valist, double);
		tab.push_back(static_cast<float>(n));
	}
	va_end(valist);
}

VectorND VectorND::GetOpposed() const
{
	VectorND vecND(*this);

	for (float& n : vecND.tab)
	{
		n = -n;
	}

	return vecND;
}

VectorND VectorND::AddVectorND(const VectorND& other) const
{
	assert(nValue == other.nValue);
	VectorND vec(nValue, tab);

	for (int n = 0; n < nValue - 1; n++)
	{
		vec.tab[n] += other[n];
	}
	return vec;
}

VectorND VectorND::AddScalar(float scalar) const
{
	VectorND vec(nValue, tab);
	for (float& n : vec.tab)
	{
		n += scalar;
	}
	return vec;
}

VectorND VectorND::ElementWiseProduct(const VectorND& other) const
{
	assert(nValue == other.nValue && "Size different VectorND");
	VectorND vec(nValue, tab);
	for (int i = 0; i < nValue; i++)
	{
		vec.tab[i] *= other.tab[i];
	}
	return vec;
}

VectorND VectorND::ProductScalar(float scalar) const
{
	VectorND vec(nValue, tab);
	for (float& n : vec.tab)
	{
		n *= scalar;
	}
	return vec;
}

VectorND VectorND::GetMid(const VectorND& other) const
{
	return AddVectorND(other).ProductScalar(1.f / 2.f);
}

float VectorND::GetDistance(const VectorND& other) const
{
	return sqrt(GetDistancePow(other));
}

float VectorND::GetDistancePow(const VectorND& other) const
{
	assert(nValue == other.nValue);
	float powed = 0;
	for (int i = 0; i < nValue; i++)
	{
		float n = this->tab[i] - other[i];
		powed += n * n;
	}
	return powed;
}

float VectorND::GetNorm() const
{
	float powed = 0;
	for (int i = 0; i < nValue; i++)
	{
		powed += (float)pow(this->tab[i], 2);
	}
	return sqrt(powed);
}

float VectorND::GetSquareNorm() const
{
	float powed = 0;
	for (int i = 0; i < nValue; i++)
	{
		powed += (float)pow(this->tab[i], 2);
	}
	return powed;
}

float VectorND::GetPerspective(float t) const
{
	if (t <= 0) return 0;

	return GetSquareNorm() / t;
}

float VectorND::DotProductVectorND(const VectorND& other) const
{
	assert(nValue == other.nValue);
	float powed = 0;
	for (int i = 0; i < nValue; i++)
	{
		powed += tab[i] * other[i];
	}
	return powed;
}

void VectorND::Print() const
{
	for (float n : tab)
	{
		std::cout << n << " ";
	}
	std::cout << std::endl;
}

bool VectorND::ContainsZero(const std::vector<float>& vec)
{
	return std::find(vec.begin(), vec.end(), 0.0f) != vec.end();
}
