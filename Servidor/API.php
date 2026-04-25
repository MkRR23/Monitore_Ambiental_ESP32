<?php

$servidor = "localhost";
$username = "";  //Your Username, in XAMPP it's usually "root"
$password = ""; //Your Password, in XAMPP it's usually empty, so just leave it as "" if you haven't set one
$database = ""; // Your Database Name, in XAMPP you need to create it first and then put the name here

// Conexión
$con = new mysqli($servidor, $username, $password, $database);

if ($con->connect_error) {
    die("Conexion fallida: " . $con->connect_error);
}

// Verificar método POST
if ($_SERVER["REQUEST_METHOD"] == "POST") {

    if (isset($_POST["Temperatura"]) && isset($_POST["Humedad"]) && isset($_POST["CO2"])) {

        $temp = floatval($_POST["Temperatura"]);
        $hum  = floatval($_POST["Humedad"]);
        $co2  = floatval($_POST["CO2"]);

        // Prepared statement
        $stmt = $con->prepare("INSERT INTO Datos (temperatura, humedad, CO2, fecha, hora) VALUES (?, ?, ?, CURDATE(), CURTIME())");

        $stmt->bind_param("ddd", $temp, $hum, $co2);

        if ($stmt->execute()) {
            echo "OK";
        } else {
            echo "Error: " . $stmt->error;
        }

        $stmt->close();

    } else {
        echo "Faltan datos";
    }
}

$con->close();

?>