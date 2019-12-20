set_property(GLOBAL PROPERTY USE_FOLDERS ON)

add_subdirectory(Graphics)
add_subdirectory(SDLSupport)
add_subdirectory(AppEvents)
add_subdirectory(GameGraphics)
add_subdirectory(SpaceInvadersEngine)
add_subdirectory(Math)
add_subdirectory(AppUtils)
add_subdirectory(CppUtils/code)



set_target_properties (SDLSupport PROPERTIES FOLDER libs)
set_target_properties (cpp-utils-h PROPERTIES FOLDER libs)
set_target_properties (Graphics PROPERTIES FOLDER libs)
set_target_properties (GameGraphics PROPERTIES FOLDER libs)
set_target_properties (AppUtils PROPERTIES FOLDER libs)
set_target_properties (AppEvents-h PROPERTIES FOLDER libs)
set_target_properties (Math PROPERTIES FOLDER libs)
set_target_properties (SpaceInvadersEngine PROPERTIES FOLDER libs)


