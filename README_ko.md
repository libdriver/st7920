[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.png"/>
</div>

## LibDriver ST7920

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/st7920/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

ST7920 LCD 컨트롤러/드라이버 IC는 알파벳, 숫자, 중국어 글꼴 및 자체 정의 문자를 표시할 수 있습니다. 8비트, 4비트 및 직렬의 3가지 종류의 버스 인터페이스를 지원합니다. 디스플레이 RAM, 문자 생성 ROM, LCD 디스플레이 드라이버 및 제어 회로를 포함한 모든 기능이 모두 하나의 칩 솔루션에 있습니다. 최소한의 시스템 구성으로 한자 표시 시스템을 쉽게 구현할 수 있습니다. ST7920에는 8192개의 16x16 도트 중국어 글꼴과 126개의 16x8 도트 반각 영숫자 글꼴이 있는 문자 ROM이 포함되어 있습니다. 또한 그래픽 디스플레이(GDRAM)를 위한 64x256 도트 그래픽 디스플레이 영역을 지원합니다. 믹스 모드 디스플레이
문자 및 그래픽 데이터 모두 가능합니다. ST7920에는 CGRAM이 내장되어 있으며 4세트 소프트웨어 프로그래밍 가능 16x16 글꼴을 제공합니다. ST7920은 넓은 작동 전압 범위(2.7V ~ 5.5V)를 제공합니다. 또한 전력 소모가 적습니다. 따라서 ST7920은 배터리 구동식 휴대용 장치에 적합합니다. ST7920 LCD 드라이버는 32-common 및 64-segment로 구성됩니다.

LibDriver ST7920은 LibDriver에서 출시한 ST7920의 전체 기능 드라이버입니다. 단일 포인트 그리기, 블록 채우기, 이미지 표시 등의 기능을 제공합니다. LibDriver는 MISRA를 준수합니다.

### 콘텐츠

  - [설명](#설명)
  - [설치](#설치)
  - [사용](#사용)
    - [example basic](#example-basic)
    - [example advance](#example-advance)
  - [문서](#문서)
  - [기고](#기고)
  - [저작권](#저작권)
  - [문의하기](#문의하기)

### 설명

/src 디렉토리에는 LibDriver ST7920의 소스 파일이 포함되어 있습니다.

/interface 디렉토리에는 LibDriver ST7920용 플랫폼 독립적인 GPIO버스 템플릿이 포함되어 있습니다.

/test 디렉토리에는 LibDriver ST7920드라이버 테스트 프로그램이 포함되어 있어 칩의 필요한 기능을 간단히 테스트할 수 있습니다.

/example 디렉토리에는 LibDriver ST7920프로그래밍 예제가 포함되어 있습니다.

/doc 디렉토리에는 LibDriver ST7920오프라인 문서가 포함되어 있습니다.

/datasheet 디렉토리에는 ST7920데이터시트가 있습니다.

/project 디렉토리에는 일반적으로 사용되는 Linux 및 마이크로컨트롤러 개발 보드의 프로젝트 샘플이 포함되어 있습니다. 모든 프로젝트는 디버깅 방법으로 셸 스크립트를 사용하며, 자세한 내용은 각 프로젝트의 README.md를 참조하십시오.

### 설치

/interface 디렉토리에서 플랫폼 독립적인GPIO버스 템플릿을 참조하여 지정된 플랫폼에 대한 GPIO버스 드라이버를 완성하십시오.

/src 디렉토리, /interface 디렉토리 및 /example 디렉토리를 프로젝트에 추가하십시오.

### 사용

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

이미지 추출 형식 및 모든 픽셀이 1바이트에 저장됩니다.

<div align=center>
<img src="/doc/image/image_format.png"/>
</div>

```c
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

### 문서

온라인 문서: https://www.libdriver.com/docs/st7920/index.html

오프라인 문서: /doc/html/index.html

### 기고

연락주세요lishifenging@outlook.com

### 저작권

저작권 (c) 2015 - 지금 LibDriver 판권 소유

MIT 라이선스(MIT)

이 소프트웨어 및 관련 문서 파일("소프트웨어")의 사본을 얻은 모든 사람은 이에 따라 무제한 사용, 복제, 수정, 통합, 출판, 배포, 2차 라이선스를 포함하여 소프트웨어를 처분할 수 있는 권리가 부여됩니다. 소프트웨어의 사본에 대한 라이선스 및/또는 판매, 그리고 소프트웨어가 위와 같이 배포된 사람의 권리에 대한 2차 라이선스는 다음 조건에 따릅니다.

위의 저작권 표시 및 이 허가 표시는 이 소프트웨어의 모든 사본 또는 내용에 포함됩니다.

이 소프트웨어는 상품성, 특정 목적에의 적합성 및 비침해에 대한 보증을 포함하되 이에 국한되지 않는 어떠한 종류의 명시적 또는 묵시적 보증 없이 "있는 그대로" 제공됩니다. 어떤 경우에도 저자 또는 저작권 소유자는 계약, 불법 행위 또는 기타 방식에 관계없이 소프트웨어 및 기타 소프트웨어 사용으로 인해 발생하거나 이와 관련하여 발생하는 청구, 손해 또는 기타 책임에 대해 책임을 지지 않습니다.

### 문의하기

연락주세요lishifenging@outlook.com