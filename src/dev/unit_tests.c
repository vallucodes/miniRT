#include "minirt.h"

bool matrix_equals(t_matrix4 m, float expected[4][4]) {
    for (size_t i = 0; i < 4; ++i)
        for (size_t j = 0; j < 4; ++j)
            if (!is_equal(m.m[i][j], expected[i][j]))
                return false;
    return true;
}

bool equality_matrix(const t_matrix3 *a, const t_matrix3 *b)
{
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (!is_equal(a->m[i][j], b->m[i][j])) {
                return false;
            }
        }
    }
    return true;
}

void test_sub_matrix(void) {
    t_matrix_ctx ctx;
    ctx.size = 3;
    ctx.m.m[0][0] = 1; ctx.m.m[0][1] = 2; ctx.m.m[0][2] = 3;
    ctx.m.m[1][0] = 4; ctx.m.m[1][1] = 5; ctx.m.m[1][2] = 6;
    ctx.m.m[2][0] = 7; ctx.m.m[2][1] = 8; ctx.m.m[2][2] = 9;

    t_matrix_result sub = sub_matrix(&ctx, 1, 1);
    // Should remove row 1, col 1: result is {{1,3},{7,9}}
    if (sub.size == 2 &&
        is_equal(sub.m.m2.m[0][0], 1) &&
        is_equal(sub.m.m2.m[0][1], 3) &&
        is_equal(sub.m.m2.m[1][0], 7) &&
        is_equal(sub.m.m2.m[1][1], 9))
        printf("✅ sub_matrix Test Passed\n");
    else
        printf("❌ sub_matrix Test Failed\n");
}

void test_minor_matrix(void) {
    t_matrix_ctx ctx;
    ctx.size = 3;
    ctx.m.m[0][0] = 1; ctx.m.m[0][1] = 2; ctx.m.m[0][2] = 3;
    ctx.m.m[1][0] = 4; ctx.m.m[1][1] = 5; ctx.m.m[1][2] = 6;
    ctx.m.m[2][0] = 7; ctx.m.m[2][1] = 8; ctx.m.m[2][2] = 9;

    float minor = minor_matrix(&ctx, 0, 0);
    // Minor for (0,0) is determinant of {{5,6},{8,9}} = 5*9-6*8 = 45-48 = -3
    if (is_equal(minor, -3))
        printf("✅ minor_matrix Test Passed\n");
    else
        printf("❌ minor_matrix Test Failed\n");
}

void test_cofactor_matrix(void) {
    t_matrix_ctx ctx;
    ctx.size = 3;
    ctx.m.m[0][0] = 1; ctx.m.m[0][1] = 2; ctx.m.m[0][2] = 3;
    ctx.m.m[1][0] = 4; ctx.m.m[1][1] = 5; ctx.m.m[1][2] = 6;
    ctx.m.m[2][0] = 7; ctx.m.m[2][1] = 8; ctx.m.m[2][2] = 9;

    float cofactor = cofactor_matrix(&ctx, 0, 0);
    // For (0,0), sign is +, so cofactor == minor == -3
    if (is_equal(cofactor, -3))
        printf("✅ cofactor_matrix Test Passed\n");
    else
        printf("❌ cofactor_matrix Test Failed\n");
}

void test_determinant_matrix2(void) {
    t_matrix2 m = { .m = { {1, 2}, {3, 4} } };
    float det = determinant_matrix2(m);
    // 1*4 - 2*3 = 4 - 6 = -2
    if (is_equal(det, -2))
        printf("✅ determinant_matrix2 Test Passed\n");
    else
        printf("❌ determinant_matrix2 Test Failed\n");
}

void test_determinant_matrix3(void) {
    t_matrix3 m = { .m = { {1,2,3}, {4,5,6}, {7,8,9} } };
    float det = determinant_matrix3(m);
    // This matrix is singular, determinant should be 0
    if (is_equal(det, 0))
        printf("✅ determinant_matrix3 Test Passed\n");
    else
        printf("❌ determinant_matrix3 Test Failed\n");
}


void unit_tests_3x3(void)
{
	test_sub_matrix();
	test_minor_matrix();
	test_cofactor_matrix();
	test_determinant_matrix2();
	test_determinant_matrix3();
}

void test_sub_matrix_4x4(void) {
    t_matrix_ctx ctx;
    ctx.size = 4;
    int val = 1;
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            ctx.m.m[i][j] = val++;

    // Remove row 1, col 2
    t_matrix_result sub = sub_matrix(&ctx, 1, 2);
    float expected[3][3] = {
        {1, 2, 4},
        {9,10,12},
        {13,14,16}
    };
    bool pass = (sub.size == 3);
    for (int i = 0; i < 3 && pass; ++i)
        for (int j = 0; j < 3 && pass; ++j)
            if (!is_equal(sub.m.m3.m[i][j], expected[i][j]))
                pass = false;
    if (pass)
        printf("✅ sub_matrix 4x4 Test Passed\n");
    else
        printf("❌ sub_matrix 4x4 Test Failed\n");
}

void test_minor_matrix_4x4(void) {
    t_matrix_ctx ctx;
    ctx.size = 4;
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            ctx.m.m[i][j] = (i == j) ? 1.0f : 0.0f;

    float minor = minor_matrix(&ctx, 0, 0);
    if (is_equal(minor, 1.0f))
        printf("✅ minor_matrix 4x4 Test Passed\n");
    else
        printf("❌ minor_matrix 4x4 Test Failed\n");
}

void test_cofactor_matrix_4x4(void) {
    t_matrix_ctx ctx;
    ctx.size = 4;
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            ctx.m.m[i][j] = (i == j) ? 1.0f : 0.0f;

    float cofactor = cofactor_matrix(&ctx, 0, 0);
    if (is_equal(cofactor, 1.0f))
        printf("✅ cofactor_matrix 4x4 Test Passed\n");
    else
        printf("❌ cofactor_matrix 4x4 Test Failed\n");
}

void test_determinant_matrix4(void) {
    t_matrix4 m = { .m = {
        {1, 0, 0, 0},
        {0, 1, 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 1}
    }};
    float det = determinant_matrix4(m);
    if (is_equal(det, 1.0f))
        printf("✅ determinant_matrix4 (identity) Test Passed\n");
    else
        printf("❌ determinant_matrix4 (identity) Test Failed\n");

    t_matrix4 m2 = { .m = {
        {1, 2, 3, 4},
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9,10,11,12}
    }};
    det = determinant_matrix4(m2);
    if (is_equal(det, 0.0f))
        printf("✅ determinant_matrix4 (singular) Test Passed\n");
    else
        printf("❌ determinant_matrix4 (singular) Test Failed\n");
}

