<div align="center">
  <h1>tcp-echo-server-with-epoll</h1>
  A slightly complicated program to show how to use the <a href="http://man7.org/linux/man-pages/man7/epoll.7.html">epoll</a> interface to create a <a href="https://en.wikipedia.org/wiki/Transmission_Control_Protocol">TCP</a> server, which echoes back what the client writes after successfully connecting.
</div>

## Authors

- [umut-sahin](https://github.com/umut-sahin) - Umut Şahin \<umutsahin@protonmail.com>

## Prerequisites

- [http-hello-world-server]
- [signalfd-with-epoll]

## Description

TODO

## Usage

```
$ make run target=tcp-echo-server-with-epoll
```

## Arguments and flags

None

## Example run

```
$ make run target=tcp-echo-server-with-epoll

```
Then, in another terminal
```
$ nc 127.0.0.1 8000
Hello World!
Hello World!
Goodbye World!
Goodbye World!
^C
```

## Known bugs

None

## Limitations

None

## Notes

- [epoll] interface has some pretty severe quirks, especially around [fork] and [exec] syscalls.
  Thus, it should be used with great care.

## Further reading

- [Epoll is fundamentally broken 1/2]
- [Epoll is fundamentally broken 2/2]


[//]: # (Links)

[epoll]:
  http://man7.org/linux/man-pages/man7/epoll.7.html
[Epoll is fundamentally broken 1/2]:
  https://idea.popcount.org/2017-02-20-epoll-is-fundamentally-broken-12/
[Epoll is fundamentally broken 2/2]:
  https://idea.popcount.org/2017-03-20-epoll-is-fundamentally-broken-22/
[exec]:
  http://man7.org/linux/man-pages/man3/exec.3.html
[fork]:
  http://man7.org/linux/man-pages/man2/fork.2.html
[http-hello-world-server]:
  https://github.com/umut-sahin/c-examples/tree/master/http-hello-world-server
[signalfd-with-epoll]:
  https://github.com/umut-sahin/c-examples/tree/master/signalfd-with-epoll
