djangourl
=========

Simple C++ classes that wrap boost regex, and invoke a callback on matches, 
similar to django urls.py

To use this code, simply copy djangourls.cpp and djangourls.h into your
project. 

On Linux, you will need the boost regex dev package, on debian/Ubuntu, you
can get it like this:

$ sudo apt-get install libboost-regex-dev

See the test directory for an example. The regular expressions in that
example are pulled from django docs, and explained there. See the URL
https://docs.djangoproject.com/en/dev/topics/http/urls/ for more details.
The example is roughly analogous to the following urls.py:

from django.conf.urls import patterns, url, include

urlpatterns = patterns('',
    (r'^articles/2003/$', 'news.views.special_case_2003'),
    (r'^articles/(\d{4})/$', 'news.views.year_archive'),
    (r'^articles/(\d{4})/(\d{2})/$', 'news.views.month_archive'),
    (r'^articles/(\d{4})/(\d{2})/(\d+)/$', 'news.views.article_detail'),
)

with the exception that in the sample, a single callback function is being
used. Of course, you can declare as many classes/objects that you like to
act as handlers when a match comes in.