void test_inverse_matrix4(void) {
    t_matrix4 m = { .m = {
        {1, 0, 0, 0},
        {0, 1, 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 1}
    }};
    bool success = false;
    t_matrix4 inv = inverse_matrix(m, &success);
    bool pass = success;
    for (int i = 0; i < 4 && pass; ++i)
        for (int j = 0; j < 4 && pass; ++j)
            if (!is_equal(inv.m[i][j], m.m[i][j]))
                pass = false;
    if (pass)
        printf("✅ inverse_matrix4 (identity) Test Passed\n");
    else
        printf("❌ inverse_matrix4 (identity) Test Failed\n");

    t_matrix4 m2 = { .m = {
        {1, 2, 3, 4},
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9,10,11,12}
    }};
    success = true;
    inv = inverse_matrix(m2, &success);
    if (!success)
        printf("✅ inverse_matrix4 (singular) Test Passed\n");
    else
        printf("❌ inverse_matrix4 (singular) Test Failed\n");
}

void unit_tests_4x4()
{
	test_sub_matrix_4x4();
	test_minor_matrix_4x4();
	test_cofactor_matrix_4x4();
	test_determinant_matrix4();
	test_inverse_matrix4();
}

void test_identity_matrix(void) {
    t_matrix4 m = identity();
    bool pass = true;
    for (int i = 0; i < 4 && pass; ++i)
        for (int j = 0; j < 4 && pass; ++j)
            if (!is_equal(m.m[i][j], (i == j) ? 1.0f : 0.0f))
                pass = false;
    if (pass)
        printf("✅ identity_matrix Test Passed\n");
    else
        printf("❌ identity_matrix Test Failed\n");
}

void test_translation_matrix(void) {
    t_matrix4 m = translation(3, 4, 5);
    bool pass = true;
    float expected[4][4] = {
        {1,0,0,3},
        {0,1,0,4},
        {0,0,1,5},
        {0,0,0,1}
    };
    for (int i = 0; i < 4 && pass; ++i)
        for (int j = 0; j < 4 && pass; ++j)
            if (!is_equal(m.m[i][j], expected[i][j]))
                pass = false;
    if (pass)
        printf("✅ translation_matrix Test Passed\n");
    else
        printf("❌ translation_matrix Test Failed\n");
}

void test_scaling_matrix(void) {
    t_matrix4 m = scaling(2.0f, 3.0f, 4.0f);
    bool pass = true;
    float expected[4][4] = {
        {2,0,0,0},
        {0,3,0,0},
        {0,0,4,0},
        {0,0,0,1}
    };
    for (int i = 0; i < 4 && pass; ++i)
        for (int j = 0; j < 4 && pass; ++j)
            if (!is_equal(m.m[i][j], expected[i][j]))
                pass = false;
    if (pass)
        printf("✅ scaling_matrix Test Passed\n");
    else
        printf("❌ scaling_matrix Test Failed\n");
}

void test_rotation_x_matrix(void) {
    float theta = M_PI / 2; // 90 degrees
    t_matrix4 m = rotation_x(theta);
    bool pass = true;
    float expected[4][4] = {
        {1,0,0,0},
        {0,cos(theta),-sin(theta),0},
        {0,sin(theta), cos(theta),0},
        {0,0,0,1}
    };
    for (int i = 0; i < 4 && pass; ++i)
        for (int j = 0; j < 4 && pass; ++j)
            if (!is_equal(m.m[i][j], expected[i][j]))
                pass = false;
    if (pass)
        printf("✅ rotation_x_matrix Test Passed\n");
    else
        printf("❌ rotation_x_matrix Test Failed\n");
}

void test_rotation_y_matrix(void) {
    float theta = M_PI / 2; // 90 degrees
    t_matrix4 m = rotation_y(theta);
    bool pass = true;
    float expected[4][4] = {
        {cos(theta),0,sin(theta),0},
        {0,1,0,0},
        {-sin(theta),0,cos(theta),0},
        {0,0,0,1}
    };
    for (int i = 0; i < 4 && pass; ++i)
        for (int j = 0; j < 4 && pass; ++j)
            if (!is_equal(m.m[i][j], expected[i][j]))
                pass = false;
    if (pass)
        printf("✅ rotation_y_matrix Test Passed\n");
    else
        printf("❌ rotation_y_matrix Test Failed\n");
}

void test_rotation_z_matrix(void) {
    float theta = M_PI / 2; // 90 degrees
    t_matrix4 m = rotation_z(theta);
    bool pass = true;
    float expected[4][4] = {
        {cos(theta),-sin(theta),0,0},
        {sin(theta), cos(theta),0,0},
        {0,0,1,0},
        {0,0,0,1}
    };
    for (int i = 0; i < 4 && pass; ++i)
        for (int j = 0; j < 4 && pass; ++j)
            if (!is_equal(m.m[i][j], expected[i][j]))
                pass = false;
    if (pass)
        printf("✅ rotation_z_matrix Test Passed\n");
    else
        printf("❌ rotation_z_matrix Test Failed\n");
}

void unit_tests_transform_matrices()
{
	test_identity_matrix();
	test_translation_matrix();
	test_scaling_matrix();
	test_rotation_x_matrix();
	test_rotation_y_matrix();
	test_rotation_z_matrix();
}

void	set_transform(t_scene_obj *object, t_matrix4 trans_mtrx)
{
	object->transform = trans_mtrx;
}

/*void test_normal_at_sphere(t_minirt *m)
{
	printf("Testing normal at sphere point. \n");
	t_scene_obj obj;

	obj.dia = 2;
	obj.transform = identity(m);
	obj.cx = 0;
	obj.cy = 0;
	obj.cz = 0;
	obj.mat = init_material();

	set_transform(&obj, translation(m, 0, 0, 0));
	print_matrix(obj.transform, "Initial s1 transform", 4);

	t_tuple	nor = normal_at_sphere(m, &obj, create_point(1, 0 ,0));
	printf("world normal 1,0,0\n");
	print_tuple(nor);
	nor = normal_at_sphere(m, &obj, create_point(0, 1 ,0));
	printf("world normal 0,1,0\n");
	print_tuple(nor);
	nor = normal_at_sphere(m, &obj, create_point(0, 0 ,1));
	printf("world normal 0,0,1\n");
	print_tuple(nor);

	nor = normal_at_sphere(m, &obj, create_point(0.57735, 0.57735, 0.57735));
	printf("world normal sqrt3/3\n");
	print_tuple(nor);

	set_transform(&obj, translation(m, 0, 1, 0));
	print_matrix(obj.transform, "Initial s1 transform", 4);

	nor = normal_at_sphere(m, &obj, create_point(0, 1.70711, -0.70711));
	printf("world normal translated by 0,1,0\n");
	print_tuple(nor);

	float **sca = scaling(m, 1, 0.5, 1);
	print_matrix(sca, "sca", 4);
	float **rot = rotation_z(m, 0.62832);
	print_matrix(rot, "rot", 4);
	float **sca_rot = multiply_mtrx_by_mtrx(m, sca, rot, 4);
	print_matrix(sca_rot, "sca * rot", 4);
	set_transform(&obj, sca_rot);
	print_matrix(obj.transform, "Initial s1 transform", 4);
	nor = normal_at_sphere(m, &obj, create_point(0, 0.70711, -0.70711));
	printf("world normal scaled and rotated\n");
	print_tuple(nor);
}*/

