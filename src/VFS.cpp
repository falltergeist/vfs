#include "VFS.h"

namespace Falltergeist::VFS {

    VFS::VFS() {
    }

    void VFS::addMount(const std::string& path, std::unique_ptr<IDriver>&& driver) {
        _mounts.insert(std::make_pair(path, std::move(driver)));
    }

    void VFS::addMount(const std::string& path, std::unique_ptr<IDriver>& driver) {
        addMount(path, std::move(driver));
    }

    bool VFS::exists(const std::string& pathToFile) {
        for (auto it = _mounts.begin(); it != _mounts.end(); ++it) {
            if (it->first.size() && pathToFile.find(it->first) == std::string::npos) {
                continue;
            }

            if (it->second->exists(it->first.size() ? pathToFile.substr(it->first.length()) : pathToFile)) {
                return true;
            }
        }

        return false;
    }

    std::shared_ptr<IFile> VFS::open(const std::string& path, IFile::OpenMode mode) {
        if (_openedFiles.count(path) != 0) {
            return _openedFiles.at(path);
        }

        for (auto it = _mounts.begin(); it != _mounts.end(); ++it) {
            if (it->first.size() && path.find(it->first) == std::string::npos) {
                continue;
            }

            if (mode == IFile::OpenMode::Read || mode == IFile::OpenMode::ReadWrite) {
                // File should exist in these modes
                if (!it->second->exists(it->first.size() ? path.substr(it->first.length() + 1) : path)) {
                    continue;
                }
            }

            auto file = it->second->open(it->first.size() ? path.substr(it->first.length() + 1) : path, mode);
            if (file) {
                _openedFiles.emplace(std::make_pair(path, file));
                return file;
            }
        }

        return nullptr;
    }

    void VFS::close(std::shared_ptr<IFile>& file) {
        file->_close();

        for (auto it = _openedFiles.begin(); it != _openedFiles.end(); ++it) {
            if (it->second == file) {
                _openedFiles.erase(it->first);
                break;
            }
        }
    }
}
