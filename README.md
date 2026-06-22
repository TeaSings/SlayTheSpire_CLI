# SlayTheSpire_CLI

一个用 C++ 写的命令行小练习，灵感来自《Slay the Spire》。

这个项目是我学习 C++ 过程中练习各种面向对象特性的产物，主要用于熟悉类、继承、多态、虚函数、智能指针、原型模式，以及简单的卡牌/怪物/状态效果建模。

## 项目结构

- `include/`: 头文件
- `src/`: 源代码
- `build/`: 编译输出

## 构建运行

需要支持 C++17 的编译器和 make。

```bash
make
make run
```

清理构建产物：

```bash
make clean
```

Windows 下可使用 MinGW/MSYS2 的 `mingw32-make` 或等价 make 工具。
