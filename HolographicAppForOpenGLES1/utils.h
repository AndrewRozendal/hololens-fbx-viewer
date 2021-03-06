#pragma once

#include <pch.h>
#include <strsafe.h>
#include <string>

class Vector3
{
public:
	Vector3() : x(0), y(0), z(0) {}
	Vector3(float xin, float yin, float zin) : x(xin), y(yin), z(zin) {}
	Vector3(const Vector3& other)
	{
		x = other.x;
		y = other.y;
		z = other.z;
	}
	Vector3& operator=(const Vector3& other)
	{
		x = other.x;
		y = other.y;
		z = other.z;
		return *this;
	}

	float x;
	float y;
	float z;
};

static void DebugLog(_In_z_ LPCWSTR format, ...)
{
	wchar_t buffer[1024];
	LPWSTR bufEnd = nullptr;

	va_list args;
	va_start(args, format);
	HRESULT hr = StringCchVPrintfExW(buffer, _countof(buffer), &bufEnd, nullptr, STRSAFE_FILL_BEHIND_NULL | STRSAFE_FILL_ON_FAILURE, format, args);

	if (SUCCEEDED(hr))
	{
		if (*bufEnd != L'\n')
		{
			StringCchCatW(buffer, _countof(buffer), L"\r\n");
		}

		OutputDebugStringW(buffer);
	}

	va_end(args);
}

static void checkGlError(std::wstring op) 
{
	int error;
	while ((error = glGetError()) != GL_NO_ERROR) 
	{
		auto str = std::wstring(L"opengl ").c_str() + op + std::wstring(L": glError %d");
		DebugLog(str.c_str(), error);
	}
}
