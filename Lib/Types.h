// Author: Jake Rieger
// Created: 6/4/2024.
//

#pragma once

#include <cstdint>
#include <memory>
#include <optional>
#include <string>
#include <limits>
#include <filesystem>
#include <optional>

using u8   = uint8_t;
using u16  = uint16_t;
using u32  = uint32_t;
using u64  = uint64_t;
using i8   = int8_t;
using i16  = int16_t;
using i32  = int32_t;
using i64  = int64_t;
using f32  = float;
using f64  = double;
using wstr = std::wstring;
using str  = std::string;

namespace FileSystem = std::filesystem;
using Path           = std::filesystem::path;

template<class T>
using Option = std::optional<T>;

static constexpr std::nullopt_t kNone = std::nullopt;

template<class T>
using Shared = std::shared_ptr<T>;

template<class T>
using Option = std::optional<T>;

template<class T>
using Unique = std::unique_ptr<T>;

template<class T>
using Vector = std::vector<T>;

template<typename T>
struct InfinityHelper {
    static constexpr T value = std::numeric_limits<T>::max();
};

template<typename T>
constexpr T Infinity() {
    return InfinityHelper<T>::value;
}

static constexpr i64 MAX_SIZE   = 100000;
static constexpr f32 MAX_SIZE_F = 100000.f;