void	test_reflect(t_minirt m)
{
	(void)m;

	printf("Testing reflection about normal. \n");
	printf("approach 45 degree\n");
	t_tuple	v1 = create_vector(1, -1, 0);
	// t_tuple p1 = create_point(0, 0, 0);
	t_tuple n1 = create_vector(0, 1, 0);
	// t_ray r1 = create_ray(v1, p1);
	print_tuple(reflect(v1, n1));

	printf("approach 45 degree inclined surface vertically\n");
	t_tuple	v2 = create_vector(0, -1, 0);
	// t_tuple p2 = create_point(0, 0, 0);
	t_tuple n2 = create_vector(0.707107, 0.707107, 0);
	// t_ray r2 = create_ray(v2, p2);
	print_tuple(reflect(v2, n2));
}

void	test_reflect_extra(t_minirt m)
{
	(void)m;

	printf("Testing reflection edge cases and angles.\n");

	printf("approach straight on (no angle)\n");
	printf("Expect (0, 1, 0)\n");
	t_tuple v1 = create_vector(0, -1, 0);
	t_tuple n1 = create_vector(0, 1, 0);
	print_tuple(reflect(v1, n1));

	printf("approach parallel to surface (no reflection)\n");
	printf("Expect (1, 0, 0)\n");
	t_tuple v2 = create_vector(1, 0, 0);
	t_tuple n2 = create_vector(0, 1, 0);
	print_tuple(reflect(v2, n2));

	printf("approach 45 degrees from below to inclined plane\n");
	printf("Expect (1, -1, 0)\n");
	t_tuple v3 = create_vector(1, -1, 0);
	t_tuple n3 = create_vector(0.707107, 0.707107, 0);
	print_tuple(reflect(v3, n3));  // Expect (0, 1, 0)

	printf("reflect across Z axis\n");
	printf("Expect (0, 0, 1)\n");
	t_tuple v4 = create_vector(0, 0, -1);
	t_tuple n4 = create_vector(0, 0, 1);
	print_tuple(reflect(v4, n4));  // Expect (0, 0, 1)

	printf("reflect diagonally in all directions\n");
	printf("Expect (1, 1, 1)\n");
	t_tuple v5 = create_vector(1, -1, 1);
	t_tuple n5 = create_vector(0, 1, 0);
	print_tuple(reflect(v5, n5));  // Expect (1, 1, 1)
}


/*void test_point_light_material(void)
{
	t_color intensity = color(1, 1, 1);
	t_tuple position = create_point(0, 0, 0);
	t_light light;
	t_sphere s;
	t_material mat = init_material();

	light.col = intensity;
	light.ori = position;

	printf("light position\n");
	print_tuple(light.ori);
	printf("light intensity\n");
	print_colour(light.col);

	s.mat = mat;
	printf("Mat, amb: %f, dif: %f, spec: %f, shine: %f\n", s.mat.ambient, s.mat.diffuse, s.mat.specular, s.mat.shininess);
	printf("mat col:\n");
	print_colour(s.mat.col);

	s.mat.ambient = 1;
	s.mat.diffuse = 1;
	s.mat.specular = 1;
	s.mat.shininess = 100;
	s.mat.col = color(0.5, 0.4, 0.3);
	printf("Mat, amb: %f, dif: %f, spec: %f, shine: %f\n", s.mat.ambient, s.mat.diffuse, s.mat.specular, s.mat.shininess);
	printf("mat col:\n");
	print_colour(s.mat.col);
}*/

/*void	test_point_light_reflections(void)
{
	t_material mat = init_material();
	t_tuple	position = create_point(0, 0, 0);

	t_tuple eyev = create_vector(0, 0, -1);
	t_tuple	normalv = create_vector(0, 0, -1);
	t_light light;
	light.ori = create_point(0, 0, -10);
	light.col = color(1, 1, 1);
	light.ratio = 1;
	bool in_shadow = 0;
	t_color res = lighting(mat, light, position, eyev, normalv, in_shadow);
	printf("Result. Lighting with the eye between the light and the surface.\n");
	print_colour(res);

	t_tuple eyev2 = create_vector(0, 0.707107, -0.707107);
	res = lighting(mat, light, position, eyev2, normalv, in_shadow);
	printf("Result. Lighting with the eye between light and surface, eye offset 45°\n");
	print_colour(res);

	light.ori.y = 10;
	res = lighting(mat, light, position, eyev, normalv, in_shadow);
	printf("Result. Lighting with eye opposite surface, light offset 45°\n");
	print_colour(res);

	t_tuple eyev3 = create_vector(0, -0.707107, -0.707107);
	res = lighting(mat, light, position, eyev3, normalv, in_shadow);
	printf("Result. Lighting with eye in the path of the reflection vector\n");
	print_colour(res);

	light.ori.y = 0;
	light.ori.z = 10;
	res = lighting(mat, light, position, eyev, normalv, in_shadow);
	printf("Result. Lighting with the light behind the surface\n");
	print_colour(res);
}*/



//run this test with
// sp 	     	0,0,0	        2 		 204,255,153
// sp 	     	0,0,0	        2 		 255,0,0
// in .rt file for example

void	test_intersect_two_spheres(t_minirt *minirt)
{
	t_xs xs;
	minirt->world->lig_s.col = color(1, 1, 1);

	t_list	*temp = minirt->world->objects;
	//first sphere
	t_scene_obj *obj = (t_scene_obj *)temp->content;
	obj->mat.diffuse = 0.7;
	obj->mat.specular = 0.2;
	obj->transform = identity();
	//next sphere
	temp = temp->next;
	obj = temp->content;
	obj->transform = scaling(0.5, 0.5, 0.5);

	t_ray r = create_ray(create_vector(0,0,1), create_point(0,0,-5));
	xs = intersect_world(minirt, r);
	print_xs(&xs);
}

