#include "minirt.h"

bool matrix_equals(float **m, float expected[4][4]) {
    for (size_t i = 0; i < 4; ++i)
        for (size_t j = 0; j < 4; ++j)
            if (!is_equal(m[i][j], expected[i][j]))
                return false;
    return true;
}


void test_matrix_alloc(t_minirt *minirt)
{
	float **m = matrix_alloc(minirt, 3);  // Allocating 3x3 matrix

	// Check allocation success
	if (m && m[0] && m[1] && m[2])
	{
		printf("✅ Matrix Allocation Test Passed\n");
	}
	else
	{
		printf("❌ Matrix Allocation Test Failed\n");
	}

	// Clean up the allocated memory
}

void test_matrix_equality(t_minirt *minirt)
{
	(void)minirt;
	// Define two 3x3 matrices
	float *m1[3] = {
		(float[]){1, 2, 3},
		(float[]){4, 5, 6},
		(float[]){7, 8, 9}
	};

	float *m2[3] = {
		(float[]){1, 2, 3},
		(float[]){4, 5, 6},
		(float[]){7, 8, 9}
	};

	float *m3[3] = {
		(float[]){1, 2, 3},
		(float[]){4, 5, 7},
		(float[]){7, 8, 9}
	};

	// Test equality
	if (equality_matrix(m1, m2, 3))
		printf("✅ Matrix Equality Test Passed (Equal Matrices)\n");
	else
		printf("❌ Matrix Equality Test Failed (Equal Matrices)\n");

	if (!equality_matrix(m1, m3, 3))
		printf("✅ Matrix Equality Test Passed (Unequal Matrices)\n");
	else
		printf("❌ Matrix Equality Test Failed (Unequal Matrices)\n");
}

void test_matrix_multiplication(t_minirt *minirt)
{
	float *m1[3] = {
		(float[]){1, 2, 3},
		(float[]){4, 5, 6},
		(float[]){7, 8, 9}
	};

	float *m2[3] = {
		(float[]){9, 8, 7},
		(float[]){6, 5, 4},
		(float[]){3, 2, 1}
	};

	// Multiply m1 and m2
	float **result = multiply_mtrx_by_mtrx(minirt, m1, m2, 3);

	// Check if result matches expected values (manually calculated result)
	if (is_equal(result[0][0], 30) && is_equal(result[0][1], 24) && is_equal(result[0][2], 18) &&
		is_equal(result[1][0], 84) && is_equal(result[1][1], 69) && is_equal(result[1][2], 54) &&
		is_equal(result[2][0], 138) && is_equal(result[2][1], 114) && is_equal(result[2][2], 90))
	{
		printf("✅ Matrix Multiplication Test Passed\n");
	}
	else
	{
		printf("❌ Matrix Multiplication Test Failed\n");
	}

	// Clean up the result matrix
}

void test_matrix_transposition(t_minirt *minirt)
{
	float *m1[3] = {
		(float[]){1, 2, 3},
		(float[]){4, 5, 6},
		(float[]){7, 8, 9}
	};

	// Get the transpose of m1
	float **transposed = transpose_matrix(minirt, m1, 3);

	// Check if transposed matrix is correct
	if (is_equal(transposed[0][0], 1) && is_equal(transposed[0][1], 4) && is_equal(transposed[0][2], 7) &&
		is_equal(transposed[1][0], 2) && is_equal(transposed[1][1], 5) && is_equal(transposed[1][2], 8) &&
		is_equal(transposed[2][0], 3) && is_equal(transposed[2][1], 6) && is_equal(transposed[2][2], 9))
	{
		printf("✅ Matrix Transposition Test Passed\n");
	}
	else
	{
		printf("❌ Matrix Transposition Test Failed\n");
	}
}

