/***************************************************************************
* Copyright (c) 2016, Johan Mabille and Sylvain Corlay                     *
*                                                                          *
* Distributed under the terms of the BSD 3-Clause License.                 *
*                                                                          *
* The full license is in the file LICENSE, distributed with this software. *
****************************************************************************/

#include <iostream>
#include <fstream>
#include <map>

#include "gtest/gtest.h"

#include "xsimd/memory/xsimd_aligned_allocator.hpp"
#include "xsimd/types/xsimd_types_include.hpp"

#include "xsimd_basic_test.hpp"

namespace xsimd
{
    template <class T, size_t N, size_t A>
    bool test_simd(std::ostream& out, const std::string& name)
    {
        simd_basic_tester<T, N, A> tester(name);
        return test_simd_basic(out, tester);
    }

    template <class T, size_t N, size_t A>
    bool test_simd_int(std::ostream& out, const std::string& name)
    {
        simd_int_basic_tester<T, N, A> tester(name);
        return test_simd_int_basic(out, tester);
    }

    template <size_t N, size_t A>
    bool test_simd_convert(std::ostream& out, const std::string& name)
    {
        simd_convert_tester<N, A> tester(name);
        return test_simd_conversion(out, tester);
    }
}

#if XSIMD_X86_INSTR_SET >= XSIMD_X86_SSE2_VERSION
TEST(xsimd, sse_float_basic)
{
    std::ofstream out("log/sse_float_basic.log", std::ios_base::out);
    bool res = xsimd::test_simd<float, 4, 16>(out, "sse float");
    EXPECT_TRUE(res);
}

TEST(xsimd, sse_double_basic)
{
    std::ofstream out("log/sse_double_basic.log", std::ios_base::out);
    bool res = xsimd::test_simd<double, 2, 16>(out, "sse double");
    EXPECT_TRUE(res);
}

TEST(xsimd, sse_int_basic)
{
    std::ofstream out("log/sse_int_basic.log", std::ios_base::out);
    bool res = xsimd::test_simd_int<int, 4, 16>(out, "sse int");
    EXPECT_TRUE(res);
}

TEST(xsimd, sse_conversion)
{
    std::ofstream out("log/sse_conversion.log", std::ios_base::out);
    bool res = xsimd::test_simd_convert<2, 16>(out, "sse conversion");
    EXPECT_TRUE(res);
}
#endif

#if XSIMD_X86_INSTR_SET >= XSIMD_X86_AVX_VERSION
TEST(xsimd, avx_float_basic)
{
    std::ofstream out("log/avx_float_basic.log", std::ios_base::out);
    bool res = xsimd::test_simd<float, 8, 32>(out, "avx float");
    EXPECT_TRUE(res);
}

TEST(xsimd, avx_double_basic)
{
    std::ofstream out("log/avx_double_basic.log", std::ios_base::out);
    bool res = xsimd::test_simd<double, 4, 32>(out, "avx double");
    EXPECT_TRUE(res);
}

TEST(xsimd, avx_int_basic)
{
    std::ofstream out("log/sse_avx_basic.log", std::ios_base::out);
    bool res = xsimd::test_simd_int<int, 8, 32>(out, "avx int");
    EXPECT_TRUE(res);
}

TEST(xsimd, avx_conversion)
{
    std::ofstream out("log/avx_conversion.log", std::ios_base::out);
    bool res = xsimd::test_simd_convert<4, 32>(out, "avx conversion");
    EXPECT_TRUE(res);
}
#endif

