# C図書管理システム（ポートフォリオ版）

このリポジトリは、過去の授業課題をオープンソース公開向けに再構成したものです。

- 英語版メインREADME: [../README.md](../README.md)
- 中国語ドキュメント: [README.zh.md](README.zh.md)
- ドキュメント索引: [INDEX.md](INDEX.md)

## 機能

- ユーザー登録・ログイン
- 司書モード（書籍の追加・削除）
- 一般ユーザーの貸出・返却
- タイトル・著者・出版年で検索
- バックエンド管理（ユーザー・貸出記録）

## ビルド

```bash
make
```

`make` がない場合：

```bash
gcc -O2 -Wall -Wextra -std=c11 -o library main.c interface.c management.c book_management.c user_management.c
```

## 実行

```bash
./library books.txt user.txt loan.txt
```

Windows PowerShell:

```powershell
.\\library.exe books.txt user.txt loan.txt
```

## 備考

- サンプルデータは匿名化済みで公開可能です。
- 旧資産の整理内容は [project-legacy-notes.md](project-legacy-notes.md) を参照してください。
