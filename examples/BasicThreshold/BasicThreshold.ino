#include <Arduino.h>
#include <embedDIP.h>

Image *inputImage = nullptr;
Image *outputImage = nullptr;

void setup() {
  Serial.begin(115200);
  delay(1000);

  if (createImageWH(8, 8, IMAGE_FORMAT_GRAYSCALE, &inputImage) != EMBEDDIP_OK ||
      createImageWH(8, 8, IMAGE_FORMAT_GRAYSCALE, &outputImage) != EMBEDDIP_OK) {
    Serial.println("Image allocation failed");
    return;
  }

  uint8_t *pixels = static_cast<uint8_t *>(inputImage->pixels);
  for (uint32_t i = 0; i < inputImage->size; i++) {
    pixels[i] = (i % inputImage->width) * 32;
  }

  if (grayscaleThreshold(inputImage, outputImage, 128) != EMBEDDIP_OK) {
    Serial.println("Threshold failed");
    return;
  }

  Serial.println("Threshold output:");
  uint8_t *thresholded = static_cast<uint8_t *>(outputImage->pixels);
  for (uint32_t y = 0; y < outputImage->height; y++) {
    for (uint32_t x = 0; x < outputImage->width; x++) {
      Serial.print(thresholded[y * outputImage->width + x] ? '#' : '.');
    }
    Serial.println();
  }
}

void loop() {
}
