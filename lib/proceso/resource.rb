module Proceso
  class Resource

    %w( utime stime maxrss ixrss idrss isrss
        minflt majflt nswap inblock oublock
        msgsnd msgrcv nsignals nvcsw nivcsw
      ).each do |name|
      define_method name do
        usage[name]
      end
    end

  end
end