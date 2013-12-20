Update me

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

pid = Proceso::PID.new(Process.pid)

pid.running?

pid.mem_size

pid.cpu_usage

pid.user_cpu_times

pid.virtual_size



```

## Rack Middleware

**Rails**

```ruby

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