#version 400

in vec3 n; // normals from vertex shader

out vec4 frag_colour;

void main () {
	// use the normals as an interesting colouration
	// whenever you get normals in the fragment shader you should
	// re-normalise them, as scaling and interpolation can bang them about a bit
	vec3 n_wor = normalize (n);
	frag_colour = vec4 (n_wor, 1.0);
}
