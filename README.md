# ros2_ws

ROS 2 Jazzy C++ 机器人控制与导航练习工作区（colcon workspace）。

## 运行环境

| 项目 | 版本 / 说明 |
| --- | --- |
| 操作系统 | Ubuntu 24.04 LTS |
| ROS 版本 | ROS 2 Jazzy |
| 语言标准 | C++17（CMake 3.8+，构建类型 `ament_cmake`） |
| 主要依赖 | `rclcpp`、`std_msgs` |

## 功能包 `jazzy_cpp_smoke`

源码位于 `src/jazzy_cpp_smoke`，共构建三个可执行节点：

| 节点 | 源文件 | 作用 |
| --- | --- | --- |
| `hello_node` | `src/hello_node.cpp` | 最小可运行节点：初始化 rclcpp、打印日志「我的第一个ROS2 Node」后进入 spin，用于验证环境与编译链路。 |
| `robot_publisher` | `src/robot_publisher.cpp` | 发布者节点：在 `robot_status` 话题上发布一条 `std_msgs/msg/String`（内容「机器人准备完毕」），随后退出，可配合 `ros2 topic echo` 观察。 |
| `robot_node` | `src/robot_node.cpp` | 控制节点：订阅 `robot_status`，按收到的状态消息（前方有人 / 距离较近 / 其他）把速度切换为 0 / 1 / 2，并通过 `robot_reply` 话题回发处理结果。节点内以 `Robot` 类保存 `speed` 状态（注册名 `jiedian`）。 |

话题接口：

- `robot_status`：`std_msgs/msg/String`，`robot_publisher` 发布 → `robot_node` 订阅
- `robot_reply`：`std_msgs/msg/String`，`robot_node` 发布

## 一键运行

```bash
./run.sh
```

等价于：

```bash
colcon build --packages-select jazzy_cpp_smoke
source install/setup.bash
ros2 run jazzy_cpp_smoke robot_node
```

单独运行其他节点：

```bash
source install/setup.bash
ros2 run jazzy_cpp_smoke hello_node
ros2 run jazzy_cpp_smoke robot_publisher
```

## 目录结构

```
ros2_ws/
├── run.sh                      # 一键编译并启动 robot_node
├── .jazzy-desktop.bashrc       # 桌面快捷方式使用的环境脚本（source ROS 2 Jazzy + 工作区）
├── src/
│   └── jazzy_cpp_smoke/
│       ├── CMakeLists.txt      # 三个可执行目标，C++17
│       ├── package.xml         # ament_cmake 包描述
│       ├── include/jazzy_cpp_smoke/
│       └── src/
│           ├── hello_node.cpp
│           ├── robot_publisher.cpp
│           └── robot_node.cpp
├── build/                      # colcon 编译产物（不纳入版本管理）
├── install/                    # colcon 安装空间（不纳入版本管理）
└── log/                        # colcon 构建日志（不纳入版本管理）
```

`build/`、`install/`、`log/`、`.vscode/`、`*.o`、`*.exe`、`*.swp` 等编译产物与临时文件已在 `.gitignore` 中排除。

## 备注

本仓库在 Windows 侧完成 Git 初始化，实际编译与运行需在 Ubuntu 24.04 + ROS 2 Jazzy 环境中进行（`run.sh` 为 Bash 脚本）。
