require 'spec_helper'

describe Proceso::PID do

  let(:process) { Proceso::PID.new($$) }

  it "should create new Process object with pid" do
    expect { Proceso::PID.new($$) }.to_not raise_error
  end

  it "creates new Base object without argument will raise error" do
    expect { Proceso::PID.new }.to raise_error
  end

  it "should be running" do
    process.running?.should be_true
  end

  it "should return process command" do
    process.command.should =~ /ruby/
  end

  it "should return executable name" do
    process.executable.should == "ruby"
  end

  it "should return path name" do
    process.path.should =~ /bin$/
  end

  it "should return resident size in bytes" do
    process.resident_size.should be_kind_of(Numeric)
    process.stub(:resident_size).and_return(100)
    process.resident_size.should == 100
  end

  it "should return virtual size in bytes" do
    process.virtual_size.should be_kind_of(Numeric)
    process.stub(:virtual_size).and_return(100)
    process.virtual_size.should == 100
  end

  it "should return user cpu times" do
    process.user_cpu_times.should be_kind_of(Float)
    process.stub(:user_cpu_times).and_return(0.1)
    process.user_cpu_times.should == 0.1
  end

  it "should return system cpu times" do
    process.system_cpu_times.should be_kind_of(Float)
    process.stub(:system_cpu_times).and_return(0.1)
    process.system_cpu_times.should == 0.1
  end

  it "should return mem size" do
    process.mem_size.should be_kind_of(Numeric)
    rss = process.resident_size
    process.stub(:resident_size).and_return(rss)
    rss *= 1024 if RUBY_PLATFORM =~ /linux/
    process.mem_size.should == rss
    process.mem_size(:kb).should == (rss / 1024.0)
    process.mem_size(:mb).should == (rss / 1024.0 / 1024.0)
    process.mem_size(:gb).should == (rss / 1024.0 / 1024.0 / 1024.0)
  end

end