void test_submatrix(t_minirt *minirt)
{
	float *m1[3] = {
		(float[]){1, 2, 3},
		(float[]){4, 5, 6},
		(float[]){7, 8, 9}
	};

	// Get a submatrix by removing row 1 and column 1 (indexing starts from 0)
	t_matrix_ctx ctx = { minirt, m1, 3 };
	float **submatrix = sub_matrix(&ctx, 1, 1);

	// Check if submatrix matches expected values
	if (is_equal(submatrix[0][0], 1) && is_equal(submatrix[0][1], 3) &&
		is_equal(submatrix[1][0], 7) && is_equal(submatrix[1][1], 9))
	{
		printf("✅ Submatrix Test Passed\n");
	}
	else
	{
		printf("❌ Submatrix Test Failed\n");
	}

}

void test_minor_matrix(t_minirt *minirt)
{
	float *m1[3] = {
		(float[]){1, 2, 3},
		(float[]){4, 5, 6},
		(float[]){7, 8, 9}
	};

	// Calculate minor for element at row 0, column 0
	t_matrix_ctx ctx = { minirt, m1, 3 };
	float minor = minor_matrix(&ctx, 0, 0);

	// Check if the minor is correct (determinant of the submatrix)
	if (is_equal(minor, -3))
	{
		printf("✅ Minor Matrix Test Passed\n");
	}
	else
	{
		printf("❌ Minor Matrix Test Failed\n");
	}
}

void test_cofactor_matrix(t_minirt *minirt)
{
	float *m1[3] = {
		(float[]){1, 2, 3},
		(float[]){4, 5, 6},
		(float[]){7, 8, 9}
	};

	// Calculate cofactor for element at row 0, column 0
	t_matrix_ctx ctx = { minirt, m1, 3 };
	float cofactor = cofactor_matrix(&ctx, 0, 0);

	// Check if the cofactor is correct (should be the same as the minor for a 3x3)
	if (is_equal(cofactor, -3))
	{
		printf("✅ Cofactor Matrix Test Passed\n");
	}
	else
	{
		printf("❌ Cofactor Matrix Test Failed\n");
	}
}

void test_determinant_matrix(t_minirt *minirt)
{
	float *m1[3] = {
		(float[]){1, 2, 3},
		(float[]){4, 5, 6},
		(float[]){7, 8, 9}
	};

	// Calculate determinant
	float det = determinant_matrix(minirt, m1, 3);

	// Check if determinant is correct
	if (is_equal(det, 0))
	{
		printf("✅ Determinant Matrix Test Passed\n");
	}
	else
	{
		printf("❌ Cofactor Matrix Test Failed\n");
	}
}

void	unit_tests_3x3(t_minirt *minirt)
{
	test_matrix_alloc(minirt);
	test_matrix_equality(minirt);
	test_matrix_transposition(minirt);
	test_submatrix(minirt);
	test_minor_matrix(minirt);
	test_cofactor_matrix(minirt);
	test_determinant_matrix(minirt);
}

void test_matrix_alloc_4x4(t_minirt *minirt)
{
	float **m = matrix_alloc(minirt, 4);
	if (m && m[0] && m[1] && m[2] && m[3])
		printf("✅ 4x4 Matrix Allocation Test Passed\n");
	else
		printf("❌ 4x4 Matrix Allocation Test Failed\n");
}


void test_matrix_equality_4x4(t_minirt *minirt)
{
	(void)minirt;

	float *m1[4] = {
		(float[]){1, 2, 3, 4},
		(float[]){5, 6, 7, 8},
		(float[]){9, 10, 11, 12},
		(float[]){13, 14, 15, 16}
	};

	float *m2[4] = {
		(float[]){1, 2, 3, 4},
		(float[]){5, 6, 7, 8},
		(float[]){9, 10, 11, 12},
		(float[]){13, 14, 15, 16}
	};

	float *m3[4] = {
		(float[]){1, 2, 3, 4},
		(float[]){5, 6, 7, 8},
		(float[]){9, 10, 11, 12},
		(float[]){13, 14, 15, 17}
	};

	if (equality_matrix(m1, m2, 4))
		printf("✅ 4x4 Matrix Equality Test Passed (Equal Matrices)\n");
	else
		printf("❌ 4x4 Matrix Equality Test Failed (Equal Matrices)\n");

	if (!equality_matrix(m1, m3, 4))
		printf("✅ 4x4 Matrix Equality Test Passed (Unequal Matrices)\n");
	else
		printf("❌ 4x4 Matrix Equality Test Failed (Unequal Matrices)\n");
}


