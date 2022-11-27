include(FetchContent)

FetchContent_Declare(
    simpleini
    GIT_REPOSITORY https://github.com/brofield/simpleini.git
    GIT_TAG        142beb4ecef7b50887ae99e7dfcbc09f779372cd
    GIT_PROGRESS TRUE
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
)
message("simpleini")
if(NOT simpleini_POPULATED)
    FetchContent_Populate(simpleini)

    file(GLOB_RECURSE SRC_SIMPLEINI 
        "${simpleini_SOURCE_DIR}/*.h"
    )
endif()
