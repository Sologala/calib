# Calib

# Usage

## Dependencies
1. opencv 4.+
2. qt5

## Clone
```shell
git clone --recurse-submodules https://github.com/Sologala/calib.git
```
## Build
```shell
mkdir build && cd build
cmake ..
make -j
```

# Core

- 相机模型
    - 通用相机模型
- IMU相关定义

# front end

前端都包含那些呢？

- 标定板
  - 生成
  - 检测
  - 3D关联
- 持续性标定
  - 标定效果展示
- UI
  - 标定效果展示
  - 绘制点
  - 绘制相机
  - 指标生成
- ROS
- 仿真

# back end

- 优化

# [标定效果评价](https://github.com/puzzlepaint/camera_calibration#how-to-obtain-and-verify-good-calibration-results)



# [GUI](./apps/README.md)
