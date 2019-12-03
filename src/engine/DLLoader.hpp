//
// EPITECH PROJECT, 2020
// R-type
// File description:
// class for lib loader
//

#ifndef DLLOADER_HPP_
#define DLLOADER_HPP_

#include <string>
#include <algorithm>
#include <vector>
#include <dlfcn.h>
#include <sys/types.h>
#include <dirent.h>

/// \def LIB_EXTENSION
/// \brief extention of shared library to load
constexpr auto const LIB_EXTENSION = ".so";

namespace ECS
{
    /// \class DLLoader
    /// \brief templated class used to load shared library
    class DLLoader
    {
    public:
        /// \brief Constructor
        DLLoader() = default;

        /// \brief Destructor
        ~DLLoader();

        /// \brief get an instance of a shared library by calling entryPoint function
        /// \param file : path to the shared library
        /// \return an instance of the specific object
        template<typename T> T *getInstance(const std::string &file);

        /// \brief open and return all instance of library in a specific directory
        /// \param directory : path to the directory to search shared libraries
        /// \return a vector of instance
        template<typename T> std::vector<T *> openDirectory(const std::string &directory);

    private:
        std::vector<void *> _ptr;

        void disp_error() const;
    };

    template<typename T>
    T *DLLoader::getInstance(const std::string &file)
    {
        void *lib_ptr;
        T *(*fct)(void);

        lib_ptr = dlopen(file.c_str(), RTLD_LAZY);
        if (lib_ptr == nullptr) {
            this->disp_error();
        } else {
            _ptr.push_back(lib_ptr);
            fct = (T *(*)())dlsym(lib_ptr, "entryPoint");
            if (fct != nullptr)
                return (fct());
            else
                this->disp_error();
            return (nullptr);
        }
        return (nullptr);
    }

    template<typename T>
    std::vector<T *> DLLoader::openDirectory(const std::string &directory)
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

#endif