<div align="center">
  <h1>write-to-console</h1>
  A simple program, which demonstrates how to write to the standard output
</div>

## Authors

- [umut-sahin](https://github.com/umut-sahin) - Umut Şahin \<umutsahin@protonmail.com>

## Prerequisites

None

## Description

This program uses a single [**printf**] function call to write "Hello World!" to the standard output.
Nothing fancy.

## Usage

```
$ make run target=write-to-console
```

## Arguments and flags

None

## Example run

```
$ make run target=write-to-console
Hello World!
```

## Known bugs

None

## Limitations

None

## Notes

- The [**printf**] function does not print a newline character after printing the formatted string.
  So an explicit `\n` is added to the end of the format string.

## Further reading

None


[//]: # (Links)

[**printf**]:
  http://man7.org/linux/man-pages/man3/printf.3.html