void test_matrix_multiplication_4x4(t_minirt *minirt)
{
	float *m1[4] = {
		(float[]){1, 2, 3, 4},
		(float[]){5, 6, 7, 8},
		(float[]){9, 8, 7, 6},
		(float[]){5, 4, 3, 2}
	};

	float *m2[4] = {
		(float[]){1, 2, 1, 2},
		(float[]){0, 1, 0, 2},
		(float[]){1, 2, 1, 2},
		(float[]){0, 2, 0, 2}
	};

	// Expected result calculated by hand or with a tool
	float expected[4][4] = {
		{ 4, 18, 4, 20 },
		{ 12, 46, 12, 52 },
		{ 16, 52, 16, 60 },
		{ 8, 24, 8, 28 }
	};

	float **result = multiply_mtrx_by_mtrx(minirt, m1, m2, 4);

	bool pass = true;
	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 4; ++j)
			if (!is_equal(result[i][j], expected[i][j]))
				pass = false;

	if (pass)
		printf("✅ 4x4 Matrix Multiplication Test Passed\n");
	else
		printf("❌ 4x4 Matrix Multiplication Test Failed\n");
}


void test_matrix_transposition_4x4(t_minirt *minirt)
{
	float *m1[4] = {
		(float[]){0, 9, 3, 0},
		(float[]){9, 8, 0, 8},
		(float[]){1, 8, 5, 3},
		(float[]){0, 0, 5, 8}
	};

	float expected[4][4] = {
		{0, 9, 1, 0},
		{9, 8, 8, 0},
		{3, 0, 5, 5},
		{0, 8, 3, 8}
	};

	float **transposed = transpose_matrix(minirt, m1, 4);

	bool pass = true;
	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 4; ++j)
			if (!is_equal(transposed[i][j], expected[i][j]))
				pass = false;

	if (pass)
		printf("✅ 4x4 Matrix Transposition Test Passed\n");
	else
		printf("❌ 4x4 Matrix Transposition Test Failed\n");
}


void test_submatrix_4x4(t_minirt *minirt)
{
	float *m1[4] = {
		(float[]){-6, 1, 1, 6},
		(float[]){-8, 5, 8, 6},
		(float[]){-1, 0, 8, 2},
		(float[]){-7, 1, -1, 1}
	};

	// Remove row 2 and col 1
	t_matrix_ctx ctx = { minirt, m1, 4 };
	float **submatrix = sub_matrix(&ctx, 2, 1);

	float expected[3][3] = {
		{-6, 1, 6},
		{-8, 8, 6},
		{-7, -1, 1}
	};

	bool pass = true;
	for (int i = 0; i < 3; ++i)
		for (int j = 0; j < 3; ++j)
			if (!is_equal(submatrix[i][j], expected[i][j]))
				pass = false;

	if (pass)
		printf("✅ 4x4 Submatrix Test Passed\n");
	else
		printf("❌ 4x4 Submatrix Test Failed\n");
}


void test_minor_matrix_4x4(t_minirt *minirt)
{
	float *m1[4] = {
		(float[]){3, 5, 0, 2},
		(float[]){2, -1, -7, 1},
		(float[]){6, -1, 5, 0},
		(float[]){-4, -7, 0, 8}
	};

	t_matrix_ctx ctx = { minirt, m1, 4 };
	float minor = minor_matrix(&ctx, 1, 0);

	// Precomputed expected minor for (1,0)
	float expected = 270;

	if (is_equal(minor, expected))
		printf("✅ 4x4 Minor Matrix Test Passed\n");
	else
		printf("❌ 4x4 Minor Matrix Test Failed (Expected %.1f, got %.1f)\n", expected, minor);
}


