#include "common.h"

namespace Agenda {
char* strcat(char *dest, const char *src)
{
    char *rdest = dest;

    while (*dest)
      dest++;
    while ((*dest++ = *src++))
      ;
    return rdest;
}

char* itoa(int num, char* buffer, int base) {
    int curr = 0;
    if (num == 0) {
        // Base case
        buffer[curr++] = '0';
        buffer[curr] = '\0';
        return buffer;
    }
    int num_digits = 0;
    if (num < 0) {
        if (base == 10) {
            num_digits ++;
            buffer[curr] = '-';
            curr ++;
            // Make it positive and finally add the minus sign
            num *= -1;
        }
        else
            // Unsupported base. Return NULL
            return nullptr;
    }
    num_digits += (int)floor(log(num) / log(base)) + 1;
    // Go through the digits one by one
    // from left to right
    while (curr < num_digits) {
        // Get the base value. For example, 10^2 = 1000, for the third digit
        int base_val = (int) pow(base, num_digits-1-curr);
        // Get the numerical value
        int num_val = num / base_val;
        char value = num_val + '0';
        buffer[curr] = value;
        curr ++;
        num -= base_val * num_val;
    }
    buffer[curr] = '\0';
    return buffer;
}
void timeToString(char* str, const AgendaTime& t) {
	char buf[10] = {'\0'};
	itoa(t.hours, buf, 10);
	strlcpy(str, buf, strlen(buf)+1);
	strcat(str, ":");
	itoa(t.minutes, buf, 10);
	strcat(str, buf);
}
void gapToString(char* str, const Gap& g) {
	char buf[10] = {'\0'};
	itoa(g.start.hours, buf, 10);
	strlcpy(str, buf, strlen(buf)+1);
	strcat(str, ":");
	itoa(g.start.minutes, buf, 10);
	strcat(str, buf);

	strcat(str, " → ");

	itoa(g.end.hours, buf, 10);
	strcat(str, buf);
	strcat(str, ":");
	itoa(g.end.minutes, buf, 10);
	strcat(str, buf);
}
bool operator==(const Gap& g1, const Gap &g2) {
	return g1.start == g2.start && g1.end == g2.end;
}
bool operator>(const AgendaTime& t1, const AgendaTime &t2) {
	if (t1.hours > t2.hours)
		return true;
	if (t1.hours < t2.hours)
		return false;
	return t1.minutes > t2.minutes;
}
bool operator==(const AgendaTime& t1, const AgendaTime &t2) {
	return t1.minutes == t2.minutes && t1.hours == t2.hours;
}
bool operator<=(const AgendaTime& t1, const AgendaTime &t2) {
	return t1 < t2 || t1 == t2;
}
} // Agenda
bool operator<(const AgendaTime& t1, const AgendaTime &t2) {
	if (t1.hours < t2.hours)
		return true;
	if (t1.hours > t2.hours)
		return false;
	return t1.minutes < t2.minutes;
}
bool operator<(const CommonGap& g1, const CommonGap &g2) {
	return g1.start < g2.start || g1.end < g2.end;
}