//run this test with
// sp 	     	0,0,0	        2 		 204,255,153
// in .rt file for example
/*void	test_prepare_computations_outside(t_minirt *minirt, char **av)
{
	(void)av;
	t_ray	r = create_ray(create_vector(0,0,1), create_point(0,0,-5));

	t_list	*temp = minirt->world->objects;
	t_scene_obj *obj = (t_scene_obj *)temp->content;
	t_i		i1 = intersection(4, obj); //hard set t value = 4
	obj->transform = identity();
	t_comps comps = prepare_computations(minirt, i1, r);
	print_comps(&comps);
}*/

//run this test with
// sp 	     	0,0,0	        2 		 204,255,153
// in .rt file for example
/*void	test_prepare_computations_inside(t_minirt *minirt, char **av)
{
	(void)av;
	t_ray	r = create_ray(create_vector(0,0,1), create_point(0,0,0));

	t_list	*temp = minirt->world->objects;
	t_scene_obj *obj = (t_scene_obj *)temp->content;
	t_i		i1 = intersection(1, obj); //hard set t value = 1
	obj->transform = identity();
	t_comps comps = prepare_computations(minirt, i1, r);
	print_comps(&comps);
}*/

/*void	test_shading_an_intersection(t_minirt *minirt, char **av)
{
	t_ray	r = create_ray(create_vector(0,0,1), create_point(0,0,-5));
	minirt->world->lig_s = init_point_light(create_point(-10, -10, -10), color(1, 1, 1), 1);

	t_list	*temp = minirt->world->objects;
	t_scene_obj *obj = (t_scene_obj *)temp->content;
	t_i		i1 = intersection(4, obj); //hard set t value
	obj->transform = identity();
	obj->mat = init_material();
	obj->mat.ambient = 0.1;
	obj->mat.diffuse = 0.7;
	obj->mat.specular = 0.2;
	obj->mat.col.r = 0.8;
	obj->mat.col.g = 1;
	obj->mat.col.b = 0.6;
	t_comps comps = prepare_computations(minirt, i1, r);
	fun_test_parsed_output(av, minirt->world);
	// print_comps(&comps);
	bool in_shadow = 0;
	t_color color = shade_hit(minirt->world, comps, in_shadow);
	print_colour(color);
}*/

/*void	test_shading_an_intersection_from_inside(t_minirt *minirt, char **av)
{
	minirt->world->lig_s = init_point_light(create_point(0, -0.25, 0), color(1, 1, 1), 1);
	t_ray	r = create_ray(create_vector(0,0,1), create_point(0,0,0));

	t_list	*temp = minirt->world->objects;
	t_scene_obj *obj = (t_scene_obj *)temp->content;
	t_i		i1 = intersection(0.5, obj); //hard set t value
	obj->transform = scaling(0.5, 0.5, 0.5);
	obj->mat = init_material();
	obj->mat.ambient = 0.1;
	obj->mat.diffuse = 0.9;
	obj->mat.specular = 0.9;
	obj->mat.col.r = 1;
	obj->mat.col.g = 1;
	obj->mat.col.b = 1;
	t_comps comps = prepare_computations(minirt, i1, r);
	fun_test_parsed_output(av, minirt->world);
	// print_comps(&comps);
	bool in_shadow = 0;
	t_color color = shade_hit(minirt->world, comps, in_shadow);
	print_colour(color);
}*/

// test this with 2 sphere objects, for example sp.rt
void	test_ray_misses_obj(t_minirt *minirt)
{
	minirt->world->lig_s = init_point_light(create_point(-10, -10, -10), color(1, 1, 1), 1);
	t_ray	r = create_ray(create_vector(0, 1, 0), create_point(0, 0, -5));

	t_list	*temp = minirt->world->objects;
	t_scene_obj *obj = (t_scene_obj *)temp->content;

	obj->transform = identity();
	obj->mat = init_material(minirt->world->amb_s.ratio);
	obj->mat.ambient = 0.1;
	obj->mat.diffuse = 0.7;
	obj->mat.specular = 0.2;
	obj->mat.col.r = 0.8;
	obj->mat.col.g = 1;
	obj->mat.col.b = 0.6;

	temp = temp->next;
	obj = (t_scene_obj *)temp->content;
	obj->transform = scaling(0.5, 0.5, 0.5);
	obj->mat = init_material(minirt->world->amb_s.ratio);
	obj->mat.ambient = 0.1;
	obj->mat.diffuse = 0.9;
	obj->mat.specular = 0.9;
	obj->mat.col.r = 1;
	obj->mat.col.g = 1;
	obj->mat.col.b = 1;

	t_color color = color_at(minirt, r);
	print_colour(color);
}

void	test_ray_hits_obj(t_minirt *minirt)
{
	minirt->world->lig_s = init_point_light(create_point(-10, -10, -10), color(1, 1, 1), 1);
	t_ray	r = create_ray(create_vector(0, 0, 1), create_point(0, 0, -5));

	t_list	*temp = minirt->world->objects;
	t_scene_obj *obj = (t_scene_obj *)temp->content;

	obj->transform = identity();
	obj->mat = init_material(minirt->world->amb_s.ratio);
	obj->mat.ambient = 0.1;
	obj->mat.diffuse = 0.7;
	obj->mat.specular = 0.2;
	obj->mat.col.r = 0.8;
	obj->mat.col.g = 1;
	obj->mat.col.b = 0.6;

	temp = temp->next;
	obj = (t_scene_obj *)temp->content;
	obj->transform = scaling(0.5, 0.5, 0.5);
	obj->mat = init_material(minirt->world->amb_s.ratio);
	obj->mat.ambient = 0.1;
	obj->mat.diffuse = 0.9;
	obj->mat.specular = 0.9;
	obj->mat.col.r = 1;
	obj->mat.col.g = 1;
	obj->mat.col.b = 1;

	t_color color = color_at(minirt, r);
	print_colour(color);
}

void	test_intersection_behind_ray(t_minirt *minirt)
{
	minirt->world->lig_s = init_point_light(create_point(-10, -10, -10), color(1, 1, 1), 1);
	t_ray	r = create_ray(create_vector(0, 0, -1), create_point(0, 0, 0.75));

	t_list	*temp = minirt->world->objects;
	t_scene_obj *obj = (t_scene_obj *)temp->content;

	obj->transform = identity();
	obj->mat = init_material(minirt->world->amb_s.ratio);
	obj->mat.ambient = 1;
	obj->mat.diffuse = 0.7;
	obj->mat.specular = 0.2;
	obj->mat.col.r = 0.8;
	obj->mat.col.g = 1;
	obj->mat.col.b = 0.6;

	temp = temp->next;
	obj = (t_scene_obj *)temp->content;
	obj->transform = scaling(0.5, 0.5, 0.5);
	obj->mat = init_material(minirt->world->amb_s.ratio);
	obj->mat.ambient = 1;
	obj->mat.diffuse = 0.9;
	obj->mat.specular = 0.9;
	obj->mat.col.r = 0.33;
	obj->mat.col.g = 0.22;
	obj->mat.col.b = 0.11;

	t_color color = color_at(minirt, r);
	printf("material color:\n");
	print_colour(obj->mat.col);
	printf("color_at color:\n");
	print_colour(color);
}

