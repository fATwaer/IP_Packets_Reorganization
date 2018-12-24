# IP_Packets_Reorganization
FreeBSD Implementation

## Platform
``` 
x64 GNU/Linux
gcc version 8.2.1 
Code::Blocks 17.12
```
## Example

``` bash
[server]
$ ./FreeBSDPacketsReorganization -s

[client]
$./FreeBSDPacketsReorganization -c 127.0.0.1 -p 6777

```



## Souce File Layout

``` 
├── bin
│   └── Debug
│       └── FreeBSDPacketsReorganization
├── client.c
├── inc
│   ├── client.h
│   ├── ipf_opt.h
│   ├── ip_packet.h
│   ├── ipq.h
│   ├── ipq_opt.h
│   ├── ip_queue.h
│   ├── paser.h
│   ├── server
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
├── paser.c
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

[] drop packet when time out
	- [x] time parmeter

[x] tcp client/server
```
