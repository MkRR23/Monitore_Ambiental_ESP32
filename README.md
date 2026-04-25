# 🌡️ Sistema de Monitoreo Ambiental con ESP32

Sistema embebido de monitoreo en tiempo real de temperatura, humedad y CO₂, con visualización en dashboard web accesible desde cualquier dispositivo en red local.

---

## 📋 Descripción

Este proyecto captura datos ambientales cada 10 segundos usando un microcontrolador ESP32 y tres sensores. Los datos se envían por WiFi a una API en PHP, se almacenan en una base de datos MySQL, y se visualizan en un dashboard web con gráficas interactivas y tabla de historial.

---

## 🔧 Hardware utilizado

| Componente | Función |
|---|---|
| ESP32 | Microcontrolador principal / WiFi |
| PT1000 + MAX31865 | Sensor de temperatura de alta precisión |
| DHT21 | Sensor de humedad relativa |
| SCD30 | Sensor de CO₂ (ppm) |

---

## 📌 Diagrama de conexiones

### MAX31865 → ESP32 (SPI)
| MAX31865 | ESP32 |
|---|---|
| VCC | 3.3V |
| GND | GND |
| CLK | GPIO 18 |
| MISO | GPIO 19 |
| MOSI | GPIO 23 |
| CS | GPIO 5 |

### DHT21 → ESP32
| DHT21 | ESP32 |
|---|---|
| VCC | 3.3V |
| GND | GND |
| DATA | GPIO 4 |

> Requiere resistencia pull-up de 4.7kΩ entre VCC y DATA.

### SCD30 → ESP32 (I2C)
| SCD30 | ESP32 |
|---|---|
| VCC | 3.3V |
| GND | GND |
| SCL | GPIO 22 |
| SDA | GPIO 21 |

---

## 🗂️ Estructura del proyecto
