#define USER_SETUP_INFO "User_Setup"

#define USE_HSPI_PORT

// Driver e Resolução
#define ST7789_DRIVER
#define TFT_WIDTH  240
#define TFT_HEIGHT 320
#define TFT_RGB_ORDER TFT_BGR

// Pinos para ESP32-S3 (Conforme sua ligação física)
#define TFT_MOSI 11
#define TFT_SCLK 12
#define TFT_CS   13
#define TFT_DC    9
#define TFT_RST  -1

// Fontes (Obrigatório para a biblioteca não dar erro)
#define LOAD_GLCD
#define LOAD_FONT2
#define LOAD_FONT4
#define LOAD_FONT6
#define LOAD_FONT7
#define LOAD_FONT8
#define LOAD_GFXFF

#define SPI_FREQUENCY  40000000 // Frequência de 40MHz
