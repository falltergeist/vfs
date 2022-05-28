#pragma once

#include "IDriver.h"
#include "IFile.h"
#include <map>
#include <memory>
#include <string>

namespace Falltergeist::VFS {
    class VFS final {
    public:
        VFS() = default;

        VFS(const VFS& other) = delete;

        VFS(VFS&& other) = delete;

        VFS& operator=(VFS other) = delete;

        void addMount(const std::string& mountPath, std::unique_ptr<IDriver>&& driver);

        void addMount(const std::string& mountPath, std::unique_ptr<IDriver>& driver);

        bool exists(const std::string& pathToFile);

        std::shared_ptr<IFile> open(const std::string& path, IFile::OpenMode mode = IFile::OpenMode::Read);

        void close(std::shared_ptr<IFile>& file);

    private:
        std::multimap<std::string, std::unique_ptr<IDriver>> _mounts;

        std::map<std::string, std::shared_ptr<IFile>> _openedFiles;
    };
}
