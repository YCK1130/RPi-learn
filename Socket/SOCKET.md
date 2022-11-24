# Problem

## What is File descriptor

-   A number that uniquely identifies an open file in a computer's operating system.
-   On a Unix-like operating system, the first three file descriptors, by default, are

    -   0 : STDIN (standard input)

    -   1 : STDOUT (standard output)
    -   2 : STDERR (standard error).

### Redirecting

You can hide stderr by redirecting file descriptor 2 to /dev/null, the special device in Linux that "goes nowhere":

```shell
find / -name '*something*' 2>/dev/null
```

where "2" means _STDERR_ , which is redirected to print output lines to /dev/null

You also can redirect stderr to stdout

```shell
find / -name '*something*' 2>&1
```

## What happens after `accept()`

accept will wait a client to connect, and, thus, blocking the program.

when a `connect` is established `accept` will return a new socket

## Difference between `write()` and `fprintf()`

`write` is a system call: it sends the given characters directly to the operating system, which (in theory, and often in practice) sends them immediately to the output device such as the screen or disk.

`fprintf` (and `fwrite` and anything that takes a `FILE *` argument) is a library call, which buffers, or collects, the data inside your program before sending it. This allows it to send larger, more uniform chunks of data, which improves efficiency.

### write

-   system call
-   immediate sending to its output
-   wait os to check whether the write succeeded
-   designed for writing binary data

### fprintf

-   library call
-   faster in pretty much every other way and is the general correct choice
-   designed for writing string

## Blocking I/O vs non-blocking I/O

[Blocking 與 Non-blocking I/O](https://ithelp.ithome.com.tw/articles/10161404)

[非同步程式設計(async)和 non-blocking IO](https://medium.com/@fcamel/%E9%9D%9E%E5%90%8C%E6%AD%A5%E7%A8%8B%E5%BC%8F%E8%A8%AD%E8%A8%88%E5%92%8C-non-blocking-io-a43881081aac)

[淺談 I/O Model](https://medium.com/@clu1022/%E6%B7%BA%E8%AB%87i-o-model-32da09c619e6)

# Reference

[Code Reference](http://zake7749.github.io/2015/03/17/SocketProgramming/)

[What is Web Socket](https://ithelp.ithome.com.tw/m/articles/10302287)

[What is File descriptor](https://www.computerhope.com/jargon/f/file-descriptor.htm)

[Blocking 與 Non-blocking I/O](https://ithelp.ithome.com.tw/articles/10161404)

[非同步程式設計(async)和 non-blocking IO](https://medium.com/@fcamel/%E9%9D%9E%E5%90%8C%E6%AD%A5%E7%A8%8B%E5%BC%8F%E8%A8%AD%E8%A8%88%E5%92%8C-non-blocking-io-a43881081aac)

[淺談 I/O Model](https://medium.com/@clu1022/%E6%B7%BA%E8%AB%87i-o-model-32da09c619e6)

# waiting multiple client

## io multiplexing

select, poll
