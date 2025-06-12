// #include <stdio.h>
// #include <stdlib.h>
// #include <time.h>
// #include <string.h>
// #include <math.h>

// // compile this
// // gcc -O3 -march=native benchmark.c -lm -o benchmark
// // ./benchmark

// // Stack-based matrix types
// typedef struct {
// 	float m[4][4];
// } matrix4_t;

// typedef struct {
// 	float x, y, z, w;
// } tuple_t;

// // Heap-based matrix allocation
// float **allocate_matrix(int size) {
// 	float **m = malloc(sizeof(float*) * size);
// 	for (int i = 0; i < size; i++) {
// 		m[i] = malloc(sizeof(float) * size);
// 	}
// 	return m;
// }

// void free_matrix(float **m, int size) {
// 	for (int i = 0; i < size; i++) {
// 		free(m[i]);
// 	}
// 	free(m);
// }

// // Initialize matrices with some sample transform data
// void init_heap_matrix(float **m) {
// 	// Sample view transform-like matrix
// 	m[0][0] = 1.0f; m[0][1] = 0.0f; m[0][2] = 0.0f; m[0][3] = 0.0f;
// 	m[1][0] = 0.0f; m[1][1] = 1.0f; m[1][2] = 0.0f; m[1][3] = 0.0f;
// 	m[2][0] = 0.0f; m[2][1] = 0.0f; m[2][2] = 1.0f; m[2][3] = 5.0f;
// 	m[3][0] = 0.0f; m[3][1] = 0.0f; m[3][2] = 0.0f; m[3][3] = 1.0f;
// }

// void init_stack_matrix(matrix4_t *m) {
// 	m->m[0][0] = 1.0f; m->m[0][1] = 0.0f; m->m[0][2] = 0.0f; m->m[0][3] = 0.0f;
// 	m->m[1][0] = 0.0f; m->m[1][1] = 1.0f; m->m[1][2] = 0.0f; m->m[1][3] = 0.0f;
// 	m->m[2][0] = 0.0f; m->m[2][1] = 0.0f; m->m[2][2] = 1.0f; m->m[2][3] = 5.0f;
// 	m->m[3][0] = 0.0f; m->m[3][1] = 0.0f; m->m[3][2] = 0.0f; m->m[3][3] = 1.0f;
// }

// // Matrix multiplication with tuple (heap version)
// tuple_t multiply_heap(float **m, tuple_t t) {
// 	tuple_t result;
// 	result.x = m[0][0] * t.x + m[0][1] * t.y + m[0][2] * t.z + m[0][3] * t.w;
// 	result.y = m[1][0] * t.x + m[1][1] * t.y + m[1][2] * t.z + m[1][3] * t.w;
// 	result.z = m[2][0] * t.x + m[2][1] * t.y + m[2][2] * t.z + m[2][3] * t.w;
// 	result.w = m[3][0] * t.x + m[3][1] * t.y + m[3][2] * t.z + m[3][3] * t.w;
// 	return result;
// }

// // Matrix multiplication with tuple (stack version)
// tuple_t multiply_stack(matrix4_t m, tuple_t t) {
// 	tuple_t result;
// 	result.x = m.m[0][0] * t.x + m.m[0][1] * t.y + m.m[0][2] * t.z + m.m[0][3] * t.w;
// 	result.y = m.m[1][0] * t.x + m.m[1][1] * t.y + m.m[1][2] * t.z + m.m[1][3] * t.w;
// 	result.z = m.m[2][0] * t.x + m.m[2][1] * t.y + m.m[2][2] * t.z + m.m[2][3] * t.w;
// 	result.w = m.m[3][0] * t.x + m.m[3][1] * t.y + m.m[3][2] * t.z + m.m[3][3] * t.w;
// 	return result;
// }

// // Matrix inversion (simplified - just transpose for demo)
// void inverse_heap(float **result, float **m) {
// 	for (int i = 0; i < 4; i++) {
// 		for (int j = 0; j < 4; j++) {
// 			result[i][j] = m[j][i];
// 		}
// 	}
// }

// matrix4_t inverse_stack(matrix4_t m) {
// 	matrix4_t result;
// 	for (int i = 0; i < 4; i++) {
// 		for (int j = 0; j < 4; j++) {
// 			result.m[i][j] = m.m[j][i];
// 		}
// 	}
// 	return result;
// }

// // Get current time in nanoseconds
// long long get_time_ns() {
// 	struct timespec ts;
// 	clock_gettime(CLOCK_MONOTONIC, &ts);
// 	return ts.tv_sec * 1000000000LL + ts.tv_nsec;
// }

// // Test 1: Simple matrix-vector multiplication (like ray_for_pixel)
// void test_matrix_vector_multiply() {
// 	const int iterations = 1000000;
// 	printf("=== Test 1: Matrix-Vector Multiplication ===\n");
// 	printf("Iterations: %d\n\n", iterations);

// 	// Heap version
// 	float **heap_matrix = allocate_matrix(4);
// 	init_heap_matrix(heap_matrix);
// 	tuple_t test_tuple = {-0.909091f, 0.909091f, -1.0f, 1.0f};

// 	long long start = get_time_ns();
// 	tuple_t heap_result;
// 	for (int i = 0; i < iterations; i++) {
// 		heap_result = multiply_heap(heap_matrix, test_tuple);
// 		// Prevent optimization
// 		test_tuple.x += 0.000001f;
// 	}
// 	long long heap_time = get_time_ns() - start;

