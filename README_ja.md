[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.png"/>
</div>

## LibDriver ST7920

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/st7920/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

ST7920 LCDコントローラー/ドライバーICは、アルファベット、数字、中国語フォント、および自己定義文字を表示できます。 8ビット、4ビット、シリアルの3種類のバスインターフェースに対応しています。ディスプレイRAM、文字生成ROM、LCDディスプレイドライバ、制御回路を含むすべての機能は、すべてワンチップソリューションに含まれています。最小限のシステム構成で、漢字表示システムを簡単に実現できます。ST7920には、8192個の16x16ドットの中国語フォントと126個の16x8ドットの半幅英数字フォントを備えた文字ROMが含まれています。さらに、グラフィックディスプレイ（GDRAM）用の64x256ドットのグラフィックディスプレイ領域をサポートします。ミックスモードディスプレイ
文字データとグラフィックデータの両方が可能です。 ST7920にはCGRAMが内蔵されており、ソフトウェアでプログラム可能な4セットの16x16フォントを提供します。ST7920の動作電圧範囲は広い（2.7V〜5.5V）。また、消費電力も低くなっています。そのため、ST7920はバッテリ駆動のポータブルデバイスに適しています。ST7920LCDドライバは、32コモンと64セグメントで構成されています。

LibDriver ST7920は、LibDriverによって起動されたST7920の全機能ドライバーです。シングルポイントの描画、ブロックの塗りつぶし、画像表示などの機能を提供します。LibDriverはMISRAに準拠しています。

### 目次

  - [説明](#説明)
  - [インストール](#インストール)
  - [使用](#使用)
    - [example basic](#example-basic)
    - [example advance](#example-advance)
  - [ドキュメント](#ドキュメント)
  - [貢献](#貢献)
  - [著作権](#著作権)
  - [連絡して](#連絡して)

### 説明

/ srcディレクトリには、LibDriver ST7920のソースファイルが含まれています。

/ interfaceディレクトリには、LibDriver ST7920用のプラットフォームに依存しないGPIOバステンプレートが含まれています。

/ testディレクトリには、チップの必要な機能を簡単にテストできるLibDriver ST7920ドライバーテストプログラムが含まれています。

/ exampleディレクトリには、LibDriver ST7920プログラミング例が含まれています。

/ docディレクトリには、LibDriver ST7920オフラインドキュメントが含まれています。

/ datasheetディレクトリには、ST7920データシートが含まれています。

/ projectディレクトリには、一般的に使用されるLinuxおよびマイクロコントローラー開発ボードのプロジェクトサンプルが含まれています。 すべてのプロジェクトは、デバッグ方法としてシェルスクリプトを使用しています。詳細については、各プロジェクトのREADME.mdを参照してください。

### インストール

/ interfaceディレクトリにあるプラットフォームに依存しないGPIOバステンプレートを参照して、指定したプラットフォームのGPIOバスドライバを完成させます。

/ srcディレクトリ、/ interfaceディレクトリ、および/exampleディレクトリをプロジェクトに追加します。

### 使用

#### example basic

```C
#include "driver_st7920_basic.h"

uint8_t res;

res = st7920_basic_init();
if (res != 0)
{
    st7920_interface_debug_print("st7920: init failed.\n");

    return 1;
}

res = st7920_basic_write_point(0, 0, 1);
if (res != 0)
{
    st7920_interface_debug_print("st7920: write point failed.\n");
    (void)st7920_basic_deinit();

    return 1;
}

res = st7920_basic_clear();
if (res != 0)
{
    st7920_interface_debug_print("st7920: clear screen failed.\n");
    (void)st7920_basic_deinit();

    return 1;
}

res = st7920_basic_string(0, 0, "LibDriver");
if (res != 0)
{
    st7920_interface_debug_print("st7920: show string failed.\n");
    (void)st7920_basic_deinit();

    return 1;
}

res = st7920_basic_rect(0, 0, 32, 32, 1);
if (res != 0)
{
    st7920_interface_debug_print("st7920: draw rect failed.\n");
    (void)st7920_basic_deinit();

    return 1;
}

res = st7920_basic_deinit();
if (res != 0)
{
    st7920_interface_debug_print("st7920: deinit failed.\n");

    return 1;
}

return 0;
```

#### example advance

画像抽出フォーマットと1バイトに格納されたすべてのピクセル。

<div align=center>
<img src="/doc/image/image_format.png"/>
</div>

```c
#include "driver_st7920_advance.h"

uint8_t res;
uint8_t gs_image[8192];

res = st7920_advance_init();
if (res != 0)
{
    st7920_interface_debug_print("st7920: init failed.\n");

    return 1;
}

res = st7920_advance_clear();
if (res != 0)
{
    st7920_interface_debug_print("st7920: clear screen failed.\n");
    (void)st7920_advance_deinit();

    return 1;
}

res = st7920_advance_string(0, 0, "LibDriver");
if (res != 0)
{
    st7920_interface_debug_print("st7920: show string failed.\n");
    (void)st7920_advance_deinit();

    return 1;
}

res = st7920_advance_write_point(0, 0, 1);
if (res != 0)
{
    st7920_interface_debug_print("st7920: write point failed.\n");
    (void)st7920_advance_deinit();

    return 1;
}

res = st7920_advance_rect(0, 0, 32, 32, 1);
if (res != 0)
{
    st7920_interface_debug_print("st7920: draw rect failed.\n");
    (void)st7920_advance_deinit();

    return 1;
}

res = st7920_advance_picture(0, 0, 127, 63, gs_image);
if (res != 0)
{
    st7920_interface_debug_print("st7920: draw picture failed.\n");
    (void)st7920_advance_deinit();

    return 1;
}

res = st7920_advance_deinit();
if (res != 0)
{
    st7920_interface_debug_print("st7920: deinit failed.\n");

    return 1;
}

return 0;
```

### ドキュメント

オンラインドキュメント: https://www.libdriver.com/docs/st7920/index.html

オフラインドキュメント: /doc/html/index.html

### 貢献

お問い合わせくださいlishifenging@outlook.com

### 著作権

著作権（c）2015-今 LibDriver 全著作権所有

MITライセンス（MIT）

このソフトウェアおよび関連するドキュメントファイル（「ソフトウェア」）のコピーを取得した人は、無制限の使用、複製、変更、組み込み、公開、配布、サブライセンスを含む、ソフトウェアを処分する権利を制限なく付与されます。ソフトウェアのライセンスおよび/またはコピーの販売、および上記のようにソフトウェアが配布された人の権利のサブライセンスは、次の条件に従うものとします。

上記の著作権表示およびこの許可通知は、このソフトウェアのすべてのコピーまたは実体に含まれるものとします。

このソフトウェアは「現状有姿」で提供され、商品性、特定目的への適合性、および非侵害の保証を含むがこれらに限定されない、明示または黙示を問わず、いかなる種類の保証もありません。 いかなる場合も、作者または著作権所有者は、契約、不法行為、またはその他の方法で、本ソフトウェアおよび本ソフトウェアの使用またはその他の廃棄に起因または関連して、請求、損害、またはその他の責任を負わないものとします。

### 連絡して

お問い合わせくださいlishifenging@outlook.com