#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>
#include <math.h>
#include "utils.h"

int len(char* str) {
	int i = 0;

	while(str[i] != '\0')
    	i++;

	return i;
}

char* format(char* str, ...) {
	int str_size = len(str);

	int buffer_size = str_size;
	char* buffer = (char*)malloc(sizeof(char) * buffer_size);
	if(!buffer) {
		exit(1);
	}

    va_list args;
    va_start(args, str);
 
 	int str_index = 0;
 	int buffer_index = 0;
    while (str[str_index] != '\0') {
    	if(str_index + 1 < str_size && str[str_index] == '$' && str[str_index + 1] == 'v') {
    		char* v = va_arg(args, char*);
    		int v_size = len(v);

			// Add buffer capacity if necessary
    		if(buffer_index + v_size > buffer_size) {
    			buffer_size += v_size - (buffer_size - buffer_index);
    			buffer = (char*)realloc(buffer, buffer_size * sizeof(char));
    		}

    		for (int j = 0; j < v_size; j++)
    			buffer[buffer_index + j] = v[j];

    		str_index += 2;
    		buffer_index += v_size;
    		continue;
    	}

    	// Add buffer capacity if necessary
    	if(buffer_index + 1 > buffer_size) {
			buffer_size += 10;
			buffer = (char*)realloc(buffer, buffer_size * sizeof(char));
		}

    	buffer[buffer_index] = str[str_index];
    	str_index++;
    	buffer_index++;
    }
 
 	// Cleans excess buffer capacity
 	if(buffer_index < buffer_size) {
		buffer_size -= (buffer_size - buffer_index);
		buffer = (char*)realloc(buffer, buffer_size * sizeof(char));
	}

	// add \0
	buffer = (char*)realloc(buffer, (buffer_size + 1) * sizeof(char));
	buffer[buffer_size] = '\0';

    va_end(args);

    return buffer;
}

void echo(char* str, ...)
{
	int str_size = len(str);

	int buffer_size = str_size;
	char* buffer = (char*)malloc(sizeof(char) * buffer_size);
	if(!buffer) {
		exit(1);
	}

    va_list args;
    va_start(args, str);
 
 	int str_index = 0;
 	int buffer_index = 0;
    while (str[str_index] != '\0') {
    	if(str_index + 1 < str_size && str[str_index] == '$' && str[str_index + 1] == 'v') {
    		char* v = va_arg(args, char*);
    		int v_size = len(v);

			// Add buffer capacity if necessary
    		if(buffer_index + v_size > buffer_size) {
    			buffer_size += v_size - (buffer_size - buffer_index);
    			buffer = (char*)realloc(buffer, buffer_size * sizeof(char));
    		}

    		for (int j = 0; j < v_size; j++)
    			buffer[buffer_index + j] = v[j];

    		str_index += 2;
    		buffer_index += v_size;
    		continue;
    	}

    	// Add buffer capacity if necessary
    	if(buffer_index + 1 > buffer_size) {
			buffer_size += 10;
			buffer = (char*)realloc(buffer, buffer_size * sizeof(char));
		}

    	buffer[buffer_index] = str[str_index];
    	str_index++;
    	buffer_index++;
    }
 
 	// Cleans excess buffer capacity
 	if(buffer_index < buffer_size) {
		buffer_size -= (buffer_size - buffer_index);
		buffer = (char*)realloc(buffer, buffer_size * sizeof(char));
	}

	// add \0
	buffer = (char*)realloc(buffer, (buffer_size + 1) * sizeof(char));
	buffer[buffer_size] = '\0';
	
    va_end(args);

    write(1, buffer, buffer_size);
    free(buffer);
}

char** explode(char* data, int data_size, char delimiter) {
	int nb_tokens = 0;

	for(int i = 0, last_delimiter_pos = 0; i < data_size; i++)
	{
		if(i == data_size - 1 && (i - last_delimiter_pos) > 0) {
			nb_tokens++;
			break;
		}

		if(data[i] == delimiter) {
			last_delimiter_pos = i;
			nb_tokens++;
		}
	}

	char** tokens = (char**)malloc(sizeof(char*) * (nb_tokens + 1));

	int current_index = 0;
	int last_token_index = 0;
	int token_founded = 0;
	while(token_founded != nb_tokens)
	{
		if((data[current_index] == delimiter && current_index < data_size - 1) || current_index == data_size - 1) {
			int pad = (data[current_index] == delimiter && current_index < data_size - 1) ? 1 : 2;
			char* token = (char*)malloc(sizeof(char) * (current_index - last_token_index + pad));

			for(int i = 0, current_token_index = last_token_index; current_token_index < current_index + (pad - 1); current_token_index++, i++)
				token[i] = data[current_token_index];

			token[(current_index - last_token_index + (pad - 1))] = '\0';

			*(tokens + token_founded) = token;
			token_founded++;
			last_token_index = current_index + pad;
		}

		current_index++;
	}

	*(tokens + nb_tokens) = '\0';

	return tokens;
}

void free_explode(char** tokens) {
	for(int i = 0; *(tokens + i); i++)
		free(*(tokens + i));
	free(tokens);
}

char* to_string(int n) {
	if(n == 0) {
		char* str_digit_zero = (char*)malloc(sizeof(char) * 2);
		*(str_digit_zero) = '0';
		*(str_digit_zero + 1) = '\0';
		return str_digit_zero;
	}

	int nbDigit = floor(log10(abs(n))) + 1;

	char* str_digit = (char*)malloc(sizeof(char) * (nbDigit + 1));
	*(str_digit + nbDigit) = '\0';

	for (int i = (nbDigit - 1); i >= 0; i--)
	{
		*(str_digit + i) = (char)('0' + (n % 10));
		n /= 10;
	}

	return str_digit;
}