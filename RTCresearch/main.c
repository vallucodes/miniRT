#include "tuple.h"

typedef struct t_environment
{
	t_tuple gravity;
	t_tuple wind;
} t_environment;

typedef struct t_projectile
{
	t_tuple position;
	t_tuple velocity;
} t_projectile;

t_projectile tick(t_environment env, t_projectile proj)
{
	t_projectile tmp;

	tmp.position = tuple_add(proj.position, proj.velocity);
	tmp.velocity = tuple_add(proj.velocity, tuple_add(env.gravity, env.wind));

	return tmp;
}

int main(void)
{
	t_environment env;
	t_projectile proj;
	
	double gravity[3] = {0, -0.1, 0};
	double wind[3] = {-0.01, 0, 0};
	
	double position[3] = {0, 1, 0};
	double velocity[3] = {1, 2, 0};

	env.gravity = tuple_from_vector(gravity);
	env.wind = tuple_from_vector(wind);
	
	proj.position = tuple_from_point(position);
	proj.velocity = tuple_normalise(tuple_from_vector(velocity));

	for (;;)
	{
		tuple_print(proj.position);
		tuple_print(proj.velocity);
		printf("\n");
		if (proj.position.y <= 0)
			break;
		proj = tick(env, proj);
	}

	/*
	* Unit tests for tuple operations. 
	*
	double p1[3] = {3, -2, 5};
	double v1[3] = {-2, 3, 1};

	printf("Create 2 tuples, point and vector\nPrint them.\n");
	t_tuple pt1 = tuple_from_point(p1);
	t_tuple vt1 = tuple_from_vector(v1);

	tuple_print(pt1);
	tuple_print(vt1);

	printf("Add them together.\n");
	t_tuple added = tuple_add(pt1, vt1);
	tuple_print(added);

	double p2[3] = {3, 2, 1};
	double p3[3] = {5, 6, 7};

	printf("\nCreate 2 tuples, points\nPrint them.\n");
	t_tuple pt2 = tuple_from_point(p2);
	t_tuple pt3 = tuple_from_point(p3);

	tuple_print(pt2);
	tuple_print(pt3);

	printf("Subtract second from first.\n");
	t_tuple subbed = tuple_sub(pt2, pt3);
	tuple_print(subbed);

	double p4[3] = {3, 2, 1};
	double v5[3] = {5, 6, 7};

	printf("\nCreate 2 tuples, point and vector\nPrint them.\n");
	t_tuple pt4 = tuple_from_point(p4);
	t_tuple vt5 = tuple_from_vector(v5);

	tuple_print(pt4);
	tuple_print(vt5);

	printf("Subtract vector from point.\n");
	t_tuple subbed2 = tuple_sub(pt4, vt5);
	tuple_print(subbed2);

	double v6[3] = {3, 2, 1};

	printf("\nCreate 2 tuples, vector and vector\nPrint them.\n");
	t_tuple vt6 = tuple_from_vector(v6);

	tuple_print(vt6);
	tuple_print(vt5);

	printf("Subtract vector from vector.\n");
	t_tuple subbed3 = tuple_sub(vt6, vt5);
	tuple_print(subbed3);

	double v7[3] = {1, -2, 3};
	t_tuple t8 = tuple_init(1, -2, 3, -4);

	printf("\nCreate 2 tuples, vector and tuple\nPrint them.\n");
	t_tuple vt7 = tuple_from_vector(v7);

	tuple_print(vt7);
	tuple_print(t8);

	printf("Negate and print them.\n");
	t_tuple neg1 = tuple_neg(vt7);
	t_tuple neg2 = tuple_neg(t8);

	tuple_print(neg1);
	tuple_print(neg2);

	printf("\nCreate a tuple\nPrint it.\n");

	tuple_print(t8);

	printf("Multiply by scalar and fraction. then print.\n");
	t_tuple mul1 = tuple_mult(t8, 3.5);
	t_tuple mul2 = tuple_mult(t8, 0.5);

	tuple_print(mul1);
	tuple_print(mul2);

	printf("\nCreate a tuple\nPrint it.\n");

	tuple_print(t8);

	printf("Divide by scalar. then print.\n");
	t_tuple div1 = tuple_div(t8, 2);

	tuple_print(div1);

	double v12[3] = {1,0,0};
	double v8[3] = {0,1,0};
	double v9[3] = {0,0,1};
	double v10[3] = {1,2,3};
	double v11[3] = {-1,-2,-3};
	
	printf("\nCreate 5 tuples, vectors.\nPrint them.\n");
	t_tuple vt12 = tuple_from_vector(v12);
	t_tuple vt8 = tuple_from_vector(v8);
	t_tuple vt9 = tuple_from_vector(v9);
	t_tuple vt10 = tuple_from_vector(v10);
	t_tuple vt11 = tuple_from_vector(v11);

	tuple_print(vt12);
	tuple_print(vt8);
	tuple_print(vt9);
	tuple_print(vt10);
	tuple_print(vt11);

	printf("Calculate magnitude. then print.\n");
	double mag1 = tuple_magnitude(vt12);
	double mag2 = tuple_magnitude(vt8);
	double mag3 = tuple_magnitude(vt9);
	double mag4 = tuple_magnitude(vt10);
	double mag5 = tuple_magnitude(vt11);

	printf("Magnitudes: %f, %f, %f, %f, %f\n", mag1, mag2, mag3, mag4, mag5);
	
	double v13[3] = {4,0,0};
	double v14[3] = {1,2,3};
	
	printf("\nCreate 2 tuples, vectors.\nPrint them.\n");
	t_tuple vt13 = tuple_from_vector(v13);
	t_tuple vt14 = tuple_from_vector(v14);

	tuple_print(vt13);
	tuple_print(vt14);

	printf("Normalise. then print.\n");
	t_tuple norm1 = tuple_normalise(vt13);
	t_tuple norm2 = tuple_normalise(vt14);

	tuple_print(norm1);
	tuple_print(norm2);

	printf("Magnitudes of norm1 and norm2: %f, %f\n", tuple_magnitude(norm1), tuple_magnitude(norm2));

	double v15[3] = {1,2,3};
	double v16[3] = {2,3,4};
	
	printf("\nCreate 2 tuples, vectors.\nPrint them.\n");
	t_tuple vt15 = tuple_from_vector(v15);
	t_tuple vt16 = tuple_from_vector(v16);

	tuple_print(vt15);
	tuple_print(vt16);

	printf("Calculate dot product. then print.\n");
	double dot1 = tuple_dot(vt15, vt16);
	double dot2 = tuple_dot(vt12, vt12);
	double dot3 = tuple_dot(vt12, vt8);

	printf("Dot products: %f, %f, %f\n", dot1, dot2, dot3);

	printf("\nCreate 2 tuples, vectors.\nPrint them.\n");
	tuple_print(vt15);
	tuple_print(vt16);

	printf("Calculate cross product. then print.\n");
	t_tuple cross1 = tuple_cross(vt15, vt16);
	t_tuple cross2 = tuple_cross(vt16, vt15);
	t_tuple cross3 = tuple_cross(vt8, vt9);
	t_tuple cross4 = tuple_cross(vt9, vt8);
	
	tuple_print(cross1);
	tuple_print(cross2);
	tuple_print(cross3);
	tuple_print(cross4);
	*/
}