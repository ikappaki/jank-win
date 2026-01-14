# jank on MS-Windows

This repository contains **jank** ported to Windows, based on the snapshot of the code as of October 6, 2025, just before the transition from Clang 21 to Clang 22. 

The only current limitation is that exceptions thrown by the C++ backend are not yet supported. An open ticket for this issue exists in the `llvm-project`.

## Building jank

First, [install MSYS2](https://www.msys2.org/). MSYS2 provides a Unix like environment and toolchains for building native Windows software. Each MSYS2 installation is fully isolated when installed in a separate directory.

Open the **CLANG64** shell and clone the jank win repository:
```sh
git clone --recurse-submodules https://github.com/ikappaki/jank-win.git

# If you didn't recurse submodules when cloning, you'll need to run this.
git submodule update --init --recursive --jobs 8
```

Install dependencies:
```sh
pacman -S mingw-w64-clang-x86_64-git-lfs mingw-w64-clang-x86_64-cmake mingw-w64-clang-x86_64-dlfcn mingw-w64-clang-x86_64-boost mingw-w64-clang-x86_64-libffi mingw-w64-clang-x86_64-doctest mingw-w64-clang-x86_64-libzip mingw-w64-clang-x86_64-gc
```

Download and install a precompiled *clang64* package with the required jank patches, If you prefer, instructions for building it locally are provided further below:
```sh
cd compiler+runtime
./bin/msys2-clang64-install.sh

```

You can now follow the official [jank build instructions](compiler+runtime/doc/build.md]).

## Quick summary

**Release build**
```sh
cd compiler+runtime
./bin/configure -GNinja -DCMAKE_BUILD_TYPE=Release
./bin/compile
```

**Debug build**
```sh
cd compiler+runtime
./bin/configure -GNinja -DCMAKE_BUILD_TYPE=Debug -Djank_test=on
./bin/compile
```

**Running the REPL**
```sh
cd compiler+runtime
./build/jank repl
```

## Compiling Clang/LLVM

Open an MSYS2 **CLANG64** shell and follow these steps:

Clone the patched MSYS2 `MINGW-packages` repository and build the LLVM packages:
```sh
# Clone the repository
git clone https://github.com/ikappaki/MINGW-packages.git

# Switch to the branch with the jank Clang 21 patches
git switch jank-clang-21

# Install essential build dependencies
pacman -S base-devel git

# Build the LLVM packages (this may take an hour or two)
cd mingw-w64-llvm
makepkg-mingw -sLf --skipchecksums --skippgpcheck --nocheck

```

Install the built packages into your environment:
```sh
pacman -U ./*.pkg.tar.zst

```

Everything below this section is the original `README.md` content.

----
<a href="https://jank-lang.org">
  <img src="https://media.githubusercontent.com/media/jank-lang/jank/main/.github/img/banner.png" alt="jank banner" />
</a>

<div align="center">
  <a href="https://clojurians.slack.com/archives/C03SRH97FDK" target="_blank"><img src="https://img.shields.io/badge/slack-%23jank-e01563.svg?style=flat&logo=slack&logoColor=fd893f&colorA=363636&colorB=363636" /></a>
  <a href="https://github.com/sponsors/jeaye" target="_blank"><img src="https://img.shields.io/github/sponsors/jeaye?style=flat&logo=github&logoColor=fd893f&colorA=363636&colorB=363636" /></a>
  <a href="https://twitter.com/jeayewilkerson" target="_blank"><img src="https://img.shields.io/twitter/follow/jeayewilkerson?style=flat&logo=x&logoColor=fd893f&colorA=363636&colorB=363636" /></a>
  <br/>
  <a href="https://github.com/jank-lang/jank/actions" target="_blank"><img src="https://img.shields.io/github/actions/workflow/status/jank-lang/jank/build.yml?branch=main&style=flat&logo=github&logoColor=fd893f&colorA=363636&colorB=363636" alt="CI" /></a>
  <a href="https://codecov.io/gh/jank-lang/jank" target="_blank"><img src="https://img.shields.io/codecov/c/github/jank-lang/jank?style=flat&logo=codecov&logoColor=fd893f&colorA=363636&colorB=363636" /></a>
</div>

