#if !defined(__DJANGOURLS_H__)
#define __DJANGOURLS_H__

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

#include <boost/regex.hpp>
#include <string>
#include <list>

/**
 * Pseudo-Django style URL dispatching based on TR1 regex.
 */

class UrlHandler
{
public:
    virtual ~UrlHandler() {};
    virtual void OnMatch(boost::cmatch &matches) = 0;
private:
};

class Url
{
public:
    Url();
    Url(std::string &re, UrlHandler *handler);
    void SetRe(std::string &re);
    void SetHandler(UrlHandler *handler);
    void Register();
    void Unregister();
    bool Match(std::string &val);
    bool operator == (const Url &rhs)
    {
        return rhs.m_re == m_re && rhs.m_handler == m_handler;
    }
private:
    std::string m_re;
    boost::regex m_rx;
    UrlHandler *m_handler; 
};

class UrlProcessor
{
public:
    static UrlProcessor *GetInstance();
    bool Match(std::string &val);
    void Register(const Url &url);
    void Unregister(const Url &url);
private:
    UrlProcessor() {};
    virtual ~UrlProcessor() {};
    UrlProcessor(UrlProcessor const&); 
    UrlProcessor& operator=(UrlProcessor const&);

    static UrlProcessor* m_instance;
    std::list<Url> m_urls;
}; 

#endif

