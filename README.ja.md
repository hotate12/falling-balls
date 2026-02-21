<p align="center">
  <h1 align="center">Falling Balls</h1>
  <p align="center">C と ncurses で作られたターミナルベースの落下ボールゲーム</p>
</p>

<p align="center">
  <a href="LICENSE.txt"><img src="https://img.shields.io/badge/license-MIT-blue.svg" alt="License: MIT"></a>
  <img src="https://img.shields.io/badge/language-C-gray.svg" alt="Language: C">
  <img src="https://img.shields.io/badge/platform-Linux-lightgrey.svg" alt="Platform: Linux">
</p>

<p align="center">
  <a href="README.md">English</a>
</p>

---

**Falling Balls** は、制限時間30秒以内にバスケットを操作して落下するボールをキャッチするターミナルゲームです。C言語と ncurses ライブラリで構築されており、ターミナル上で直接動作します。

## 特徴

- **シンプルで奥深いゲームプレイ** — 矢印キーでバスケットを動かし、できるだけ多くのボールをキャッチ
- **Fever Time** — 8回連続キャッチで発動し、スコアと時間ボーナスが2倍に（8秒間）
- **2種類のボール** — 通常ボール（`o`）は +1点 / +0.8秒、スペシャルボール（`*`）は +3点 / +2秒
- **スコアランキング** — 上位3件のスコアを CSV ファイルにローカル保存
- **どこでも動作** — ncurses 対応の Linux ターミナルがあれば OK（最小 75×17）

## クイックスタート

### 前提条件

- GCC
- GNU Make
- ncurses 開発ライブラリ
- 日本語ロケール（`ja_JP.UTF-8`）

**Ubuntu / Debian の場合：**

```bash
sudo apt install build-essential libncurses5-dev libncursesw5-dev locales
sudo locale-gen ja_JP.UTF-8
```

### ビルド・実行

```bash
cd src
make start
```

コンパイルとゲーム起動を同時に行います。コンパイルのみの場合：

```bash
cd src
make game
```

ビルド成果物のクリーン：

```bash
cd src
make clean
```

### Dev Container の利用

再現可能な開発環境のための Dev Container 設定が同梱されています。VS Code の [Dev Containers 拡張機能](https://marketplace.visualstudio.com/items?itemName=ms-vscode-remote.remote-containers) でプロジェクトを開くと、すべての依存関係が自動的にセットアップされます。

## 遊び方

| 操作 | キー |
|------|------|
| バスケットを左に移動 | ← |
| バスケットを右に移動 | → |
| ゲーム終了 | `q` |

### スコアリング

| イベント | スコア | 時間 |
|----------|--------|------|
| 通常ボール（`o`）をキャッチ | +1 | +0.8秒 |
| スペシャルボール（`*`）をキャッチ | +3 | +2.0秒 |
| ボールを落とした場合 | — | −1.0秒 |

### Fever Time

**8回連続**でボールをキャッチすると Fever Time が発動します（8秒間）。Fever Time 中は：
- すべてのスコア・時間ボーナスが **2倍**
- ボールを落としても時間が**減らない**

## プロジェクト構成

```
.
├── .devcontainer/           # Dev Container 設定
│   ├── Dockerfile
│   └── devcontainer.json
├── src/
│   ├── main.c               # エントリーポイント、ncurses 初期化
│   ├── falling_balls.c            # ゲームループとメカニクス
│   ├── game_sup_func.c      # スコア処理、結果表示、保存
│   ├── scr_sup_func.c       # 画面描画、UI ヘルパー
│   ├── file_io.c            # CSV ファイル入出力
│   ├── makefile
│   └── rw_file/
│       ├── hist_scores.csv  # スコアデータ（永続化）
│       └── help.txt         # ゲーム内ヘルプ
├── LICENSE.txt
├── README.md                # English
└── README.ja.md             # 日本語
```

## 技術詳細

- **言語：** C（C99）
- **UIライブラリ：** ncursesw
- **タイミング制御：** `gettimeofday()` によるミリ秒精度
- **プレイエリア：** 20×12 文字
- **ゲーム時間：** 30秒
- **最小ターミナルサイズ：** 75桁 × 17行

## ライセンス

本プロジェクトは MIT ライセンスの下で公開されています。詳細は [LICENSE.txt](LICENSE.txt) をご覧ください。

## 作者

Kosuke Baba
