<?php
header("Content-Type: application/json");
header("Access-Control-Allow-Origin: *");

$servidor  = "localhost";
$username  = "";  //Your database username here in XAMPP is usually "root"
$password  = "";   //Your database password here in XAMPP is usually empty
$database  = ""; //Your database name here

$con = new mysqli($servidor, $username, $password, $database);

if ($con->connect_error) {
    echo json_encode(["error" => "Conexión fallida: " . $con->connect_error]);
    exit;
}

$limite = isset($_GET["limite"]) ? intval($_GET["limite"]) : 50;
if ($limite < 1 || $limite > 500) $limite = 50;

$stmt = $con->prepare(
    "SELECT temperatura, humedad, CO2, fecha, hora
     FROM Datos
     ORDER BY fecha DESC, hora DESC
     LIMIT ?"
);
$stmt->bind_param("i", $limite);
$stmt->execute();
$result = $stmt->get_result();

$rows = [];
while ($row = $result->fetch_assoc()) {
    $rows[] = $row;
}


$rows = array_reverse($rows);

echo json_encode(["data" => $rows, "total" => count($rows)]);

$stmt->close();
$con->close();
?>
