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

/**
 * Constructor.
 */

Url::Url()
{
}


/**
 * Constructor.
 *
 * @param[in] re regular expression 
 *
 * @param[in] handler an instance of UrlHandler, called if there is a match.
 */

Url::Url(std::string &re, UrlHandler *handler)
{
    SetRe(re);
    SetHandler(handler);
}


/**
 * Set the handler to be called on a match. Similar to method portion of
 * urls.py entry.
 * 
 * @param[in] handler an instance of UrlHandler, called if there is a match.
 */

void
Url::SetHandler(UrlHandler *handler)
{
    m_handler = handler;
}


/**
 * Set the regular expression.
 *
 * @param[in] re regular expression that this URL tries to match.
 */

void
Url::SetRe(std::string &re)
{
    m_re = re;
    m_rx.assign(re, boost::regex_constants::icase);  // compile the regex
}


/**
 * Perform a match operation and invoke corresponding function if found.
 *
 * @param[in] val the string to match.
 */

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


/**
 * Add the URL to the list checked by the URL processor.
 */

void
Url::Register()
{
    UrlProcessor *processor = UrlProcessor::GetInstance();      
    if (processor) {
        processor->Register(*this);
    }
}


/**
 * Remove the URL from the list checked by the URL processor.
 */

void
Url::Unregister()
{
    UrlProcessor *processor = UrlProcessor::GetInstance();      
    if (processor) {
        processor->Unregister(*this);
    }
}


/**
 * Get the UrlProcessor singleton.
 *
 * @return UrlProcessor instance (NULL if couldn't create).
 */

UrlProcessor *
UrlProcessor::GetInstance()
{
    static UrlProcessor *m_instance = NULL;
    if (!m_instance) {
        m_instance = new UrlProcessor();
    }
    return m_instance;
}


/**
 * Walk the list of URLs and stop when a match is found, or EOL
 *
 * @param[in] val pattern to match.
 *
 * @return if a match is found, True, else False.
 */

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


/**
 * Push URL to end of list checked by processor.
 *
 * @param[in] url Url object to be checked.
 */
 
void 
UrlProcessor::Register(const Url &url)
{
    m_urls.push_back(url);
}


/**
 * Remove URL from list of those checked by processor.
 *
 * @param[in] url Url object to be removed.
 */

void 
UrlProcessor::Unregister(const Url &url)
{
    m_urls.remove(url);
}

