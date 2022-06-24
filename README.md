# IRC-Server

This realization server operating under the <a href="https://ru.wikipedia.org/wiki/IRC">IRC</a> protocol.
The server works according to the standard ``"RFC 1459"``

### For start

Using ``make`` for compile project. For start server ``./ircserver`` ``port`` ``password``.

Example: 
```bash
~/IRC-Server/ % make
~/IRC-Server/ % ./ircserv 6667 password
```

### For connect

You may use <a href="http://www.kvirc.net/?id=releases&platform=macosx&lang=en">KVIrc</a> or any IRC Client. Also You may use ``telnet`` or any utilites fo connect.

### For work

Server can process the following commands:
 + ``PASS`` - for insert a password.
 + ``NICK`` - for insert a nickname.
 + ``USER`` - for set user_name, host_name, server_hame and real_name.
 + ``PRIVMSG`` - for send a privat message.
 + ``NOTICE`` - for send a notice.
 + ``OPER`` - for set server_operator (only operator_server).
 + ``KILL`` - for "kill" user on a server (only operator_server).
 + ``RESTART`` - for restart a server (only operator_server).
 + ``JOIN`` - for join or create a channel.
 + ``MODE`` - for set mode for a channel(only operator_channel).
 + ``TOPIC`` - for set topic for a channel.
 + ``INVITE`` - for invite users in a channel.
 + ``KICK`` - for kick users from a channel(only operator_channel).
 + ``WHO`` - for get info about users.
 + ``LIST`` - for get info about channels.
 + ``PART`` - for left a channel.
 + ``PING`` - for check a connection.
 + ``QUIT`` - for left a server.
 
 ### Bot
 
Using ``make bot`` for compile project. For start server ``./bot`` ``port`` ``password``.

Example: 
```bash
~/IRC-Server/ % make bot
~/IRC-Server/ % ./bot 6667 password
```

Now You can to send private message for bot and talk with him. He know weather in any city.