void test_cofactor_matrix_4x4(t_minirt *minirt)
{
	float *m1[4] = {
		(float[]){3, 5, 0, 2},
		(float[]){2, -1, -7, 1},
		(float[]){6, -1, 5, 0},
		(float[]){-4, -7, 0, 8}
	};

	t_matrix_ctx ctx = { minirt, m1, 4 };
	float cofactor = cofactor_matrix(&ctx, 1, 0);

	// Precomputed expected cofactor for (1,0)
	float expected = -270;

	if (is_equal(cofactor, expected))
		printf("✅ 4x4 Cofactor Matrix Test Passed\n");
	else
		printf("❌ 4x4 Cofactor Matrix Test Failed (Expected %.1f, got %.1f)\n", expected, cofactor);
}


void test_determinant_matrix_4x4(t_minirt *minirt)
{
	float *m1[4] = {
		(float[]){-2, -8, 3, 5},
		(float[]){-3, 1, 7, 3},
		(float[]){1, 2, -9, 6},
		(float[]){-6, 7, 7, -9}
	};

	float det = determinant_matrix(minirt, m1, 4);

	float expected = -4071;

	if (is_equal(det, expected))
		printf("✅ 4x4 Determinant Matrix Test Passed\n");
	else
		printf("❌ 4x4 Determinant Matrix Test Failed (Expected %.1f, got %.1f)\n", expected, det);
}


void unit_tests_4x4(t_minirt *minirt)
{
	test_matrix_alloc_4x4(minirt);
	test_matrix_equality_4x4(minirt);
	test_matrix_multiplication_4x4(minirt);
	test_matrix_transposition_4x4(minirt);
	test_submatrix_4x4(minirt);
	test_minor_matrix_4x4(minirt);
	test_cofactor_matrix_4x4(minirt);
	test_determinant_matrix_4x4(minirt);
}


void	unit_tests_2x2(void)
{
	t_minirt	minirt;
	init_minirt(&minirt);

	printf("🔬 Starting matrix unit tests...\n");

	// Allocate and set up two 2x2 matrices
	float **m1 = matrix_alloc(&minirt, 2);
	float **m2 = matrix_alloc(&minirt, 2);

	m1[0][0] = 1; m1[0][1] = 2;
	m1[1][0] = 3; m1[1][1] = 4;

	m2[0][0] = 5; m2[0][1] = 6;
	m2[1][0] = 7; m2[1][1] = 8;

	// === Test Matrix Multiplication ===
	float **m3 = multiply_mtrx_by_mtrx(&minirt, m1, m2, 2);

	if (m3[0][0] == 19 && m3[0][1] == 22 && m3[1][0] == 43 && m3[1][1] == 50)
		printf("✅ Matrix multiplication test passed\n");
	else
		printf("❌ Matrix multiplication test failed\n");

	// === Test Transpose ===
	float **transposed = transpose_matrix(&minirt, m1, 2);
	if (transposed[0][1] == 3 && transposed[1][0] == 2)
		printf("✅ Transpose matrix test passed\n");
	else
		printf("❌ Transpose matrix test failed\n");

	// === Test Determinant ===
	float det = determinant_matrix(&minirt, m1, 2);
	if (is_equal(det, -2))
		printf("✅ Determinant test passed\n");
	else
		printf("❌ Determinant test failed (got %f)\n", det);

	// === Test Inverse Matrix ===
	float **inv = inverse_matrix(&minirt, m1, 2);
	if (inv &&
		is_equal(inv[0][0], -2.0) &&
		is_equal(inv[0][1], 1.0) &&
		is_equal(inv[1][0], 1.5) &&
		is_equal(inv[1][1], -0.5))
	{
		printf("✅ Inverse matrix test passed\n");
	}
	else
	{
		printf("❌ Inverse matrix test failed\n");
	}


	// === Test Tuple Multiplication ===
	t_tuple tup = {.x = 1, .y = 2, .z = 3, .w = 1};
	t_tuple result = multiply_mtrx_by_tuple(m1, tup, 2);
	if (is_equal(result.x, 5) && is_equal(result.y, 11))
		printf("✅ Multiply matrix by tuple test passed\n");
	else
		printf("❌ Multiply matrix by tuple test failed (got x=%.2f, y=%.2f)\n", result.x, result.y);

	// === Test Equality ===
	float **copy = matrix_alloc(&minirt, 2);
	copy[0][0] = 1; copy[0][1] = 2;
	copy[1][0] = 3; copy[1][1] = 4;

	if (equality_matrix(m1, copy, 2))
		printf("✅ Equality test passed\n");
	else
		printf("❌ Equality test failed\n");

	printf("🧪 Unit tests complete.\n");
}