void	test_orientation(void)
{
	printf("default orientation:\n");
	t_tuple	from = create_point(0, 0, 0);
	t_tuple	to = create_point(0, 0, -1);
	t_tuple	up = create_vector(0, 1, 0);
	t_matrix4 t = view_transform(from, to, up);
	print_matrix(t, "identity expected: ", 4);
	printf("\n\n");

	printf("looking pos z:\n");
	from = create_point(0, 0, 0);
	to = create_point(0, 0, 1);
	up = create_vector(0, 1, 0);
	t = view_transform(from, to, up);
	print_matrix(t, "result matrix t", 4);
	t = scaling(-1, 1, -1);
	print_matrix(t, "previous should match", 4);
	printf("\n\n");

	printf("move the world:\n");
	from = create_point(0, 0, 8);
	to = create_point(0, 0, 0);
	up = create_vector(0, 1, 0);
	t = view_transform(from, to, up);
	print_matrix(t, "result matrix t", 4);
	t = translation(0, 0, -8);
	print_matrix(t, "previous should match", 4);

	printf("arbitrary view transformation:\n");
	from = create_point(1, 3, 2);
	to = create_point(4, -2, 8);
	up = create_vector(1, 1, 0);
	t = view_transform(from, to, up);
	print_matrix(t, "result matrix t", 4);
	/*
	Then t is the following 4x4 matrix:
	| -0.50709 | 0.50709 |  0.67612 | -2.36643 |
	|  0.76772 | 0.60609 |  0.12122 | -2.82843 |
	| -0.35857 | 0.59761 | -0.71714 |  0.00000 |
	|  0.00000 | 0.00000 |  0.00000 |  1.00000 |
	*/
}

//test with width 201 and height 101
void	test_camera(t_minirt *minirt)
{
	init_camera(minirt);
	print_camera(&minirt->world->cam_s);
}

//test with sp1.rt
void	test_ray_for_pixel(t_minirt *minirt)
{
	printf("test center of canvas\n");
	init_camera(minirt);
	t_ray r = ray_for_pixel(minirt, &minirt->world->cam_s, 100, 50);
	print_ray(r);

	printf("test corner of canvas\n");
	r = ray_for_pixel(minirt, &minirt->world->cam_s, 0, 0);
	print_ray(r);

	printf("test transformed camera\n");
	minirt->world->cam_s.transform = multiply_mtrx_by_mtrx(rotation_y(M_PI / 4), translation(0, -2, 5));
	r = ray_for_pixel(minirt, &minirt->world->cam_s, 100, 50);
	print_ray(r);
}

void	test_shape(t_minirt *minirt)
{
	t_scene_obj object;
	t_matrix4 trans;
	// t_material mat;

	/*//Test 1, set test object's trans to ident
	object.transform = identity(minirt);
	print_matrix(object.transform, "Test 1. Transform set to identity", 4);

	//Test 2, set transform to a translation
	trans = translation(minirt, 2, 3, 4);
	set_transform(&object, trans);
	print_matrix(object.transform, "Test 2. Transform set to translate 2,3,4", 4);

	//Test 3, assign material
	mat = init_material();
	object.mat = mat;
	printf("Test 3. Test object mat: amb: %f, diff: %f, spec: %f, shin: %f\nColours:\n", object.mat.ambient, object.mat.diffuse, object.mat.specular, object.mat.shininess);
	print_colour(object.mat.col);*/

	//Test 4, normal on translated shape
	object.type = SPHERE;
	trans = translation(0, 1, 0);
	set_transform(&object, trans);
	//t_tuple norm = normal_at(&object, create_point(0, 1.70711, -0.70711));
	printf("Test 4. Normal of translated 0,1,0\n");
	//print_tuple(norm);

	//Test 5, normal on transformed shape
	trans = multiply_mtrx_by_mtrx(scaling(1, 0.5, 1), rotation_z(0.62832));
	set_transform(&object, trans);
	//norm = normal_at(&object, create_point(0, 0.70711, -0.70711));
	printf("Test 5. Normal of transformed sca-rot\n");
	//print_tuple(norm);
}

void	test_intersect_generic(void)
{
	t_xs *xs = NULL;
	t_ray ray = create_ray(create_vector(0,0,1), create_point(0,0,-5));
	t_scene_obj obj;
	set_transform(&obj, scaling(2, 2, 2));
	xs = intersect(NULL, &obj, ray, xs);
	(void)xs;
	printf("Scaled 2,2,2 saved_ray\n");
	print_ray(obj.saved_ray);

	t_ray ray2 = create_ray(create_vector(0,0,1), create_point(0,0,-5));
	set_transform(&obj, translation(5, 0, 0));
	t_xs *xs2 = intersect(NULL, &obj, ray2, xs);
	(void)xs2;
	printf("Translated 5,0,0 saved_ray\n");
	print_ray(obj.saved_ray);
}

/*void	test_plane_normal(t_minirt *minirt)
{
	printf("Scenario: The normal of a plane is constant everywhere\n");
	t_scene_obj	p = plane(minirt);

	t_tuple	n1 = normal_at(minirt,&p, create_point(0, 0, 0));
	printf("Normal at point 0,0,0\n");
	print_tuple(n1);

	t_tuple	n2 = normal_at(minirt,&p, create_point(10, 0, -10));
	printf("Normal at point 10,0,-10\n");
	print_tuple(n2);

	t_tuple	n3 = normal_at(minirt,&p, create_point(-5, 0, 150));
	printf("Normal at point -5,0,150\n");
	print_tuple(n3);
}*/

