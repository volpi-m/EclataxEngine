//
// EPITECH PROJECT, 2020
// R-type
// File description:
// class for lib loader
//

#ifndef WinDLLOADER_HPP_
#define WinDLLOADER_HPP_

#include <string>
#include <algorithm>
#include <vector>
#include <dlfcn.h>
#include <sys/types.h>
#include <dirent.h>
#include <windows.h>
#include <Winerror.h>

#define LIB_EXTENSION ".dll"

namespace ECS {

    class WinDLLoader {
    public:
        WinDLLoader();
        ~WinDLLoader();

        template<typename T>
        T *getInstance(const std::string &file);
        template<typename T>
        std::vector<T *> openDirectory(const std::string &directory);

    private:
        std::vector<void *> _ptr;

        void disp_error() const;
    };

    template<typename T>
    T *WinDLLoader::getInstance(const std::string &file)
    {
        void *lib_ptr;
        T *(*fct)(void);

        lib_ptr = LoadLibrary(file.c_str());
        if (lib_ptr == nullptr)
            this->disp_error();
        else {
            _ptr.push_back(lib_ptr);
            fct = (T *(*)())GetProcAddress(lib_ptr, "entryPoint");
            if (fct != nullptr)
                return (fct());
            else
                this->disp_error();
            return (nullptr);
        }
        return (nullptr);
    }

    template<typename T>
    std::vector<T *> WinDLLoader::openDirectory(const std::string &directory)
    {
        DIR *dir = opendir(directory.c_str());
        struct dirent *stream = nullptr;
        std::vector<T *> v;

        if (!dir)
            return v;
        stream = readdir(dir);
        for (std::string str; stream; stream = readdir(dir)) {
            str = stream->d_name;
            if (str.length() >= 3 && stream->d_type == DT_REG && str.find_last_of(LIB_EXTENSION, std::string::npos) != std::string::npos) {
                auto newElement = getInstance<T>(directory + "/" + str);
                if (newElement)
                    v.push_back(newElement);
            }
        }
        closedir(dir);
        return v;
    }

}