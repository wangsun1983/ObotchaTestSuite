#include <stdio.h>
#include <unistd.h>

#include "http_parser.h"

#include "HttpPacketParser.hpp"
#include "HttpPacketParserImpl.hpp"
#include "TestLog.hpp"
#include "HttpMethod.hpp"
#include "Http.hpp"

using namespace obotcha;

#undef TRUE
#define TRUE 1
#undef FALSE
#define FALSE 0

#define MAX_HEADERS 13
#define MAX_ELEMENT_SIZE 2048
#define MAX_CHUNKS 16

#define MIN(a,b) ((a) < (b) ? (a) : (b))

#define ARRAY_SIZE(x) (sizeof(x) / sizeof(*x))

extern "C" {

    struct message {
        const char *name; // for debugging purposes
        const char *raw;
        int type;
        st(HttpMethod)::Id method;
        int status_code;
        char response_status[MAX_ELEMENT_SIZE];
        char request_path[MAX_ELEMENT_SIZE];
        char request_url[MAX_ELEMENT_SIZE];
        char fragment[MAX_ELEMENT_SIZE];
        char query_string[MAX_ELEMENT_SIZE];
        char body[MAX_ELEMENT_SIZE];
        size_t body_size;
        const char *host;
        const char *userinfo;
        uint16_t port;
        int num_headers;
        enum { NONE=0, FIELD, VALUE } last_header_element;
        char headers [MAX_HEADERS][2][MAX_ELEMENT_SIZE];
        int should_keep_alive;

        int num_chunks;
        int num_chunks_complete;
        int chunk_lengths[MAX_CHUNKS];

        const char *key_value[MAX_ELEMENT_SIZE];
        int key_value_size;

        const char *upgrade; // upgraded body

        unsigned short http_major;
        unsigned short http_minor;
        int content_length;

        int message_begin_cb_called;
        int headers_complete_cb_called;
        int message_complete_cb_called;
        int status_cb_called;
        int message_complete_on_eof;
        int body_is_final;
        int allow_chunked_length;
    };

    static int currently_parsing_eof;

    static struct message messages[5];
    static int num_messages;

 /* * R E Q U E S T S * */
const struct message requests[] =
#define CURL_GET 0
{ {.name= "curl get"
    ,.type= static_cast<int>(st(Http)::PacketType::Request)
    ,.raw= "GET /test HTTP/1.1\r\n"
                 "User-Agent: curl/7.18.0 (i486-pc-linux-gnu) libcurl/7.18.0 OpenSSL/0.9.8g zlib/1.2.3.3 libidn/1.1\r\n"
                 "Host: 0.0.0.0=5000\r\n"
                 "Accept: */*\r\n"
                 "\r\n"
    ,.should_keep_alive= TRUE
    ,.message_complete_on_eof= FALSE
    ,.http_major= 1
    ,.http_minor= 1
    ,.method= st(HttpMethod)::Id::Get
    ,.query_string= ""
    ,.fragment= ""
    ,.request_path= "test"
    ,.request_url= "/test"
    ,.content_length= -1
    ,.num_headers= 3
    ,.headers=
        { { "User-Agent", "curl/7.18.0 (i486-pc-linux-gnu) libcurl/7.18.0 OpenSSL/0.9.8g zlib/1.2.3.3 libidn/1.1" }
        , { "Host", "0.0.0.0=5000" }
        , { "Accept", "*/*" }
        }
    ,.body= ""
    }

#define FIREFOX_GET 1
, {.name= "firefox get"
    ,.type= static_cast<int>(st(Http)::PacketType::Request)
    ,.raw= "GET /favicon.ico HTTP/1.1\r\n"
                 "Host: 0.0.0.0=5000\r\n"
                 "User-Agent: Mozilla/5.0 (X11; U; Linux i686; en-US; rv:1.9) Gecko/2008061015 Firefox/3.0\r\n"
                 "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8\r\n"
                 "Accept-Language: en-us,en;q=0.5\r\n"
                 "Accept-Encoding: gzip,deflate\r\n"
                 "Accept-Charset: ISO-8859-1, utf-8;q=0.7, *;q=0.7\r\n"
                 "Keep-Alive: 300\r\n"
                 "Connection: keep-alive\r\n"
                 "\r\n"
    ,.should_keep_alive= TRUE
    ,.message_complete_on_eof= FALSE
    ,.http_major= 1
    ,.http_minor= 1
    ,.method= st(HttpMethod)::Id::Get
    ,.query_string= ""
    ,.fragment= ""
    ,.request_path= "favicon.ico"
    ,.request_url= "/favicon.ico"
    ,.content_length= -1
    ,.num_headers= 8
    ,.headers=
        { { "Host", "0.0.0.0=5000" }
        , { "User-Agent", "Mozilla/5.0 (X11; U; Linux i686; en-US; rv:1.9) Gecko/2008061015 Firefox/3.0" }
        , { "Accept", "text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8" }
        , { "Accept-Language", "en-us,en;q=0.5" }
        , { "Accept-Encoding", "gzip,deflate" }
        , { "Accept-Charset", "ISO-8859-1, utf-8,*;q=0.7" }
        , { "Keep-Alive", "300" }
        , { "Connection", "keep-alive" }
        }
    ,.body= ""
    }

#define DUMBLUCK 2
, {.name= "dumbluck"
    ,.type= static_cast<int>(st(Http)::PacketType::Request)
    ,.raw= "GET /dumbluck HTTP/1.1\r\n"
                 "aaaaaaaaaaaaa:++++++++++\r\n"
                 "\r\n"
    ,.should_keep_alive= TRUE
    ,.message_complete_on_eof= FALSE
    ,.http_major= 1
    ,.http_minor= 1
    ,.method= st(HttpMethod)::Id::Get
    ,.query_string= ""
    ,.fragment= ""
    ,.request_path= "dumbluck"
    ,.request_url= "/dumbluck"
    ,.content_length= -1
    ,.num_headers= 1
    ,.headers=
        { { "aaaaaaaaaaaaa",    "++++++++++" }
        }
    ,.body= ""
    }

#define FRAGMENT_IN_URI 3
, {.name= "fragment in url"
    ,.type= static_cast<int>(st(Http)::PacketType::Request)
    ,.raw= "GET /forums/1/topics/2375?page=1#posts-17408 HTTP/1.1\r\n"
                 "\r\n"
    ,.should_keep_alive= TRUE
    ,.message_complete_on_eof= FALSE
    ,.http_major= 1
    ,.http_minor= 1
    ,.method= st(HttpMethod)::Id::Get
    ,.query_string= "page=1"
    ,.fragment= "posts-17408"
    ,.request_path= "forums/1/topics/2375"
    /* XXX request url does include fragment? */
    ,.request_url= "/forums/1/topics/2375?page=1#posts-17408"
    ,.content_length= -1
    ,.num_headers= 0
    ,.body= ""
    }

#define GET_NO_HEADERS_NO_BODY 4
, {.name= "get no headers no body"
    ,.type= static_cast<int>(st(Http)::PacketType::Request)
    ,.raw= "GET /get_no_headers_no_body/world HTTP/1.1\r\n"
                 "\r\n"
    ,.should_keep_alive= TRUE
    ,.message_complete_on_eof= FALSE /* would need Connection: close */
    ,.http_major= 1
    ,.http_minor= 1
    ,.method= st(HttpMethod)::Id::Get
    ,.query_string= ""
    ,.fragment= ""
    ,.request_path= "get_no_headers_no_body/world"
    ,.request_url= "/get_no_headers_no_body/world"
    ,.content_length= -1
    ,.num_headers= 0
    ,.body= ""
    }

#define GET_ONE_HEADER_NO_BODY 5
, {.name= "get one header no body"
    ,.type= static_cast<int>(st(Http)::PacketType::Request)
    ,.raw= "GET /get_one_header_no_body HTTP/1.1\r\n"
                 "Accept: */*\r\n"
                 "\r\n"
    ,.should_keep_alive= TRUE
    ,.message_complete_on_eof= FALSE /* would need Connection: close */
    ,.http_major= 1
    ,.http_minor= 1
    ,.method= st(HttpMethod)::Id::Get
    ,.query_string= ""
    ,.fragment= ""
    ,.request_path= "get_one_header_no_body"
    ,.request_url= "/get_one_header_no_body"
    ,.content_length= -1
    ,.num_headers= 1
    ,.headers=
        { { "Accept" , "*/*" }
        }
    ,.body= ""
    }

#define GET_FUNKY_CONTENT_LENGTH 6
, {.name= "get funky content length body hello"
    ,.type= static_cast<int>(st(Http)::PacketType::Request)
    ,.raw= "GET /get_funky_content_length_body_hello HTTP/1.0\r\n"
                 "conTENT-Length: 5\r\n"
                 "\r\n"
                 "HELLO"
    ,.should_keep_alive= FALSE
    ,.message_complete_on_eof= FALSE
    ,.http_major= 1
    ,.http_minor= 0
    ,.method= st(HttpMethod)::Id::Get
    ,.query_string= ""
    ,.fragment= ""
    ,.request_path= "get_funky_content_length_body_hello"
    ,.request_url= "/get_funky_content_length_body_hello"
    ,.content_length= 5
    ,.num_headers= 1
    ,.headers=
        { { "conTENT-Length" , "5" }
        }
    ,.body= "HELLO"
    }

#define POST_IDENTITY_BODY_WORLD 7
, {.name= "post identity body world"
    ,.type= static_cast<int>(st(Http)::PacketType::Request)
    ,.raw= "POST /post_identity_body_world?q=search#hey HTTP/1.1\r\n"
                 "Accept: */*\r\n"
                 "Content-Length: 5\r\n"
                 "\r\n"
                 "World"
    ,.should_keep_alive= TRUE
    ,.message_complete_on_eof= FALSE
    ,.http_major= 1
    ,.http_minor= 1
    ,.method= st(HttpMethod)::Id::Post
    ,.query_string= "q=search"
    ,.fragment= "hey"
    ,.request_path= "post_identity_body_world"
    ,.request_url= "/post_identity_body_world?q=search#hey"
    ,.content_length= 5
    ,.num_headers= 2
    ,.headers=
        { { "Accept", "*/*" }
        , { "Content-Length", "5" }
        }
    ,.body= "World"
    }

#define POST_CHUNKED_ALL_YOUR_BASE 8
, {.name= "post - chunked body: all your base are belong to us"
    ,.type= static_cast<int>(st(Http)::PacketType::Request)
    ,.raw= "POST /post_chunked_all_your_base HTTP/1.1\r\n"
                 "Transfer-Encoding: chunked\r\n"
                 "\r\n"
                 "1e\r\nall your base are belong to us\r\n"
                 "0\r\n"
                 "\r\n"
    ,.should_keep_alive= TRUE
    ,.message_complete_on_eof= FALSE
    ,.http_major= 1
    ,.http_minor= 1
    ,.method= st(HttpMethod)::Id::Post
    ,.query_string= ""
    ,.fragment= ""
    ,.request_path= "post_chunked_all_your_base"
    ,.request_url= "/post_chunked_all_your_base"
    ,.content_length= -1
    ,.num_headers= 1
    ,.headers=
        { { "Transfer-Encoding" , "chunked" }
        }
    ,.body= "all your base are belong to us"
    ,.num_chunks_complete= 2
    ,.chunk_lengths= { 0x1e }
    }

#define TWO_CHUNKS_MULT_ZERO_END 9
, {.name= "two chunks ; triple zero ending"
    ,.type= static_cast<int>(st(Http)::PacketType::Request)
    ,.raw= "POST /two_chunks_mult_zero_end HTTP/1.1\r\n"
                 "Transfer-Encoding: chunked\r\n"
                 "\r\n"
                 "5\r\nhello\r\n"
                 "6\r\n world\r\n"
                 "000\r\n"
                 "\r\n"
    ,.should_keep_alive= TRUE
    ,.message_complete_on_eof= FALSE
    ,.http_major= 1
    ,.http_minor= 1
    ,.method= st(HttpMethod)::Id::Post
    ,.query_string= ""
    ,.fragment= ""
    ,.request_path= "two_chunks_mult_zero_end"
    ,.request_url= "/two_chunks_mult_zero_end"
    ,.content_length= -1
    ,.num_headers= 1
    ,.headers=
        { { "Transfer-Encoding", "chunked" }
        }
    ,.body= "hello world"
    ,.num_chunks_complete= 3
    ,.chunk_lengths= { 5, 6 }
    }

#define CHUNKED_W_TRAILING_HEADERS 10
, {.name= "chunked with trailing headers. blech."
    ,.type= static_cast<int>(st(Http)::PacketType::Request)
    ,.raw= "POST /chunked_w_trailing_headers HTTP/1.1\r\n"
                 "Transfer-Encoding: chunked\r\n"
                 "\r\n"
                 "5\r\nhello\r\n"
                 "6\r\n world\r\n"
                 "0\r\n"
                 "Vary: *\r\n"
                 "Content-Type: text/plain\r\n"
                 "\r\n"
    ,.should_keep_alive= TRUE
    ,.message_complete_on_eof= FALSE
    ,.http_major= 1
    ,.http_minor= 1
    ,.method= st(HttpMethod)::Id::Post
    ,.query_string= ""
    ,.fragment= ""
    ,.request_path= "chunked_w_trailing_headers"
    ,.request_url= "/chunked_w_trailing_headers"
    ,.content_length= -1
    ,.num_headers= 3
    ,.headers=
        { { "Transfer-Encoding",    "chunked" }
        , { "Vary", "*" }
        , { "Content-Type", "text/plain" }
        }
    ,.body= "hello world"
    ,.num_chunks_complete= 3
    ,.chunk_lengths= { 5, 6 }
    }

#define CHUNKED_W_NONSENSE_AFTER_LENGTH 11
, {.name= "with nonsense after the length"
    ,.type= static_cast<int>(st(Http)::PacketType::Request)
    ,.raw= "POST /chunked_w_nonsense_after_length HTTP/1.1\r\n"
                 "Transfer-Encoding: chunked\r\n"
                 "\r\n"
                 "5; ilovew3;whattheluck=aretheseparametersfor\r\nhello\r\n"
                 "6; blahblah; blah\r\n world\r\n"
                 "0\r\n"
                 "\r\n"
    ,.should_keep_alive= TRUE
    ,.message_complete_on_eof= FALSE
    ,.http_major= 1
    ,.http_minor= 1
    ,.method= st(HttpMethod)::Id::Post
    ,.query_string= ""
    ,.fragment= ""
    ,.request_path= "chunked_w_nonsense_after_length"
    ,.request_url= "/chunked_w_nonsense_after_length"
    ,.content_length= -1
    ,.num_headers= 1
    ,.headers=
        { { "Transfer-Encoding", "chunked" }
        }
    ,.body= "hello world"
    ,.num_chunks_complete= 3
    ,.chunk_lengths= { 5, 6 }
    }

#define WITH_QUOTES 12
, {.name= "with quotes"
    ,.type= static_cast<int>(st(Http)::PacketType::Request)
    ,.raw= "GET /with_\"stupid\"_quotes?foo=\"bar\" HTTP/1.1\r\n\r\n"
    ,.should_keep_alive= TRUE
    ,.message_complete_on_eof= FALSE
    ,.http_major= 1
    ,.http_minor= 1
    ,.method= st(HttpMethod)::Id::Get
    ,.query_string= "foo=\"bar\""
    ,.fragment= ""
    ,.request_path= "with_\"stupid\"_quotes"
    ,.request_url= "/with_\"stupid\"_quotes?foo=\"bar\""
    ,.content_length= -1
    ,.num_headers= 0
    ,.headers= { }
    ,.body= ""
    }

#define APACHEBENCH_GET 13
/* The server receiving this request SHOULD NOT wait for EOF
 * to know that content-length == 0.
 * How to represent this in a unit test? message_complete_on_eof
 * Compare with NO_CONTENT_LENGTH_RESPONSE.
 */
, {.name = "apachebench get"
    ,.type= static_cast<int>(st(Http)::PacketType::Request)
    ,.raw= "GET /test HTTP/1.0\r\n"
                 "Host: 0.0.0.0:5000\r\n"
                 "User-Agent: ApacheBench/2.3\r\n"
                 "Accept: */*\r\n\r\n"
    ,.should_keep_alive= FALSE
    ,.message_complete_on_eof= FALSE
    ,.http_major= 1
    ,.http_minor= 0
    ,.method= st(HttpMethod)::Id::Get
    ,.query_string= ""
    ,.fragment= ""
    ,.request_path= "test"
    ,.request_url= "/test"
    ,.content_length= -1
    ,.num_headers= 3
    ,.headers= { { "Host", "0.0.0.0:5000" }
                         , { "User-Agent", "ApacheBench/2.3" }
                         , { "Accept", "*/*" }
                         }
    ,.body= ""
    }

#define QUERY_URL_WITH_QUESTION_MARK_GET 14
/* Some clients include '?' characters in query strings.
 */
, {.name = "query url with question mark"
    ,.type= static_cast<int>(st(Http)::PacketType::Request)
    ,.raw= "GET /test.cgi?foo=bar?baz HTTP/1.1\r\n\r\n"
    ,.should_keep_alive= TRUE
    ,.message_complete_on_eof= FALSE
    ,.http_major= 1
    ,.http_minor= 1
    ,.method= st(HttpMethod)::Id::Get
    ,.query_string= "foo=bar?baz"
    ,.fragment= ""
    ,.request_path= "test.cgi"
    ,.request_url= "/test.cgi?foo=bar?baz"
    ,.content_length= -1
    ,.num_headers= 0
    ,.headers= {}
    ,.body= ""
    }

#define PREFIX_NEWLINE_GET 15
/* Some clients, especially after a POST in a keep-alive connection,
 * will send an extra CRLF before the next request
 */
, {.name = "newline prefix get"
    ,.type= static_cast<int>(st(Http)::PacketType::Request)
    ,.raw= "\r\nGET /test HTTP/1.1\r\n\r\n"
    ,.should_keep_alive= TRUE
    ,.message_complete_on_eof= FALSE
    ,.http_major= 1
    ,.http_minor= 1
    ,.method= st(HttpMethod)::Id::Get
    ,.query_string= ""
    ,.fragment= ""
    ,.request_path= "test"
    ,.request_url= "/test"
    ,.content_length= -1
    ,.num_headers= 0
    ,.headers= { }
    ,.body= ""
    }

#define UPGRADE_REQUEST 16
, {.name = "upgrade request"
    ,.type= static_cast<int>(st(Http)::PacketType::Request)
    ,.raw= "GET /demo HTTP/1.1\r\n"
                 "Host: example.com\r\n"
                 "Connection: Upgrade\r\n"
                 "Sec-WebSocket-Key2: 12998 5 Y3 1    .P00\r\n"
                 "Sec-WebSocket-Protocol: sample\r\n"
                 "Upgrade: WebSocket\r\n"
                 "Sec-WebSocket-Key1: 4 @1    46546xW%0l 1 5\r\n"
                 "Origin: http://example.com\r\n"
                 "\r\n"
                 "Hot diggity dogg"
    ,.should_keep_alive= TRUE
    ,.message_complete_on_eof= FALSE
    ,.http_major= 1
    ,.http_minor= 1
    ,.method= st(HttpMethod)::Id::Get
    ,.query_string= ""
    ,.fragment= ""
    ,.request_path= "demo"
    ,.request_url= "/demo"
    ,.content_length= -1
    ,.num_headers= 7
    ,.upgrade="Hot diggity dogg"
    ,.headers= { { "Host", "example.com" }
                         , { "Connection", "Upgrade" }
                         , { "Sec-WebSocket-Key2", "12998 5 Y3 1    .P00" }
                         , { "Sec-WebSocket-Protocol", "sample" }
                         , { "Upgrade", "WebSocket" }
                         , { "Sec-WebSocket-Key1", "4 @1    46546xW%0l 1 5" }
                         , { "Origin", "http://example.com" }
                         }
    ,.body= ""
    }

#if 0
#define CONNECT_REQUEST 17
, {.name = "connect request"
    ,.type= static_cast<int>(st(Http)::PacketType::Request)
    ,.raw= "CONNECT 0-home0.netscape.com:443 HTTP/1.0\r\n"
                 "User-agent: Mozilla/1.1N\r\n"
                 "Proxy-authorization: basic aGVsbG86d29ybGQ=\r\n"
                 "\r\n"
                 "some data\r\n"
                 "and yet even more data"
    ,.should_keep_alive= FALSE
    ,.message_complete_on_eof= FALSE
    ,.http_major= 1
    ,.http_minor= 0
    ,.method= st(HttpMethod)::Id::Connect
    ,.query_string= ""
    ,.fragment= ""
    ,.request_path= ""
    ,.request_url= "0-home0.netscape.com:443"
    ,.content_length= -1
    ,.num_headers= 2
    ,.upgrade="some data\r\nand yet even more data"
    ,.headers= { { "User-agent", "Mozilla/1.1N" }
                         , { "Proxy-authorization", "basic aGVsbG86d29ybGQ=" }
                         }
    ,.body= ""
    }
#endif

#define REPORT_REQ 18
, {.name= "report request"
    ,.type= static_cast<int>(st(Http)::PacketType::Request)
    ,.raw= "REPORT /test HTTP/1.1\r\n"
                 "\r\n"
    ,.should_keep_alive= TRUE
    ,.message_complete_on_eof= FALSE
    ,.http_major= 1
    ,.http_minor= 1
    ,.method= st(HttpMethod)::Id::Report
    ,.query_string= ""
    ,.fragment= ""
    ,.request_path= "test"
    ,.request_url= "/test"
    ,.content_length= -1
    ,.num_headers= 0
    ,.headers= {}
    ,.body= ""
    }



#define NO_HTTP_VERSION 19
, {.name= "request with no http version"
    ,.type= static_cast<int>(st(Http)::PacketType::Request)
    ,.raw= "GET /\r\n"
                 "\r\n"
    ,.should_keep_alive= FALSE
    ,.message_complete_on_eof= FALSE
    ,.http_major= 0
    ,.http_minor= 9
    ,.method= st(HttpMethod)::Id::Get
    ,.query_string= ""
    ,.fragment= ""
    ,.request_path= ""
    ,.request_url= "/"
    ,.content_length= -1
    ,.num_headers= 0
    ,.headers= {}
    ,.body= ""
    }

#define MSEARCH_REQ 20
, {.name= "m-search request"
    ,.type= static_cast<int>(st(Http)::PacketType::Request)
    ,.raw= "M-SEARCH * HTTP/1.1\r\n"
                 "HOST: 239.255.255.250:1900\r\n"
                 "MAN: \"ssdp:discover\"\r\n"
                 "ST: \"ssdp:all\"\r\n"
                 "\r\n"
    ,.should_keep_alive= TRUE
    ,.message_complete_on_eof= FALSE
    ,.http_major= 1
    ,.http_minor= 1
    ,.method= st(HttpMethod)::Id::Msearch
    ,.query_string= ""
    ,.fragment= ""
    ,.request_path= "*"
    ,.request_url= "*"
    ,.content_length= -1
    ,.num_headers= 3
    ,.headers= { { "HOST", "239.255.255.250:1900" }
                         , { "MAN", "\"ssdp:discover\"" }
                         , { "ST", "\"ssdp:all\"" }
                         }
    ,.body= ""
    }

#if 0
#define LINE_FOLDING_IN_HEADER 21
, {.name= "line folding in header value"
    ,.type= static_cast<int>(st(Http)::PacketType::Request)
    ,.raw= "GET / HTTP/1.1\r\n"
                 "Line1:     abc\r\n"
                 "\tdef\r\n"
                 " ghi\r\n"
                 "\t\tjkl\r\n"
                 "    mno \r\n"
                 "\t \tqrs\r\n"
                 "Line2: \t line2\t\r\n"
                 "Line3:\r\n"
                 " line3\r\n"
                 "Line4: \r\n"
                 " \r\n"
                 "Connection:\r\n"
                 " close\r\n"
                 "\r\n"
    ,.should_keep_alive= FALSE
    ,.message_complete_on_eof= FALSE
    ,.http_major= 1
    ,.http_minor= 1
    ,.method= st(HttpMethod)::Id::Get
    ,.query_string= ""
    ,.fragment= ""
    ,.request_path= ""
    ,.request_url= "/"
    ,.content_length= -1
    ,.num_headers= 5
    ,.headers= { { "Line1", "abc\tdef ghi\t\tjkl    mno \t \tqrs" }
                         , { "Line2", "line2\t" }
                         , { "Line3", "line3" }
                         , { "Line4", "" }
                         , { "Connection", "close" },
                         }
    ,.body= ""
    }
#endif

#define QUERY_TERMINATED_HOST 22
, {.name= "host terminated by a query string"
    ,.type= static_cast<int>(st(Http)::PacketType::Request)
    ,.raw= "GET http://hypnotoad.org?hail=all HTTP/1.1\r\n"
                 "\r\n"
    ,.should_keep_alive= TRUE
    ,.message_complete_on_eof= FALSE
    ,.http_major= 1
    ,.http_minor= 1
    ,.method= st(HttpMethod)::Id::Get
    ,.query_string= "hail=all"
    ,.fragment= ""
    ,.request_path= ""
    ,.request_url= "http://hypnotoad.org?hail=all"
    ,.host= "hypnotoad.org"
    ,.content_length= -1
    ,.num_headers= 0
    ,.headers= { }
    ,.body= ""
    }

#define QUERY_TERMINATED_HOSTPORT 23
, {.name= "host:port terminated by a query string"
    ,.type= static_cast<int>(st(Http)::PacketType::Request)
    ,.raw= "GET http://hypnotoad.org:1234?hail=all HTTP/1.1\r\n"
                 "\r\n"
    ,.should_keep_alive= TRUE
    ,.message_complete_on_eof= FALSE
    ,.http_major= 1
    ,.http_minor= 1
    ,.method= st(HttpMethod)::Id::Get
    ,.query_string= "hail=all"
    ,.fragment= ""
    ,.request_path= ""
    ,.request_url= "http://hypnotoad.org:1234?hail=all"
    ,.host= "hypnotoad.org"
    ,.port= 1234
    ,.content_length= -1
    ,.num_headers= 0
    ,.headers= { }
    ,.body= ""
    }

#define SPACE_TERMINATED_HOSTPORT 24
, {.name= "host:port terminated by a space"
    ,.type= static_cast<int>(st(Http)::PacketType::Request)
    ,.raw= "GET http://hypnotoad.org:1234 HTTP/1.1\r\n"
                 "\r\n"
    ,.should_keep_alive= TRUE
    ,.message_complete_on_eof= FALSE
    ,.http_major= 1
    ,.http_minor= 1
    ,.method= st(HttpMethod)::Id::Get
    ,.query_string= ""
    ,.fragment= ""
    ,.request_path= ""
    ,.request_url= "http://hypnotoad.org:1234"
    ,.host= "hypnotoad.org"
    ,.port= 1234
    ,.content_length= -1
    ,.num_headers= 0
    ,.headers= { }
    ,.body= ""
    }

#define PATCH_REQ 25
, {.name = "PATCH request"
    ,.type= static_cast<int>(st(Http)::PacketType::Request)
    ,.raw= "PATCH /file.txt HTTP/1.1\r\n"
                 "Host: www.example.com\r\n"
                 "Content-Type: application/example\r\n"
                 "If-Match: \"e0023aa4e\"\r\n"
                 "Content-Length: 10\r\n"
                 "\r\n"
                 "cccccccccc"
    ,.should_keep_alive= TRUE
    ,.message_complete_on_eof= FALSE
    ,.http_major= 1
    ,.http_minor= 1
    ,.method= st(HttpMethod)::Id::Patch
    ,.query_string= ""
    ,.fragment= ""
    ,.request_path= "file.txt"
    ,.request_url= "/file.txt"
    ,.content_length= 10
    ,.num_headers= 4
    ,.headers= { { "Host", "www.example.com" }
                         , { "Content-Type", "application/example" }
                         , { "If-Match", "\"e0023aa4e\"" }
                         , { "Content-Length", "10" }
                         }
    ,.body= "cccccccccc"
    }

#define CONNECT_CAPS_REQUEST 26
, {.name = "connect caps request"
    ,.type= static_cast<int>(st(Http)::PacketType::Request)
    ,.raw= "CONNECT HOME0.NETSCAPE.COM:443 HTTP/1.0\r\n"
                 "User-agent: Mozilla/1.1N\r\n"
                 "Proxy-authorization: basic aGVsbG86d29ybGQ=\r\n"
                 "\r\n"
    ,.should_keep_alive= FALSE
    ,.message_complete_on_eof= FALSE
    ,.http_major= 1
    ,.http_minor= 0
    ,.method= st(HttpMethod)::Id::Connect
    ,.query_string= ""
    ,.fragment= ""
    ,.request_path= ""
    ,.request_url= "HOME0.NETSCAPE.COM:443"
    ,.content_length= -1
    ,.num_headers= 2
    ,.upgrade=""
    ,.headers= { { "User-agent", "Mozilla/1.1N" }
                         , { "Proxy-authorization", "basic aGVsbG86d29ybGQ=" }
                         }
    ,.body= ""
    }

#if !HTTP_PARSER_STRICT
#define UTF8_PATH_REQ 27
, {.name= "utf-8 path request"
    ,.type= static_cast<int>(st(Http)::PacketType::Request)
    ,.raw= "GET /δ¶/δt/pope?q=1#narf HTTP/1.1\r\n"
                 "Host: github.com\r\n"
                 "\r\n"
    ,.should_keep_alive= TRUE
    ,.message_complete_on_eof= FALSE
    ,.http_major= 1
    ,.http_minor= 1
    ,.method= st(HttpMethod)::Id::Get
    ,.query_string= "q=1"
    ,.fragment= "narf"
    ,.request_path= "δ¶/δt/pope"
    ,.request_url= "/δ¶/δt/pope?q=1#narf"
    ,.content_length= -1
    ,.num_headers= 1
    ,.headers= { {"Host", "github.com" }
                         }
    ,.body= ""
    }

#define HOSTNAME_UNDERSCORE 28
, {.name = "hostname underscore"
    ,.type= static_cast<int>(st(Http)::PacketType::Request)
    ,.raw= "CONNECT home_0.netscape.com:443 HTTP/1.0\r\n"
                 "User-agent: Mozilla/1.1N\r\n"
                 "Proxy-authorization: basic aGVsbG86d29ybGQ=\r\n"
                 "\r\n"
    ,.should_keep_alive= FALSE
    ,.message_complete_on_eof= FALSE
    ,.http_major= 1
    ,.http_minor= 0
    ,.method= st(HttpMethod)::Id::Connect
    ,.query_string= ""
    ,.fragment= ""
    ,.request_path= ""
    ,.request_url= "home_0.netscape.com:443"
    ,.content_length= -1
    ,.num_headers= 2
    ,.upgrade=""
    ,.headers= { { "User-agent", "Mozilla/1.1N" }
                         , { "Proxy-authorization", "basic aGVsbG86d29ybGQ=" }
                         }
    ,.body= ""
    }
#endif    /* !HTTP_PARSER_STRICT */

/* see https://github.com/ry/http-parser/issues/47 */
#if 0
#define EAT_TRAILING_CRLF_NO_CONNECTION_CLOSE 29
, {.name = "eat CRLF between requests, no \"Connection: close\" header"
    ,.raw= "POST / HTTP/1.1\r\n"
                 "Host: www.example.com\r\n"
                 "\r\n"
                 "Content-Length: 4\r\n"
                 "\r\n"
                 "q=42\r\n" /* note the trailing CRLF */
    ,.type= static_cast<int>(st(Http)::PacketType::Request)
    ,.should_keep_alive= TRUE
    ,.message_complete_on_eof= FALSE
    ,.http_major= 1
    ,.http_minor= 1
    ,.method= st(HttpMethod)::Id::Post
    ,.query_string= ""
    ,.fragment= ""
    ,.request_path= ""
    ,.request_url= "/"
    ,.content_length= 4
    ,.num_headers= 3
    ,.upgrade= 0
    ,.headers= { { "Host", "www.example.com" }
                         , { "Content-Type", "application/x-www-form-urlencoded" }
                         , { "Content-Length", "4" }
                         }
    ,.body= "q=42"
    ,.key_value={"q","42"}
    ,.key_value_size = 2
    }
#endif
/* see https://github.com/ry/http-parser/issues/47 */
#define EAT_TRAILING_CRLF_WITH_CONNECTION_CLOSE 30
, {.name = "eat CRLF between requests even if \"Connection: close\" is set"
    ,.raw= "POST / HTTP/1.1\r\n"
                 "Host: www.example.com\r\n"
                 "Content-Type: application/x-www-form-urlencoded\r\n"
                 "Content-Length: 4\r\n"
                 "Connection: close\r\n"
                 "\r\n"
                 "q=42\r\n" /* note the trailing CRLF */
    ,.type= static_cast<int>(st(Http)::PacketType::Request)
    ,.should_keep_alive= FALSE
    ,.message_complete_on_eof= FALSE /* input buffer isn't empty when on_message_complete is called */
    ,.http_major= 1
    ,.http_minor= 1
    ,.method= st(HttpMethod)::Id::Post
    ,.query_string= ""
    ,.fragment= ""
    ,.request_path= ""
    ,.request_url= "/"
    ,.content_length= 4
    ,.num_headers= 4
    ,.upgrade= 0
    ,.headers= { { "Host", "www.example.com" }
                         , { "Content-Type", "application/x-www-form-urlencoded" }
                         , { "Content-Length", "4" }
                         , { "Connection", "close" }
                         }
    ,.body= ""
    ,.key_value={"q","42"}
    ,.key_value_size = 2
    }

#define PURGE_REQ 31
, {.name = "PURGE request"
    ,.type= static_cast<int>(st(Http)::PacketType::Request)
    ,.raw= "PURGE /file.txt HTTP/1.1\r\n"
                 "Host: www.example.com\r\n"
                 "\r\n"
    ,.should_keep_alive= TRUE
    ,.message_complete_on_eof= FALSE
    ,.http_major= 1
    ,.http_minor= 1
    ,.method= st(HttpMethod)::Id::Purge
    ,.query_string= ""
    ,.fragment= ""
    ,.request_path= "file.txt"
    ,.request_url= "/file.txt"
    ,.content_length= -1
    ,.num_headers= 1
    ,.headers= { { "Host", "www.example.com" } }
    ,.body= ""
    }

#define SEARCH_REQ 32
, {.name = "SEARCH request"
    ,.type= static_cast<int>(st(Http)::PacketType::Request)
    ,.raw= "SEARCH / HTTP/1.1\r\n"
                 "Host: www.example.com\r\n"
                 "\r\n"
    ,.should_keep_alive= TRUE
    ,.message_complete_on_eof= FALSE
    ,.http_major= 1
    ,.http_minor= 1
    ,.method= st(HttpMethod)::Id::Search
    ,.query_string= ""
    ,.fragment= ""
    ,.request_path= ""
    ,.request_url= "/"
    ,.content_length= -1
    ,.num_headers= 1
    ,.headers= { { "Host", "www.example.com" } }
    ,.body= ""
    }

#define PROXY_WITH_BASIC_AUTH 33
, {.name= "host:port and basic_auth"
    ,.type= static_cast<int>(st(Http)::PacketType::Request)
    ,.raw= "GET http://a%12:b!&*$@hypnotoad.org:1234/toto HTTP/1.1\r\n"
                 "\r\n"
    ,.should_keep_alive= TRUE
    ,.message_complete_on_eof= FALSE
    ,.http_major= 1
    ,.http_minor= 1
    ,.method= st(HttpMethod)::Id::Get
    ,.fragment= ""
    ,.request_path= "toto"
    ,.request_url= "http://a%12:b!&*$@hypnotoad.org:1234/toto"
    ,.host= "hypnotoad.org"
    ,.userinfo= "a%12:b!&*$"
    ,.port= 1234
    ,.content_length= -1
    ,.num_headers= 0
    ,.headers= { }
    ,.body= ""
    }
#if 0
#define LINE_FOLDING_IN_HEADER_WITH_LF 34
, {.name= "line folding in header value"
    ,.type= static_cast<int>(st(Http)::PacketType::Request)
    ,.raw= "GET / HTTP/1.1\n"
                 "Line1:     abc\n"
                 "\tdef\n"
                 " ghi\n"
                 "\t\tjkl\n"
                 "    mno \n"
                 "\t \tqrs\n"
                 "Line2: \t line2\t\n"
                 "Line3:\n"
                 " line3\n"
                 "Line4: \n"
                 " \n"
                 "Connection:\n"
                 " close\n"
                 "\n"
    ,.should_keep_alive= FALSE
    ,.message_complete_on_eof= FALSE
    ,.http_major= 1
    ,.http_minor= 1
    ,.method= st(HttpMethod)::Id::Get
    ,.query_string= ""
    ,.fragment= ""
    ,.request_path= ""
    ,.request_url= "/"
    ,.content_length= -1
    ,.num_headers= 5
    ,.headers= { { "Line1", "abc\tdef ghi\t\tjkl    mno \t \tqrs" }
                         , { "Line2", "line2\t" }
                         , { "Line3", "line3" }
                         , { "Line4", "" }
                         , { "Connection", "close" },
                         }
    ,.body= ""
    }
#endif

#define CONNECTION_MULTI 35
, {.name = "multiple connection header values with folding"
    ,.type= static_cast<int>(st(Http)::PacketType::Request)
    ,.raw= "GET /demo HTTP/1.1\r\n"
                 "Host: example.com\r\n"
                 "Connection: Something,\r\n"
                 " Upgrade, ,Keep-Alive\r\n"
                 "Sec-WebSocket-Key2: 12998 5 Y3 1    .P00\r\n"
                 "Sec-WebSocket-Protocol: sample\r\n"
                 "Upgrade: WebSocket\r\n"
                 "Sec-WebSocket-Key1: 4 @1    46546xW%0l 1 5\r\n"
                 "Origin: http://example.com\r\n"
                 "\r\n"
                 "Hot diggity dogg"
    ,.should_keep_alive= TRUE
    ,.message_complete_on_eof= FALSE
    ,.http_major= 1
    ,.http_minor= 1
    ,.method= st(HttpMethod)::Id::Get
    ,.query_string= ""
    ,.fragment= ""
    ,.request_path= "demo"
    ,.request_url= "/demo"
    ,.content_length= -1
    ,.num_headers= 7
    ,.upgrade="Hot diggity dogg"
    ,.headers= { { "Host", "example.com" }
                         , { "Connection", "Something,Upgrade, ,Keep-Alive" }
                         , { "Sec-WebSocket-Key2", "12998 5 Y3 1    .P00" }
                         , { "Sec-WebSocket-Protocol", "sample" }
                         , { "Upgrade", "WebSocket" }
                         , { "Sec-WebSocket-Key1", "4 @1    46546xW%0l 1 5" }
                         , { "Origin", "http://example.com" }
                         }
    ,.body= ""
    }

#define CONNECTION_MULTI_LWS 36
, {.name = "multiple connection header values with folding and lws"
    ,.type= static_cast<int>(st(Http)::PacketType::Request)
    ,.raw= "GET /demo HTTP/1.1\r\n"
                 "Connection: keep-alive, upgrade\r\n"
                 "Upgrade: WebSocket\r\n"
                 "\r\n"
                 "Hot diggity dogg"
    ,.should_keep_alive= TRUE
    ,.message_complete_on_eof= FALSE
    ,.http_major= 1
    ,.http_minor= 1
    ,.method= st(HttpMethod)::Id::Get
    ,.query_string= ""
    ,.fragment= ""
    ,.request_path= "demo"
    ,.request_url= "/demo"
    ,.content_length= -1
    ,.num_headers= 2
    ,.upgrade="Hot diggity dogg"
    ,.headers= { { "Connection", "keep-alive, upgrade" }
                         , { "Upgrade", "WebSocket" }
                         }
    ,.body= ""
    }

#define CONNECTION_MULTI_LWS_CRLF 37
, {.name = "multiple connection header values with folding and lws"
    ,.type= static_cast<int>(st(Http)::PacketType::Request)
    ,.raw= "GET /demo HTTP/1.1\r\n"
                 "Connection: keep-alive, \r\n upgrade\r\n"
                 "Upgrade: WebSocket\r\n"
                 "\r\n"
                 "Hot diggity dogg"
    ,.should_keep_alive= TRUE
    ,.message_complete_on_eof= FALSE
    ,.http_major= 1
    ,.http_minor= 1
    ,.method= st(HttpMethod)::Id::Get
    ,.query_string= ""
    ,.fragment= ""
    ,.request_path= "demo"
    ,.request_url= "/demo"
    ,.content_length= -1
    ,.num_headers= 2
    ,.upgrade="Hot diggity dogg"
    ,.headers= { { "Connection", "keep-alive, upgrade" }
                         , { "Upgrade", "WebSocket" }
                         }
    ,.body= ""
    }

#define UPGRADE_POST_REQUEST 38
, {.name = "upgrade post request"
    ,.type= static_cast<int>(st(Http)::PacketType::Request)
    ,.raw= "POST /demo HTTP/1.1\r\n"
                 "Host: example.com\r\n"
                 "Connection: Upgrade\r\n"
                 "Upgrade: HTTP/2.0\r\n"
                 "Content-Length: 15\r\n"
                 "\r\n"
                 "sweet post body"
                 "Hot diggity dogg"
    ,.should_keep_alive= TRUE
    ,.message_complete_on_eof= FALSE
    ,.http_major= 1
    ,.http_minor= 1
    ,.method= st(HttpMethod)::Id::Post
    ,.request_path= "demo"
    ,.request_url= "/demo"
    ,.content_length= 15
    ,.num_headers= 4
    ,.upgrade="Hot diggity dogg"
    ,.headers= { { "Host", "example.com" }
                         , { "Connection", "Upgrade" }
                         , { "Upgrade", "HTTP/2.0" }
                         , { "Content-Length", "15" }
                         }
    ,.body= "sweet post body"
    }

#if 0
#define CONNECT_WITH_BODY_REQUEST 39
, {.name = "connect with body request"
    ,.type= static_cast<int>(st(Http)::PacketType::Request)
    ,.raw= "CONNECT foo.bar.com:443 HTTP/1.0\r\n"
                 "User-agent: Mozilla/1.1N\r\n"
                 "Proxy-authorization: basic aGVsbG86d29ybGQ=\r\n"
                 "Content-Length: 10\r\n"
                 "\r\n"
                 "blarfcicle"
    ,.should_keep_alive= FALSE
    ,.message_complete_on_eof= FALSE
    ,.http_major= 1
    ,.http_minor= 0
    ,.method= st(HttpMethod)::Id::Connect
    ,.request_url= "foo.bar.com:443"
    ,.content_length= 10
    ,.num_headers= 3
    ,.upgrade="blarfcicle"
    ,.headers= { { "User-agent", "Mozilla/1.1N" }
                         , { "Proxy-authorization", "basic aGVsbG86d29ybGQ=" }
                         , { "Content-Length", "10" }
                         }
    ,.body= ""
    }
#endif

/* Examples from the Internet draft for LINK/UNLINK methods:
 * https://tools.ietf.org/id/draft-snell-link-method-01.html#rfc.section.5
 */

#define LINK_REQUEST 40
, {.name = "link request"
    ,.type= static_cast<int>(st(Http)::PacketType::Request)
    ,.raw= "LINK /images/my_dog.jpg HTTP/1.1\r\n"
                 "Host: example.com\r\n"
                 "Link: <http://example.com/profiles/joe>; rel=\"tag\"\r\n"
                 "Link: <http://example.com/profiles/sally>; rel=\"tag\"\r\n"
                 "\r\n"
    ,.should_keep_alive= TRUE
    ,.message_complete_on_eof= FALSE
    ,.http_major= 1
    ,.http_minor= 1
    ,.method= st(HttpMethod)::Id::Link
    ,.request_path= "images/my_dog.jpg"
    ,.request_url= "/images/my_dog.jpg"
    ,.query_string= ""
    ,.fragment= ""
    ,.content_length= -1
    ,.num_headers= 3
    ,.headers= { { "Host", "example.com" }
                         , { "Link", "<http://example.com/profiles/joe>; rel=\"tag\"" }
             , { "Link", "<http://example.com/profiles/sally>; rel=\"tag\"" }
                         }
    ,.body= ""
    }

#define UNLINK_REQUEST 41
, {.name = "unlink request"
    ,.type= static_cast<int>(st(Http)::PacketType::Request)
    ,.raw= "UNLINK /images/my_dog.jpg HTTP/1.1\r\n"
                 "Host: example.com\r\n"
                 "Link: <http://example.com/profiles/sally>; rel=\"tag\"\r\n"
                 "\r\n"
    ,.should_keep_alive= TRUE
    ,.message_complete_on_eof= FALSE
    ,.http_major= 1
    ,.http_minor= 1
    ,.method= st(HttpMethod)::Id::Unlink
    ,.request_path= "images/my_dog.jpg"
    ,.request_url= "/images/my_dog.jpg"
    ,.query_string= ""
    ,.fragment= ""
    ,.content_length= -1
    ,.num_headers= 2
    ,.headers= { { "Host", "example.com" }
             , { "Link", "<http://example.com/profiles/sally>; rel=\"tag\"" }
                         }
    ,.body= ""
    }

#define SOURCE_REQUEST 42
, {.name = "source request"
    ,.type= static_cast<int>(st(Http)::PacketType::Request)
    ,.raw= "SOURCE /music/sweet/music HTTP/1.1\r\n"
                 "Host: example.com\r\n"
                 "\r\n"
    ,.should_keep_alive= TRUE
    ,.message_complete_on_eof= FALSE
    ,.http_major= 1
    ,.http_minor= 1
    ,.method= st(HttpMethod)::Id::Source
    ,.request_path= "music/sweet/music"
    ,.request_url= "/music/sweet/music"
    ,.query_string= ""
    ,.fragment= ""
    ,.content_length= -1
    ,.num_headers= 1
    ,.headers= { { "Host", "example.com" } }
    ,.body= ""
    }

#define SOURCE_ICE_REQUEST 43
, {.name = "source request"
    ,.type= static_cast<int>(st(Http)::PacketType::Request)
    ,.raw= "SOURCE /music/sweet/music ICE/1.0\r\n"
                 "Host: example.com\r\n"
                 "\r\n"
    ,.should_keep_alive= FALSE
    ,.message_complete_on_eof= FALSE
    ,.http_major= 1
    ,.http_minor= 0
    ,.method= st(HttpMethod)::Id::Source
    ,.request_path= "music/sweet/music"
    ,.request_url= "/music/sweet/music"
    ,.query_string= ""
    ,.fragment= ""
    ,.content_length= -1
    ,.num_headers= 1
    ,.headers= { { "Host", "example.com" } }
    ,.body= ""
    }

#define POST_MULTI_TE_LAST_CHUNKED 44
, {.name= "post - multi coding transfer-encoding chunked body"
    ,.type= static_cast<int>(st(Http)::PacketType::Request)
    ,.raw= "POST / HTTP/1.1\r\n"
                 "Transfer-Encoding: deflate, chunked\r\n"
                 "\r\n"
                 "1e\r\nall your base are belong to us\r\n"
                 "0\r\n"
                 "\r\n"
    ,.should_keep_alive= TRUE
    ,.message_complete_on_eof= FALSE
    ,.http_major= 1
    ,.http_minor= 1
    ,.method= st(HttpMethod)::Id::Post
    ,.query_string= ""
    ,.fragment= ""
    ,.request_path= ""
    ,.request_url= "/"
    ,.content_length= -1
    ,.num_headers= 1
    ,.headers=
        { { "Transfer-Encoding" , "deflate, chunked" }
        }
    ,.body= "all your base are belong to us"
    ,.num_chunks_complete= 2
    ,.chunk_lengths= { 0x1e }
    }

#define POST_MULTI_LINE_TE_LAST_CHUNKED 45
, {.name= "post - multi line coding transfer-encoding chunked body"
    ,.type= static_cast<int>(st(Http)::PacketType::Request)
    ,.raw= "POST / HTTP/1.1\r\n"
                 "Transfer-Encoding: deflate,\r\n"
                 " chunked\r\n"
                 "\r\n"
                 "1e\r\nall your base are belong to us\r\n"
                 "0\r\n"
                 "\r\n"
    ,.should_keep_alive= TRUE
    ,.message_complete_on_eof= FALSE
    ,.http_major= 1
    ,.http_minor= 1
    ,.method= st(HttpMethod)::Id::Post
    ,.query_string= ""
    ,.fragment= ""
    ,.request_path= ""
    ,.request_url= "/"
    ,.content_length= -1
    ,.num_headers= 1
    ,.headers=
        { { "Transfer-Encoding" , "deflate, chunked" }
        }
    ,.body= "all your base are belong to us"
    ,.num_chunks_complete= 2
    ,.chunk_lengths= { 0x1e }
    }

#define CHUNKED_CONTENT_LENGTH 46
, {.name= "chunked with content-length set, allow_chunked_length flag is set"
    ,.type= static_cast<int>(st(Http)::PacketType::Request)
    ,.raw= "POST /chunked_w_content_length HTTP/1.1\r\n"
                 "Content-Length: 10\r\n"
                 "Transfer-Encoding: chunked\r\n"
                 "\r\n"
                 "5; ilovew3;whattheluck=aretheseparametersfor\r\nhello\r\n"
                 "6; blahblah; blah\r\n world\r\n"
                 "0\r\n"
                 "\r\n"
    ,.allow_chunked_length = 1
    ,.should_keep_alive= TRUE
    ,.message_complete_on_eof= FALSE
    ,.http_major= 1
    ,.http_minor= 1
    ,.method= st(HttpMethod)::Id::Post
    ,.query_string= ""
    ,.fragment= ""
    ,.request_path= "chunked_w_content_length"
    ,.request_url= "/chunked_w_content_length"
    ,.content_length= 10
    ,.num_headers= 2
    ,.headers={ { "Content-Length", "10"}
                        , { "Transfer-Encoding", "chunked" }
    }
    ,.body= "hello world"
    ,.num_chunks_complete= 3
    ,.chunk_lengths= { 5, 6 }
    }
};
}

