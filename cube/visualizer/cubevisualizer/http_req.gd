extends Node3D


func _ready() -> void:
	$HTTPRequest.request_completed.connect(_on_request_completed)
	$HTTPRequest.request("http://127.0.0.1:8080")


func _on_request_completed(result, response_code, headers, body):
	var json = JSON.parse_string(body.get_string_from_utf8())
	var roll: float = json["r"]
	var pitch: float = json["p"]
	var heading: float = json["h"]
	var orientation: Vector3 = Vector3(-pitch, heading, -roll)
	rotation_degrees = orientation
	$HTTPRequest.request("http://127.0.0.1:8080")
