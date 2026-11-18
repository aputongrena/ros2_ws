cmake_minimum_required(VERSION 3.8)
project(jazzy_cpp_smoke)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies  —— 所有依赖统一在这里 find，且必须在 ament_target_dependencies 之前
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)   # ← 移到这里

add_executable(hello_node src/hello_node.cpp)
add_executable(robot_publisher src/robot_publisher.cpp)
add_executable(robot_node src/robot_node.cpp)

target_include_directories(hello_node PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include/${PROJECT_NAME}>)
target_compile_features(hello_node PUBLIC c_std_99 cxx_std_17)

ament_target_dependencies(
  hello_node
  "rclcpp"
)

ament_target_dependencies(
  robot_publisher
  "rclcpp"
  "std_msgs"
  "geometry_msgs"
)

# robot_node 也需要声明依赖；如果它实际用不到 geometry_msgs，可以删掉对应项
ament_target_dependencies(
  robot_node
  "rclcpp"
  "std_msgs"
  "geometry_msgs"
)

install(TARGETS
  hello_node
  robot_publisher
  robot_node
  DESTINATION lib/${PROJECT_NAME}
)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # 这里不要再 find_package(geometry_msgs)，已经在顶部找过了
  set(ament_cmake_copyright_FOUND TRUE)
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()