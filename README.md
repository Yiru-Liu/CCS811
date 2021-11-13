# CCS811
Arduino code for working with the CCS811 sensor

Circuit:
- Connections from CCS811 module to Arduino Uno:
  - GND &mdash; GND
  - VCC &mdash; 5V
  - SDA &mdash; A4
  - SCL &mdash; A5
  - RST &mdash; No connection
  - WAKE &mdash; GND
  - INT &mdash; No connection
- Connections from LCD1602 to Arduino Uno:
  - VSS &mdash; GND
  - VDD &mdash; 5V
  - VO &mdash; Connected to the middle pin of potentiometer with the two other pins connected to GND and 5V respectively; the potentiometer controls the contrast setting of the display.
  - RS &mdash; Digital Pin 4
  - RW &mdash; GND
  - E &mdash; Digital Pin 6
  - D0 through D3 &mdash; No connection
  - D4 &mdash; Digital Pin 10
  - D5 &mdash; Digital Pin 11
  - D6 &mdash; Digital Pin 12
  - D7 &mdash; Digital Pin 13
  - A &mdash; 3.3V
  - K &mdash; GND