void testHttpParse() {
    //struct message requests
    int size = sizeof(requests)/sizeof(struct message);
    printf("size is %d \n",size);
    for(int turn = 0; turn < 2;turn++) {
        for(int i = 0;i<size;i++) {
            //printf("////HttpPacketParser start %d ////\n",i);
            HttpPacketParserImpl parser = HttpPacketParserImpl::New();
            struct message msg = requests[i];
            //printf("turn is %d msg is %s \n",turn,msg.raw);
            ArrayList<HttpPacket> packets = ArrayList<HttpPacket>::New();
            if(turn == 0) {
                parser->pushData(ByteArray::New((byte *)msg.raw,strlen(msg.raw)));
                packets = parser->doParse();
            } else {
                int index = 0;
                for(;index<strlen(msg.raw);index++) {
                  ByteArray data = ByteArray::New(1);
                  data[0] = (byte)msg.raw[index];
                  parser->pushData(data);
                  auto result = parser->doParse();
                  if(result != nullptr && result->size() != 0) {
                    packets->add(result);
                  }
                }
            }
            
            //check size
            if(packets->size() != 1) {
                TEST_FAIL("HttpPacketParse CheckSize failed,packet size is %d",packets->size());
                continue;
            }

            HttpPacket packet = packets->get(0);
            HttpEntity entity = packet->getEntity();
            HttpHeader header = packet->getHeader();

            //check Type
            if(static_cast<int>(header->getType()) != msg.type) {
                TEST_FAIL("HttpPacketParse CheckType failed,msg.type is %d,parse result is %d",msg.type,header->getType());
                continue;
            }

            //check method
            if(header->getMethod() != msg.method) {
                TEST_FAIL("HttpPacketParse CheckMethod failed,msg.method is %d,parse result is %d",msg.method,header->getMethod());
                continue;
            }

            //check request url
            if(strlen(msg.request_url) > 0) {
                HttpUrl url = header->getUrl();
                String rawDataUrl = url->getRawUrl();
                if(rawDataUrl == nullptr || !rawDataUrl->sameAs(msg.request_url)) {
                    TEST_FAIL("HttpPacketParse CheckRequestUrl failed,msg.request_url is %s,parse result is %s",msg.request_url,rawDataUrl->toChars());
                    TEST_FAIL("HttpPacketParse CheckRequestUrl failed,msg.request_url size is %zu,parse result is %d",strlen(msg.request_url),rawDataUrl->size());
                    continue;
                }
            }

            //check path
            if(strlen(msg.request_path) > 0) {
                HttpUrl url = header->getUrl();
                String path = url->getPath();

                String f1 = String::New(msg.request_path);
                //path does not contain /
                //if(f1->size() != 1) {
                //    f1 = String::New("/")->append(f1);
                //}

                if(path == nullptr || !path->equals(f1)) {
                    TEST_FAIL("HttpPacketParse CheckPath failed,msg.path is [%s],parse result is [%s]",msg.request_path,f1->toChars());
                    continue;
                }
            }

            //fragment
            if(strlen(msg.fragment) > 0) {
                HttpUrl url = header->getUrl();
                String fragment = url->getFragment();
                if(fragment == nullptr || !fragment->sameAs(msg.fragment)) {
                    TEST_FAIL("HttpPacketParse CheckFragment failed,msg.request_path is %s,parse result is %s",msg.fragment,fragment->toChars());
                    continue;
                }
            }

            //check query_string
            if(strlen(msg.query_string) > 0) {
                HttpUrl url = header->getUrl();
                String rawQuery = url->getRawQuery();
                
                if(rawQuery == nullptr || !rawQuery->sameAs(msg.query_string)) {
                    TEST_FAIL("HttpPacketParse CheckQuery failed,msg.query_string is %s,parse result is %s",msg.query_string,rawQuery->toChars());
                    continue;
                }
            }

            //check body
            if(strlen(msg.body) > 0) {
                String content = nullptr;
                if(msg.num_chunks_complete != 0) {
                  content = entity->getChunk()->getData()->toString();
                } else {
                  content = entity->getContent()->toString();
                }

                if(content == nullptr || !content->sameAs(msg.body)) {
                    TEST_FAIL("HttpPacketParse CheckBody failed,msg.body is %s,parse result is %s",msg.body,content->toChars());
                    continue;
                }
            }

            //check host
            if(msg.host != nullptr) {
                HttpUrl url = header->getUrl();
                String host = url->getHost();
                if(host == nullptr || !host->sameAs(msg.host)) {
                    TEST_FAIL("HttpPacketParse CheckHost failed,msg.host is %s,parse result is %s",msg.host,host->toChars());
                    continue;
                }
            }

            //check userinfo
            if(msg.userinfo != nullptr) {
                HttpUrl url = header->getUrl();
                String username = url->getUser();
                String password = url->getPassword();
                String userInfo = username->append(":")->append(password);
                if(!userInfo->sameAs(msg.userinfo)) {
                    TEST_FAIL("HttpPacketParse CheckUserInfo failed,msg.userinfo is %s,parse result is %s",msg.userinfo,userInfo->toChars());
                    continue;
                }
            }

            //check headers
            int num_headers = msg.num_headers;
            for(int i = 0;i<num_headers;i++) {
                String key = String::New(msg.headers[i][0]);
                String value = String::New(msg.headers[i][1]);
                String fValue = packet->getHeader()->get(key->toLowerCase());
                if(fValue == nullptr && !key->equalsIgnoreCase("Link")) {
                    //maybe it is a trailing_headers
                    HttpChunk chunk = packet->getEntity()->getChunk();
                    if(chunk != nullptr) {
                        HttpHeader h = chunk->getTrailingHeader();
                        if(h != nullptr) {
                            fValue = h->get(key->toLowerCase());
                        }
                    }

                    if(fValue == nullptr) {
                        TEST_FAIL("HttpPacketParser CheckHeader Fail,packet value is null,key is %s",key->toChars());
                    }
                    continue;
                }
                if(key->equalsIgnoreCase("Keep-Alive")) {
                    int timeout = packet->getHeader()->getKeepAlive()->getTimeout();
                    if(timeout != value->toBasicInt()) {
                        TEST_FAIL("HttpPacketParser CheckHeader Keep-Alive,msg.key is %s,msg.value is %s,parse value is %d",
                                                              key->toChars(),value->toChars(),timeout);
                    }
                } else if(key->equalsIgnoreCase("Link")) {
                    ArrayList<HttpHeaderLink> links = packet->getHeader()->getLinks();
                    HttpHeaderLink link = links->removeAt(0);
                    if(!value->equalsIgnoreCase(link->toString())) {
                        TEST_FAIL("HttpPacketParser CheckHeader Link,msg.key is %s,msg.value is %s,parse value is %s",
                                                              key->toChars(),value->toChars(),link->toString()->toChars());
                    }
                } else if(!fValue->trimAll()->equals(value->trimAll())) {
                    TEST_FAIL("HttpPacketParser CheckHeader,msg.key is %s,msg.value is %s,parse value is %s",
                                                              key->toChars(),value->toChars(),fValue->toChars());
                    continue;
                }
            }

            //TODO:check chunk

            //check key_value
            if(msg.key_value_size > 0) {
                String content = entity->getContent()->toString();
                HttpUrlEncodedValue encodeValue = HttpUrlEncodedValue::New(entity->getContent()->toString());
                HashMap<String,String> map = encodeValue->getValues();
                if(map == nullptr) {
                    TEST_FAIL("HttpPacketParser CheckKeyValue,parse EncodedKeyValues size is 0");
                    continue;
                }

                int count = 0;
                for(int i = 0;i < msg.key_value_size;i++) {
                    const char *key = msg.key_value[i];
                    i++;
                    const char *value = msg.key_value[i];

                    String findValue = map->get(String::New(key));
                    if(!findValue->sameAs(value)) {
                        TEST_FAIL("HttpPacketParser CheckKeyValue Fail,parsed key is %s,parser value is %s",
                                    key,findValue->toChars());
                    }
                    count++;
                }
            }


            //check upgrade
            //if(msg.upgrade != nullptr && strlen(msg.upgrade) > 0) {
            //    String upgrade = packet->getEntity()->getContent()->toString();
            //    if(upgrade == nullptr || !upgrade->equals(msg.upgrade)) {
            //      TEST_FAIL("HttpPacketParse CheckUpgrade failed,msg.upgrade is %s,parse result is %s",msg.upgrade,upgrade->toChars());
            //      continue;
            //    }
            //}

            //check http major version
            HttpHeaderVersion ver = header->getVersion();
            if(ver == nullptr) {
                TEST_FAIL("HttpPacketParse CheckVersion failed,version is null");
                continue;
            }

            if(ver->getMajorVer() != msg.http_major) {
               TEST_FAIL("HttpPacketParse CheckMajorVersion failed,Msg.http_major is %d,parse major version is %d",msg.http_major,ver->getMajorVer());
               continue;
            }

            if(ver->getMinorVer() != msg.http_minor) {
               TEST_FAIL("HttpPacketParse CheckMinorVersion failed,Msg.http_minor is %d,parse minor version is %d",msg.http_major,ver->getMajorVer());
               continue;
            }
        }
    }

    TEST_OK("HttpRequestParser BaseTest case100");
                    
}
