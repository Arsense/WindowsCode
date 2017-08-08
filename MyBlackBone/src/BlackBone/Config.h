#pragma once

// Lib/Dll switch
//如果导出 导入函数都没有定义

#if !defined(BLACKBONE_EXPORTS) && !defined(BLACKBONE_IMPORTS) && !defined(BLACKBONE_STATIC)
#define BLACKBONE_STATIC
#endif


#if defined(_MSC_VER)

#define COMPILER_MSVC

#if defined(BLACKBONE_IMPORTS)
#define BLACKBONE_API __declspec(dllimport)
#elif defined(BLACKBONE_EXPORTS)
#define BLACKBONE_API __declspec(dllexport)
#else
#define BLACKBONE_API
#endif

#elif defined(__GNUC__)
#define COMPILER_GCC
#define BLACKBONE_API
#else
#error "Unknown or unsupported compiler"
#endif