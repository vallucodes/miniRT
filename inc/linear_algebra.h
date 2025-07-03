/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linear_algebra.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlopatin <vlopatin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 19:13:01 by vlopatin          #+#    #+#             */
/*   Updated: 2025/07/03 19:13:02 by vlopatin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LINEAR_ALGEBRA_H
# define LINEAR_ALGEBRA_H

typedef struct s_tuple
{
	float	x;
	float	y;
	float	z;
	float	w;
}	t_tuple;

typedef struct s_matrix4
{
	float	m[4][4];
}	t_matrix4;

typedef struct s_matrix3
{
	float	m[3][3];
}	t_matrix3;

typedef struct s_matrix2
{
	float	m[2][2];
}	t_matrix2;
typedef struct s_matrix_ctx
{
	t_matrix4	m;
	size_t		size;
}	t_matrix_ctx;

typedef union s_matrix_union
{
	t_matrix2	m2;
	t_matrix3	m3;
}	t_matrix_union;

typedef struct s_matrix_result
{
	t_matrix_union	m;
	size_t			size;
}	t_matrix_result;

//tuples operators
t_tuple		create_vector(float x, float y, float z);
t_tuple		create_point(float x, float y, float z);

//tuple operations
t_tuple		addition_tuples(t_tuple tuple1, t_tuple tuple2);
t_tuple		substraction_tuples(t_tuple tuple1, t_tuple tuple2);
t_tuple		negate_tuple(t_tuple tuple1);
t_tuple		scalar_multiply_tuple(t_tuple tuple1, float scalar);
t_tuple		scalar_divide_tuple(t_tuple tuple1, float scalar);
float		magnitude_tuple(t_tuple tuple);
t_tuple		normalize_tuple(t_tuple tuple);
float		dot_tuple(t_tuple tuple1, t_tuple tuple2);
t_tuple		cross_tuple(t_tuple tuple1, t_tuple tuple2);

//matrix operators
t_matrix4	identity(void);
t_matrix4	translation(float x, float y, float z);
t_matrix4	scaling(float x, float y, float z);
t_matrix4	rotation_x(float theta);
t_matrix4	rotation_y(float theta);
t_matrix4	rotation_z(float theta);

//matrix oprations
t_matrix4		multiply_mtrx_by_mtrx(t_matrix4 m, t_matrix4 m2);
t_tuple			multiply_mtrx_by_tuple(t_matrix4 m, t_tuple t1);
t_matrix4		transpose_matrix(t_matrix4 m);
float			determinant_matrix4(t_matrix4 m);
float			determinant_matrix3(t_matrix3 m);
float			determinant_matrix2(t_matrix2 m);
t_matrix_result	sub_matrix(t_matrix_ctx *ctx, size_t row, size_t col);
float			minor_matrix(t_matrix_ctx *ctx, int row, int col);
float			cofactor_matrix(t_matrix_ctx *ctx, int row, int col);
t_matrix4		inverse_matrix(t_matrix4 m, bool *success);
t_matrix4		scalar_multiply_matrix(t_matrix4 m, float scalar);
t_matrix4		addition_matrix(t_matrix4 a, t_matrix4 b);

//matrix utils
void		matrix_fill_zero(t_matrix4 *m);

#endif
