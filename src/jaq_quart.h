
#include <gmp.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
typedef struct jac_quart_point jac_quart_point;
struct jac_quart_point
{
	mpf_t x,y,a;
};
void jqp_init(jac_quart_point* q);
void jqp_init_str(jac_quart_point* q, const char* xstr, const char* ystr, const char* astr);
void jqp_init_mpf(jac_quart_point* q, const mpf_t x, const mpf_t y, const mpf_t a);
void jqp_free(jac_quart_point *q);
void jqp_print(const jac_quart_point q);
void jqp_add(jac_quart_point* result, const jac_quart_point a1, const jac_quart_point a2);
void jqp_double(jac_quart_point* result, const jac_quart_point a);
void count_point(jac_quart_point *result, const mpz_t k, const jac_quart_point P);
