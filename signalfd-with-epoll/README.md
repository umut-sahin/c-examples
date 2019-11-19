<div align="center">
  <h1>signalfd-with-epoll</h1>
  A slightly complicated program to show how to use the <a href="http://man7.org/linux/man-pages/man7/epoll.7.html">epoll</a> interface to catch the <a href="https://en.wikipedia.org/wiki/Signal_(IPC)">POSIX signals</a> using a file like interface
</div>

## Authors

- [umut-sahin](https://github.com/umut-sahin) - Umut Şahin \<umutsahin@protonmail.com>

## Prerequisites

- [write-to-console]

## Description

TODO

## Usage

```
$ make run target=signalfd-with-epoll
```

## Arguments and flags

None

## Example run

Run the following command then resize the terminal window.

```
$ make run target=signalfd-with-epoll
Caught resize signal (Now have 24 rows and 81 columns)...
Caught resize signal (Now have 24 rows and 82 columns)...
Caught resize signal (Now have 24 rows and 83 columns)...
Caught resize signal (Now have 24 rows and 84 columns)...
Caught resize signal (Now have 25 rows and 84 columns)...
Caught resize signal (Now have 25 rows and 83 columns)...
Caught resize signal (Now have 26 rows and 83 columns)...
Caught resize signal (Now have 26 rows and 82 columns)...
^CCaught termination signal...
```

## Known bugs

None

## Limitations

- Some environments don't support the **SIGWINCH** signal.
  Thus, the output of the program may change from environment to environment.

## Notes

- [epoll] interface has some pretty severe quirks, especially around [fork] and [exec] syscalls.
  Thus, it should be used with great care.

## Further reading

- [signalfd is useless]
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
[signalfd is useless]:
  https://ldpreload.com/blog/signalfd-is-useless
[signalfd-with-epoll]:
  https://github.com/umut-sahin/c-examples/tree/master/signalfd-with-epoll
[write-to-console]:
  https://github.com/umut-sahin/c-examples/tree/master/write-to-console
