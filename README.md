<!--
CRuby
README.md
Distributed under the MIT license, see LICENSE.
-->

![Platforms](https://img.shields.io/badge/platform-macOS%20%7C%20linux-lightgrey.svg)
![License](https://cocoapod-badges.herokuapp.com/l/RubyGateway/badge.png)

# CRuby

Wrap `libruby` for SwiftPM or Xcode.  Easily reconfigure for your Ruby
installation.

See [RubyGateway](https://github.com/johnfairh/RubyGateway) for a high-level
Swift-Ruby integration framework.

Tested with environments:
* macOS 11 system Ruby
* macOS Homebrew, RBEnv, RVM
* macOS bespoke installation
* Ubuntu 20.04 x86_64 RBEnv, RVM, bespoke

And Ruby versions:
* 2.6, 2.7, 3.0, 3.1, 3.2

## Usage

`CRuby` comes set up to use the macOS system Ruby, and Xcode to provide C
headers.

If you want to use a different Ruby then use the `cfg-cruby` script to
rewrite the build config files.

For options other than macOS system Ruby, `cfg-cruby` generates a custom
pkg-config file called `CRuby.pc` that can be passed directly to `swift build`
or manually copied into your Xcode project settings.

Ruby 3's C interface header files use a non-default feature of Clang, the
C compiler that the Swift tools use.  Because of interesting Swift design
choices, you must pass the `-fdeclspec` Clang flag when building a target
that depends on CRuby.

### Swift Package Manager

Include this repo as a dependency in your project:
```swift
.package(url: "https://github.com/johnfairh/CRuby/", majorVersion: 2)
```

To use a Ruby other than macOS system default you need to reconfigure.  For
example to set up Ruby 2.4.1 managed by `rbenv`:
```shell
swift package edit CRuby
./Packages/CRuby/cfg-cruby --mode rbenv --name 2.7.3
export PKG_CONFIG_PATH=$(pwd)/Packages/CRuby:$PKG_CONFIG_PATH
swift build
```
Either leave the `CRuby` package in edit mode or fork the repo, use that fork
as your remote, and push your customizations back there.

If you are using Ruby 3 then you must pass an extra flag through to the C
compiler:
```
swift build -Xcc -fdeclspec
```

### Xcode

Include this repo in your project.  A git submodule works well.  So either way
you have a directory called `CRuby`.  Then go to *Build Settings* for the Target
where you want to do `import CRuby` and find *Import Paths* under *Swift
Compiler - Search Paths*.  Add the path to your `CRuby` directory - you can
use `${SRCROOT}` to substitute for the directory containing the project file.

Check Xcode is happy with an `import CRuby` line.

If you want to use a different Ruby, run `cfg-cruby`.  Now transfer the settings
from the `CRuby.pc` to the Xcode build settings for the target:
1. Find *Header Search Paths* under *Search Paths* and add the directories
   mentioned in the `Cflags:` line of `CRuby.pc`.  Don't copy over the `-I` part,
   just the paths.
2. Find *Library Search Paths* under *Search Paths* and add the directories
   mentioned in the `Libs:` line of `CRuby.pc`.  Don't copy over the `-L` part,
   just the paths.  Ignore any `-l` flags [please tell me if you find a case
   where this breaks].
3. If you are using Ruby 3, find *Other Swift Flags* under *Swift Compiler - Custom Flags*
   and add two flags: `-Xcc` `-fdeclspec`.

That's it: Xcode should now resolve `CRuby` against your chosen version.

## Supported Ruby Configs

### macOS system

Use the `xcode-select`ed Xcode:
```shell
cfg-cruby --mode xcode
```
This configuration does not require a pkg-config file.

### macOS Homebrew or Linux -dev package

```shell
cfg-cruby --mode pkgconfig --name <pkg-name>
```
Use `pkg-config --list-all` to see what you have installed.

The pkg-config setup is not directly consumable by SwiftPM.  `cfg-cruby` uses
it to create the `CRuby.pc` that is compatible with SwiftPM.

### RBEnv or RVM

```shell
cfg-cruby --mode rbenv --name <version>
```

or

```shell
cfg-cruby --mode rvm --name <ruby name>
```

### Something else

If you've built Ruby yourself or are using a different version manager that
preserves the regular layout then:

```shell
cfg-cruby --path <full path to Ruby directory>
```

The path required is one to a directory that is called `ruby-*something*` and
contains subdirectories including `lib`, `include`, and `bin`.

## Contributions

Welcome - github / johnfairh@gmail.com

## License

Distributed under the MIT license.
