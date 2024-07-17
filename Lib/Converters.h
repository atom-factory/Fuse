// Author: Jake Rieger
// Created: 7/10/2024.
//

#pragma once
#pragma warning(disable : 4996)

#include "Types.h"

#include <codecvt>
#include <locale>

namespace Fuse::Converters {
    inline void HexToRGBA(const u32 hex, f32& r, f32& g, f32& b, f32& a) {
        const unsigned char alphaByte = (hex >> 24) & 0xFF;
        const unsigned char redByte   = (hex >> 16) & 0xFF;
        const unsigned char greenByte = (hex >> 8) & 0xFF;
        const unsigned char blueByte  = hex & 0xFF;

        a = static_cast<float>(static_cast<u32>(alphaByte) / 255.0);
        r = static_cast<float>(static_cast<u32>(redByte) / 255.0);
        g = static_cast<float>(static_cast<u32>(greenByte) / 255.0);
        b = static_cast<float>(static_cast<u32>(blueByte) / 255.0);
    }

    inline void HexToRGBA(const u32 hex, u32& r, u32& g, u32& b, u32& a) {
        const unsigned char alphaByte = (hex >> 24) & 0xFF;
        const unsigned char redByte   = (hex >> 16) & 0xFF;
        const unsigned char greenByte = (hex >> 8) & 0xFF;
        const unsigned char blueByte  = hex & 0xFF;

        a = static_cast<u32>(alphaByte);
        r = static_cast<u32>(redByte);
        g = static_cast<u32>(greenByte);
        b = static_cast<u32>(blueByte);
    }

    inline u32 RGBAToHex(const f32 r, const f32 g, const f32 b, const f32 a) {
        const auto redByte   = static_cast<unsigned char>(r * 255.0f);
        const auto greenByte = static_cast<unsigned char>(g * 255.0f);
        const auto blueByte  = static_cast<unsigned char>(b * 255.0f);
        const auto alphaByte = static_cast<unsigned char>(a * 255.0f);

        return (alphaByte << 24) | (redByte << 16) | (greenByte << 8) | blueByte;
    }

    inline void WideToANSI(const std::wstring& value, std::string& converted) {
        std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
        converted = converter.to_bytes(value);
    }

    inline void ANSIToWide(const std::string& value, std::wstring& converted) {
        std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
        converted = converter.from_bytes(value);
    }
}  // namespace Fuse::Converters