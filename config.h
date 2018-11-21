#define PIN           D6
#define COLOR_ORDER   NEO_BRG
#define CHIPSET       WS2811

#define NUM_TILES_X     4
#define NUM_TILES_Y     1
#define MATRIX_HEIGHT   8
#define MATRIX_WIDTH    8
#define MATRIX_SIZE     MATRIX_HEIGHT*MATRIX_WIDTH
#define PANNEL_WIDTH    MATRIX_WIDTH*NUM_TILES_X
#define NUM_LEDS        (MATRIX_HEIGHT*MATRIX_WIDTH)*(NUM_TILES_X*NUM_TILES_Y)

#define BRIGHTNESS      25 // In percentage

#define DATA_PROVIDER "http://PATH_TO_FILE/api-request.php"
