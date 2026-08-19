#version 330

uniform vec3		objInvFrameRowX;
uniform vec3		objInvFrameRowY; //RowZ for this matrix is ommited as z is recalculated manually
uniform float		halfExtent;
uniform vec2		diskCenter;
uniform float		diskRadius;
uniform int			drawMode;
uniform sampler2D	texture0;
uniform vec2		textureOffset;

vec3	poincareToMinkowski(vec2 poincare)
{
	float	r2 = dot(poincare, poincare);
	if (r2 >= 1.0)
		discard ;
	
	float	denom = 1.0 - r2;
	return vec3(
		2.0 * poincare.x / denom,
		2.0 * poincare.y / denom,
		(1.0 + r2) / denom
	);
}

void main(void)
{
	vec2	poincare = (gl_FragCoord.xy - diskCenter) / diskRadius;
	vec3	minkowski = poincareToMinkowski(poincare);
	
	float	lX = dot(objInvFrameRowX, minkowski);
	float	lY = dot(objInvFrameRowY, minkowski);
	float	lZ = sqrt(lX * lX + lY * lY + 1.0);
	vec2	local = vec2(lX, lY) / (lZ + 1.0);

	if (drawMode == 0)	
		local -= textureOffset;
	local = local / (2.0 * halfExtent) + 0.5;
	if (local.x < 0.0 || local.x > 1.0 || local.y < 0.0 || local.y > 1.0)
		discard ;

	if (drawMode == 0)
	{
		vec4	colour = texture2D(texture0, vec2(local.x, 1.0 - local.y));
		if (colour.a < 0.01)
			discard ;
		gl_FragColor = colour;
	}
	else if (drawMode == 1)
	{
		if (distance(local, vec2(0.5)) > 0.5)
	 		discard ;
		gl_FragColor = vec4(1, 0, 0, 0.6);
	}
}