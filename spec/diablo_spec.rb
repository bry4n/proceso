require "spec_helper"

describe Diablo do

  let(:process) { Diablo::Process.new($$) }

  it "should create new Process object with pid" do
    expect { Diablo::Process.new($$) }.to_not raise_error
  end

  it "creates new Base object without argument will raise error" do
    expect { Diablo::Process.new }.to raise_error
  end

  it "should return process name" do
    process.name.should =~ /ruby/
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

end