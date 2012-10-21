/*
    Copyright © 2012 Syd Logan. All Rights Reserved.

    Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

    1. Redistributions of source code must retain the above copyright notice,
this list of conditions and the following disclaimer.

    2. Redistributions in binary form must reproduce the above copyright
notice, this list of conditions and the following disclaimer in the
documentation and/or other materials provided with the distribution.

    3. The name of the author may not be used to endorse or promote products
derived from this software without specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY Syd Logan "AS IS" AND ANY EXPRESS OR IMPLIED
WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO
EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER
IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
POSSIBILITY OF SUCH DAMAGE.
*/

#include "djangourls.h"

class MyHandler : public UrlHandler
{
public:
    void OnMatch(boost::cmatch &matches);
};

void
MyHandler::OnMatch(boost::cmatch &matches)
{
    printf("%s: got a match\n", __FUNCTION__);
    for (int i = 0; i < matches.size(); i++) {
        std::string match(matches[i].first, matches[i].second);
        printf("%s: %d --> %s\n", __FUNCTION__, i, match.c_str());
    }
}

int
main(int argc, char *argv[])
{
    UrlProcessor *processor;
    MyHandler myHandler;

    std::string re("^articles/2003/$");
    Url aUrl(re, static_cast<UrlHandler *>(&myHandler));
    aUrl.Register();

    re = "^articles/(\\d{4})/$";
    aUrl.SetRe(re);
    aUrl.Register();

    re = "^articles/(\\d{4})/(\\d{2})/$";
    aUrl.SetRe(re);
    aUrl.Register();

    re = "^articles/(\\d{4})/(\\d{2})/(\\d+)/$";
    aUrl.SetRe(re);
    aUrl.Register();

    std::string pattern;

    processor = UrlProcessor::GetInstance();
    if (!processor) {
        printf("%s: failed to get UrlProcessor instance\n", __FUNCTION__);
        goto out;
    }


    pattern = "hello world";
    if (processor->Match(pattern) == true) {
        printf("%s fail %s\n", __FUNCTION__, pattern.c_str());
    }

    pattern = "articles/2005/03/";
    if (processor->Match(pattern) == false) {
        printf("%s fail %s\n", __FUNCTION__, pattern.c_str());
    }
    pattern = "articles/2005/3/";
    if (processor->Match(pattern) == true) {
        printf("%s fail %s\n", __FUNCTION__, pattern.c_str());
    }
    pattern = "articles/2003/";
    if (processor->Match(pattern) == false) {
        printf("%s fail %s\n", __FUNCTION__, pattern.c_str());
    }
    pattern = "articles/2003";
    if (processor->Match(pattern) == true) {
        printf("%s fail %s\n", __FUNCTION__, pattern.c_str());
    }
    pattern = "articles/2003/03/03/";
    if (processor->Match(pattern) == false) {
        printf("%s fail %s\n", __FUNCTION__, pattern.c_str());
    }
out:
    return 0;
}