# What is jank?

Most simply, jank is a [Clojure](https://clojure.org/) dialect on LLVM with C++ interop.
Less simply, jank is a general-purpose programming language which embraces the interactive,
functional, value-oriented nature of Clojure and the desire for the native
runtime and performance of C++. jank aims to be strongly compatible with
Clojure. While Clojure's default host is the JVM and its interop is with Java,
jank's host is LLVM and its interop is with C++.

For the current progress of jank and its usability, see the tables here: https://jank-lang.org/progress/

**jank is expected to have its alpha launch in December 2025!**

## Docs
* [Installing jank](./compiler+runtime/doc/install.md)
* [Building jank](./compiler+runtime/doc/build.md)
* [Using jank with Leiningen](./lein-jank/README.md)
* [Using jank with Clojure CLI](./clojure-cli/README.md)

## Appetizer
```clojure
; Comments begin with a ;
(println "meow") ; => nil

; All built-in data structures are persistent and immutable.
(def george {:name "George Clooney"}) ; => #'user/george

; Though all data is immutable by default, side effects are adhoc.
(defn say-hi [who]
  (println (str "Hi " (:name who) "!"))
  (assoc who :greeted? true))

; Doesn't change george.
(say-hi george) ; => {:name "George Clooney"
                ;     :greeted? true}

; Many core functions for working with immutable data.
(apply + (distinct [12 8 12 16 8 6])) ; => 42

; Interop with C++ can happen *seamlessly*.
(defn sleep [ms]
  (let [duration (cpp/std.chrono.milliseconds ms)]
    (cpp/std.this_thread.sleep_for duration)))
```

## Sponsors
If you'd like your name, company, or logo here, you can
[sponsor this project](https://github.com/sponsors/jeaye) for at least $25/m.

<br/>

<p align="center">
  <a href="https://www.clojuriststogether.org/">
    <img src="https://www.clojuriststogether.org/header-logo.svg" height="100px">
  </a>
</p>

<p align="center">
  <a href="https://nubank.com.br/">
    <img src="https://upload.wikimedia.org/wikipedia/commons/f/f7/Nubank_logo_2021.svg" height="100px">
  </a>
</p>

<!-- mkarp -->
<p align="center">
  <a href="https://pitch.com/">
    Misha Karpenko
  </a>
</p>

<!-- stijlist -->
<p align="center">
  <a href="http://www.somethingdoneright.net/about">
    Bert Muthalaly
  </a>
</p>

<!-- modulr-software -->
<p align="center">
  <a href="https://github.com/modulr-software">
    modulr-software
  </a>
</p>

<!-- multiplyco -->
<p align="center">
  <a href="https://multiply.co/">
    multiply.co
  </a>
</p>

<!-- keychera -->
<p align="center">
  <a href="https://keychera.github.io/">
    keychera
  </a>
</p>

## In the news
<div align="center">

| [<img src="https://i0.wp.com/2023.clojure-conj.org/wp-content/uploads/2019/06/clojure.png?resize=150%2C150&ssl=1" height="100px"><br /><sub><b>Clojure Conj 2023</b></sub>](https://www.youtube.com/watch?v=Yw4IAY4Nx_o)<br />        | [<img src="https://user-images.githubusercontent.com/1057635/193151333-449385c2-9ddb-468e-b715-f149d173e310.svg" height="100px"><br /><sub><b>The REPL Interview</b></sub>](https://www.therepl.net/episodes/44/)<br /> |  [<img src="https://github.com/jank-lang/jank/assets/1057635/72ff097c-578c-46f8-a727-aae6dcf2a82f" width="100px"><br /><sub><b>Language Introduction</b></sub>](https://youtu.be/ncYlHfK25i0)<br />          | [<img src="https://github.com/jank-lang/jank/assets/1057635/9788a7c8-93da-47ea-8d1d-8a258a747942" width="100px"><br /><sub><b>Compiler Spotlight</b></sub>](https://compilerspotlight.substack.com/p/language-showcase-jank)<br /> |
| :-----------------------------------------------------------------------------------------------------------------------------------------------------------------: | :-----------------------------------------------------------------------------------------------------------------------------------------------------------------------: | :-: | :-: |

</div>
