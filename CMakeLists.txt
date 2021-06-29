cmake_minimum_required(VERSION 3.19)
project(QTodo)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 COMPONENTS Widgets)
if( NOT Qt6_FOUND )
    set(QT_VERSION 5)
else()
    set(QT_VERSION 6)
endif()

set(REQUIRED_LIBS Core Gui Widgets Network)
set(REQUIRED_LIBS_QUALIFIED Qt${QT_VERSION}::Core Qt${QT_VERSION}::Gui Qt${QT_VERSION}::Widgets Qt${QT_VERSION}::Network)

add_executable(${PROJECT_NAME} src/main.cpp src/appwindow.cpp include/appwindow.hpp resources.qrc dark/style.qrc src/homewidget.cpp include/homewidget.hpp include/HomeWidget.ui src/signupwidget.cpp include/signupwidget.hpp include/SignupWidget.ui include/user.hpp src/signinwidget.cpp include/signinwidget.hpp include/SigninWidget.ui include/task.hpp include/serializable.hpp include/step.hpp src/taskformwidget.cpp include/taskformwidget.hpp include/TaskFormWidget.ui src/stepformwidget.cpp include/stepformwidget.hpp include/StepFormWidget.ui include/abstractform.hpp src/httprequesthandler.cpp include/httprequesthandler.hpp src/taskwidget.cpp include/taskwidget.hpp include/TaskWidget.ui src/tasklist.cpp include/tasklist.hpp include/TaskList.ui)

if (NOT CMAKE_PREFIX_PATH)
    message(WARNING "CMAKE_PREFIX_PATH is not defined, you may need to set it "
            "(-DCMAKE_PREFIX_PATH=\"path/to/Qt/lib/cmake\" or -DCMAKE_PREFIX_PATH=/usr/include/{host}/qt{version}/ on Ubuntu)")
endif ()

if ( CMAKE_COMPILER_IS_GNUCC )
    set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -Wunused")
endif()
if ( MSVC )
    set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} /W4")
endif()
include_directories(${QTodo_SOURCE_DIR}/include)
find_package(Qt${QT_VERSION} COMPONENTS ${REQUIRED_LIBS} REQUIRED)
target_link_libraries(${PROJECT_NAME} ${REQUIRED_LIBS_QUALIFIED})
