
##############################################
#Input

target_sources(${PROJECT_NAME}
    PRIVATE
        Button.h
        Button.cpp
        InputModule.h
        InputModule.cpp
        InputSet.h
        Modules/GLFW/GLFWInputBackend.cpp
        Modules/GLFW/GLFWInputBackend.h
        Modules/Mock/MockInputBackend.cpp
        Modules/Mock/MockInputBackend.h
)
