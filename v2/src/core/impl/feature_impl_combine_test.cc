//
// Created by Arseny Tolmachev on 2017/03/03.
//

#include "feature_impl_combine.h"
#include "testing/standalone_test.h"

using namespace jumanpp::core::features::impl;
using namespace jumanpp;

TEST_CASE("pattern feature compiles") {
  static constexpr i32 refs[] = {0, 2, 3};
  constexpr DynamicPatternFeatureImpl pat{0, refs};
  u64 data[] = {0, 0, 0};
  util::MutableArraySlice<u64> wrap{data};
  util::ArraySlice<u64> input{1, 2, 3, 4};
  pat.apply(input, &wrap);
  CHECK(data[0] == 0x9d8a01713676eec6ULL);
  CHECK(data[1] == 0);
  CHECK(data[2] == 0);
}

// TODO: fixme
TEST_CASE("ngram features can be compiled", "[.]") {
  constexpr NgramFeatureImpl<1> uni{0, 1};
  constexpr NgramFeatureImpl<2> bi{1, 1, 2};
  constexpr NgramFeatureImpl<3> tri{2, 1, 2, 0};
  u32 data[] = {0, 0, 0};
  util::MutableArraySlice<u32> res{data};
  util::ArraySlice<u64> t2{1, 1, 1};
  util::ArraySlice<u64> t1{1, 1, 1};
  util::ArraySlice<u64> t0{1, 1, 1};
  uni.apply(&res, t2, t1, t0);
  bi.apply(&res, t2, t1, t0);
  tri.apply(&res, t2, t1, t0);
  CHECK(data[0] == 0x45514d5e);
  CHECK(data[1] == 0x1e35b1b0);
  CHECK(data[2] == 0xf3eb0535);
}