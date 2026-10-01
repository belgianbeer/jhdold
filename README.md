# jhdold — 日本語 Hex Dump ユーティリティ（1986–1999 アーカイブ）

[日本語](#日本語) / [English](#english)

> 📦 CVS 時代の**オリジナルのまま**のソースと man を、履歴付きで保存するアーカイブです。
> ここでの開発は行いません。
>
> **現代版（ANSI C 移植 + 保守版）** はこちら 👉 https://github.com/belgianbeer/jhd
> （※ 別リポジトリの URL は計画時点の想定です。実 URL が異なる場合はご一報ください）

## 日本語

### 概要

`jhd`（Japanese HexDump）は、1986 年に開発を開始した日本語対応の hex dump ツールです。
Shift-JIS / EUC を意識した端末出力、漢字・かなの 2 バイト処理、8/16 ビットのオクタル・リトル/ビッグエンディアンダンプなど、当時の日本語 UNIX 端末で「文字化けしないダンプ」を出す工夫が詰まっています。

### 来歴

| 日付 | バージョン | 備考 |
|------|-----------|------|
| 1986-09-11 | v1.0 | 初版 |
| 1988-09-14 | v2.0 | |
| 1989-01-20 | v2.1 | octal-word のバグ修正 |
| 1989-02-23 | v2.2 | stdin 時のオフセット修正 |
| 1999-01-27 | v2.4 | CVS 上での最終版 |

- 作者：民田 雅人（Masato Minda）
- 管理：当初は **CVS**（1986 年〜）。2026 年に **Git** へ履歴移行（`git cvsimport` 使用）。

### 収録物

- `jhd.c` — 原典ソース（K&R スタイル、`#if` で UNIX / OS-9 / LSI-C を分岐）
- `jhd.1` — 日本語 man ページ
- `README.md` / `LICENSE`

> ※ 当時の配布物に `Makefile` は含まれていなかったため、本リポジトリにもありません。
> man のインストール先ディレクトリ（`man/man1` や `share/man/man1` など）も環境差があるため、
> ここでは一般的な手順のみ示します。

### ビルド / man 参照

```sh
cc -O jhd.c -o jhd              # POSIX 環境（FreeBSD / Linux / macOS）想定
man -l ./jhd.1                  # BSD の man なら -l でローカル man を読む
man ./jhd.1                     # Linux 等ではこれで読めることがある
```

`#include <unistd.h>` と `fseek()` を使うため、MSVC 単体では調整が必要です。

### ライセンス

作者本人が所有するフリーソフトウェアです（→ `LICENSE` 参照）。

---

*This repository is frozen. No further changes will be made.*

## English

### Overview

`jhd` (Japanese HexDump) is a Japanese-aware hex dump utility, first developed in 1986.
It handles Shift-JIS / EUC terminal output, 2-byte kanji/kana processing, and 8/16-bit octal dumps (both endiannesses), so that a hex dump of Japanese text wouldn't garble on the Japanese UNIX terminals of the day.

### History

| Date | Version | Notes |
|------|---------|-------|
| 1986-09-11 | v1.0 | Initial release |
| 1988-09-14 | v2.0 | |
| 1989-01-20 | v2.1 | bug fix in octal-word |
| 1989-02-23 | v2.2 | fix offset when file is stdin |
| 1999-01-27 | v2.4 | last version under CVS |

- Author: Masato Minda
- Version control: originally managed under **CVS** (since 1986). History migrated to **Git** in 2026 via `git cvsimport`.

### Contents

- `jhd.c` — original source (K&R style; `#if` blocks for UNIX / OS-9 / LSI-C)
- `jhd.1` — Japanese man page
- `README.md` / `LICENSE`

> No `Makefile` was distributed back then, so none is included here either.
> The man directory (`man/man1`, `share/man/man1`, …) varies by OS, so only a generic path is shown.

### Build / viewing the man page

```sh
cc -O jhd.c -o jhd              # intended for POSIX systems (FreeBSD / Linux / macOS)
man -l ./jhd.1                  # on BSD man, -l reads a local man page
man ./jhd.1                     # on some systems this works too
```

It relies on `<unistd.h>` and `fseek()`, so MSVC alone will need adjustments.

### License

Free software owned by its author. See `LICENSE`.

---

*This repository is frozen. No further changes will be made.*
