#!/bin/bash

colcon build --packages-select jazzy_cpp_smoke
source install/setup.bash
ros2 run jazzy_cpp_smoke robot_node
