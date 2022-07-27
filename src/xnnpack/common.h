// Copyright (c) Facebook, Inc. and its affiliates.
// All rights reserved.
//
// Copyright 2019 Google LLC
//
// This source code is licensed under the BSD-style license found in the
// LICENSE file in the root directory of this source tree.

#pragma once

#if defined(__APPLE__)
  #include <TargetConditionals.h>
#endif


// Define architecture identification macros

#if defined(__i386__) || defined(__i486__) || defined(__i586__) || defined(__i686__) || defined(_M_IX86)
  #define XNN_ARCH_X86 1
#else
  #define XNN_ARCH_X86 0
#endif

#if defined(__x86_64__) || defined(__x86_64) || defined(_M_X64) || defined(_M_AMD64)
  #define XNN_ARCH_X86_64 1
#else
  #define XNN_ARCH_X86_64 0
#endif

#if defined(__arm__) || defined(_M_ARM)
  #define XNN_ARCH_ARM 1
#else
  #define XNN_ARCH_ARM 0
#endif

#if defined(__aarch64__) || defined(_M_ARM64)
  #define XNN_ARCH_ARM64 1
#else
  #define XNN_ARCH_ARM64 0
#endif

#if defined(__PPC64__) || defined(__ppc64__) || defined(__powerpc64__) || defined(_ARCH_PPC64)
  #define XNN_ARCH_PPC64 1
#else
  #define XNN_ARCH_PPC64 0
#endif

#if defined(__riscv) || defined(__riscv__)
  #define XNN_ARCH_RISCV 1
#else
  #define XNN_ARCH_RISCV 0
#endif

#if defined(__wasm__)
  #if defined(__wasm_relaxed_simd__)
    #define XNN_ARCH_WASM 0
    #define XNN_ARCH_WASMSIMD 0
    #define XNN_ARCH_WASMRELAXEDSIMD 1
  #elif defined(__wasm_simd128__)
    #define XNN_ARCH_WASM 0
    #define XNN_ARCH_WASMSIMD 1
    #define XNN_ARCH_WASMRELAXEDSIMD 0
  #else
    #define XNN_ARCH_WASM 1
    #define XNN_ARCH_WASMSIMD 0
    #define XNN_ARCH_WASMRELAXEDSIMD 0
  #endif
#else
  #define XNN_ARCH_WASM 0
  #define XNN_ARCH_WASMSIMD 0
  #define XNN_ARCH_WASMRELAXEDSIMD 0
#endif

// Define platform identification macros

#if defined(__ANDROID__)
  #define XNN_PLATFORM_ANDROID 1
#else
  #define XNN_PLATFORM_ANDROID 0
#endif

#if defined(__linux__)
  #define XNN_PLATFORM_LINUX 1
#else
  #define XNN_PLATFORM_LINUX 0
#endif

#if defined(__APPLE__) && TARGET_OS_IPHONE
  // iOS on iPhone / iPad Touch, iPad OS, watchOS, or tvOS
  #define XNN_PLATFORM_IOS 1
#else
  #define XNN_PLATFORM_IOS 0
#endif

#if defined(__APPLE__) && TARGET_OS_MAC
  #define XNN_PLATFORM_MAC 1
#else
  #define XNN_PLATFORM_MAC 0
#endif

#if XNN_PLATFORM_ANDROID || XNN_PLATFORM_IOS
  #define XNN_PLATFORM_MOBILE 1
#else
  #define XNN_PLATFORM_MOBILE 0
#endif

#if defined(__EMSCRIPTEN__) || defined(__wasm__)
  #define XNN_PLATFORM_WEB 1
#else
  #define XNN_PLATFORM_WEB 0
#endif

#if defined(_WIN32)
  #define XNN_PLATFORM_WINDOWS 1
#else
  #define XNN_PLATFORM_WINDOWS 0
#endif

#if defined(__Fuchsia__)
  #define XNN_PLATFORM_FUCHSIA 1
#else
  #define XNN_PLATFORM_FUCHSIA 0
#endif

#if (XNN_ARCH_ARM || XNN_ARCH_ARM64) && !XNN_PLATFORM_IOS && !XNN_PLATFORM_FUCHSIA
  #define XNN_PLATFORM_JIT 1
#else
  #define XNN_PLATFORM_JIT 0
#endif

// Define compile identification macros

#if defined(__clang__)
  #define XNN_COMPILER_CLANG 1
#elif defined(__INTEL_COMPILER)
  #define XNN_COMPILER_ICC 1
#elif defined(_MSC_VER)
  #define XNN_COMPILER_MSVC 1
#elif defined(__GNUC__)
  #define XNN_COMPILER_GCC 1
#endif

#ifndef XNN_COMPILER_CLANG
  #define XNN_COMPILER_CLANG 0
#endif

#ifndef XNN_COMPILER_GCC
  #define XNN_COMPILER_GCC 0
#endif

#ifndef XNN_COMPILER_MSVC
  #define XNN_COMPILER_MSVC 0
#endif

#ifndef XNN_COMPILER_ICC
  #define XNN_COMPILER_ICC 0
#endif


#ifndef XNN_TEST_MODE
  #define XNN_TEST_MODE 0
#endif

