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
monitoreo-ambiental-esp32/


├── esp32/
│   ├── MonitoreoAmbiental.ino

├── servidor/
│   ├── API.php
│   ├── getData.php
│   └── db_config.example.php  ← Copia como db_config.php y agrega tus datos

├── dashboard/
    └── dashboard.html


---

## ⚙️ Instalación

### Requisitos
- [XAMPP](https://www.apachefriends.org/) (Apache + MySQL + PHP)
- [Arduino IDE](https://www.arduino.cc/en/software)
- Librerías de Arduino:
  - `Adafruit MAX31865`
  - `DHT sensor library`
  - `SparkFun SCD30 Arduino Library`

### Base de datos

Crea la base de datos en phpMyAdmin con esta estructura:

```sql
CREATE DATABASE esp_db;

USE esp_db;

CREATE TABLE Datos (
  id          INT AUTO_INCREMENT PRIMARY KEY,
  temperatura FLOAT,
  humedad     FLOAT,
  CO2         FLOAT,
  fecha       DATE,
  hora        TIME
);
```

### Configuración del ESP32

1. Copia `esp32/config.example.h` como `esp32/config.h`
2. Llena tu red WiFi y la IP de tu computadora
3. Sube `main.ino` al ESP32 desde Arduino IDE

### Configuración del servidor

1. Copia `servidor/db_config.example.php` como `servidor/db_config.php`
2. Llena tus credenciales de MySQL
3. Copia la carpeta `servidor/` y `dashboard/` a `htdocs/` en XAMPP
4. Inicia Apache y MySQL desde el panel de XAMPP

### Acceso al dashboard

Desde la misma red WiFi abre en el navegador:
http://TU_IP_LOCAL/dashboard/dashboard.html



---

## 🛠️ Tecnologías usadas

- C++ / Arduino
- PHP
- MySQL
- HTML / CSS / JavaScript
- Chart.js
- XAMPP

---

## 📊 Funcionalidades del dashboard

- Tarjetas con el último valor registrado de cada sensor
- Gráficas de línea por sensor con historial
- Tabla de registros ordenable por columna
- Actualización automática cada 10 segundos
- Diseño responsivo para celular y escritorio

---
