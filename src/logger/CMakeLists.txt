add_library(logger STATIC
    logger.h
)

target_link_libraries(logger
    Qt5::Widgets
    Qt5::Core
)