/*void	test_plane_intersect(t_minirt *minirt)
{
	t_xs *xs1 = NULL;
	printf("Scenario: Intersect with a ray parallel to the plane\n");
	t_scene_obj	p = plane(minirt);
	t_ray r1 = create_ray(create_vector(0,0,1), create_point(0,10,0));
	intersect(minirt, &p, r1, xs1);
	printf("t_xs count: %u\n", xs1->count);

	t_xs *xs2 = NULL;
	printf("Scenario: Intersect with a coplanar ray\n");
	t_ray r2 = create_ray(create_vector(0,0,0), create_point(0,0,1));
	intersect(minirt, &p, r2, xs2);
	printf("t_xs count: %u\n", xs2->count);

	t_xs *xs3 = NULL;
	printf("Scenario: A ray intersecting a plane from above\n");
	t_ray r3 = create_ray(create_vector(0,1,0), create_point(0,-1,0));
	intersect(minirt, &p, r3, xs3);
	printf("t_xs count: %u\n", xs3->count);
	printf("t_xs xs1: %f, xs2: %f\n", xs3->t[0], xs3->t[1]);
	printf("t_xs obj: %d\n", ((t_scene_obj *)xs3->object)->type);

	t_xs *xs4 = NULL;
	printf("Scenario: A ray intersecting a plane from below\n");
	t_ray r4 = create_ray(create_vector(0,-1,0), create_point(0,1,0));
	intersect(minirt, &p, r4, xs4);
	printf("t_xs count: %u\n", xs4->count);
	printf("t_xs xs1: %f, xs2: %f\n", xs4->t[0], xs4->t[1]);
	printf("t_xs obj: %d\n", ((t_scene_obj *)xs4->object)->type);

	//((t_scene_obj *)temp->content)
}*/


void	test_render_world(t_minirt *minirt)
{
	minirt->world->lig_s = init_point_light(create_point(-10, -10, -10), color(1, 1, 1), 1);

	t_list	*temp = minirt->world->objects;
	t_scene_obj *obj = (t_scene_obj *)temp->content;

	obj->transform = identity();
	obj->mat = init_material(minirt->world->amb_s.ratio);
	obj->mat.ambient = 0.1;
	obj->mat.diffuse = 0.7;
	obj->mat.specular = 0.2;
	obj->mat.col.r = 0.8;
	obj->mat.col.g = 1;
	obj->mat.col.b = 0.6;

	temp = temp->next;
	obj = (t_scene_obj *)temp->content;
	obj->transform = scaling(0.5, 0.5, 0.5);
	obj->mat = init_material(minirt->world->amb_s.ratio);
	obj->mat.ambient = 0.1;
	obj->mat.diffuse = 0.9;
	obj->mat.specular = 0.9;
	obj->mat.col.r = 1;
	obj->mat.col.g = 1;
	obj->mat.col.b = 1;

	init_camera(minirt); //test with w:11  h:11, Pi/2
	t_tuple	from = create_point(0, 0, -5);
	t_tuple	to = create_point(0, 0, 0);
	t_tuple	up = create_vector(0, 1, 0);
	minirt->world->cam_s.transform = view_transform(from, to, up);
	// print_matrix(minirt->world->cam_s.transform, "camera", 4);
	set_pixel_color(minirt);
}

void	test_cylinder_rotation(void)
{
	t_scene_obj obj;
	obj.ox = 0;
	obj.oy = 0;
	obj.oz = 1;
	t_matrix4	m = cylinder_rotation(&obj);
	print_matrix(m, "cylinder rotation", 4);
	//expect
	// | -1 | 0 |  0 | 0 |
	// |  0 | 0 | -1 | 0 |
	// |  0 | 1 |  0 | 0 |
	// |  0 | 0 |  0 | 1 |
	obj.ox = -0.7071068;
	obj.oy = 0.5;
	obj.oz = 0.5;
	m = cylinder_rotation(&obj);
	print_matrix(m, "cylinder rotation", 4);
	//expect
	// | 0.6667  -0.7071   0.2357 |
	// | 0.7071   0.5     -0.5    |
	// | 0.2357   0.5      0.8333 |
}

void	test_cylinder_transformation(void)
{
	t_scene_obj obj;
	obj.dia = 1.5;
	obj.height = 3.2;
	obj.ox = -0.7071068;
	obj.oy = 0.5;
	obj.oz = 0.5;
	obj.cx = 3;
	obj.cy = 0.5;
	obj.cz = -4;
	t_matrix4 scale = scaling(obj.dia / 2.0, obj.height, obj.dia / 2.0);
	print_matrix(scale, "cylinder scale", 4);
	t_matrix4 rotate = cylinder_rotation(&obj);
	print_matrix(rotate, "cylinder rotation", 4);
	t_matrix4 translate = translation(obj.cx, obj.cy, obj.cz);
	print_matrix(translate, "cylinder translation", 4);
	t_matrix4 res = multiply_mtrx_by_mtrx(translate, multiply_mtrx_by_mtrx(rotate, scale));
	print_matrix(res, "cylinder transform", 4);
	//expect
	// [0.50000, -2.26275,  0.17678,  3.00000]
	// [0.53033,  1.60000, -0.37500,  0.50000]
	// [0.17678,  1.60000,  0.62500, -4.00000]
	// [0.00000,  0.00000,  0.00000,  1.00000]
}

void	test_plane_transformation(void)
{
	t_scene_obj obj;
	obj.ox = 0;
	obj.oy = 0;
	obj.oz = 1;
	t_matrix4	m = plane_rotation(&obj);
	print_matrix(m, "cylinder rotation", 4);
	//expect
	// | -1 | 0 |  0 | 0 |
	// |  0 | 0 | -1 | 0 |
	// |  0 | 1 |  0 | 0 |
	// |  0 | 0 |  0 | 1 |
	obj.ox = -0.7071068;
	obj.oy = 0.5;
	obj.oz = 0.5;
	m = plane_rotation(&obj);
	print_matrix(m, "cylinder rotation", 4);
	//expect
	// | 0.6667  -0.7071   0.2357 |
	// | 0.7071   0.5     -0.5    |
	// | 0.2357   0.5      0.8333 |
}


/*void	test_point_light_shadows(void)
{
	t_material mat = init_material();
	t_tuple	position = create_point(0, 0, 0);

	t_tuple eyev = create_vector(0, 0, -1);
	t_tuple	normalv = create_vector(0, 0, -1);
	t_light light;
	light.ori = create_point(0, 0, -10);
	light.col = color(1, 1, 1);
	light.ratio = 1;
	bool in_shadow = 1;
	t_color res = lighting(mat, light, position, eyev, normalv, in_shadow);
	printf("Result. Lighting with the eye between the light and the surface.\n");
	print_colour(res);

	t_tuple eyev2 = create_vector(0, 0.707107, -0.707107);
	res = lighting(mat, light, position, eyev2, normalv, in_shadow);
	printf("Result. Lighting with the eye between light and surface, eye offset 45°\n");
	print_colour(res);

	light.ori.y = 10;
	res = lighting(mat, light, position, eyev, normalv, in_shadow);
	printf("Result. Lighting with eye opposite surface, light offset 45°\n");
	print_colour(res);

	t_tuple eyev3 = create_vector(0, -0.707107, -0.707107);
	res = lighting(mat, light, position, eyev3, normalv, in_shadow);
	printf("Result. Lighting with eye in the path of the reflection vector\n");
	print_colour(res);

	light.ori.y = 0;
	light.ori.z = 10;
	res = lighting(mat, light, position, eyev, normalv, in_shadow);
	printf("Result. Lighting with the light behind the surface\n");
	print_colour(res);
}*/

