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
Solution 1 works ok but I could make the redirect page a string contant as it only needs to say OK and bounce back.

next thing I could do is replace links with buttond?

```HTML
<form method = "get" action = "minimal.cgi">
<input type="submit">Data: <input name="myfield">
</form>

```
but it returns

http://myhost/minimal.cgi?myfield=dddd 

how would "server.on ( "/minimal.cgi", handleButton );" handle the "?myfield=dddd " bit?
