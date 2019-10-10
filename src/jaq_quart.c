#include "jaq_quart.h"
const int MAX_DIGITS=100;
const int BASE=10;
void jqp_init(jac_quart_point* q)
{
	mpf_init(q->x);
	mpf_init(q->y);
	mpf_init(q->a);
}

//initialising a quartic point with strings of base 10
void jqp_init_str(jac_quart_point* q, const char* xstr, const char* ystr, const char* astr)
{
	mpf_init_set_str(q->x, xstr, BASE);
	mpf_init_set_str(q->y, ystr, BASE);
	mpf_init_set_str(q->a, astr, BASE);
	//gmp_printf("%Ff", q.x);
}

//initialising a quartic point with mpf_t numbers
void jqp_init_mpf(jac_quart_point* q, const mpf_t x, const mpf_t y, const mpf_t a)
{
	mpf_init_set(q->x, x);
	mpf_init_set(q->y, y);
	mpf_init_set(q->a, a);

}

//free memory allocated on quartic point
void jqp_free(jac_quart_point *q)
{
	mpf_clear(q->x);
	mpf_clear(q->y);
	mpf_clear(q->a);

}
//prints quartic point coordinates
void jqp_print(const jac_quart_point q)
{
	//mpf_out_str(stdout, BASE, MAX_DIGITS, q.x);
	//mpf_out_str(stdout, BASE, MAX_DIGITS, q.y);
	gmp_printf("(%Ff, %Ff)\n", q.x, q.y);
}

//addition of two quartic points
void jqp_add(jac_quart_point* result, const jac_quart_point a1, const jac_quart_point a2) 
//x3=(x1*y2+x2*y1)/(1-(x1*x2)^2)
//y3=((1+(x1*x2)^2)*(y1*y2+2*a*x1*x2)+2*x1*x2*(x1^2+x2^2))/(1-(x1*x2)^2)^2
{
	mpf_t buf1, buf2, buf3, buf4, buf5;
	mpf_init(buf1);
	mpf_init(buf2);
	mpf_init(buf4);
	mpf_init(buf5);
	mpf_mul(buf1, a1.x, a2.y);
        mpf_mul(buf2, a2.x, a1.y);
	mpf_add(buf1, buf1, buf2); //buf1=x1*y2+x2*y1
	mpf_mul(buf2, a1.x, a2.x); //buf2=x1*x2
	mpf_mul(buf2, buf2, buf2); //buf2=(x1*x2)^2
	mpf_ui_sub(buf2, 1, buf2); //buf2=1-(x1*x2)^2
	mpf_init_set(buf3, buf2);  //saving 1-(x1*x2)^2 to buf3 because of usage in y computation
	if(!mpf_cmp_ui(buf2, 0))
	{
		perror("Division by zero in jqp_add in x computation\n");
	}
	mpf_div(result->x, buf1, buf2); // result.x is set 
	//y computations
	mpf_mul(buf1, a1.x, a2.x);
	mpf_mul(buf1, buf1, buf1); // buf1=(x1*x2)^2
	mpf_add_ui(buf1, buf1, 1); // buf1=1+(x1*x2)^2
	mpf_mul(buf2, a1.y, a2.y); // buf2=y1*y2
	mpf_mul(buf4, a1.x, a2.x);
	mpf_mul(buf4, buf4, a1.a);
	mpf_mul_ui(buf4, buf4, 2); //buf4=2*a*x1*x2
	mpf_add(buf2, buf2, buf4); //buf2=y1*y2+2*a*x1*x2
	mpf_mul(buf1, buf1, buf2); //buf1=(1+(x1*x2)^2)*(y1*y2+2*a*x1*x2)
	mpf_mul(buf2, a1.x, a2.x);
	mpf_mul_ui(buf2, buf2, 2); //buf2=2*x1*x2
	mpf_mul(buf4, a1.x, a1.x);
	mpf_mul(buf5, a2.x, a2.x);
	mpf_add(buf4, buf4, buf5); //buf4=x1^2+x2^2
	mpf_mul(buf2, buf2, buf4); //buf2=2*x1*x2(x1^2+x2^2)
	mpf_add(buf1, buf1, buf2); //buf1=(1+(x1*x2)^2)*(y1*y2+2*a*x1*x2)+2*x1*x2(x1^2+x2^2)
	mpf_mul(buf3, buf3, buf3);
	mpf_div(result->y, buf1, buf3); //result.y is set
	mpf_clear(buf1);
	mpf_clear(buf2);
	mpf_clear(buf3);
	mpf_clear(buf4);
	mpf_clear(buf5);
}

//double a quartic point
void jqp_double(jac_quart_point* result, const jac_quart_point a)
{
	jqp_add(result, a, a);
}

//count point k*P

void count_point(jac_quart_point *result, const mpz_t k, const jac_quart_point P)
{
	jac_quart_point Q;
	char* b;
	mpf_t a,x,y;
	mpf_init_set_str(x, "0", 10);
	mpf_init_set_str(y, "1", 10);
	mpf_init_set(a, P.a);
	int i;
	jqp_init_mpf(&Q, x, y, a);
	b=mpz_get_str(b, 2, k);
	//printf(b);
	for(i=strlen(b)-1;i>=0;i--)
	{
		jqp_double(&Q, Q);
		if(b[i]=='1')
		{
			jqp_add(&Q, Q, P);
		}
	}
	mpf_set(result->x, x);
	mpf_set(result->y, y);
	mpf_set(result->a, a);
	jqp_free(&Q);
}

