# Unitree Go2 Navigation and SLAM

ROS 2 workspace for **Unitree Go2** autonomous navigation. The core package is **`go2_goal_nav`**, which lets you click a goal pose in RViz2 and drives the robot there using odometry feedback and the Unitree Sport API.

## Features

- **RViz2 goal navigation** (`go2_goal_nav`): subscribe to `/goal_pose`, navigate with a simple go-to-goal controller
- **Odometry & TF** (`go2_drive_py`): publish `/odom` and TF from `SportModeState`
- **Twist bridge** (`go2_twist_bridge`): convert `cmd_vel` to Unitree Sport API requests
- **Action-based navigation** (`go2_nav` + `go2_inter`): ROS 2 Action interface for programmatic navigation
- **Robot description** (`go2_description`): URDF model and RViz visualization
- **Cruising / state / control** (`go2_cruising`, `go2_state`, `go2_ctrl`): additional motion and state utilities

## Architecture

```
RViz2 (/goal_pose)
       │
       ▼
┌──────────────────┐     /odom        ┌─────────────────┐
│  go2_goal_nav    │◄───────────────  │  go2_drive_py   │◄── SportModeState
│ goal_subscriber  │                  │     driver      │
└────────┬─────────┘                  └─────────────────┘
         │ /api/sport/request
         ▼
┌──────────────────┐
│ go2_twist_bridge │◄── cmd_vel (optional)
└──────────────────┘
         │
         ▼
   Unitree Go2 (Sport API)
```

## Prerequisites

| Component | Version / Notes |
|-----------|-----------------|
| OS | Ubuntu 22.04 (recommended) |
| ROS 2 | Humble |
| Python | 3.10+ |
| Unitree SDK | `unitree_go`, `unitree_api` message packages |

### Install ROS 2 Humble

```bash
sudo apt update
sudo apt install ros-humble-desktop python3-colcon-common-extensions
```

### Install Python dependencies

```bash
sudo apt install python3-tf-transformations ros-humble-tf-transformations
```

### Unitree ROS 2 packages

Clone and build the official Unitree ROS 2 interface packages (provides `unitree_go` and `unitree_api`):

```bash
# Example — adjust path to your workspace
cd ~/ros2_ws/src
git clone https://github.com/unitreerobotics/unitree_ros2.git
cd ~/ros2_ws
colcon build --symlink-install
source install/setup.bash
```

> Make sure the Go2 is on the same network and ROS 2 DDS is configured to reach the robot.

## Build

```bash
cd Unitree_GO2_ws
source /opt/ros/humble/setup.bash

# Build all packages
colcon build --symlink-install

# Or build only what you need for goal navigation
colcon build --symlink-install --packages-select \
  go2_description go2_inter go2_drive_py go2_twist_bridge go2_goal_nav

source install/setup.bash
```

## Run — Goal Navigation (Core)

This is the main workflow using **`go2_goal_nav`**.

### 1. Start the navigation stack

```bash
source install/setup.bash
ros2 launch go2_goal_nav go2_goal_nav.launch.py
```

This launch file starts:
- `go2_drive_py` — odometry, TF, RViz2
- `go2_twist_bridge` — Sport API bridge
- `go2_goal_nav` — goal pose navigator (`goal_subscriber`)

### 2. Send a goal in RViz2

1. In RViz2, set **Fixed Frame** to `odom`
2. Click **2D Goal Pose** in the toolbar
3. Click and drag on the map to set position and heading
4. The robot will rotate toward the goal, drive forward, and stop when within ~15 cm

### 3. Monitor topics (optional)

```bash
# Odometry
ros2 topic echo /odom

# Goal pose
ros2 topic echo /goal_pose

# Sport API commands
ros2 topic echo /api/sport/request
```

## Run — Action-based Navigation

For programmatic navigation via ROS 2 Action:

```bash
# Terminal 1 — navigation server
source install/setup.bash
ros2 launch go2_nav go2_nav.launch.py

# Terminal 2 — send a goal
ros2 run go2_nav go2_nav_client
```

## Package Overview

| Package | Description |
|---------|-------------|
| **`go2_goal_nav`** | **Core** — RViz2 `/goal_pose` navigation |
| `go2_drive_py` | Odometry publisher, joint states, RViz launch |
| `go2_twist_bridge` | `cmd_vel` → Unitree Sport API |
| `go2_description` | Go2 URDF and visualization |
| `go2_inter` | Custom Action (`Nav`) and Service (`Cruising`) interfaces |
| `go2_nav` | Action server/client navigation |
| `go2_cruising` | Cruising mode service |
| `go2_state` | Robot state monitoring |
| `go2_ctrl` | Low-level control utilities |

## Configuration

### Drive parameters

`src/go2_drive_py/params/drive.yaml`:

```yaml
/**:
  ros__parameters:
    base_frame: base
    odom_frame: odom
    publish_tf: true
```

### Navigation tuning

Key values in `src/go2_goal_nav/go2_goal_nav/goal_subscriber.py`:

| Parameter | Default | Description |
|-----------|---------|-------------|
| Arrival distance | 0.15 m | Stop when within this radius |
| Heading threshold | 12° | Rotate in place above this error |
| Max linear speed | 0.50 m/s | Forward speed cap |
| Goal timeout | 120 s | Abandon goal after timeout |

## Network Setup (Robot Connection)

The Go2 must be reachable on the network. Typical setup:

1. Connect your PC and the Go2 to the same subnet (e.g. `192.168.123.x`)
2. Set `ROS_DOMAIN_ID` if needed: `export ROS_DOMAIN_ID=0`
3. Verify connectivity: `ros2 topic list` should show robot topics like `/lf/sportmodestate`

## Troubleshooting

| Problem | Solution |
|---------|----------|
| No `/odom` topic | Check robot connection; ensure `go2_drive_py` driver is running |
| Robot doesn't move on goal | Confirm `/api/sport/request` is publishing; check Sport mode is active |
| Goal ignored | Goals must be in `odom` frame (set RViz Fixed Frame to `odom`) |
| `unitree_api` not found | Build [unitree_ros2](https://github.com/unitreerobotics/unitree_ros2) first |
| TF errors in RViz | Ensure `publish_tf: true` in `drive.yaml` |

## License

See individual package licenses in `src/*/package.xml`.

## Maintainer

m2m — houshoulaopo@gmail.com