void test_identity_matrix(t_minirt *minirt)
{
	float expected[4][4] = {
		{1,0,0,0},
		{0,1,0,0},
		{0,0,1,0},
		{0,0,0,1}
	};
	float **m = identity(minirt);
	if (matrix_equals(m, expected))
		printf("✅ Identity Matrix Test Passed\n");
	else
		printf("❌ Identity Matrix Test Failed\n");
}

void test_translation_matrix(t_minirt *minirt)
{
	int x = 3, y = 4, z = 5;
	float expected[4][4] = {
		{1,0,0,3},
		{0,1,0,4},
		{0,0,1,5},
		{0,0,0,1}
	};
	float **m = translation(minirt, x, y, z);
	if (matrix_equals(m, expected))
		printf("✅ Translation Matrix Test Passed\n");
	else
		printf("❌ Translation Matrix Test Failed\n");
}

void test_scaling_matrix(t_minirt *minirt)
{
	int x = 2, y = 3, z = 4;
	float expected[4][4] = {
		{2,0,0,0},
		{0,3,0,0},
		{0,0,4,0},
		{0,0,0,1}
	};
	float **m = scaling(minirt, x, y, z);
	if (matrix_equals(m, expected))
		printf("✅ Scaling Matrix Test Passed\n");
	else
		printf("❌ Scaling Matrix Test Failed\n");
}

void test_rotation_x_matrix(t_minirt *minirt)
{
	float theta = M_PI / 4; // 45 degrees
	float c = cos(theta), s = sin(theta);
	float expected[4][4] = {
		{1, 0, 0, 0},
		{0, c, -s, 0},
		{0, s,  c, 0},
		{0, 0, 0, 1}
	};
	float **m = rotation_x(minirt, theta);
	if (matrix_equals(m, expected))
		printf("✅ Rotation X Matrix Test Passed\n");
	else
		printf("❌ Rotation X Matrix Test Failed\n");
}

void test_rotation_y_matrix(t_minirt *minirt)
{
	float theta = M_PI / 4; // 45 degrees
	float c = cos(theta), s = sin(theta);
	float expected[4][4] = {
		{ c, 0, s, 0},
		{ 0, 1, 0, 0},
		{-s, 0, c, 0},
		{ 0, 0, 0, 1}
	};
	float **m = rotation_y(minirt, theta);
	if (matrix_equals(m, expected))
		printf("✅ Rotation Y Matrix Test Passed\n");
	else
		printf("❌ Rotation Y Matrix Test Failed\n");
}

void test_rotation_z_matrix(t_minirt *minirt)

{
	float theta = M_PI / 4; // 45 degrees
	float c = cos(theta), s = sin(theta);
	float expected[4][4] = {
		{c, -s, 0, 0},
		{s,  c, 0, 0},
		{0,  0, 1, 0},
		{0,  0, 0, 1}
	};
	float **m = rotation_z(minirt, theta);
	if (matrix_equals(m, expected))
		printf("✅ Rotation Z Matrix Test Passed\n");
	else
		printf("❌ Rotation Z Matrix Test Failed\n");
}

