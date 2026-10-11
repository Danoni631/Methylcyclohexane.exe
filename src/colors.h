#pragma once

#include "Methylcyclohexane.h"

/*
* HSL CODED BY Danoni631
* HSV CODED BY JhoPro
*/

// structure for HSL
typedef struct
{
	float h; // hue
	float s; // saturation
	float l; // light
} HSL;

// structure for HSV
typedef struct
{
	float h; // hue
	float s; // saturation
	float v; // value
} HSV;

// RGBQUAD
typedef union
{
	COLORREF rgb; // pinto

	struct
	{
		BYTE r; // red
		BYTE g; // green
		BYTE b; // blue

		BYTE reserved; // unused
	};
} RGBQUAD_t;

typedef RGBQUAD_t* PRGBQUAD_t; // null pointer

// AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
static float HueToRGB(float p, float q, float t)
{
	if (t < 0.0f) t += 1.0f;
	if (t > 1.0f) t -= 1.0f;
	if (t < 1.0f / 6.0f) return p + (q - p) * 6.0f * t;
	if (t < 1.0f / 2.0f) return q;
	if (t < 2.0f / 3.0f) return p + (q - p) * (2.0f / 3.0f - t) * 6.0f;
	return p;
}

// convert a hsl to rgb
RGBQUAD_t HSLtoRGB(HSL hsl)
{
	RGBQUAD_t rgb;
	rgb.reserved = 0;

	if (hsl.s == 0.0f)
	{
		BYTE val = (BYTE)(hsl.l * 255.0f);
		rgb.r = val;
		rgb.g = val;
		rgb.b = val;
	}

	else
	{
		float q = (hsl.l < 0.5f) ? (hsl.l * (1.0f + hsl.s)) : (hsl.l + hsl.s - hsl.l * hsl.s);
		float p = 2.0f * hsl.l - q;

		rgb.r = (BYTE)(HueToRGB(p, q, hsl.h + 1.0f / 3.0f) * 255.0f);
		rgb.g = (BYTE)(HueToRGB(p, q, hsl.h) * 255.0f);
		rgb.b = (BYTE)(HueToRGB(p, q, hsl.h - 1.0f / 3.0f) * 255.0f);
	}

	return rgb;
}

// convert a rgb to hsl
HSL RGBtoHSL(RGBQUAD_t rgb)
{
	float r = rgb.r / 255.0f;
	float g = rgb.g / 255.0f;
	float b = rgb.b / 255.0f;

	float max = fmaxf(r, fmaxf(g, b)), min = fminf(r, fminf(g, b));
	float h, s, l = (max + min) / 2.0f;

	if (max == min)
	{
		h = s = 0;
	}

	else
	{
		float d = max - min;
		s = l > 0.5f ? d / (2 - max - min) : d / (max + min);
		if (max == r) h = (g - b) / d + (g < b ? 6 : 0);
		else if (max == g) h = (b - r) / d + 2;
		else h = (r - g) / d + 4;
		h /= 6;
	}

	return { h, s, l };
}

// convert a hsv to rgb
RGBQUAD HSVtoRGB(HSV hsv)
{
	int hi = (int)floor(hsv.h / 60.0) % 6;
	double f = hsv.h / 60.0 - floor(hsv.h / 60.0);
	double p = hsv.v * (1.0 - hsv.s);
	double q = hsv.v * (1.0 - f * hsv.s);
	double t = hsv.v * (1.0 - (1.0 - f) * hsv.s);

	switch (hi)
	{
		case 0:
			return { static_cast<BYTE>(hsv.v * 255), static_cast<BYTE>(t * 255), static_cast<BYTE>(p * 255) };
		case 1:
			return { static_cast<BYTE>(q * 255), static_cast<BYTE>(hsv.v * 255), static_cast<BYTE>(p * 255) };
		case 2:
			return { static_cast<BYTE>(p * 255), static_cast<BYTE>(hsv.v * 255), static_cast<BYTE>(t * 255) };
		case 3:
			return { static_cast<BYTE>(p * 255), static_cast<BYTE>(q * 255), static_cast<BYTE>(hsv.v * 255) };
		case 4:
			return { static_cast<BYTE>(t * 255), static_cast<BYTE>(p * 255), static_cast<BYTE>(hsv.v * 255) };
		default:
			return { static_cast<BYTE>(hsv.v * 255), static_cast<BYTE>(p * 255), static_cast<BYTE>(q * 255) };
	}
}

// convert a rgb to hsl
HSV RGBtoHSV(RGBQUAD rgbquad)
{
	HSV hsv;

	double rd = rgbquad.rgbRed / 255.0;
	double gd = rgbquad.rgbGreen / 255.0;
	double bd = rgbquad.rgbBlue / 255.0;

	double cmax = max(max(rd, gd), bd);
	double cmin = min(min(rd, gd), bd);
	double delta = cmax - cmin;

	hsv.v = cmax;

	if (cmax > 0.0)
		hsv.s = delta / cmax;
	else
		hsv.s = 0.0;

	if (delta > 0.0)
	{
		if (cmax == rd)
			hsv.h = 60.0 * fmod((gd - bd) / delta, 6.0);
		else if (cmax == gd)
			hsv.h = 60.0 * ((bd - rd) / delta + 2.0);
		else if (cmax == bd)
			hsv.h = 60.0 * ((rd - gd) / delta + 4.0);

		if (hsv.h < 0.0)
			hsv.h += 360.0;
	}
	else
	{
		hsv.h = 0.0;
	}

	return hsv;
}