//
// Created by Arseny Tolmachev on 2017/03/02.
//

#include "core.h"

namespace jumanpp {
namespace core {

CoreHolder::CoreHolder(const RuntimeInfo &runtime,
                       const dic::DictionaryHolder &dic)
    : runtime_{runtime}, dic_{dic} {
  latticeCfg_.entrySize = dic.entries().entrySize();
  latticeCfg_.numPrimitiveFeatures =
      runtime.features.primitive.size() + runtime.features.compute.size();
  latticeCfg_.numFeaturePatterns = runtime.features.patterns.size();
  latticeCfg_.numFinalFeatures = runtime.features.ngrams.size();
}

Status CoreHolder::initialize(const features::StaticFeatureFactory *sff) {
  JPP_RETURN_IF_ERROR(
      analysis::makeMakers(*this, runtime_.unkMakers, &unkMakers_));
  JPP_RETURN_IF_ERROR(features::makeFeatures(*this, sff, &features_));
  return Status::Ok();
}

}  // namespace core
}  // namespace jumanpp
