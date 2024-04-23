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
* macOS 14 system Ruby (still 2.6 - beware)
* macOS Homebrew, RBEnv, RVM
* macOS bespoke installation
* Ubuntu Jammy bespoke, RBEnv, RVM

And Ruby versions:
* 2.6 - 3.3

## Usage

`CRuby` comes set up to use the macOS system Ruby, and Xcode to provide C
headers.

If you want to use a different Ruby then use the `cfg-cruby` script to
rewrite the build config files.

For options other than macOS system Ruby, `cfg-cruby` generates a custom
pkg-config file called `CRuby.pc` for `swift build`, and an Xcconfig file
called `CRuby.xcconfig` for Xcode.

### Swift Package Manager

Include this repo as a dependency in your project:
```swift
.package(url: "https://github.com/johnfairh/CRuby/", majorVersion: 2)
```

To use a Ruby other than macOS system default you need to reconfigure.  For
example to set up Ruby 3.3.0 managed by `rbenv`:
```shell
swift package edit CRuby
./Packages/CRuby/cfg-cruby --mode rbenv --name 3.3.0
export PKG_CONFIG_PATH=$(pwd)/Packages/CRuby:$PKG_CONFIG_PATH
swift build
```
Either leave the `CRuby` package in edit mode or fork the repo, use that fork
as your remote, and push your customizations back there.

### Xcode

Include this repo in your project.  A git submodule works well.  So either way
you have a directory called `CRuby`.  Then go to *Build Settings* for the Target
where you want to do `import CRuby` and find *Import Paths* under *Swift
Compiler - Search Paths*.  Add the path to your `CRuby` directory - you can
use `${SRCROOT}` to substitute for the directory containing the project file.

Check Xcode is happy with an `import CRuby` line.  This is using the macOS
system default Ruby, probably a very old 2.6.

If you want to use a different Ruby, run `cfg-cruby`.  This creates a file
called `CRuby.xcconfig` that you need to include in the appropriate targets.
Start [here](https://nshipster.com/xcconfig/) for help with using xcconfig
files.

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