void	test_shadows(t_minirt *minirt)
{
	t_list	*temp = minirt->world->objects;
	t_scene_obj *obj = (t_scene_obj *)temp->content;

	obj->transform = identity();
	obj->mat = init_material(minirt->world->amb_s.ratio);
	obj->mat.ambient = 1;
	obj->mat.diffuse = 0.7;
	obj->mat.specular = 0.2;

	temp = temp->next;
	obj = (t_scene_obj *)temp->content;
	obj->transform = scaling(0.5, 0.5, 0.5);
	obj->mat = init_material(minirt->world->amb_s.ratio);
	obj->mat.ambient = 1;
	obj->mat.diffuse = 0.9;
	obj->mat.specular = 0.9;

	bool sh = is_shadowed(minirt, create_point(0, 10, 0), obj);
	printf("expect 0, is shadowed: %i\n", sh);

	sh = is_shadowed(minirt, create_point(10, -10, 10), obj);
	printf("expect 1, is shadowed: %i\n", sh);

	sh = is_shadowed(minirt, create_point(-20, 20, -20), obj);
	printf("expect 0, is shadowed: %i\n", sh);

	sh = is_shadowed(minirt, create_point(-2, 2, -2), obj);
	printf("expect 0, is shadowed: %i\n", sh);
}

void	test_cylinder(t_minirt *minirt)
{
	t_scene_obj	cyl = cylinder(minirt);
	t_ray		r1;
	t_xs		*xs1 = calloc(1,sizeof(t_xs));

	printf("Test #1: A Ray Misses a Cylinder\n");
	printf("Test #1: | point(1, 0, 0) | vector(0, 1, 0) |\n");
	r1 = create_ray(normalize_tuple(create_vector(0,1,0)), create_point(1,0,0));
	init_xs(xs1);
	xs1 = intersect(NULL, &cyl, r1, xs1);
	printf("xs.count: %lu\n", xs1->count);

	printf("Test #1: | point(0, 0, 0) | vector(0, 1, 0) |\n");
	r1 = create_ray(normalize_tuple(create_vector(0,1,0)), create_point(0,0,0));
	init_xs(xs1);
	xs1 = intersect(NULL, &cyl, r1, xs1);
	printf("xs.count: %lu\n", xs1->count);

	printf("Test #1: | point(0, 0, -5) | vector(1, 1, 1) |\n");
	r1 = create_ray(normalize_tuple(create_vector(1,1,1)), create_point(0,0,-5));
	init_xs(xs1);
	xs1 = intersect(NULL, &cyl, r1, xs1);
	printf("xs.count: %lu\n", xs1->count);

	free(xs1);


	cyl.closed = true;
	printf("\nTest #2: A Ray Hits a Cylinder\n");
	printf("Test #2: | point(1, 0, -5) | vector(0, 0, 1) | 5 | 5 |\n");
	r1 = create_ray(normalize_tuple(create_vector(0,0,1)), create_point(1,0,-5));
	t_xs		*xs2 = calloc(1, sizeof(t_xs));
	init_xs(xs2);
	xs2 = intersect(NULL, &cyl, r1, xs2);
	printf("xs.count: %lu | t0: %f | t1: %f\n", xs2->count, xs2->t[0], xs2->t[1]);
	free(xs2);

	printf("Test #2: | point(0, 0, -5) | vector(0, 0, 1) | 4 | 6 |\n");
	r1 = create_ray(normalize_tuple(create_vector(0,0,1)), create_point(0,0,-5));
	t_xs		*xs3 = calloc(1, sizeof(t_xs));
	init_xs(xs3);
	xs3 = intersect(NULL, &cyl, r1, xs3);
	printf("xs.count: %lu | t0: %f | t1: %f\n", xs3->count, xs3->t[0], xs3->t[1]);
	free(xs3);

	printf("Test #2: | point(0.5, 0, -5) | vector(0.1, 1, 1) | 6.80798 | 7.08872 |\n");
	r1 = create_ray(normalize_tuple(create_vector(0.1,1,1)), create_point(0.5,0,-5));
	t_xs		*xs4 = calloc(1, sizeof(t_xs));
	init_xs(xs4);
	xs4 = intersect(NULL, &cyl, r1, xs4);
	printf("xs.count: %lu | t0: %f | t1: %f\n", xs4->count, xs4->t[0], xs4->t[1]);
	free(xs4);


	//printf("\nTest #3: Normal Vector on a Cylinder\n");
	//printf("Test #3: | point(1, 0, 0) | vector(1, 0, 0) |\n");
	//t_tuple	norm = normal_at_cylinder(create_point(1,0,0));
	//print_tuple(norm);

	//printf("Test #3: | point(0, 5, -1) | vector(0, 0, -1) |\n");
	//norm = normal_at_cylinder(create_point(0,5,-1));
	//print_tuple(norm);

	//printf("Test #3: | point(0, -2, 1) | vector(0, 0, 1) |\n");
	//norm = normal_at_cylinder(create_point(0,-2,1));
	//print_tuple(norm);

	//printf("Test #3: | point(-1, 1, 0) | vector(-1, 0, 0) |\n");
	//norm = normal_at_cylinder(create_point(-1,1,0));
	//print_tuple(norm);


	printf("\nTest #4: Minimum and Maximum Bounds\n");
	printf("Test #4: cyl.min: %f | cyl.max: %f\n", cyl.min, cyl.max);


	printf("\nTest #5: Truncated cylinder\n");
	t_scene_obj	trun = cylinder(minirt);
	trun.min = 1;
	trun.max = 2;
	printf("Test #5: | 1 | point(0, 1.5, 0) | vector(0.1, 1, 0) | 0 |\n");
	r1 = create_ray(normalize_tuple(create_vector(0.1,1,0)), create_point(0,1.5,0));
	t_xs		*xs5 = calloc(1, sizeof(t_xs));
	init_xs(xs5);
	xs5 = intersect(NULL, &trun, r1, xs5);
	printf("xs.count: %lu\n", xs5->count);
	free(xs5);

	printf("Test #5: | 2 | point(0, 3, -5) | vector(0, 0, 1) | 0 |\n");
	r1 = create_ray(normalize_tuple(create_vector(0,0,1)), create_point(0,3,-5));
	t_xs		*xs6 = calloc(1, sizeof(t_xs));
	init_xs(xs6);
	xs6 = intersect(NULL, &trun, r1, xs6);
	printf("xs.count: %lu\n", xs6->count);
	free(xs6);

	printf("Test #5: | 3 | point(0, 0, -5) | vector(0, 0, 1) | 0 |\n");
	r1 = create_ray(normalize_tuple(create_vector(0,0,1)), create_point(0,0,-5));
	t_xs		*xs7 = calloc(1,sizeof(t_xs));
	init_xs(xs7);
	xs7 = intersect(NULL, &trun, r1, xs7);
	printf("xs.count: %lu\n", xs7->count);
	free(xs7);

	printf("Test #5: | 4 | point(0, 2, -5) | vector(0, 0, 1) | 0 |\n");
	r1 = create_ray(normalize_tuple(create_vector(0,0,1)), create_point(0,2,-5));
	t_xs		*xs8 = calloc(1,sizeof(t_xs));
	init_xs(xs8);
	xs8 = intersect(NULL, &trun, r1, xs8);
	printf("xs.count: %lu\n", xs8->count);
	free(xs8);

	printf("Test #5: | 5 | point(0, 1, -5) | vector(0, 0, 1) | 0 |\n");
	r1 = create_ray(normalize_tuple(create_vector(0,0,1)), create_point(0,1,-5));
	t_xs		*xs9 = calloc(1,sizeof(t_xs));
	init_xs(xs9);
	xs9 = intersect(NULL, &trun, r1, xs9);
	printf("xs.count: %lu\n", xs9->count);
	free(xs9);

	printf("Test #5: | 6 | point(0, 1.5, -2) | vector(0, 0, 1) | 2 |\n");
	r1 = create_ray(normalize_tuple(create_vector(0,0,1)), create_point(0,1.5,-2));
	t_xs		*xs10 = calloc(1,sizeof(t_xs));
	init_xs(xs10);
	xs10 = intersect(NULL, &trun, r1, xs10);
	printf("xs.count: %lu\n", xs10->count);
	free(xs10);
}

