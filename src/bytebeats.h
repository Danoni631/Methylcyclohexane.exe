#pragma once

#include "Methylcyclohexane.h"

/*
* CODED BY Danoni631
* 
* Is the sounds of this shit
*/

#define SAMPLE_RATE 8000 // 8000 is 8kHz
#define SECONDS 30 // 30 seconds
#define BUFFER_SIZE (SAMPLE_RATE * SECONDS) // 8kHz and 30 seconds

#define FASTER_SAMPLE_RATE 11025 // 11025 is 11kHz
#define NEW_BUFFER_SIZE (FASTER_SAMPLE_RATE * SECONDS) // 11kHz and 30 seconds

// the 22kHz bytebeats don't need this declarations

namespace Bytebeats
{
	DWORD WINAPI Sound1(LPVOID lpvd)
	{
		HWAVEOUT hWaveOut;
		WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, FASTER_SAMPLE_RATE, FASTER_SAMPLE_RATE, 1, 8, 0 };

		if (waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL) != MMSYSERR_NOERROR)
		{
			return 1;
		}

		std::vector<unsigned char> buffer(NEW_BUFFER_SIZE);

		for (int t = 0; t < NEW_BUFFER_SIZE; ++t)
		{
			buffer[t] = (unsigned char)((t * (t >> 5 & t >> 7)) + (t >> t));
		}

		WAVEHDR header = { (LPSTR)buffer.data(), (DWORD)buffer.size(), 0, 0, 0, 0, 0, 0 };

		waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
		waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));

		while (!(header.dwFlags & WHDR_DONE))
		{
			Sleep(100);
		}

		waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
		waveOutClose(hWaveOut);

		return 0;
	}

	DWORD WINAPI Sound2(LPVOID lpvd)
	{
		HWAVEOUT hWaveOut;
		WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, FASTER_SAMPLE_RATE, FASTER_SAMPLE_RATE, 1, 8, 0 };

		if (waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL) != MMSYSERR_NOERROR)
		{
			return 1;
		}

		std::vector<unsigned char> buffer(NEW_BUFFER_SIZE);

		for (int t = 0; t < NEW_BUFFER_SIZE; ++t)
		{
			buffer[t] = (unsigned char)
			(
				(5 * (t + (t ^ t >> 7) ^ 5) | 19 * (2 * t >> 43 | 15 * t >> 4) &
				(7 * t >> 172) / 2 * t * ((t >> 9 | t >> 13) & 15) & 129 | t *
				((t >> 9 | 3 < t) & 25 & t >> 10)) + (t * (t >> 6 & t >> 5))
			);
		}

		WAVEHDR header = { (LPSTR)buffer.data(), (DWORD)buffer.size(), 0, 0, 0, 0, 0, 0 };

		waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
		waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));

		while (!(header.dwFlags & WHDR_DONE))
		{
			Sleep(100);
		}

		waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
		waveOutClose(hWaveOut);

		return 0;
	}

	DWORD WINAPI Sound3(LPVOID lpvd)
	{
		HWAVEOUT hWaveOut;
		WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, FASTER_SAMPLE_RATE, FASTER_SAMPLE_RATE, 1, 8, 0 };

		if (waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL) != MMSYSERR_NOERROR)
		{
			return 1;
		}

		std::vector<unsigned char> buffer(NEW_BUFFER_SIZE);

		for (int t = 0; t < NEW_BUFFER_SIZE; ++t)
		{
			buffer[t] = (unsigned char)
			(
				(((((t / 8 | 0) ^ (t / 8 | 0) - 1280) % 11 * t / 2 & 127) +
				(((t / 512 | 0) ^ (t / 500 | 0) - 2) % 13 * t / 2 & 127)) * 5) + (t * (t >> 6 & t >> 5))
			);
		}

		WAVEHDR header = { (LPSTR)buffer.data(), (DWORD)buffer.size(), 0, 0, 0, 0, 0, 0 };

		waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
		waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));

		while (!(header.dwFlags & WHDR_DONE))
		{
			Sleep(100);
		}

		waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
		waveOutClose(hWaveOut);

		return 0;
	}

	DWORD WINAPI Sound4(LPVOID lpvd)
	{
		HWAVEOUT hWaveOut;
		WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, FASTER_SAMPLE_RATE, FASTER_SAMPLE_RATE, 1, 8, 0 };

		if (waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL) != MMSYSERR_NOERROR)
		{
			return 1;
		}

		std::vector<unsigned char> buffer(NEW_BUFFER_SIZE);

		for (int t = 0; t < NEW_BUFFER_SIZE; ++t)
		{
			buffer[t] = (unsigned char)((t >> 5) + (t >> t));
		}

		WAVEHDR header = { (LPSTR)buffer.data(), (DWORD)buffer.size(), 0, 0, 0, 0, 0, 0 };

		waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
		waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));

		while (!(header.dwFlags & WHDR_DONE))
		{
			Sleep(100);
		}

		waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
		waveOutClose(hWaveOut);

		return 0;
	}

	DWORD WINAPI Sound5(LPVOID lpvd)
	{
		HWAVEOUT hWaveOut = 0;
		WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 22050, 22050, 1, 8, 0 };

		if (waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL) != MMSYSERR_NOERROR)
		{
			return 1;
		}

		DWORD bufferSize = 22050 * 30;
		char* buffer = new char[bufferSize];

		for (DWORD t = 0; t < bufferSize; ++t)
		{
			buffer[t] = static_cast<char>
			(
				(t >> (t & 8192 ? 3 : 4) | t * (t >> 5 & t >> 7) |
				t * (t >> 4 & t >> 5 | t >> 9) & 144 | (t + t >> t)) +
				(((t >> 5 | (t >> 2) * (t >> 5))))
			);
		}

		WAVEHDR header = { 0 };
		header.lpData = buffer;
		header.dwBufferLength = bufferSize;

		waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
		waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));

		while (!(header.dwFlags & WHDR_DONE))
		{
			Sleep(100);
		}

		waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
		waveOutClose(hWaveOut);

		delete[] buffer;
		return 0;
	}

	DWORD WINAPI Sound6(LPVOID lpvd)
	{
		HWAVEOUT hWaveOut;
		WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, FASTER_SAMPLE_RATE, FASTER_SAMPLE_RATE, 1, 8, 0 };

		if (waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL) != MMSYSERR_NOERROR)
		{
			return 1;
		}

		std::vector<unsigned char> buffer(NEW_BUFFER_SIZE);

		for (int t = 0; t < NEW_BUFFER_SIZE; ++t)
		{
			buffer[t] = (unsigned char)((10 * (t ^ 6 & t >> (t & 167 & t ^ 11))) + (t >> 4) * (t ^ t >> 5));
		}

		WAVEHDR header = { (LPSTR)buffer.data(), (DWORD)buffer.size(), 0, 0, 0, 0, 0, 0 };

		waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
		waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));

		while (!(header.dwFlags & WHDR_DONE))
		{
			Sleep(100);
		}

		waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
		waveOutClose(hWaveOut);

		return 0;
	}

	DWORD WINAPI Sound7(LPVOID lpvd)
	{
		HWAVEOUT hWaveOut;
		WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, SAMPLE_RATE, SAMPLE_RATE, 1, 8, 0 };

		if (waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL) != MMSYSERR_NOERROR)
			return 1;

		std::vector<unsigned char> buffer(BUFFER_SIZE);

		for (int t = 0; t < BUFFER_SIZE; ++t)
		{
			buffer[t] =
			(unsigned char)
			(
				(((t >> 5 | (t >> 2) * (t >> 5)))) + (t << (t >> 8) * 231)
			);
		}

		WAVEHDR header = { (LPSTR)buffer.data(), BUFFER_SIZE, 0, 0, 0, 0, 0, 0 };

		waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
		waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));

		while (!(header.dwFlags & WHDR_DONE))
		{
			Sleep(100);
		}

		waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
		waveOutClose(hWaveOut);
		return 0;
	}

	DWORD WINAPI Sound8(LPVOID lpvd)
	{
		HWAVEOUT hWaveOut;
		WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, SAMPLE_RATE, SAMPLE_RATE, 1, 8, 0 };

		if (waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL) != MMSYSERR_NOERROR)
			return 1;

		std::vector<unsigned char> buffer(BUFFER_SIZE);

		for (int t = 0; t < BUFFER_SIZE; ++t)
		{
			buffer[t] = (unsigned char)((t * (1 * t >> 4) + (t * (t >> 5 & t >> 9))));
		}

		WAVEHDR header = { (LPSTR)buffer.data(), BUFFER_SIZE, 0, 0, 0, 0, 0, 0 };

		waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
		waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));

		while (!(header.dwFlags & WHDR_DONE))
		{
			Sleep(100);
		}

		waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
		waveOutClose(hWaveOut);
		return 0;
	}

	DWORD WINAPI Sound9(LPVOID lpvd)
	{
		HWAVEOUT hWaveOut = 0;
		WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 22050, 22050, 1, 8, 0 };

		if (waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL) != MMSYSERR_NOERROR)
		{
			return 1;
		}

		DWORD bufferSize = 22050 * 30;
		char* buffer = new char[bufferSize];

		for (DWORD t = 0; t < bufferSize; ++t)
		{
			buffer[t] = static_cast<char>
			(
				(2 * (1 - (t + 10 >> (t >> 9 & t >> 14) & t >> 4 & -2)) * (t >> 10 ^ t + 128))
			);
		}

		WAVEHDR header = { 0 };
		header.lpData = buffer;
		header.dwBufferLength = bufferSize;

		waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
		waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));

		while (!(header.dwFlags & WHDR_DONE))
		{
			Sleep(100);
		}

		waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
		waveOutClose(hWaveOut);

		delete[] buffer;
		return 0;
	}

	DWORD WINAPI Sound10(LPVOID lpvd)
	{
		HWAVEOUT hWaveOut = 0;
		WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 22050, 22050, 1, 8, 0 };

		if (waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL) != MMSYSERR_NOERROR)
		{
			return 1;
		}

		DWORD bufferSize = 22050 * 30;
		char* buffer = new char[bufferSize];

		for (DWORD t = 0; t < bufferSize; ++t)
		{
			buffer[t] = static_cast<char>
			(
				(t >> 5 | (t >> 2) * (t >> 5)) +
				(t * ((t / 2 >> 10 | t % 16 * t >> 8) & 8 * t >> 12 & 18) | (t / 16) + 64)
			);
		}

		WAVEHDR header = { 0 };
		header.lpData = buffer;
		header.dwBufferLength = bufferSize;

		waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
		waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));

		while (!(header.dwFlags & WHDR_DONE))
		{
			Sleep(100);
		}

		waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
		waveOutClose(hWaveOut);

		delete[] buffer;
		return 0;
	}

	DWORD WINAPI Sound11(LPVOID lpvd)
	{
		HWAVEOUT hWaveOut;
		WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, SAMPLE_RATE, SAMPLE_RATE, 1, 8, 0 };

		if (waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL) != MMSYSERR_NOERROR)
			return 1;

		std::vector<unsigned char> buffer(BUFFER_SIZE);

		for (int t = 0; t < BUFFER_SIZE; ++t)
		{
			buffer[t] = (unsigned char)(((t * t >> (t / 256)) + (t + (t & t ^ t >> 6))));
		}

		WAVEHDR header = { (LPSTR)buffer.data(), BUFFER_SIZE, 0, 0, 0, 0, 0, 0 };

		waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
		waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));

		while (!(header.dwFlags & WHDR_DONE))
		{
			Sleep(100);
		}

		waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
		waveOutClose(hWaveOut);
		return 0;
	}

	DWORD WINAPI Sound12(LPVOID lpvd)
	{
		HWAVEOUT hWaveOut;
		WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, FASTER_SAMPLE_RATE, FASTER_SAMPLE_RATE, 1, 8, 0 };

		if (waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL) != MMSYSERR_NOERROR)
		{
			return 1;
		}

		std::vector<unsigned char> buffer(NEW_BUFFER_SIZE);

		for (int t = 0; t < NEW_BUFFER_SIZE; ++t)
		{
			buffer[t] = (unsigned char)(128 * sin((t * t >> (t / 256))) + 12);
		}

		WAVEHDR header = { (LPSTR)buffer.data(), (DWORD)buffer.size(), 0, 0, 0, 0, 0, 0 };

		waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
		waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));

		while (!(header.dwFlags & WHDR_DONE))
		{
			Sleep(100);
		}

		waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
		waveOutClose(hWaveOut);

		return 0;
	}

	DWORD WINAPI Sound13(LPVOID lpvd)
	{
		HWAVEOUT hWaveOut = 0;
		WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 22050, 22050, 1, 8, 0 };

		if (waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL) != MMSYSERR_NOERROR)
		{
			return 1;
		}

		DWORD bufferSize = 22050 * 30;
		char* buffer = new char[bufferSize];

		for (DWORD t = 0; t < bufferSize; ++t)
		{
			buffer[t] = static_cast<char>
			(
				((((2 * t & (t & 256 ? t : t) >> 8 & (t & 256 ? t : t) >> 6)) * 10) + (t >> 3)) & 128
			);
		}

		WAVEHDR header = { 0 };
		header.lpData = buffer;
		header.dwBufferLength = bufferSize;

		waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
		waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));

		while (!(header.dwFlags & WHDR_DONE))
		{
			Sleep(100);
		}

		waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
		waveOutClose(hWaveOut);

		delete[] buffer;
		return 0;
	}

	DWORD WINAPI Sound14(LPVOID lpvd)
	{
		HWAVEOUT hWaveOut;
		WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, SAMPLE_RATE, SAMPLE_RATE, 1, 8, 0 };

		if (waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL) != MMSYSERR_NOERROR)
			return 1;

		std::vector<unsigned char> buffer(BUFFER_SIZE);

		for (int t = 0; t < BUFFER_SIZE; ++t)
		{
			buffer[t] = (unsigned char)((t * (61 ^ t >> 5)) + (t * (t >> 1 | t >> 8)));
		}

		WAVEHDR header = { (LPSTR)buffer.data(), BUFFER_SIZE, 0, 0, 0, 0, 0, 0 };

		waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
		waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));

		while (!(header.dwFlags & WHDR_DONE))
		{
			Sleep(100);
		}

		waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
		waveOutClose(hWaveOut);
		return 0;
	}

	DWORD WINAPI Sound15(LPVOID lpvd)
	{
		HWAVEOUT hWaveOut;
		WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, FASTER_SAMPLE_RATE, FASTER_SAMPLE_RATE, 1, 8, 0 };

		if (waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL) != MMSYSERR_NOERROR)
		{
			return 1;
		}

		std::vector<unsigned char> buffer(NEW_BUFFER_SIZE);

		for (int t = 0; t < NEW_BUFFER_SIZE; ++t)
		{
			buffer[t] = (unsigned char)((t * (61 ^ t >> 5)) + (t >> t));
		}

		WAVEHDR header = { (LPSTR)buffer.data(), (DWORD)buffer.size(), 0, 0, 0, 0, 0, 0 };

		waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
		waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));

		while (!(header.dwFlags & WHDR_DONE))
		{
			Sleep(100);
		}

		waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
		waveOutClose(hWaveOut);

		return 0;
	}
}