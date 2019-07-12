/* +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
Copyright (c) 2008-2017, Petr Kobalicek

This software is provided 'as-is', without any express or implied
warranty. In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not
   claim that you wrote the original software. If you use this software
   in a product, an acknowledgment in the product documentation would be
   appreciated but is not required.
2. Altered source versions must be plainly marked as such, and must not be
   misrepresented as being the original software.
3. This notice may not be removed or altered from any source distribution.
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */
// [AsmJit]
// Complete x86/x64 JIT and Remote Assembler for C++.
//
// [License]
// Zlib - See LICENSE.md file in the package.

// [Dependencies]
#if !defined(_ASMJIT_BUILD_H)
# include "./build.h"
#endif // !_ASMJIT_BUILD_H

// [Guard]
#if !defined(ASMJIT_API_SCOPE)
# define ASMJIT_API_SCOPE
#else
# error "[asmjit] api-scope is already active, previous scope not closed by asmjit_apiend.h?"
#endif // ASMJIT_API_SCOPE

// ============================================================================
// [C++ Support]
// ============================================================================

// [NoExcept]
#if !ASMJIT_CC_HAS_NOEXCEPT && !defined(noexcept)
# define noexcept ASMJIT_NOEXCEPT
# define ASMJIT_UNDEF_NOEXCEPT
#endif // !ASMJIT_CC_HAS_NOEXCEPT && !noexcept

// [NullPtr]
#if !ASMJIT_CC_HAS_NULLPTR && !defined(nullptr)
# define nullptr NULL
# define ASMJIT_UNDEF_NULLPTR
#endif // !ASMJIT_CC_HAS_NULLPTR && !nullptr

// [Override]
#if !ASMJIT_CC_HAS_OVERRIDE && !defined(override)
# define override
# define ASMJIT_UNDEF_OVERRIDE
#endif // !ASMJIT_CC_HAS_OVERRIDE && !override

// ============================================================================
// [Compiler Support]
// ============================================================================

// [Clang]
#if ASMJIT_CC_CLANG
# pragma clang diagnostic push
# pragma clang diagnostic ignored "-Wc++11-extensions"
# pragma clang diagnostic ignored "-Wconstant-logical-operand"
# pragma clang diagnostic ignored "-Wunnamed-type-template-args"
#endif // ASMJIT_CC_CLANG

// [GCC]
#if ASMJIT_CC_GCC
# pragma GCC diagnostic push
# if ASMJIT_CC_GCC_GE(7, 0, 0)
# endif
# if ASMJIT_CC_GCC_GE(8, 0, 0)
#  pragma GCC diagnostic ignored "-Wclass-memaccess"
# endif
#endif // ASMJIT_CC_GCC

// [MSC]
#if ASMJIT_CC_MSC
# pragma warning(push)
# pragma warning(disable: 4127) // conditional expression is constant
# pragma warning(disable: 4201) // nameless struct/union
# pragma warning(disable: 4244) // '+=' : conversion from 'int' to 'x', possible loss of data
# pragma warning(disable: 4251) // struct needs to have dll-interface to be used by clients of struct ...
# pragma warning(disable: 4275) // non dll-interface struct ... used as base for dll-interface struct
# pragma warning(disable: 4355) // this used in base member initializer list
# pragma warning(disable: 4480) // specifying underlying type for enum
# pragma warning(disable: 4800) // forcing value to bool 'true' or 'false'
# pragma warning(disable: 4838) // comversion from 'int' to ...
# if _MSC_VER < 1900
#  if !defined(vsnprintf)
#   define ASMJIT_UNDEF_VSNPRINTF
#   define vsnprintf _vsnprintf
#  endif // !vsnprintf
#  if !defined(snprintf)
#   define ASMJIT_UNDEF_SNPRINTF
#   define snprintf _snprintf
#  endif // !snprintf
# endif
#endif // ASMJIT_CC_MSC

// ============================================================================
// [Custom Macros]
// ============================================================================

// [ASMJIT_NON...]
#if ASMJIT_CC_HAS_DELETE_FUNCTION
#define ASMJIT_NONCONSTRUCTIBLE(...)                         \
private:                                                     \
  __VA_ARGS__() = delete;                                    \
  __VA_ARGS__(const __VA_ARGS__& other) = delete;            \
  __VA_ARGS__& operator=(const __VA_ARGS__& other) = delete; \
public:
#define ASMJIT_NONCOPYABLE(...)                              \
private:                                                     \
  __VA_ARGS__(const __VA_ARGS__& other) = delete;            \
  __VA_ARGS__& operator=(const __VA_ARGS__& other) = delete; \
public:
#else
#define ASMJIT_NONCONSTRUCTIBLE(...)                         \
private:                                                     \
  inline __VA_ARGS__();                                      \
  inline __VA_ARGS__(const __VA_ARGS__& other);              \
  inline __VA_ARGS__& operator=(const __VA_ARGS__& other);   \
public:
#define ASMJIT_NONCOPYABLE(...)                              \
private:                                                     \
  inline __VA_ARGS__(const __VA_ARGS__& other);              \
  inline __VA_ARGS__& operator=(const __VA_ARGS__& other);   \
public:
#endif // ASMJIT_CC_HAS_DELETE_FUNCTION

// [ASMJIT_ENUM]
#if defined(_MSC_VER) && _MSC_VER >= 1400
# define ASMJIT_ENUM(NAME) enum NAME : uint32_t
#else
# define ASMJIT_ENUM(NAME) enum NAME
#endif
