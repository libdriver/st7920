[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver ST7920

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/st7920/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE) 

Der ST7920 LCD-Controller/Treiber-IC kann Alphabete, Zahlen, chinesische Schriftarten und selbst definierte Zeichen anzeigen. Es unterstützt 3 Arten von Busschnittstellen, nämlich 8-Bit, 4-Bit und seriell. Alle Funktionen, einschließlich Anzeige-RAM, Zeichenerzeugungs-ROM, LCD-Anzeigetreiber und Steuerschaltungen, befinden sich alle in einer Ein-Chip-Lösung. Mit einer minimalen Systemkonfiguration kann leicht ein Anzeigesystem für chinesische Schriftzeichen erreicht werden. Der ST7920 enthält ein Zeichen-ROM mit 8192 16 x 16 Punkten chinesischen Schriftarten und 126 16 x 8 Punkten halbbreiten alphanumerischen Schriftarten. Außerdem unterstützt es einen Grafikanzeigebereich mit 64 x 256 Punkten für die Grafikanzeige (GDRAM). Mix-Modus-Anzeige mit
sowohl Zeichen- als auch Grafikdaten sind möglich. Der ST7920 verfügt über einen integrierten CGRAM und bietet 4 Sätze softwareprogrammierbarer 16x16-Schriftarten. Der ST7920 verfügt über einen großen Betriebsspannungsbereich (2,7 V bis 5,5 V). Es hat auch einen geringen Stromverbrauch. Daher ist der ST7920 für batteriebetriebene tragbare Geräte geeignet. Der ST7920-LCD-Treiber besteht aus 32 gemeinsamen und 64 Segmenten.

LibDriver ST7920 ist der Treiber mit vollem Funktionsumfang von ST7920, der von LibDriver gestartet wurde. Er bietet die Funktionen zum Zeichnen von Einzelpunkten, Füllen von Blöcken, Bildanzeige usw. LibDriver ist MISRA-kompatibel.

### Inhaltsverzeichnis

  - [Anweisung](#Anweisung)
  - [Installieren](#Installieren)
  - [Nutzung](#Nutzung)
    - [example basic](#example-basic)
    - [example advance](#example-advance)
  - [Dokument](#Dokument)
  - [Beitrag](#Beitrag)
  - [Lizenz](#Lizenz)
  - [Kontaktieren Sie uns](#Kontaktieren-Sie-uns)

### Anweisung

/src enthält LibDriver ST7920-Quelldateien.

/interface enthält die plattformunabhängige Vorlage LibDriver ST7920 GPIO.

/test enthält den Testcode des LibDriver ST7920-Treibers und dieser Code kann die erforderliche Funktion des Chips einfach testen.

/example enthält LibDriver ST7920-Beispielcode.

/doc enthält das LibDriver ST7920-Offlinedokument.

/Datenblatt enthält ST7920-Datenblatt.

/project enthält den allgemeinen Beispielcode für Linux- und MCU-Entwicklungsboards. Alle Projekte verwenden das Shell-Skript, um den Treiber zu debuggen, und die detaillierten Anweisungen finden Sie in der README.md jedes Projekts.

/misra enthält die Ergebnisse des LibDriver MISRA Code Scans.

### Installieren

Verweisen Sie auf eine plattformunabhängige GPIO-Schnittstellenvorlage und stellen Sie Ihren Plattform-GPIO-Treiber fertig.

Fügen Sie /src, /interface und /example zu Ihrem Projekt hinzu.

### Nutzung

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

Das Bildextraktionsformat ist wie folgt und jedes Pixel wird in einem Byte gespeichert.

<div align=center>
<img src="/doc/image/image_format.svg" width="220" height="220"/>
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

### Dokument

Online-Dokumente: [https://www.libdriver.com/docs/st7920/index.html](https://www.libdriver.com/docs/st7920/index.html).

Offline-Dokumente: /doc/html/index.html.

### Beitrag

Bitte beachten Sie CONTRIBUTING.md.

### Lizenz

Urheberrechte © (c) 2015 - Gegenwart LibDriver Alle Rechte vorbehalten



Die MIT-Lizenz (MIT)



Hiermit wird jeder Person kostenlos die Erlaubnis erteilt, eine Kopie zu erhalten

dieser Software und zugehörigen Dokumentationsdateien (die „Software“) zu behandeln

in der Software ohne Einschränkung, einschließlich, aber nicht beschränkt auf die Rechte

zu verwenden, zu kopieren, zu modifizieren, zusammenzuführen, zu veröffentlichen, zu verteilen, unterzulizenzieren und/oder zu verkaufen

Kopien der Software und Personen, denen die Software gehört, zu gestatten

dazu eingerichtet werden, unter folgenden Bedingungen:



Der obige Urheberrechtshinweis und dieser Genehmigungshinweis müssen in allen enthalten sein

Kopien oder wesentliche Teile der Software.



DIE SOFTWARE WIRD "WIE BESEHEN" BEREITGESTELLT, OHNE JEGLICHE GEWÄHRLEISTUNG, AUSDRÜCKLICH ODER

STILLSCHWEIGEND, EINSCHLIESSLICH, ABER NICHT BESCHRÄNKT AUF DIE GEWÄHRLEISTUNG DER MARKTGÄNGIGKEIT,

EIGNUNG FÜR EINEN BESTIMMTEN ZWECK UND NICHTVERLETZUNG VON RECHTEN DRITTER. IN KEINEM FALL DARF DAS

AUTOREN ODER URHEBERRECHTSINHABER HAFTEN FÜR JEGLICHE ANSPRÜCHE, SCHÄDEN ODER ANDERE

HAFTUNG, OB AUS VERTRAG, DELIKT ODER ANDERWEITIG, ENTSTEHEND AUS,

AUS ODER IM ZUSAMMENHANG MIT DER SOFTWARE ODER DER VERWENDUNG ODER ANDEREN HANDLUNGEN MIT DER

SOFTWARE.

### Kontaktieren Sie uns

Bitte senden Sie eine E-Mail an lishifenging@outlook.com.