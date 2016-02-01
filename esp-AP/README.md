programed into esp8266 01 unit to act as wifi monitor 
using https://github.com/esp8266/Arduino
TODO web interface that gives current data when connected from webbrowser.
Could add commands using CGI format or buttons

need to add redirection on the on off links.
https://en.wikipedia.org/wiki/URL_redirection

```HTML

<html>
<head>
<meta http-equiv="Refresh" content="0; url=http://www.example.com/" />
</head>
<body>
<p>Please follow <a href="http://www.example.com/">this link</a>.</p>
</body>
</html>

```

looks a good idea.

or

```HTTP

HTTP/1.1 200 ok
Refresh: 0; url=http://www.example.com/
Content-type: text/html
Content-length: 78

Please follow <a href="http://www.example.com/">this link</a>

```
Not sure what is easier with the API give.
