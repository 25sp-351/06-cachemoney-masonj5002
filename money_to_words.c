#include "money_to_words.h"

#include <math.h>
#include <stdio.h>
#include <string.h>

char* intToString(int value) {
    char text_output[140] = "";

    strcat(text_output, dollarsToString(value / 100));

    int greaterThanNinetyNine = 0;
    if (value > 99)
        greaterThanNinetyNine = 1;

    strcat(text_output, centsToString(greaterThanNinetyNine, value % 100));
    return strdup(text_output);
};

char* dollarsToString(int value) {
    if (value <= 0)
        return "zero dollars ";
    char text_output[130] = "";

    char* scales[]        = {"", "thousand ", "million ", "billion "};

    char* tens[] = {"",       "",       "twenty ",  "thirty ", "forty ",
                    "fifty ", "sixty ", "seventy ", "eighty ", "ninety "};

    char* ones_and_teens[] = {
        "",         "one ",     "two ",       "three ",    "four ",
        "five ",    "six ",     "seven ",     "eight ",    "nine ",
        "ten ",     "eleven ",  "twelve ",    "thirteen ", "fourteen ",
        "fifteen ", "sixteen ", "seventeen ", "eighteen ", "nineteen "};

    int scale_size = 0;
    if (value > 999999999) {  // 999,999,999
        scale_size = 3;
    } else if (value > 999999) {  // 999,999
        scale_size = 2;
    } else if (value > 999) {
        scale_size = 1;
    }

    for (int ix = scale_size; ix >= 0; ix--) {
        int divisor        = pow(1000, ix);

        int scale_value    = (value / divisor) % 1000;

        int hundreds_place = scale_value / 100;
        if (hundreds_place != 0) {
            strcat(text_output, ones_and_teens[hundreds_place]);
            strcat(text_output, "hundred ");
        }
        int ones_and_teens_place = scale_value % 100;
        if (ones_and_teens_place < 20 && ones_and_teens_place != 0) {
            strcat(text_output, ones_and_teens[ones_and_teens_place]);
        } else {

            int tens_place = (scale_value % 100) / 10;
            if (tens_place != 0)
                strcat(text_output, tens[tens_place]);

            int ones_place = scale_value % 10;
            if (tens_place != 0)
                strcat(text_output, ones_and_teens[ones_place]);
        }

        if (scale_value != 0)
            strcat(text_output, scales[ix]);
    }

    if (value > 1) {
        strcat(text_output, "dollars");
        return strdup(text_output);
    }
    if (value == 1)
        strcat(text_output, "dollar");
    return strdup(text_output);
}

char* centsToString(int greaterThanNinetyNine, int cents) {
    if (cents == 0 && greaterThanNinetyNine == 1)
        return " and zero cents";
    else if (cents == 0)
        return "zero cents";

    char text_output[35]   = "";

    char* ones_and_teens[] = {"",        "one",       "two",      "three",
                              "four",    "five",      "six",      "seven",
                              "eight",   "nine",      "ten",      "eleven",
                              "twelve",  "thirteen",  "fourteen", "fifteen",
                              "sixteen", "seventeen", "eighteen", "nineteen"};

    char* tens[]           = {"",      "",      "twenty",  "thirty", "forty",
                              "fifty", "sixty", "seventy", "eighty", "ninety"};

    if (greaterThanNinetyNine == 1)
        strcat(text_output, " and ");

    if (cents < 20) {
        strcat(text_output, ones_and_teens[cents]);
    } else if (cents < 100) {

        int tens_place = cents / 10;
        strcat(text_output, tens[tens_place]);

        strcat(text_output, "-");

        int ones_place = cents % 10;
        strcat(text_output, ones_and_teens[ones_place]);
    }
    if (cents == 1) {
        strcat(text_output, " cent");
        return strdup(text_output);
    }

    strcat(text_output, " cents");

    return strdup(text_output);
}
