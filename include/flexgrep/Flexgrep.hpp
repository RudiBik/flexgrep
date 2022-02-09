#pragma once

#include <ContentProcessors/IContentProcessor.hpp>
#include <PathFilter/IContentFilter.hpp>
#include <PathFilter/IMetaFilter.hpp>
#include <Utilities/Configuration.hpp>

#include <memory>
#include <optional>

namespace lg {

//!================================================
//! \brief Main thread traversing the directory tree recursively,
//!        filtering files via meta data like filename/size/binary/...
//!        and forwarding matching files to the content filter
//!------------------------------------------------
class Flexgrep
{
  public:
    //!================================================
    //! \brief Initializing the meta and content filters using
    //!        the provided configuration
    //!
    //! Only the constructor is templated to be able to forward the
    //! output iterator directly to the content filter on construction
    //!------------------------------------------------
    template<typename OutputIterator>
    Flexgrep(std::shared_ptr<const Configuration> config, OutputIterator oiter);

    Flexgrep(const Flexgrep& rhs) = delete;
    Flexgrep& operator=(const Flexgrep& rhs) = delete;

    void searchAndOutput();

  private:
    bool passesMetaFilters(const File::Meta& metaData) const;

    void processDirectory(const std::filesystem::path& p);
    void processSymlink(const std::filesystem::path& p);
    void processRegular(const std::filesystem::path& p);

    static std::vector<IMetaFilterUPtr> createMetaFilters(
      const Configuration* config);

  private:
    std::shared_ptr<const Configuration> mConfiguration;

    std::vector<IMetaFilterUPtr> mMetaFilters;
    std::unique_ptr<IContentProcessor> mContentFilter;

    // used to prevent following recursive symlinks
    std::optional<std::filesystem::path> mCurrentSymlink;
};

template<typename OutputIterator>
Flexgrep::Flexgrep(std::shared_ptr<const Configuration> config,
                   OutputIterator oiter)
  : mConfiguration{ config }
  , mCurrentSymlink{}
{
    mMetaFilters = Flexgrep::createMetaFilters(config.get());

    mContentFilter = IContentProcessor::create(oiter, mConfiguration);
    if (!mContentFilter) {
        // TODO: Throw exception
    }
}

} // namespace lg
