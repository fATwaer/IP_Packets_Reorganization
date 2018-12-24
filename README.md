# IP_Packets_Reorganization
FreeBSD Implementation

## Platform
``` 
x64 GNU/Linux
gcc version 8.2.1 
Code::Blocks 17.12
```
## Usage

``` bash

[compile]
$ make

[server]
# no delay
$ ./pktreorg -s
# delay 1s
$ ./pktreorg -d 1 -s


[client]
$./pktreorg -c 127.0.0.1 -p 6777


```



## Souce File Layout

``` 
├── bin
│   └── Debug
│       └── FreeBSDPacketsReorganization
├── client.c
├── config
│   └── config
├── FreeBSDPacketsReorganization.cbp
├── FreeBSDPacketsReorganization.depend
├── FreeBSDPacketsReorganization.layout
├── inc
│   ├── client.h
│   ├── ipf_opt.h
│   ├── ip_packet.h
│   ├── ipq.h
│   ├── ipq_opt.h
│   ├── ip_queue.h
│   ├── netpkt.h
│   ├── paser.h
│   ├── server.h
│   └── unit_test.h
├── ipf_opt.c
├── ipq_opt.c
├── lib
│   ├── _color_print.h
│   ├── lib.h
│   └── types.h
├── log
│   └── server.log
├── main.c
├── Makefile
├── netpkt.c
├── paser.c
├── pktreorg
├── README.md
├── server.c
├── text
│   └── server.file
├── unit_test.c
└── utility.c


```


## TODO

```
[x] unit test: fragment reorganization

[x] ip pakcet struct for passing network 
	(with associated function)

[x] drop packet when time out
	- [x] time parmeter

[] error usage information print

[] file config support

[] create thread to interact with user

[x] insert packets into ip linkedlist


[x] tcp client/server
```
