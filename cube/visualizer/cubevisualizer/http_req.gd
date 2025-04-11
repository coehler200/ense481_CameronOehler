extends Node3D


# Setup callback and make first request to flask server
func _ready() -> void:
	$HTTPRequest.request_completed.connect(_on_request_completed)
	$HTTPRequest.request("http://127.0.0.1:8080")


# On data received
func _on_request_completed(result, response_code, headers, body):
	var json = JSON.parse_string(body.get_string_from_utf8()) # Parse response
	var roll: float = json["r"]
	var pitch: float = json["p"]
	var heading: float = json["h"]
	var orientation: Vector3 = Vector3(-pitch, heading, -roll) # Set orientation of Node3D
	rotation_degrees = orientation
	$HTTPRequest.request("http://127.0.0.1:8080")
