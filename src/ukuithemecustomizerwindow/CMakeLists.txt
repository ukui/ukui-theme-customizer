add_library(ukuithemecustomizerwindow STATIC
    ukuithemecustomizerwindow.cpp
    ukuithemecustomizerwindow.ui
)
target_link_libraries(ukuithemecustomizerwindow PRIVATE Qt5::Widgets)
