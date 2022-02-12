// Copyright (c) 2022, Rudi Bikschentajew
// All rights reserved.
//
// This source code is licensed under the BSD-style license found in the
// LICENSE file in the root directory of this source tree.

#include <ContentProcessors/IContentProcessor.hpp>

// filters
#include <PathFilter/ContentRegexFilter.hpp>

// processors
#include <ContentProcessors/ParallelContentProcessor/ParallelContentProcessor.hpp>
#include <ContentProcessors/SequentialContentProcessor.hpp>

namespace lg {

template<typename OutputIterator>
std::unique_ptr<IContentProcessor>
IContentProcessor::create(OutputIterator oiter,
                          std::shared_ptr<const Configuration> opt)
{
    // Create the content filter
    // if regex filter
    auto contentFilter =
      std::make_shared<ContentRegexFilter>(opt->mRegexContent);
    if (!contentFilter) {
        // TODO: Throw exception
    }

    // Create the processor (single- or multi-threaded)
    if (opt->mParallelContentFiltering) {
        return std::make_unique<ParallelContentProcessor<OutputIterator>>(
          oiter, contentFilter);
    } else {
        return std::make_unique<SequentialContentProcessor<OutputIterator>>(
          oiter, contentFilter);
    }
}

} // namespace lg
