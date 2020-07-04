// Copyright 2019 The TCMalloc Authors
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     https://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "tcmalloc/common.h"

namespace tcmalloc {

// <fixed> is fixed per-size-class overhead due to end-of-span fragmentation
// and other factors. For instance, if we have a 96 byte size class, and use a
// single 8KiB page, then we will hold 85 objects per span, and have 32 bytes
// left over. There is also a fixed component of 48 bytes of TCMalloc metadata
// per span. Together, the fixed overhead would be wasted/allocated =
// (32 + 48) / (8192 - 32) ~= 0.98%.
// There is also a dynamic component to overhead based on mismatches between the
// number of bytes requested and the number of bytes provided by the size class.
// Together they sum to the total overhead; for instance if you asked for a
// 50-byte allocation that rounds up to a 64-byte size class, the dynamic
// overhead would be 28%, and if <fixed> were 22% it would mean (on average)
// 25 bytes of overhead for allocations of that size.

// clang-format off
#if defined(__cpp_aligned_new) && __STDCPP_DEFAULT_NEW_ALIGNMENT__ <= 8
#if TCMALLOC_PAGE_SHIFT == 13
static_assert(kMaxSize == 262144, "kMaxSize mismatch");
const SizeClassInfo SizeMap::kSizeClasses[] = {
    // <bytes>, <pages>, <batch size>    <fixed>
    {        0,       0,           0},  // +Inf%
    {        8,       1,          32},  // 0.59%
    {       16,       1,          32},  // 0.59%
    {       24,       1,          32},  // 0.68%
    {       32,       1,          32},  // 0.59%
    {       40,       1,          32},  // 0.98%
    {       48,       1,          32},  // 0.98%
    {       56,       1,          32},  // 0.78%
    {       64,       1,          32},  // 0.59%
    {       72,       1,          32},  // 1.28%
    {       80,       1,          32},  // 0.98%
    {       88,       1,          32},  // 0.68%
    {       96,       1,          32},  // 0.98%
    {      104,       1,          32},  // 1.58%
    {      112,       1,          32},  // 0.78%
    {      120,       1,          32},  // 0.98%
    {      128,       1,          32},  // 0.59%
    {      136,       1,          32},  // 0.98%
    {      144,       1,          32},  // 2.18%
    {      160,       1,          32},  // 0.98%
    {      176,       1,          32},  // 1.78%
    {      192,       1,          32},  // 2.18%
    {      208,       1,          32},  // 1.58%
    {      224,       1,          32},  // 2.18%
    {      240,       1,          32},  // 0.98%
    {      256,       1,          32},  // 0.59%
    {      272,       1,          32},  // 0.98%
    {      288,       1,          32},  // 2.18%
    {      312,       1,          32},  // 1.58%
    {      336,       1,          32},  // 2.18%
    {      352,       1,          32},  // 1.78%
    {      384,       1,          32},  // 2.18%
    {      408,       1,          32},  // 0.98%
    {      424,       1,          32},  // 2.28%
    {      448,       1,          32},  // 2.18%
    {      480,       1,          32},  // 0.98%
    {      512,       1,          32},  // 0.59%
    {      576,       1,          32},  // 2.18%
    {      640,       1,          32},  // 7.29%
    {      704,       1,          32},  // 6.40%
    {      768,       1,          32},  // 7.29%
    {      896,       1,          32},  // 2.18%
    {     1024,       1,          32},  // 0.59%
    {     1152,       2,          32},  // 1.88%
    {     1280,       2,          32},  // 6.98%
    {     1408,       2,          32},  // 6.10%
    {     1536,       2,          32},  // 6.98%
    {     1792,       2,          32},  // 1.88%
    {     2048,       2,          32},  // 0.29%
    {     2304,       2,          28},  // 1.88%
    {     2688,       2,          24},  // 1.88%
    {     3200,       2,          20},  // 2.70%
    {     3456,       3,          18},  // 1.79%
    {     3584,       4,          18},  // 1.74%
    {     4096,       2,          16},  // 0.29%
    {     4736,       3,          13},  // 3.99%
    {     5376,       2,          12},  // 1.88%
    {     6144,       3,          10},  // 0.20%
    {     6528,       4,          10},  // 0.54%
    {     7168,       7,           9},  // 0.08%
    {     8192,       2,           8},  // 0.29%
    {     9472,       5,           6},  // 8.23%
    {    10240,       4,           6},  // 6.82%
    {    12288,       3,           5},  // 0.20%
    {    14336,       7,           4},  // 0.08%
    {    16384,       2,           4},  // 0.29%
    {    20480,       5,           3},  // 0.12%
    {    24576,       3,           2},  // 0.20%
    {    28672,       7,           2},  // 0.08%
    {    32768,       4,           2},  // 0.15%
    {    40960,       5,           2},  // 0.12%
    {    49152,       6,           2},  // 0.10%
    {    57344,       7,           2},  // 0.08%
    {    65536,       8,           2},  // 0.07%
    {    73728,       9,           2},  // 0.07%
    {    81920,      10,           2},  // 0.06%
    {    98304,      12,           2},  // 0.05%
    {   106496,      13,           2},  // 0.05%
    {   114688,      14,           2},  // 0.04%
    {   131072,      16,           2},  // 0.04%
    {   147456,      18,           2},  // 0.03%
    {   163840,      20,           2},  // 0.03%
    {   180224,      22,           2},  // 0.03%
    {   204800,      25,           2},  // 0.02%
    {   229376,      28,           2},  // 0.02%
    {   262144,      32,           2},  // 0.02%
};
#elif TCMALLOC_PAGE_SHIFT == 15
static_assert(kMaxSize == 262144, "kMaxSize mismatch");
const SizeClassInfo SizeMap::kSizeClasses[] = {
    // <bytes>, <pages>, <batch size>    <fixed>
    {        0,       0,           0},  // +Inf%
    {        8,       1,          32},  // 0.15%
    {       16,       1,          32},  // 0.15%
    {       24,       1,          32},  // 0.17%
    {       32,       1,          32},  // 0.15%
    {       40,       1,          32},  // 0.17%
    {       48,       1,          32},  // 0.24%
    {       56,       1,          32},  // 0.17%
    {       64,       1,          32},  // 0.15%
    {       72,       1,          32},  // 0.17%
    {       80,       1,          32},  // 0.29%
    {       88,       1,          32},  // 0.24%
    {       96,       1,          32},  // 0.24%
    {      104,       1,          32},  // 0.17%
    {      112,       1,          32},  // 0.34%
    {      120,       1,          32},  // 0.17%
    {      128,       1,          32},  // 0.15%
    {      144,       1,          32},  // 0.39%
    {      160,       1,          32},  // 0.54%
    {      176,       1,          32},  // 0.24%
    {      192,       1,          32},  // 0.54%
    {      208,       1,          32},  // 0.49%
    {      224,       1,          32},  // 0.34%
    {      240,       1,          32},  // 0.54%
    {      256,       1,          32},  // 0.15%
    {      280,       1,          32},  // 0.17%
    {      304,       1,          32},  // 0.89%
    {      336,       1,          32},  // 0.69%
    {      368,       1,          32},  // 0.20%
    {      416,       1,          32},  // 1.13%
    {      464,       1,          32},  // 1.03%
    {      512,       1,          32},  // 0.15%
    {      576,       1,          32},  // 1.74%
    {      640,       1,          32},  // 0.54%
    {      704,       1,          32},  // 1.33%
    {      832,       1,          32},  // 1.13%
    {      896,       1,          32},  // 1.74%
    {     1024,       1,          32},  // 0.15%
    {     1152,       1,          32},  // 1.74%
    {     1280,       1,          32},  // 2.55%
    {     1408,       1,          32},  // 1.33%
    {     1536,       1,          32},  // 1.74%
    {     1792,       1,          32},  // 1.74%
    {     2048,       1,          32},  // 0.15%
    {     2176,       1,          30},  // 0.54%
    {     2432,       1,          26},  // 3.80%
    {     2688,       1,          24},  // 1.74%
    {     2944,       1,          22},  // 1.33%
    {     3200,       1,          20},  // 2.55%
    {     3584,       1,          18},  // 1.74%
    {     4096,       1,          16},  // 0.15%
    {     4608,       1,          14},  // 1.74%
    {     5376,       1,          12},  // 1.74%
    {     6528,       1,          10},  // 0.54%
    {     8192,       1,           8},  // 0.15%
    {     9344,       2,           7},  // 0.27%
    {    10880,       1,           6},  // 0.54%
    {    13056,       2,           5},  // 0.47%
    {    13952,       3,           4},  // 0.70%
    {    16384,       1,           4},  // 0.15%
    {    19072,       3,           3},  // 3.14%
    {    21760,       2,           3},  // 0.47%
    {    24576,       3,           2},  // 0.05%
    {    28032,       6,           2},  // 0.22%
    {    32768,       1,           2},  // 0.15%
    {    38144,       5,           2},  // 7.41%
    {    40960,       4,           2},  // 6.71%
    {    49152,       3,           2},  // 0.05%
    {    57344,       7,           2},  // 0.02%
    {    65536,       2,           2},  // 0.07%
    {    81920,       5,           2},  // 0.03%
    {    98304,       3,           2},  // 0.05%
    {   114688,       7,           2},  // 0.02%
    {   131072,       4,           2},  // 0.04%
    {   163840,       5,           2},  // 0.03%
    {   196608,       6,           2},  // 0.02%
    {   229376,       7,           2},  // 0.02%
    {   262144,       8,           2},  // 0.02%
};
#elif TCMALLOC_PAGE_SHIFT == 18
#ifndef TCMALLOC_4M_MAX_SIZE
static_assert(kMaxSize == 262144, "kMaxSize mismatch");
#else
static_assert(kMaxSize == 4<<20, "kMaxSize mismatch");
#endif
const SizeClassInfo SizeMap::kSizeClasses[] = {
    // <bytes>, <pages>, <batch size>    <fixed>
    {        0,       0,           0},  // +Inf%
    {        8,       1,          32},  // 0.02%
    {       16,       1,          32},  // 0.02%
    {       24,       1,          32},  // 0.02%
    {       32,       1,          32},  // 0.02%
    {       40,       1,          32},  // 0.03%
    {       48,       1,          32},  // 0.02%
    {       56,       1,          32},  // 0.02%
    {       64,       1,          32},  // 0.02%
    {       72,       1,          32},  // 0.04%
    {       80,       1,          32},  // 0.04%
    {       88,       1,          32},  // 0.05%
    {       96,       1,          32},  // 0.04%
    {      104,       1,          32},  // 0.04%
    {      112,       1,          32},  // 0.04%
    {      128,       1,          32},  // 0.02%
    {      144,       1,          32},  // 0.04%
    {      160,       1,          32},  // 0.04%
    {      176,       1,          32},  // 0.05%
    {      192,       1,          32},  // 0.04%
    {      216,       1,          32},  // 0.07%
    {      232,       1,          32},  // 0.10%
    {      256,       1,          32},  // 0.02%
    {      288,       1,          32},  // 0.04%
    {      304,       1,          32},  // 0.05%
    {      320,       1,          32},  // 0.04%
    {      344,       1,          32},  // 0.02%
    {      384,       1,          32},  // 0.12%
    {      416,       1,          32},  // 0.04%
    {      464,       1,          32},  // 0.19%
    {      512,       1,          32},  // 0.02%
    {      576,       1,          32},  // 0.04%
    {      640,       1,          32},  // 0.17%
    {      704,       1,          32},  // 0.12%
    {      832,       1,          32},  // 0.04%
    {      960,       1,          32},  // 0.04%
    {     1024,       1,          32},  // 0.02%
    {     1152,       1,          32},  // 0.26%
    {     1280,       1,          32},  // 0.41%
    {     1408,       1,          32},  // 0.12%
    {     1664,       1,          32},  // 0.36%
    {     1792,       1,          32},  // 0.21%
    {     1920,       1,          32},  // 0.41%
    {     2048,       1,          32},  // 0.02%
    {     2176,       1,          30},  // 0.41%
    {     2304,       1,          28},  // 0.71%
    {     2432,       1,          26},  // 0.76%
    {     2688,       1,          24},  // 0.56%
    {     2944,       1,          22},  // 0.07%
    {     3328,       1,          19},  // 1.00%
    {     3584,       1,          18},  // 0.21%
    {     4096,       1,          16},  // 0.02%
    {     4736,       1,          13},  // 0.66%
    {     5120,       1,          12},  // 0.41%
    {     5504,       1,          11},  // 1.35%
    {     5760,       1,          11},  // 1.15%
    {     6144,       1,          10},  // 1.61%
    {     6528,       1,          10},  // 0.41%
    {     7168,       1,           9},  // 1.61%
    {     8192,       1,           8},  // 0.02%
#ifndef TCMALLOC_4M_MAX_SIZE
    {     8704,       1,           7},  // 0.41%
    {     9600,       1,           6},  // 1.15%
    {    10880,       1,           6},  // 0.41%
    {    11904,       1,           5},  // 0.12%
#endif
    {    13056,       1,           5},  // 0.41%
    {    14464,       1,           4},  // 0.71%
    {    16384,       1,           4},  // 0.02%
    {    18688,       1,           3},  // 0.21%
    {    21760,       1,           3},  // 0.41%
    {    23808,       1,           2},  // 0.12%
    {    26112,       1,           2},  // 0.41%
    {    29056,       1,           2},  // 0.26%
    {    32768,       1,           2},  // 0.02%
    {    37376,       1,           2},  // 0.21%
    {    43648,       1,           2},  // 0.12%
    {    45568,       2,           2},  // 4.61%
    {    52352,       1,           2},  // 0.17%
    {    56064,       2,           2},  // 3.92%
    {    65536,       1,           2},  // 0.02%
    {    74880,       2,           2},  // 0.03%
    {    87296,       1,           2},  // 0.12%
    {   104832,       2,           2},  // 0.03%
    {   112256,       3,           2},  // 0.09%
    {   131072,       1,           2},  // 0.02%
    {   149760,       3,           2},  // 5.03%
    {   174720,       2,           2},  // 0.03%
    {   196608,       3,           2},  // 0.01%
    {   209664,       4,           2},  // 0.03%
    {   262144,       1,           2},  // 0.02%
#ifdef TCMALLOC_4M_MAX_SIZE
    {  512<<10,       2,           2},
    {    1<<20,       4,           2},
    {    2<<20,       8,           2},
    {    4<<20,      16,           2},
#endif
};
#elif TCMALLOC_PAGE_SHIFT == 12
static_assert(kMaxSize == 8192, "kMaxSize mismatch");
const SizeClassInfo SizeMap::kSizeClasses[] = {
    // <bytes>, <pages>, <batch size>    <fixed>
    {        0,       0,           0},  // +Inf%
    {        8,       1,          32},  // 1.17%
    {       16,       1,          32},  // 1.17%
    {       24,       1,          32},  // 1.57%
    {       32,       1,          32},  // 1.17%
    {       40,       1,          32},  // 1.57%
    {       48,       1,          32},  // 1.57%
    {       56,       1,          32},  // 1.37%
    {       64,       1,          32},  // 1.17%
    {       72,       1,          32},  // 2.78%
    {       80,       1,          32},  // 1.57%
    {       96,       1,          32},  // 2.78%
    {      104,       1,          32},  // 2.17%
    {      112,       1,          32},  // 2.78%
    {      128,       1,          32},  // 1.17%
    {      144,       1,          32},  // 2.78%
    {      160,       1,          32},  // 3.60%
    {      176,       1,          32},  // 2.37%
    {      192,       1,          32},  // 2.78%
    {      208,       1,          32},  // 4.86%
    {      240,       1,          32},  // 1.57%
    {      272,       1,          32},  // 1.57%
    {      288,       1,          32},  // 2.78%
    {      312,       1,          32},  // 2.17%
    {      336,       1,          32},  // 2.78%
    {      408,       1,          32},  // 1.57%
    {      448,       1,          32},  // 2.78%
    {      512,       1,          32},  // 1.17%
    {      576,       2,          32},  // 2.18%
    {      640,       2,          32},  // 7.29%
    {      704,       2,          32},  // 6.40%
    {      896,       2,          32},  // 2.18%
    {     1024,       2,          32},  // 0.59%
    {     1152,       3,          32},  // 7.08%
    {     1280,       3,          32},  // 7.08%
    {     1536,       3,          32},  // 0.39%
    {     1792,       4,          32},  // 1.88%
    {     2048,       4,          32},  // 0.29%
    {     2304,       4,          28},  // 1.88%
    {     2688,       4,          24},  // 1.88%
    {     3200,       4,          20},  // 2.70%
    {     4096,       4,          16},  // 0.29%
    {     4736,       5,          13},  // 8.36%
    {     6144,       3,          10},  // 0.39%
    {     7168,       7,           9},  // 0.17%
    {     8192,       4,           8},  // 0.29%
};
#else
#error "Unsupported TCMALLOC_PAGE_SHIFT value!"
#endif
#else
#if TCMALLOC_PAGE_SHIFT == 13
static_assert(kMaxSize == 262144, "kMaxSize mismatch");
const SizeClassInfo SizeMap::kSizeClasses[] = {
    // <bytes>, <pages>, <batch size>    <fixed>
    {        0,       0,           0},  // +Inf%
    {        8,       1,          32},  // 0.59%
    {       16,       1,          32},  // 0.59%
    {       32,       1,          32},  // 0.59%
    {       48,       1,          32},  // 0.98%
    {       64,       1,          32},  // 0.59%
    {       80,       1,          32},  // 0.98%
    {       96,       1,          32},  // 0.98%
    {      112,       1,          32},  // 0.78%
    {      128,       1,          32},  // 0.59%
    {      144,       1,          32},  // 2.18%
    {      160,       1,          32},  // 0.98%
    {      176,       1,          32},  // 1.78%
    {      192,       1,          32},  // 2.18%
    {      208,       1,          32},  // 1.58%
    {      224,       1,          32},  // 2.18%
    {      240,       1,          32},  // 0.98%
    {      256,       1,          32},  // 0.59%
    {      272,       1,          32},  // 0.98%
    {      288,       1,          32},  // 2.18%
    {      304,       1,          32},  // 4.25%
    {      320,       1,          32},  // 3.00%
    {      336,       1,          32},  // 2.18%
    {      352,       1,          32},  // 1.78%
    {      368,       1,          32},  // 1.78%
    {      384,       1,          32},  // 2.18%
    {      400,       1,          32},  // 3.00%
    {      416,       1,          32},  // 4.25%
    {      448,       1,          32},  // 2.18%
    {      480,       1,          32},  // 0.98%
    {      512,       1,          32},  // 0.59%
    {      576,       1,          32},  // 2.18%
    {      640,       1,          32},  // 7.29%
    {      704,       1,          32},  // 6.40%
    {      768,       1,          32},  // 7.29%
    {      896,       1,          32},  // 2.18%
    {     1024,       1,          32},  // 0.59%
    {     1152,       2,          32},  // 1.88%
    {     1280,       2,          32},  // 6.98%
    {     1408,       2,          32},  // 6.10%
    {     1536,       2,          32},  // 6.98%
    {     1792,       2,          32},  // 1.88%
    {     2048,       2,          32},  // 0.29%
    {     2304,       2,          28},  // 1.88%
    {     2688,       2,          24},  // 1.88%
    {     2816,       3,          23},  // 9.30%
    {     3200,       2,          20},  // 2.70%
    {     3456,       3,          18},  // 1.79%
    {     3584,       4,          18},  // 1.74%
    {     4096,       2,          16},  // 0.29%
    {     4736,       3,          13},  // 3.99%
    {     5376,       2,          12},  // 1.88%
    {     6144,       3,          10},  // 0.20%
    {     6528,       4,          10},  // 0.54%
    {     6784,       5,           9},  // 0.75%
    {     7168,       7,           9},  // 0.08%
    {     8192,       2,           8},  // 0.29%
    {     9472,       5,           6},  // 8.23%
    {    10240,       4,           6},  // 6.82%
    {    12288,       3,           5},  // 0.20%
    {    13568,       5,           4},  // 0.75%
    {    14336,       7,           4},  // 0.08%
    {    16384,       2,           4},  // 0.29%
    {    20480,       5,           3},  // 0.12%
    {    24576,       3,           2},  // 0.20%
    {    28672,       7,           2},  // 0.08%
    {    32768,       4,           2},  // 0.15%
    {    40960,       5,           2},  // 0.12%
    {    49152,       6,           2},  // 0.10%
    {    57344,       7,           2},  // 0.08%
    {    65536,       8,           2},  // 0.07%
    {    73728,       9,           2},  // 0.07%
    {    81920,      10,           2},  // 0.06%
    {    90112,      11,           2},  // 0.05%
    {    98304,      12,           2},  // 0.05%
    {   106496,      13,           2},  // 0.05%
    {   114688,      14,           2},  // 0.04%
    {   131072,      16,           2},  // 0.04%
    {   139264,      17,           2},  // 0.03%
    {   155648,      19,           2},  // 0.03%
    {   172032,      21,           2},  // 0.03%
    {   196608,      24,           2},  // 0.02%
    {   204800,      25,           2},  // 0.02%
    {   221184,      27,           2},  // 0.02%
    {   245760,      30,           2},  // 0.02%
    {   262144,      32,           2},  // 0.02%
};
#elif TCMALLOC_PAGE_SHIFT == 15
static_assert(kMaxSize == 262144, "kMaxSize mismatch");
const SizeClassInfo SizeMap::kSizeClasses[] = {
    // <bytes>, <pages>, <batch size>    <fixed>
    {        0,       0,           0},  // +Inf%
    {        8,       1,          32},  // 0.15%
    {       16,       1,          32},  // 0.15%
    {       32,       1,          32},  // 0.15%
    {       48,       1,          32},  // 0.24%
    {       64,       1,          32},  // 0.15%
    {       80,       1,          32},  // 0.29%
    {       96,       1,          32},  // 0.24%
    {      112,       1,          32},  // 0.34%
    {      128,       1,          32},  // 0.15%
    {      144,       1,          32},  // 0.39%
    {      160,       1,          32},  // 0.54%
    {      176,       1,          32},  // 0.24%
    {      192,       1,          32},  // 0.54%
    {      208,       1,          32},  // 0.49%
    {      224,       1,          32},  // 0.34%
    {      240,       1,          32},  // 0.54%
    {      256,       1,          32},  // 0.15%
    {      272,       1,          32},  // 0.54%
    {      288,       1,          32},  // 0.84%
    {      304,       1,          32},  // 0.89%
    {      336,       1,          32},  // 0.69%
    {      368,       1,          32},  // 0.20%
    {      400,       1,          32},  // 1.28%
    {      416,       1,          32},  // 1.13%
    {      464,       1,          32},  // 1.03%
    {      512,       1,          32},  // 0.15%
    {      576,       1,          32},  // 1.74%
    {      640,       1,          32},  // 0.54%
    {      704,       1,          32},  // 1.33%
    {      768,       1,          32},  // 1.74%
    {      832,       1,          32},  // 1.13%
    {      896,       1,          32},  // 1.74%
    {      960,       1,          32},  // 0.54%
    {     1024,       1,          32},  // 0.15%
    {     1152,       1,          32},  // 1.74%
    {     1280,       1,          32},  // 2.55%
    {     1408,       1,          32},  // 1.33%
    {     1536,       1,          32},  // 1.74%
    {     1664,       1,          32},  // 3.80%
    {     1920,       1,          32},  // 0.54%
    {     2048,       1,          32},  // 0.15%
    {     2176,       1,          30},  // 0.54%
    {     2304,       1,          28},  // 1.74%
    {     2432,       1,          26},  // 3.80%
    {     2688,       1,          24},  // 1.74%
    {     2944,       1,          22},  // 1.33%
    {     3200,       1,          20},  // 2.55%
    {     3584,       1,          18},  // 1.74%
    {     4096,       1,          16},  // 0.15%
    {     4608,       1,          14},  // 1.74%
    {     5376,       1,          12},  // 1.74%
    {     6528,       1,          10},  // 0.54%
    {     7168,       2,           9},  // 1.66%
    {     8192,       1,           8},  // 0.15%
    {     9344,       2,           7},  // 0.27%
    {    10880,       1,           6},  // 0.54%
    {    13056,       2,           5},  // 0.47%
    {    13952,       3,           4},  // 0.70%
    {    16384,       1,           4},  // 0.15%
    {    19072,       3,           3},  // 3.14%
    {    21760,       2,           3},  // 0.47%
    {    24576,       3,           2},  // 0.05%
    {    28032,       6,           2},  // 0.22%
    {    32768,       1,           2},  // 0.15%
    {    38144,       5,           2},  // 7.41%
    {    40960,       4,           2},  // 6.71%
    {    49152,       3,           2},  // 0.05%
    {    57344,       7,           2},  // 0.02%
    {    65536,       2,           2},  // 0.07%
    {    81920,       5,           2},  // 0.03%
    {    98304,       3,           2},  // 0.05%
    {   114688,       7,           2},  // 0.02%
    {   131072,       4,           2},  // 0.04%
    {   163840,       5,           2},  // 0.03%
    {   196608,       6,           2},  // 0.02%
    {   229376,       7,           2},  // 0.02%
    {   262144,       8,           2},  // 0.02%
};
#elif TCMALLOC_PAGE_SHIFT == 18
#ifndef TCMALLOC_4M_MAX_SIZE
static_assert(kMaxSize == 262144, "kMaxSize mismatch");
#else
static_assert(kMaxSize == 4<<20, "kMaxSize mismatch");
#endif
const SizeClassInfo SizeMap::kSizeClasses[] = {
    // <bytes>, <pages>, <batch size>    <fixed>
    {        0,       0,           0},  // +Inf%
    {        8,       1,          32},  // 0.02%
    {       16,       1,          32},  // 0.02%
    {       32,       1,          32},  // 0.02%
    {       48,       1,          32},  // 0.02%
    {       64,       1,          32},  // 0.02%
    {       80,       1,          32},  // 0.04%
    {       96,       1,          32},  // 0.04%
    {      112,       1,          32},  // 0.04%
    {      128,       1,          32},  // 0.02%
    {      144,       1,          32},  // 0.04%
    {      160,       1,          32},  // 0.04%
    {      176,       1,          32},  // 0.05%
    {      192,       1,          32},  // 0.04%
    {      208,       1,          32},  // 0.04%
    {      224,       1,          32},  // 0.04%
    {      240,       1,          32},  // 0.04%
    {      256,       1,          32},  // 0.02%
    {      288,       1,          32},  // 0.04%
    {      304,       1,          32},  // 0.05%
    {      320,       1,          32},  // 0.04%
    {      352,       1,          32},  // 0.12%
    {      384,       1,          32},  // 0.12%
    {      416,       1,          32},  // 0.04%
    {      464,       1,          32},  // 0.19%
    {      512,       1,          32},  // 0.02%
    {      576,       1,          32},  // 0.04%
    {      640,       1,          32},  // 0.17%
    {      704,       1,          32},  // 0.12%
    {      832,       1,          32},  // 0.04%
    {      960,       1,          32},  // 0.04%
    {     1024,       1,          32},  // 0.02%
    {     1152,       1,          32},  // 0.26%
    {     1280,       1,          32},  // 0.41%
    {     1408,       1,          32},  // 0.12%
    {     1536,       1,          32},  // 0.41%
    {     1664,       1,          32},  // 0.36%
    {     1792,       1,          32},  // 0.21%
    {     1920,       1,          32},  // 0.41%
    {     2048,       1,          32},  // 0.02%
    {     2176,       1,          30},  // 0.41%
    {     2304,       1,          28},  // 0.71%
    {     2432,       1,          26},  // 0.76%
    {     2688,       1,          24},  // 0.56%
    {     2944,       1,          22},  // 0.07%
    {     3328,       1,          19},  // 1.00%
    {     3584,       1,          18},  // 0.21%
    {     4096,       1,          16},  // 0.02%
    {     4736,       1,          13},  // 0.66%
    {     5120,       1,          12},  // 0.41%
    {     5504,       1,          11},  // 1.35%
    {     5760,       1,          11},  // 1.15%
    {     6144,       1,          10},  // 1.61%
    {     6528,       1,          10},  // 0.41%
    {     7168,       1,           9},  // 1.61%
    {     7680,       1,           8},  // 0.41%
    {     8192,       1,           8},  // 0.02%
#ifndef TCMALLOC_4M_MAX_SIZE
    {     8704,       1,           7},  // 0.41%
    {     9344,       1,           7},  // 0.21%
    {     9984,       1,           6},  // 1.00%
    {    10880,       1,           6},  // 0.41%
#endif
    {    11904,       1,           5},  // 0.12%
    {    13056,       1,           5},  // 0.41%
    {    14464,       1,           4},  // 0.71%
    {    16384,       1,           4},  // 0.02%
    {    17408,       1,           3},  // 0.41%
    {    18688,       1,           3},  // 0.21%
    {    20096,       1,           3},  // 0.36%
    {    21760,       1,           3},  // 0.41%
    {    23808,       1,           2},  // 0.12%
    {    26112,       1,           2},  // 0.41%
    {    29056,       1,           2},  // 0.26%
    {    32768,       1,           2},  // 0.02%
    {    37376,       1,           2},  // 0.21%
    {    43648,       1,           2},  // 0.12%
    {    45568,       2,           2},  // 4.61%
    {    52352,       1,           2},  // 0.17%
    {    56064,       2,           2},  // 3.92%
    {    65536,       1,           2},  // 0.02%
    {    74880,       2,           2},  // 0.03%
    {    87296,       1,           2},  // 0.12%
    {   104832,       2,           2},  // 0.03%
    {   112256,       3,           2},  // 0.09%
    {   131072,       1,           2},  // 0.02%
    {   149760,       3,           2},  // 5.03%
    {   174720,       2,           2},  // 0.03%
    {   196608,       3,           2},  // 0.01%
    {   209664,       4,           2},  // 0.03%
    {   262144,       1,           2},  // 0.02%
#ifdef TCMALLOC_4M_MAX_SIZE
    {  512<<10,       2,           2},
    {    1<<20,       4,           2},
    {    2<<20,       8,           2},
    {    4<<20,      16,           2},
#endif
};
#elif TCMALLOC_PAGE_SHIFT == 12
static_assert(kMaxSize == 8192, "kMaxSize mismatch");
const SizeClassInfo SizeMap::kSizeClasses[] = {
    // <bytes>, <pages>, <batch size>    <fixed>
    {        0,       0,           0},  // +Inf%
    {        8,       1,          32},  // 1.17%
    {       16,       1,          32},  // 1.17%
    {       32,       1,          32},  // 1.17%
    {       48,       1,          32},  // 1.57%
    {       64,       1,          32},  // 1.17%
    {       80,       1,          32},  // 1.57%
    {       96,       1,          32},  // 2.78%
    {      112,       1,          32},  // 2.78%
    {      128,       1,          32},  // 1.17%
    {      144,       1,          32},  // 2.78%
    {      160,       1,          32},  // 3.60%
    {      176,       1,          32},  // 2.37%
    {      192,       1,          32},  // 2.78%
    {      208,       1,          32},  // 4.86%
    {      224,       1,          32},  // 2.78%
    {      240,       1,          32},  // 1.57%
    {      256,       1,          32},  // 1.17%
    {      272,       1,          32},  // 1.57%
    {      288,       1,          32},  // 2.78%
    {      304,       1,          32},  // 4.86%
    {      336,       1,          32},  // 2.78%
    {      368,       1,          32},  // 2.37%
    {      400,       1,          32},  // 3.60%
    {      448,       1,          32},  // 2.78%
    {      512,       1,          32},  // 1.17%
    {      576,       2,          32},  // 2.18%
    {      640,       2,          32},  // 7.29%
    {      704,       2,          32},  // 6.40%
    {      768,       2,          32},  // 7.29%
    {      896,       2,          32},  // 2.18%
    {     1024,       2,          32},  // 0.59%
    {     1152,       3,          32},  // 7.08%
    {     1280,       3,          32},  // 7.08%
    {     1536,       3,          32},  // 0.39%
    {     1792,       4,          32},  // 1.88%
    {     2048,       4,          32},  // 0.29%
    {     2304,       4,          28},  // 1.88%
    {     2688,       4,          24},  // 1.88%
    {     3200,       4,          20},  // 2.70%
    {     3584,       7,          18},  // 0.17%
    {     4096,       4,          16},  // 0.29%
    {     4736,       5,          13},  // 8.36%
    {     6144,       3,          10},  // 0.39%
    {     7168,       7,           9},  // 0.17%
    {     8192,       4,           8},  // 0.29%
};
#else
#error "Unsupported TCMALLOC_PAGE_SHIFT value!"
#endif
#endif
// clang-format on

}  // namespace tcmalloc
