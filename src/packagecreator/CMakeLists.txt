add_library(packagecreator STATIC
    packagecreator.cpp
    packagecreator.ui
)
target_link_libraries(packagecreator PRIVATE Qt5::Widgets)
