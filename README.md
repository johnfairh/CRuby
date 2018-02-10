# CRuby

Wrap `libruby` for SwiftPM 4.  Easily reconfigure for your Ruby installation.

Tested with:
* macOS 10.13 system Ruby
* macOS Homebrew, RBEnv, RVM
* macOS bespoke installation
* Ubuntu 14.04 x86_64 Brightbox ruby2.4-dev
* Ubuntu 14.04 x86_64 RBEnv, RVM

## Usage

Include this repo as a dependency in your project:
```swift
.package(url: "https://github.com/johnfairh/CRuby/", majorVersion: 1)
```

`CRuby` comes set up to use the macOS system Ruby and the Xcode installed in
`/Applications/Xcode.app`.  If you want to use a different Ruby then you have
to use the `cfg-cruby` script to rewrite the package files, for example:
```shell
swift package edit CRuby
./Packages/CRuby/cfg-cruby --mode rbenv --name 2.4.1
export PKG_CONFIG_PATH=$(pwd)/Packages/CRuby/CRuby.pc:$PKG_CONFIG_PATH
swift build
```
Either leave the `CRuby` package in edit mode or fork the repo, use that fork
as your source, and push your customizations back there.

## Configs

### Xcode

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

Welcome - github / johnfairh@gmail.com.

## License

Distributed under the MIT license.
