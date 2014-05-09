Proceso
=======

[![Build Status](https://travis-ci.org/bry4n/proceso.svg?branch=master)](https://travis-ci.org/bry4n/proceso)

Proceso is a ruby gem to collect the process information. **This is still experimental**.  See [Contributing](#contributing) if you find problem or can improve this gem.

* [Information](#information)
* [Installation](#installation)
* [Usage](#usage)
* [List of available methods](#list-of-available-methods)
* [Credits](#credits)
* [Contributing](#contributing)
* [License](#license)

## Information

I have developed this project against the following:

* Ruby 2.0
* OSX 10.9.1
* Vagrant - Ubuntu 13.04 (raring) - experimental

## Installation

```
gem install proceso
```

Gemfile

```
gem 'proceso'
```


## Usage

```
require 'proceso'

irb(main):001:0> process = Proceso::PID.new($$)
=> #<Proceso::PID:0x007f51a5d09208 @pid=13455>

irb(main):002:0> process.running?
=> true

irb(main):003:0> process.resident_size
=> 4794
```

### List of Proceso methods

| METHOD NAME | DESCRIPTION | TYPE |
|------------|:--------------:|:----:|
| Proceso.current | Grab current process instance | Proceso::PID object |
| Proceso::PID#running? | Check if process is running or not | Boolean |
| Proceso::PID#command | Grab the process command line and arguments| String |
| Proceso::PID#executable | Grab the path of command name | String |
| Proceso::PID#path | Grab the path of command line | String |
| Proceso::PID#resident_size | Grab current resident size | Integer |
| Proceso::PID#virtual_size | Grab current virtual resident size | Integer |
| Proceso::PID#user_cpu_times | Grab current User CPU ticks | Integer |
| Proceso::PID#system_cpu_times | Grab current System CPU ticks | Integer |

**FYI**: Linux returns resident and virtual size in kilobytes. OSX shows them in bytes.


## Credits

[psutil](https://code.google.com/p/psutil/) and [procps](procps.sourceforge.net) helped me to learn more about OS' powerful C libraries (kern_proc, sysctl, task_info, etc).

## Contributing

If you wish to contribute to this project, please:

* Fork this project on GitHub
* If it involves code, please also write tests for it
* Push your change to a named branch
* Send a pull request

## License

Proceso is licensed under the MIT license.
