# C 图书管理系统（作品集版）

本项目是早期课程作业的重构版本，现用于个人开源作品集展示。

- 英文主文档: [../README.md](../README.md)
- 日文文档: [README.ja.md](README.ja.md)
- 文档索引: [INDEX.md](INDEX.md)

## 功能

- 用户注册与登录
- 管理员模式（增删图书）
- 普通用户借书与还书
- 按书名、作者、年份检索
- 后台管理（用户与借阅记录）

## 构建

```bash
make
```

无 `make` 时：

```bash
gcc -O2 -Wall -Wextra -std=c11 -o library main.c interface.c management.c book_management.c user_management.c
```

## 运行

```bash
./library books.txt user.txt loan.txt
```

Windows PowerShell:

```powershell
.\\library.exe books.txt user.txt loan.txt
```

## 说明

- 示例数据已脱敏，可直接公开。
- 旧版本整理与清理说明见 [project-legacy-notes.md](project-legacy-notes.md)。
