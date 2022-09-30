add_library(settingmanager STATIC
    settingmanager.cpp
)

target_link_libraries(settingmanager
    Qt5::Widgets
    Qt5::Core
)
