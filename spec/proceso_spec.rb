require "spec_helper"

describe Proceso do

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

  it "should be existed" do
    process.exists?.should be_true
  end

  it "should return process command" do
    process.command.should =~ /ruby/
  end

  it "should return resident size in bytes" do
    process.resident_size.should be_kind_of(Numeric)
  end

  it "should return virtual size in bytes" do
    process.virtual_size.should be_kind_of(Numeric)
  end

  it "should return cpu usage" do
    process.cpu_usage.should be_kind_of(Float)
  end

  it "should return user cpu times" do
    process.user_cpu_times.should be_kind_of(Float)
  end

  it "should return system cpu times" do
    process.system_cpu_times.should be_kind_of(Float)
  end

end