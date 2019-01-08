#include <stdio.h> //for sscanf(), printf("%s\n", )
#include <stdlib.h> // for EXIT_SUCCESS
#include <limits.h>
#include <string.h>
#include <stdint.h> //for uint8_t, etc
#include <inttypes.h>
#include <ctype.h>



#define SECONDS_IN_MINUTE 60
#define SECONDS_IN_HOUR 3600
#define SECONDS_IN_DAY 86400
#define SECONDS_IN_MONTH 2629800
#define SECONDS_IN_YEAR 31557600
#define MAX_SEC 3155760000


typedef unsigned char bool;
bool TRUE = 1;
bool FALSE = 0;

typedef uint32_t num_seconds_t;

typedef struct time_spec_tt {
	uint8_t year;
	uint8_t month;
	uint8_t day;
	uint8_t hour;
	uint8_t minute;
	uint8_t second;
} time_spec_t;

char * standardized_string_input (char * input);
bool is_legal_time_spec(char * input);
bool is_legal_seconds(char * input);
num_seconds_t string_to_seconds( char * input );
time_spec_t *string_to_time_spec( char * input );
time_spec_t *seconds_to_time_spec( num_seconds_t input);
num_seconds_t time_spec_to_seconds( time_spec_t * input);
void print_time_spec( time_spec_t *time_spec );
bool get_time_arg( char *in_str, num_seconds_t *seconds_p );
void conv( char * string );
void add( char * string1, char * string2 ); 
void subt( char * string1, char * string2 );
void comp( char * string1, char * string2 );
void usage( void );
void help( void );

////The main function can get two or three arguments
int main(int argc, char *argv[]){
	if( argc > 1 ){
		char * Option = argv[1];
		if( strcmp(Option, "conv") == 0 && argc > 1){
			conv(argv[2]);
		} else if( strcmp(Option, "add") == 0 && argc > 3){
			add(argv[2], argv[3]);
		} else if( strcmp(Option, "subt") == 0 && argc > 3){
			subt(argv[2], argv[3]);
		} else if( strcmp(Option, "comp") == 0 && argc > 3){
			comp(argv[2], argv[3]);
		} else if( strcmp(Option, "help") == 0 ){
			help();
		} else {
			printf("Please verify your input matchs one of the following expressions:\n");
			usage();
			printf("Type 'help' for more details\n");
		}
	} else {
		printf("Please verify your input matchs one of the following expressions:\n");
		usage();
		printf("Type 'help' for more details\n");
	}
	return(0);
}


///This functiion removes all the spaces 
char * standardized_string_input (char * input){
	//to remove all spaces from a given string
	// The time complexity of this approach is O(n)
	int count = 0; 
    // Traverse the given string. If current character 
    // is not space, then place it at index 'count++' 
    for (int i = 0; input[i]; i++) 
        if (input[i] != ' ') 
            input[count++] = input[i]; // here count is 
                                   // incremented 
    input[count] = '\0';

    return input;
}

// This function returns TRUE if the string given as the input argument is a valid time spec; 
// otherwise produces diagnostic messages on stderr and return FALSE. 
// Errors diagnosed include extraneous characters and field values exceeding limits.
bool is_legal_time_spec(char * input){

	char * std_input = standardized_string_input(input);
    ///extracting integers from the text
    int8_t year, month, day, hour, minute, second;
    int check = sscanf(std_input, "%" PRIu8 "y%" PRIu8 "n%" PRIu8 "d%" PRIu8 "h%" PRIu8 "m%" PRIu8 "s", \
    		   &year, &month, &day, &hour, &minute, &second);

    if (check==6 && year < 100 && year >= 0 && month < 12 && month >= 0 && day >= 0 && day < 31 \
    	         && hour < 24 && hour >= 0 && minute < 60 && minute >= 0 && second < 60 && second >= 0)
		return TRUE;
	else
		return FALSE;

}

// return TRUE if the string given as the input argument is a valid number of seconds; 
//otherwise produce diagnostic messages on stderr and return FALSE. 
//Errors diagnosed include extraneous characters and field values exceeding the limit on the number of seconds.
bool is_legal_seconds(char * input){
	uint32_t seconds;
	char * std_input = standardized_string_input(input);
	int check;
	
	check = sscanf(std_input, "%" PRIu32, &seconds);
	///sscanf is used to read from a string and convert the string into integer.
	while (*std_input != '\0') {
		if (!isdigit(*std_input)) {
			return FALSE;
			fprintf(stderr, "argument is not a valid number of seconds \n");
		}
		std_input++;
	}
	return TRUE;
	
	// if (check ==1 && seconds < MAX_SEC  && seconds > 0){
	// 	return TRUE;
	// } else {
	// 	fprintf(stderr, "argument is not a valid number of seconds \n");
	// 	return FALSE;
	// }
} 

