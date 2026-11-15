# Environment for the ROS2 Jazzy desktop shortcut.
if [ -f ~/.bashrc ]; then source ~/.bashrc; fi
if [ -f /opt/ros/jazzy/setup.bash ]; then
    source /opt/ros/jazzy/setup.bash
else
    printf 'ROS2 Jazzy setup is missing: /opt/ros/jazzy/setup.bash\n' >&2
fi
if [ -f /home/robot/ros2_ws/install/setup.bash ]; then
    source /home/robot/ros2_ws/install/setup.bash
fi
cd /home/robot/ros2_ws || return
printf '\nROS2 %s | Workspace: %s\n\n' "${ROS_DISTRO:-not loaded}" "$PWD"