void unit_tests_transform_matrices(t_minirt *minirt)
{
	test_identity_matrix(minirt);
	test_translation_matrix(minirt);
	test_scaling_matrix(minirt);
	test_rotation_x_matrix(minirt);
	test_rotation_y_matrix(minirt);
	test_rotation_z_matrix(minirt);
}

void test_normal_at_sphere(t_minirt *m)
{
	printf("Testing normal at sphere point. \n");
	t_sphere	s1 = sphere(m);
	set_transform(&s1, translation(m, 0, 0, 0));
	print_matrix(s1.transform, "Initial s1 transform", 4);

	t_tuple	nor = normal_at_sphere(m, s1, create_point(1, 0 ,0));
	printf("world normal 1,0,0\n");
	print_tuple(nor);
	nor = normal_at_sphere(m, s1, create_point(0, 1 ,0));
	printf("world normal 0,1,0\n");
	print_tuple(nor);
	nor = normal_at_sphere(m, s1, create_point(0, 0 ,1));
	printf("world normal 0,0,1\n");
	print_tuple(nor);

	nor = normal_at_sphere(m, s1, create_point(0.57735, 0.57735, 0.57735));
	printf("world normal sqrt3/3\n");
	print_tuple(nor);

	set_transform(&s1, translation(m, 0, 1, 0));
	print_matrix(s1.transform, "Initial s1 transform", 4);

	nor = normal_at_sphere(m, s1, create_point(0, 1.70711, -0.70711));
	printf("world normal translated by 0,1,0\n");
	print_tuple(nor);

	float **sca = scaling(m, 1, 0.5, 1);
	print_matrix(sca, "sca", 4);
	float **rot = rotation_z(m, 0.62832);
	print_matrix(rot, "rot", 4);
	float **sca_rot = multiply_mtrx_by_mtrx(m, sca, rot, 4);
	print_matrix(sca_rot, "sca * rot", 4);
	set_transform(&s1, sca_rot);
	print_matrix(s1.transform, "Initial s1 transform", 4);
	nor = normal_at_sphere(m, s1, create_point(0, 0.70711, -0.70711));
	printf("world normal scaled and rotated\n");
	print_tuple(nor);
}

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


void test_point_light_material(void)
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
}

void	test_point_light_reflections(void)
{
	t_material mat = init_material();
	t_tuple	position = create_point(0, 0, 0);

	t_tuple eyev = create_vector(0, 0, -1);
	t_tuple	normalv = create_vector(0, 0, -1);
	t_light light;
	light.ori = create_point(0, 0, -10);
	light.col = color(1, 1, 1);
	light.ratio = 1;
	t_color res = lighting(mat, light, position, eyev, normalv);
	printf("Result. Lighting with the eye between the light and the surface.\n");
	print_colour(res);

	t_tuple eyev2 = create_vector(0, 0.707107, -0.707107);
	res = lighting(mat, light, position, eyev2, normalv);
	printf("Result. Lighting with the eye between light and surface, eye offset 45°\n");
	print_colour(res);

	light.ori.y = 10;
	res = lighting(mat, light, position, eyev, normalv);
	printf("Result. Lighting with eye opposite surface, light offset 45°\n");
	print_colour(res);

	t_tuple eyev3 = create_vector(0, -0.707107, -0.707107);
	res = lighting(mat, light, position, eyev3, normalv);
	printf("Result. Lighting with eye in the path of the reflection vector\n");
	print_colour(res);

	light.ori.y = 0;
	light.ori.z = 10;
	res = lighting(mat, light, position, eyev, normalv);
	printf("Result. Lighting with the light behind the surface\n");
	print_colour(res);
}
