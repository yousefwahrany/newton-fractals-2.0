#include <iostream>
#include <cmath>
#include <windows.h>
#include <vector>
#include <ctime>
using namespace std;

class complex
{
public:

	double real, imag;

	complex() : real(0), imag(0)
	{
	}

	complex(double rel, double img) : real(rel), imag(img)
	{
	}

	complex(double doble) : real(doble), imag(0)
	{
	}

	complex(long lng) : real(lng), imag(0)
	{
	}

	complex(int it) : real(it), imag(0)
	{
	}

	complex(float flot) : real(flot), imag(0)
	{
	}


	friend complex operator + (const complex& comp, const complex& comp1) 
	{
		complex comp2;
		comp2.real = comp.real + comp1.real;
		comp2.imag = comp.imag + comp1.imag;
		return comp2;
	}

	friend complex operator - (const complex& comp1, const complex& comp) 
	{
		complex comp2;
		comp2.real = comp1.real - comp.real;
		comp2.imag = comp1.imag - comp.imag;
		return comp2;
	}

	friend complex operator * (const complex& comp1, const complex& comp)
	{
		complex comp2;
		comp2.real = comp1.real * comp.real - comp1.imag * comp.imag;
		comp2.imag = comp1.real * comp.imag + comp1.imag * comp.real;
		return comp2;
	}

	friend complex operator / (const complex& comp1, const complex& comp) 
	{
		complex comp2;
		comp2.real = (comp1.real * comp.real + comp1.imag * comp.imag) / (comp.real * comp.real + comp.imag * comp.imag);
		comp2.imag = (comp1.imag * comp.real - comp1.real * comp.imag) / (comp.real * comp.real + comp.imag * comp.imag);
		return comp2;
	}

	friend bool operator == (const complex& comp1, const complex& comp)
	{
		if (comp.real == comp1.real && comp.imag == comp1.imag)
			return true;
		else 
			return false;
	}

	complex operator - () const
	{
		complex comp2;
		comp2.real = -real;
		comp2.imag = -imag;
		return comp2;
	}

	complex operator -- () const
	{
		complex comp2;
		comp2.real = real - 1;
		comp2.imag = imag;
		return comp2;
	}

	complex operator ++ () const
	{
		complex comp2;
		comp2.real = real + 1;
		comp2.imag = imag;
		return comp2;
	}


	friend ostream& operator << (ostream& outs, const complex& comp)
	{
		outs << comp.real << " + " << comp.imag << "i";
		return outs;
	}

	friend float argd(const complex& comp)
	{
		return atan(comp.imag / comp.real) * (180 / 3.14159265359);
	}

	friend float argr(const complex& comp)
	{
		return atan(comp.imag / comp.real);
	}

	friend float abs(const complex& comp)
	{
		return sqrt(comp.real * comp.real + comp.imag * comp.imag);
	}

	friend complex conj(const complex& comp)
	{
		complex comp2;
		comp2.real = comp.real;
		comp2.imag = -comp.imag;
		return comp2;
	}

	friend complex pow(const complex& comp, int i)
	{
		complex prod(1, 0);
		for (int j = 0; j < i; j++)
		{
			prod = prod * comp;
		}
		return prod;
	}

	friend complex round(complex& comp, int place)
	{
		comp.real = double(floor(comp.real * pow(10, place))) / pow(10, place);
		comp.imag = double(floor(comp.imag * pow(10, place))) / pow(10, place);
		return comp;
	}

	friend complex cosh(complex& comp)
	{
		int fact = 1;
		complex sum = 1;

		for (int i = 1; i <= 10; i++)
		{
			fact = fact * i;
			if (i % 2 == 0)
			{
				sum = sum + pow(comp, i) / fact;
			}
		}
		return sum;
	}

	friend complex sinh(complex& comp)
	{
		int fact = 1;
		complex sum = 0;

		for (int i = 1; i <= 10; i++)
		{
			fact = fact * i;
			if (i % 2 == 1)
			{
				sum = sum + pow(comp, i) / fact;
			}
		}
		return sum;
	}

private:

};

complex f(complex z)
{
	return cosh(z) - 1;
}

complex Df(complex z)
{
	return sinh(z) ;
}

complex newton(complex z)
{
	for (int i = 0; i < 200; i++)
	{
		z = z - f(z) / Df(z);
	}
	return round(z, 1);
}

int main()
{
	HWND myconsole = GetConsoleWindow();
	HDC mydc = GetDC(myconsole);
	COLORREF color[10];
	for (int i = 0; i < 10; i++)
		color[i] = RGB(rand() % 256, rand() % 256, rand() % 256);

	complex sol[1000];
	int c = 1, no, size = 256, zoom = 1;
	bool found;


	sol[0] = newton(complex(0, 0));

	for (int i = -size; i < size; i++)
	{
		for (int j = -size; j < size; j++)
		{
			complex z(i / zoom, j / zoom);
			complex y = newton(z);
			found = false;

			for (int k = 0; k < c; k++)
			{
				if (y == sol[k])
				{
					no = k;
					found = true;
					break;
				}
			}

			if (!found)
			{
				sol[c] = y;
				no = c;
				c++;
			}
			SetPixel(mydc, i + size, j + size, color[no]);
		}
	}

	ReleaseDC(myconsole, mydc);
	cin.ignore();

}

/*int main() 
{
	complex z(3, 0);
	cout << sinh(z);
}*/