#ifndef XNN_MAX_UARCH_TYPES
  #if (XNN_ARCH_ARM || XNN_ARCH_ARM64) && !XNN_PLATFORM_IOS
    #define XNN_MAX_UARCH_TYPES 3
  #else
    #define XNN_MAX_UARCH_TYPES 1
  #endif
#endif

#define XNN_UARCH_DEFAULT 0

#if defined(__has_builtin)
  #define XNN_COMPILER_HAS_BUILTIN(builtin) __has_builtin(builtin)
#else
  #define XNN_COMPILER_HAS_BUILTIN(builtin) 0
#endif

#if defined(__has_feature)
  #define XNN_COMPILER_HAS_FEATURE(builtin) __has_feature(builtin)
#else
  #define XNN_COMPILER_HAS_FEATURE(builtin) 0
#endif

#if defined(__GNUC__)
  #if defined(__clang__) || (__GNUC__ > 4 || __GNUC__ == 4 && __GNUC_MINOR__ >= 5)
    #define XNN_UNREACHABLE do { __builtin_unreachable(); } while (0)
  #else
    #define XNN_UNREACHABLE do { __builtin_trap(); } while (0)
  #endif
#elif defined(_MSC_VER)
  #define XNN_UNREACHABLE __assume(0)
#else
  #define XNN_UNREACHABLE do { } while (0)
#endif

#if defined(__GNUC__)
  #define XNN_ALIGN(alignment) __attribute__((__aligned__(alignment)))
#elif defined(_MSC_VER)
  #define XNN_ALIGN(alignment) __declspec(align(alignment))
#else
  #error "Platform-specific implementation of XNN_ALIGN required"
#endif

#if defined(__GNUC__)
  #define XNN_UNALIGNED __attribute__((__aligned__(1)))
#elif defined(_MSC_VER)
  #if defined(_M_IX86)
    #define XNN_UNALIGNED
  #else
    #define XNN_UNALIGNED __unaligned
  #endif
#else
  #error "Platform-specific implementation of XNN_UNALIGNED required"
#endif

#define XNN_COUNT_OF(array) (sizeof(array) / sizeof(0[array]))

#if defined(__cplusplus) || XNN_COMPILER_MSVC
  #define XNN_MIN_ELEMENTS(count) count
#else
  #define XNN_MIN_ELEMENTS(count) static count
#endif

#if defined(__GNUC__)
  #define XNN_LIKELY(condition) (__builtin_expect(!!(condition), 1))
  #define XNN_UNLIKELY(condition) (__builtin_expect(!!(condition), 0))
#else
  #define XNN_LIKELY(condition) (!!(condition))
  #define XNN_UNLIKELY(condition) (!!(condition))
#endif

#if XNN_COMPILER_HAS_BUILTIN(__builtin_unpredictable)
  #define XNN_UNPREDICTABLE(condition) (__builtin_unpredictable(!!(condition)))
#elif defined(__GNUC__) && (__GNUC__ >= 9) && !defined(__INTEL_COMPILER)
  #define XNN_UNPREDICTABLE(condition) (__builtin_expect_with_probability(!!(condition), 0, 0.5))
#else
  #define XNN_UNPREDICTABLE(condition) (!!(condition))
#endif

#if XNN_COMPILER_HAS_FEATURE(thread_sanitizer)
  #define XNN_DISABLE_TSAN __attribute__((__no_sanitize__("thread")))
#else
  #define XNN_DISABLE_TSAN
#endif

#if XNN_COMPILER_HAS_FEATURE(memory_sanitizer)
  #define XNN_DISABLE_MSAN __attribute__((__no_sanitize__("memory")))
#else
  #define XNN_DISABLE_MSAN
#endif

#if XNN_COMPILER_HAS_FEATURE(hwaddress_sanitizer)
  #define XNN_DISABLE_HWASAN __attribute__((__no_sanitize__("hwaddress")))
#else
  #define XNN_DISABLE_HWASAN
#endif

#define XNN_OOB_READS XNN_DISABLE_TSAN XNN_DISABLE_MSAN XNN_DISABLE_HWASAN

#if defined(__GNUC__)
  #define XNN_INTRINSIC inline __attribute__((__always_inline__, __artificial__))
#elif defined(_MSC_VER)
  #define XNN_INTRINSIC __forceinline
#else
  #define XNN_INTRINSIC inline
#endif

#if defined(__GNUC__)
  #define XNN_INLINE inline __attribute__((__always_inline__))
#elif defined(_MSC_VER)
  #define XNN_INLINE __forceinline
#else
  #define XNN_INLINE inline
#endif

#ifndef XNN_INTERNAL
  #if defined(__ELF__)
    #define XNN_INTERNAL __attribute__((__visibility__("internal")))
  #elif defined(__MACH__)
    #define XNN_INTERNAL __attribute__((__visibility__("hidden")))
  #else
    #define XNN_INTERNAL
  #endif
#endif

#ifndef XNN_PRIVATE
  #if defined(__ELF__)
    #define XNN_PRIVATE __attribute__((__visibility__("hidden")))
  #elif defined(__MACH__)
    #define XNN_PRIVATE __attribute__((__visibility__("hidden")))
  #else
    #define XNN_PRIVATE
  #endif
#endif
