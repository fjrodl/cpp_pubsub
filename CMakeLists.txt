cmake_minimum_required(VERSION 3.8)
project(cpp_pubsub)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  # set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  # set(ament_cmake_cpplint_FOUND TRUE)
  # ament_copyright does not detect copyright headers in .md files,
  # so exclude CONTRIBUTING.md from the copyright check.
  set(AMENT_LINT_AUTO_FILE_EXCLUDE "*/CONTRIBUTING.md")
  ament_lint_auto_find_test_dependencies()
endif()


add_executable(publisher_node src/publisher_node.cpp)
ament_target_dependencies(publisher_node rclcpp std_msgs)

add_executable(subscriber_node src/subscriber_node.cpp)
ament_target_dependencies(subscriber_node rclcpp std_msgs)

add_executable(primos_publisher_node src/primos_publisher_node.cpp)
ament_target_dependencies(primos_publisher_node rclcpp std_msgs)

install(TARGETS
  publisher_node
  subscriber_node
  primos_publisher_node
  DESTINATION lib/${PROJECT_NAME})

ament_package()
