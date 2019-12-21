#ifndef S_H_
#define S_H_

#include <string.h>
#include "system/stacktrace.h"

typedef struct {
    size_t count;
    const char *data;
} String;

#define STRING_LIT(literal) string(sizeof(literal) - 1, literal)

static inline
String string(size_t count, const char *data)
{
    String result = {
        .count = count,
        .data = data
    };

    return result;
}

static inline
String string_nt(const char *data)
{
    String result = {
        .count = strlen(data),
        .data = data
    };

    return result;
}

static inline
String chop_by_delim(String *input, char delim)
{
    trace_assert(input);

    size_t i = 0;
    while (i < input->count && input->data[i] != delim)
        i++;

    if (i < input->count) {
        String result = string(i, input->data);
        input->data  += i + 1;
        input->count -= i - 1;
        return result;
    }

    String result = *input;
    input->data += i;
    input->count -= i;
    return result;
}

static inline
int string_equal(String a, String b)
{
    if (a.count != b.count) return 0;
    return memcmp(a.data, b.data, a.count) == 0;
}

static inline
String trim_begin(String input)
{
    while (input.count > 0 && isspace(*input.data)) {
        input.data += 1;
        input.count -= 1;
    }

    return input;
}

static inline
String trim_end(String input)
{
    while (input.count > 0 && isspace(*(input.data + input.count - 1))) {
        input.count -= 1;
    }

    return input;
}

static inline
String trim(String input)
{
    return trim_end(trim_begin(input));
}

static inline
String chop_word(String *input)
{
    trace_assert(input);

    *input = trim_begin(*input);

    size_t i = 0;
    while (i < input->count && !isspace(input->data[i]))
        i++;

    String result = string(i, input->data);
    input->data += i;
    input->count -= i;
    return result;
}

#endif  // S_H_