// 	// Stack version
// 	matrix4_t stack_matrix;
// 	init_stack_matrix(&stack_matrix);
// 	test_tuple = (tuple_t){-0.909091f, 0.909091f, -1.0f, 1.0f};

// 	start = get_time_ns();
// 	tuple_t stack_result;
// 	for (int i = 0; i < iterations; i++) {
// 		stack_result = multiply_stack(stack_matrix, test_tuple);
// 		// Prevent optimization
// 		test_tuple.x += 0.000001f;
// 	}
// 	long long stack_time = get_time_ns() - start;

// 	printf("Heap approach:  %lld ns (%lld ns per op)\n", heap_time, heap_time / iterations);
// 	printf("Stack approach: %lld ns (%lld ns per op)\n", stack_time, stack_time / iterations);
// 	printf("Speedup: %.2fx\n", (double)heap_time / stack_time);
// 	printf("Stack result: (%.6f, %.6f, %.6f, %.6f)\n",
// 		stack_result.x, stack_result.y, stack_result.z, stack_result.w);
// 	printf("Heap result:  (%.6f, %.6f, %.6f, %.6f)\n\n",
// 		heap_result.x, heap_result.y, heap_result.z, heap_result.w);

// 	free_matrix(heap_matrix, 4);
// }

// // Test 2: Ray transformation workload (inverse + multiply)
// void test_ray_transform_workload() {
// 	const int iterations = 500000;
// 	printf("=== Test 2: Ray Transform Workload ===\n");
// 	printf("Iterations: %d (inverse + 2 multiplications per iteration)\n\n", iterations);

// 	// Heap version
// 	float **heap_transform = allocate_matrix(4);
// 	float **heap_inverse = allocate_matrix(4);
// 	init_heap_matrix(heap_transform);

// 	tuple_t point = {-0.909091f, 0.909091f, -1.0f, 1.0f};
// 	tuple_t origin = {0.0f, 0.0f, 0.0f, 1.0f};

// 	long long start = get_time_ns();
// 	tuple_t heap_pixel, heap_origin, heap_direction;
// 	for (int i = 0; i < iterations; i++) {
// 		inverse_heap(heap_inverse, heap_transform);
// 		heap_pixel = multiply_heap(heap_inverse, point);
// 		heap_origin = multiply_heap(heap_inverse, origin);

// 		// Simple direction calculation (subtract + normalize)
// 		heap_direction.x = heap_pixel.x - heap_origin.x;
// 		heap_direction.y = heap_pixel.y - heap_origin.y;
// 		heap_direction.z = heap_pixel.z - heap_origin.z;
// 		float len = sqrtf(heap_direction.x * heap_direction.x +
// 						heap_direction.y * heap_direction.y +
// 						heap_direction.z * heap_direction.z);
// 		heap_direction.x /= len;
// 		heap_direction.y /= len;
// 		heap_direction.z /= len;

// 		// Prevent optimization
// 		point.x += 0.000001f;
// 	}
// 	long long heap_time = get_time_ns() - start;

// 	// Stack version
// 	matrix4_t stack_transform;
// 	init_stack_matrix(&stack_transform);
// 	point = (tuple_t){-0.909091f, 0.909091f, -1.0f, 1.0f};
// 	origin = (tuple_t){0.0f, 0.0f, 0.0f, 1.0f};

// 	start = get_time_ns();
// 	tuple_t stack_pixel, stack_origin, stack_direction;
// 	for (int i = 0; i < iterations; i++) {
// 		matrix4_t stack_inverse = inverse_stack(stack_transform);
// 		stack_pixel = multiply_stack(stack_inverse, point);
// 		stack_origin = multiply_stack(stack_inverse, origin);

// 		// Simple direction calculation (subtract + normalize)
// 		stack_direction.x = stack_pixel.x - stack_origin.x;
// 		stack_direction.y = stack_pixel.y - stack_origin.y;
// 		stack_direction.z = stack_pixel.z - stack_origin.z;
// 		float len = sqrtf(stack_direction.x * stack_direction.x +
// 						stack_direction.y * stack_direction.y +
// 						stack_direction.z * stack_direction.z);
// 		stack_direction.x /= len;
// 		stack_direction.y /= len;
// 		stack_direction.z /= len;

// 		// Prevent optimization
// 		point.x += 0.000001f;
// 	}
// 	long long stack_time = get_time_ns() - start;

// 	printf("Heap approach:  %lld ns (%lld ns per op)\n", heap_time, heap_time / iterations);
// 	printf("Stack approach: %lld ns (%lld ns per op)\n", stack_time, stack_time / iterations);
// 	printf("Speedup: %.2fx\n", (double)heap_time / stack_time);
// 	printf("Stack direction: (%.6f, %.6f, %.6f)\n",
// 		stack_direction.x, stack_direction.y, stack_direction.z);
// 	printf("Heap direction:  (%.6f, %.6f, %.6f)\n\n",
// 		heap_direction.x, heap_direction.y, heap_direction.z);

// 	free_matrix(heap_transform, 4);
// 	free_matrix(heap_inverse, 4);
// }

// int main() {
// 	printf("Matrix Performance Benchmark\n");
// 	printf("============================\n\n");

// 	test_matrix_vector_multiply();
// 	test_ray_transform_workload();

// 	printf("Note: Results may vary based on compiler optimizations and CPU cache.\n");
// 	printf("Compile with: gcc -O3 -march=native benchmark.c -lm -o benchmark\n");

// 	return 0;
// }
