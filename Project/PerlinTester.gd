extends Control


# Called when the node enters the scene tree for the first time.
func _ready():
	var image = Image.new()
	var width = 512
	var height = 512
	var scale = 8 # Similar to frequency, setting this higher will increase the complexity of the image
	image = Image.create(width, height, false, Image.FORMAT_RGBA8)
	var perlin_noise = get_node("Perlin")
	for y in range(height):
		for x in range(width):
			var fx = x + 0.0
			var fy = y + 0.0
			# Normalize x and y to the desired scale for your noise function
			var nx = scale  * fx / width
			var ny = scale * fy / height
			
			
			# Get the noise value, normalize it to the range 0-1
			var num_octaves = 3
			var persistance = 0.5
			var initial_frequency = 1
			var noise_value = (perlin_noise.generate_fractal_noise(nx , ny, num_octaves, persistance, initial_frequency)) + 0.5
			# print(noise_value)
			var color = Color(noise_value, noise_value, noise_value)
			
			
			
			# Set the pixel color on the image
			image.set_pixel(x, y, color)


	# Create a texture from the image
	image.save_png("res://Images/image.png")
	var texture = ImageTexture.new()
	texture.create_from_image(image)
	

# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	pass