void	test_cylinder2(t_minirt *minirt)
{
	t_scene_obj	cyl = cylinder(minirt);
	cyl.min = 1;
	cyl.max = 2;
	cyl.closed = true; //Is not necessary, all cylinders are capped in miniRT
	t_ray		r1;

	printf("\nTest #7: Intersecting a Cylinder’s End Caps\n");
	printf("| 1 | point(0, 3, 0) | vector(0, -1, 0) | 2 |\n");
	r1 = create_ray(normalize_tuple(create_vector(0,-1,0)), create_point(0,3,0));
	t_xs		*xs1 = calloc(1,sizeof(t_xs));
	init_xs(xs1);
	xs1 = intersect(NULL, &cyl, r1, xs1);
	printf("xs.count: %lu\n", xs1->count);
	free(xs1);

	printf("| 2 | point(0, 3, -2) | vector(0, -1, 2) | 2 |\n");
	r1 = create_ray(normalize_tuple(create_vector(0,-1,2)), create_point(0,3,-2));
	xs1 = calloc(1,sizeof(t_xs));
	init_xs(xs1);
	xs1 = intersect(NULL, &cyl, r1, xs1);
	printf("xs.count: %lu\n", xs1->count);
	free(xs1);

	printf("| 3 | point(0, 4, -2) | vector(0, -1, 1) | 2 |\n");
	r1 = create_ray(normalize_tuple(create_vector(0,-1,1)), create_point(0,4,-2));
	xs1 = calloc(1,sizeof(t_xs));
	init_xs(xs1);
	xs1 = intersect(NULL, &cyl, r1, xs1);
	printf("xs.count: %lu\n", xs1->count);
	free(xs1);

	printf("| 4 | point(0, 0, -2) | vector(0, 1, 2) | 2 |\n");
	r1 = create_ray(normalize_tuple(create_vector(0,1,2)), create_point(0,0,-2));
	xs1 = calloc(1,sizeof(t_xs));
	init_xs(xs1);
	xs1 = intersect(NULL, &cyl, r1, xs1);
	printf("xs.count: %lu\n", xs1->count);
	free(xs1);

	printf("| 5 | point(0, -1, -2) | vector(0, 1, 1) | 2 |\n");
	r1 = create_ray(normalize_tuple(create_vector(0,1,1)), create_point(0,-1,-2));
	xs1 = calloc(1,sizeof(t_xs));
	init_xs(xs1);
	xs1 = intersect(NULL, &cyl, r1, xs1);
	printf("xs.count: %lu\n", xs1->count);
	free(xs1);


	printf("\nTest #3 redo: Normal Vector on a Cylinder (curved)\n");
	printf("Test #3: | point(1, 0, 0) | vector(1, 0, 0) |\n");
	t_tuple	norm = normal_at_cylinder(&cyl, create_point(1,0,0));
	print_tuple(norm);

	printf("Test #3: | point(0, 5, -1) | vector(0, 0, -1) |\n");
	norm = normal_at_cylinder(&cyl, create_point(0,5,-1));
	print_tuple(norm);

	printf("Test #3: | point(0, -2, 1) | vector(0, 0, 1) |\n");
	norm = normal_at_cylinder(&cyl, create_point(0,-2,1));
	print_tuple(norm);

	printf("Test #3: | point(-1, 1, 0) | vector(-1, 0, 0) |\n");
	norm = normal_at_cylinder(&cyl, create_point(-1,1,0));
	print_tuple(norm);


	printf("\nTest #8: Computing the Normal Vector at the End Caps\n");
	printf("| point(0, 1, 0) | vector(0, -1, 0) |\n");
	norm = normal_at_cylinder(&cyl, create_point(0,1,0));
	print_tuple(norm);

	printf("| point(0.5, 1, 0) | vector(0, -1, 0) |\n");
	norm = normal_at_cylinder(&cyl, create_point(0.5,1,0));
	print_tuple(norm);

	printf("| point(0, 1, 0.5) | vector(0, -1, 0) |\n");
	norm = normal_at_cylinder(&cyl, create_point(0,1,0.5));
	print_tuple(norm);

	printf("| point(0, 2, 0) | vector(0, 1, 0) |\n");
	norm = normal_at_cylinder(&cyl, create_point(0,2,0));
	print_tuple(norm);

	printf("| point(0.5, 2, 0) | vector(0, 1, 0) |\n");
	norm = normal_at_cylinder(&cyl, create_point(0.5,2,0));
	print_tuple(norm);

	printf("| point(0, 2, 0.5) | vector(0, 1, 0) |\n");
	norm = normal_at_cylinder(&cyl, create_point(0,2,0.5));
	print_tuple(norm);
}
