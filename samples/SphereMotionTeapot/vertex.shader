/*
<codex>
<abstract>Simple vertex shader.</abstract>
<version>1.0</version>
</codex>
*/

struct directional_light {
	vec3 direction;
	vec3 halfplane;
	vec4 ambient_color;
	vec4 diffuse_color;
	vec4 specular_color;
};

struct material_properties {
	vec4 ambient_color;
	vec4 diffuse_color;
	vec4 specular_color;
	float specular_exponent;
};

uniform mat4 u_mvpMatrix;
uniform mat3 u_modelViewMatrix;
uniform material_properties u_material;
uniform directional_light u_light;

attribute vec4 a_position;
attribute vec3 a_normal;

varying vec4 v_color;

const float c_zero = 0.0;
const float c_one = 1.0;

vec4 compute_color(vec3 normal)
{
	vec4 computed_color = vec4(c_zero, c_zero, c_zero, c_zero);
	float ndotl;	// normal dot light direction
	float ndoth;	// normal dot half-plane vector
	
	ndotl = max(c_zero, dot(normal, u_light.direction));
	ndoth = max(c_zero, dot(normal, u_light.halfplane));
	
	computed_color += (u_light.ambient_color * u_material.ambient_color);
	computed_color += (ndotl * u_light.diffuse_color * u_material.diffuse_color);
	
	if (ndoth > c_zero) {
		computed_color += (pow(ndoth, u_material.specular_exponent) * u_material.specular_color * u_light.specular_color);
	}
	return computed_color;
}

void main()
{
	gl_Position = u_mvpMatrix * a_position;
	v_color = compute_color(normalize(u_modelViewMatrix * a_normal));
}
