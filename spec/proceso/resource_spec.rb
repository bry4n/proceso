require 'spec_helper'

describe Proceso::Resource do

  let(:resource) { Proceso::Resource.new($$) }

 %w( utime stime maxrss ixrss idrss isrss
        minflt majflt nswap inblock oublock
        msgsnd msgrcv nsignals nvcsw nivcsw
      ).each do |name|
    it "should return #{name} value" do

      resource.send(name).should_not be_nil

    end

  end
end