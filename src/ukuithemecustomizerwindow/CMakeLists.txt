add_library(ukuithemecustomizerwindow STATIC
    ukuithemecustomizerwindow.cpp
    ukuithemecustomizerwindow.ui
)
target_link_libraries(ukuithemecustomizerwindow
    Qt5::Widgets
    Qt5::Core
    packagecreator
)
