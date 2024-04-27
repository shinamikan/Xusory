#pragma once

#if defined(__AVX512F__) || defined(__AVX512CD__) || defined(__AVX512BW__) || defined(__AVX512DQ__)
#define SUPPORT_AVX512
#define SIMD_LEVEL 5
#elif defined(__AVX2__) 
#define SUPPORT_AVX2
#define SIMD_LEVEL 4
#elif defined(__AVX__)
#define SUPPORT_AVX
#define SIMD_LEVEL 3
#elif defined(_M_IX86_FP) && _M_IX86_FP == 2
#define SUPPORT_SSE2
#define SIMD_LEVEL 2
#elif defined(_M_IX86_FP) && _M_IX86_FP == 1
#define SUPPORT_SSE
#define SIMD_LEVEL 1
#else
#define SIMD_LEVEL 0
#endif

#define SHUFFLE2(x, y) (_MM_SHUFFLE(3, 2, y, x))
#define SHUFFLE3(x, y, z) (_MM_SHUFFLE(3, z, y, x))
#define SHUFFLE4(x, y, z, w) (_MM_SHUFFLE(w, z, y, x))

#define SHUFFLE_VECTOR2(v, x, y) _mm_shuffle_ps(v, v, SHUFFLE2(x, y))
#define SHUFFLE_VECTOR3(v, x, y, z) _mm_shuffle_ps(v, v, SHUFFLE3(x, y, z))
#define SHUFFLE_VECTOR4(v, x, y, z, w) _mm_shuffle_ps(v, v, SHUFFLE4(x, y, z, w))
