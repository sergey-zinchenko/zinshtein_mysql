//
//  Created by Sergey Zinchenko on 07.01.17.
//  Copyright © 2017 SMediaLink. All rights reserved.
//

#include <mysql.h>
#include <my_global.h>
#include "algo.h"
#include <codecvt>
#include <locale>

#ifdef __cplusplus
extern "C" {
#endif

my_bool zinshtein_init(UDF_INIT *initid, UDF_ARGS *args, char *message) {
    if (args->arg_count < 2) {
        strcpy(message, "ZINSHTEIN() requires two or more arguments");
        return 1;
    }
    for (long i = 0; i < args->arg_count; i++) {
        if (args->arg_type[i] != STRING_RESULT) {
            strcpy(message, "ZINSHTEIN() requires only string arguments");
            return 1;
        }
    }
    initid->max_length = 3;
    initid->maybe_null = 0;
    return 0;
}

longlong zinshtein(UDF_INIT *initid, UDF_ARGS *args, char *is_null, char *error) {
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    std::wstring str1 = converter.from_bytes(args->args[0]);
    for (long i = 1; i < args->arg_count - 1; i++) {
        str1 += converter.from_bytes(args->args[i]);
    }
    std::wstring str2 = converter.from_bytes(args->args[args->arg_count - 1]);
    return zinshtein(&str1, &str2);
}

#ifdef __cplusplus
}
#endif
