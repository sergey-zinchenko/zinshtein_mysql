//
// Created by Sergey Zinchenko on 16.01.17.
//

#include "ertranslit.h"

std::wstring *retranslit(std::wstring *input) {
    std::wstring *result = new std::wstring();
    for (wchar_t c : *input) {
        switch (c) {
            case L'а' : *result += L'a';
                break;
            case L'б' : *result += L'b';
                break;
            case L'в' : *result += L'v';
                break;
            case L'г' : *result += L'g';
                break;
            case L'д' : *result += L'd';
                break;
            case L'е' : *result += L'e';
                break;
            case L'ё' : *result += L"je";
                break;
            case L'ж' : *result += L"zh";
                break;
            case L'з' : *result += L'z';
                break;
            case L'и' : *result += L'i';
                break;
            case L'й' : *result += L'y';
                break;
            case L'к' : *result += L'k';
                break;
            case L'л' : *result += L'l';
                break;
            case L'м' : *result += L'm';
                break;
            case L'н' : *result += L'n';
                break;
            case L'о' : *result += L'o';
                break;
            case L'п' : *result += L'p';
                break;
            case L'р' : *result += L'r';
                break;
            case L'с': *result += L"s";
                break;
            case L'т': *result += L"t";
                break;
            case L'у': *result += L"u";
                break;
            case L'ф': *result += L"f";
                break;
            case L'х': *result += L"kh";
                break;
            case L'ц': *result += L'c';
                break;
            case L'ч': *result += L"ch";
                break;
            case L'ш': *result += L"sh";
                break;
            case L'щ': *result += L"jsh";
                break;
            case L'ъ': *result += L"hh";
                break;
            case L'ы': *result += L"ih";
                break;
            case L'ь': *result += L"jh";
                break;
            case L'э': *result += L"eh";
                break;
            case L'ю': *result += L"ju";
                break;
            case L'я': *result += L"ja";
                break;
            default: *result += c;
        }
    }
    return result;
}
