/**
 *  @file     src/engine/LibraryLoader.hpp
 *  @author   ltabis
 *  @date     2020-03-31
 * 
 *  project: EclataxEngine
 * 
 */

#pragma once

#include <string>
#include <algorithm>
#include <filesystem>
#include <unordered_map>

/// \def LIB_ENTRYPOINT
/// \brief name of the entrypoint function in all lib
constexpr auto const LIB_ENTRYPOINT = "entryPoint";

/// \def LIB_EXTENSION
/// \brief extention of shared library to load
#ifdef WIN32
    #include <windows.h>

    constexpr auto const LIB_EXTENSION = ".dll";
#else
    #include <sys/types.h>
    #include <dirent.h>
    #include <dlfcn.h>

    constexpr auto const LIB_EXTENSION = ".so";
#endif

/// \namespace Module
/// Module namespace for EclataxEngine project
namespace Module {

    /// \class LibraryLoader
    /// \brief templated class used to load shared library
    class LibraryLoader
    {
    public:
        /// \brief Constructor
        LibraryLoader() = default;

        /// \brief Destructor
        ~LibraryLoader();

        /// \brief get an instance of a shared library by calling entryPoint function.
        /// \param file : path to the shared library.
        /// \return an instance of the disered object.
        template<typename T> T *getInstance(const std::string &file);

        /// \brief open and return all instance of library in a specific directory.
        /// \param directory : path to the directory to search shared libraries.
        /// \return a vector of the needed instance.
        template<typename T> std::vector<T *> getDirectory(const std::string &directory);

        /// \brief clear all saved pointers librairies
        void clear();

    private:
        std::unordered_map<std::string, void *> _loadedLib;

        #ifndef WIN32
            void* loadLibrarie(const std::string &directory);
        #endif
    };

    template<typename T>
    std::vector<T *> LibraryLoader::getDirectory(const std::string &directory)
    {
        std::vector<T *> libraries;

        // Check wether the directory exists or not.
        if (!std::filesystem::exists(directory) || !std::filesystem::is_directory(directory))
        {
            return libraries;
        }

        // Reading the directory.
        for (const auto &file : std::filesystem::directory_iterator(directory))
        {
            // Getting the name of the file and position of the extension.
            std::string filepath = file.path().string();
            auto posExtension = filepath.find_last_of(".", std::string::npos);

            // Check wether the file is a dynamic library or not.
            if (file.is_regular_file() && posExtension != std::string::npos && filepath.substr(posExtension) == LIB_EXTENSION)
            {
                auto newElement = getInstance<T>(filepath);

                // Adding the library to the vector.
                if (newElement)
                    libraries.push_back(newElement);
            }
        }
        return libraries;
    }


#ifdef WIN32

    template<typename T>
    T *LibraryLoader::getInstance(const std::string &filepath)
    {
        T *(*fct)(void) = nullptr;

        // Load the library.
        auto libPtr = _loadedLib.find(filepath);

        // Check if the libraire instance was already loaded.
        if (libPtr != _loadedLib.end())
        {
            // Getting the entry point. (casts are for windows -> can't make a static cast on the GetProcAddress function)
            fct = reinterpret_cast<T *(*)(void)>(GetProcAddress(static_cast<HMODULE>(libPtr->second), LIB_ENTRYPOINT));

            if (fct)
                return (fct());
        }
        else
        {
            // Getting the library.
            std::cout << filepath.c_str() << std::endl;
            HINSTANCE newLibrary = LoadLibrary(filepath.c_str());

            if (newLibrary)
            {
                // Storing the handler.
                _loadedLib.emplace(filepath, newLibrary);

                // Getting the entry point. (casts are for windows)
                fct = reinterpret_cast<T *(*)(void)>(GetProcAddress(static_cast<HMODULE>(newLibrary), LIB_ENTRYPOINT));
                if (fct)
                    return (fct());
            }
        }
        return (nullptr);
    }

#else

    template<typename T>
    T *LibraryLoader::getInstance(const std::string &file)
    {
        T *(*fct)(void) = nullptr;

        // If the libraire instance was already loaded
        auto lib_ptr = _loadedLib.find(file);
        if (lib_ptr != _loadedLib.end()) {
            fct = reinterpret_cast<T *(*)()>(dlsym((*lib_ptr).second, LIB_ENTRYPOINT));
            if (fct != nullptr)
                return (fct());
        // Load the librairie if it is not
        } else {
            void *ptr = loadLibrarie(file);
    
            if (ptr != nullptr) {
                _loadedLib.emplace(file, ptr);
                fct = reinterpret_cast<T *(*)()>(dlsym(ptr, LIB_ENTRYPOINT));
                if (fct != nullptr)
                    return (fct());
            }
        }
        return (nullptr);
    }

#endif

}