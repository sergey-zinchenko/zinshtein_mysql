//
// Created by Sergey Zinchenko on 08.01.17.
// Copyright © 2017 SMediaLink. All rights reserved.
//

#include "algo.h"
#include <vector>

class Match {
public:
    long shrt;
    long lng;
    long len;

    Match(long shrt, long lng, long len) {
        this->shrt = shrt - len;
        this->lng = lng - len;
        this->len = len;
    }
};

typedef std::vector<Match> Matches;

inline Matches *spliceMatches(Match *match, Match *maskMatch) {
    long lng = match->lng;
    long shrt = match->shrt;
    long len = 0;
    Matches *matches = new Matches;
    while (shrt - match->shrt < match->len) {
        if ((lng < maskMatch->lng - 1 || lng > maskMatch->lng + maskMatch->len) &&
            (shrt < maskMatch->shrt - 1 || shrt > maskMatch->shrt + maskMatch->len)) {
            len++;
        } else if (len > 0) {
            matches->push_back(Match(shrt, lng, len));
            len = 0;
        }
        lng++;
        shrt++;
    }
    if (len > 0) {
        matches->push_back(Match(shrt, lng, len));
    }
    return matches;
}

inline Matches *filterMatches(long idx, Matches *matches) {
    Matches *filtered = new Matches;
    Match *matcheIdx = &matches->at(idx);
    for (long i = 0; i < matches->size(); i++) {
        if (idx != i) {
            Matches *spliced = spliceMatches(&matches->at(i), matcheIdx);
            filtered->insert(filtered->end(), spliced->begin(), spliced->end());
            spliced->clear();
            delete spliced;
        }
    }
    return filtered;
}

inline long step(Matches *matches) {
    long maxLength = 0;
    for (unsigned long i = 0; i < matches->size(); i++) {
        Matches *filteredMatches = filterMatches(i, matches);
        long curMaxLength = matches->at(i).len + 1 + step(filteredMatches);
        if (curMaxLength > maxLength) {
            maxLength = curMaxLength;
        }
        filteredMatches->clear();
        delete filteredMatches;
    }
    return maxLength;
}

long zinshtein(std::wstring *str1, std::wstring *str2) {

    str1->erase(std::remove_if(str1->begin(), str1->end(), ::isspace), str1->end());
    std::transform(str1->begin(), str1->end(), str1->begin(), ::tolower);
    str2->erase(std::remove_if(str2->begin(), str2->end(), ::isspace), str2->end());
    std::transform(str2->begin(), str2->end(), str2->begin(), ::tolower);

    if (str2->size() > str1->size()) {
        std::wstring *tempStr = str2;
        str2 = str1;
        str1 = tempStr;
    }


    long lngPtnCount = str1->size() - 1, shrtPtnCount = str2->size() - 1;

    Matches *matches = new Matches;

    for (long i = 0; i < shrtPtnCount; i++) {
        long lng = 0, shrt = i, len = 0;
        while (lng < lngPtnCount && shrt < shrtPtnCount) {
            if ((str2->at(shrt) == str1->at(lng)) && (str2->at(shrt + 1) == str1->at(lng + 1))) {
                len++;
            } else if (len > 0) {
                matches->push_back(Match(shrt, lng, len));
                len = 0;
            }
            lng++;
            shrt++;
        }
        if (len > 0) {
            matches->push_back(Match(shrt, lng, len));
            len = 0;
        }
    }

    for (long i = 1; i < lngPtnCount; i++) {
        long lng = i, shrt = 0, len = 0;
        while (lng < lngPtnCount && shrt < shrtPtnCount) {
            if ((str2->at(shrt) == str1->at(lng)) && (str2->at(shrt + 1) == str1->at(lng + 1))) {
                len++;
            } else if (len > 0) {
                matches->push_back(Match(shrt, lng, len));
                len = 0;
            }
            lng++;
            shrt++;
        }
        if (len > 0) {
            matches->push_back(Match(shrt, lng, len));
            len = 0;
        }
    }

    long result = step(matches);
    matches->clear();
    delete matches;
    return result;
}