add_library(globalthemecreator STATIC
    globalthemecreator.cpp
    globalthemecreator.ui
)
target_link_libraries(globalthemecreator
    Qt5::Widgets
    Qt5::Core
)
