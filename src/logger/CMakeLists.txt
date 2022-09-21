add_library(logger STATIC
    logger.cpp
)

target_link_libraries(logger
    Qt5::Widgets
    Qt5::Core
)