//return the number of seconds specified by the string passed as the argument to the function. 
//The string is known to contain a valid "number of seconds" specification.
num_seconds_t string_to_seconds( char * input ){
  
  num_seconds_t seconds_value = 0;

  for (int i = 0; input[i] != '\0'; i++){
  	char c = input[i];
  	int n = c - '0';
  	seconds_value = seconds_value*10 + n;
  }
  
  return seconds_value;
} 

//return a pointer to a dynamically allocated struct containing the fields of a time spec 
//specified by the string passed as the argument to the function. 
//The string is known to contain a valid time spec. If memory for the struct cannot be allocated, 
//the function returns NULL.
time_spec_t *string_to_time_spec( char * input ){
	
	if (is_legal_time_spec(input) == TRUE){
		time_spec_t * time_spec_value = (time_spec_t *) malloc(6*sizeof(int8_t));
		if (time_spec_value == NULL) {
			fputs("Memory allocation error", stderr);
			return NULL;
		} else {
        
        char * std_input = standardized_string_input(input);
		int8_t year, month, day, hour, minute, second;
    	sscanf(std_input, "%" PRIu8 "y%" PRIu8 "n%" PRIu8 "d%" PRIu8 "h%" PRIu8 "m%" PRIu8 "s", \
    		   &year, &month, &day, &hour, &minute, &second);
    		
		time_spec_value->year = year;
		time_spec_value->month = month;
		time_spec_value->day = day;
		time_spec_value->hour = hour;
		time_spec_value->minute = minute;
		time_spec_value->second = second;


		return time_spec_value;	
		}
		
	} else {
		fputs("invalid string input", stderr);
		return NULL;
	}

} 

// Converts a valid number of seconds to a time spec, 
//and store the fields of the time spec in a dynamically allocated time_spec_t structure. 
//On success, a pointer to the newly allocated structure is returned. 
//If memory for the struct cannot be allocated, the function returns NULL.
time_spec_t *seconds_to_time_spec( num_seconds_t input){
	    
    	num_seconds_t inputNum = input;

		time_spec_t * time_spec_value = (time_spec_t *) malloc(20* sizeof(time_spec_t *));
		if (time_spec_value == NULL)
			return NULL;
		else {
			int8_t year = inputNum / SECONDS_IN_YEAR;
			int8_t monthInSec = inputNum % SECONDS_IN_YEAR;
			int8_t month = monthInSec / SECONDS_IN_MONTH;
			int8_t dayInSec = monthInSec % SECONDS_IN_MONTH; 
			int8_t day = dayInSec / SECONDS_IN_DAY;
			int8_t hourInSec = dayInSec % SECONDS_IN_DAY;
			int8_t hour = hourInSec / SECONDS_IN_HOUR;
			int8_t minutesInSec = hourInSec % SECONDS_IN_HOUR;
			int8_t minutes = minutesInSec / SECONDS_IN_MINUTE;
			int8_t second = minutesInSec % SECONDS_IN_MINUTE;

			time_spec_value->year = year;
			time_spec_value->month = month;
			time_spec_value->day = day;
			time_spec_value->hour = hour;
			time_spec_value->minute = minutes;
			time_spec_value->second = second;

			// sprintf(year,"%s", time_spec_value->year);
			// sprintf(month,"%s", time_spec_value->month);
			// sprintf(day,"%s", time_spec_value->day);
			// sprintf(hour,"%s", time_spec_value->hour);
			// sprintf(minutes,"%s", time_spec_value->minute);
			// sprintf(second,"%s", time_spec_value->second);

			return time_spec_value;
    	}
    

}

//Converts a valid time spec to the corresponding number of seconds and return that number of seconds.
num_seconds_t time_spec_to_seconds( time_spec_t * input){
	num_seconds_t second_value = 0;
	second_value = (input->year) * SECONDS_IN_YEAR + (input->month) * SECONDS_IN_MONTH + \
					(input->day) * SECONDS_IN_DAY + (input->hour) * SECONDS_IN_HOUR + \
					((input->minute) * SECONDS_IN_MINUTE) + input->second;
	
	return second_value;
}

// Outputs a valid time spec on stdout.
void print_time_spec( time_spec_t *time_spec ){
	printf("%" PRIu8 "y", time_spec->year);
	printf("%" PRIu8 "n", time_spec->month);
	printf("%" PRIu8 "d", time_spec->day);
	printf("%" PRIu8 "h", time_spec->hour);
	printf("%" PRIu8 "m", time_spec->minute);
	printf("%" PRIu8 "s\n", time_spec->second);	 
}

