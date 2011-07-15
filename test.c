
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>


#define DEFAULT_INT	32
#define DEFAULT_STR	"MY COOL BROTHER"

const uint8_t def_val1 = DEFAULT_INT;

uint8_t		val1 	=	12;
uint32_t	val2 =	1135134123;

char mystr[] = "asdghsfh";


#define CONFIG_PARAM_TYPE_INT	1
#define CONFIG_PARAM_TYPE_STR	2

typedef struct config_param_t {
	uint8_t type;
	uint16_t size;
	uint8_t min;
	uint32_t max;
	const void * def;
	void * val;
} config_param_t;

typedef struct config_cmd_t {
	int id;
	char * str;
	int num_params;

	config_param_t params[3];
} config_cmd_t;

config_cmd_t config_cmd = {
	.id = 0,
	.str = "TEST",
	.num_params = 2,
	.params = { 
		{
			.type = CONFIG_PARAM_TYPE_INT,
			.size = sizeof(val1),
			.def = &def_val1,
			.min = 0,
			.max = 255,
			.val = &val1
		},
		{ 
			.type = CONFIG_PARAM_TYPE_STR,
			.size = sizeof(mystr),
			.def = DEFAULT_STR,
			.val = &mystr
		}
	}
};

int main()
{
	printf("%d: %s\n", config_cmd.id, config_cmd.str);
	int i;
	for (i = 0; i < config_cmd.num_params; i++) {
		config_param_t * param = &config_cmd.params[i];
		printf("Type: %d\n", param->type);
		switch (param->type) {
		case CONFIG_PARAM_TYPE_INT:
		{
			printf("Size: %d, Default: %d, Min: %d, Max: %d, Val: %d\n", param->size, 
																											*(const uint8_t *)param->def,
																											param->min, 
																											param->max,
																											*(uint8_t *)param->val);
			break;
		}
		case CONFIG_PARAM_TYPE_STR:
		{
			strcpy(param->val, "123");
			printf("Size: %d, Default: %s, Val: %s\n", param->size, 	
																									(char *)param->def,
																									(char *)param->val);

			break;
		}
		}
	}
}
