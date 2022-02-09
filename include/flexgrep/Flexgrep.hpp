#pragma once

#include <ContentProcessors/IContentProcessor.hpp>
#include <PathFilter/IContentFilter.hpp>
#include <PathFilter/IMetaFilter.hpp>
#include <Utilities/Options.hpp>

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
    Flexgrep(std::shared_ptr<const Options> options, OutputIterator oiter);

    Flexgrep(const Flexgrep& rhs) = delete;
    Flexgrep& operator=(const Flexgrep& rhs) = delete;

    void searchAndOutput();

  private:
    bool passesMetaFilters(const File::Meta& metaData) const;

    void processDirectory(const std::filesystem::path& p);
    void processSymlink(const std::filesystem::path& p);
    void processRegular(const std::filesystem::path& p);

    static std::vector<IMetaFilterUPtr> createMetaFilters(
      const Options* options);

  private:
    std::shared_ptr<const Options> mOptions;

    std::vector<IMetaFilterUPtr> mMetaFilters;
    std::unique_ptr<IContentProcessor> mContentFilter;

    // used to prevent following recursive symlinks
    std::optional<std::filesystem::path> mCurrentSymlink;
};

template<typename OutputIterator>
Flexgrep::Flexgrep(std::shared_ptr<const Options> options, OutputIterator oiter)
  : mOptions{ options }
  , mCurrentSymlink{}
{
    mMetaFilters = Flexgrep::createMetaFilters(options.get());

    mContentFilter = IContentProcessor::create(oiter, mOptions);
    if (!mContentFilter) {
        // TODO: Throw exception
    }
}

} // namespace lg