//The function returns TRUE if it was able to convert the string pointed to by in_str to a number of seconds. 
//In this case the number of seconds is stored in the location pointed to by seconds_p. 
//The string pointed to by in_str could be a time spec or it could specify a number of seconds. 
//The function returns FALSE if it was not able to convert the string pointed to by in_str to a number of seconds; 
//for example, the string was neither a legal time spec nor a legal number of seconds. 
//It also returns FALSE if the number of seconds is not less than the limit of 3155760000. 
//In the latter two cases an appropriate error message is generated on stderr. 
//If the input pointed to by in_str is neither a legal time spec nor a legal number of seconds, 
//then no operation should be performed on the location pointed to by seconds_p.
bool get_time_arg( char *in_str, num_seconds_t *seconds_p ){
	
	if (!is_legal_seconds(in_str) && !is_legal_time_spec(in_str)) {
		fprintf(stderr, "String given does not fit required specifications.\n");
		return FALSE;
	}
	if (is_legal_seconds(in_str) && string_to_seconds(in_str) > MAX_SEC) {
		fprintf(stderr, "String given converts to a second value that exceeds maximum value.\n");
		return FALSE;
	}

	//num_seconds_t * seconds_p = (num_seconds_t *) malloc(sizeof(num_seconds_t *));
	if(is_legal_seconds(in_str) == TRUE){
		* seconds_p = string_to_seconds(in_str);
	} else {
		* seconds_p = time_spec_to_seconds(string_to_time_spec(in_str));
	}

	return TRUE;

} 

////This function converts a number of seconds (an unsigned integer) less than 3155760000 to
// a "time specification" and vice versa
void conv( char * string ) {
	if (is_legal_seconds(string)) {
		print_time_spec(seconds_to_time_spec(string_to_seconds(string)));
		printf ("hi1\n");
	} else if (is_legal_time_spec(string)) {
		printf ("hi\n");
		// printf("%"PRIu8"\n", string_to_time_spec(string)->year);
		printf("%"PRIu32"\n", time_spec_to_seconds(string_to_time_spec(string)));
		// print_time_spec(string_to_time_spec(string));
	}
}

/// adds two time values
void add( char * string1, char * string2 ) {
	num_seconds_t seconds1, seconds2;

	if (is_legal_seconds(string1)) {
		seconds1 = string_to_seconds(string1);
	} else {
		seconds1 = time_spec_to_seconds(string_to_time_spec(string1));
	}

	if (is_legal_seconds(string2)) {
		seconds2 = string_to_seconds(string2);
	} else {
		seconds2 = time_spec_to_seconds(string_to_time_spec(string2));
	}

	if (seconds1 + seconds2 < MAX_SEC) {
		print_time_spec(seconds_to_time_spec(seconds1 + seconds2));
	} else {
		printf("Value exceeds maximum second value.\n");
	}
}

/// subtracts two time values
void subt( char * string1, char * string2 ) {
	num_seconds_t seconds1, seconds2;

	if (is_legal_seconds(string1)) {
		seconds1 = string_to_seconds(string1);
	} else {
		seconds1 = time_spec_to_seconds(string_to_time_spec(string1));
	}

	if (is_legal_seconds(string2)) {
		seconds2 = string_to_seconds(string2);
	} else {
		seconds2 = time_spec_to_seconds(string_to_time_spec(string2));
	}

	if (seconds1 < seconds2) {
		printf("Subtraction results in negative time value\n");
	} else {
		print_time_spec(seconds_to_time_spec(seconds1 - seconds2));
	}
}

//// compares two time values
void comp( char * string1, char * string2 ) {
	num_seconds_t seconds1, seconds2;

	if (is_legal_seconds(string1)) {
		seconds1 = string_to_seconds(string1);
	} else {
		seconds1 = time_spec_to_seconds(string_to_time_spec(string1));
	}

	if (is_legal_seconds(string2)) {
		seconds2 = string_to_seconds(string2);
	} else {
		seconds2 = time_spec_to_seconds(string_to_time_spec(string2));
	}

	if (seconds1 < seconds2) {
		printf("less\n");
	} else if (seconds1 == seconds2) {
		printf("equal\n");
	} else if (seconds1 > seconds2) {
		printf("greater\n");
	}
}



void usage( void ) {
puts( "Usage: time_calc help" );
puts( " time_calc conv " );
puts( " time_calc {add,subt,comp} " );
}

// help function
void help( void ){
	printf("time value is either seconds (integer between 0 - %ld) or time specification of the form '0y 0n 0d 0h 0m 0s'.\n", MAX_SEC);
	printf("time_calc conv 'time value' : converts between a time spec value and a number of seconds\n");
	printf("time_calc add 'time value' 'time value' : adds two time values and prints the resulting time specification\n");
	printf("time_calc subt 'time value' 'time value' : subtracts two time values and prints the resulting time specification\n");
	printf("time_calc comp 'time value' 'time value : compares two time values and prints outcome of the comparison\n");
	printf("time_calc help : lists parameters of all possible commands aswell as a brief description of the outcome of the command\n");

}


