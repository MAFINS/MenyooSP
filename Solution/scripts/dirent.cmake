include(FetchContent)

set(DIRENT_BUILD_TESTS OFF CACHE INTERNAL "")

FetchContent_Declare(
    dirent
    GIT_REPOSITORY https://github.com/tronkko/dirent.git
    GIT_TAG        328e7fca1497f1d990d8b55b3cec39c869e3a6a8
    GIT_PROGRESS TRUE
) 
message("dirent")
FetchContent_MakeAvailable(dirent)
