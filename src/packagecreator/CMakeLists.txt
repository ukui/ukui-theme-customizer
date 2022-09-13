add_library(packagecreator STATIC
    packagecreator.cpp
    packagecreator.ui
)
target_link_libraries(packagecreator
    Qt5::Widgets
    Qt5::Core
)
