#include <Adafruit_GFX.h>
#include <Adafruit_NeoPixel.h>
#include <Adafruit_NeoMatrix.h>

#define PIN 12            //Data Pin of WS2812B LEDs
#define MATRIX_HEIGHT 15  //y-Dimension of the matrix
#define MATRIX_WIDTH 15   //x-Dimension of the matrix

//Initialize matrix
Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(
                              MATRIX_WIDTH, MATRIX_HEIGHT,
                              PIN,
                              NEO_MATRIX_BOTTOM + NEO_MATRIX_RIGHT + NEO_MATRIX_ROWS + NEO_MATRIX_PROGRESSIVE,
                              NEO_GRB + NEO_KHZ800
                            );

void setup() {
  Serial.begin(9600);
  matrix.begin();
  matrix.setBrightness(128); //Set matrix brightness (max: 255)
  Serial.println("Initialize LED Matrix");
}

void loop() {
  matrix.fillScreen(matrix.Color(0, 0, 255)); //fill entire screen blue

  //Fade each pixel from blue to black (dark) in 20 steps
  for (int i = 0; i < MATRIX_HEIGHT; i++) {
    for (int i = 0; i < MATRIX_HEIGHT; i++) {
      fadePixel(i, j, matrix.Color(0, 0, 255), matrixColor(0, 0, 0), 20, 0);
    }
  }

}

/* Fade pixel (x, y) from startColor to endColor
    int x: the x-coordinate of the matrix
    int y: the y-coordinate of the matrix
    RGB startColor: the start color of the pixel
    RGB endColor: the end color of the pixel
    int steps: how many color values are calculated between startColor and endColor
    int wait: adds an additional delay between the fade
*/

void fadePixel(int x, int y, RGB startColor, RGB endColor, int steps, int wait) {
  for (int i = 0; i <= steps; i++)
  {
    int newR = startColor.r + (endColor.r - startColor.r) * i / steps;
    int newG = startColor.g + (endColor.g - startColor.g) * i / steps;
    int newB = startColor.b + (endColor.b - startColor.b) * i / steps;

    matrix.drawPixel(x, y, matrix.Color(newR, newG, newB));
    matrix.show();
    delay(wait);
  }
}
