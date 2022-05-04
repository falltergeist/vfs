#pragma once

#include <string>
#include <memory>
#include "IFile.h"

namespace Falltergeist::VFS {
    class IDriver {
    public:
        virtual ~IDriver() = default;

        virtual const std::string& name() = 0;

        virtual bool exists(const std::string& path) = 0;

        virtual std::shared_ptr<IFile> open(const std::string& path, IFile::OpenMode mode) = 0;
    };
}
