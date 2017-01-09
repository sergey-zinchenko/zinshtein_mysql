//
//  Created by Sergey Zinchenko on 07.01.17.
//  Copyright © 2017 SMediaLink. All rights reserved.
//

#include <mysql.h>
#include <my_global.h>
#include "algo.h"
#include <codecvt>

#ifdef __cplusplus
extern "C" {
#endif

my_bool zinshtein_init(UDF_INIT *initid, UDF_ARGS *args, char *message) {
    if (args->arg_count != 2)
    {
        strcpy(message, "ZINSHTEIN() requires two arguments");
        return 1;
    }
    else if (args->arg_type[0] != STRING_RESULT || args->arg_type[1] != STRING_RESULT)
    {
        strcpy(message, "ZINSHTEIN() requires two string arguments");
        return 1;
    }
    initid->max_length = 3;
    initid->maybe_null = 0;
    return 0;
}

void zinshtein_deinit(UDF_INIT *initid) {

}

longlong zinshtein(UDF_INIT *initid, UDF_ARGS *args, char *is_null, char *error) {
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    std::wstring str1 = converter.from_bytes(args->args[0]);
    std::wstring str2 = converter.from_bytes(args->args[1]);
    return zinshtein(&str1, &str2);
}

#ifdef __cplusplus
}
#endif
