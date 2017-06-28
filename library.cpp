//
//  Created by Sergey Zinchenko on 07.01.17.
//  Copyright © 2017 SMediaLink. All rights reserved.
//

#include <mysql.h>
#include <my_global.h>
#include <codecvt>
#include <functional>
#include <locale>
#include "algo.h"
#include "ertranslit.h"

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
    if (args->args[args->arg_count - 1] == NULL) {
        strcpy(message, "ZINSHTEIN() requires last one argument not to be null");
        return 1;
    }
    initid->max_length = 3;
    initid->maybe_null = 0;
    return 0;
}

longlong zinshtein(UDF_INIT *initid, UDF_ARGS *args, char *is_null, char *error) {

    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    std::wstring str1 = L"";
    for (long i = 0; i < args->arg_count - 1; i++) {
        if (args->args[i] != NULL)
            str1 += converter.from_bytes(args->args[i]);
    }
    std::wstring str2 = converter.from_bytes(args->args[args->arg_count - 1]);

    str1.erase(std::remove_if(str1.begin(), str1.end(), ::isspace), str1.end());
    //std::transform(str1.begin(), str1.end(), str1.begin(), std::bind2nd(std::ptr_fun(&std::tolower<wchar_t>), std::locale("")));
    str2.erase(std::remove_if(str2.begin(), str2.end(), ::isspace), str2.end());
    //std::transform(str2.begin(), str2.end(), str2.begin(), std::bind2nd(std::ptr_fun(&std::tolower<wchar_t>), std::locale("")));
    return zinshtein(&str1, &str2);

//    std::wstring *ps1 = retranslit(&str1), *ps2 = retranslit(&str2);
//    longlong result = zinshtein(ps1, ps2);
//    delete ps1;
//    delete ps2;
//    return result;


}

#ifdef __cplusplus
}
#endif
