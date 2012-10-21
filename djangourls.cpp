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

Url::Url()
{
}

Url::Url(std::string &re, UrlHandler *handler)
{
    SetRe(re);
    SetHandler(handler);
}

void
Url::SetHandler(UrlHandler *handler)
{
    m_handler = handler;
}

void
Url::SetRe(std::string &re)
{
    m_re = re;
    m_rx.assign(re, boost::regex_constants::icase);  // compile the regex
}

bool 
Url::Match(std::string &val)
{
    bool ret;

    boost::cmatch res;
    ret = boost::regex_search(val.c_str(), res, m_rx);
    if (ret == true) {
        m_handler->OnMatch(res);
    }
    return ret;
}

void
Url::Register()
{
    UrlProcessor *processor = UrlProcessor::GetInstance();      
    if (processor) {
        processor->Register(*this);
    }
}

void
Url::Unregister()
{
    UrlProcessor *processor = UrlProcessor::GetInstance();      
    if (processor) {
        processor->Unregister(*this);
    }
}

UrlProcessor *
UrlProcessor::GetInstance()
{
    static UrlProcessor *m_instance = NULL;
    if (!m_instance) {
        m_instance = new UrlProcessor();
    }
    return m_instance;
}

bool 
UrlProcessor::Match(std::string &val)
{
    std::list<Url>::iterator iter;
    bool ret = false;

    // first match wins

    for (iter = m_urls.begin(); iter != m_urls.end(); ++iter) {
        if ((*iter).Match(val) == true) {
            ret = true;
            break;
        }
    }
    return ret;
}

void 
UrlProcessor::Register(const Url &url)
{
    m_urls.push_back(url);
}

void 
UrlProcessor::Unregister(const Url &url)
{
    m_urls.remove(url);
}


