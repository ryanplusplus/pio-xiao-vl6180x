#include <Arduino.h>
#include <Adafruit_VL6180X.h>

extern "C" {
#include <stddef.h>
#include "tiny_timer.h"
#include "tiny_time_source.h"
#include "tiny_heartbeat.h"
}

static tiny_timer_group_t timer_group;
static Adafruit_VL6180X sensor;

void setup()
{
  Serial.begin(9600);

  sensor.begin();

  tiny_timer_group_init(&timer_group, tiny_time_source_init());
  tiny_heartbeat_init(&timer_group, 1000);
}

void loop()
{
  tiny_timer_group_run(&timer_group);

  Serial.println("Lux: " + String(sensor.readLux(VL6180X_ALS_GAIN_5)));

  uint8_t range = sensor.readRange();

  if(sensor.readRangeStatus() == VL6180X_ERROR_NONE) {
    Serial.println("Range: " + String(range));
  }
  else {
    Serial.println("Range: ?");
  }

  delay(500);
}
