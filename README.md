Proceso
=======

[![Build Status](https://travis-ci.org/bry4n/proceso.svg?branch=master)](https://travis-ci.org/bry4n/proceso)

Proceso is a ruby gem to collect the process information.

* [Information](#information)
* [Installation](#installation)
* [Usage](#usage)
* [List of available methods](#list-of-available-methods)
* [Rack Middleware](#rack-middleware)
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

### List of available methods

**Proceso.current** - Current process

**Proceso::PID#running?** -- Process alive?

**Proceso::PID#command** -- Process Command Line

**Proceso::PID#executable** -- Process Command Name

**Proceso::PID#path** -- Path of Process Command Line

**Proceso::PID#resident_size** -- Process Resident Size (memory)

**Proceso::PID#resident_size** -- Process Virtual Size

Note: Linux returns resident size value in kilobytes. OSX returns value in bytes.

**Proceso::PID#mem_size** -- Process Memory Size (RSS)

**Proceso::PID#user_cpu_times** -- Process User CPU ticks

**Proceso::PID#system_cpu_times** -- Process System CPU ticks

## Rack Middleware

You can monitor your Ruby on Rails project's memory usage and cpu usage.

**Rails**

```

# config/application.rb

config.middleware.use Proceso::Middleware


# config/initializers/proceso.rb

Proceso::Middleware.report

# or

Proceso::Middleware.subscribe do |name, start, finish, id, payload|
  puts
  puts "******* PROCESO INFORMATION *******"
  mem_used = (payload[:mem_used].to_f / 1024.0).round(1)
  cpu_used = payload[:cpu_used].to_f.round(1)
  resp_time = payload[:resp_time]
  path     = payload[:request].path_info
  puts "MEM: #{mem_used} CPU: #{cpu_used} RESP: #{resp_time} PATH: #{path}"
  puts "******* END OF PROCESO INFORMATION *******"
  puts
end

```

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
