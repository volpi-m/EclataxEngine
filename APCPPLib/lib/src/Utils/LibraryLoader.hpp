//
// Created by tabis on 10/01/2020.
//

#pragma once

#include <algorithm>
#include <iostream>
#include <dirent.h>
#include <dlfcn.h>
#include <cstring>
#include <vector>
#include <string>

namespace Utils
{

    /// \class LibraryLoader
    /// \brief an object that loads dynamic libraries.
    class LibraryLoader
    {
    public:

        /// \brief opens a library via a filepath.
        /// \param lib : path of the library to open.
        /// \return a pointer to the new allocated object.
        template<typename T>
        T *openLibrary(const std::string &lib)
        {
            T *obj = nullptr;
            std::string cat = "./" + lib;
            void *handle = dlopen(cat.c_str(), RTLD_LAZY);
            char *error = nullptr;

            // Failed to open the dynamic library.
            if (!handle)
            {
                std::cout << dlerror() << std::endl;
                return nullptr;
            }

            // Getting the entry point.
            auto func = (T *(*)())dlsym(handle, "entryPoint");

            // Found error.
            if ((error = dlerror()))
            {
                std::cout << "error : " << error << std::endl;
                return nullptr;
            }

            // Creating the desired object via the entry point.
            obj = func();

            // Saving the handle.
            _handles.push_back(handle);
            
            return obj;
        }

        /// \brief opens all libraries from a directory.
        /// \param directory : directory path to open.
        /// \return a vector of pointers to the new allocated object.
        template<typename T>
        std::vector<T *> openDirectory(const std::string &directory)
        {
            std::vector<T *> objects;
            DIR *dir = opendir(directory.c_str());

            // Failed to open directory.
            if (!dir)
                return objects;

            struct dirent *stream = nullptr;

            // Reading files
            stream = readdir(dir);
            for (std::string str; stream; stream = readdir(dir))
            {
                str = stream->d_name;

                // Checking if the name of the file is correct.
                if (stream->d_type == DT_REG && str.find_last_of(".so", std::string::npos) != std::string::npos)
                {
                    auto newElement = openLibrary<T>(directory + "/" + str);

                    // If the element as been loaded correctly, adding it to the new vector of objects.
                    if (newElement)
                        objects.push_back(newElement);
                }
            }

            // Closing stream.
            closedir(dir);
            return objects;
        }

    private:
        // bool checkIfLibraryInMemory();

        /// \brief deletes all handles
        void deleteHandles();

        /*! Vector of all the handles of currently loaded libraries */
        std::vector<void *> _handles;
    };
}