<div align="center">
  <h1>C Examples</h1>
  Various code examples in C to show how to get things done in an idiomatic way
</div>

## Installing

You need to have a **C compiler**, which supports the [C11] standard, and [CMake] **v3.9** or higher installed in order to run the examples.

Some examples depend on external libraries. 
Those external libraries' availability are checked by [CMake] before the build. 
So if you got a [CMake] error, it's probably because of a missing library.
Anyway, to install run the examples, just clone the repository using the following commands, and you are good to go.

```
$ git clone https://github.com/umut-sahin/c-examples.git
$ cd c-examples
```

## Building

You can use the following command to build every single example.

```
$ make build verbose=1
```

## Running a specific example

```
$ make run target=<example-name>
```

Also, you can pass arguments like so

```
$ make run target=<example-name> args="[arguments...]"
```

Note that there are some examples, which are in the form of a library, therefore, does not come with an executable. 
For those examples, you may use the test command like so

```
$ make test target=<example-name>
```

## Available examples

- [command-line-arguments]
- [http-hello-world-server]
- [memory-mapped-io]
- [parking-pthreads]
- [pthreads]
- [read-from-console]
- [signalfd-with-epoll]
- [tcp-echo-server-with-epoll]
- [write-to-console]

## Changelog

See [CHANGELOG].

## License

This repository is released under [MIT license].
Please see the [LICENSE] for further information.

## Contributing

Contributions are welcome!
Please see [CONTRIBUTING] for guidance.

## Authors

See [AUTHORS].


[//]: # (Links)

[AUTHORS]:
  https://github.com/umut-sahin/c-examples/blob/master/AUTHORS.md
[C11]:
  https://en.wikipedia.org/wiki/C11_(C_standard_revision)
[CHANGELOG]:
  https://github.com/umut-sahin/c-examples/blob/master/CHANGELOG.md
[CMake]:
  https://cmake.org/
[command-line-arguments]:
  https://github.com/umut-sahin/c-examples/tree/master/command-line-arguments
[CONTRIBUTING]:
  https://github.com/umut-sahin/c-examples/blob/master/CONTRIBUTING.md
[http-hello-world-server]:
  https://github.com/umut-sahin/c-examples/tree/master/http-hello-world-server
[LICENSE]:
  https://github.com/umut-sahin/c-examples/blob/master/LICENSE
[memory-mapped-io]:
  https://github.com/umut-sahin/c-examples/tree/master/memory-mapped-io
[MIT License]:
  https://tldrlegal.com/license/mit-license
[parking-pthreads]:
  https://github.com/umut-sahin/c-examples/tree/master/parking-pthreads
[pthreads]:
  https://github.com/umut-sahin/c-examples/tree/master/pthreads
[read-from-console]:
  https://github.com/umut-sahin/c-examples/tree/master/read-from-console
[signalfd-with-epoll]:
  https://github.com/umut-sahin/c-examples/tree/master/signalfd-with-epoll
[tcp-echo-server-with-epoll]:
  https://github.com/umut-sahin/c-examples/tree/master/tcp-echo-server-with-epoll
[write-to-console]:
  https://github.com/umut-sahin/c-examples/tree/master/write-to-console
