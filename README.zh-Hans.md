[English](README.md) | [简体中文](README.zh-Hans.md)

# AutoRootMotion

AutoRootMotion 是一个 Unreal Engine 编辑器插件，用于批量/自动管理动画资产（`UAnimSequence`）的 **Root Motion（根运动）** 设置。

> UE 版本：**5.7**（已验证）。其他版本：尽力兼容。

---

## 功能特性

- 在 **内容浏览器（Content Browser）** 右键菜单中批量处理 `UAnimSequence`（动画序列）
- **自动检测**动画是否“可能需要”根运动（基于骨盆位移 + 阈值过滤站立动作的轻微抖动）
- 强制 **开启 Root Motion** / **关闭 Root Motion**
- 操作反馈：通知 + 日志输出

---

## 安装

### 方式（推荐）：项目级插件

将插件文件夹复制到你的项目目录下：YourProject/Plugins/

（通常最终路径形如：`YourProject/Plugins/AutoRootMotion/`）

重启编辑器。若是 C++ 工程，可能会提示编译插件。

在编辑器中启用：

`Edit → Plugins → AutoRootMotion`

---

## 使用方法

1. 在 **内容浏览器（Content Browser）** 中选择一个或多个 `UAnimSequence` 资产
2. 右键 → **AutoRootMotion**

菜单项说明：

- **Detect Root Motion Automatically（自动检测）**
  - 当规则“强烈建议”需要根运动时，会自动开启 Root Motion
  - 不会盲目覆盖你已有的手动选择（强制修改请使用明确的 Enable/Disable 操作）
- **Enable Root Motion（强制开启）**
  - 对选中资产强制开启 Root Motion
- **Disable Root Motion（强制关闭）**
  - 对选中资产强制关闭 Root Motion

---

## 自动检测规则（V1）

目标：识别“类似走/跑等有意义的位移”，同时过滤站立动作的轻微移动（例如换弹/idle 扭腰等）。

- 对骨盆骨骼进行采样（默认骨骼名：`pelvis`），取动画开始/结束时的位移
- 计算位移差值（translation delta）
- 如果位移长度 > **Movement Threshold（位移阈值）**，则认为是“有意义的移动”

备注：

- 如果你的骨架骨盆名称不是 `pelvis`（例如 `Pelvis` / `hip`），需要在代码里调整（后续计划做 Settings 页）。
- 阈值强依赖项目（10uu ≈ 10cm 是一个常见起点，可按需求调整）。

---

## 迭代计划

- Project Settings 设置页：`Project Settings → Plugins → AutoRootMotion`
  - Enable Post Import（导入后自动执行）
  - Movement Threshold（位移阈值）
  - Pelvis Bone Name（骨盆骨骼名）
- 导入后自动执行（可选）
- 缩略图角标 / 内容浏览器标签
- Audit 报告导出（CSV）/ 更丰富 UI
- Undo/Redo 支持（Scoped transactions）

---

## 贡献

欢迎提 Issue / PR。请尽量提供：

- UE 版本
- 复现步骤
- 示例资产（如方便）

---

## 联系方式

有更好的想法或建议，欢迎发邮件：

**aze.unreal@outlook.com**