[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.png"/>
</div>

## LibDriver ST7920

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/st7920/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

ST7920液晶控制器/驅動IC可以顯示字母、數字、漢字和自定義字符。它支持 3 種總線接口，即 8 位、4 位和串行。所有功能，包括顯示 RAM、字符生成 ROM、LCD 顯示驅動器和控制電路都在一個單芯片解決方案中。只需最少的系統配置，即可輕鬆實現漢字顯示系統。 ST7920包含8192個16x16點中文字體和126個16x8點半角字母數字字體的字符ROM。此外，它還支持 64x256 點圖形顯示區域用於圖形顯示 (GDRAM)。混合模式顯示
字符和圖形數據都是可能的。 ST7920 內置 CGRAM，提供 4 組軟件可編程 16x16 字體。 ST7920 具有寬工作電壓範圍（2.7V 至 5.5V）。它還具有低功耗。所以ST7920是合適的用於電池供電的便攜式設備。 ST7920 LCD 驅動器由 32-common 和 64-segment 組成。

LibDriver ST7920是LibDriver推出的ST7920的全功能驅動，該驅動提供繪製單點，填充塊，圖片顯示等功能並且它符合MISRA標準。

### 目錄

  - [說明](#說明)
  - [安裝](#安裝)
  - [使用](#使用)
    - [example basic](#example-basic)
    - [example advance](#example-advance)
  - [文檔](#文檔)
  - [貢獻](#貢獻)
  - [版權](#版權)
  - [聯繫我們](#聯繫我們)

### 說明

/src目錄包含了LibDriver ST7920的源文件。

/interface目錄包含了LibDriver ST7920與平台無關的GPIO總線模板。

/test目錄包含了LibDriver ST7920驅動測試程序，該程序可以簡單的測試芯片必要功能。

/example目錄包含了LibDriver ST7920編程範例。

/doc目錄包含了LibDriver ST7920離線文檔。

/datasheet目錄包含了ST7920數據手冊。

/project目錄包含了常用Linux與單片機開發板的工程樣例。所有工程均採用shell腳本作為調試方法，詳細內容可參考每個工程裡面的README.md。

### 安裝

參考/interface目錄下與平台無關的GPIO總線模板，完成指定平台的GPIO總線驅動。

將/src目錄，/interface目錄和/example目錄加入工程。

### 使用

#### example basic

```C
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

圖像提取格式如下，每個像素使用1個字節存儲。

<div align=center>
<img src="/doc/image/image_format.png"/>
</div>

```C
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

### 文檔

在線文檔: https://www.libdriver.com/docs/st7920/index.html

離線文檔: /doc/html/index.html

### 貢獻

請聯繫lishifenging@outlook.com

### 版權

版權 (c) 2015 - 現在 LibDriver 版權所有

MIT 許可證（MIT）

特此免費授予任何獲得本軟件副本和相關文檔文件（下稱“軟件”）的人不受限制地處置該軟件的權利，包括不受限制地使用、複製、修改、合併、發布、分發、轉授許可和/或出售該軟件副本，以及再授權被配發了本軟件的人如上的權利，須在下列條件下：

上述版權聲明和本許可聲明應包含在該軟件的所有副本或實質成分中。

本軟件是“如此”提供的，沒有任何形式的明示或暗示的保證，包括但不限於對適銷性、特定用途的適用性和不侵權的保證。在任何情況下，作者或版權持有人都不對任何索賠、損害或其他責任負責，無論這些追責來自合同、侵權或其它行為中，還是產生於、源於或有關於本軟件以及本軟件的使用或其它處置。

### 聯繫我們

請聯繫lishifenging@outlook.com