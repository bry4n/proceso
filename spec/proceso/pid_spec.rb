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
    process.stub(:resident_size).and_return(100)
    process.resident_size.should be_kind_of(Numeric)
    process.resident_size.should == 100
  end

  it "should return virtual size in bytes" do
    process.stub(:virtual_size).and_return(100)
    process.virtual_size.should be_kind_of(Numeric)
    process.virtual_size.should == 100
  end

  it "should return cpu usage" do
    process.stub(:cpu_usage).and_return(0.1)
    process.cpu_usage.should be_kind_of(Float)
    process.cpu_usage.should == 0.1
  end

  it "should return user cpu times" do
    process.stub(:user_cpu_times).and_return(0.1)
    process.user_cpu_times.should be_kind_of(Float)
    process.user_cpu_times.should == 0.1
  end

  it "should return system cpu times" do
    process.stub(:system_cpu_times).and_return(0.1)
    process.system_cpu_times.should be_kind_of(Float)
    process.system_cpu_times.should == 0.1
  end

  it "should return mem size" do
    rss = 10000000000
    process.stub(:resident_size).and_return(rss)
    process.mem_size.should == rss
    process.mem_size(:kb).should == (rss / 1024.0)
    process.mem_size(:mb).should == (rss / 1024.0 / 1024.0)
    process.mem_size(:gb).should == (rss / 1024.0 / 1024.0 / 1024.0)
  end

end
