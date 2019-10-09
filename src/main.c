#include "jaq_quart.h"
int main()
{
	mpz_t k;
	mpf_t x1,x2,y1,y2, a;
	mpf_init_set_ui(x1, 1);
	mpf_init_set_ui(y1, 2);
	mpf_sqrt(y1, y1);
	mpf_init_set_ui(x2, 2);
	mpf_init_set_ui(y2, 17);
	mpf_sqrt(y2, y2);
	mpf_init_set_ui(a, 4);
	jac_quart_point jqp1, jqp2, result;
	//mpz_init_set_ui(k, 10);
	jqp_init(&result);
	jqp_init_mpf(&jqp1, x1, y1, a);
	jqp_init_mpf(&jqp2, x2, y2, a);
	//count_point(&result, k, jqp1);
	jqp_add(&result, jqp1, jqp2);
	jqp_print(result);
}
